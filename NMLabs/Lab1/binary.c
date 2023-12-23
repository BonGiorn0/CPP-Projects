#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float f(float x)
{
	return x*x*x - 3*x*x + 6*x + 3;
}

float Binary(float a, float b, float e)
{
	if(f(a) * f(b) > 0){
		printf("There's no roots.\n");
		exit(0);
	}

	float x;
	int n = (int)(log(fabs((b - a) / e - 1)) / log(2));
	for(int i = 0; i < n; i++){
		x = (a + b) / 2;
		if(f(a) * f(x) > 0)
			a = x;
		if(f(b) * f(x) > 0)
			b = x;
	}
	return x;
}

int main(int argc, char *argv[])
{
	float a = atof(argv[1]);
	float b = atof(argv[2]);
	float e = atof(argv[3]);
	printf("%f\n", Binary(a, b, e));
	return 0;
}
