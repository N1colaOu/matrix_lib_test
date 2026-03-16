#include <cassert>
#include <iostream>
#include "mtrx_class.hpp"
#include <cmath>

Coordinate::Coordinate() = default;
Coordinate::Coordinate(size_t r, size_t c) : row(r), col(c){}
Coordinate::~Coordinate() = default;

