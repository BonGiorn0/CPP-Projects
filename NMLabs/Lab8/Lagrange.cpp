#include <stdio.h>

struct Point{
    double x, y;
};

void PrintArr(double arr[], size_t size){
    for (size_t i = 0; i < size; i++)
        printf("%f ", arr[i]);
}

void Polynom(double res[], double arr[], size_t size){
    for (size_t i = size; i > 0; i--){
        for (size_t j =  i; j < size + 1; j++){
            double tmp = (j == size) ? 0 : res[j + 1];
            res[j] = -1 * res[j] * arr[size - i] + tmp;
            //PrintArr(res, size + 1);
            //printf("\n");
        }
    }
}

void LagrangePolynom(double res[], Point f[], size_t size){
    double *arr = new double[size - 1];
    for (size_t i = 0; i < size; i++){

        double divider = 1;
        size_t counter = 0;
        for (size_t j = 0; j < size; j++){
            if (f[j].x == f[i].x) 
                continue;
            arr[counter] = f[j].x;
            divider *= f[i].x - f[j].x;
            counter++;

        }
        //PrintArr(arr, 2);
        //printf("y: %f div : %f \n", f[i].y, divider);

        double coef[3] = {1, 1, 1};
        Polynom(coef, arr, size - 1);
        //PrintArr(coef, 3);
        //printf("\n");
        for (size_t j = 0; j < size; j++){
            coef[j] *= f[i].y / divider;
            res[j] += coef[j];
        }

        //PrintArr(res, 3);
        //printf("\n");
    }
}

double LagrangePoint(Point f[], double x, size_t size){
    double res = 0;
    for (size_t i = 0; i < size; i++){
        double numer = f[i].y;
        double denom = 1;
        for (size_t j = 0; j < size; j++){
            if (f[j].x == f[i].x) 
                continue;
            numer *= x - f[j].x;
            denom *= f[i].x - f[j].x;

        }
        res += numer / denom;
    }
    return res;
}

int main(){
    double res[3] = {0};
    Point test[3] = {
        {1, 10},
        {2, 15},
        {3, 12}
    };
    Point arr[10] = {};

    //Polynom(res, test, 3);
    LagrangePolynom(res, test, 3);
    double a = LagrangePoint(test, 2, 3);
    PrintArr(res, 3);
    printf("%f\n", a);
    return 0;
}