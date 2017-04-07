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
};

#endif // FASTWALSHTRANSFORM_H
