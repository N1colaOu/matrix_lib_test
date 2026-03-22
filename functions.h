#pragma once
#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include "classes.h"

double det(const Matrix&);
bool existInv(const Matrix&);
bool isSingular(const Matrix&);//wip
Matrix transpon(const Matrix&);
//Matrix inv(const Matrix&);
//size_t findPivot(const Matrix&, size_t);
//void switchRows(Matrix&, size_t, size_t);
//Matrix gj_triangle(const Matrix&);
std::ostream& operator<<(std::ostream&, const Spline&);
std::ostream& operator<<(std::ostream&, const Matrix&);
std::ostream& operator<<(std::ostream&, const Vector&);