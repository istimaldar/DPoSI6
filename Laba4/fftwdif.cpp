#include "fftwdif.h"
#include <QDebug>

Transform *FFTWDIF::instance = nullptr;

FFTWDIF::FFTWDIF()
{

}

QVector<std::complex<double>> *FFTWDIF::fastTransform(const QVector<std::complex<double>> &data, bool direction)
{
    if (data.size() == 1)
    {
        QVector<std::complex<double>> *vector = new QVector<std::complex<double>>(1);
        (*vector)[0] = data[0];
        return vector;
    }
    QVector<std::complex<double>> b(data.size()/2);
    QVector<std::complex<double>> c(data.size()/2);
    std::complex<double> e(exp(1.0), 0);
    std::complex<double> wn = std::pow(e, (direction ? -2. : 2.) * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size()));
    if (direction) mulOpirations += 4;
    if (direction) powOperations += 1;
    std::complex<double> w(1, 0);
    for (int i = 0;i<data.size()/2;i++)
    {
        b[i] = data[i] + data[i + data.size()/2];
        c[i] = w * (data[i] - data[i + data.size()/2]);
        w = w * wn;
        if (direction) mulOpirations += 2;
        if (direction) addOperations += 4;
    }
    QVector<std::complex<double>> *nb = fastTransform(b, direction);
    QVector<std::complex<double>> *nc = fastTransform(c, direction);
    QVector<std::complex<double>> *y = new QVector<std::complex<double>>(data.size());
    for (int i = 0;i<data.size()/2;i++)
    {
        (*y)[2*i] = (*nb)[i];
        (*y)[2*i+1] = (*nc)[i];
    }
    delete nb;
    delete nc;
    return y;
}

QVector<std::complex<double> > *FFTWDIF::transform(const QVector<std::complex<double> > &data)
{
    return fastTransform(data, true);
}

QVector<std::complex<double> > *FFTWDIF::directTransform(const QVector<std::complex<double> > &data)
{
    lastSize = data.size();
    addOperations = 0;
    mulOpirations = 0;
    powOperations = 0;
    QVector<std::complex<double>> *y = transform(data);
    for (int i = 0;i<data.size();i++)
    {
        (*y)[i] /= static_cast<double>(data.size());
        mulOpirations += 1;
    }
    return y;
}

QVector<std::complex<double> > *FFTWDIF::directTransform(const QVector<double> &data)
{
    QVector<std::complex<double>> u(data.size());
    for (int i = 0;i<data.size();i++)
    {
        u[i] = std::complex<double>(data[i], 0);
    }
    return directTransform(u);
}

QVector<double> *FFTWDIF::inverseTransform(const QVector<std::complex<double> > &data)
{
    QVector<std::complex<double>> *vector = fastTransform(data, false);
    QVector<double> *result = new QVector<double>(vector->size());
    for (unsigned int i = 0; i < vector->size(); i++)
    {
        (*result)[i] = (*vector)[i].real();
    }
    delete vector;
    return result;
}

Transform *FFTWDIF::getInstance()
{
    if (instance == nullptr)
    {
        instance = new FFTWDIF();
    }
    return instance;
}
