#include "correlation.h"

OperationWithTwoOperands *Correlation::instance = nullptr;

Correlation::Correlation()
{

}

QVector<double> *Correlation::execute(const QVector<std::complex<double> > &first, const QVector<std::complex<double> > &second, Transform &transform)
{
    QVector<std::complex<double>> *cx = transform.directTransform(first);
    QVector<std::complex<double>> *cy = transform.directTransform(second);
    QVector<std::complex<double>> *c = new QVector<std::complex<double>>(first.size());
    for (int i = 0; i<first.size(); i++)
    {
        (*c)[i] = std::complex<double>((*cx)[i].real(), -((*cx)[i].imag())) * (*cy)[i];
        transform.addMulOperations(1);
        transform.addAddOperations(1);
    }
    QVector<double> *x = transform.inverseTransform((*c));
    delete c;
    return x;
}

QVector<double> *Correlation::execute(const QVector<double> &first, const QVector<double> &second, Transform &transform)
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

QVector<std::complex<double> > *Correlation::executeFrequencyDomain(const QVector<std::complex<double> > &first, const QVector<std::complex<double> > &second, Transform &transform)
{
    return nullptr;
}

QVector<std::complex<double> > *Correlation::executeFrequencyDomain(const QVector<double> &first, const QVector<double> &second, Transform &transform)
{
    return nullptr;
}

OperationWithTwoOperands *Correlation::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Correlation();
    }
    return instance;
}
