#include <iostream>
#include <fstream>
#include <cmath>

#include "Deposit.hpp"

Deposit::Deposit() :
    rate(7), term(7), installment(7){};

void Deposit::setRate(double val){
    if(val >= MINIMAL_RATE){
        rate = val;
    }else{
        std::cout << "Minimal rate is 3 percent!\n";
        exit(1);
    }
}
Deposit::~Deposit(){};

bool Deposit::isValid() const{
    return rate != 0 && term != 0 && installment != 0;
}

void Deposit::setTerm(unsigned int val){
    if(val >= MINIMAL_TERM){
        term = val;
    }else{
        std::cout << "Minimal term is 1 month!\n";
        exit(1);
    }
}


void Deposit::setFirstInstallment(double val){
    if(val >= MINIMAL_FIRST_INSTALLMENT){
        installment = val;
    }else{
        std::cout << "Minimal first installlment is 1000 UAH!\n";
        exit(1);
    }
}

FixedDeposit::FixedDeposit(){}
//    Deposit(){};

FixedDeposit::~FixedDeposit(){};

void FixedDeposit::PrintName(std::ostream &file) const{
    file << "FixedDeposit";
}

double FixedDeposit::EndTermIncome() const{
    return installment + installment * (rate / 100 * (double)term / 12);
}

double FixedDeposit::ChosenTimeIncome(unsigned int val) const{
    return installment + installment * (rate / 100 * (double)val / 12);
}


AccumulativeDeposit::AccumulativeDeposit() :
    Deposit(){};

AccumulativeDeposit::~AccumulativeDeposit(){};

void AccumulativeDeposit::PrintName(std::ostream &file) const{
    file << "AccumulativeDeposit";
}

double AccumulativeDeposit::ChosenTimeIncome(unsigned int val) const{
    return installment * 
        pow(1 + (rate / 100), (double)val / 12 * capitalizationRate);
}
double AccumulativeDeposit::EndTermIncome() const{
    return installment * 
        pow(1 + (rate / 100), (double)term / 12 * capitalizationRate);
}

VIPDeposit::VIPDeposit() :
    Deposit(){};

VIPDeposit::~VIPDeposit(){};

void VIPDeposit::PrintName(std::ostream &file) const{
    file << "VIPDeposit";
}

void VIPDeposit::raiseInstallment(unsigned int val){
    installment += val;
    rate *= rateIncreaseCoef;
}

double VIPDeposit::ChosenTimeIncome(unsigned int val) const{
    return installment * 
        pow(1 + (rate / 100), (double)val / 12 * capitalizationRate);
}
double VIPDeposit::EndTermIncome() const{
    return installment * 
        pow(1 + (rate / 100), (double)term / 12 * capitalizationRate);

}