#include <cassert>
#include <iostream>
#include "classes.h"
#include "functions.h"
#include "num_algs.h"
#include <cmath>
#include <vector>

int main(){
    std::cout << std::endl << '\n';
    // Matrix* A = new Matrix("input_m.txt");
    // std::cout << "\nYour matrix: \n";
    // A->print();
    // Vector* b = new Vector("input_v.txt");
    // std::cout << "\nYour vector: \n";
    // b->print();

    LinSystem lin_sys(new Matrix("input_m.txt"), new Vector("input_v.txt"));
    std::cout << *lin_sys.get_solution("gauss_jordan");

    //std::cout << "The determinant: " << det(m) << '\n';
    //std::cout << "Solved matrix: \n";
    //std::cout << "Solved matrix:\n";
    //gj_triangle(m)->print();
    //inv(m)->print();

    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1.5, {1, 2}, {1, 4});
    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1,{1,2},{1,4});
    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1.5,{0,1,2},{1,3,7});
    // std::cout << "\nInterpolated value: " << neville_intrp<double>(1.5,{0,1,2,3},{0,1,4,9});
    // std::cout << "\nInterpolated value: " << neville_intrp<double>(2.5,{0,1,2,3,4},{5,3,9,47,165});

    // std::vector<double> coeffs = lagr_plnm<double>({0,1,2},{1,3,2});
    // std::vector<double> coeffs = lagr_plnm<double>({-1,0,1},{2,0,2});
    // std::vector<double> coeffs = lagr_plnm<double>({0,1,2},{-1,0,5});
    // std::vector<double> coeffs = lagr_plnm<double>({-2,-1,0,1},{4,1,0,1});
    // std::vector<double> coeffs = lagr_plnm<double>({0,1,2,3},{1,2,4,8});
    // std::vector<double> coeffs = lagr_plnm<double>({0,1,2,3},{0,1,0,1});
    // for(auto c : coeffs){
    //     std::cout << c << " ";
    // }

    //  std::vector<Spline> coeffs = cubic_nat_splines({1, 1.5, 2.1, 2.9},{1, 0.7, 0, 0.2});
    //  for(auto c : coeffs){
    //      std::cout << c << '\n';
    //  }
    return 0;
}