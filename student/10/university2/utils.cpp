/* Utils
 * Utils: provides the utility function split,
 * as well as a few other utility functions for later use in the program.
 *
 * The source code file of Utils includes:
 *   @Function split: split a line of content into parts with a delimiter.
 *   @Function is_empty: check if the content put in is empty
 *   @Function is_numeric: check if the content put in is numeric
 *   @Function numeric_part: extract a sequence of digits from the input string
 *   @Function to_lower: returns a new string that is the lowercase version
 *
 * Notes about the program and it's implementation (if any):
 * All already implemented
 *
 * */


#include "utils.hh"


/**
 * @Function split: split a line of content into parts with a delimiter.
 * @parameter: s, string: containing the string content that needs to be
 * splitted.
 * @parameter: delimiter, const char: the delimiter that seperate contents in
 * the line
 **/
std::vector<std::string> Utils::split(const std::string& str, char delim)
{
    std::vector<std::string> result = {""};
    bool insideQuotation = false;
    for ( char currentChar : str )
    {
        if ( currentChar == '"' )
        {
            insideQuotation = not insideQuotation;
        }
        else if ( currentChar == delim and not insideQuotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(currentChar);
        }
    }
    return result;
}

/**
 * @Function is_empty: check if the content put in is empty
 * @parameter: str, string: containing the string content that needs to be
 * checked.
 * @return true if the string is empty, false otherwise
 **/
bool Utils::is_empty(const std::string &str)
{
    for ( char ch : str )
    {
        if ( ch != ' ' )
        {
            return false;
        }
    }
    return true;
}


/**
 * @Function is_numeric: check if the content put in is numeric
 * @parameter: s, string: containing the string content that needs to be
 * checked.
 * @return true if the string is empty, false otherwise
 **/
bool Utils::is_numeric(const std::string& s)
{
    for ( unsigned int i = 0; i < s.size(); ++i )
    {
        if( not isdigit(s.at(i)) )
        {
            return false;
        }
    }
    return true;
}

/**
 * @Function numeric_part: extract a sequence of digits from the input string
 * @parameter: s, string: containing the string content that needs to be
 * checked.
 * @return integer of the numeric part
 **/
int Utils::numeric_part(const std::string &s)
{
    std::string num = "";
    for ( unsigned int i = 0; i < s.size(); ++i )
    {
        while ( i < s.size() and isdigit(s.at(i)) )
        {
            num += s.at(i);
            ++i;
        }
    }
    if ( num == "" )
    {
        return 0;
    }
    else
    {
        return stoi(num);
    }
}

/**
 * @Function to_lower: returns a new string that is the lowercase version
 * @parameter: s, string: containing the string content that needs to be
 * lowered
 **/
std::string Utils::to_lower(const std::string &s)
{
    std::string result = "";
    for ( unsigned int i = 0; i < s.size(); ++i )
    {
        result += tolower(s.at(i));
    }
    return result;
}

