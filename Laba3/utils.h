#ifndef UTILS_H
#define UTILS_H


class Utils
{
public:
    Utils();
    static short rademacherFunction(unsigned int k, double t);
    static unsigned short *toBinary(unsigned int n);
    static short walshFunction(unsigned int n, double t);
};

#endif // UTILS_H
