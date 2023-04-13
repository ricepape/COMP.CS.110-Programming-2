/* University
 * University: describes a university (in general, there can be several of them,
 * but in this program, we need only one). The class contains information about all the
 * courses and persons in the university. As said earlier, a person can be a student or a
 * teacher. For this data, the class has map structures that are added with new elements
 * based on user-given commands. It is possible for students to sign up for courses and
 * complete (pass) courses. All the commands targeting to the university will be implemented
 * in this class.
 * The source code file of class University includes:
 *   @ Function ~University: destructor for the University class. The destructor
 *   is responsible for cleaning up any dynamically allocated memory used by
 *   the class before it is destroyed.
 *   @ Function new_course: add a new_course into the university system (already implemented)
 *   @ Function print_courses: print all the courses available in the system
 *   and their information (already implemented)
 *   @ Function print_course: print a course required by the user and its information
 *   (already implemented)
 *   @ Function new_account: add a new person (students/staff) into the university system
 *   by creating an account. (already implemented)
 *   @ Function print_accounts: print all the accounts available in the system
 *   and their information (already implemented)
 *   @ Function print_account: print an account required by the user and its information
 *   (already implemented)
 *   @ Function check_if_course_exists: check if the course given by the user
 *   is available in the system.
 *   @ Function check_if_student_exists: check if the student given by the user
 *   is available in the system.
 *   @ Function add_staff: assign a person who has defined in the system
 *   (already implemented)
 *   to be staff of a course, with the info of the course code and student
 *   account number given by user
 *   @ Function sign_up: sign up a student into a course with the info of the course
 *   code and student account number given by user
 *   @ Function complete: complete a course for a student with the info of the course
 *   code and student account number given by user (by changing the complete status of
 *   the course)
 *   @ Function print_signups: print out all the students who have signed up
 *   for the course in order of signing up with the course code given by the user
 *   @ Function print_completed: print out the completed courses in order of
 *   completion with the student account number given by the user
 *   @ Function print_study_state: print out the study state of a student, including
 *   the incompleted course in the order of signing up, and the completed courses
 *   in order of completion  with the student account number given by the user
 *   @ Function graduate: put a student account to the graduation status
 *   (change the graduation status of a student to true and complete all the courses)
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

#include "university.hh"
#include <iostream>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}
/**
 * @Function ~University: destructor for the University class. The destructor
 * is responsible for cleaning up any dynamically allocated memory used by
 * the class before it is destroyed.
 **/
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
/**
 * @Function new_course: add a new_course into the university system
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containing string of the course code
 * and string of the name of the code
 **/
void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);
    //check if the course code already exists in the system
    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }
    //add the course into the system
    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

/**
 * @Function print_courses: print all the courses available in the system
 * and their information
 **/
void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}
/**
 * @Function print_course: print a course required by the user and its information
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containing string of the course code
 * that the user wants to print the information.
 **/
void University::print_course(Params params)
{
    std::string code = params.at(0);
    //check if the code is found in the system
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

/**
 * @Function new_account: add a new person (students/staff) into the university system
 * by creating an account.
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containing string of the full name
 * of the person
 **/
void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    //check if are there any same name in the existing accounts, to add the correct
    //number to distinguish between these accounts' informations.
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

/**
 * @Function print_accounts: print all the accounts available in the system
 * and their information
 **/
void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

/**
 * @Function print_account: print an account required by the user and its information
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containing string of the account
 * number that the user wants to print the information.
 **/
void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    //create an iterator
    std::map<int, Account*>::iterator iter = accounts_.find(account);
    //check if the account number exists in the system
    if ( iter == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    iter->second->print();
}


/**
 * @Function check_if_course_exists: check if the course given by the user
 * is available in the system.
 * @parameter: code, std::string: the course code that needs
 * to be checked
 * @return true if the course is found, false otherwise
 **/
bool University::check_if_course_exists(std::string code){
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return false;
    }
    else return true;
}

/**
 * @Function check_if_student_exists: check if the student given by the user
 * is available in the system.
 * @parameter: account, unsigned long int: the student account number that needs
 * to be checked
 * @return true if the account is found, false otherwise
 **/
bool University::check_if_student_exists(unsigned long int account){
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return false;
    }
    else return true;
}

/**
 * @Function add_staff: assign a person who has defined in the system
 * to be staff of a course, with the info of the course code and student
 * account number given by user
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containing string of the course code
 * and string containing student account number given by the user
 **/
void University::add_staff(Params params)
{
    //get the course code from the user
    std::string code = params.at(0);
    //get the student account number and transform the value of
    //the student account from string to integer
    int account = std::stoi(params.at(1));
    //check if the course code and the student account number
    // provided by the user exists in the system
    if (not check_if_course_exists(code)){
        return;
    }
    if (not check_if_student_exists(account)){
        return;
    }
    courses_.at(code)->add_staff(accounts_.at(account));
}

/**
 * @Function sign_up: sign up a student into a course with the info of the course
 * code and student account number given by user
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containing string of the course code
 * and string containing student account number given by the user
 **/
void University::sign_up(Params params)
{
    //get the course code from the user
    std::string code = params.at(0);
    //get the student account number and transform the value of
    //the student account from string to integer
    unsigned long int account = std::stoi(params.at(1));
    //check if the course code and the student account number
    // provided by the user exists in the system
    if (not check_if_course_exists(code)){
        return;
    }
    if (not check_if_student_exists(account)){
        return;
    }
    //get the student account from the account number
    //and the course class from the course code
    Course* chosen_course =  courses_[code];
    Account* chosen_account = accounts_[account];
    //check if the student has already graduated
    if (chosen_account->get_graduated() == true){
        std::cout << ALREADY_GRADUATED << std::endl;
        return;
    }
    //check if the student has already completed the course. If yes
    //then the student cannot sign up again
    if (chosen_account->is_course_completed(code)){
            std::cout << STUDENT_COMPLETED << std::endl;
            return;
        }
    //check if the student has signed up for the course
    if (chosen_course->is_student_exists(account)){
            std::cout << STUDENT_EXISTS << std::endl;
            return;
        }
    //add the student into the course's linked list of students signed up using function
    //add_student
    chosen_course->add_student(account);
    //add the course into the student account's linked list of course using function
    //add_course
    chosen_account->add_course(code);
    std::cout << SIGNED_UP << std::endl;
}


/**
 * @Function complete: complete a course for a student with the info of the course
 * code and student account number given by user (by changing the complete status of the course)
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containing string of the course code
 * and string containing student account number given by the user
 **/
void University::complete(Params params)
{
    //get the course code from the user
    std::string code = params.at(0);
    //get the student account number and transform the value of
    //the student account from string to integer
    unsigned long int account = std::stoi(params.at(1));
    //check if the course code and the student account number
    // provided by the user exists in the system
    if (not check_if_course_exists(code)){
        return;
    }
    if (not check_if_student_exists(account)){
        return;
    }
    //get the student account from the account number
    //and the course class from the course code
    Course* chosen_course =  courses_[code];
    Account* chosen_account = accounts_[account];
    //check if the student has signed up for the course
    if (not chosen_course->is_student_exists(account)){
            std::cout << NO_SIGNUPS << std::endl;
            return;
        }
    //check if the student has already completed the course
    if (chosen_account->is_course_completed(code)){
        std::cout << NO_SIGNUPS << std::endl;
        return;
    }
    //change the completion status of the course in the student account
    chosen_account->complete(code);
    std::cout << COMPLETED << std::endl;
}


/**
 * @Function print_signups: print out all the students who have signed up
 * for the course in order of signing up with the course code given by the user
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containg string of the
 * course code given by the user
 **/
void University::print_signups(Params params)
{
    //transform the value of the student account from string to integer
    std::string code = params.at(0);
    //check if the student account number provided by the user exists in the system
    if (not check_if_course_exists(code)){
        return;
    }
    Course* chosen_course =  courses_[code];
    //get the vector containing all students who have signed up and print
    //their infomation
    print_account(chosen_course->vector_students());

}


/**
 * @Function print_completed: print out the completed courses in order of
 * completion  with the student account number given by the user
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containg string of the
 * student account number given by the user
 **/
void University::print_completed(Params params)
{
    //transform the value of the student account from string to integer
    unsigned long int account= std::stoi(params.at(0));
    //check if the student account number provided by the user exists in the system
    if (not check_if_student_exists(account)){
        return;
    }
    //print the completed courses
    //get the student account from the account number
    Account* chosen_account = accounts_[account];
    //create a parameter for storing the total credits
    int total_credits=0;
    //get the vector containing all completed courses and
    for (auto& element: chosen_account->vector_courses(true)){
        //print the info of the course
        courses_.at(element)->print_info(true);
        //add the credits of each course into the total_credits parameter
        total_credits+=courses_.at(element)->get_credits();
    }
    std::cout<<"Total credits: "<< total_credits <<std::endl;

}

/**
 * @Function print_study_state: print out the study state of a student, including
 * the incompleted course in the order of signing up, and the completed courses
 * in order of completion  with the student account number given by the user
 * @parameter: params, Params (std::vector<std::string>): a vector containing strings with
 * contents given by the user. In this case, the vector containg string of the
 * student account number given by the user
 **/
void University::print_study_state(Params params)
{
    //transform the value of the student account from string to integer
    unsigned long int account= std::stoi(params.at(0));
    //check if the student account number provided by the user exists in the system
    if (not check_if_student_exists(account)){
        return;
    }
    //print the incompleted courses
    //get the student account from the account number
    Account* chosen_account = accounts_[account];
    std::cout << "Current:" << std::endl;
    //get the vector containing all incompleted courses and
    for (auto &element: chosen_account->vector_courses(false)){
        //print the info of the course
            courses_.at(element)->print_info(true);
        }
    std::cout << "Completed:" << std::endl;
    //print the completed courses
    print_completed(params);
}

/**
 * @Function graduate: put a student account to the graduation status
 * (change the graduation status of a student to true and complete all the courses)
 * @parameter: params, Params (std::vector<std::string>): a vector
 * containing strings with contents given by the user. In this case, the vector
 * containg string of the student account number given by the user
 **/
void University::graduate(Params params)
{
    unsigned long int account= std::stoi(params.at(0));
    //check if the student account
    if (not check_if_student_exists(account)){
        return;
    }
    Account* chosen_account = accounts_[account];
    //change the graduation status
    chosen_account->graduation();
    //complete all the courses still remained incompleted in the account's
    //linked list of courses running through all the courses available
    for (auto &course : courses_ ){
        //check if the student have signed up for the course
        if (course.second->is_student_exists(account)){
            //check if the student have completed the course.
            //if not then complete the course.
            if (not chosen_account->is_course_completed(course.first)){
                chosen_account->complete(course.first);
            }
        }
    }
    std::cout << GRADUATED << std::endl;
}
