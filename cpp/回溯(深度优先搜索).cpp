#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

namespace ns1
{
    void backtrack(const vector<int> &nums, vector<int> &path, vector<vector<int>> &res)
    {
        const int n = nums.size();
        if (path.size() == n)
        {
            res.emplace_back(path);
            return;
        }
        for (int i = 0; i < n; i++)
        {
            const int value = nums[i];
            if (find(path.cbegin(), path.cend(), value) != path.cend())
                continue;

            path.emplace_back(value);
            backtrack(nums, path, res);
            path.pop_back();
        }
    }
    vector<vector<int>> permute(const vector<int> &nums)
    {
        vector<int> path;
        vector<vector<int>> res;
        backtrack(nums, path, res);
        return res;
    }
}

namespace ns2
{
    bool isValid(const vector<string> &board, int row, int col)
    {
        const int n = board.size();
        for (int i = row - 1; i >= 0; i--)
            if (board[i][col] == 'Q')
                return false;
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q')
                return false;
        for (int i = row - 1, j = col + 1; i >= 0 && j <= n - 1; i--, j++)
            if (board[i][j] == 'Q')
                return false;
        return true;
    }
    void backtrack(vector<string> &board, int row, vector<vector<string>> &res)
    {
        const int n = board.size();
        if (row == n)
        {
            res.emplace_back(board);
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if (!isValid(board, row, col))
                continue;

            board[row][col] = 'Q';
            backtrack(board, row + 1, res);
            board[row][col] = '.';
        }
    }
    vector<vector<string>> permute(int n)
    {
        vector<string> board(n, string(n, '.'));
        vector<vector<string>> res;
        backtrack(board, 0, res);
        return res;
    }
}

int main()
{
    cout << ns1::permute({1, 2, 3, 4}).size() << endl;
    cout << ns2::permute(8).size() << endl;
    cout << "Over!\n";
    return 0;
}