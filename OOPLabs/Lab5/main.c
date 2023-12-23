#include <utility>
#if 0
#include "CSetUnique.hpp"
#else
#include "CSet.hpp"
#endif

int main(){
    CSet *a = new CSet,
         *b = new CSet;

    a->Add(5);
    a->Add(3);
    a->Add(1);
    a->Add(4);
    a->Add(96);
    a->Add(104);

    b->Add(1);
    b->Add(34);
    b->Add(42);
    b->Add(69);

    CSet *c = new CSet;
    std::cin >> *c;
    std::cout << *a << "\n";
    std::cout << *b << "\n";
    std::cout << *c << "\n";

    *c = *a + *b;
    std::cout << *c << "\n";
    *c = *a - *b;
    std::cout << *c << "\n";
    *c = *b / *a;
    std::cout << *c << "\n";
    *c = *a / *b;
    std::cout << *c << "\n";

    delete a;
    delete b;
    delete c;
}