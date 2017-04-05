#include "utils.h"
#include <exception>
#include <cmath>

Utils::Utils()
{

}

short Utils::rademacherFunction(unsigned int k, double t)
{
    if (t >= 1 || t < 0) {
        throw std::exception();
    }
    double x = std::sin((2 << (k - 1)) * M_PI * t);
    return (x < 0) ? -1 : 1;
}

short *Utils::toBinary(unsigned int n, unsigned int r)
{
    short *result = new short[r + 1];
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
    int r = std::ceil(std::log2(n));
    short *nBinary = toBinary(n, r);
    short result = 1;
    for (int k = 1; k <= r; k++)
    {
        result *= std::pow(rademacherFunction(k, t), nBinary[r - k + 1] ^ nBinary[r - k]);
    }
    return result;
}
