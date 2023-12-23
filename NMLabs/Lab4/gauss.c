#include <stdio.h>
#include <math.h>

void PrintMatrix(const float m[3][4]){
    for(int i = 0; i < 3; i++){
		printf("\n");
        for(int j = 0; j < 4; j++)
			printf("%f ", m[i][j]);
	}
	printf("\n");
}

void CopyMatrix(float res[3][4], const float m[3][4])
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 4; j++)
			res[i][j] = m[i][j];

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
void Solve(float res[3], const float ans[3], const float u[3][4])
{
	for(int i = 2; i >= 0; i--){
		float sum = 0;
		for(int m = 3; m > i; m--)
			sum += u[i][m] * res[m];
		res[i] =  (u[i][3] - sum) / u[i][i];
	}


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

int main()
{
	float m[3][4] = {
		{3.75, -0.28, 0.17, 0.75},
		{2.11, -0.11, -0.12, 1.11},
		{0.22, -3.17, 1.81, 0.05}
	};
	float ans[3] = {0.75, 1.11, 0.05};
	float res1[3] = {0};
	float res2[3] = {0};
	float L[3][4] = {0};
	float U[3][3] = {0};
	float X[3][3] = {0};

	CopyMatrix(L, m);
	MakeTriangle(L);
	Solve(res1, ans, L);
	

	PrintMatrix(L);
	printf("\n%f %f %f\n", res1[0], res1[1], res1[2]);

	return 0;
}
