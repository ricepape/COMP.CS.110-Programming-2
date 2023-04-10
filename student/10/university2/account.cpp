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
    List_completed_courses* current = first_;
        while (current != nullptr) {
            List_completed_courses* temp = current;
            current = current->next;
            delete temp;
        }

        List_incompleted_courses* in_current = in_first_;
        while (in_current != nullptr) {
            List_incompleted_courses* in_temp = in_current;
            in_current = in_current->next;
            delete in_temp;
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


bool Account::is_course_completed(const std::string&course_to_be_checked)
{
    List_completed_courses* course_lists= first_;
    if (course_lists==nullptr){
        return false;
    }
    while ( course_lists != nullptr ) {
      if (course_lists->courses_completed == course_to_be_checked){
          return true;
      }
      else {
          course_lists = course_lists->next;
      }
    }
    return false;
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

void Account::add_course(const std::string &course_to_be_added, int num_mark)
{
    if (num_mark==1){
    List_completed_courses* new_item = new List_completed_courses{course_to_be_added, nullptr};
    if ( first_ == nullptr ) {
       first_ = new_item;
       last_ = new_item;
    } else {
       last_->next = new_item;
       last_ = new_item;
        }
    }
    else {
        List_incompleted_courses* new_item = new List_incompleted_courses{course_to_be_added, nullptr};
        if ( in_first_ == nullptr ) {
           in_first_ = new_item;
           in_last_ = new_item;
        } else {
           in_last_->next = new_item;
           in_last_ = new_item;
            }
    }
}

std::vector<std::string> Account::vector_courses(int num_mark)
{

    std::vector<std::string> courses;
    if (num_mark==1){
    List_completed_courses* course_lists= first_;
    while ( course_lists != nullptr ) {
        courses.push_back(course_lists->courses_completed);
        course_lists=course_lists->next;
    }
    }
    else if (num_mark==0){
        List_incompleted_courses* course_lists= in_first_;
        while ( course_lists != nullptr ) {
            courses.push_back(course_lists->courses_incompleted);
            course_lists=course_lists->next;
        }
    }
    return courses;
}

void Account::delete_course(const std::string &course_to_be_deleted)
{
    List_incompleted_courses* course= in_first_;
    while ( course != nullptr ) {
        if (course->courses_incompleted == course_to_be_deleted){
            in_first_ = in_first_->next;
            return;
    }
        else course = course->next;
    }
    return;
}

