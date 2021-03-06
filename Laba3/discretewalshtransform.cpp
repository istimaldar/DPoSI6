#include "discretewalshtransform.h"
#include <utils.h>
#include <QDebug>

DiscreteWalshTransform::DiscreteWalshTransform()
{

}

QVector<std::complex<double>> *DiscreteWalshTransform::directTransform(const QVector<std::complex<double> > &data)
{
    QVector<std::complex<double>> *result = new QVector<std::complex<double>>(data.size());
    for (int k = 0; k < data.size(); k++)
    {
        (*result)[k] = std::complex<double>(0, 0);
        for (int i = 0; i < data.size(); i++)
        {
            (*result)[k] += std::complex<double>(data[i].real() * Utils::walshFunction(Utils::walshToAdamar(k, data.size()), static_cast<double>(i) / data.size()), 0);
            mulOpirations += 1;
        }
    }
    return result;
}

QVector<std::complex<double> > *DiscreteWalshTransform::directTransform(const QVector<double> &data)
{
    lastSize = data.size();
    addOperations = 0;
    mulOpirations = 0;
    powOperations = 0;
    QVector<std::complex<double>> u(data.size());
    for (int i = 0;i<data.size();i++)
    {
        u[i] = std::complex<double>(data[i], 0);
    }
    return directTransform(u);
}

QVector<std::complex<double>> *DiscreteWalshTransform::inverseTransform(const QVector<std::complex<double> > &data)
{
    QVector<std::complex<double>> *result = new QVector<std::complex<double>>(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        (*result)[i] = std::complex<double>(0, 0);
        for (int k = 0; k < data.size(); k++)
        {
            (*result)[i] += std::complex<double>(data[k].real() * Utils::walshFunction(Utils::walshToAdamar(k, data.size()), static_cast<double>(i) / data.size()), 0);
        }
        (*result)[i] /= data.size();
    }
    return result;
}
