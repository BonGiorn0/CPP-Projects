#include "header.h"

int main()
{
//    double dMatrixA = (double)malloc(ROWS * sizeof(double*));
//    for(int i=0;i<ROWS;i++)
//    {
//        dMatrixA[i] = (double*)malloc(COLS * sizeof(double));
//    }
//
//    double *dMatrixB = (double*)malloc(ROWS * sizeof(double));
//
//    for (int i = 0;i < ROWS;i++) {
//        printf("Enter  koefs of %d equations \n", i + 1);
//        for (int j = 0;j < COLS;j++) {
//            scanf_s("%lf", &dMatrixA[i][j]);
//        }
//        scanf_s("%lf", &dMatrixB[i]);
//    }

    double dMatrixA[ROWS][COLS] = {
        {0.11, -0.46, -0.36},
        {0.12, 0.08, -0.34},
        {0.15, -0.35, -0.18}
    };
    double dMatrixB[ROWS] = {-0.44, 1.42, -0.83};

    printf("------------------------------------------------\n");
    printf("Matrix A:\n");
    PrintMatrix(dMatrixA);
    printf("Vector B:\n");
    PrintVector(dMatrixB);

    printf("Jacobi Method:\n\n");
    JacobiMethod(dMatrixA, dMatrixB);
    printf("Zeidel Method:\n\n");
    ZeidelMethod(dMatrixA, dMatrixB);

//    for (int i = 0; i < ROWS; ++i) {
//        free(dMatrixA[i]);
//    }
//    free(dMatrixB);
//    free(dMatrixA);

    system("pause");
    return 0;
}