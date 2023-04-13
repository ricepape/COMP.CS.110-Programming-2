/* University
 *
 * Desc:
 *   This program implements a program University contains all informations
 *   and related actions and works of these informations. The program has 5 different
 *   classes, each representing an aspect of the University, as well as the functional
 *   part of the program.
 *
 *   @class Account: describes persons: students and teachers (staff). These persons
 *   are not separated at all. When a new person (account) is added, they get an account
 *   number (that can be called a student number in the case of a student). Account numbers
 *   are running numbers such that the first person added gets the number 111111. Besides
 *   the account number, each person has a name and contact information. For each new account,
 *   the program generates automatically an e-mail address with the suffix tuni.fi such that
 *   accounts with the same name have different e-mail addresses.
 *
 *   @class Course: describes a course. From each course, its code, name, credit points,
 *   and course staff (there can be several of them) is provided. By default, all courses
 *   give five credit points. It is possible to add staff and students for a course, as well
 *   as print course data.
 *
 *   @class University: describes a university (in general, there can be several of them,
 *   but in this program, we need only one). The class contains information about all the
 *   courses and persons in the university. As said earlier, a person can be a student or a
 *   teacher. For this data, the class has map structures that are added with new elements
 *   based on user-given commands. It is possible for students to sign up for courses and
 *   complete (pass) courses. All the commands targeting to the university will be implemented
 *   in this class.
 *
 *   @namespace Utils: provides the utility function split,
 *   as well as a few other utility functions for later use in the program.
 *
 *   @class Cli: identify the commands from the user input. All the commands will be implemented
 *   in the University class. The header file of the command line interpreter defines a command
 *   vector including function pointers. From it you can see which function in class University
 *   implements each command.
 *
 *   The main program module is very simple. It just starts the command line interpreter (CLI)
 *   that goes on until the QUIT command is given by the user.
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


#include "cli.hh"
#include "university.hh"
const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}

