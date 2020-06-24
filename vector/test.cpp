#include "vector.cpp"
#include <extended/matrix>
#include <initializer_list>
#include <iostream>
using extended::vector;

template<typename T>
extended::vector<T> returnVector(const extended::vector<T> &other)
{
    auto v1 = other;
    for(size_t i = 0; i < 10; i++) 
        v1.push(1);
        
    return std::move(v1);
}

int main() {
    vector<char> v1(10);
    std::cout << v1.size()     << std::endl;
    std::cout << v1.max_size() << std::endl;
    std::cout << "------------" << std::endl;
    v1.assign(10);

    for(auto i = v1.begin(); i < v1.end(); i++)
        std::cin >> *i;

    std::cout << "------------" << std::endl;

    for(auto i = v1.begin(); i < v1.end(); i++)
        std::cout << *i << std::endl;

    v1.free(5);
    std::cout << "------------" << std::endl;
    std::cout << v1.size() << std::endl;
    std::cout << v1.max_size() << std::endl;

    for(auto i = v1.begin(); i < v1.end(); i++)
        std::cout << *i << std::endl;


    std::cout << "------------" << std::endl;
    v1.free_memory(5);

    for(auto i = v1.begin(); i < v1.end(); i++)
        std::cout << *i << std::endl;

    v1.add_memory(5);
    auto v2 = returnVector(v1);

    std::cout << "------------" << std::endl;
    std::cout << v2.size() << std::endl;

    for(auto i = v2.begin(); i < v2.end(); i++)
        std::cout << *i << std::endl;

    auto v3 = std::move(v2);

    std::cout << "------------" << std::endl;
    std::cout << v3.size() << std::endl;

    for(auto i = v3.begin(); i < v3.end(); i++)
        std::cout << *i << std::endl;

    std::cout << "------------" << std::endl;

    for(size_t i = 0; i < 5; i++)
        v3.push();

    std::cout << v3.size() << std::endl;

    v3 += v1;

    std::cout << "------------" << std::endl;

    vector<double> v4 = {0.5, 1.0, 1.5};
    extended::matrix<double> m1 = { {1,0,0}, {0,1,0}, {0,0,1}};

    auto v5 = v4*m1;

    for(auto i = v5.begin(); i < v5.end(); i++)
        std::cout << *i << ":";

    std::cout << std::endl;
}