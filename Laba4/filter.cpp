#include "filter.h"
#include "convolution.h"
#include "fftwdif.h"

Filter::Filter()
{

}

QVector<double> *Filter::buildLowFrequencyIR(unsigned int size, unsigned int M, double f)
{
    QVector<double> *result = new QVector<double>(size);
    for (int i = 0; i <= M; i++)
    {
        int n = i - M / 2;
        if (n != 0)
        {
            (*result)[i] = (M - (size - M)) *  std::sin(2 * M_PI * f * n) / (M_PI * n);
        }
        else
        {
            (*result)[i] = (M - (size - M)) * 1;
        }
    }
    for (int i = M + 1; i < size; i++)
    {
        (*result)[i] = 0;
    }
    return result;
}

QVector<double> *Filter::buildHighFrequencyIR(unsigned int size, unsigned int M, double f)
{
    QVector<double> *result = new QVector<double>(size);
    double fNew;
    if (f <= 0.5)
    {
        fNew = 0.5 - f;
    }
    else
    {
        fNew = 1 - f + 0.5;
    }
    for (int i = 0; i <= M; i++)
    {
        int n = i - M / 2;
        if (n != 0)
        {
            (*result)[i] = (M - (size - M)) *  std::sin(2 * M_PI * fNew * n) / (M_PI * n);
        }
        else
        {
            (*result)[i] = (M - (size - M)) * 1;
        }
        if (i % 2 == 1)
        {
            (*result)[i] = 0 - (*result)[i];
        }
    }
    for (int i = M + 1; i < size; i++)
    {
        (*result)[i] = 0;
    }
    return result;
}

QVector<double> *Filter::lowPassFilter(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform, const QVector<double> &impulseResponse)
{
    QVector<double> *result = Convolution::getInstance()->execute(data, impulseResponse, *(transform));
    return result;
}



QVector<std::complex<double> > *Filter::lowPassFilterFrequencyDomain(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform, const QVector<double> &impulseResponse)
{
    QVector<double> *vector = lowPassFilter(data, M, f, transform, impulseResponse);
    QVector<std::complex<double>> *result = transform->directTransform((*vector));
    delete vector;
    return result;
}

QVector<double> *Filter::highPassFilter(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform)
{
//    if (M % 2 != 0)
//    {
//        M += 1;
//    }
//    QVector<double> filterFunction(data.size());
//    for (int i = 0; i <= M; i++)
//    {
//        filterFunction[i] = 0 - std::sin(2 * M_PI * f * (i + 1)) / (M_PI * (i + 1));
//    }
//    for (int i = M + 1; i < data.size(); i++)
//    {
//        filterFunction[i] = 0;
//    }
//    QVector<std::complex<double>> *vector = Convolution::getInstance()->execute(data, filterFunction, *(transform));
//    QVector<double> *result = new QVector<double>(vector->size());
//    for (int i = 0; i < vector->size(); i++)
//    {
//        (*result)[i] = (*vector)[i].real();
//    }
//    delete vector;
//    return result;
    return nullptr;
}

QVector<std::complex<double> > *Filter::highPhssFilterFrequencyDomain(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform)
{
//    QVector<double> *vector = highPassFilter(data, M, f, transform);
//    QVector<std::complex<double>> *result = transform->directTransform((*vector));
//    delete vector;
//    return result;
    return nullptr;
}

QVector<double> *Filter::blackmansWindow(const QVector<double> &data, unsigned int M)
{
    QVector<double> vector(data.size());
    for (int i = 0; i <= M; i++)
    {
        vector[i] = 0.42 - 0.5 * std::cos(2 * M_PI * i / M) + 0.08 * std::cos(4 * M_PI * i / M);
    }
    for (int i = M + 1; i < data.size(); i++)
    {
        vector[i] = 0;
    }
    QVector<double> *result = new QVector<double>(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        (*result)[i] = data[i] * vector[i];
    }
    return result;
}

QVector<std::complex<double> > *Filter::normalize(const QVector<std::complex<double>> &data)
{
    double maxModule = std::pow(data[0].real(), 2) + std::pow(data[0].imag(), 2);
    for (int i = 1; i < data.size(); i++)
    {
        double currentModule = std::pow(data[i].real(), 2) + std::pow(data[i].imag(), 2);
        if (currentModule > maxModule)
        {
            maxModule = currentModule;
        }
    }
    QVector<std::complex<double> > *result = new QVector<std::complex<double>>(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        (*result)[i] = data[i] * (1 / maxModule);
    }
    return result;
}

QVector<std::complex<double> > *Filter::bandPassFilter(QVector<std::complex<double> > &lowPass, QVector<std::complex<double> > &highPass, Transform *transform)
{
//    QVector<std::complex<double> > *lowPassTimeDomain = transform->inverseTransform(lowPass);
//    QVector<std::complex<double> > *highPassTimeDomain = transform->inverseTransform(highPass);
//    QVector<std::complex<double> > *bandPassTimeDomain = Convolution::getInstance()->execute((*lowPassTimeDomain), (*highPassTimeDomain), (*transform));
//    delete lowPassTimeDomain;
//    delete highPassTimeDomain;
//    QVector<std::complex<double>> *result = transform->directTransform((*bandPassTimeDomain));
//    delete bandPassTimeDomain;
//    return result;
    return nullptr;
}

