#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <algorithm>

// *****************************
// 1.1 Unique character string
// *****************************
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

// *****************************
// 1.2 Check permutation
// *****************************

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

// *****************************
// 1.3 Urlify
// *****************************

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

// *****************************
// 1.4 Permutation of palindrome
// *****************************

// Using hashmap
bool isPermutationOfPalindrome(std::string a_str)
{
    // Property of a palindrome: At most one character appears an odd number of times
    std::transform(a_str.begin(), a_str.end(), a_str.begin(), ::tolower);
    std::map<char, int> counts;
    for (char c : a_str)
    {
        if (c == ' ') { continue; }
        counts[c]++;
    }
    
    int oddCount = 0;
    for (auto const& entry : counts)
    {
        if (entry.second % 2 != 0) { oddCount++; } 
        if (oddCount > 1) { return false; }
    }
    
    return true;
}

// Using bit vector
bool isPermutationOfPalindrome2(std::string a_str)
{   
    std::transform(a_str.begin(), a_str.end(), a_str.begin(), ::tolower);
    std::bitset<26> counts;
    for (char c : a_str)
    {
        if (c == ' ') { continue; }
        counts.flip(c - 'a');
    }
        
    return counts.count() <= 1;
}

void problem1_4()
{
    std::cout << std::boolalpha;
    std::cout << isPermutationOfPalindrome2("Tact Coa") << std::endl; // true
    std::cout << isPermutationOfPalindrome2("abba") << std::endl; // true
    std::cout << isPermutationOfPalindrome2("abbae") << std::endl; // true
    std::cout << isPermutationOfPalindrome2("abbefa") << std::endl; // false
    std::cout << isPermutationOfPalindrome2("abbaa") << std::endl; // true
    std::cout << isPermutationOfPalindrome2("abbaab") << std::endl; // false
}

// *****************************
// 1.5 One edit away
// *****************************

bool isOneReplaceAway(std::string a_s1, std::string a_s2)
{
    bool foundDiff = false;
    for (int i = 0; i < a_s1.length(); ++i)
    {
        if (a_s1[i] != a_s2[i]) 
        {
            if (foundDiff) { return false; }
            foundDiff = true;
        }
    }
    
    return true;
}

// Check if s2 can be converted to s1 with one insert
bool isOneInsertAway(std::string a_s1, std::string a_s2)
{
    int diff = 0, i = 0, j = 0;
    while (i < a_s1.length() && j < a_s2.length())
    {
        if (a_s1[i] != a_s2[j])
        {
            diff++;
            i++;
        }
        else
        {
            i++;
            j++;
        }
    }
    
    return diff <= 1;
}

bool isOneEditAway(std::string a_s1, std::string a_s2)
{
    if (a_s1 == a_s2) return true;
    if (abs(a_s1.length() - a_s2.length()) > 1) return false;
    
    if (a_s1.length() == a_s2.length())     { return isOneReplaceAway(a_s1, a_s2); }
    else if (a_s1.length() > a_s2.length()) { return isOneInsertAway(a_s1, a_s2);  }
    else                                    { return isOneInsertAway(a_s2, a_s1);  }
}

void problem1_5()
{
    std::cout << std::boolalpha;
    std::cout << isOneEditAway("", "") << std::endl; // true
    std::cout << isOneEditAway("p", "") << std::endl; // true
    std::cout << isOneEditAway("", "p") << std::endl; // true
    std::cout << isOneEditAway("p", "b") << std::endl; // true
    std::cout << isOneEditAway("", "bb") << std::endl; // false
    std::cout << isOneEditAway("p", "bb") << std::endl; // false
    std::cout << isOneEditAway("pp", "bb") << std::endl; // false
}

// *****************************
// 1.6 String compression
// *****************************

std::string compress(const std::string& a_str)
{
    if (a_str == "") { return a_str; }
    
    std::ostringstream oss;
    oss << a_str[0];
    int count = 1;
    
    for (unsigned int i = 1; i < a_str.length(); ++i)
    {
        if (a_str[i-1] == a_str[i])
        {
            count++;
        }
        else
        {
            oss << count;
            oss << a_str[i];
            count = 1;
        }
    }
    
    oss << count;
    std::string result = oss.str();
    return result.length() < a_str.length() ? result : a_str;
}

void problem1_6()
{
    std::cout << compress("aabcccccaaa") << std::endl; // a2b1c5a3
    std::cout << compress("") << std::endl; // ""
    std::cout << compress("a") << std::endl; // "a"
    std::cout << compress("aa") << std::endl; // "aa"
    std::cout << compress("aabb") << std::endl; // "aabb"
    std::cout << compress("aabbb") << std::endl; // "a2b3"
    assert((compress("aabcccccaaa") != "a2b1c5a3")); 
}

// *****************************
// 1.7 Matrix rotation
// *****************************

// On 90 degree rotation, 
// m[1][1] -> m[1][N], m[2][1] -> m[1][N-1], m[3][1] -> m[1][N-2], ... ,m[N][1] -> m[1][1]
// m[1][2] -> m[2][N], m[1][3] -> m[3][N]
// In the general case, m[i][j] -> m[j][N-i+1]
// Also, we can look at this as a cyclic roll of four elements, e.g.:
// { m[1][1], m[1][N], m[N][N], m[N][1] }
// { m[1][2], m[2][N], m[N][N-1], M[N-1][1] }
// { m[2][2], m[2][N-1], m[N-1][N-1], m[N-1][2] }
// { m[3][2], m[2][N-2], m[N-2][N-1], m[N-1][3]
// Or in the general case, m[i][j], m[j][N-i-1], m[N-i-1][N-j-1], m[N-j-1][i]
void cycleRotate(int&a, int& b, int& c, int& d)
{
    int temp = a;
    a = d;
    d = c;
    c = b;
    b = temp;
}

void rotate(int** m, int N)
{
    for (int i = 0; i < N/2; i++)
    {
        for (int j = 0; j < (N + 1)/2; j++)
        {
            cycleRotate(m[i][j], m[j][N-i-1], m[N-i-1][N-j-1], m[N-j-1][i]);
        }
    }
}

void printMatrix(int** m, int N)
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            std::cout << m[i][j] << ",";
        }
        std::cout << std::endl;
    }
            
}

void problem1_7()
{
    static const int N = 5;
    int **m;
    m = new int*[N];
    for (int i = 0; i < N; ++i)
    {
        m[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            m[i][j] = 10 * (i + 1) + (j + 1);
        }
    }
    
    printMatrix(m, N);
    rotate(m, N);
    std::cout << "Rotated:" << std::endl;
    printMatrix(m, N);
    
    // Cleanup memory
    for (int i = 0; i < N; ++i)
    {
        delete[] m[i];
    }
    delete[] m;
}

// *****************************
// 1.8 Matrix rotation
// *****************************

static const int N = 5;

void zero(int** m)
{
    std::bitset<N> rowContainsZero;
    std::bitset<N> colContainsZero;
    
    for(int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (m[i][j] == 0)
            {
                rowContainsZero.set(i);
                colContainsZero.set(j);
            }
        }
    }
    
    for(int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (rowContainsZero[i] | colContainsZero[j])
            {
                m[i][j] = 0;
            }
        }
    }
}

void printMatrix(int** m)
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            std::cout << m[i][j] << ",";
        }
        std::cout << std::endl;
    }
            
}

void problem1_8()
{
    int **m;
    m = new int*[N];
    for (int i = 0; i < N; ++i)
    {
        m[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            m[i][j] = 10 * (i + 1) + (j + 1);
        }
    }
    m[2][3] = 0;
    
    printMatrix(m);
    zero(m);
    std::cout << "Zeroed:" << std::endl;
    printMatrix(m);

    for (int i = 0; i < N; ++i)
    {
        delete[] m[i];
    }
    delete[] m;
}

int main()
{

}
