#include "transform.h"
#include <math.h>

Transform::Transform()
{

}

double Transform::getAmplitude(std::complex<double> number)
{
    return sqrt(pow(number.real(), 2) + pow(number.imag(), 2));
}

double Transform::getPhase(std::complex<double> number)
{
    return atan(number.imag() / number.real());
}
