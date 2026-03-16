#include <cassert>
#include <iostream>
#include "mtrx_class.hpp"
#include "mtrx_funcs.hpp"
#include <cmath>
#include <vector>

int main(){
    std::cout << "\nEnter matrix dimensions: ";
    size_t rows, cols;
    std::cin >> rows >> cols;
    Matrix<double> m(rows, cols);
    m.fill_up();
    std::cout << "Your matrix: \n";
    m.print();
    std::cout << "The determinant: " << det(m) << '\n';
    //std::cout << "Solved matrix: \n";
    //gj_triangle(m)->print();
    inv(m)->print();
    return 0;
}