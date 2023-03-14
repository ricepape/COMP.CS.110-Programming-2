/* Library
 *
 * Desc:
 *   This program implements a library from a file. Then, the programs follows
 * the commands related to the library from the requirements of the user.
 *   At first, the program asks the user to input the file containing the
 * contents related to the library. Each line in the file contains a specific
 * content. There are four fields on each line, and none of the fields can be
 * empty or filled with spaces only. The program checks if the input file can
 * be opened or if it is in the correct form.
 *   After the file has been read, the program starts its actual operation.
 * Every time it expects input from the user, it prints the command prompt lib>
 * (and a space) at the beginning of the line. The user give commands to the
 * program. The commands includes:
 * - libraries: Prints all the known libraries in alphabetical order, one below
 * the other
 * - material <name of the library>: Prints, in alphabetical order, one below
 * the other, all the books of the given library
 * - books <name of the library> <name of the author>: Printing all
 * the books and the number of reservations of them (separated by ”—”) in
 * the library in question arranged alphabetically by the book name
 * - reservable <name of the author> <name of the book>: Prints the shortest
 * reservation queue of the author and book in question, and below that,
 * alphabetized, the libraries with this equal length of reservation queue.
 * If the user input has an error, the program prints the relevant error
 * message, and after that, returns to waiting for user input. When the user
 * enters "quit", the program terminates with the return value EXIT_SUCCESS
 * without printing anything.
 *
 * Program author
 * Name: Nguyen The Long (Long Nguyen)
 * Student number: 151317891
 * UserID: xblong
 * E-Mail: long.nguyen@tuni.fi
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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

/**
 * Define a struct for book information
 * The struct includes:
 * @parameter: author, string: contains the name of the author of the book.
 * @parameter: title, string: contains the title of the book.
 * @parameter: reservations, int: the number of reservations of the book.
 **/
struct Book {
    string author;
    string title;
    int reservations;
};

/**
 * @Function read_books: read the input file and populate a vector of struct
 * Books
 * @parameter: filename, string: containing the name of the input file.
 * Return a vector containing an amount of struct Books, each containing the
 * content of a seperate book.
 * */
map<string, vector<Book>> read_books(string filename) {
    map<string, vector<Book>> books;
    ifstream infile(filename);
    // check if the file can be opened
    if (!infile.is_open()) {
        // print out error warning if the file cannot be opened
        throw invalid_argument("input file cannot be opened");
    }
    // check if the file is empty
    if (infile.peek() == ifstream::traits_type::eof()) {
        throw invalid_argument("empty field");
    }
    string line;
    // access each line in the input file
    while (getline(infile, line)) {
        try {
            Book book = parse_book(line);
            // using split function to split the line
            vector<string> split_line = split(line, ';');
            // check if line[0] exists in map and input book into vector and
            // input into map
            if (books.find(split_line[0]) == books.end()) {
                vector<Book> book_vector;
                book_vector.push_back(book);
                books.insert({split_line[0], book_vector});
            } else {
                books[split_line[0]].push_back(book);
            }
            // print the errors that occurs during the function process
        } catch (invalid_argument &e) {
            throw invalid_argument(e);
        }
    }
    return books;
}

// Define the main function
int main() {
    cout << "Input file: ";
    string filename;
    // get the filename from the user
    getline(cin, filename);
    map<string, vector<Book>> books;
    // Using the function to read the file
    try {
        books = read_books(filename);
        // print errors defined in the functions
    } catch (invalid_argument &e) {
        cout << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return check_command(books);
}
