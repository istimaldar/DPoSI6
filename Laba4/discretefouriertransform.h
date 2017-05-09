#ifndef DISCRETEFOURIERTRANSFORM_H
#define DISCRETEFOURIERTRANSFORM_H
#include "transform.h"


class DiscreteFourierTransform : public Transform
{
    static Transform *instance;
public:
    virtual QVector<std::complex<double>> * directTransform(const QVector<std::complex<double> > &data);
    QVector<std::complex<double>> * directTransform(const QVector<double> & data);
    QVector<double> * inverseTransform(const QVector<std::complex<double>> & data);
    static Transform *getInstance();
private:
    DiscreteFourierTransform();
};

#endif // DISCRETEFOURIERTRANSFORM_H
