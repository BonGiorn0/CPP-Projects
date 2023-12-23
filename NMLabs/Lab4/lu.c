#include <stdio.h>
#include <math.h>

void PrintMatrix(const float m[3][3]){
    for(int i = 0; i < 3; i++){
		printf("\n");
        for(int j = 0; j < 3; j++)
			printf("%f ", m[i][j]);
	}
	printf("\n");
}

void CopyMatrix(float res[3][3], const float m[3][3])
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
			res[i][j] = m[i][j];

}

float CalculateDeterminant(const float m[3][3])
{
    float res = 1;
	float boo[3][3];
	CopyMatrix(boo, m);
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


void MultMatrix(float res[3][3], const float a[3][3], const float b[3][3], int n, int m)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++){
            for(int k = 0; k < n; k++){
                res[i][j] += a[i][k] * b[k][j];
			}
		}

}
void LUDecompose(float l[3][3], float u[3][3], const float m[3][3], int size)
{
	for(int k = 0; k < size; k++)
		for(int i = k, j = k + 1; i < size; i++, (j < size - 1) ? j++ : j){
			float sum = 0;
			for(int m = 0; m < k; m++)
				sum += l[i][m] * u[m][k];
			l[i][k] = m[i][k] - sum;
			u[k][k] = 1;
			sum = 0;
			for(int m = 0; m < k; m++)
				sum += l[k][m] * u[m][j];
			u[k][j] = (m[k][j] - sum) / l[k][k];
	}

}
void SolveInorder(float res[3], const float ans[3], const float l[3][3])
{
	for(int i = 0; i < 3; i++){
		float sum = 0;
		for(int m = 0; m < i; m++)
			sum += l[i][m] * res[m];
		res[i] =  (ans[i] - sum) / l[i][i];
	}

}

void SolveReverse(float res[3], const float ans[3], const float u[3][3])
{
	for(int i = 2; i >= 0; i--){
		float sum = 0;
		for(int m = 2; m > i; m--)
			sum += u[i][m] * res[m];
		res[i] =  ans[i] - sum;
	}

}




int main()
{
	float m[3][3] = {
		{3.75, -0.28, 0.17},
		{2.11, -0.11, -0.12},
		{0.22, -3.17, 1.81}
	};
	float ans[3] = {0.75, 1.11, 0.05};
	float res1[3] = {0};
	float res2[3] = {0};
	float L[3][3] = {0};
	float U[3][3] = {0};
	float X[3][3] = {0};

	LUDecompose(L, U, m, 3);
	MultMatrix(X, L, U, 3, 3);
	SolveInorder(res1, ans, L);
	SolveReverse(res2, res1, U);

	PrintMatrix(L);
	PrintMatrix(U);
	//PrintMatrix(X);
	printf("\n%f %f %f\n", res1[0], res1[1], res1[2]);
	printf("\n%f %f %f\n", res2[0], res2[1], res2[2]);




	return 0;
}
