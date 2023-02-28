#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  // Add your implementation here
     if (s.length() == 0)
         return false;
     else
          {
                int t=0;
                int u = s.length()-1;
                if (s.at(t)==s.at(u))
                {
                    s=s.erase(u,1);
                    s=s.erase(t,1);
                    //std::cout << s <<std::endl;
                    //std::cout << s.length() <<std::endl;
                    if (s.length() == 1 or s.length () ==0)
                      return true;
                    else
                       return palindrome_recursive(s);
                }
                else
                    return false;

}}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
