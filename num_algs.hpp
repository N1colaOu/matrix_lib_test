#pragma once
#include <vector>
#include <cassert>
#include "mtrx_class.hpp"

template<typename T>
T neville_intrp(T x0, std::vector<T> x, std::vector<T> y){
    size_t n = x.size();
    assert(n == y.size());
    Matrix<T> p(n, n);
    for (size_t i = 0; i < n; i++)
    {
        p.at({i, 0}) = y.at(i);
    }
    
    for (size_t j = 1; j < n; j++)
    {
        for (size_t i = 0; i < n-j; i++)
        {
            p.at({i,j}) = ((x0 - x.at(i)) * p.at({i+1, j-1}) - (x0 - x.at(i+j)) * p.at({i, j-1})) / (x.at(i+j) - x.at(i));
        }
    }
    //p.print();
    return p.at({0, n-1});
}