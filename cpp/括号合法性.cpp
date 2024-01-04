#include <string>
using namespace std;

bool isValid(const string &str)
{
    int left = 0;
    for (char c : str)
    {
        if (c == '(')
            left++;
        else if (c == ')')
            left--;
        if (left < 0)
            return false;
    }
    return left == 0;
}