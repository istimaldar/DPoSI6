#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QVector>
#include <complex>

class Transform
{
public:
    Transform();
    virtual QVector<std::complex<double>> * directTransform(const QVector<std::complex<double>> & data) = 0;
    virtual QVector<std::complex<double>> * directTransform(const QVector<double> & data) = 0;
    virtual QVector<std::complex<double>> * inverseTransform(const QVector<std::complex<double>> & data) = 0;
    static QVector<double> * getAmplitude(const QVector<std::complex<double>> & numbers);
    static QVector<double> *getPhase(const QVector<std::complex<double>> & numbers);
};

#endif // TRANSFORM_H
