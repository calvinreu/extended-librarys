#pragma once
#include <time.h>
#include <random>

inline int random_int()
{
    srand(time(NULL));
    return rand();
}

inline double random_double(double fMin, double fMax)
{
    srand(time(NULL));

    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}