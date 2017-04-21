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
private:
    QVector<std::complex<double>> *fastTransform(const QVector<std::complex<double>> &data, bool direction);
};

#endif // DISCRETEFOURIERTRANSFORM_H
