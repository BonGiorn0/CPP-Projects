#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float f(float x)
{
	return x*x*x - 3*x*x + 6*x + 3;
}

float Hords(float a, float b, float e)
{
	if(f(a) * f(b) > 0){
		printf("There's no roots.\n");
		exit(0);
	}

	float x1, x = a;
	do{
		x1 = x; 
		x = x1 - (f(x1) * (b - x1) / (f(b) - f(x1)));
		//printf("%f\n", x);
	}while(fabs(x1 - x) > e);
	return x;
}

int main(int argc, char *argv[])
{
	float a = atof(argv[1]);
	float b = atof(argv[2]);
	float e = atof(argv[3]);
	printf("%f\n", Hords(a, b, e));
	return 0;
}
