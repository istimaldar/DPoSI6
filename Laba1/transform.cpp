#include "transform.h"
#include <math.h>

Transform::Transform()
{
    addOperations = 0;
    mulOpirations = 0;
    powOperations = 0;
    lastSize = 0;
}

QVector<double> * Transform::getAmplitude(const QVector<std::complex<double>> & numbers)
{
    QVector<double> *result = new QVector<double>(numbers.size());
    for (int i=0;i<numbers.size();i++) {
        (*result)[i] = sqrt(pow(numbers[i].real(), 2) + pow(numbers[i].imag(), 2));
    }
    return result;
}

QVector<double> * Transform::getPhase(const QVector<std::complex<double>> & numbers)
{
    QVector<double> *result = new QVector<double>(numbers.size());
    for (int i=0;i<numbers.size();i++) {
        (*result)[i] = atan(numbers[i].imag() / numbers[i].real());;
    }
    return result;
}
