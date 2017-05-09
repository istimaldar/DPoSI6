#include "fftwdit.h"

Transform *FFTWDIT::instance = nullptr;

FFTWDIT::FFTWDIT()
{

}

QVector<std::complex<double>> *FFTWDIT::fastTransform(const QVector<std::complex<double>> &data, bool direction)
{
    if (data.size() == 1)
    {
        QVector<std::complex<double>> *vector = new QVector<std::complex<double>>(1);
        (*vector)[0] = data[0];
        return vector;
    }
    QVector<std::complex<double>> even(data.size()/2);
    QVector<std::complex<double>> odd(data.size()/2);
    for (int i=0;i<data.size();i++)
    {
        if (!(i%2))
        {
            even[i/2] = data[i];
        }
        else
        {
            odd[i/2] = data[i];
        }
    }
    QVector<std::complex<double>> *yEven = fastTransform(even, direction);
    QVector<std::complex<double>> *yOdd = fastTransform(odd, direction);
    std::complex<double> e(exp(1.0), 0);
    std::complex<double> wn = std::pow(e, (direction ? -2. : 2.) * std::complex<double>(0,1) * M_PI / static_cast<double>(data.size()));
    std::complex<double> w(1, 0);
    if (direction) mulOpirations += 4;
    if (direction) powOperations += 1;
    QVector<std::complex<double>> *y = new QVector<std::complex<double>>(data.size());
    for (int i = 0; i < data.size() / 2; i++)
    {
        (*y)[i] = ((*yEven)[i] + (w * (*yOdd)[i]));
        (*y)[i + data.size()/2] = ((*yEven)[i] - (w * (*yOdd)[i]));
        w = w * wn;
        if (direction) mulOpirations += 3;
        if (direction) addOperations += 2;
    }
    delete yEven;
    delete yOdd;
    return y;
}

QVector<std::complex<double>> *FFTWDIT::transform(const QVector<std::complex<double>> &data)
{
    return fastTransform(data, true);
}

QVector<std::complex<double> > *FFTWDIT::directTransform(const QVector<std::complex<double> > &data)
{
    lastSize = data.size();
    addOperations = 0;
    mulOpirations = 0;
    powOperations = 0;
    QVector<std::complex<double>> *y = transform(data);
    for (int i = 0; i < data.size(); i++)
    {
        (*y)[i] /= static_cast<double>(data.size());
        mulOpirations += 1;
    }
    return y;
}

QVector<std::complex<double> > *FFTWDIT::directTransform(const QVector<double> &data)
{
    QVector<std::complex<double>> u(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        u[i] = std::complex<double>(data[i], 0);
    }
    return directTransform(u);
}

QVector<double> * FFTWDIT::inverseTransform(const QVector<std::complex<double>> & data)
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

Transform *FFTWDIT::getInstance()
{
    if (instance == nullptr)
    {
        instance = new FFTWDIT();
    }
    return instance;
}
