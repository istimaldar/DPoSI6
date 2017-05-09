#ifndef FFTWDIT_H
#define FFTWDIT_H
#include <transform.h>


class FFTWDIT : public Transform
{
    static Transform *instance;
public:
    QVector<std::complex<double>> *directTransform(const QVector<std::complex<double>> &data);
    QVector<std::complex<double> > *directTransform(const QVector<double> &data);
    QVector<double> *inverseTransform(const QVector<std::complex<double>> &data);
    static Transform *getInstance();
private:
    QVector<std::complex<double>> *transform(const QVector<std::complex<double>> &data);
    QVector<std::complex<double>> *fastTransform(const QVector<std::complex<double>> &data, bool direction);
    FFTWDIT();
};

#endif // FFTWDIT_H
