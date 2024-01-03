#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
using namespace std;

int main()
{
#if 0
    int n = 7, m = 8;
    vector<int> nums_1;
    vector<int> nums_2(n);       // n个，默认值为0
    vector<int> nums_3{1, 3, 5}; // 3个
    vector<int> nums_4(n, 2);    // n个，默认值为2
    vector<vector<int>> dp_1;
    vector<vector<bool>> dp_2(m, vector<bool>(n, true)); // m*n个，默认值为true
    //empty
    //size
    //back, front
    //insert, erase
    //emplace_back, pop_back
#endif

#if 0
    string s;
    //size
    //empty
    //push_back, pop_back
    //substr
#endif

#if 0
    unordered_map<string, vector<int>> mapping;

    vector<int> nums{1, 1, 3, 4, 5, 3, 6};
    unordered_map<int, int> counter;
    for (int num : nums)
    {
        //if (!counter.count(num))
        //    counter[num] = 0;
        counter[num]++; // 若key不存在则自动创建，val为默认值
    }
    for (const pair<int, int> &it : counter)
    {
        int key = it.first;
        int val = it.second;
        cout << key << ": " << val << endl;
    }
    // size
    // empty
    // count
    // erase
#endif

#if 0
    unordered_set<int> visited;
    // size
    // empty
    // count
    // erase
    // insert
#endif

#if 1
    queue<int> q;
    // size
    // empty
    // push
    // front, back
    // pop
#endif

#if 1
    stack<int> stk;
    // size
    // empty
    // push
    // top
    // pop
#endif



    cout << "Over!\n";
    return 0;
}