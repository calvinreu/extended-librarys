#pragma once
#include <time.h>
#include <random>

namespace extended{

    inline int random_int(const int &max)
    {
        srand(time(NULL));
        return rand()%max+1;
    }
    
    inline double random_double(double fMin, double fMax)
    {
        srand(time(NULL));
    
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

}