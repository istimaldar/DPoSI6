#ifndef DISCRETEFOURIERTRANSFORM_H
#define DISCRETEFOURIERTRANSFORM_H
#include "transform.h"


class DiscreteFourierTransform : public Transform
{
public:
    DiscreteFourierTransform();
    virtual QVector<std::complex<double>> directTransform(QVector<double> data);
    virtual QVector<double> inverseTransform(QVector<std::complex<double>> data);
};

#endif // DISCRETEFOURIERTRANSFORM_H
