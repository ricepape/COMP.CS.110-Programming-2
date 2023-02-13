#include <iostream>
#include <string>
#include <vector>


std::vector< std::string > split (std::string line, char separator, bool value = false){
        std::vector< std::string > string_no_empty;
        std::vector< std::string > string_with_empty;
        std::string part;
        int string_length= line.size();
        for (int i=0; (i < string_length);i++){
            if (line[i]==separator){
                string_no_empty.push_back(part);
                string_with_empty.push_back(part);
                string_with_empty.push_back("");
                part="";
            } else{
                part.push_back(line[i]);
            }
        }
        if (value==true){
            return string_no_empty;
        } else return string_with_empty;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
