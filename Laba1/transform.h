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
    QVector<double> getAmplitude(QVector<std::complex<double> > numbers);
    QVector<double> getPhase(QVector<std::complex<double>> numbers);
};

#endif // TRANSFORM_H
