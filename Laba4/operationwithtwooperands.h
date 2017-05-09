#ifndef OPERATIONWITHTWOOPERANDS_H
#define OPERATIONWITHTWOOPERANDS_H
#include <QVector>
#include <complex>
#include <transform.h>

class OperationWithTwoOperands
{
public:
    OperationWithTwoOperands();
    virtual QVector<double> * execute(const QVector<std::complex<double>> & first, const QVector<std::complex<double>> & second, Transform & transform) = 0;
    virtual QVector<double> * execute(const QVector<double> & first, const QVector<double> & second, Transform & transform) = 0;
    virtual QVector<std::complex<double>> * executeFrequencyDomain(const QVector<std::complex<double>> & first, const QVector<std::complex<double>> & second, Transform & transform) = 0;
    virtual QVector<std::complex<double>> * executeFrequencyDomain(const QVector<double> & first, const QVector<double> & second, Transform & transform) = 0;
};

#endif // OPERATIONWITHTWOOPERANDS_H
