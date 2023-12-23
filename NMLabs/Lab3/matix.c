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

float Minor(int n, int m, const float mx[3][3])
{
	float a[4];
	int boo = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
			if(i == n || j == m)
				continue;
			a[boo] = mx[i][j];
			boo++;
		}
	}
	return pow(-1, n + m) * (a[0] * a[3] - a[1] * a[2]);

}

void MakeInverse(float res[3][3], const float m[3][3])
{
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
			res[j][i] = Minor(i, j, m);
		}
	}

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
			res[i][j] *= 1.f / CalculateDeterminant(m);
}

void MultMatrix(float res[3][1], const float a[3][3], const float b[3][1], int size)
{
    for(int i = 0; i < size; i++)
        for(int j = 0; j < 1; j++){
            for(int k = 0; k < size; k++){
                res[i][j] += a[i][k] * b[k][j];
			}
		}

}


int main()
{
	float m[3][3] = {
		{3.75, -0.28, 0.17},
		{2.11, -0.11, -0.12},
		{0.22, -3.17, 1.81}
	};
	float ans[3][1] = {
		{0.75}, 
		{1.11}, 
		{0.05}
	};
	float inv[3][3];
	float res[3][1] = {0};

	MakeInverse(inv, m);
	MultMatrix(res, inv, ans, 3);

	PrintMatrix(inv);
	//printf("%f\n", Minor(0,0,m));
	//printf("%f\n", CalculateDeterminant(m));
	printf("\n%f %f %f\n", res[0][0], res[1][0], res[2][0]);


	return 0;
}
