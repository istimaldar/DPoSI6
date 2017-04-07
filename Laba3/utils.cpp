#include "utils.h"
#include <exception>
#include <cmath>
#include <QDebug>
#include <iostream>

Utils::Utils()
{

}

short Utils::rademacherFunction(unsigned int k, double t)
{
    if (t >= 1 || t < 0) {
        throw std::exception(); //TODO: Fix this shit
    }
    double x = std::sin((2 << (k - 1)) * M_PI * t);
    return (x < 0) ? -1 : 1;
}

unsigned short *Utils::toBinary(unsigned int n)
{
    unsigned int r = static_cast<unsigned int>(std::log2(n) + 1);
    unsigned short *result = new unsigned short[r + 1];
    for (unsigned int i = 0; i < r; i++)
    {
        result[r - i] = n % 2;
        n /= 2;
    }
    result[0] = 0;
    return result;
}

short Utils::walshFunction(unsigned int n, double t)
{
    if (n == 0)
    {
        return 1;
    }
    unsigned int r = static_cast<unsigned int>(std::log2(n) + 1);
    unsigned short *nBinary = toBinary(n);
    short result = 1;
    for (unsigned int k = 1; k <= r; k++)
    {
        short power = nBinary[r - k + 1] ^ nBinary[r - k];
        result *= std::pow(rademacherFunction(k, t), power);
    }
    return result;
}
