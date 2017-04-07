#ifndef DISCRETEFOURIERTRANSFORM_H
#define DISCRETEFOURIERTRANSFORM_H
#include "transform.h"


class DiscreteFourierTransform : public Transform
{
public:
    DiscreteFourierTransform();
    virtual QVector<std::complex<double> > *directTransform(const QVector<std::complex<double> > &data);
    virtual QVector<std::complex<double> > *directTransform(const QVector<double> & data);
    virtual QVector<std::complex<double> > *inverseTransform(const QVector<std::complex<double>> & data);
};

#endif // DISCRETEFOURIERTRANSFORM_H
