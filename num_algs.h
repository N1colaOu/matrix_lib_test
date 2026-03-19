#pragma once
#include <vector>
#include <cassert>
#include "classes.h"
#include "functions.h"
#include <cmath>


double neville_intrp(double x0, std::vector<double> x, std::vector<double> y);
std::vector<double> lagr_plnm(std::vector<double> x, std::vector<double> y);
std::vector<Spline> cubic_nat_splines(std::vector<double> x, std::vector<double> y);