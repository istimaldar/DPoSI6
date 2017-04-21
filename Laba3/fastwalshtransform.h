#ifndef FASTWALSHTRANSFORM_H
#define FASTWALSHTRANSFORM_H
#include "transform.h"


class FastWalshTransform : public Transform
{
public:
    FastWalshTransform();
    virtual QVector<std::complex<double>> * directTransform(const QVector<std::complex<double> > &data);
    virtual QVector<std::complex<double>> * directTransform(const QVector<double> & data);
    virtual QVector<std::complex<double>> * inverseTransform(const QVector<std::complex<double>> & data);
private:
    QVector<std::complex<double>> *fastTransform(const QVector<std::complex<double>> &data, bool direction);
};

#endif // FASTWALSHTRANSFORM_H
