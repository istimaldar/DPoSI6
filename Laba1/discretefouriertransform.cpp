#include "discretefouriertransform.h"

DiscreteFourierTransform::DiscreteFourierTransform()
{

}

QVector<std::complex<double> > DiscreteFourierTransform::directTransform(QVector<double> data)
{
    return *(new QVector<std::complex<double>>);
}

QVector<double> DiscreteFourierTransform::inverseTransform(QVector<std::complex<double> > data)
{
    return *(new QVector<double>);
}
