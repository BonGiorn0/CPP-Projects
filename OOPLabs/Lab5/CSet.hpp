#include <iostream>

class CSet{
public:
    CSet();
    CSet(const CSet &other);
    CSet(CSet&& other);
    ~CSet();

    bool Has(int val) const;
    int  Power() const;
    int  MaxValue() const;
    int  MinValue() const;
    void Print() const;
    void Add(int val);
    void Delete(int val);

    void operator=(const CSet &other);
    void operator=(CSet &&other);
    CSet operator+(const CSet &other);
    CSet operator-(const CSet &other);
    CSet operator/(const CSet &other);
    friend std::istream &operator>>(std::istream &in, CSet &b);
    friend std::ostream &operator<<(std::ostream &out, const CSet &b);
private:
    int counter = 0;
    int *arr = NULL;
    void Resize();
    unsigned int GetElementIndex(int val);
};