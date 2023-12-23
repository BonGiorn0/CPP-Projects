#include <iostream>
#include <fstream>
#include <memory>

#include "Deposit.hpp"

int main(){
    std::unique_ptr<Deposit> arr[3];
    arr[0] = std::unique_ptr<Deposit>(new FixedDeposit());
    arr[1] = std::unique_ptr<Deposit>(new AccumulativeDeposit());
    arr[2] = std::unique_ptr<Deposit>(new VIPDeposit());

    for(int i = 0; i < 3; i++){
        arr[i]->setFirstInstallment(1000);
        arr[i]->setRate(18);
        arr[i]->setTerm(12);
    }


    std::ofstream file("out.txt");
    for(int i = 0; i < 3; i++){
        arr[i]->PrintName(file);
        file << ":\n";
        if(arr[i]->isValid()){
            file << arr[i]->EndTermIncome() <<     '\n';
            file << arr[i]->ChosenTimeIncome(6) << '\n';
        }else{
            file << "Setted data is not correct\n";
        }
    }
    file.close();

    return 0;
}