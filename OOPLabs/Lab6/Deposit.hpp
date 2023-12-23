const int MINIMAL_TERM = 1;
const double MINIMAL_RATE = 3.0;
const int MINIMAL_FIRST_INSTALLMENT = 1000;

class Deposit{
public:
    Deposit();
    ~Deposit();

    bool isValid() const;
    void setRate(double val);
    void setTerm(unsigned int val);
    void setFirstInstallment(double val);

    virtual void PrintName(std::ofstream &file) const       = 0;
    virtual double EndTermIncome() const                    = 0;
    virtual double ChosenTimeIncome(unsigned int val) const = 0;
protected: 
    double rate;           //percents
    unsigned int term;     //in months
    double installment;    //UAH
};

class FixedDeposit : public Deposit{
public:
    FixedDeposit();
    virtual ~FixedDeposit();

    virtual void PrintName(std::ofstream &file) const;
    virtual double EndTermIncome() const;
    virtual double ChosenTimeIncome(unsigned int val) const;
};

class AccumulativeDeposit : public Deposit{
public:
    AccumulativeDeposit();
    virtual ~AccumulativeDeposit();

    virtual void PrintName(std::ofstream &file) const;
    virtual double EndTermIncome() const;
    virtual double ChosenTimeIncome(unsigned int val) const;

protected:
    const int capitalizationRate = 2;      //times per year
};

class VIPDeposit : public Deposit{
public:
    VIPDeposit();
    virtual ~VIPDeposit();

    void raiseInstallment(unsigned int val);

    virtual void PrintName(std::ofstream &file) const;
    virtual double EndTermIncome() const;
    virtual double ChosenTimeIncome(unsigned int val) const;
protected:
    const int capitalizationRate = 4;      //times per year
    const double rateIncreaseCoef = 0.05;
};