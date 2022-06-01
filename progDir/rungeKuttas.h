//
// Created by alex on 23.03.2020.
//

#ifndef TASK9_RUNGEKUTTAS_H
#define TASK9_RUNGEKUTTAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "func.h"

void rungeKuttas(std::string, bool writeOut, bool right, long double X_a[2 * length]);
long double *funcForShoot(long double *);
void shoot(std::string, bool right);
void leftShoot(std::string);
void rightShoot(std::string);
void grid(std::string);

long double *funcForGrid(long double *);

#endif //TASK9_RUNGEKUTTAS_H
