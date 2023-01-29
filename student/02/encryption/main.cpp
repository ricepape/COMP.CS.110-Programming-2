#include <iostream>
#include <cctype>

using namespace std;

int main()
{
    cout << "Enter the encryption key: ";
    string encrypt;
    getline(cin,encrypt);
    string::size_type len = encrypt.length();
    int k=0;

    if (len==26) {
                while (k<26){

                    char letter = encrypt.at(k);
                    if (isupper(letter)){

                        cout <<"Error! The encryption key must contain only lower case characters."<<endl;
                        return EXIT_FAILURE;
                    }
                    k+=1;
                }
                for( char letter1 = 'a'; (letter1 < 'z'); ++letter1 ){
                    string::size_type count = encrypt.find(letter1,0);
                       if (count==string::npos){
                            cout <<"Error! The encryption key must contain all alphabets a-z."<<endl;
                            return EXIT_FAILURE;
                    }}

                 }
    else {
        cout <<"Error! The encryption key must contain 26 characters."<<endl;
        return EXIT_FAILURE;
    }
    cout << "Enter the text to be encrypted: " ;
    string encrypted;
    getline(cin,encrypted);
    int len2 = encrypted.length();
    int l=0;
    int x=0;
    while (x<len2){

        char letter = encrypted.at(k);
        if (isupper(letter)){
            cout <<"Error! The text to be encrypted must contain only lower case characters."<<endl;
            return EXIT_FAILURE;
        }
        k+=1;
    }
    string new_line;
    while (l<len2){
        int ascii_value_of_ch = static_cast<int>(encrypted.at(l));
        new_line+=encrypt.at(ascii_value_of_ch-97);
        l++;
    }
    cout << "Encrypted text: " <<new_line <<endl;




    return 0;
}
