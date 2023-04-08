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

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}

void University::sign_up(Params params)
{
    std::string code = params.at(0);
    unsigned long int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
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
    std::cout << SIGNED_UP << std::endl;
}

void University::complete(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end())
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    Course* chosen_course =  courses_[code];
    Account* chosen_account = accounts_[account];
    if (not chosen_course->is_student_exists(account)){
            std::cout << NO_SIGNUPS << std::endl;
            return;
        }
    chosen_account->add_course(code);
    chosen_course->delete_student(account);
    std::cout << COMPLETED << std::endl;
}


void University::print_signups(Params params)
{
    if (std::stoi(params.at(0))){
    if ( accounts_.find(std::stoi(params.at(0))) == accounts_.end() )
    {
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    }
    else std::cout << CANT_FIND << params.at(0) << std::endl;
    Course* chosen_course =  courses_[params.at(0)];


    for (auto& element: chosen_course->vector_students()){
        std::cout << element << ": "<< accounts_[element]->get_full_name()
                  << ", " << accounts_[element]->get_email() << std::endl;
    }

}

void University::print_completed(Params params)
{
    if ( accounts_.find(std::stoi(params.at(0))) == accounts_.end() )
    {
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    Account* chosen_account = accounts_[std::stoi(params.at(0))];
    int total_credits=0;
    for (auto& element: chosen_account->vector_courses()){
        courses_.at(element)->print_long_info();
        total_credits+=courses_.at(element)->get_credits();
    }
    std::cout<<"Total credits: "<< total_credits <<std::endl;

}

void University::print_study_state(Params params)
{
    unsigned long int account= std::stoi(params.at(0));
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    std::cout << "Current:" << std::endl;
    for ( auto course : courses_ ){
        if (course.second->is_student_exists(account)){
            course.second->print_info(true);
        }
    }
    std::cout << "Completed:" << std::endl;
    print_completed(params);
}


void University::graduate(Params params)
{
    if ( accounts_.find(std::stoi(params.at(0))) == accounts_.end() )
    {
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    unsigned long int student_number= std::stoi(params.at(0));
    Account* chosen_account = accounts_[student_number];
    chosen_account->graduation();
    for ( auto course : courses_ ){
        if (course.second->is_student_exists(student_number)){
            course.second->delete_student(student_number);
        }
    }
    std::cout << GRADUATED << std::endl;
}
