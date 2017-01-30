#include "discretefouriertransform.h"
#include <math.h>

DiscreteFourierTransform::DiscreteFourierTransform()
{

}

QVector<std::complex<double>> DiscreteFourierTransform::directTransform(QVector<double> data)
{
    QVector<std::complex<double>> *result = new QVector<std::complex<double>>(data.size());
    std::complex<double> e(exp(1.0), 0);
    for(int k = 0;k<data.size();k++)
    {
        std::complex<double> w = std::pow(e, -2. * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size())); //W=e^(-2*pi*i/N)
        std::complex<double> summ(0,0);
        for(int m = 0;m<data.size();m++)
        {
            summ += data[m] * std::pow(w, k * m);
        }
        (*result)[k]= summ / static_cast<double>(data.size());
    }
    return *(result);
}

QVector<double> DiscreteFourierTransform::inverseTransform(QVector<std::complex<double>> data)
{
    QVector<double> *result = new QVector<double>(data.size());
    std::complex<double> e(exp(1.0), 0);
    for(int m = 0;m<data.size();m++)
    {
        std::complex<double> w = std::pow(e, -2. * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size())); //W=e^(-2*pi*i/N)
        double summ = 0;
        for(int k = 0;k<data.size();k++)
        {
            summ += (data[k] * std::pow(w, -1 * k * m)).real();
        }
        (*result)[m]= summ;
    }
    return *(result);
}
