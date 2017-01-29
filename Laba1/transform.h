#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QVector>
#include <complex>

class Transform
{
public:
    Transform();
    virtual QVector<std::complex<double>> directTransform(QVector<double> data) = 0;
    virtual QVector<double> inverseTransform(QVector<std::complex<double>> data) = 0;
    double getAmplitude(std::complex<double> number);
    double getPhase(std::complex<double> number);
};

#endif // TRANSFORM_H
