#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include "classes.h"


double det(Matrix& m){
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

bool existInv(Matrix& m){
    return det(m) != 0;
}



bool isSingular(Matrix& m){
    if(m.isSquare()){
        return det(m) == 0.0;
    }
    else{
        return true; //wip
    }
}

Matrix transpon(Matrix& m){
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
        out << m.at({i, 0}) << '\n';       
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

// Matrix* gj_triangle(Matrix& m){
//     assert(m.get_cols() >= m.get_rows()); //if false, then matrix is overdefined and should run with only a trimmed version (aka less equs)
//     assert(m.get_data() != nullptr);
//     for (size_t i = 0; i < m.get_rows(); i++)
//     {
//         double coef;
//         if(m.at({i, i}) == 0.0){
//             size_t pivotPoint = findPivot(m, i);//find the row to pivot with
//             if(pivotPoint >= m.get_rows()){
//                 std::cout << "Singular matrix!\n";//if it doesnt exist -> no sol
//                 assert(false);
//             }
//             switchRows(m, i, pivotPoint);
//         }
//         coef = m.at({i, i});
//         m.at({i, i}) = 1.0;
//         for (size_t j = i+1; j < m.get_cols(); j++)
//         {
//             m.at({i, j}) = m.at({i, j}) / coef; //normalize the row
//         }
//         for (size_t j = 0; j < m.get_rows(); j++)
//         {
//             if(j==i) continue;
//             coef = m.at({j, i});
//             if(coef == 0.0) continue;
//             for (size_t k = 0; k < m.get_cols(); k++)
//             {
//                 m.at({j, k}) -= m.at({i, k})*coef; //nullify the coresponding element and decrement the row    
//             }  
//         }   
//     }  
//     return &m; 
// }

// Matrix* inv(Matrix& m){
//     assert(m.isSquare());
//     size_t n = m.get_cols();
//     std::vector<double> col{};
//     col.reserve(n);
//     for (size_t k = 0; k < n; k++)
//     {
//         for (size_t i = 0; i < n; i++)
//         {
//             if(i == k){
//                 col.push_back(1);
//             }
//             else{
//                 col.push_back(0);
//             }
//         }
//         m.add_col(col);//we add the respective column to perform the gj method on
//         col.clear();
//     }
//     Matrix* inv_m_ptr = gj_triangle(m);
//     for (size_t i = 0; i < n; i++)
//     {
//         inv_m_ptr->rem_col(0);//remove the extra columns
//     }
//     return inv_m_ptr;
// }