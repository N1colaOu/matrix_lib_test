#pragma once
#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

struct Coordinate{
    size_t row;
    size_t col;    
    Coordinate();
    Coordinate(size_t, size_t);
    ~Coordinate();
};

class Matrix{
    protected:
    size_t num_rows;
    size_t num_cols;
    double* data;
    
    size_t toIndex(const Coordinate&) const;

    public:
    Matrix();
    Matrix(std::string);
    Matrix(size_t, size_t);
    Matrix(const Matrix&);
    virtual ~Matrix();
    
    bool empty() const;
    
    double* get_data() const;
    size_t get_rows() const;
    std::vector<double> get_row_val(size_t) const;
    size_t get_cols() const;
    std::vector<double> get_col_val(size_t) const;
    void add_col(const std::vector<double>&);
    void rem_col(const size_t);
    
    double& at(const Coordinate&);
    void print() const;    
};

class Spline{
    double a;
    double b;
    double c;
    double d;
    double x;
    public:
    Spline();
    Spline(double, double, double, double, double);
    ~Spline();

    double get_zero() const;
    double get_first() const;
    double get_second() const;
    double get_third() const;
    double get_x() const;
    double get_overall() const;
    double get_1_derv() const;
    double get_2_derv() const;

    void set_zero(double);
    void set_first(double);
    void set_second(double);
    void set_third(double);
    void set_x(double);

};