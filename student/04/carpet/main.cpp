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
 * Student number:
 * UserID:
 * E-Mail: thi.vu@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
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
    {
        return R;
    }
    else if (name == 'G')
    {
        return G;
    }
    else if (name == 'B')
    {
        return B;
    }
    else if (name == 'Y')
    {
        return Y;
    }
    else if (name == 'W')
    {
        return W;
    }
    else
    {
        return Error;
    }
}

const vector<string> ENUM_TO_COLOR = {"R", "G", "B", "Y", "W"};

bool read_numbers(int &width, int &height)
{
    cout << "Enter carpet's width and height: ";
    cin >> width;
    cin >> height;
    return width >= 2 and height >= 2;
}

bool checkString(std::string s)
{
    for (int i = 0; i <= int(s.length()) - 1; i++)
    {
        // cout << i <<endl;
        string a(1, s[i]);
        if (find(ENUM_TO_COLOR.begin(), ENUM_TO_COLOR.end(), a) == ENUM_TO_COLOR.end())
        {
            return false;
        }
    }
    return true;
}

string read_input(string &input, int width, int height, Pattern Data)
{
    cout << "Enter 4 colors, or q to quit: ";
    cin >> input;
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    if (input == "Q")
    {
        return input;
    }
    if (input.length() != 4)
    {
        cout << " Error: Wrong amount of colors." << endl;
        return read_input(input, width, height, Data);
    }
    else if (!checkString(input))
    {
        cout << " Error: Unknown color." << endl;
        return read_input(input, width, height, Data);
    }
    return input;
}

void find_square(string input, int width, Pattern Data)
{
    int count = 0;
    for (int i = 1; i < int(Data.size()) - width; i++)
    {
        if (Data.at(i - 1) == input.at(0) && Data.at(i) == input.at(1) && input.at(2) == Data.at((i - 1 + width)) && input.at(3) == Data.at((i + width)))
        {
            cout << " - Found at (" << i % width << ", " << i / width + 1 << ")" << endl;
            count++;
        }
    }
    cout << " = Matches found: " << count << endl;
}

void print_pattern(int width, Enumtype Carpet)
{
    for (int i = 1; i <= int(Carpet.size()); i++)
    {
        if (i % width == 0)
            cout << " " << ENUM_TO_COLOR.at(Carpet.at(i - 1)) << endl;
        else
            cout << " " << ENUM_TO_COLOR.at(Carpet.at(i - 1));
    }
}

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
        key.append((ENUM_TO_COLOR.at(u)));
    }
    return key;
}

void convert_string_to_vector(Pattern &Data, string initial, Enumtype &Carpet)
{
    for (int i = 0; i < int(initial.length()); i++)
    {
        Data.push_back(initial[i]);
        Carpet.push_back(string_to_color(initial[i]));
    }
}

void read_command(string &command, int width, int height, Pattern &Data, Enumtype &Carpet)
{
    string initial;
    int seed;

    cout << "Select start (R for random, I for input): ";
    cin >> command;

    // upercase the string
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    if (command == "I")
    {
        cout << "Input: ";
        cin >> initial;
        if (int(initial.length()) != width * height)
        {
            cout << " Error: Wrong amount of colors." << endl;
            return read_command(command, width, height, Data, Carpet);
        }
        if (!checkString(initial))
        {
            cout << " Error: Unknown color." << endl;
            return read_command(command, width, height, Data, Carpet);
        }
    }
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

int main()
{
    int width;
    int height;
    string input;
    string command;
    Pattern Data = {};
    Enumtype Carpet = {};
    // read and check given numbers
    if (!read_numbers(width, height))
    {
        cout << "Error: Carpet cannot be smaller than pattern.";
        return EXIT_FAILURE;
    }
    read_command(command, width, height, Data, Carpet);

    while (true)
    {
        if (read_input(input, width, height, Data) == "Q")
            break;
        find_square(input, width, Data);
    }

    return EXIT_SUCCESS;
}
