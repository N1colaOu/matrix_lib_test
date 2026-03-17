#include <cassert>
#include <iostream>
#include "mtrx_class.hpp"
#include "mtrx_funcs.hpp"
#include "num_algs.hpp"
#include <cmath>
#include <vector>

int main(){
    //Matrix<double> m("input_m.txt");
    //std::cout << "\nYour matrix: \n";
    //m.print();
    //std::cout << "The determinant: " << det(m) << '\n';
    //std::cout << "Solved matrix: \n";
    //std::cout << "Solved matrix:\n";
    //gj_triangle(m)->print();
    //inv(m)->print();

    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1.5, {1, 2}, {1, 4});
    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1,{1,2},{1,4});
    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1.5,{0,1,2},{1,3,7});
    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1.5,{0,1,2,3},{0,1,4,9});
     std::cout << "\nInterpolated value: " << neville_intrp<double>(2.5,{0,1,2,3,4},{5,3,9,47,165});


    return 0;
}