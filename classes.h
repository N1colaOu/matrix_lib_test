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
    private:
    protected:
    size_t num_rows;
    size_t num_cols;
    double* data;
    size_t toIndex(const Coordinate&) const;
    
    public:
    void add_col(const std::vector<double>&);
    void rem_col(const size_t);
    
    Matrix();
    Matrix(std::string);
    Matrix(size_t, size_t);
    Matrix(const Matrix&);
    virtual ~Matrix();
    
    bool empty() const;
    bool isSquare() const;
    
    double* get_data() const;
    size_t get_rows() const;
    std::vector<double> get_row_val(size_t) const;
    size_t get_cols() const;
    std::vector<double> get_col_val(size_t) const;
    
    virtual double& at(const Coordinate&);
    virtual double at(const Coordinate&) const;
    virtual void print() const;    

    Matrix& operator=(const Matrix&);
    //Matrix*& operator=(const Matrix*&);
};

class Vector : public Matrix{
    public:
    Vector();
    Vector(std::string);
    Vector(size_t);
    Vector(const Vector&);
    Vector(const std::vector<double>&);
    ~Vector();

    double& at(const Coordinate&) override final;
    double at(const Coordinate&) const override final;

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
};

class SymMatrix : public Matrix{

};

class DiagMatrix : public SymMatrix{

};

class TridiagMatrix : public Matrix{

};

class LinSystem{
    Matrix* A;
    Vector* b;
    Vector* x;
    void solve_GJ();
    void solve_LU();
    void solve_QR();
    public:
    LinSystem();
    LinSystem(Matrix*, Vector*);
    virtual ~LinSystem();
    Vector* get_solution(const std::string&);
};
