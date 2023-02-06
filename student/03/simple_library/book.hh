#ifndef BOOK_HH
#define BOOK_HH
#include <date.hh>
#include <iostream>


class Book
{
public:
    Book();

    Book(const std::string author, const std::string book_name) ;

    void print() const;
    void loan(Date& loan_date);
    void renew();
    void give_back();


private:
    std::string author_;
    std::string book_name_;
    bool available = true;
    Date borrow_date_;
    Date return_date_;





};

#endif // BOOK_HH
