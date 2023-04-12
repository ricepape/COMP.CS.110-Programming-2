#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>
#include <memory>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
    List_courses* current = first_;
        while (current != nullptr) {
            List_courses* temp = current;
            current = current->next;
            delete temp;
        }
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

bool Account::get_graduated()
{
    return graduated;
}

void Account::graduation()
{
    graduated = true;
    get_graduated();
}

bool Account::is_course_completed(const std::string&course_to_be_checked)
{
    List_courses* course_lists= first_;
    if (course_lists==nullptr){
        return false;
    }
    while ( course_lists != nullptr ) {
      if (course_lists->courses == course_to_be_checked){
          if(course_lists->is_completed == true){
            return true ;
          } else return false;
      }
      else {
          course_lists = course_lists->next;
      }
    }
    return false;
 }


void Account::add_course(const std::string &course_to_be_added)
{
    List_courses* new_item = new List_courses{course_to_be_added, false, 0, nullptr};
    if ( first_ == nullptr ) {
       first_ = new_item;
       last_ = new_item;
    } else {
       last_->next = new_item;
       last_ = new_item;
    }
}

void Account::complete(const std::string& course_to_be_completed) {
    List_courses* course = first_;

    while (course != nullptr) {
        if (course->courses == course_to_be_completed) {
            if (!course->is_completed) {
                course->is_completed = true;
                course->order_completed_=complete_running_number_;
                complete_running_number_+=1;
                return;
                }
            } else
        {
            course = course->next;
        }

    }
}



std::vector<std::string> Account::vector_courses(bool is_completed)
{

    std::vector<std::string> vector_courses;
    if (is_completed){
        for (int k=0; k<complete_running_number_; ++k){
            List_courses* course_ptr= first_;
            while ( course_ptr != nullptr ) {
                if (course_ptr->is_completed == is_completed and course_ptr->order_completed_==k)
                vector_courses.push_back(course_ptr->courses);
                course_ptr=course_ptr->next;
            }
        }
    }
    else {
    List_courses* course_ptr= first_;
    while ( course_ptr != nullptr ) {
        if (course_ptr->is_completed == is_completed)
        vector_courses.push_back(course_ptr->courses);
        course_ptr=course_ptr->next;
    }
    }
    return vector_courses;
}



