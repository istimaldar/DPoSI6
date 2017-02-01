#ifndef CORRELATION_H
#define CORRELATION_H
#include "operationwithtwooperands.h"

class Correlation : public OperationWithTwoOperands
{
public:
    Correlation();
    QVector<std::complex<double> > *execute(const QVector<std::complex<double> > &first, const QVector<std::complex<double> > &second, Transform &transform);
    QVector<std::complex<double> > *execute(const QVector<double> &first, const QVector<double> &second, Transform &transform);
};

#endif // CORRELATION_H
