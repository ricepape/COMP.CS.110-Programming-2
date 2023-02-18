#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string filename = "";
    cout << "Input file: ";
    getline(cin,filename);
    string output_filename = "";
    cout << "Output file: ";
    getline(cin,output_filename);

    ifstream file_object(filename);
        if ( not file_object ) {
            cout << "Error! The file " << filename << " cannot be opened." << endl;
            return EXIT_FAILURE;
        } else {
            int count = 1;
            string line;
            string new_line;
            while ( getline(file_object, line) ) {
                new_line+=count;
                new_line.append(" ");
                new_line.append(line);
                line=new_line;
                ofstream output;
                output.open(output_filename);
                output << new_line;
                new_line="";
                output.close();
            }
            file_object.close();

        }

}
