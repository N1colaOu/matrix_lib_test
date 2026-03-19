#include <cassert>
#include <iostream>
#include "classes.h"
#include <cmath>

Coordinate::Coordinate() = default;
Coordinate::Coordinate(size_t r, size_t c) : row(r), col(c){}
Coordinate::~Coordinate() = default;

Matrix::Matrix() : num_rows(0), num_cols(0), data(nullptr) {}

Matrix::Matrix(std::string filename){
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

Matrix::Matrix(const Matrix &m) : num_rows(m.get_rows()), num_cols(m.get_cols()), data(m.get_data()) {}

Matrix::~Matrix() {delete[] data;} 


size_t Matrix::toIndex(const Coordinate& coord) const{
    return coord.row*(num_cols) + coord.col;
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

Spline::Spline() = default;

Spline::Spline(double _a, double _b, double _c, double _d, double _x) : a(_a), b(_b), c(_c), d(_d), x(_x) {}

Spline::~Spline() = default;

double Spline::get_zero() const{
    return a;
}

double Spline::get_first() const{
    return b;
}

double Spline::get_second() const{
    return c;
}

double Spline::get_third() const{
    return d;
}

double Spline::get_x() const{
    return x;
}

double Spline::get_overall() const{
    return a + b*x + c*x*x + d*x*x*x;
}

double Spline::get_1_derv() const{
    return b + 2*c*x + 3*d*x*x;
}

double Spline::get_2_derv() const{
    return 2*c + 6*d*x;
}


void Spline::set_zero(double _a){
    a = _a;
}

void Spline::set_first(double _b){
    b = _b;
}

void Spline::set_second(double _c){
    c = _c;
}

void Spline::set_third(double _d){
    d = _d;
}

void Spline::set_x(double _x){
    x = _x;
}


