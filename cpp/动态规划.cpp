#include <iostream>
#include <vector>
using namespace std;

namespace ns1
{
    int fib(int N)
    {
        if (N <= 0)
            return 0;
        if (N == 1 || N == 2)
            return 1;
        return fib(N - 1) + fib(N - 2);
    }
}

namespace ns2
{
    int helper(vector<int> &memo, int n)
    {
        if (n == 1 || n == 2)
            return 1;
        if (memo[n] == 0)
            memo[n] = helper(memo, n - 1) + helper(memo, n - 2);
        return memo[n];
    }

    int fib(int N)
    {
        if (N <= 0)
            return 0;
        if (N == 1 || N == 2)
            return 1;
        vector<int> memo(N + 1, 0);
        return helper(memo, N);
    }
}

namespace ns3
{
    int fib(int N)
    {
        if (N <= 0)
            return 0;
        if (N == 1 || N == 2)
            return 1;
        vector<int> dp(N + 1, 0);
        dp[2] = dp[1] = 1;
        for (int i = 3; i <= N; i++)
            dp[i] = dp[i - 1] + dp[i - 2];
        return dp[N];
    }
}
namespace ns4
{
    int fib(int N)
    {
        if (N <= 0)
            return 0;
        if (N == 1 || N == 2)
            return 1;
        int prev = 1, curr = 1;
        for (int i = 3; i <= N; i++)
        {
            int sum = prev + curr;
            prev = curr;
            curr = sum;
        }
        return curr;
    }
}

int main()
{

    cout << "Over!\n";
    return 0;
}