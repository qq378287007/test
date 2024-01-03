#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

namespace ns1
{
    int dp(const unordered_set<int> &coins, int n)
    {
        if (n < 0)
            return -1;
        if (n == 0)
            return 0;
        int res = INT_MAX;
        for (int coin : coins)
        {
            int subproblem = dp(coins, n - coin);
            if (subproblem == -1)
                continue;
            res = min(res, 1 + subproblem);
        }
        return res == INT_MAX ? -1 : res;
    }
    int coinChange(const unordered_set<int> &coins, int amount)
    {
        return dp(coins, amount);
    }
}

namespace ns2
{
    int dp(const unordered_set<int> &coins, int n, unordered_map<int, int> &memo)
    {
        if (n < 0)
            return -1;
        if (n == 0)
            return 0;
        if (memo.find(n) != memo.end())
            return memo[n];
        int res = INT_MAX;
        for (int coin : coins)
        {
            int subproblem = dp(coins, n - coin, memo);
            if (subproblem == -1)
                continue;
            res = min(res, 1 + subproblem);
        }
        memo[n] = res == INT_MAX ? -1 : res;
        return memo[n];
    }
    int coinChange(const unordered_set<int> &coins, int amount)
    {
        unordered_map<int, int> memo;
        return dp(coins, amount, memo);
    }
}

namespace ns3
{
    int coinChange(const unordered_set<int> &coins, int amount)
    {
        if (amount < 0)
            return -1;
        if (amount == 0)
            return 0;
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (int coin : coins)
            {
                if (i - coin < 0)
                    continue;
                dp[i] = min(dp[i], 1 + dp[i - coin]);
            }
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
}

int main()
{
    cout << "Over!\n";
    return 0;
}