#include "fftwdif.h"
#include <QDebug>

FFTWDIF::FFTWDIF()
{

}

QVector<std::complex<double> > *FFTWDIF::transform(const QVector<std::complex<double> > &data)
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
    std::complex<double> wn = std::pow(e, -2. * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size()));
    mulOpirations += 4;
    powOperations += 1;
    std::complex<double> w(1, 0);
    for (int i = 0;i<data.size()/2;i++)
    {
        b[i] = data[i] + data[i + data.size()/2];
        c[i] = w * (data[i] - data[i + data.size()/2]);
        w = w * wn;
        mulOpirations += 2;
        addOperations += 4;
    }
    QVector<std::complex<double>> *nb = transform(b);
    QVector<std::complex<double>> *nc = transform(c);
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

QVector<std::complex<double> > *FFTWDIF::inverseTransform(const QVector<std::complex<double> > &data)
{
    QVector<std::complex<double>> *result = new QVector<std::complex<double>>(data.size());
    std::complex<double> e(exp(1.0), 0);
    for(int m = 0;m<data.size();m++)
    {
        std::complex<double> w = std::pow(e, -2. * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size())); //W=e^(-2*pi*i/N)
        std::complex<double> summ(0,0);
        for(int k = 0;k<data.size();k++)
        {
            summ += data[k] * std::pow(w, -1 * k * m);
        }
        (*result)[m]= summ;
    }
    return result;
}
