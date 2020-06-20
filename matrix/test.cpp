#include <iostream>
#include <vector>
#include <random>

#include "lib_v1/matrix.h"
#include "lib_v2/matrix"

int main(int argc, char const *argv[]) {
    
    

    std::cout << "test 2 started \n";

    extended::matrix<double> a = {
        {0.9, 1.1, 1.2},
        {1.3, 1.4, 0.8}
    };
    extended::matrix<double> b;
    b = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    auto c = a*b;

    std::cout << c.row_size() << std::endl;

    for (auto i = c.begin(); i < c.end(); i++)
        std::cout << *i << std::endl;
    
    return 0;
}

