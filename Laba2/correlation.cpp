#include "correlation.h"

Correlation::Correlation()
{

}

QVector<std::complex<double> > *Correlation::execute(const QVector<std::complex<double> > &first, const QVector<std::complex<double> > &second, Transform &transform)
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
    QVector<std::complex<double>> *x = transform.inverseTransform((*c));
    delete c;
    return x;
}

QVector<std::complex<double> > *Correlation::execute(const QVector<double> &first, const QVector<double> &second, Transform &transform)
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
