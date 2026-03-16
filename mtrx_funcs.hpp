#pragma once
#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include "mtrx_class.hpp"

template<typename T>
T det(Matrix<T>& m){
    assert(isSquare(m));
    T res{};
    if(m.get_rows() == 1){
        return m.at({0, 0});
    }
    if(m.get_rows() == 2){
        return m.at({0, 0}) * m.at({1, 1}) - m.at({0, 1}) * m.at({1, 0});
    }
    else{
        size_t col_it{};
        size_t dim = m.get_cols();
        Matrix<T> cut(dim-1, dim-1);
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

template<typename T>
bool existInv(const Matrix<T>& m){
    return det(m, 0) != 0;
}
template<typename T>
bool isSquare(const Matrix<T>& m){
    return m.get_cols() == m.get_rows();
}
template<typename T>
Matrix<T> transpon(Matrix<T>& m){
    //wip
}
template<typename T>
Matrix<T>* inv(Matrix<T>& m){
    assert(isSquare(m));
    size_t n = m.get_cols();
    std::vector<T> col{};
    col.reserve(n);
    for (size_t k = 0; k < n; k++)
    {
        for (size_t i = 0; i < n; i++)
        {
            if(i == k){
                col.push_back(1);
            }
            else{
                col.push_back(0);
            }
        }
        m.add_col(col);//we add the respective column to perform the gj method on
        col.clear();
    }
    Matrix<T>* inv_m_ptr = gj_triangle(m);
    for (size_t i = 0; i < n; i++)
    {
        inv_m_ptr->rem_col(0);//remove the extra columns
    }
    return inv_m_ptr;
}

namespace{
    template<typename T>
    size_t findPivot(Matrix<T>& m, size_t curr_col){
        T max_el{};
        size_t max_idx{m.get_rows()};
        for (size_t i = curr_col; i < m.get_rows(); i++)
        {
            if(m.at({i, curr_col}) != 0){
                if(max_el < m.at({i, curr_col})){
                    max_el = m.at({i, curr_col});
                    max_idx = i;
                }
            }
        }
        return max_idx;
    }
}

template<typename T>
void switchRows(Matrix<T>& m, size_t row1, size_t row2){
    assert(row1 < m.get_rows() && row2 < m.get_rows());
    for (size_t j = 0; j < m.get_cols(); j++)
    {
        T temp = m.at({row1, j});
        m.at({row1, j}) = m.at({row2, j});
        m.at({row2, j}) = temp;
    } 
}

template<typename T>
Matrix<T>* gj_triangle(Matrix<T>& m){
    assert(m.get_cols() >= m.get_rows()); //if false, then matrix is overdefined and should run with only a trimmed version (aka less equs)
    assert(m.get_data() != nullptr);
    for (size_t i = 0; i < m.get_rows(); i++)
    {
        T coef;
        if(m.at({i, i}) == 0.0){
            size_t pivotPoint = findPivot(m, i);//find the row to pivot with
            if(pivotPoint >= m.get_rows()){
                std::cout << "Singular matrix!\n";//if it doesnt exist -> no sol
                assert(false);
            }
            else{
                switchRows(m, i, pivotPoint);//if it does we swap
            }
        }
        coef = m.at({i, i});
        m.at({i, i}) = 1.0;
        for (size_t j = i+1; j < m.get_cols(); j++)
        {
            m.at({i, j}) = m.at({i, j}) / coef; //normalize the row
        }
        for (size_t j = 0; j < m.get_rows(); j++)
        {
            if(j==i) continue;
            coef = m.at({j, i});
            if(coef == 0.0) continue;
            for (size_t k = 0; k < m.get_cols(); k++)
            {
                m.at({j, k}) -= m.at({i, k})*coef; //nullify the coresponding element and decrement the row    
            }  
        }   
    }  
    return &m; 
}