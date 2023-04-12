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




private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    bool graduated = false;

    struct List_courses{
        std::string courses;
        bool is_completed;
        int order_completed_;
        List_courses* next;
    };

    List_courses* first_ =nullptr;
    List_courses* last_ = nullptr;

    //to keep track of the order of the completed courses
    int complete_running_number_=1;




};

#endif // ACCOUNT_HH
