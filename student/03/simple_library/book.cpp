#include "book.hh"
#include "date.hh"



Book::Book(const std::string author, const std::string book_name): author_(author),book_name_(book_name)
{

}


void Book::print() const
{
    std::cout << author_ << " : " << book_name_ << std::endl;
   if (available){
       std::cout<<"- available" << std::endl;
   }
   else{
     std::cout<< "- loaned: "; borrow_date_.print();
     std::cout<< "- to be returned: "; return_date_.print();

   }
}

void Book::loan(Date& loan_date){
    if (available){
        borrow_date_=loan_date;
        return_date_=loan_date;
        return_date_.advance(28);
        available=false;
    }
    else std::cout<<"Already loaned: cannot be loaned" << std::endl;

}


void Book::renew(){
    if (not available){
        return_date_.advance(28);
    }
    else std::cout<<"Not loaned: cannot be renewed" << std::endl;
}

void Book::give_back(){
    available=true;
}
