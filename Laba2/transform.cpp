#include "transform.h"
#include <math.h>

Transform::Transform()
{
    addOperations = 0;
    mulOpirations = 0;
    powOperations = 0;
    lastSize = 0;
    zeroing = false;
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

void Transform::addAddOperations(int value)
{
    addOperations += value;
}

void Transform::addMulOperations(int value)
{
    mulOpirations += value;
}

void Transform::addPowOperations(int value)
{
    powOperations += value;
}

void Transform::setZeroing(bool zeroing)
{
    this->zeroing = zeroing;
}
