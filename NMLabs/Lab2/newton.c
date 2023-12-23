#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x)
{
	return x*x*x - 3*x*x + 6*x + 3;
}

double df(double x)
{
	return 3*x*x - 6*x + 6;
}

double d2f(double x)
{
	return 6*x - 6;
}

double Newton(double a, double b, double e)
{
	if(f(a) * f(b) > 0){
		printf("There's no roots.\n");
		exit(0);
	}

	if(df(a) * d2f(a) > 0){
		double tmp = a;
		a = b;
		b = tmp;
	}

	double x1, x = a;
	do{
		x1 = f(x) / df(x); 
		x -= x1;
		//printf("%f %f %f\n", x, x1, x1 - x);
	}while(fabs(x1) > e);
	return x;
}

int main(int argc, char *argv[])
{
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	double e = atof(argv[3]);
	printf("%f\n", Newton(a, b, e));
	return 0;
}
