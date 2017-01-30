#include "transform.h"
#include <math.h>

Transform::Transform()
{

}

QVector<double> Transform::getAmplitude(QVector<std::complex<double>> numbers)
{
    QVector<double> *result = new QVector<double>(numbers.size());
    for (int i=0;i<numbers.size();i++) {
        (*result)[i] = sqrt(pow(numbers[i].real(), 2) + pow(numbers[i].imag(), 2));
    }
    return (*result);
}

QVector<double> Transform::getPhase(QVector<std::complex<double>> numbers)
{
    QVector<double> *result = new QVector<double>(numbers.size());
    for (int i=0;i<numbers.size();i++) {
        (*result)[i] = atan(numbers[i].imag() / numbers[i].real());;
    }
    return (*result);
}
