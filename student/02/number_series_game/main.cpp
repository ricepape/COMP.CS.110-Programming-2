#include <iostream>

int main()
{
    std::cout << "How many numbers would you like to have? ";
    int number = 0;
    std::cin >> number;
    int k = 1;
    while (k <= number)
    {
        int remain3 = (k % 3);
        int remain7 = (k % 7);
        if (remain3<1) {
            if (remain7<1){
                std::cout <<"zip boing" << std::endl;
            }
            else std::cout << "zip" << std::endl;
        } else if (remain7 < 1) {
            std::cout << "boing" << std::endl;
        } else std::cout << k << std::endl ;
        k+=1;
    }


    return 0;
}
