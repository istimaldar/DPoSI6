#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include <QVector>
#include <complex>
#include "transform.h"

class Filter
{
public:
    Filter();
    static QVector<double> *lowPassFilter(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform);
    static QVector<std::complex<double>> *lowPassFilterFrequencyDomain(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform);
    static QVector<double> *highPassFilter(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform);
    static QVector<std::complex<double>> *highPhssFilterFrequencyDomain(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform);
    static QVector<std::complex<double>> *blackmansWindow(const QVector<double> &data, unsigned int M, Transform *transform);
    static QVector<std::complex<double>> *normalize(const QVector<std::complex<double>> &data);
    static QVector<std::complex<double>> *inverse(const QVector<std::complex<double>> &data);
    static QVector<std::complex<double>> *bandPassFilter(QVector<std::complex<double>> &lowPass, QVector<std::complex<double>> &highPass, Transform *transform);
};

#endif // LOWPASSFILTER_H
