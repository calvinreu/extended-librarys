#include <iostream>
#include <vector>
#include <random>

#include "matrix"

int main(int argc, char const *argv[]) {
    
    

    std::cout << "test 2 started \n";

    extended::matrix<double> a = {
        {0.9, 1.1, 1.2},
        {1.3, 1.4, 0.8}
    };

    std::cout << "created matrix a \n";
    extended::matrix<double> b;

    std::cout << "created matrix b \n";
    b = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    std::cout << "init matrix b \n";
    auto d = a;
    auto c = std::move(a);
    c = c*b;
    std::cout << c.row_count() << ":" << c. row_size() << std::endl;
    c = d+c;
    std::cout << c.row_count() << ":" << c. row_size() << std::endl;
    c = c-d;
    std::cout << c.row_count() << ":" << c. row_size() << std::endl;

    for (auto iR = c.begin(); iR < c.end(); iR++)
    {
        for (auto i = iR->begin(); i < iR->end(); i++)
            std::cout << *i << std::endl;
        std::cout << "\n";
    }

    for (auto iR = d.begin(); iR < d.end(); iR++)
    {
        for (auto i = iR->begin(); i < iR->end(); i++)
            std::cout << *i << std::endl;
        std::cout << "\n";
    }
    
    return 0;
}

