#ifndef CORRELATION_H
#define CORRELATION_H
#include "operationwithtwooperands.h"

class Correlation : public OperationWithTwoOperands
{
    static OperationWithTwoOperands *instance;
public:
    QVector<double> * execute(const QVector<std::complex<double>> & first, const QVector<std::complex<double>> & second, Transform & transform);
    QVector<double> * execute(const QVector<double> & first, const QVector<double> & second, Transform & transform);
    QVector<std::complex<double>> * executeFrequencyDomain(const QVector<std::complex<double>> & first, const QVector<std::complex<double>> & second, Transform & transform);
    QVector<std::complex<double>> * executeFrequencyDomain(const QVector<double> & first, const QVector<double> & second, Transform & transform);
    static OperationWithTwoOperands *getInstance();
private:
    Correlation();
};

#endif // CORRELATION_H
