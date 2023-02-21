#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#define max 8

using namespace std;

string strings[max];

void split (string str, char seperator)
{
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= int (str.length()))
    {
        if (str[i] == seperator || i == int (str.length()))
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            strings[currIndex] = subStr;
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
        }
}

int main()
{
    string filename = "";
    cout << "Input file: ";
    getline(cin,filename);


    ifstream file_object(filename);
        if ( not file_object ) {
            cout << "Error! The file " << filename << " cannot be opened." << endl;
            return EXIT_FAILURE;
        } else {
            string line;
            map<string, int> dictionary_points;
            while ( getline(file_object, line) ) {
                split (line,':');
                int points= stoi(strings[1]);
                if(dictionary_points.find(strings[0])!=dictionary_points.end()){
                    dictionary_points.at(strings[0])+=points;
                } else{
                    dictionary_points.insert({strings[0],points});
                }
            }
           cout << "Final scores:" << endl;
           for(const auto& elem : dictionary_points)
           {
              std::cout << elem.first << ": " << elem.second << "\n";
           }
            }

            file_object.close();
            return EXIT_SUCCESS;

 }
