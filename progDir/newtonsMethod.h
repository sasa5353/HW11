//
// Created by alex on 23.03.2020.
//

#ifndef TASK9_NEWTONSMETHOD_H
#define TASK9_NEWTONSMETHOD_H

#include <cmath>
#include "func.h"
#include "quad/Gauss.h"

void newtonMethod(long double*(*)(long double*), long double*, unsigned int, long double *, unsigned int nForNewton = length);
long double deltaNorm(long double*, long double*, unsigned int nForNewton);
long double **jacobi(long double *(*)(long double *), long double *, unsigned int nForNewton);
const long double step = 1e-7;

#endif //TASK9_NEWTONSMETHOD_H
