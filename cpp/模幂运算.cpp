#include <vector>
using namespace std;

// a^b=a*a^(b-1)，b为奇数
// a^b=(a^(b/2))^2，b为偶数
//(a*b)%k = ((a%k)*(b%k))%k
// a^b%k = (a%k)^b%k

// a^b%k
// b:0-10
int mypow(int a, int b, int k = 1337)
{
    if (b == 0)
        return 1 % k;

    a %= k;
    if (b % 2 == 1)
        return (a * mypow(a, b - 1, k)) % k;

    int sub = mypow(a, b / 2, k);
    return (sub * sub) % k;
}

// a^b%k
int superPow(int a, vector<int> &b, int k)
{
    if (b.empty())
        return 1;

    int last = b.back();
    b.pop_back();

    int part1 = mypow(a, last, k);
    int part2 = mypow(superPow(a, b, k), 10, k);
    return (part1 * part2) % k;
}