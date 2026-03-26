#pragma once
#include <vector>
#include <cassert>
#include "../lib/classes.h"
#include "../lib/functions.h"
#include <cmath>


double neville_intrp(double x0, const Vector& x, const Vector& y);
Vector lagr_plnm(const Vector& x, const Vector& y);
std::vector<Spline> cubic_nat_splines(std::vector<double> x, std::vector<double> y);