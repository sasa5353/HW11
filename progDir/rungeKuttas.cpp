//
// Created by alex on 23.03.2020.
//

#include <cmath>
#include "rungeKuttas.h"
#include "newtonsMethod.h"

const long double aFirst = (long double) 0.0;
const long double bFirst = (long double) 1.0;
const long double hFirst = 5.0e-3;
const long long p = ((10 * (bFirst - aFirst) / hFirst + (long double) 0.5) / 10);


void rungeKuttas(std::string s, bool writeOut, bool right, long double X_a[2 * length]) {
    
    long double a = aFirst;
    long double b = bFirst;
    long double h = hFirst;
    std::ofstream out;
    out.setf(std::ios::scientific);
    out.precision(10);
    out.open(s);
    const int devid = 2;
    long double X[devid][2 * length];
    for (int i = 0; i < 2 * length; i++) {
        X[0][i] = X_a[i];
    }
    if (right) {
        a = b;
        h *= (long double) -1.0;
    }
    
    long double k[4][2 * length];
    long double tmp[2 * length];
    long double t_i = a;
    if (writeOut) {
        out << t_i << " ";
        for (int i = 0; i < 2 * length; i++) {
            out << X[0][i] << " ";
        }
        out << std::endl;
    }
    for (long long unsigned i = 0; i < p; i++) {
        t_i = a + h * i;
        for (int j = 0; j < 2 * length; j++) {
            k[0][j] = h * f(t_i, X[i % devid])[j];
        }
        for (int j = 0; j < 2 * length; j++) {
            tmp[j] = X[i % devid][j] + k[0][j] / (long double) 2.0;
        }
        for (int j = 0; j < 2 * length; j++) {
            k[1][j] = h * f(t_i + h / (long double) 2.0, tmp)[j];
        }
        for (int j = 0; j < 2 * length; j++) {
            tmp[j] = X[i % devid][j] + k[1][j] / (long double) 2.0;
        }
        for (int j = 0; j < 2 * length; j++) {
            k[2][j] = h * f(t_i + h / (long double) 2.0, tmp)[j];
        }
        for (int j = 0; j < 2 * length; j++) {
            tmp[j] = X[i % devid][j] + k[2][j];
        }
        for (int j = 0; j < 2 * length; j++) {
            k[3][j] = h * f(t_i + h, tmp)[j];
        }
        
        for (int j = 0; j < 2 * length; j++) {
            X[(i + 1) % devid][j] =
                    X[i % devid][j] + (k[0][j] + (long double) 2.0 * (k[1][j] + k[2][j]) + k[3][j]) / (long double) 6.0;
        }
        if (writeOut) {
            t_i += h;
            out << t_i << " ";
            for (int j = 0; j < length; j++) {
                out << X[(i + 1) % devid][j] << " ";
            }
            out << std::endl;
        }
    }
    out.close();
    if (!writeOut) {
        out.open("justOnce_" + s);
        for (int i = 0; i < length; i++) {
            out << X[p % devid][i] << " ";
        }
        out << std::endl;
        out.close();
    }
}

bool flag;
std::string tmpStr;

void shoot(std::string s, bool right) {
    flag = right;
    tmpStr = s;
    
    long double importantArray[length];
    importantArray[0] = (long double) 0.0 ;
    importantArray[1] = (long double) 0.0 ;
    
    long double *ans = new long double[length];
    newtonMethod(funcForShoot, importantArray, 1000, ans);
    
    long double tmp[2 * length];
    for (int i = 0; i < length; i++) {
        tmp[i] = (flag) ? X_0_r[i] : X_0_l[i];
    }
    for (int i = 0; i < length; i++) {
        tmp[length + i] = ans[i];
    }
    delete[] ans;
    
    rungeKuttas(s, true, right, tmp);
}

long double X_b[length];

long double *funcForShoot(long double *Y) {
    long double tmp[2 * length];
    for (int i = 0; i < length; i++) {
        tmp[i] = (flag) ? X_0_r[i] : X_0_l[i];
    }
    for (int i = 0; i < length; i++) {
        tmp[length + i] = Y[i];
    }
    
    rungeKuttas(tmpStr, false, flag, tmp);
    std::ifstream in;
    in.open("justOnce_" + tmpStr);
    for (int i = 0; i < length; i++) {
        in >> X_b[i];
    }
    in.close();
    
    for (int i = 0; i < length; i++) {
        X_b[i] -= (flag) ? X_0_l[i] : X_0_r[i];
    }
    return X_b;
}

void leftShoot(std::string s) {
    shoot(s, false);
}

void rightShoot(std::string s) {
    shoot(s, true);
}

long double importantArray[length * (p + 1)];
void grid(std::string s) {
    tmpStr = s;
    std::ofstream out;
    out.setf(std::ios::scientific);
    out.precision(10);
    out.open(s);
    
    long double percip[length * (p + 1)];
    std::fill_n(percip, length * (p + 1), (long double) 0.0);
    
    newtonMethod(funcForGrid, percip, 1000, importantArray, length * (p + 1));
    long double t_i;
    long double *reallyImportantPointer = importantArray + (p + 1);
    
    for (int i = 0; i <= p; i++) {
        t_i = aFirst + i * hFirst;
        out << t_i << " " << importantArray[i] << " " << reallyImportantPointer[i] << std::endl;
    }
}

long double LaTeX[length * (p + 1)];
long double *funcForGrid(long double *array) {
    long double *x = array;
    long double *y = array + (p + 1);
    LaTeX[0] = x[0] - X_0_l[0];
    LaTeX[p] = x[p] - X_0_r[0];
    LaTeX[p + 1] = y[0] - X_0_l[1];
    LaTeX[length * (p + 1) - 1] = y[p] - X_0_r[1];
    
    for (int i = 1; i < p; i++) {
        LaTeX[i] = (x[i + 1] - (long double) 2.0 * x[i] + x[i - 1]) / (hFirst * hFirst) - exp(-(x[i + 1] - x[i - 1]) / hFirst / (long double) 2.0);
        LaTeX[i + (p + 1)] = (y[i + 1] - (long double) 2.0 * y[i] + y[i - 1]) / (hFirst * hFirst) - exp(-(y[i + 1] - y[i - 1]) / hFirst / (long double) 2.0);
    }
    return LaTeX;
}
