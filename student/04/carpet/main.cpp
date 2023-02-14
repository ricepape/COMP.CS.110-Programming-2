/* Mystery carpet
 *
 * Desc:
 *   This program implements a mystery carpet applying pattern matching.
 * The carpet consists of squares of different colors, which also holds
 * true for the pattern, but the size of the pattern is always 2 x 2, i.e.
 * it has four colored squares. The program searches for pattern
 * occurrences from the carpet.
 *   At first, the program asks for the size of the carpet (width and heigth).
 * The user is also asked for if the carpet (grid) will be filled with
 * randomly drawn colors, or with user-given ones. In the first option,
 * a seed value for the random number generator will be asked next.
 * In the latter option,  the user is asked to input as many colors as the
 * there are squares in the carpet, whereupon the user lists the first
 * letters of the colors as one long string.
 *   On each round, the user is asked for a pattern to be searched for
 * (a string consisting of four letters/colors). The program prints, how
 * many occurrences was found and from which coordinates they were found.
 *   The program checks if the user-given colors are among accepted ones.
 * The program terminates when the user gives a quitting command ('q' or 'Q').
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
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
using Pattern = vector<char>;

// Declare the color used in the carpet
enum Color{R,G,B,Y,W,Error};

using Enumtype = vector<Color>;

int main() {

  int width, height;
  string input, command;
  Pattern Data;
  Enumtype Carpet;

  if (!read_numbers(width, height)) {
    cout << "Error: Carpet cannot be smaller than pattern.";
    return EXIT_FAILURE;
  }
  read_command(command, width, height, Data, Carpet);

  while (read_input(input) != "Q")
    find_square(input, width, Data);

  return EXIT_SUCCESS;
}


