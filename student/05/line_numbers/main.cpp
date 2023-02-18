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
            ofstream output;
            output.open(output_filename);
            while ( getline(file_object, line) ) {
                new_line+=to_string(count);
                new_line.append(" ");
                new_line.append(line);
                new_line+='\n';
                output << new_line;
                new_line="";
                count+=1;
            }
            output.close();
            file_object.close();

        }

}
