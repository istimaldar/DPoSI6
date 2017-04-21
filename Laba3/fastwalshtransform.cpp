#include "fastwalshtransform.h"

FastWalshTransform::FastWalshTransform()
{

}

QVector<std::complex<double> > *FastWalshTransform::directTransform(const QVector<std::complex<double> > &data)
{
    if (data.size() == 1)
    {
        QVector<std::complex<double>> *vector = new QVector<std::complex<double>>(1);
        (*vector)[0] = data[0];
        return vector;
    }
    int newVectorSize = data.size() / 2;
    QVector<std::complex<double>> *first = new QVector<std::complex<double>>(newVectorSize);
    QVector<std::complex<double>> *last = new QVector<std::complex<double>>(newVectorSize);
    for (int i = 0; i < newVectorSize; i++)
    {
        (*first)[i] = data[i] + data[newVectorSize + i];
        (*last)[i] = data[i] - data[newVectorSize + i];
    }
    QVector<std::complex<double>> *firstResult = directTransform(*first);
    //delete first;
    QVector<std::complex<double>> *lastResult = directTransform(*last);
    //delete last;
    QVector<std::complex<double>> *result = new QVector<std::complex<double>>(data.size());
    for (int i = 0; i < newVectorSize; i++)
    {
        (*result)[i] = (*firstResult)[i];
        (*result)[newVectorSize + i] = (*lastResult)[i];
    }
    //delete lastResult;
    return result;
}

QVector<std::complex<double> > *FastWalshTransform::directTransform(const QVector<double> &data)
{
    QVector<std::complex<double>> u(data.size());
    for (int i = 0;i<data.size();i++)
    {
        u[i] = std::complex<double>(data[i], 0);
    }
    return directTransform(u);
}

QVector<std::complex<double> > *FastWalshTransform::inverseTransform(const QVector<std::complex<double> > &data)
{
    QVector<std::complex<double> > *result = directTransform(data);
    for (int i = 0; i < data.size(); i++)
    {
        (*result)[i] /= std::complex<double>(data.size(), 0);
    }
    return result;
}
