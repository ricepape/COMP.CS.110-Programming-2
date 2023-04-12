#include "university.hh"
#include <iostream>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);
    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    std::map<int, Account*>::iterator iter = accounts_.find(account);
    if ( iter == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    iter->second->print();
}

bool University::check_if_course_exists(std::string code){
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return false;
    }
    else return true;
}

bool University::check_if_student_exists(unsigned long int account){
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return false;
    }
    else return true;
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if (not check_if_course_exists(code)){
        return;
    }
    if (not check_if_student_exists(account)){
        return;
    }
    courses_.at(code)->add_staff(accounts_.at(account));
}

void University::sign_up(Params params)
{
    std::string code = params.at(0);
    unsigned long int account = std::stoi(params.at(1));
    if (not check_if_course_exists(code)){
        return;
    }
    if (not check_if_student_exists(account)){
        return;
    }
    Course* chosen_course =  courses_[code];
    Account* chosen_account = accounts_[account];
    if (chosen_account->get_graduated() == true){
        std::cout << ALREADY_GRADUATED << std::endl;
        return;
    }
    if (chosen_account->is_course_completed(code)){
            std::cout << STUDENT_COMPLETED << std::endl;
            return;
        }
    if (chosen_course->is_student_exists(account)){
            std::cout << STUDENT_EXISTS << std::endl;
            return;
        }

    chosen_course->add_student(account);
    chosen_account->add_course(code);
    std::cout << SIGNED_UP << std::endl;
}

void University::complete(Params params)
{
    std::string code = params.at(0);
    unsigned long int account = std::stoi(params.at(1));
    if (not check_if_course_exists(code)){
        return;
    }
    if (not check_if_student_exists(account)){
        return;
    }
    Course* chosen_course =  courses_[code];
    Account* chosen_account = accounts_[account];
    if (not chosen_course->is_student_exists(account)){
            std::cout << NO_SIGNUPS << std::endl;
            return;
        }
    if (chosen_account->is_course_completed(code)){
        std::cout << NO_SIGNUPS << std::endl;
        return;
    }
    chosen_account->complete(code);
    std::cout << COMPLETED << std::endl;
}


void University::print_signups(Params params)
{

}

void University::print_completed(Params params)
{


}


void University::print_study_state(Params params)
{

}


void University::graduate(Params params)
{

}
