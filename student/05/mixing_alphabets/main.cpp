#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }
        if (word.length()>2){
            char first_letter=word[0];
            char last_letter=word.back();
            word=word.substr(1,word.length()-2);
            shuffle(word.begin(), word.end(), generator);
            word=first_letter+word+last_letter;
        }
        std::cout << word << std::endl;
    }
}
