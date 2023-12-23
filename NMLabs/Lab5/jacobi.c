#include <stdio.h>
#include <math.h>

void PrintMatrix(const float *a, int n, int m){
    for(int i = 0; i < n; i++){
		printf("\n");
        for(int j = 0; j < m; j++)
			printf("%f ", a[i * n + j]);
	}
	printf("\n");
}

void CopyMatrix(float *res, const float *a, int n, int m)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
			res[i * n + j] = a[i * n + j];

}


void swap(float *a, float *b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}



void SwapRows(float m[3][4], int i, int j)
{
	for(int k = 0; k < 4; k++)
		swap(&m[i][k], &m[j][k]);
}

void MakeTriangle(float m[3][4])
{
    for(int i = 0; i < 3; i++){
		float max = -99999;
		int maxId = 0;
		for(int j = i; j < 3; j++)
			if(m[j][i] > max){
				max = m[j][i];
				maxId = j;
			}
		SwapRows(m, maxId, i);

        for(int j = i + 1; j < 3; j++){
            float coef = m[j][i] / m[i][i];
			m[j][i] = 0;
            for(int k = i + 1; k < 4; k++)
                m[j][k] -= m[i][k] * coef;
        }
	}
}
float CalculateDeterminant(const float m[3][3])
{
    float res = 1;
	float boo[3][3];
	CopyMatrix(boo, m, 3, 3);
    for(int i = 0; i < 3 - 1; i++)
        for(int j = i + 1; j < 3; j++){
            if (!boo[i][i])
                return 0;
            float coef = boo[j][i] / boo[i][i];
            for(int k = i + 1; k < 3; k++)
                boo[j][k] -= boo[i][k] * coef;
        }
    for(int i = 0; i < 3; i++)
        res *= boo[i][i];
    return res;
}

void MakeAlpha(float *alpha, const float *a, int n, int m)
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(i != j)
				alpha[i * n + j] = -a[i * n + j] / a[i * n + i];
}

void MakeBetha(float *betha, const float *a, int n, int m)
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(i != j)
				betha[i * n + j] = a[i * n + m - 1] / a[i * n + i];
}

void MultMatrix(float *res, const float *a, const float *b, int an, int am, int bn, int bm)
{
	if(an != bm)
		return;
	for(int i = 0; i < an; i++)
        for(int j = 0; j < bm; j++){
            for(int k = 0; k < bn; k++){
                res[i * an + j] += a[i * an + k] * b[k * bn + j];
			}
		}

}

int main()
{
	float m[4][5] = {
		{0.42, -0.32, 0.03, 0.00, -0.44},
		{0.11, -0.46, -0.36, 0.00, 1.42},
		{0.12, 0.08, -0.34, -0.24, -0.83},
		{0.15, -0.35, -0.18, -1.42, -1.22}
	};
	float a[3][3] ={
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	float b[3][3] ={
		{1, 1, 1},
		{2, 2, 2},
		{3, 3, 3}
	};
	float alpha[3][3] = {0};
	float betha[3][1] = {0};
	float X[3][1] = {0};

	MakeAlpha(alpha, m, 4, 5);
	MakeBetha(alpha, m, 4, 5);
	CopyMatrix(X, betha, 4, 5);

	PrintMatrix(X, 3, 1);
	PrintMatrix(betha, 3, 1);
	PrintMatrix(alpha, 4, 4);
	
	return 0;
}
