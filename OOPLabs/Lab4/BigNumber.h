#include <iostream>

class CBigNumber{
	long long upper;
	unsigned long long lower;
public:
	CBigNumber();
	explicit CBigNumber(const unsigned long long &rhs);
	CBigNumber(const long long &upper_rhs, const unsigned long long &lower_rhs);

	void setNum(const long long &upper, const unsigned long long &lower);
	void setNum(const unsigned long long &lower);
	void getNum(long long &upper, unsigned long long &lower) const;

	CBigNumber operator+(const CBigNumber &rhs);
	CBigNumber operator+(const unsigned long long &rhs);
	CBigNumber operator-(const CBigNumber &rhs);
	CBigNumber operator-(const unsigned long long &rhs);


	friend bool operator> (const CBigNumber &lhs, const CBigNumber &rhs);
	friend bool operator< (const CBigNumber &lhs, const CBigNumber &rhs);
	friend bool operator==(const CBigNumber &lhs, const CBigNumber &rhs);

	friend std::istream &operator>>(std::istream &out, CBigNumber &rhs);
	friend std::ostream &operator<<(std::ostream &out, const CBigNumber &rhs);
};