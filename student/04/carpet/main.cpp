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

// Return the colors in the enum using the values corresponding
Color string_to_color(char const &name)
{
    if (name == 'R')
        return R;

    else if (name == 'G')
        return G;

    else if (name == 'B')
        return B;

    else if (name == 'Y')
        return Y;

    else if (name == 'W')
        return W;

    else
        return Error;

}

//Declare the vector ENUM_TO_COLOR to call for the colors based on the values created by enum
const vector<string> ENUM_TO_COLOR = {"R", "G", "B", "Y", "W"};

/**
 * @Function read_numbers: Read the numerical values of the carpet (width and height) putting in
 * @parameter: width, int; The width of the carpet
 * @parameter: height, int; The height of the carpet
 * The width and value is typed in, have checked and stores into the parameters above
 * Return true if width and height are greater or equal to 2, false if any else case
 * */
bool read_numbers(int &width, int &height) {

  cout << "Enter carpet's width and height: ";
  cin >> width >> height;
  return width >= 2 && height >= 2;

}

/**
 * @Function checkString: Check if the string contains the right colors as declared
 * @parameter: s, constant_string; The pattern as a string
 * Return true if all colors are declared, return false for any else case.
 * */

bool checkString(const string &s) {
  for (char c : s) {
    string a(1, c);

    //Find if the color typed in exists in the enum COLOR which has been declared.
    if (find(ENUM_TO_COLOR.begin(), ENUM_TO_COLOR.end(), a) ==
        ENUM_TO_COLOR.end()) {
        return false;
    }
  }
  return true;
}

/**
 * @Function read_input: Read the pattern colors as the requirement to find in the carpet
 * @parameter: input, string;
 * After the function, the input pattern that needs to find in the carpet
 * is stored in input
 * return the pattern needs to find as string type
 * */
string read_input(string &input)
{
    cout << "Enter 4 colors, or q to quit: ";
    cin >> input;
    //Upper the input pattern
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    if (input == "Q")
    {
        return input;
    }
    //Check the amount of colors, as the pattern is 2x2, which is 4
    if (input.length() != 4)
    {
        cout << " Error: Wrong amount of colors." << endl;
        return read_input(input);
    }
    //Check if all the input colors is declared.
    else if (!checkString(input))
    {
        cout << " Error: Unknown color." << endl;
        return read_input(input);
    }
    return input;
}


/**
 * @Function find_square: Find the pattern required in the carpet
 * @parameter: input, string; the input pattern that needs to find in the carpet
 * @parameter: width, int; the width of the carpet
 * @parameter: Data, vector<char> Pattern; the created carpet
 * print out the frequency of the pattern in the carpet if any, and its position
 * */
void find_square(string input, int width, Pattern Data)
{
    int count = 0;
    //
    for (size_t i = 1; i < Data.size() - width; i++)
    {
        //Check if each data in a 2x2 pattern part of the carpet is equal to that of the input pattern.
        if (Data.at(i - 1) == input.at(0) && Data.at(i) == input.at(1)
            && input.at(2) == Data.at((i - 1 + width)) && input.at(3) == Data.at((i + width)))

        {//Check the position in column and rows of the data
            cout << " - Found at (" << i % width << ", " << i / width + 1 << ")" << endl;
            count++;
        }
    }
    cout << " = Matches found: " << count << endl;
}

/**
 * @Function print_pattern: Print the carpet created, either by random or input
 * @parameter: width, int; the width of the carpet
 * @parameter: Carpet, vector<Color> Enumtype; the created carpet
 * */
//
void print_pattern(int width, Enumtype Carpet)
{
    for (size_t i = 1; i <= Carpet.size(); i++)
    {
        cout << " " << ENUM_TO_COLOR.at(Carpet.at(i - 1));
        if (i % width == 0)
             cout << endl;
    }
}

/**
 * @Function create_string: Create the carpet in terms of the string,
 * if the user choose to create the carpet randomly
 * @parameter: seed, int; the seed value to create the random carpet
 * @parameter: width, int; the width of the carpet
 * @parameter: height, int; the height of the carpet
 * @parameter: key, string; contain the random carpet
 * return the randomly created carpet as a string - key.
 * */
string create_string(int seed, int width, int height)
{
    string key = "";
    default_random_engine rand_gen;
    if (to_string(seed) == "")
    {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        rand_gen.seed(time(NULL));
    }
    else
    {
        // If the user gave a seed value, use it.
        rand_gen.seed(seed);
    }
    uniform_int_distribution<int> distr(0, 4);
    for (int y = 0; y < width * height; ++y)
    {
        int u = distr(rand_gen);
        //Getting the color with the enum value and the const vector.
        key.append((ENUM_TO_COLOR.at(u)));
    }
    return key;
}




/**
 * @Function read_command: perform various steps in the program, including:
 * - Select the way to create the carpet, either in random or manual
 * - Enter the seed if choosing random, or enter the carpet if choosing manual
 * - Check the input carpet if manual
 * @parameter: Data, vector<char> Pattern; containing the carpet as a vector of letters
 * @parameter: width, int; the width of the carpet
 * @parameter: height, int; the height of the carpet
 * @parameter: Carpet, vector<Color> Enumtype; containing the carpet as a vector of numbers correspond to the enum values
 * @parameter: command, string; storing the command for creating the carpet
 *
 * */
void read_command(string &command, int width, int height, Pattern &Data, Enumtype &Carpet)
{
    string initial;
    int seed;

    cout << "Select start (R for random, I for input): ";
    cin >> command;

    // upercase the string
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    //The user enters the carpet him/herself
    if (command == "I")
    {
        cout << "Input: ";
        cin >> initial;

        //Check if the length of the input carpet is equal to the length given before
        if (int(initial.length()) != width * height)
        {
            cout << " Error: Wrong amount of colors." << endl;
            //Restart the process of entering the carpet
            return read_command(command, width, height, Data, Carpet);
        }

        //Check if the colors in the carpet is declared in enum.
        if (!checkString(initial))
        {
            cout << " Error: Unknown color." << endl;
            return read_command(command, width, height, Data, Carpet);
        }
    }

    //The user choose to create the carpet randomly
    else if (command == "R")
    {
        cout << "Enter a seed value: ";
        cin >> seed;
        initial = create_string(seed, width, height);
    }
    else
        return read_command(command, width, height, Data, Carpet);

    convert_string_to_vector(Data, initial, Carpet);
    print_pattern(width, Carpet);
}


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


