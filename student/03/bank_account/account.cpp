#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit): owner_(owner), has_credit(has_credit)
{
   generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
{
    std::cout << Account::owner_ <<" : " << Account::iban_ << " : "<< Account::balance_ << std::endl;
}

void Account::save_money(int save){
    Account::balance_+=save;
}

bool Account::take_money(int take){
    if (Account::has_credit){
        if (Account::balance_-take<(-Account::credit_limit_)){
            std::cout<<"Cannot take money: credit limit overflow"<<std::endl;
            return false;
        }
        else {
            Account::balance_-=take;
            std::cout<< take <<" euros taken: new balance of "<<Account::iban_<<" is "<<Account::balance_<< " euros" <<std::endl;
            return true;
        }
    }
    else{
        if (take>Account::balance_){
            std::cout<<"Cannot take money: balance underflow"<<std::endl;
            return false;
        }
        else {
            Account::balance_-=take;
            std::cout<< take <<" euros taken: new balance of "<<Account::iban_<<" is "<<Account::balance_<< " euros" <<std::endl;
            return true;
        }
    }
}

void Account::transfer_to(Account&name, int total){
    if (Account::has_credit){
        if (Account::take_money(total)){
            name.save_money(total);
        }
        else {
            std::cout<<"Transfer from "<<Account::iban_<<" failed" <<std::endl;
        }
    }
    else {
        if (Account::take_money(total)){
           name.save_money(total);
                }
        else{
            std::cout<<"Transfer from "<<Account::iban_<<" failed" <<std::endl;
    }

}
}

void Account::set_credit_limit(int limit){
    if (Account::has_credit){
        Account::credit_limit_+=limit;
    }
    else{
            std::cout <<"Cannot set credit limit: the account has no credit card" << std::endl;
        }
}


