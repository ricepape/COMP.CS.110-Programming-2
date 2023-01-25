#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int number = 0;
    cin >> number;
    if (number < 1) {
        cout <<"Only positive numbers accepted" << endl;
    } else {
        int factor1 = 0;
        int factor2 = 0;
        int root = sqrt(number);
        int k = 1;
        while (k <= root){
            int remainder = number % k;
            if (remainder < 1){
                factor1 = k;
                factor2 = number / k;
            }
            k+=1;
        }
        cout << number <<" = "<< factor1 <<" * "<< factor2 << endl;


}
    return 0;
}
