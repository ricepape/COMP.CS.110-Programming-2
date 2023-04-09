/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * In the project, this class should be expanded to
 * include necessary methods and attributes.
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

    bool is_course_completed(std::string course_to_be_checked);

    bool get_graduated();

    void add_course(std::string course_to_be_added, int num_mark);

    void sort();

    std::vector<std::string> vector_courses(int num_mark);

    void graduation();

    void delete_course(const std::string course_to_be_deleted);

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    bool graduated = false;

    struct List_completed_courses{
        std::string courses_completed;
        List_completed_courses* next;
        List_completed_courses(std::string courses_completed, List_completed_courses* next = nullptr) : courses_completed(std::move(courses_completed)), next(next) {};
    };

    List_completed_courses* first_ =nullptr;
    List_completed_courses* last_ = nullptr;

    struct List_incompleted_courses{
        std::string courses_incompleted;
        List_incompleted_courses* next;
        List_incompleted_courses(std::string courses_incompleted, List_incompleted_courses* next = nullptr) : courses_incompleted(std::move(courses_incompleted)), next(next) {};
    };

    List_incompleted_courses* in_first_ =nullptr;
    List_incompleted_courses* in_last_ = nullptr;


    // Most probably you will need here an attribute (e.g. vector) containing 
    // courses the account has signed up for (either completed or uncompleted
    // or both)

};

#endif // ACCOUNT_HH


