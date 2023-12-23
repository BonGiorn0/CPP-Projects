#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;
bool is(double X[10]) {
    double sum = 0;
    for (int i = 0;i < 9;i++) {
        sum += X[i + 1] - X[i];
    }
    if ((int)sum / 9 == 0) {
        return true;
    }
    return false;
}
void methodLagrange(double x0, double X[10], double Y[10]) {
    if (is(X)&&x0!=0)
    {
        printf("Lagrange method:\n");
        double res = 0, top = 1, bot = 1;
        for (int i = 0;i < 10;i++) {
            top = 1;
            bot = 1;
            for (int j = 0;j < 10;j++) {
                if (i == j)   continue;
                top *= x0 - X[j];
                bot *= X[i] - X[j];
            }
            res += (top / bot) * Y[i];
            cout<< endl << res << " = " << top << "/" << bot << "*" << Y[i]<<endl;
        }
        printf("\ny = %f\n",res);
    }
    return;
}
void methodNewton(double x0, double X[10], double Y[10]) {
    if (x0 == 0)  return;
    if (is(X) == false) {
        return;
    }
    printf("\nNewton method:\n");
    double Q, deltaY[9][9], H = X[1] - X[0];
    for (int i = 0;i < 9;i++)
        for (int k = 0;k < 9;k++)
            if(k!=0)
                deltaY[i][k] = 0;
            else
                deltaY[i][0] = Y[i + 1] - Y[i];
    for (int i = 1;i < 9;i++)
        for (int k = 0;k < 9 - i;k++)
            deltaY[k][i] = deltaY[k + 1][i - 1] - deltaY[k][i - 1];
    printf("                                         P(x0)                               D[i]       Y[i] \n");
    for (int i = 0;i < 10;i++)
    {
        printf("%2.0i ", i+1);
        double d = 1;
        for (int j = 0;j < 10;j++)
        {
            if (i == j) {
                printf("%+2.3lf ", x0 - X[j]);
                d = d * (x0 - X[j]);
            }
            else {
                printf("%+2.3lf ", X[i] - X[j]);
                d = d * (X[i] - X[j]);
            }
        }
        cout << d;
        printf("\t%5.2lf \n", Y[i]);
    }
    double QRes = 1, factorial = 1, res = Y[0];
    Q = (x0 - X[0]) / H;
    for (int i = 0;i < 9;i++) {
        factorial *= i + 1;
        QRes *= (Q - i);
        res += (QRes * deltaY[0][i]) / factorial;
    }
    printf("\ny = %f\n",res);
}

int main()
{
    double x0 = 0.3119;
    double X[10] ={0};
    double xi = 0.15;
    for(size_t i = 0; i < 10; i++){
        X[i] = xi;
        xi += 0.05;
    } 
    double Y[10] = {0.86, 0.819, 0.779, 0.741, 0.705, 0.670, 0.638, 0.606, 0.577, 0.549};
    methodLagrange(x0, X, Y);
    methodNewton(x0, X, Y);
    return 0;
}