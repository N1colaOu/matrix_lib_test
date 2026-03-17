#pragma once
#include <vector>
#include <cassert>
#include "mtrx_class.hpp"
#include "mtrx_funcs.hpp"
#include <cmath>

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
    return p.at({0, n-1});
}

template<typename T>
std::vector<T> lagr_plnm(std::vector<T> x, std::vector<T> y){
    size_t n = x.size();
    assert(n == y.size());
    Matrix<T> lin_sys(n, n);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            lin_sys.at({i, j}) = pow(x.at(i), j);
        }
    }
    lin_sys.add_col(y);
    //lin_sys.print();
    lin_sys = *gj_triangle(lin_sys);
    //lin_sys.print();
    return lin_sys.get_col_val(n);
}

template<typename T>
Matrix<T> n_spline(std::vector<T> x, std::vector<T> y, size_t n){
    //wip
}

template<typename T>
Matrix<T> cubic_spline(std::vector<T> x, std::vector<T> y){
    n_spline(x, y, 3);
    //wip
}