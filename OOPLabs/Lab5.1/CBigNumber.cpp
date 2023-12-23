#include "CBigNumber.hpp"

CBigNumber::CBigNumber() : upper(0), lower(0){}
CBigNumber::CBigNumber(const CBigNumber &rhs){
	upper = rhs.upper;
	lower = rhs.lower;
}
CBigNumber::CBigNumber(const unsigned long long &rhs) : upper(0), lower(rhs){};
CBigNumber::CBigNumber(const long long &upper_rhs, const unsigned long long &lower_rhs) 
    : upper(upper_rhs), lower(lower_rhs){}

void CBigNumber::setNum(const long long &u, const unsigned long long &l){
    upper = u;
    lower = l;
}

void CBigNumber::setNum(const unsigned long long &l){
    upper = 0;
    lower = l;
}
void CBigNumber::getNum(long long &u, unsigned long long &l) const{
	u = upper;
	l = lower;
}
void CBigNumber::operator=(const CBigNumber &rhs){
	upper = rhs.upper;
	lower = rhs.lower;
}

CBigNumber CBigNumber::operator+(const CBigNumber &rhs){
    unsigned long long tmp = lower + rhs.lower;
    return CBigNumber(upper + rhs.upper + (tmp < rhs.lower), tmp);
}

CBigNumber CBigNumber::operator+(const unsigned long long &rhs){
    unsigned long long tmp = lower + rhs;
    return CBigNumber(upper  + (tmp < rhs), tmp);
}

CBigNumber CBigNumber::operator-(const CBigNumber &rhs){
	unsigned long long tmp = lower - rhs.lower;
	return CBigNumber(upper - rhs.upper - (tmp > rhs.lower) , tmp);
}

CBigNumber CBigNumber::operator-(const unsigned long long &rhs){
    unsigned long long tmp = lower - rhs;
    return CBigNumber(upper - (tmp > rhs), tmp);
}

bool operator>(const CBigNumber &lhs, const CBigNumber &rhs){
	if(lhs.upper == rhs.upper)
		return (lhs.lower > rhs.lower);
	return (lhs.upper > rhs.upper);
}

bool operator<(const CBigNumber &lhs, const CBigNumber &rhs){
	if(lhs.upper == rhs.upper)
		return (lhs.lower < rhs.lower);
	return (lhs.upper < rhs.upper);
}
bool operator==(const CBigNumber &lhs, const CBigNumber &rhs){
	return(lhs.upper == rhs.upper && lhs.lower == rhs.lower);
}

std::istream &operator>>(std::istream &in, CBigNumber &rhs){
	in >> rhs.upper >> rhs.lower;
	return in;
}

std::ostream &operator<<(std::ostream &out, const CBigNumber &rhs){
	out << rhs.upper << rhs.lower;
	return out;
}