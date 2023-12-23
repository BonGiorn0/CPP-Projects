#include <algorithm>
#include "CSetUnique.hpp"

static const int RESIZE_VALUE = 5;

CSet::CSet():
    counter(0), arr(nullptr){};

CSet::CSet(const CSet &other){
    counter = other.counter;
    arr = std::unique_ptr<int[]>(new int[counter + counter % RESIZE_VALUE]);
    for(int i = 0; i < counter; i++){
        arr[i] = other.arr[i];
    }
}

CSet::CSet(CSet&& other){
    std::swap(counter, other.counter);
    std::swap(arr, other.arr);
}


bool CSet::Has(int val) const{
    for(int i = 0; i < counter; i++){
        if (arr[i] == val)
            return true;
    }
    return false;
}

int comp(const void *x, const void *y){
    if(*(int*)x < *(int*)y)
        return -1;
    if(*(int*)x > *(int*)y)
        return 1;
    return 0;
}

void bubbleSort(std::unique_ptr<int[]> &arr, int size){
    for(int i = 0; i < size; i++)
        for(int j = i; j < size; j++)
            if(arr[i] > arr[j])
                std::swap(arr[i], arr[j ]);
}

void CSet::Add(int val){
    if(counter % RESIZE_VALUE == 0)
        Resize();
    if (!Has(val)){
        arr[counter] = val;
        counter++;
        bubbleSort(arr, counter);
    }
}

void CSet::Delete(int val){
    if (Has(val)){
        counter--;
        std::swap(arr[GetElementIndex(val)], arr[counter]);
    }
    if((counter + 1) % RESIZE_VALUE == 0)
        this->Resize();
    bubbleSort(arr, counter);
}

int  CSet::MaxValue() const{
    if (arr == NULL){
        std::cout << "Error: Cannot find max value in empty set." << "\n";
        exit(1);
    }
    int max = arr[0];
    for(int i = 0; i < counter; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int CSet::MinValue() const{
    if (arr == NULL){
        std::cout << "Error: Cannot find min value in empty set." << "\n";
        exit(1);
    }
    int min = arr[0];
    for(int i = 0; i < counter; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
};

int CSet::Power() const{
    return counter;
}

std::istream &operator>>(std::istream &in, CSet &b){
    int i = 5;
    do{
        int n;
        in >> n;
        b.Add(n);
        i--;
    }while(i > 0);
    return in;
}

std::ostream &operator<<(std::ostream &out, const CSet &b){
    if (b.counter == 0)
        return out << "{}";
    out << "{";
    for(int i = 0; i < b.counter - 1; i++)
        out << b.arr[i] << ", ";
    out << b.arr[b.counter - 1] << "}";
    return out;
}

void CSet::operator=(const CSet &other){
    counter = other.counter;
    arr = std::unique_ptr<int[]>(new int[counter + counter % RESIZE_VALUE]);
    for(int i = 0; i < counter; i++){
        arr[i] = other.arr[i];
    }
}

void CSet::operator=(CSet&& other){
    std::swap(counter, other.counter);
    std::swap(arr, other.arr);
}

CSet CSet::operator+(const CSet &other){
    CSet tmp(*this);
    for(int i = 0; i < other.counter; i++)
        if(!tmp.Has(other.arr[i]))
            tmp.Add(other.arr[i]);
    return tmp;
}

CSet CSet::operator-(const CSet &other){
    CSet tmp;
    for(int i = 0; i < other.counter; i++)
        if(this->Has(other.arr[i]))
            tmp.Add(other.arr[i]);
    return tmp;
}

CSet CSet::operator/(const CSet &other){
    CSet tmp(*this);
    for(int i = 0; i < other.counter; i++)
        if(tmp.Has(other.arr[i]))
            tmp.Delete(other.arr[i]);
    return tmp;
}

unsigned int CSet::GetElementIndex(int val){
    for(int i = 0; i < counter; i++)
        if (arr[i] == val)
            return i;
}

void CSet::Resize(){
    std::unique_ptr<int[]> p(new int [counter + RESIZE_VALUE]);
    for(int i = 0; i < counter; i++)
        p[i] = arr[i];
    arr = std::move(p);
}