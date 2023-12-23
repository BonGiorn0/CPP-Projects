#include <stdio.h>

void PrintMatrix(float m[3][3]){
    for(int i = 0; i < 3; i++){
		printf("\n");
        for(int j = 0; j < 3; j++)
			printf("%f ", m[i][j]);
	}
	printf("\n");
}


void MakeDelta(int n, float res[3][3], float m[3][3], float ans[3])
{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			if(j == n)
				res[i][j] = ans[i];
			else
				res[i][j] = m[i][j];
		}
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


int main()
{
	float m[3][3] = {
		{3.75, -0.28, 0.17},
		{2.11, -0.11, -0.12},
		{0.22, -3.17, 1.81}
	};
	float ans[3] = {0.75, 1.11, 0.05};

	float d1[3][3], d2[3][3], d3[3][3];

	MakeDelta(0, d1, m, ans);
	MakeDelta(1, d2, m, ans);
	MakeDelta(2, d3, m, ans);

	PrintMatrix(d1);
	PrintMatrix(d2);
	PrintMatrix(d3);

	printf("\n./");
	printf("%f\n", CalculateDeterminant(d1) / CalculateDeterminant(m));
	printf("%f\n", CalculateDeterminant(d2) / CalculateDeterminant(m));
	printf("%f\n", CalculateDeterminant(d3) / CalculateDeterminant(m));


	return 0;
}
