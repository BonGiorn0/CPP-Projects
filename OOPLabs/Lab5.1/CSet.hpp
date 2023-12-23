#include <fstream>
#include <iostream>

template<class T>
class CSet{
public:
    CSet();
    CSet(const CSet<T> &other);
    CSet(CSet<T>&& other);
    ~CSet();

    bool Has(T val) const;
    size_t  Power() const;
    T  MaxValue() const;
    T  MinValue() const;
    void Add(T val);
    void Delete(T val);

    void operator=(const CSet<T> &other);
    void operator=(CSet<T> &&other);
    bool operator==(const CSet<T> &other);
    bool operator<(const CSet<T> &other);
    bool operator>(const CSet<T> &other);
    CSet<T> operator+(const CSet<T> &other);
    CSet<T> operator-(const CSet<T> &other);
    CSet<T> operator/(const CSet<T> &other);
    
    template<class U>
    friend std::istream &operator>>(std::istream &in, CSet<U> &b);
    template<class U>
    friend std::ostream &operator<<(std::ostream &out, const CSet<U> &b);
private:
    int counter;
    T *arr = NULL;
    void Resize();
    unsigned int GetElementIndex(T val);
};