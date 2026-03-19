#pragma once
#include <vector>
#include <cassert>
#include "classes.h"
#include "functions.h"
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
std::vector<Spline<T>> cubic_nat_splines(std::vector<T> x, std::vector<T> y){
    size_t n = x.size();
    assert(n-- == y.size());    

    std::vector<double> a_s(n+1);
    for (size_t i = 0; i < n + 1; i++)
    {
        a_s.at(i) = ((y.at(i)));
    }
    
    std::vector<double> b_s(n);
    std::vector<double> d_s(n);
    std::vector<double> h(n);
    for (size_t i = 0; i < n; i++)
    {
        h.at(i) = (x.at(i+1) - x.at(i));
    }
    
    std::vector<double> alpha(n);
    for (size_t i = 1; i < n; i++)
    {
        alpha.at(i) = (3/h.at(i)*(a_s.at(i+1) - a_s.at(i)) - 3/h.at(i  -1)*(a_s.at(i) - a_s.at(i - 1)));
    }
    
    std::vector<double> c_s(n+1);
    std::vector<double> z(n+1);
    std::vector<double> m(n+1);
    std::vector<double> l(n+1);
    
    l.at(0) = 1.0;
    m.at(0) = 0.0;
    z.at(0) = 0.0;
    
    for (size_t i = 1; i < n; i++)
    {
        l.at(i) = (2*(x.at(i+1) - x.at(i-1)) - h.at(i-1)*m.at(i-1));
        m.at(i) = (h.at(i)/l.at(i));
        z.at(i) = ((alpha.at(i) - h.at(i-1)*z.at(i-1))/l.at(i));
    }
    l.at(n) = 1.0;
    c_s.at(n) = 0.0;
    z.at(n) = 0.0;
    for (int i = n-1; i >= 0; i--)
    {
        c_s.at(i) = z.at(i) - m.at(i)*c_s.at(i+1);
        b_s.at(i) = (a_s.at(i+1)-a_s.at(i))/h.at(i) - h.at(i)*(c_s.at(i+1) + 2*c_s.at(i))/3;
        d_s.at(i) = (c_s.at(i+1)-c_s.at(i))/(3*h.at(i));
    }
    
    std::vector<Spline<T>> splines;
    splines.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        splines.push_back({a_s.at(i), b_s.at(i), c_s.at(i), d_s.at(i), x.at(i)});
    }
    return splines;
}