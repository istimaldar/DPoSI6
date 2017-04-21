#include "utils.h"
#include <exception>
#include <cmath>
#include <QDebug>
#include <iostream>
#define MINIMAL_OFFSET 0.0000000001

Utils::Utils()
{

}

short Utils::rademacherFunction(unsigned int k, double t)
{
    if (t > 1 || t < 0) {
        throw std::exception(); //TODO: Fix this shit
    }
    double x = std::sin((2 << (k  - 1)) * M_PI * (t + MINIMAL_OFFSET));
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

unsigned short Utils::walshToAdamar(unsigned short n, unsigned short max)
{
    unsigned int r = static_cast<unsigned int>(std::log2(n) + 1);
    unsigned int r_new = static_cast<unsigned int>(std::log2(max) + 1);
    unsigned short *gray = toBinary(n);
    unsigned short *array = new unsigned short[r_new + 1];
    for (unsigned int i = 0; i < r_new - r - 1; i++)
    {
        array[i] = 0;
    }
    array[r_new - r - 1] = gray[0];
    for (unsigned int i = 0; i <= r; i++)
    {
        array[i + r_new - r] = array[i - 1 + r_new - r] ^ gray[i];
    }
#ifdef PRINT
    for (int i = 0; i <= r; i++)
    {
        std::cout << gray[i];
    }
    std::cout << std::endl;
    for (int i = 0; i <= r_new; i++)
    {
        std::cout << array[i];
    }
    std::cout << std::endl;
#endif
    delete gray;
    unsigned short result = 0;
    for (unsigned int i = r_new; i > 1; i--)
    {
        result = result << 1;
        result += array[i];

    }
    delete array;
    return result;
}

