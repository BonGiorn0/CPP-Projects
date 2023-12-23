#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
#include <list>

template<class T, class U>
void printMap(std::map<T, U> &m){
    for(auto i = m.begin(); i != m.end(); i++)
        std::cout << i->first << " : " << i->second << '\n';

}

int main(){
    std::map<const char *, size_t> color{
        {"red", 0xff0000}, 
        {"green", 0x00ff00},
        {"purple", 0xcc8899}
    };

    std::cout.setf(std::ios_base::dec, std::ios_base::basefield);
    printMap(color);
    std::cout << '\n';
    color["cyan"] = 0x00ffff;
    printMap(color);
    std::cout << '\n';
    color["purple"] = 0x8b008b;
    printMap(color);
    std::cout << '\n';

    auto good = color.find("purple");
    auto bad = color.find("blue");

    std::cout << good->first << ' ' << good->second << '\n';

    std::set<int> s;
    std::list<int> l;
    /*s.insert(3);
    s.insert(5);
    s.insert(6);
    s.insert(-1);
    s.insert(-3);
    s.insert(87);
    s.insert(42);
    */
    /*for(auto i = s.begin(); i != s.end(); i++)
        std::cout << *i << ' ';
    std::cout << '\n';
    */
    std::copy(
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>(), 
        std::inserter(s, s.end())
    );
    std::copy(
        s.begin(),
        s.end(),
        std::back_inserter(l)
    );
    //std::copy(
    //    l.begin(), l.end(), 
    //    std::ostream_iterator<int>(std::cout, " ")
    //);

    auto it = std::remove_if(l.begin(), l.end(), 
                    [](int i){if (i < 2) return true;});

    l.erase(it, l.end());
    int sum = std::accumulate(l.begin(), l.end(), 0);
    

    std::copy(
        l.begin(), l.end(), 
        std::ostream_iterator<int>(std::cout, " ")
    );

    std::cout << sum << '\n';

    return 0;
}