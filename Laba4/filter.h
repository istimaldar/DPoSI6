#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include <QVector>
#include <complex>
#include "transform.h"

class Filter
{
public:
    Filter();
    static QVector<double> *buildLowFrequencyIR(unsigned int size, unsigned int M, double f);
    static QVector<double> *buildHighFrequencyIR(unsigned int size, unsigned int M, double f);
    static QVector<double> *buildBandPassIR(QVector<double> &lowPass, QVector<double> &highPass, Transform *transform);
    static QVector<double> *filter(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform, const QVector<double> &impulseResponse);
    static QVector<std::complex<double>> *filterFrequencyDomain(const QVector<double> &data, unsigned int M, unsigned int f, Transform *transform, const QVector<double> &impulseResponse);
    static QVector<double> *blackmansWindow(const QVector<double> &data, unsigned int M);
    static QVector<std::complex<double>> *normalize(const QVector<std::complex<double>> &data);
};

#endif // LOWPASSFILTER_H
