#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include "operationwithtwooperands.h"
#include <QVector>


class Convolution : public OperationWithTwoOperands
{
    static OperationWithTwoOperands *instance;
public:
    QVector<double> * execute(const QVector<std::complex<double>> & first, const QVector<std::complex<double>> & second, Transform & transform);
    QVector<double> * execute(const QVector<double> & first, const QVector<double> & second, Transform & transform);
    QVector<std::complex<double>> * executeFrequencyDomain(const QVector<std::complex<double>> & first, const QVector<std::complex<double>> & second, Transform & transform);
    QVector<std::complex<double>> * executeFrequencyDomain(const QVector<double> & first, const QVector<double> & second, Transform & transform);
    static OperationWithTwoOperands *getInstance();
private:
    Convolution();
};

#endif // CONVOLUTION_H
