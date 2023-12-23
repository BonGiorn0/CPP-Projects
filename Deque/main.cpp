#include "ListImplem.hpp"
#include "Deposit.hpp"

int main()
{
	List<List<Deposit *> > doubleList;
	List<Deposit *> a, b, tmp;

	a.push_front(new FixedDeposit());
	a.push_front(new AccumulativeDeposit());
	a.push_front(new VIPDeposit());

	b.push_front(new FixedDeposit());
	b.push_front(new AccumulativeDeposit());
	b.push_front(new VIPDeposit());

    doubleList.push_back(a);
    doubleList.push_back(b);
    doubleList.push_back(b);

	tmp = doubleList.pop_front();
	while(!tmp.isEmpty()){
		Deposit *x = tmp.pop_front();
		x->setFirstInstallment(1000);
		x->setRate(3);
		x->setTerm(24);

		x->PrintName(std::cout);
		std::cout << ":\n";
		std::cout << x->EndTermIncome() << '\n';		
		std::cout << x->ChosenTimeIncome(12) << '\n';		
	}

	return 0;
}