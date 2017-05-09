#ifndef RECURSIVEFILTER_H
#define RECURSIVEFILTER_H
#include <QVector>

class RecursiveFilter
{
public:
    RecursiveFilter();
    static QVector<double> *filter(QVector<double>& data, double x);
};

#endif // RECURSIVEFILTER_H
