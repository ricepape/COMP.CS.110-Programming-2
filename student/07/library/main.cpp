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
 * If the user input has an error, the program prints the relevant error message,
 * and after that, returns to waiting for user input.
 * When the user enters "quit", the program terminates with the return value
 * EXIT_SUCCESS without printing anything.
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
#include <sstream>
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
* @parameter: s, string: containing the string content that needs to be splitted.
* @parameter: delimiter, const char: the delimiter that seperate contents in
* the line
* @parameter: ignore_empty, bool: denoted as a flag to skip adding empty parts.
* Return a vector of splitted contents
*
**/
std::vector<std::string> split(const std::string &s, const char delimiter,
                               bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;
    //create the loop to find the delimiter in the string
    while (tmp.find(delimiter) != std::string::npos) {
        //assign the content seperated by the delimeter, from the start to the
        //point the delimiter into another parameter.
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        //delete the assigned part in the main string content
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        //check if the new_part is empty
        if (not(ignore_empty and new_part.empty())) {
            //assign into the vector
            result.push_back(new_part);
        }
    }
    //After all the delimiters has been deleted in the string, check if there are
    //any contents left in the string. If yes then add the remaining as an element
    //into the string
    if (not(ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


/**
 * @Function parse_book: parse a line containing different
 * contents from the input file into a book struct.
 * @parameter: line, string: Containing each row in the input file as a string.
 * Return the struct Book containing the splitted input file contents into categories.
 * */
Book parse_book(string line) {
    stringstream ss(line);
    string field;
    vector<string> fields;
    //split parts of the line and assign into the vector fields.
    while (getline(ss, field, ';')) {
        fields.push_back(field);
    }
    //Check if the number of elements of the vector, which comes from the
    //line in the file, is correct according to initial requirements, which is 4.
    if (fields.size() != 4) {
        //Print error as empty field
        throw invalid_argument("empty field");
    }
    Book book;
    // Assign the splitted values of each line in the file data
    // into the Book elements
    book.author = fields[1];
    book.title = fields[2];
    if (fields[3] == "on-the-shelf") {
        book.reservations = 0;
    } else {
        //Turns the value from the file into integers, and assign it.
        book.reservations = stoi(fields[3]);
    }
    return book;
}


/**
 * @Function read_books: read the input file and populate a vector of struct Books
 * @parameter: filename, string: containing the name of the input file.
 * Return a vector containing an amount of struct Books, each containing the content
 * of a seperate book.
 * */
map<string, vector<Book>> read_books(string filename) {
    map<string, vector<Book>> books;
    ifstream infile(filename);
    // check if the file can be opened
    if (!infile.is_open()) {
        // print out error warning if the file cannot be opened
        throw invalid_argument("input file cannot be opened");
    }
    if ( infile.peek() == std::ifstream::traits_type::eof() )
    {
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

        } catch (invalid_argument &e) {
            throw invalid_argument(e);
        }
    }
    return books;


}
/**
 * @Function sort_vector_by_author: return the true-false value by comparing
 * the "author" field of the book struct of 2 different books.
 * @parameter: a,b, iterator of Book struct: containing two Book struct that the author
 * field needs to be compared. It goes through every element in the map.
 * */
bool sort_vector_by_author(const Book & a,
    const Book & b) {
    return a.author < b.author;
}


/**
 * @Function sort_vector_by_title: return the true-false value by comparing
 * the "title" field of the book struct of 2 different books.
 * @parameter: a,b, iterator of Book struct: containing two Book struct that the title
 * field needs to be compared. It goes through every element in the map.
 *
 * */
bool sort_vector_by_title(const Book & a,
    const Book & b) {
    return a.title < b.title;
}

/**
 * @Function print_material: print the books and their authors in a library given
 * by the user
 * @parameter: books, map<string, vector<Book>>: a map containing
 * @parameter: condition, int: containing the number of the condition, which represents
 * the command of the user
 * @parameter: b, string:
 *
 * */
void print_material(map<string, vector<Book>> books, string b) {
    // Denote a flag for the existance of the library given by user
    bool library_exist = true;
    // Check if the library exists
    for (auto &pair : books) {
        if (pair.first == b) {
            //If there exists the library, the flag would be denoted as false
            library_exist = false;
            break;
        }
    }
    //If the flag stays being true, then the library does not exists in the file
    if (library_exist) {
        //Print error warning
        cout << "Error: unknown library" << endl;
        return;
    }
    for (auto &pair : books) {
        if (pair.first == b) {
            // Using sort_vector_by_author function above
            // to sort the vector ascending
            sort(pair.second.begin(), pair.second.end(), sort_vector_by_author);
            for (const Book &book : pair.second) {
                cout << book.author << ": " << book.title << endl;
            }
        }
        // cout << b << endl;
        // cout << book.author << " " << book.library << " " << book.title << "
        // "<< book.reservations <<endl;
    }
    return;
}
// inherited from if condition == 1 in print_book
void print_libraries(map<string, vector<Book>> books) {
    // libraries
    for (auto &pair : books) {
        cout << pair.first << endl;
    }
    return;
}

// inherited from if condition == 2 in print_book

void print_books(map<string, vector<Book>> books, string b, string c) {
    // books <library> <author>
    map<string, int> book_title;
    bool library_exist = true;
    bool author_exist = true;
    // check library exists
    for (auto &pair : books) {
        if (pair.first == b) {
            library_exist = false;
            break;
        }
    }
    if (library_exist) {
        cout << "Error: unknown library" << endl;
        return;
    }
    // check author exists
    for (auto &pair : books) {
        if (pair.first == b) {
            for (const Book &book : pair.second) {
                if (book.author == c) {
                    author_exist = false;
                    break;
                }
            }
        }
    }

    if (author_exist) {
        cout << "Error: unknown author" << endl;
        return;
    }
    //int i = 0;
    for (auto &pair : books) {
        // count the occurence of book title
        if (pair.first == b) {
            for (const Book &book : pair.second) {
                // make if function above to be if in if function
                if (book.author == c) {
                    if (book_title.find(book.title) == book_title.end()) {
                        book_title.insert({book.title, book.reservations});
                    } else {
                        book_title[book.title] += book.reservations;
                    }
            }
            }
        }
    }
    for (auto &pair : book_title) {
        //i++;
        //cout << i << endl;

        if (pair.second > 0)
            cout << pair.first << " --- " << pair.second << " reservations"
                 << endl;
        else if (pair.second == 0)
            cout << pair.first << " ---"
                 << " on the shelf" << endl;
    }
}
// inherited from if condition == 3 in print_book
void print_reservable(map<string, vector<Book>> books, string b, string c) {
    // reservable <author> <book_name>
    map<string, int> queue;
    vector<string> minlist;
    for (auto &pair : books) {
        // run the for vector of books
        for (const Book &book : pair.second) {
            if (book.author == b && book.title == c) {
                queue.insert({pair.first, book.reservations});
                // continue;
            }
        }
    }

    // check if book in the queue
    if (queue.size() == 0) {
        cout << "Book is not a library book" << endl;
        return;
    }
    // find min value in the map
    auto min_iter = std::min_element(
        queue.begin(), queue.end(),
        [](const auto &a, const auto &b) { return a.second < b.second; });
    for (auto iter = queue.begin(); iter != queue.end(); ++iter) {
        if (iter->second == min_iter->second) {
            minlist.push_back(iter->first);
        }
    }
    if (min_iter->second == 0)
        cout << "on the shelf" << endl;
    else if (min_iter->second > 0 && min_iter->second < 100)
        cout << min_iter->second << " reservations" << endl;
    else {
        cout << "Book is not reservable from any library" << endl;
        return;
    }
    for (auto &pair : minlist) {
        cout << "--- " << pair << endl;
    }
    return;
}
// inherited from if condition == 4 in print_book
void print_loanable(map<string, vector<Book>> books) {
    map<string, vector<string>> list;
    for (auto &pair : books) {
        for (const Book &book : pair.second) {
            if (list.find(pair.first) == list.end() && book.reservations == 0) {
                vector<string> list_of_books;
                list.insert({pair.first, list_of_books});
                list[book.author].push_back(book.title);
            } else {
                if ((std::find(list[book.author].begin(),
                               list[book.author].end(), book.title)) ==
                        list[book.author].end() &&
                    book.reservations == 0) {
                    list[book.author].push_back(book.title);
                }
            }
        }
    }
    for (auto &author : list) {
        sort(author.second.begin(), author.second.end());
        for (auto &title : author.second) {
            cout << author.first << ": " << title << endl;
        }
    }
    return;
}

int check_command(map<string, vector<Book>> books) {
    while (true) {
        string command;
        cout << "lib> ";
        getline(std::cin, command);
        vector<string> words = split(command, ' ');
        if (words.at(0) == "quit" && words.size() == 1)
            break;
        else if (command == "libraries") {
            print_libraries(books);
        } else if (words.size() == 2 && words.at(0) == "material") {
            print_material(books, words.at(1));
        } else if (words.at(0) == "books") {
            if (words.size() == 3)
                print_books(books, words.at(1), words.at(2));
            else
                cout << "Error: wrong number of parameters" << endl;
        } else if (words.size() >= 3 && words.at(0) == "reservable") {
            if (words.size() >= 3) {
                std::string combined;
                for (size_t i = 2; i < words.size(); ++i) {
                    combined += words[i] + " ";
                }
                combined.pop_back();
                size_t pos = combined.find("\"");
                while (pos != std::string::npos) {
                    combined.erase(pos, 1);
                    pos = combined.find("\"", pos);
                }
                std::replace(words.begin(), words.end(), words[2], combined);
            }
            print_reservable(books, words.at(1), words.at(2));
        } else if (words.size() == 1 && words.at(0) == "loanable") {
            print_loanable(books);
        } else
            cout << "Error: unknown command" << endl;
    }
    return EXIT_SUCCESS;
}

// Define the main function
int main() {
    // string filename;
    cout << "Input file: ";
    // cin >> filename;
    string filename;
    getline(cin,filename);
    map < string, vector<Book> > books;
    try {
        books = read_books(filename);
    } catch (invalid_argument & e) {
        cout << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return check_command(books);
}
