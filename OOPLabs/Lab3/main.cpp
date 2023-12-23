#include <stdio.h>
#include <climits>

#include "BigNumber.h"

int main()
{
	long long h, h1, l, l1;
	CBigNumber a, a1, b(2, -2);
	a = b -  CBigNumber(2, LLONG_MAX);
	a1 = b - LLONG_MAX;
	a.getNum(h, l);
	a1.getNum(h1, l1);
	printf("%lld %lld\n", h, l);
	printf("%lld %lld\n", h1, l1);
	printf("%lld \n", 0 - LLONG_MAX);

	return 0;
}
