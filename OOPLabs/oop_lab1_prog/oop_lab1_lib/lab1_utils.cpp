#include <cmath>
#include "lab1_utils.h"
int g_iNumberOfCalls_03 = 0;
int GetNumberOfArgumentsByArgc_03(int argc)
{
    ++g_iNumberOfCalls_03;
    return argc - 1;
}
static bool IsTriangleValid_03(double sideA, double sideB, double sideC)
{
    const bool cbRes =
        (sideA > (sideB + sideC)) && (sideB > (sideA + sideC)) && (sideC > (sideA + sideB));
    return cbRes;
}
double GetTriangleAreaByHeron_03(double sideA, double sideB, double sideC)
{
    ++g_iNumberOfCalls_03;
    double dRes = NAN;
    if (IsTriangleValid_03(sideA, sideB, sideC))
    {
        const double cbSemiP = (sideA + sideB + sideC) * 0.5;
        dRes = sqrt(cbSemiP * (cbSemiP - sideA) * (cbSemiP - sideB) * (cbSemiP - sideC));
    }
    return dRes;
}