#pragma once
#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include "classes.h"

double det(Matrix&);
bool existInv(const Matrix&);
bool isSingular(Matrix&);
Matrix transpon(Matrix&);
Matrix* inv(Matrix&);
size_t findPivot(Matrix&, size_t);
void switchRows(Matrix&, size_t, size_t);
Matrix* gj_triangle(Matrix&);
std::ostream& operator<<(std::ostream&, const Spline&);
std::ostream& operator<<(std::ostream&, const Matrix&);
std::ostream& operator<<(std::ostream&, const Vector&);