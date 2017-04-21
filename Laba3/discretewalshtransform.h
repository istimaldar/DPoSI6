#ifndef DISCRETEWALSHTRANSFORM_H
#define DISCRETEWALSHTRANSFORM_H
#include <transform.h>

class DiscreteWalshTransform : public Transform
{
public:
    DiscreteWalshTransform();
    virtual QVector<std::complex<double> > *directTransform(const QVector<std::complex<double> > &data);
    virtual QVector<std::complex<double> > *directTransform(const QVector<double> & data);
    virtual QVector<std::complex<double> > *inverseTransform(const QVector<std::complex<double>> & data);
};

#endif // DISCRETEWALSHTRANSFORM_H
