#pragma once
#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>

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
    Matrix(size_t, size_t);
    Matrix(const Matrix&);
    virtual ~Matrix();
    
    

    bool empty() const;
    
    
    
    size_t get_rows() const;
    size_t get_cols() const;
    void add_col(const std::vector<T>&);
    void rem_col(const size_t);
    T* get_data() const;
    
    T& at(const Coordinate&);
    void print() const;
    void fill_up();
    
    
};

// template<typename T>
// T det(Matrix<T>&);

// template<typename T>
// Matrix<T> inv(const Matrix<T>&);

// template<typename T>
// Matrix<T> transpon(const Matrix<T>&);

// template<typename T>
// bool existInv(const Matrix<T>&);

// template<typename T>
// bool isSquare(const Matrix<T>&);

///////////////////////////////////////////////////////

template<typename T>
Matrix<T>::Matrix() : num_rows(0), num_cols(0), data(nullptr) {}
template<typename T>
Matrix<T>::Matrix(size_t r, size_t c) : num_rows(r), num_cols(c), data(new T[r*c]) {}
template<typename T>
Matrix<T>::Matrix(const Matrix &m) : num_rows(m.get_rows()), num_cols(m.get_cols()), data(m.get_data()) {}
template<typename T>
Matrix<T>::~Matrix() {delete[] data;} 

template<typename T>
size_t Matrix<T>::toIndex(const Coordinate& coord) const{
    return coord.row*(num_cols) + coord.col;
}

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
bool Matrix<T>::empty() const{
    return data == nullptr && num_cols == 0 && num_rows == 0;
}

template<typename T>
size_t Matrix<T>::get_rows() const{
    return num_rows;
}
template<typename T>
size_t Matrix<T>::get_cols() const{
    return num_cols;
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

template<typename T>
void Matrix<T>::fill_up(){
    std::cout << "Enter your " << num_rows << "x" << num_cols << " matrix!\n";
    for (size_t i = 0; i < num_rows; i++)
    {
        std::cout << "Enter row " << i << ": ";
        for (size_t j = 0; j < num_cols; j++)
        {
            std::cin >> data[i*num_cols + j];
        }
    }
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