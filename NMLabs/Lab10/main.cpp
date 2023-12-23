#include <cmath>
#include <stdio.h>
double y(double x)
{
	return log(1 + x) / (1 + 3*x + 3*x*x);
}
void quadro(double a,double b)
{
	double h = (b-a)/100;
	double x = a;
	double sum[11];
	double sumMed[11];
	double sumL=0,sumR=0,sumM=0;
	printf("Array of points:\n");
	for (int i = 0;i < 11;i++)
	{
		sum[i]=y(x);
		sumMed[i]=y(x+h/2);
		x += h;
		printf("%lf ", sum[i]);
	}
	printf("\n");
	for (int i = 0;i < 10;i++)
	{
		sumL += sum[i];
		//printf("%lf+", sum[i]);
	}
	printf("Result of left side:");
	printf("\n%lf",sumL*h);
	for (int i = 1;i <= 10;i++)
	{
		sumR += sum[i];
		//printf("%lf+", sum[i]);
	}
	//printf("=%lf", sumL);
	printf("\nResult of right side:");
	printf("\n%lf", sumR*h);
	for (int i = 0;i < 10;i++)
	{
		sumM += sumMed[i];
		//printf("%lf+", sumMed[i]);
	}
	printf("\nResult of middle:");
	printf("\n%lf", sumM* h);
}
void trapec(double a, double b)
{
	double h = (b - a) / 100, x = a;
	double sumA[11];
	double sum=0;
	for (int i = 0;i < 11;i++)
	{
		sumA[i]= y(x);
		x += h;
	}
	for (int i = 1;i < 10;i++)
		sum += sumA[i];
	sum += (sumA[0] + sumA[10]) / 2;
	printf("\nResult of trapec:");
	printf("\n%lf", sum * h);
}
void simpson(double a, double b)
{
	double h = (b - a) / 100, x = a;
	double sumA[11];
	double sum = 0;
	for (int i = 0;i < 11;i++)
	{
		sumA[i] = y(x);
		x += h;
	}
	for (int i = 0;i < 10;i++)
	{
		sum += (sumA[i] + 4 * sumA[i + 1] + sumA[i + 2]);
			i++;
	}
	printf("\nResult of Simpson:");
	printf("\n%lf", sum*h/3);
}
int main()
{
	quadro(0,2);
	trapec(0,2);
	simpson(0,2);
	return 0;
}