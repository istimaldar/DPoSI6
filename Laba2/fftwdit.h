#ifndef FFTWDIT_H
#define FFTWDIT_H
#include <transform.h>


class FFTWDIT : public Transform
{
public:
    FFTWDIT();
    QVector<std::complex<double>> *directTransform(const QVector<std::complex<double>> &data);
    QVector<std::complex<double> > *directTransform(const QVector<double> &data);
    QVector<std::complex<double> > *inverseTransform(const QVector<std::complex<double>> &data);
private:
    QVector<std::complex<double>> *transform(const QVector<std::complex<double>> &data);
};

#endif // FFTWDIT_H
