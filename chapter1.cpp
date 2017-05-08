#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <algorithm>

bool problem1_1allUniqueCharactersHashMap(const std::string& a_str)
{
    std::map<char, bool> count;
    for(char c : a_str)
    {
        if (count[c]) { return false; }
        count[c] = true;
    }
    
    return true;
}

bool problem1_1_allUniqueCharactersSort(std::string a_str)
{
    std::sort(a_str.begin(), a_str.end());

    for (unsigned int i = 0; i < a_str.length() - 1; ++i)
    {
        if (a_str[i] == a_str[i + 1]) { return false; }    
    }
    
    return true;
}

void problem1_1()
{
    // Hashmap version
    std::cout << allUniqueCharactersHashMap("heldo") << std::endl;
    std::cout << allUniqueCharactersHashMap("hello world") << std::endl;
    // Sort version
    std::cout << allUniqueCharactersSort("heldo") << std::endl;
    std::cout << allUniqueCharactersSort("hello world") << std::endl;
}

bool checkPermutation(std::string s1, std::string s2)
{
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    
    return s1 == s2;
}

void problem1_2()
{
    // Hashmap version
    std::cout << std::boolalpha;
    std::cout << checkPermutation("hello", "lleho") << std::endl;
    std::cout << checkPermutation("hello", "hell") << std::endl;
}

void urlify(std::string& a_str, int a_len)
{
    int copyFrom = a_len - 1;
    int copyTo = a_str.length() - 1;
    
    while(copyFrom >= 0 && copyTo >= 0)
    {
        if (a_str[copyFrom] == ' ')
        {
            a_str[copyTo--] = '0';
            a_str[copyTo--] = '2';
            a_str[copyTo--] = '%';
        }
        else
        {
            a_str[copyTo--] = a_str[copyFrom];
        }
        copyFrom--;
    }
}

void problem1_3()
{
    std::string str = "Mr John Smith    ";
    urlify(str, 13);
    std::cout << str << std::endl;
}

int main()
{

}
