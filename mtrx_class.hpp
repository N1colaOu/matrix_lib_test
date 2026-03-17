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

template<typename T>
class Matrix{
    protected:
    size_t num_rows;
    size_t num_cols;
    T* data;
    
    size_t toIndex(const Coordinate&) const;

    public:
    Matrix();
    Matrix(std::string);
    Matrix(size_t, size_t);
    Matrix(const Matrix&);
    virtual ~Matrix();
    
    bool empty() const;
    
    T* get_data() const;
    size_t get_rows() const;
    std::vector<T> get_row_val(size_t) const;
    size_t get_cols() const;
    std::vector<T> get_col_val(size_t) const;
    void add_col(const std::vector<T>&);
    void rem_col(const size_t);
    
    T& at(const Coordinate&);
    void print() const;    
};

template<typename T>
Matrix<T>::Matrix() : num_rows(0), num_cols(0), data(nullptr) {}
template<typename T>
Matrix<T>::Matrix(std::string filename){
    std::ifstream input(filename);
    input >> num_rows >> num_cols;
    data = new T[num_cols*num_rows];
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            input >> data[i*num_cols + j];
        }  
    }
    input.close();
}
template<typename T>
Matrix<T>::Matrix(size_t r, size_t c) : num_rows(r), num_cols(c), data(new T[r*c]) {
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            data[i*num_cols+j] = 0;
        }
    }
}
template<typename T>
Matrix<T>::Matrix(const Matrix &m) : num_rows(m.get_rows()), num_cols(m.get_cols()), data(m.get_data()) {}
template<typename T>
Matrix<T>::~Matrix() {delete[] data;} 

template<typename T>
size_t Matrix<T>::toIndex(const Coordinate& coord) const{
    return coord.row*(num_cols) + coord.col;
}

template<typename T>
bool Matrix<T>::empty() const{
    return data == nullptr && num_cols == 0 && num_rows == 0;
}
template<typename T>
size_t Matrix<T>::get_rows() const{
    return num_rows;
}
template<typename T>
std::vector<T> Matrix<T>::get_row_val(size_t idx) const{
    std::vector<T> row;
    row.reserve(num_cols);
    for (size_t i = 0; i < num_cols; i++)
    {
        row.push_back(data[idx*num_cols + i]);
    }
    return row;
}
template<typename T>
size_t Matrix<T>::get_cols() const{
    return num_cols;
}
template<typename T>
std::vector<T> Matrix<T>::get_col_val(size_t idx) const{
    std::vector<T> col;
    col.reserve(num_rows);
    for (size_t i = 0; i < num_rows; i++)
    {
        col.push_back(data[idx + i*num_cols]);
    }
    return col;
}
template<typename T>
T* Matrix<T>::get_data() const{
    return data;
}
template<typename T>
void Matrix<T>::add_col(const std::vector<T>& column){
    num_cols++;
    T* data_new = new T[num_cols*num_rows];
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

template<typename T>
void Matrix<T>::rem_col(const size_t idx){
    size_t ctr_new{};
    T* data_new = new T[(num_cols-1)*num_rows];
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

template<typename T>
T& Matrix<T>::at(const Coordinate& coord){
    return data[toIndex(coord)];
}

template<typename T>
void Matrix<T>::print() const {
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            std::cout << data[i * num_cols + j] << " ";       
        }
        std::cout << '\n';
    }
}

// template<typename T>
// void Matrix<T>::fill_up(std::string filename){

// }

