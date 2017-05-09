#include "convolution.h"

OperationWithTwoOperands *Convolution::instance = nullptr;

Convolution::Convolution()
{
    
}

QVector<double> *Convolution::execute(const QVector<std::complex<double> > &first, const QVector<std::complex<double> > &second, Transform & transform)
{
    transform.setZeroing(false);
    QVector<std::complex<double>> *cx = transform.directTransform(first);
    QVector<std::complex<double>> *cy = transform.directTransform(second);
    QVector<std::complex<double>> *c = new QVector<std::complex<double>>(first.size());
    for (int i = 0; i<first.size(); i++)
    {
        (*c)[i] = (*cx)[i] * (*cy)[i];
        transform.addMulOperations(1);
    }
    QVector<double> *x = transform.inverseTransform((*c));
    delete c;
    return x;
}

QVector<double> *Convolution::execute(const QVector<double> &first, const QVector<double> &second, Transform & transform)
{
    QVector<std::complex<double>> u(first.size());
    QVector<std::complex<double>> y(first.size());
    for (int i = 0;i<first.size();i++)
    {
        u[i] = std::complex<double>(first[i], 0);
        y[i] = std::complex<double>(second[i], 0);
    }
    return execute(u, y, transform);
}

QVector<std::complex<double> > *Convolution::executeFrequencyDomain(const QVector<std::complex<double> > &first, const QVector<std::complex<double> > &second, Transform &transform)
{
    return nullptr;
}

QVector<std::complex<double> > *Convolution::executeFrequencyDomain(const QVector<double> &first, const QVector<double> &second, Transform &transform)
{
    return nullptr;
}

OperationWithTwoOperands *Convolution::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Convolution();
    }
    return instance;
}
