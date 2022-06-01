//
// Created by alex on 23.03.2020.
//

#include <iostream>
#include "newtonsMethod.h"

void newtonMethod(long double *(*funcPointer)(long double *), long double *X0, unsigned int maxIter, long double *X2, unsigned int nForNewton) {
    long double *X1;
    long double **matrix;
    X1 = new long double[nForNewton];
    for (unsigned int i = 0; i < nForNewton; i++) {
        X2[i] = X0[i];
    }
    long double *tmp = new long double [nForNewton];
    long double fX1[nForNewton];
    for (unsigned int iter = 0; (iter < 15) || ((iter < maxIter) && deltaNorm(X1, X2, nForNewton) > 1e-7); iter++) {
        for (unsigned int i = 0; i < nForNewton; i++) {
            X1[i] = X2[i];
        }
        for (unsigned int i = 0; i < nForNewton; i++) {
            fX1[i] = -funcPointer(X1)[i];
        }
        matrix = jacobi(funcPointer, X1, nForNewton);
        gaussMod(matrix, fX1, nForNewton, tmp);
        for (unsigned int i = 0; i < nForNewton; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        for (unsigned int i = 0; i < nForNewton; i++) {
            X2[i] = X1[i] + tmp[i];
        }
        
    }
    delete[] tmp;
    delete[] X1;
}

long double deltaNorm(long double *X1, long double *X2, unsigned int nForNewton) {
    long double result = 0.0;
    long double tmp;
    for (unsigned int i = 0; i < nForNewton; i++) {
        tmp = X2[i] - X1[i];
        result += tmp * tmp;
    }
    return sqrt(result);
}

long double **jacobi(long double *(*funcPointer)(long double *), long double *X, unsigned int nForNewton) {
    long double **a;
    long double tmp[nForNewton];
    a = new long double *[nForNewton];
    for (unsigned int i = 0; i < nForNewton; i++) {
        tmp[i] = X[i];
    }
    for (unsigned int i = 0; i < nForNewton; i++) {
        a[i] = new long double[nForNewton];
        for (unsigned int j = 0; j < nForNewton; j++) {
            tmp[j] += step;
            a[i][j] = ((*funcPointer)(tmp)[i] - (*funcPointer)(X)[i]) / step;
            tmp[j] -=step;
        }
    }
    return a;
}
