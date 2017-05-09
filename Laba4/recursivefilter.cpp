#include "recursivefilter.h"

RecursiveFilter::RecursiveFilter()
{

}

QVector<double> *RecursiveFilter::filter(QVector<double> &data, double x)
{
    QVector<double> *a = new QVector<double>(1);
    QVector<double> *b = new QVector<double>(4);
    (*a)[0] = std::pow((1 - x), 4);
    (*b)[0] = 4 * x;
    (*b)[1] = -6 * std::pow(x, 2);
    (*b)[2] = 4 * std::pow(x, 3);
    (*b)[3] = - std::pow(x, 4);
    QVector<double> *result = new QVector<double>(data.size());
    for (unsigned int i = 0; i < data.size(); i++)
    {
        (*result)[i] = 0;
        unsigned int j = 0;
        while (j < a->size() && j < i)
        {
            (*result)[i] += data[i - j] * (*a)[j];
            j++;
        }
        j = 0;
        while (j < b->size() && j < i) {
            (*result)[i] += (*result)[i - j - 1] * (*b)[j];
            j++;
        }
    }
    delete a;
    delete b;
    return result;
}
