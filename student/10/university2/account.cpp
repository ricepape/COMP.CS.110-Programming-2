#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>

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

bool Account::is_course_completed(const std::string&student_to_be_checked)
{
    List_completed_courses* student_lists= first_;
    if (student_lists==nullptr){
        return false;
    }
    while ( student_lists != nullptr ) {
      if (student_lists->courses_completed == student_to_be_checked){
          return true;
      }
      else {
          student_lists = student_lists->next;
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

void Account::add_course(const std::string &course_to_be_added)
{
    List_completed_courses* new_item = new List_completed_courses{course_to_be_added, nullptr};
    if ( first_ == nullptr ) {
       first_ = new_item;
       last_ = new_item;
    } else {
       last_->next = new_item;
       last_ = new_item;
    }
}

void Account::sort() {
    bool swapped = true;
    List_completed_courses* ptr1 = nullptr;
    List_completed_courses* lptr = nullptr;

    if (first_ == nullptr)
        return;

    while (swapped) {
        swapped = false;
        ptr1 = first_;
        while (ptr1->next != lptr) {
            if (ptr1->courses_completed > ptr1->next->courses_completed) {
                std::string temp = ptr1->courses_completed;
                ptr1->courses_completed = ptr1->next->courses_completed;
                ptr1->next->courses_completed = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}

std::vector<std::string> Account::vector_courses()
{
    sort();
    std::vector<std::string> students;
    List_completed_courses* student_lists= first_;
    while ( student_lists != nullptr ) {
        students.push_back(student_lists->courses_completed);
        student_lists=student_lists->next;
    }
    return students;
}
