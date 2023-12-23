#include "Exceptions.hpp"
#include "CBigNumber.hpp"

#ifdef UNIQUE 
#include "CSetUnique.hpp"
#else
#include "CSetImplem.hpp"
#endif


int main(int argc, char *argv[]){
try{
    CSet<CSet<int> > ss;
    CSet<int> a, b, c;

    //a.MinValue();
    //a.MaxValue();
    //a.Delete(3);

    a.Add(5);
    a.Add(3);
    a.Add(1);
    a.Add(4);
    a.Add(96);
    a.Add(104);

    b.Add(1);
    b.Add(34);
    b.Add(42);
    b.Add(69);

    ss.Add(a);
    ss.Add(b);



    //std::ifstream &in = static_cast<std::ifstream &>(std::cin);
    std::ifstream in("input.txt");
    //in.open(argv[1]);
    if(!in)
        throw NoFileFound(argv[1]);
    in >> c;
    std::cout << a << "\n";
    std::cout << b << "\n";
    std::cout << c << "\n";

    std::cout << "\n" << ss.MaxValue() << "\n\n";

    c = a + b;
    std::cout << c << "\n";
    c = a - b;
    std::cout << c << "\n";
    c = b / a;
    std::cout << c << "\n";
    c = a / b;
    std::cout << c << "\n";

    return 0;

}catch(std::bad_alloc &exc){
    std::cout << exc.what();

}catch(const InputError &exc){
    std::cout << exc.what();

}catch(const EmptySet &exc){
    std::cout << exc.what() << " : " << exc.getMethodName() << '\n';

}catch(const NoFileFound &exc){
    std::cout << exc.what() << " : " << exc.getFileName() << '\n';

}catch(const std::exception &exc){
    std::cout << "Standart error\n";
    std::cout << exc.what();


}catch(...){
    std::cout << "Unknown error\n";
};
    return 1;
}