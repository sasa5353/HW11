//
// Created by alex on 23.03.2020.
//

#include <cmath>
#include "func.h"

long double X_1[length * 2];

long double *f(long double t, long double *X) {
    for (int i = 0; i < length; i++) {
        X_1[i] = X[i + length];
    }
    
    X_1[length] = exp(-X[length]);
    X_1[length + 1] = exp(-X[length + 1]);
    
    return X_1;
}
