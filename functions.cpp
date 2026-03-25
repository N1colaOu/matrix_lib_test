#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include "classes.h"


double det(const Matrix& m){
    assert(m.isSquare());
    double res{};
    if(m.get_rows() == 1){
        return m.at({0, 0});
    }
    if(m.get_rows() == 2){
        return m.at({0, 0}) * m.at({1, 1}) - m.at({0, 1}) * m.at({1, 0});
    }
    else{
        size_t col_it{};
        size_t dim = m.get_cols();
        Matrix cut(dim-1, dim-1);
        for (size_t k = 0; k < dim; k++)
        {
            size_t c_i{};
            for (size_t i = 0; i < dim; i++)
            {
                size_t c_j{};
                if(k != i){
                    for (size_t j = 0; j < dim; j++)
                    {
                        if(j != col_it){
                            cut.at({c_i, c_j++}) = m.at({i, j});
                        }
                    }
                    c_i++;
                }
            }
            res += pow(-1, k+col_it) * m.at({k, col_it}) * det(cut);
        }
    }
    return res;
}
bool existInv(const Matrix& m){
    return det(m) != 0;
}
bool isSingular(const Matrix& m){
    if(m.isSquare()){
        return det(m) == 0.0;
    }
    else{
        return true; //wip
    }
}
Matrix transpon(const Matrix& m){
    //wip
    return m;
}

std::ostream& operator<<(std::ostream& out, const Spline& s){
    out << s.get_zero() << " + " << s.get_first() << "(x-" << s.get_x() <<") + " << s.get_second() << "(x-" << s.get_x() << ")^2 + " << s.get_third() << "(x-" << s.get_x() << ")^3";
    return out;
}
std::ostream& operator<<(std::ostream& out, const Vector& m){
    for (size_t i = 0; i < m.get_rows(); i++)
    {
        out << m.at(i) << '\n';       
    }
    return out;
}
std::ostream& operator<<(std::ostream& out, const Matrix& m){
    for (size_t i = 0; i < m.get_rows(); i++)
    {
        for (size_t j = 0; j < m.get_cols(); j++)
        {
            out << m.at({i, j}) << " ";       
        }
        out << '\n';
    }
    return out;
}
bool operator==(const Matrix& m1, const Matrix& m2){
    if(m1.get_cols() != m2.get_cols() || m1.get_rows() != m2.get_rows()) return false;
    size_t n = m1.get_cols();
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if(m1.at({i, j}) - m2.at({i, j}) > 1e-9) return false; //check if they are equal or at least practically euqal
        }
    }
    return true;
}
bool operator==(const Vector& v1, const Vector& v2){
    if(v1.get_rows() != v2.get_rows()) return false;
    size_t n = v1.get_rows();
    for (size_t i = 0; i < n; i++)
    {
        if(v1.at(i) - v2.at(i) > 1e-9) return false; //check if they are equal or at least practically euqal
    }
    return true;
}

Matrix MatMatMult(const Matrix& A, const Matrix& B){
    Matrix C (A.get_rows(), B.get_cols());
    size_t n = A.get_rows();
    size_t m = A.get_cols();
    assert(m == B.get_rows());
    size_t t = B.get_cols();
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < t; j++)
        {
            double sum{};
            for (size_t k = 0; k < m; k++)
            {
                sum += A.at({i, k})*B.at({k, j});
            }
            C.at({i, j}) = sum; 
        }
    }
    return C;
}
Vector MatVecMult(const Matrix& A, const Vector& v){
    size_t n = A.get_cols();
    assert(n == v.get_rows());
    Vector u(n);
    for (size_t i = 0; i < n; i++)
    {
        double sum{};
        for (size_t j = 0; j < n; j++)
        {
            sum += A.at({i, j})*v.at(j);
        }
        u.at(i) = sum;
    }
    return u;
}