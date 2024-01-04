#include <vector>
using namespace std;

namespace ns1
{
    int getMax(const vector<int> &piles)
    {
        int value = 0;
        for (int n : piles)
            value = max(value, n);
        return value;
    }

    // 每小时speed速度吃n个香蕉，需要小时数
    // 向上取整
    int timeOf(int n, int speed) { return n / speed + (n % speed == 0 ? 0 : 1); }

    // 每小时speed速度吃一堆香蕉，需要小时数
    size_t usedTime(const vector<int> &piles, int speed)
    {
        size_t time = 0;
        for (int n : piles)
            time += timeOf(n, speed);
        return time;
    }

    // H小时内吃完piles堆香蕉，最少速度是多少（每小时至少吃多少个香蕉）
    // 每小时最多吃一堆香蕉，
    int minEatintSpeed(const vector<int> piles, size_t H)
    {
        size_t sz = piles.size();
        if (sz == 0 || H < sz)
            return 0;

        int left = 1;
        int right = getMax(piles);
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            size_t time = usedTime(piles, mid);
            if (time <= H)
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
}

namespace ns2
{
    int getMax(const vector<int> &weight)
    {
        int value = 0;
        for (int n : weight)
            value = max(value, n);
        return value;
    }

    int getSum(const vector<int> &weight)
    {
        int value = 0;
        for (int n : weight)
            value += n;
        return value;
    }

    size_t usedTime(const vector<int> &weight, int cap)
    {
        size_t time = 0;
        int value = 0;
        for (int n : weight)
        {
            value += n;
            if (value >= cap)
            {
                if (value == cap)
                    value = 0;
                else
                    value = n;
                time++;
            }
        }
        if (value > 0)
            time++;
        return time;
    }

    // D天内按序运输货物weight，求每天最低运载能力
    // 货物不开分割
    int shipWidthinDays(const vector<int> &weight, size_t D)
    {
        if (0 == D || 0 == weight.size())
            return 0;

        int left = getMax(weight);
        int right = getSum(weight);
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            size_t time = usedTime(weight, mid);
            if (time <= D)
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
}