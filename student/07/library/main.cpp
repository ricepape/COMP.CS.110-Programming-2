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
 * @Function split: split a line of content into parts with a delimiter.
 * @parameter: s, string: containing the string content that needs to be
 *splitted.
 * @parameter: delimiter, const char: the delimiter that seperate contents in
 * the line
 * @parameter: ignore_empty, bool: denoted as a flag to skip adding empty parts.
 * Return a vector of splitted contents
 **/
std::vector<std::string> split(const std::string &s, const char delimiter,
                               bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;
    // create the loop to find the delimiter in the string
    while (tmp.find(delimiter) != std::string::npos) {
        // assign the content seperated by the delimeter, from the start to the
        // point the delimiter into another parameter.
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        // delete the assigned part in the main string content
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        // check if the new_part is empty
        if (!(ignore_empty and new_part.empty())) {
            // assign into the vector
            result.push_back(new_part);
        }
    }
    // After all the delimiters has been deleted in the string, check if there
    // are any contents left in the string. If yes then add the remaining as an
    // element into the string
    if (!(ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}

/**
 * @Function parse_book: parse a line containing different
 * contents from the input file into a book struct.
 * @parameter: line, string: Containing each row in the input file as a string.
 * Return the struct Book containing the splitted input file contents into
 * categories.
 * */
Book parse_book(string line) {
    // split parts of the line and assign into the vector fields.
    vector<string> fields = split(line, ';');

    // Check if the number of elements of the vector, which comes from the
    // line in the file, is correct according to initial requirements, which
    // is 4.
    if (fields.size() != 4) {
        // Print error as empty field
        throw invalid_argument("empty field");
    }

    // Check if the elements in the vector are empty or not.
    for (const auto &word : fields) {
        if (word.empty()) {
            throw invalid_argument("empty field");
        }
    }

    Book book;
    // Assign the splitted values of each line in the file data
    // into the Book elements
    book.author = fields[1];
    book.title = fields[2];
    if (fields[3] == "on-the-shelf") {
        book.reservations = 0;
    } else {
        // Turns the value from the file into integers, and assign it.
        book.reservations = stoi(fields[3]);
    }
    return book;
}

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

/**
 * @Function check_command: the function serves at the interfaces of the
 * program, where it receives the command from the user, and analyse the
 * command.
 * @parameter: books, map<string, vector<Book>>: a map containing the library
 * name as the key, and the struct Book as its elements The function returns the
 * results according to the command of the user. In case there is an unknown
 * command, the function prints an error warning. The function quits when the
 * user put in the "quit" command, and quit the whole program.
 * */
int check_command(map<string, vector<Book>> books) {
    while (true) {
        string command;
        cout << "lib> ";
        // Getting the command from the user
        getline(std::cin, command);
        // Using split function to split the command
        vector<string> words = split(command, ' ');
        // Consider the cases of the command given
        // If the command received is "quit"
        //  There must be only 1 word "quit" in the command.
        //  If there are any other words after that, the command is considered
        //  as unknown.
        if (words.at(0) == "quit" && words.size() == 1)
            // Exit the program successfully
            break;
        // Command printing all the libraries
        else if (command == "libraries") {
            print_libraries(books);
            // Command priting all the books in the input library
            // There must be 2 words in the command: material + "name of
            // library" If there are any other words after that or words are
            // missing, the command is considered as unknown.
        } else if (words.size() == 2 && words.at(0) == "material") {
            print_material(books, words.at(1));
            // Command priting all the books of an author in a library, both
            // input by the user There must be only 3 words in the command:
            // books + "name of library"
            // + "name of author"
            // If there are any other words after that or words are missing, the
            // command is considered as unknown.
        } else if (words.at(0) == "books") {
            if (words.size() == 3)
                print_books(books, words.at(1), words.at(2));
            else
                cout << "Error: wrong number of parameters" << endl;
            // Command priting the reservation of a book and all the libraries
            // contains the books, which the name of the book and the name of
            // the author is given by the user There must be at least 3 words in
            // the command: reservable + "name of author"
            // + "name of book". The name of book can be longer than 1 word
        } else if (words.size() >= 3 && words.at(0) == "reservable") {
            if (words.size() >= 3) {
                std::string combined;
                // Combining all the words which is the name of the book
                for (size_t i = 2; i < words.size(); ++i) {
                    combined += words[i] + " ";
                }
                // Delete the seperated words which is the name of the book,
                // leaving only the first word.
                combined.pop_back();
                size_t pos = combined.find("\"");
                while (pos != std::string::npos) {
                    combined.erase(pos, 1);
                    pos = combined.find("\"", pos);
                }
                // replace the first word with the whole and complete name
                // of the book after combined.
                std::replace(words.begin(), words.end(), words[2], combined);
            }
            print_reservable(books, words.at(1), words.at(2));
            // Command priting all the books are on the shelf in all the
            // libraries.
        } else if (words.size() == 1 && words.at(0) == "loanable") {
            print_loanable(books);
        } else
            cout << "Error: unknown command" << endl;
    }
    return EXIT_SUCCESS;
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
