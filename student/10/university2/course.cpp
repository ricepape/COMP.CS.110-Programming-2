/* Course
 * Course: describes a course. From each course, its code, name, credit points,
 * and course staff (there can be several of them) is provided. By default, all courses
 * give five credit points. It is possible to add staff and students for a course, as well
 * as print course data.
 *
 * The source code file of class Course includes:
 *   @ Function ~Account: destructor for the Course class.
 *   @ Function print_info: print the information of the course given by user
 *   (already implemented)
 *   @ Function print_long_info: print the information of the course given by user in
 *   a longer and more formal way (already implemented)
 *   @ Function print_staff: print the information of the staff of the course
 *   (already implemented)
 *   @ Function add_staff: add an account to be staff of the course (already implemented)
 *   @ Function get_code: return the code of the course (already implemented)
 *   @ Function get_credits: return the credits of the course (already implemented)
 *   @ Function add_student: form a struct and add the student info
 *   into the end of the linked list of the given course
 *   @ Function is_student_exists: check if the student has signed up in the course
 *   @ Function vector_students: returning a vector of students' code
 *   account in the signing up order.
 *
 * Program author
 * Name: Vu Dinh Thi (Thi Vu)
 * Student number: 151394898
 * UserID: tpthvu
 * E-Mail: thi.vu@tuni.fi
 *
 * Notes about the program and it's implementation (if any): None
 *
 * */


#include "course.hh"
#include <iostream>
#include <memory>


//initialization of the class
Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}
/**
 * @Function ~Course: destructor for the Course class. The destructor
 * is responsible for cleaning up any dynamically allocated memory used by
 * the class before it is destroyed. The function releases the memory allocated
 * to all the List_students objects that were created as part of the Course
 * object, ensuring that there are no memory leaks when the object is destroyed.
 **/
Course::~Course()
{
    List_students* current = first_;
        while (current != nullptr) {
            List_students* temp = current;
            current = current->next;
            delete temp;
        }
}
/**
 * @Function print_info: print the information of the course given by user
 **/
void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}
/**
 * @Function print_long_info: print the information of the course given by user in
 * a longer and more formal way.
 **/
void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

/**
 * @Function print_staff: print the information of the staff
 * of the course
 **/
void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

/**
 * @Function add_staff: add an account to be staff of the course
 * @parameter: new_staff_member, class Account: the account of the person
 * that is added to be staff, given by user
 **/
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

/**
 * @Function get_code: return the code of the course
 **/
const std::string Course::get_code() const
{
    return course_code_;
}

/**
 * @Function get_credits: return the credits of the course
 **/
int Course::get_credits() const
{
    return credits_;
}

/**
 * @Function add_student: form a struct and add the student info
 * into the end of the linked list of the given course
 * @parameter: student_to_be_added, std::string: containing the student number
 * that is determined by the user to be added to the course
 **/
void Course::add_student(const unsigned long int &student_to_be_added) {
   List_students* new_item = new List_students{student_to_be_added, nullptr};  

    //add the struct to the end of the linked list
   if ( first_ == nullptr ) {
      first_ = new_item;
      last_ = new_item;
   } else {
      last_->next = new_item;
      last_ = new_item;
   }
}

/**
 * @Function is_student_exists: check if the student has signed up in the course
 * @return true if there exists the student account number in the linked list of students signed up,
 * false otherwise
 * @parameter: student_to_be_checked, unsigned long int: containing the course that is
 * determined by the user to be completed
 **/
bool Course::is_student_exists(const unsigned long int &student_to_be_checked)
{
    //create a pointer
    List_students* student_lists= first_;
    //Run through all the elements in the linked list
    while ( student_lists != nullptr ) {
        //check if the value in which the pointer is pointing in is the same
      if (student_lists->students_signed_up == student_to_be_checked){
          return true;
      }
      else student_lists = student_lists->next;
    }
    return false;
}

/**
 * @Function vector_students: returning a vector of students' code account in the signing up order.
 **/
std::vector<unsigned long int> Course::vector_students()

{   //Create a vector for storage
    std::vector<unsigned long int> students;
    List_students* student_lists= first_;
    //Run through all the elements in the linked list
    while ( student_lists != nullptr ) {
            students.push_back(student_lists->students_signed_up);
            student_lists=student_lists->next;
        }
        return students;

}

