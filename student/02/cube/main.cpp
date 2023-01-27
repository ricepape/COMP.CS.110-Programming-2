#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int number = 0;
    cin >> number;

    int triple = pow(number,3);
    if (number>-1) {
        if (triple<number) {
            cout << "Error! The cube of " << number << " is not " << triple << " ." << endl;
        }
    else if (number<0){
        if (triple>number) {
            cout << "Error! The cube of " << number << " is not " << triple << " ." << endl;
    }}
    else {cout << "The cube of " << number << " is " << triple << " ." << endl;}
}
    return 0;
}
