#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

namespace ns1
{
    struct TreeNode
    {
        TreeNode *left;
        TreeNode *right;
    };
    int minDepth(TreeNode *root)
    {
        if (root = nullptr)
            return 0;
        int depth = 1;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            const int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                if (node->left == nullptr && node->right == nullptr)
                    return depth;
                if (node->left != nullptr)
                    q.push(node->left);
                if (node->right != nullptr)
                    q.push(node->right);
            }
            depth++;
        }
        return depth;
    }
}

namespace ns2
{
    string plusOne(const string &s, int j)
    {
        string ch(s);
        if (ch[j] == '9')
            ch[j] = '0';
        else
            ch[j] += 1;
        return ch;
    }
    string minusOne(const string &s, int j)
    {
        string ch(s);
        if (ch[j] == '0')
            ch[j] = '9';
        else
            ch[j] -= 1;
        return ch;
    }

    int BFS(const string &target, const string &init, unordered_set<string> &deads)
    {
        queue<string> q;
        q.push(init);

        int depth = 0;
        while (!q.empty())
        {
            const int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                string cur = q.front();
                q.pop();
                deads.insert(cur);

                if (cur == target)
                    return depth;

                for (int j = 0; j < 4; j++)
                {
                    string up = plusOne(cur, j);
                    if (deads.find(up) == deads.cend())
                        q.push(up);
                }
                for (int j = 0; j < 4; j++)
                {
                    string down = minusOne(cur, j);
                    if (deads.count(down) == 0)
                        q.push(down);
                }
            }
            depth++;
        }
        return -1;
    }
}

namespace ns3
{
    string plusOne(const string &s, int j)
    {
        string ch(s);
        if (ch[j] == '9')
            ch[j] = '0';
        else
            ch[j] += 1;
        return ch;
    }
    string minusOne(const string &s, int j)
    {
        string ch(s);
        if (ch[j] == '0')
            ch[j] = '9';
        else
            ch[j] -= 1;
        return ch;
    }

    int BFS(const string &target, const string &init, unordered_set<string> &deads)
    {
        unordered_set<string> s1;
        s1.insert(init);

        unordered_set<string> s2;
        s2.insert(target);

        int depth = 0;
        while (!s1.empty() && !s2.empty())
        {
            if (s1.size() > s2.size())
                swap(s1, s2);

            unordered_set<string> tmp;
            for (const string &cur : s1)
            {
                if (s2.count(cur) > 0)
                    return depth;
                deads.insert(cur);

                for (int j = 0; j < 4; j++)
                {
                    string up = plusOne(cur, j);
                    if (deads.find(up) == deads.cend())
                        tmp.insert(up);
                }
                for (int j = 0; j < 4; j++)
                {
                    string down = minusOne(cur, j);
                    if (deads.count(down) == 0)
                        tmp.insert(down);
                }
            }
            swap(s1, tmp);

            depth++;
        }
        return -1;
    }
}

int main()
{
    string str = "123";

    str[2] += 2;

    cout << str << endl;
    cout << "Over!\n";
    return 0;
}