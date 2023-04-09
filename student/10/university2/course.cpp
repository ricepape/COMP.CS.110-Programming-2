#include "course.hh"
#include <iostream>
#include <memory>

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}

void Course::add_student(unsigned long int student_to_be_added) {
    auto new_item = std::make_unique<List_students>(student_to_be_added, nullptr);
        if (!first_) {
          first_ = new_item.release();
          last_ = new_item.release();
        } else {
          last_->next = new_item.release();
          last_ = new_item.release();
        }
}

bool Course::is_student_exists(unsigned long int student_to_be_checked)
{
    std::unique_ptr<List_students> student_lists{first_};
    while ( student_lists != nullptr ) {
        if (student_lists->students_signed_up == student_to_be_checked){
            return true;
        }
        else student_lists = std::unique_ptr<List_students>{student_lists->next};
    }
    return false;
}


std::vector<unsigned long int> Course::vector_students()
{
    std::vector<unsigned long int> students;
        std::unique_ptr<List_students> student_lists{first_};
        while ( student_lists != nullptr ) {
            students.push_back(student_lists->students_signed_up);
            student_lists=std::unique_ptr<List_students>{student_lists->next};
        }
        return students;
    }
