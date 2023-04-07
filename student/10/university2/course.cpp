#include "course.hh"
#include <iostream>


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

void Course::add_student(const unsigned long int &student_to_be_added) {
   List_students* new_item = new List_students{student_to_be_added, nullptr};

   if ( first_ == nullptr ) {
      first_ = new_item;
      last_ = new_item;
   } else {
      last_->next = new_item;
      last_ = new_item;
   }
}

bool Course::is_student_exists(const unsigned long int &student_to_be_checked)
{
    List_students* student_lists= first_;
    while ( student_lists != nullptr ) {
      if (student_lists->students_signed_up == student_to_be_checked){
          return true;
      }
      else student_lists = student_lists->next;
    }
    return false;
}

void Course::delete_student(const unsigned long int &student_to_be_deleted)
{
    List_students* student_lists= first_;
    while ( student_lists != nullptr ) {
        if (student_lists->students_signed_up == student_to_be_deleted){
            first_ = first_->next;
            return;
    }
        else student_lists = student_lists->next;
    }
    return;
}


void Course::sort() {
    bool swapped = true;
    List_students* ptr1 = nullptr;
    List_students* lptr = nullptr;

    if (first_ == nullptr)
        return;

    while (swapped) {
        swapped = false;
        ptr1 = first_;
        while (ptr1->next != lptr) {
            if (ptr1->students_signed_up > ptr1->next->students_signed_up) {
                unsigned long int temp = ptr1->students_signed_up;
                ptr1->students_signed_up = ptr1->next->students_signed_up;
                ptr1->next->students_signed_up = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}



std::vector<unsigned long int> Course::vector_students()
{
    sort();
    std::vector<unsigned long int> students;
    List_students* student_lists= first_;
    while ( student_lists != nullptr ) {
        students.push_back(student_lists->students_signed_up);
        student_lists=student_lists->next;
    }
    return students;
}
