#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
#define K 5

void print_matrix(double matrix[3][3]);

double Det3(double a[3][3]);
double Det2(double a[3][3],int i1,int j1);
void Inverse(double a[3][3], double b[3][3]);
void multiple(double a[3][K],double b[3][1],double x[3][1]);
void multiple2(double a[3][3],double b[3][1],double x[3][1]);
void multiple3(double a[3][K],double b[K][3], double c[3][3], int row1, int col1, int col2);


int main()
{
//    int Arr[5][4] = {1,3,-2,-5,
//                    -1,2,1,1,
//                    3,-2,-2,-5,
//                    3,1,-3,1,
//                    1,-1,-7,5};
//
    double A[5][3] = {
        {2, 2, -1},
        {4, 3, -1},
        {8, 5, -3},
        {3, 3, -2},
        {1, 2, -1}
    };
    double B[5][1] = {-2 , -1, -3, -4, 12};

    //double A[6][3] = {1,0,0,1,1,0,1,1,1,0,1,0,0,1,1,0,0,1};
    //double B[6][1] = {1.4,-1.5,3.2,0.6,4.3,4.2};

    double AT[3][K];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < K; ++j) {
            AT[i][j] = A[j][i];
        }
    }

    double N[3][3];
    multiple3(AT,A,N,3,K,3);

    cout << "Matrix N:\n";
    print_matrix(N);

    double C[3][1];
    multiple(AT,B,C);

    cout << "\nMatrix C:\n" << C[0][0] << " " << C[1][0] << " " << C[2][0] << endl;

    cout << "\nDet. N:" << Det3(N) << endl;
    if(Det3(N) <= 0)
        return 0;

    double L[3][3] = {0};
    L[0][0] = sqrt(N[0][0]);
    L[1][0] = N[1][0] / L[0][0];
    L[2][0] = N[2][0] / L[0][0];
    L[1][1] = sqrt(N[1][1] - (L[1][0] * L[1][0]) );
    L[2][1] = (N[2][1] - L[2][0] * L[1][0]) / L[1][1];
    L[2][2] = sqrt( N[2][2] - L[2][0] * L[2][0] - L[2][1] * L[2][1] );

    cout << "\nMatrix L:\n";
    //print_matrix(L);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            printf("% .3f ", L[i][j]);
        cout << '\n';
    }    

    double Y[3][1];
    double LObern[3][3];
    Inverse(L,LObern);
    multiple2(LObern,C,Y);

    cout << "\nMatrix Y:\n" << Y[0][0] << " " << Y[1][0] << " " << Y[2][0] << endl;

    double LT[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            LT[i][j] = L[j][i];
        }
    }

    double X[3][1];
    double LTObern[3][3];
    Inverse(LT,LTObern);
    multiple2(LTObern,Y,X);

    cout << "\nMatrix X:\n" << X[0][0] << " " << X[1][0] << " " << X[2][0] << endl;
    return 0;
}

void print_matrix(double matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

double Det3(double a[3][3])
{
    double temp = a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[1][0] * a[2][1] * a[0][2] - ( a[0][2] * a[1][1] * a[2][0] + a[0][1] * a[1][0] * a[2][2] + a[0][0] * a[1][2] * a[2][1] );
    return temp;
}

double Det2(double a[3][3],int i1,int j1)
{
    double temp[2][2];
    int row=0,col=0;
    for (int i = 0; i < 3;i++)
    {
        if(i!=i1)
        {
            col = 0;
            for (int j = 0; j < 3;j++)
            {
                if (j != j1 )
                {
                    temp[row][col] = a[i][j];
                    col++;
                }
            }
            row++;
        }
    }
    return (pow(-1,i1+j1+2) * ( temp[0][0] * temp[1][1] - ( temp[0][1] * temp[1][0] )));
}

void Inverse(double a[3][3], double b[3][3])
{
    double tempdet = Det3(a);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            b[j][i] = ( Det2(a,i,j) / tempdet );
        }
    }
}

void multiple(double a[3][K],double b[3][1],double x[3][1])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<K;j++)
        {
            x[i][0] = x[i][0] + a[i][j] * b[j][0];
        }
    }
}

void multiple3(double a[3][K],double b[K][3], double c[3][3], int row1, int col1, int col2)
{
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            c[i][j] = 0;
            for (int k = 0; k < col1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
}

void multiple2(double a[3][3],double b[3][1],double x[3][1])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            x[i][0] = x[i][0] + a[i][j] * b[j][0];
        }
    }
}