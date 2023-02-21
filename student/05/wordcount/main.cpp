#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <map>
#include <set>
#include <vector>
using namespace std;
using split_string = vector<string>;
split_string split(const string &line,const char sep, bool ignore_empty = false)
{
    split_string parts = {};
    string word = "";
    for (char c:line)
    {
        if (c == sep)
        {
            if (!(word.empty()&&ignore_empty))
            {
                parts.push_back(word);
            }
            word.clear();
        }
        else {
            word +=c;
        }
    }
    parts.push_back(word);
    return parts;
}
void print_word_data(pair<string,set<int>> const &word)
{
    int total_row_number = word.second.size();
    cout <<word.first << ' ' << total_row_number << ":";
    for (set<int>::iterator iter = word.second.begin();iter!= word.second.end();iter++)
    {
        cout << ' ' << *iter;
        if (++iter != word.second.end())
        {
            cout << ',';
        }
        iter--;
    }
}
int main()
{
    string filename = "";
    cout << "Input file: ";
    getline(cin, filename);

    ifstream file_object(filename);
    if ( not file_object )
    {
        cout << "Error! The file " << filename <<" cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        string line;
        int line_counter = 1;
        vector<string> line_words;
        map<string, set<int>> words;
        vector<string>::iterator words_iter;
        //map<string,int>::iterator iter;
        while (getline(file_object,line))
        {
            line_words = split(line, ' ', true);
            words_iter = line_words.begin();
            while (words_iter != line_words.end())
            {
                if(words.find(*words_iter) == words.end())
                {
                    words.insert({*words_iter, {}});
                }
                words.at(*words_iter).insert(line_counter);
                ++words_iter;

            }
        ++line_counter;
        }
        for (pair<string,set<int>> const &word_data:words)
        {
            print_word_data(word_data);
            cout << endl;
         }
        file_object.close();
        return EXIT_SUCCESS;
    }



}
