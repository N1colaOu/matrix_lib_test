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
Matrix inv(const Matrix&); //wip
std::ostream& operator<<(std::ostream&, const Spline&);
std::ostream& operator<<(std::ostream&, const Matrix&);
std::ostream& operator<<(std::ostream&, const Vector&);
bool operator==(const Matrix&, const Matrix&);
bool operator==(const Vector&, const Vector&);

Matrix MatMatMult(const Matrix&, const Matrix&);
Vector MatVecMult(const Matrix&, const Vector&);