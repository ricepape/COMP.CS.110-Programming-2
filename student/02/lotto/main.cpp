#include <iostream>

using namespace std;

unsigned long int multiply(int number)
{
    unsigned long int total=1;
    int t=1;
    while (t<=number)
    {total=total*t;
        t+=1;
    }
    return total;
}

int main()
{
    cout << "Enter the total number of lottery balls: ";
    int lottery=0;
    cin >> lottery;
    cout << "Enter the number of drawn balls: ";
    int drawn=0;
    cin >> drawn;
    if (lottery<1){
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    } else if (drawn > lottery){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    } else {
        int different_combinations= 0;
        different_combinations= multiply(lottery)/(multiply(lottery-drawn)*multiply(drawn));
        cout <<"The probability of guessing all " << drawn <<" balls correctly is 1/" <<different_combinations << endl;
    }


    return 0;
}
