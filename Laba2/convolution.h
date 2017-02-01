#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include "operationwithtwooperands.h"
#include <QVector>


class Convolution : public OperationWithTwoOperands
{
public:
    Convolution();
    QVector<std::complex<double> > *execute(const QVector<std::complex<double> > &first, const QVector<std::complex<double> > &second, Transform &transform);
    QVector<std::complex<double> > *execute(const QVector<double> &first, const QVector<double> &second, Transform &transform);
};

#endif // CONVOLUTION_H
