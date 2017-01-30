#ifndef FFTWDIT_H
#define FFTWDIT_H
#include <transform.h>


class FFTWDIT : public Transform
{
public:
    FFTWDIT();

    // Transform interface
public:
    QVector<std::complex<double>> *directTransform(const QVector<std::complex<double>> &data);
    QVector<std::complex<double> > *directTransform(const QVector<double> &data);
    QVector<std::complex<double> > *inverseTransform(const QVector<std::complex<double>> &data);
};

#endif // FFTWDIT_H
