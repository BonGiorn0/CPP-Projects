#include <cmath>
#include <string>
#include <cstdio>
#include <iostream>
#include <unistd.h>

#include "function.h"

float function(float x)
{
	return (x + x*x + x*x*x) / cos(x);
}

void tabulateFunction(FILE *f, float a, float step, size_t iterationCount)
{
	for (size_t i = 0; i < iterationCount; i++) {
		//std::cout << "| " << i << " | " << a << " | " << function(a) << " |\n";
		fprintf(f, "| %5u | %.5f | % 10.5f |\n", getpid(), a, function(a));
		a += step;
	}
}
