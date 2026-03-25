#include <cassert>
#include <iostream>
#include "classes.h"
#include "functions.h"
#include <cmath>

Coordinate::Coordinate() = default;
Coordinate::Coordinate(size_t r, size_t c) : row(r), col(c){}
Coordinate::~Coordinate() = default;

Matrix::Matrix() : num_rows(0), num_cols(0), data(nullptr) {}

Matrix::Matrix(const std::string& filename){
    std::ifstream input(filename);
    input >> num_rows >> num_cols;
    data = new double[num_cols*num_rows];
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            input >> data[i*num_cols + j];
        }  
    }
    input.close();
}

Matrix::Matrix(size_t r, size_t c) : num_rows(r), num_cols(c), data(new double[r*c]) {
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            data[i*num_cols+j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &m) : num_rows(m.get_rows()), num_cols(m.get_cols()){
    data = new double[num_cols*num_rows];
    for (size_t i = 0; i < num_cols*num_rows; i++)
    {
        data[i] = m.get_data()[i];
    }
}

Matrix::~Matrix() {if(data != nullptr) delete[] data; } 


size_t Matrix::toIndex(const Coordinate& coord) const{
    return coord.row*(num_cols) + coord.col;
}

bool Matrix::isSquare() const{
    return num_cols == num_rows;
}
bool Matrix::empty() const{
    return data == nullptr && num_cols == 0 && num_rows == 0;
}

size_t Matrix::get_rows() const{
    return num_rows;
}

std::vector<double> Matrix::get_row_val(size_t idx) const{
    std::vector<double> row;
    row.reserve(num_cols);
    for (size_t i = 0; i < num_cols; i++)
    {
        row.push_back(data[idx*num_cols + i]);
    }
    return row;
}

size_t Matrix::get_cols() const{
    return num_cols;
}

std::vector<double> Matrix::get_col_val(size_t idx) const{
    std::vector<double> col;
    col.reserve(num_rows);
    for (size_t i = 0; i < num_rows; i++)
    {
        col.push_back(data[idx + i*num_cols]);
    }
    return col;
}

double* Matrix::get_data() const{
    return data;
}

void Matrix::add_col(const std::vector<double>& column){
    num_cols++;
    double* data_new = new double[num_cols*num_rows];
    size_t ctr_old{}, ctr_col{};
    for (size_t i = 0; i < num_cols*num_rows; i++)
    {
        if((i+1) % num_cols == 0){
            data_new[i] = column[ctr_col++];
        }
        else{
            data_new[i] = data[ctr_old++];
        }
    }
    delete[] data;
    data = data_new;
}


void Matrix::rem_col(const size_t idx){
    size_t ctr_new{};
    double* data_new = new double[(num_cols-1)*num_rows];
    for (size_t i = 0; i < num_cols*num_rows; i++)
    {
        if((i-idx) % num_cols != 0){
            data_new[ctr_new++] = data[i];
        }
    }
    num_cols--;
    delete[] data;
    data = data_new;
}


double& Matrix::at(const Coordinate& coord){
    return data[toIndex(coord)];
}
double Matrix::at(const Coordinate& coord) const{
    return data[toIndex(coord)];
}


void Matrix::print() const {
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            std::cout << data[i * num_cols + j] << " ";       
        }
        std::cout << '\n';
    }
}

Matrix& Matrix::operator=(const Matrix& m){
    if(data != nullptr) delete[] data;
    num_rows = m.get_rows();
    num_cols = m.get_cols();
    data = new double[num_cols*num_cols];
    for (size_t i = 0; i < num_cols*num_rows; i++)
    {
        data[i] = m.get_data()[i];
    }
    return *this;
}
// Matrix*& Matrix::operator=(const Matrix*& m){
//     num_rows = m->get_rows();
//     num_cols = m->get_cols();
//     data = m->get_data();
//     return this;
// }

Spline::Spline() = default;
Spline::Spline(double _a, double _b, double _c, double _d, double _x) : a(_a), b(_b), c(_c), d(_d), x(_x) {}
Spline::~Spline() = default;
double Spline::get_zero() const{return a;}
double Spline::get_first() const{return b;}
double Spline::get_second() const{return c;}
double Spline::get_third() const{return d;}
double Spline::get_x() const{return x;}

Vector::Vector() : rows(0), data(nullptr){}
Vector::Vector(const std::string& filename){
    std::ifstream input(filename);
    input >> rows;
    data = new double[rows];
    for (size_t i = 0; i < rows; i++)
    {
        input >> data[i];
    }
    input.close();
}
Vector::Vector(size_t r) : rows(r), data(new double[r]){}
Vector::Vector(const Vector& vctr) : rows(vctr.get_rows()){
    if(vctr.get_data() !=  nullptr)
    data = new double[rows];
    for (size_t i = 0; i < rows; i++)
    {
        data[i] = vctr.get_data()[i];
    }
}
Vector::Vector(const std::vector<double>& vctr) : rows(vctr.size()){data = const_cast<double*>(vctr.data());}
Vector::~Vector(){delete[] data;}
double& Vector::at(size_t i){return data[i];}
double Vector::at(size_t i) const {return data[i];}

size_t Vector::get_rows() const{
    return rows;
}
double* Vector::get_data() const{
    return data;
}

Vector& Vector::operator=(const Vector& v){
    if(data != nullptr) delete[] data;
    rows = v.get_rows();
    data = new double[rows];
    for (size_t i = 0; i < rows; i++)
    {
        data[i] = v.get_data()[i];
    }
    return *this;
}

namespace{
    size_t findPivot(Matrix& m, size_t curr_col){
        double max_el{};
        size_t max_idx{m.get_rows()};
        for (size_t i = curr_col; i < m.get_rows(); i++)
        {
            if(m.at({i, curr_col}) != 0){
                if(max_el <= std::abs(m.at({i, curr_col}))){
                    max_el = std::abs(m.at({i, curr_col}));
                    max_idx = i;
                }
            }
        }
        return max_idx;
    }
    void switchRows(Matrix& m, size_t row1, size_t row2){
    assert(row1 < m.get_rows() && row2 < m.get_rows());
    for (size_t j = 0; j < m.get_cols(); j++)
    {
        double temp = m.at({row1, j});
        m.at({row1, j}) = m.at({row2, j});
        m.at({row2, j}) = temp;
    } 
}
}

GJLinSystem::GJLinSystem() = default;
GJLinSystem::GJLinSystem(const Matrix& _A, const Vector& _b) : A(_A), b(_b){}
GJLinSystem::~GJLinSystem() = default;
Vector GJLinSystem::solve(){
    assert(A.isSquare());
    assert(A.get_data() != nullptr);
    size_t n = A.get_cols();

    for (size_t i = 0; i < n; i++)
    {
        double coef;
        if(A.at({i, i}) < 1e-9){
            size_t pivotPoint = findPivot(A, i);//find the row to pivot with
            if(pivotPoint >= n){
                std::cout << "No singular defined solution!\n";//if it doesnt exist -> no sol
                assert(false);
            }
            switchRows(A, i, pivotPoint);
        }
        coef = A.at({i, i});
        A.at({i, i}) = 1.0;
        for (size_t j = i+1; j < n; j++)
        {
            A.at({i, j}) /= coef; //normalize the row
        }
        b.at(i) /= coef; 
        for (size_t j = 0; j < n; j++)
        {
            if(j==i) continue;
            coef = A.at({j, i});
            if(coef == 0.0) continue;
            for (size_t k = 0; k < n; k++)//can be sped up
            {
                A.at({j, k}) -= A.at({i, k})*coef; //nullify the coresponding element and decrement the row    
            } 
            b.at(j) -= b.at(i)*coef;
        }   
    } 
    return b;
}

LULinSystem::LULinSystem() = default;
LULinSystem::LULinSystem(const Matrix& _A, const Vector& _b) : A(_A), b(_b){
    assert(A.isSquare());
    assert(!isSingular(A));
    size_t n = A.get_cols();
    L = Matrix(n, n);
    U = Matrix(n, n);
    P = Matrix(n, n); //permutation matrix
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j <  n; j++)
        {
            if(i == j)  P.at({i, j}) = 1.0;
            else P.at({i, j}) = 0.0;
        }
    }
    
    for (size_t i = 0; i < n; i++) //we pivot the whole matrix A so that the diag elements are not 0 or near 0
    {
        if(A.at({i, i}) < 1e-9){
            size_t to_swap = findPivot(A, i);
            if(to_swap < n){
                switchRows(A, i, to_swap);
                switchRows(P, i, to_swap);
            }
        }
    }
    
    for (size_t i = 0; i < n; i++)//this for loop sets all the start known values and the3 rest are zeroes
    {
        for (size_t j = 0; j < n; j++)
        {
            L.at({i, j}) = 0.0;
        }
        for (size_t j = i+1; j < n; j++)
        {
            U.at({i, j}) = 0.0;
        }
        U.at({0, i}) = A.at({0, i});
        L.at({i, i}) = 1.0;
        L.at({i, 0}) = A.at({i, 0}) / U.at({0, 0});
    } 
    for (size_t i = 1; i < n; i++)
    {
        for (size_t j = 0; j < i; j++)//for L
        {
            double sum{};
            for (size_t k = 0; k < j; k++)
            {
                sum += L.at({i, k}) * U.at({k, j});
            }
            L.at({i, j}) = (A.at({i, j}) - sum) / U.at({j, j});
        }
        for (size_t j = i; j < n; j++)//for U
        {
            double sum{};
            for (size_t k = 0; k < i; k++)
            {
                sum += L.at({i, k}) * U.at({k, j});
            }
            U.at({i, j}) = A.at({i, j}) - sum;
        }
    }
    Matrix A_check = MatMatMult(P, MatMatMult(L, U));
    assert(_A == A_check); //we check if the factorization and pivoting when multipled lead to the start matrix
}
LULinSystem::~LULinSystem() = default;
Vector LULinSystem::solve(){
    size_t n = U.get_cols();
    Vector y(n), b_scrambled(MatVecMult(P, b));

    y.at(0) = b_scrambled.at(0);
    for (size_t i = 1; i < n; i++)
    {
        double sum{};
        for (size_t j = 0; j < i; j++)
        {
            sum += b_scrambled.at(j-1)*L.at({j, j-1});
        } 
        b_scrambled.at(i) -= sum; 
    }
    y = b_scrambled;
    // for (size_t i = 0; i < n; i++)//normalize diagonal
    // {
    //     y.at(i) /= U.at({i, i});
    // }
    for (int i = n-1; i >=0; i--)
    {
        double sum{};
        for (int j = n-1; j > i ; j--)
        {
            sum += y.at(j)*U.at({j-1, j});
        }
        y.at(i) -= sum;
        y.at(i) /= U.at({i, i});
    }
    //y = MatVecMult(P, y);
    return y; 
}
