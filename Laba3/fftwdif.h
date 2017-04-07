#ifndef FFTWDIF_H
#define FFTWDIF_H
#include "transform.h"


class FFTWDIF : public Transform
{
public:
    FFTWDIF();
    virtual QVector<std::complex<double> > *directTransform(const QVector<std::complex<double> > &data);
    virtual QVector<std::complex<double> > *directTransform(const QVector<double> &data);
    virtual QVector<std::complex<double> > *inverseTransform(const QVector<std::complex<double> > &data);
private:
    QVector<std::complex<double>> *transform(const QVector<std::complex<double>> &data);
    QVector<std::complex<double>> *fastTransform(const QVector<std::complex<double>> &data, bool direction);
};

#endif // FFTWDIF_H
