/* Class: Course
 * -------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a single course, with name and code, staff and students.
 *
 *   From each course, its code, name, credit points,
 *   and course staff (there can be several of them) is provided. By default, all courses
 *   give five credit points. It is possible to add staff and students for a course, as well
 *   as print course data.
 * */
#ifndef COURSE_HH
#define COURSE_HH

#include "account.hh"
#include <string>
#include <vector>

//const std::string STUDENT_ADDED = "A new student has been added.";
const std::string STAFF_ADDED = "A new staff member has been added.";
const std::string STAFF_EXISTS = "Error: Staff member already added on this course.";
const std::string STUDENT_EXISTS = "Error: Student already added on this course.";
const std::string STUDENT_COMPLETED = "Error: Student already completed this course.";


class Course
{
public:
    /**
     * @brief Course
     * @param code unique code for the course, used as id
     * @param name
     * @param credits
     */
    Course( const std::string& code, const std::string& name, int credits = 5);

    /**
     * @brief Course destructor
     */
    ~Course();

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, pring also a newline
     * at the end.
     */
    void print_info(bool print_new_line);

    /**
     * @brief print_long_info
     * Print longer course info with staff.
     */
    void print_long_info();

    /**
     * @brief print_staff
     * Print all staff of the course.
     */
    void print_staff();

    /**
     * @brief add staff
     * @param new_staff
     * Add a staff member to course.
     */
    void add_staff(Account* new_staff_member);

    /**
     * @brief get_code
     * @return the course code.
     */
    const std::string get_code() const;

    /**
     * @brief get_credits
     * @return the amount of credits this course is valued.
     */
    int get_credits() const;

    /**
     * @brief add_student: adding a student into the struct containing
     * the list of students who signed up for the course
     */
    void add_student(const unsigned long int& student_to_be_added);

    /**
     * @brief is_student_exists: checking whether the student number is
     * in the list of students of the course
     * @return the status value, true if there exists, false otherwise
     */
    bool is_student_exists(const unsigned long int& student_to_be_checked);

    /**
     * @brief vector_students
     * @return a vector containing all student numbers whose signed up
     * in the course
     */
    std::vector<unsigned long int> vector_students();

private:
    std::string course_code_;
    std::string name_;
    int credits_;
    std::vector<Account*> course_staff_;

    //
    /**
     * Define a struct containing the students' number who have signed up
     * for the course and the pointer next which pointed at the next course
     * in the linked list
     * The struct includes:
     * @parameter: students_signed_up, unsigned long int: contains the
     * account number of the student.
     * @parameter: next, List_students*: the pointer pointing to the next student
     * in the linked list
     **/
    struct List_students{
        unsigned long int students_signed_up;
        List_students* next;
    };

    // the pointer point to the struct for using the dynamic memory management
    // for later use
    List_students* first_ =nullptr;
    List_students* last_ = nullptr;
};

#endif // COURSE_HH

