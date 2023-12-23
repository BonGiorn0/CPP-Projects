#include <climits>

#include "BigNumber.h"

int main()
{
	CBigNumber a0, a, a1, b(2, 0);
	std::cin >> a0;
	a0 = a;
	a = b + CBigNumber(2, ULLONG_MAX);
	a1 = b - ULLONG_MAX - 2;
	std::cout << a0 << '\n';
	std::cout << a  << '\n';
	std::cout << a1 << '\n';
	std::cout << (b > a1) << '\n';
	std::cout << (b < a1) << '\n';
	std::cout << (b > a ) << '\n';
	std::cout << (b < a ) << '\n';
	std::cout << (b > a0) << '\n';
	std::cout << (b < a0) << '\n';
	std::cout << (b == a0) << '\n';
	std::cout << -0xfffffffffffffff << '\n';


	return 0;
}
