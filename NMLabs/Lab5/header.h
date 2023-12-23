#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <cstdio>
#include <cstdlib>
#define ROWS 3
#define COLS 3
#define EPS 0.01

void JacobiMethod(double matrixA[ROWS][COLS], double matrixB[ROWS]);
void ZeidelMethod(double matrixA[ROWS][COLS], double matrixB[ROWS]);
void PrintMatrix(double matrix[ROWS][COLS]);
void PrintVector(double vector[ROWS]);

#endif