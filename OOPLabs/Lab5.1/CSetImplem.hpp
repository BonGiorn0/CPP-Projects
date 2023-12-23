#include <algorithm>
#include "CSet.hpp"
#include "Exceptions.hpp"

static const int RESIZE_VALUE = 1;
static const int INPUT_NUMBERS_COUNT = 5;
static const int CHAR_COUNT = 1;

template<class T>
CSet<T>::CSet():
    counter(0), arr(NULL){};

template<class T>
CSet<T>::CSet(const CSet<T> &other){
    counter = other.counter;
    arr = new T[other.counter + other.counter % RESIZE_VALUE];
    for(int i = 0; i < counter; i++){
        arr[i] = other.arr[i];
    }
}

template<class T>
CSet<T>::CSet(CSet<T>&& other){
    std::swap(counter, other.counter);
    std::swap(arr, other.arr);
}

template<class T>
CSet<T>::~CSet(){
    delete [] arr;
}

template<class T>
bool CSet<T>::Has(T val) const{
    for(int i = 0; i < counter; i++){
        if (arr[i] == val)
            return true;
    }
    return false;
}

template<class T>
int comp(const void *x, const void *y){
    if(*(T*)x < *(T*)y)
        return -1;
    if(*(T*)x > *(T*)y)
        return 1;
    return 0;
}

template<class T>
void CSet<T>::Add(T val){
    if(counter % RESIZE_VALUE == 0)
        Resize();
    if (!Has(val)){
        arr[counter] = val;
        counter++;
        qsort(arr, counter, sizeof(T), comp<T>);
    }
}

template<class T>
void CSet<T>::Delete(T val){
    if (arr == NULL)
        throw EmptySet("Delete(int val)");
    if (Has(val)){
        counter--;
        std::swap(arr[GetElementIndex(val)], arr[counter]);
    }
    if((counter + 1) % RESIZE_VALUE == 0)
        this->Resize();
    qsort(arr, counter, sizeof(T), comp<T>);
}

template<class T>
T CSet<T>::MaxValue() const{
    if (arr == NULL){
        throw EmptySet("MaxValue()");
    }
    T max = arr[0];
    for(int i = 0; i < counter; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

template<class T>
T CSet<T>::MinValue() const{
    if (arr == NULL){
        throw EmptySet("MinValue()");
    }
    T min = arr[0];
    for(int i = 0; i < counter; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

template<class T>
size_t CSet<T>::Power() const{
    return counter;
}

template<class T>
std::istream &operator>>(std::istream &in, CSet<T> &b){
    std::cout << "Enter your set(reads until EOF):\n";
    while(!in.eof()){
        T n = 0;
        in >> n;
        if(in.fail()){
            std::cout << InputError().what();
            in.clear();
            in.ignore(CHAR_COUNT, ' ');
        }else{
            b.Add(n);
        }
    }
    return in;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const CSet<T> &b){
    if (b.counter == 0)
        return out << "{}";
    out << "{";
    for(int i = 0; i < b.counter - 1; i++)
        out << b.arr[i] << ", ";
    out << b.arr[b.counter - 1] << "}";
    return out;
}

template<class T>
void CSet<T>::operator=(const CSet<T> &other){
    counter = other.counter;
    arr = new T[counter + counter % RESIZE_VALUE];
    for(int i = 0; i < counter; i++){
        arr[i] = other.arr[i];
    }
}

template<class T>
bool CSet<T>::operator==(const CSet<T> &other){
    return counter == other.counter;
}

template<class T>
bool CSet<T>::operator<(const CSet<T> &other){
    return counter < other.counter;
}

template<class T>
bool CSet<T>::operator>(const CSet<T> &other){
    return counter > other.counter;
}

template<class T>
void CSet<T>::operator=(CSet<T>&& other){
    std::swap(counter, other.counter);
    std::swap(arr, other.arr);
}

template<class T>
CSet<T> CSet<T>::operator+(const CSet<T> &other){
    CSet<T> tmp(*this);
    for(int i = 0; i < other.counter; i++)
        if(!tmp.Has(other.arr[i]))
            tmp.Add(other.arr[i]);
    return tmp;
}

template<class T>
CSet<T> CSet<T>::operator-(const CSet<T> &other){
    CSet<T> tmp;
    for(int i = 0; i < other.counter; i++)
        if(this->Has(other.arr[i]))
            tmp.Add(other.arr[i]);
    return tmp;
}

template<class T>
CSet<T> CSet<T>::operator/(const CSet<T> &other){
    CSet<T> tmp(*this);
    for(int i = 0; i < other.counter; i++)
        if(tmp.Has(other.arr[i]))
            tmp.Delete(other.arr[i]);
    return tmp;
}

template<class T>
unsigned int CSet<T>::GetElementIndex(T val){
    for(int i = 0; i < counter; i++)
        if (arr[i] == val)
            return i;
}

template<class T>
void CSet<T>::Resize(){
    T *p = new T[counter + RESIZE_VALUE];
    for(int i = 0; i < counter; i++)
        p[i] = arr[i];
    delete [] arr;
    arr = p;
}