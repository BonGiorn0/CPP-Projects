#include "header.h"
#include <math.h>

void JacobiMethod(double matrixA[ROWS][COLS], double *matrixB)
{
    double dMatrixX[COLS], dMatrixOldX[COLS];
    double dMatrixAlpha[ROWS][COLS] = {0};
//    for (int i = 0; i < ROWS; ++i) {
//        dMatrixAlpha[i] = (double*)calloc(COLS, sizeof(double));
//    }
    double dMatrixBeta[ROWS] = {0};
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == j)
            {
                dMatrixAlpha[i][i] = 0;
                continue;
            }
            dMatrixAlpha[i][j] = -matrixA[i][j] / matrixA[i][i];
        }
    }
    for (int i = 0; i < ROWS; ++i) {
        dMatrixBeta[i] = matrixB[i] / matrixA[i][i];
    }
    //printf("Casting matrixes to normal type:\n");
    printf("Matrix Alpha:\n");
    PrintMatrix(dMatrixAlpha);
    printf("Matrix Beta:\n");
    PrintVector(dMatrixBeta);
    for (int i = 0; i < COLS; ++i) {
        dMatrixX[i] = 0;
    }
    int Iteration = 1;
    do {
        for (int i = 0; i < COLS; ++i) {
            dMatrixOldX[i] = dMatrixX[i];
        }
        for (int i = 0; i < COLS; ++i) {
            dMatrixX[i] = dMatrixBeta[i];
            for (int j = 0; j < COLS; ++j) {
                if (j == i) continue;
                dMatrixX[i] += dMatrixAlpha[i][j] * dMatrixOldX[j];
            }
        }
        printf("Vector X after iteration %i:\n", Iteration);
        PrintVector(dMatrixX);
        Iteration++;

    } while (fabs(dMatrixX[0] - dMatrixOldX[0]) > (EPS));

    printf("RESULTS:\nVector X:\n");
    PrintVector(dMatrixX);

//    free(dMatrixBeta);
//    for (int i = 0; i < ROWS; ++i) {
//        free(dMatrixAlpha[i]);
//    }
//    free(dMatrixAlpha);
}
//------------------------------------------------------------------------------------
void ZeidelMethod(double matrixA[ROWS][COLS], double *matrixB)
{
double dMatrixX[COLS], dMatrixOldX[COLS];

double dMatrixAlpha[ROWS][COLS] = {0};
//for (int i = 0; i < ROWS; ++i) {
//dMatrixAlpha[i] = (double*)calloc(COLS, sizeof(double));
//}

double dMatrixBeta[ROWS] = {0};

for (int i = 0; i < ROWS; ++i) {
for (int j = 0; j < COLS; ++j) {
if (i == j)
{
dMatrixAlpha[i][i] = 0;
continue;
}
dMatrixAlpha[i][j] = -matrixA[i][j] / matrixA[i][i];
}
}
for (int i = 0; i < ROWS; ++i) {
dMatrixBeta[i] = matrixB[i] / matrixA[i][i];
}
//printf("Casting matrixes to normal type:\n");
printf("Matrix Alpha:\n");
PrintMatrix(dMatrixAlpha);
printf("Matrix Beta:\n");
PrintVector(dMatrixBeta);
for (int i = 0; i < COLS; ++i) {
dMatrixX[i] = 0;
}
int Iteration = 1;
do {
for (int i = 0; i < COLS; ++i) {
dMatrixOldX[i] = dMatrixX[i];
}
for (int i = 0; i < COLS; ++i) {
dMatrixX[i] = dMatrixBeta[i];
for (int j = 0; j < COLS; ++j) {
if (j == i) continue;
dMatrixX[i] += dMatrixAlpha[i][j] * dMatrixX[j];
}
}
printf("Vector X after iteration %i:\n", Iteration);
PrintVector(dMatrixX);
Iteration++;
} while (fabs(dMatrixX[0] - dMatrixOldX[0]) > EPS);

printf("RESULTS:\nVector X:\n");
PrintVector(dMatrixX);

//free(dMatrixBeta);
//for (int i = 0; i < ROWS; ++i) {
//free(dMatrixAlpha[i]);
//}
//free(dMatrixAlpha);
}
//------------------------------------------------------------------------------------
void PrintMatrix(double matrix[ROWS][COLS])
{
    for (int i = 0;i< ROWS;i++)
    {
        for (int j = 0;j< COLS ;j++)
        {
            printf("%-7.3lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n------------------------------------------------\n");
}
//------------------------------------------------------------------------------------
void PrintVector(double *vector)
{
    for (int i = 0;i< COLS;i++)
    {
        printf("%-7.3lf ", vector[i]);
    }
    printf("\n");
    printf("\n------------------------------------------------\n");
}