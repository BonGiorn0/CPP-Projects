#include <algorithm>
#include "CSet.hpp"
#include "Exceptions.hpp"

static const int RESIZE_VALUE = 5;
static const int INPUT_NUMBERS_COUNT = 5;
static const int CHAR_COUNT = 1;

template<class T>
CSet<T>::CSet(){}

template<class T>
CSet<T>::CSet(const CSet<T> &other){
    arr = other.arr;
}

template<class T>
CSet<T>::CSet(CSet<T>&& other){
    std::swap(arr, other.arr);
}

template<class T>
CSet<T>::~CSet(){}

template<class T>
bool CSet<T>::Has(T val) const{
    return std::binary_search(arr.begin(), arr.end(), val);
}

template<class T>
void CSet<T>::Add(T val){
    if (!Has(val)){
        arr.push_back(val);
        std::sort(arr.begin(), arr.end(), std::less<T>());
    }
}

template<class T>
void CSet<T>::Delete(T val){
    if (arr.empty())
        throw EmptySet("Delete(int val)");
    if (Has(val))
        arr.erase(std::find(arr.begin(), arr.end(), val));
}

template<class T>
T CSet<T>::MaxValue() const{
    if (arr.empty())
        throw EmptySet("MaxValue()");
    return arr.front();
}

template<class T>
T CSet<T>::MinValue() const{
    if (arr.empty())
        throw EmptySet("MinValue()");
    return arr.back();
}

template<class T>
size_t CSet<T>::Power() const{
    return arr.size();
}

template<class T>
std::istream &operator>>(std::istream &in, CSet<T> &other){
    std::cout << "Enter your set(reads until EOF):\n";
    while(!in.eof()){
        T n = 0;
        in >> n;
        if(in.fail()){
            std::cout << InputError().what();
            in.clear();
            in.ignore(CHAR_COUNT, ' ');
        }else{
            other.Add(n);
        }
    }
    return in;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const CSet<T> &other){
    if (other.arr.empty())
        return out << "{}";
    out << "{";
    for(auto i = other.arr.begin(); i != --(other.arr.end()); i++)
        out << *i << ", ";
    out << *(--other.arr.end()) << "}";
    return out;
}

template<class T>
void CSet<T>::operator=(const CSet<T> &other){
    arr = other.arr;
}

template<class T>
void CSet<T>::operator=(CSet<T>&& other){
    std::swap(arr, other.arr);
}

template<class T>
CSet<T> CSet<T>::operator+(const CSet<T> &other){
    CSet<T> tmp;
    std::set_union(
        arr.begin(), arr.end(),
        other.arr.begin(), other.arr.end(),
        std::back_inserter(tmp.arr)
    );
    return tmp;
}

template<class T>
CSet<T> CSet<T>::operator-(const CSet<T> &other){
    CSet<T> tmp;
    std::set_intersection(
        arr.begin(), arr.end(),
        other.arr.begin(), other.arr.end(),
        std::back_inserter(tmp.arr)
    );
    return tmp;
}

template<class T>
CSet<T> CSet<T>::operator/(const CSet<T> &other){
    CSet<T> tmp;
    std::set_difference(
        arr.begin(), arr.end(),
        other.arr.begin(), other.arr.end(),
        std::back_inserter(tmp.arr)
    );
    return tmp;
}