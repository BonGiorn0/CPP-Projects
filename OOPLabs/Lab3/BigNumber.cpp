#include "BigNumber.h"
#include <climits>

CBigNumber::CBigNumber() : upper(0), lower(0){};
CBigNumber::CBigNumber(const long long &rhs) : upper(0), lower(rhs){};
CBigNumber::CBigNumber(const long long &upper_rhs, const long long &lower_rhs) 
    : upper(upper_rhs), lower(lower_rhs){};

CBigNumber CBigNumber::operator+(const CBigNumber &rhs) const{
    long long tmp = lower + rhs.lower;
    return CBigNumber(upper + rhs.upper + (tmp < lower),
                        -(LLONG_MAX + 1) * (tmp < lower) + lower + rhs.lower);
}
/*CBigNumber CBigNumber::operator+(const long long &rhs) const{
		long long tmp = lower + rhs;
		return CBigNumber(upper + (tmp < lower), 
							-(LLONG_MAX + 1) * (tmp < lower) + lower + rhs);
	}*/
CBigNumber CBigNumber::operator-(const CBigNumber &rhs) const{
		long long tmp = lower - rhs.lower;
		return CBigNumber(upper - rhs.upper - (tmp > lower) , 
							(LLONG_MAX) * (tmp > lower) + lower - rhs.lower + 2 *(tmp > lower));
	}
/*CBigNumber CBigNumber::operator-(const long long &rhs) const{
		long long tmp = lower - rhs;
		return CBigNumber(upper - (tmp > lower), 
							(LLONG_MAX) * (tmp > lower) + lower - rhs + 2 *(tmp > lower));
	}*/
void CBigNumber::setNum(const long long &u, const long long &l){
    upper = u;
    lower = l;
    
}

void CBigNumber::getNum(long long &u, long long &l) const{
		u = upper;
		l = lower;
	}
