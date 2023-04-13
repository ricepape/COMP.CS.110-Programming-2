/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 * When a new person (account) is added, they get an account
 * number (that can be called a student number in the case of a student). Account numbers
 * are running numbers such that the first person added gets the number 111111. Besides
 * the account number, each person has a name and contact information. For each new account,
 * the program generates automatically an e-mail address with the suffix tuni.fi such that
 * accounts with the same name have different e-mail addresses.
 *
 *
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>

class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

    /**
     * @brief check if the course given is completed or not
     * @return true if completed, false otherwise
     */
    bool is_course_completed(const std::string& course_to_be_checked);

    /**
     * @brief get_graduation status
     * @return graduation status as bool value linked to this account
     */
    bool get_graduated();

    /**
     * @brief add the given course into the struct List_courses linked to this account
     */
    void add_course(const std::string &course_to_be_added);

    /**
     * @brief change the status of the given course and the order of completion
     * in the struct List_courses linked to this account
     */
    void complete(const std::string& course_to_be_completed);

    /**
     * @brief create a vector of courses for later printing use
     */
    std::vector<std::string> vector_courses(bool is_completed);

    /**
     * @brief change the graduation status
     */
    void graduation();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    // a flag denotes the graduation status of the student
    bool graduated = false;

    /**
     * Struct Course_attended: a struct containing the courses' code
     * which students has signed up for and their related attributes.
     * The struct includes:
     * The courses are stored in a linked list, in the order of signing up.
     * @parameter courses, std::string: containing the course code
     * @parameter is_completed, bool: containing the status of the course, whether
     * it is completed or not
     * @parameter order_completed_, int: containing the complete order of the course.
     * If the course is incompleted, the order is 0.
     * @parameter: next, List_students*: the pointer pointing to the next student
     * in the linked list
     */
    struct Course_attended{
        std::string courses;
        bool is_completed;
        int order_completed_;
        Course_attended* next;
    };

    // the pointer point to the struct for using the dynamic memory management
    // for later use
    Course_attended* first_ =nullptr;
    Course_attended* last_ = nullptr;

    //to keep track of the order of the completed courses
    int complete_running_number_=1;




};

#endif // ACCOUNT_HH
