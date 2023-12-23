#include <iostream>
#include<cmath>
double fi1(double x)
{
    return  cos(x + 1) / 2;
}
double fi2(double y)
{
    return -(sin(y) + 0.4);
}
double Det(double a[2][2])
{
    return a[0][0] * a[1][1] - (a[0][1] * a[1][0]);
}
double Jcobi(double x, double y)
{
    double mas[2][2];
    mas[0][0] = sin(x);
    mas[0][1] = 2;
    mas[1][0] = cos(y - 1);
    mas[1][1] = 1;
    return Det(mas);
}
double deltaX(double x, double y)
{
    double mas[2][2];
    mas[0][0] = 2 * y - cos(x + 1);
    mas[0][1] = 2;
    mas[1][0] = sin(y) + x + 0.4;
    mas[1][1] = cos(y);

    return Det(mas);
}
double deltaY(double x, double y)
{
    double mas[2][2];
    mas[0][0] = sin(x + 1);
    mas[0][1] = 2 * y - cos(x + 1);
    mas[1][0] = 1;
    mas[1][1] = sin(y) + x + 0.4;

    return Det(mas);
}
void NewtonMethod(double ep)
{
    double x0 = 0;
    double y0 = -0;
    if (Jcobi(x0, y0) == 0)
        printf("Yakobian = 0!");
    else {
        printf("\n\nNewhon method:\n");
        double x1 = x0 - (deltaX(x0, y0) / Jcobi(x0, y0));
        double y1 = y0 - (deltaY(x0, y0) / Jcobi(x0, y0));
        int k = 0;
        printf(" ________________________________________________");
        do
        {
            x0 = x1;
            y0 = y1;
            x1 = x0 - (deltaX(x0, y0) / Jcobi(x0, y0));
            y1 = y0 - (deltaY(x0, y0) / Jcobi(x0, y0));
            k++;
            printf("\n|%d  | \tx = %.4lf \t| \ty = %.4lf\t|\n", k,x1, y1);
            printf("|___|___________________|_______________________|");
        } while ((fabs(x1 - x0) + fabs(y1 - y0)) > ep);
    }
}
bool check(double x, double y)
{
    return fabs(sin(x - 1)) < 1 && fabs(0.5 * cos(y)) < 1;
}
void IterationMethod(double eps)
{
    double xprev = 0;
    double yprev = 0;
    if (!check(xprev, yprev))
        printf( "The system isn`t convergent!");
    else {
        double x = xprev, y = yprev;
        int k = 0;
        printf("\nIterations method:\n");
        printf(" ________________________________________________");
        do
        {
            xprev = x;
            yprev = y;
            x = fi2(yprev);
            y = fi1(xprev);
            k++;
            printf("\n|%1.d  | \tx = %.4lf \t| \ty = %.4lf\t|\n", k, x, y);
            printf("|___|___________________|_______________________|");
        } while ((fabs(x - xprev) + fabs(y - yprev)) > eps);
    }
}
int main()
{
    double eps = 0.0001;
    IterationMethod(eps);
    NewtonMethod(eps);
    return 0;
}