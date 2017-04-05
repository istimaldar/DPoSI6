#ifndef DISCRETEFOURIERTRANSOFM_H
#define DISCRETEFOURIERTRANSOFM_H
#include <complex>
#include <vector>

class DiscreteFourierTransofm
{
public:
    DiscreteFourierTransofm();
    static std::vector<std::complex<double>> directTransform(std::vector<double> data);
    static std::vector<double> inverseTransform(std::vector<std::complex<double>> data);
    static
};

#endif // DISCRETEFOURIERTRANSOFM_H
