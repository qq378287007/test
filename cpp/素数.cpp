#include <cmath>
#include <cassert>
#include <vector>
using namespace std;

namespace ns1
{
    bool isPrime(int n)
    {
        assert(n > 1);
        const int number = sqrt(n);
        for (int i = 2; i <= number; i++)
            if (n % i == 0)
                return false;
        return true;
    }

    int countPrimes(int n)
    {
        int count = 0;
        for (int i = 2; i <= n; i++)
            if (isPrime(i))
                count++;
        return count;
    }
}

namespace ns2
{
    int countPrimes2(int n)
    {
        if (n < 2)
            return 0;

        const int number = sqrt(n);
        vector<bool> isPrime(n + 1, true);
        for (int i = 2; i <= number; i++)
            if (isPrime[i])
                for (int j = i * i; j <= n; j += i)
                    isPrime[j] = false;

        int count = 0;
        for (int i = 2; i <= n; i++)
            if (isPrime[i])
                count++;
        return count;
    }
}