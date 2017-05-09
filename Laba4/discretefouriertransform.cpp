#include "discretefouriertransform.h"
#include <math.h>

Transform *DiscreteFourierTransform::instance = nullptr;

DiscreteFourierTransform::DiscreteFourierTransform()
{

}

QVector<std::complex<double>> * DiscreteFourierTransform::directTransform(const QVector<std::complex<double>> & data)
{
    lastSize = data.size();
    if(zeroing)
    {
        addOperations = 0;
        mulOpirations = 0;
        powOperations = 0;
    }
    QVector<std::complex<double>> *result = new QVector<std::complex<double>>(data.size());
    std::complex<double> e(exp(1.0), 0);
    for(int k = 0;k<data.size();k++)
    {
        std::complex<double> w = std::pow(e, -2. * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size())); //W=e^(-2*pi*i/N)
        mulOpirations += 4;
        powOperations += 1;
        std::complex<double> summ(0,0);
        for(int m = 0;m<data.size();m++)
        {
            summ += data[m] * std::pow(w, k * m);
            addOperations += 1;
            mulOpirations += 2;
            powOperations += 1;
        }
        (*result)[k]= summ / static_cast<double>(data.size());
        mulOpirations += 1;
    }
    return result;
}

QVector<std::complex<double> > *DiscreteFourierTransform::directTransform(const QVector<double> &data)
{
    QVector<std::complex<double>> u(data.size());
    for (int i = 0;i<data.size();i++)
    {
        u[i] = std::complex<double>(data[i], 0);
    }
    return directTransform(u);
}

QVector<double> *DiscreteFourierTransform::inverseTransform(const QVector<std::complex<double>> &data)
{
    QVector<double> *result = new QVector<double>(data.size());
    std::complex<double> e(exp(1.0), 0);
    for(int m = 0; m < data.size(); m++)
    {
        std::complex<double> w = std::pow(e, 2. * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size())); //W=e^(-2*pi*i/N)
        double summ = 0;
        for(int k = 0; k < data.size(); k++)
        {
            summ += (data[k] * std::pow(w, k * m)).real();
        }
        (*result)[m]= summ;
    }
    return result;
}

Transform *DiscreteFourierTransform::getInstance()
{
    if (instance == nullptr) {
        instance = new DiscreteFourierTransform();
    }
    return instance;
}
