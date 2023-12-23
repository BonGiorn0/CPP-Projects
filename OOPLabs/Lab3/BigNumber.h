
class CBigNumber{
	long long upper;
	long long lower;
public:
	CBigNumber();
	CBigNumber(const long long &rhs);
	CBigNumber(const long long &upper_rhs, const long long &lower_rhs);
		
	void setNum(const long long &upper, const long long &lower);
	void getNum(long long &upper, long long &lower) const;

	CBigNumber operator+(const CBigNumber &rhs) const;
	CBigNumber operator-(const CBigNumber &rhs) const;
    
};