/* Account
 * Account: describes persons: students and teachers (staff). These persons
 * are not separated at all. When a new person (account) is added, they get an account
 * number (that can be called a student number in the case of a student). Account numbers
 * are running numbers such that the first person added gets the number 111111. Besides
 * the account number, each person has a name and contact information. For each new account,
 * the program generates automatically an e-mail address with the suffix tuni.fi such that
 * accounts with the same name have different e-mail addresses.
 *
 * The source code file of class Account includes:
 *   @ Function ~Account: destructor for the Account class.
 *   @ Function print: print all the information of the account given by user (already implemented)
 *   @ Function get_email: return the email of the account whose student is (already implemented)
 *   @ Function get_full_name: return the full name of the account whose student is
 *   (already implemented)
 *   @ Function get_account_number: return the account number of the account (already implemented)
 *   @ Function get_graduated: return the graduation status of the account
 *   @ Function graduation: turn a graduation status of an account into true
 *   @ Function is_course_completed: check if the student has completed a given course, both
 *   student account number and course given by user
 *   @ Function add_course: form a struct of course and add the course
 *   @ Function complete: turn a completion status of a course into true
 *   @ Function vector_courses: returning a vector of courses under the condition, either completed
 *   in the completion order, or incompleted in the signing up order.
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

#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>
#include <memory>

//initialization of the class
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

/**
 * @Function ~Account: destructor for the Account class. The destructor
 * is responsible for cleaning up any dynamically allocated memory used by
 * the class before it is destroyed. In this case, this destructor is responsible
 * for freeing the memory allocated to the linked list of Course_attended
 * objects stored in the "first_" data member of the Account class.
 **/
Account::~Account()
{
    Course_attended* current = first_;
        while (current != nullptr) {
            Course_attended* temp = current;
            current = current->next;
            delete temp;
        }
}

/**
 * @Function print: print all the information of the account given by user
 **/
void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}


/**
 * @Function get_email: return the email of the account whose student is
 **/
std::string Account::get_email() const
{
    return email_;
}

/**
 * @Function get_full_name: return the full name of the account whose student is
 **/
std::string Account::get_full_name() const
{
    return full_name_;
}

/**
 * @Function get_account_number: return the account number of the account
 **/
int Account::get_account_number() const
{
    return account_number_;
}

/**
 * @Function get_graduated: return the graduation status of the account
 **/
bool Account::get_graduated()
{
    return graduated;
}


/**
 * @Function graduation: turn a graduation status of an account into true
 **/
void Account::graduation()
{
    //change the graduation status (graduated variable)
    graduated = true;
    get_graduated();
}


/**
 * @Function is_course_completed: check if the student has completed a given course, both
 * student account number and course given by user
 * @return true if the course is mark as completed in the student account, false otherwise
 * @parameter: course_to_be_checked, std::string: containing the course that is
 * determined by the user to be completed
 **/
bool Account::is_course_completed(const std::string&course_to_be_checked)
{
    Course_attended* course_lists= first_;
    //If there's no struct of course in the linked list, there's sure to be no completed course
    if (course_lists==nullptr){
        return false;
    }
    while ( course_lists != nullptr ) {
        //check if the course being pointed to is the same as the given course
      if (course_lists->courses == course_to_be_checked){
          //check the complete status of the course
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

/**
 * @Function add_course: form a struct of course and add the course
 * into the end of the linked list of the account
 * @parameter: course_to_be_added, std::string: containing the course that is
 * determined by the user to be added to the account
 **/
void Account::add_course(const std::string &course_to_be_added)
{
    Course_attended* new_item = new Course_attended{course_to_be_added, false, 0, nullptr};

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
 * @Function complete: turn a completion status of a course into true
 * @parameter: course_to_be_completed, std::string: containing the course that is
 * determined by the user to be completed
 **/
void Account::complete(const std::string& course_to_be_completed) {
    //create the pointer for use
    Course_attended* course = first_;

    while (course != nullptr) {
        //check through the linked list to find the given course
        if (course->courses == course_to_be_completed) {
            //check if the course is completed
            if (!course->is_completed) {
                //turn the completion status of the course to true
                course->is_completed = true;
                //add in the complete order
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


/**
 * @Function vector_courses: returning a vector of courses under the condition, either completed
 * in the completion order, or incompleted in the signing up order.
 * @parameter: is_completed, bool: containing the status of the course need to be printed,
 * completed or not
 **/
std::vector<std::string> Account::vector_courses(bool is_completed)
{
    //Create a vector for storage
    std::vector<std::string> vector_courses;
    //Returning the completed courses
    if (is_completed){
        //run for the order of completion
        for (int k=1; k<complete_running_number_; ++k){
            Course_attended* course_ptr= first_;
            while ( course_ptr != nullptr ) {
                //find the completed course in the linked list of the struct, and its order must be
                //satisfies
                if (course_ptr->is_completed == is_completed
                        and course_ptr->order_completed_==k)
                //if satisfies, add the course to the vector
                vector_courses.push_back(course_ptr->courses);
                //move on to the next struct
                course_ptr=course_ptr->next;
            }
        }//eventually returns a vector of complete courses in the completed order.
    }
    //Returning the incompleted courses
    else {
    Course_attended* course_ptr= first_;
    while ( course_ptr != nullptr ) {
        //find the incompleted course in the linked list of the struct
        if (course_ptr->is_completed == is_completed)
        //if satisfies, add the course to the vector
        vector_courses.push_back(course_ptr->courses);
        //move on to the next struct
        course_ptr=course_ptr->next;
        }
    }
    return vector_courses;
}



