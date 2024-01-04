#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;

namespace ns1
{
    struct Node
    {
        int key;
        int value;
        Node *next{nullptr};
        Node *prev{nullptr};
        Node(int k = 0, int v = 0) : key(k), value(v) {}
        int getKey() const { return key; }
        int getValue() const { return value; }
    };

    class DoubleList
    {
        Node *head;
        Node *tail;
        int size;

    public:
        DoubleList()
        {
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head->next = tail;
            tail->prev = head;
            size = 0;
        }
        void addLast(Node *x)
        {
            x->prev = tail->prev;
            x->next = tail;
            tail->prev->next = x;
            tail->prev = x;
            size++;
        }
        Node *remove(Node *x)
        {
            x->prev->next = x->next;
            x->next->prev = x->prev;
            size--;
            return x;
        }
        Node *removeFirst()
        {
            if (head->next == tail)
                return NULL;
            return remove(head->next);
        }
        int getSize()
        {
            return size;
        }
        void removeAll()
        {
            Node *x;
            while ((x = removeFirst()) != NULL)
            {
                delete x;
                x = NULL;
            }
        }
    };

    class LRUCache
    {
        int cap;
        DoubleList cache;
        unordered_map<int, Node *> nodeMap;

    private:
        void makeRecently(int k)
        {
            Node *x = nodeMap[k];
            cache.remove(x);
            cache.addLast(x);
        }
        void addRecently(int k, int v)
        {
            Node *x = new Node(k, v);
            cache.addLast(x);
            nodeMap[k] = x;
        }
        void deleteKey(int k)
        {
            Node *x = nodeMap[k];
            cache.remove(x);
            nodeMap.erase(k);
            delete x;
            x = NULL;
        }
        void removeLeastRecently()
        {
            Node *x = cache.removeFirst();
            int k = x->getKey();
            nodeMap.erase(k);
            delete x;
            x = NULL;
        }
        void removeAll()
        {
            while (!nodeMap.empty())
                removeLeastRecently();
        }

    public:
        LRUCache(int c) : cap(c) {}
        ~LRUCache() { removeAll(); }
        void put(int key, int value)
        {
            if (nodeMap.count(key) == 1)
            {
                deleteKey(key);
                addRecently(key, value);
                return;
            }

            if (cap == cache.getSize())
                removeLeastRecently();

            addRecently(key, value);
        }
        int get(int key)
        {
            if (nodeMap.count(key) == 0)
                return -1;
            makeRecently(key);
            return nodeMap[key]->getValue();
        }
    };
}
namespace ns2
{
    struct Node
    {
        int key;
        int val;
        Node(int k = 0, int v = 0) : key(k), val(v) {}
    };

    class LRUCache
    {
        size_t cap;
        list<Node *> cache;
        unordered_map<int, Node *> nodeMap;

    private:
        void makeRecently(int key)
        {
            Node *x = nodeMap[key];
            cache.remove(x);
            cache.push_front(x);
        }
        void addRecently(int key, int val)
        {
            Node *x = new Node(key, val);
            cache.push_front(x);
            nodeMap[key] = x;
        }
        void deleteKey(int key)
        {
            Node *x = nodeMap[key];
            cache.remove(x);
            nodeMap.erase(key);
            delete x;
        }
        void removeLeastRecently()
        {
            Node *x = cache.back();
            cache.pop_back();
            nodeMap.erase(x->key);
            delete x;
        }
        void removeAll()
        {
            while (cache.size())
                removeLeastRecently();
        }

    public:
        LRUCache(size_t c) : cap(c) {}
        ~LRUCache() { removeAll(); }
        int get(int key)
        {
            if (!nodeMap.count(key))
                return -1;

            makeRecently(key);
            return nodeMap[key]->val;
        }
        void put(int key, int val)
        {
            if (nodeMap.count(key))
                deleteKey(key);
            if (cap == cache.size())
                removeLeastRecently();
            addRecently(key, val);
        }
    };
}

namespace ns3
{
    class LRUCache
    {
        size_t capacity;                                       // 缓存容量
        list<pair<int, int>> cl;                               // 存储对应的key和value
        unordered_map<int, list<pair<int, int>>::iterator> cm; // 存储key和对应链表节点位置
    public:
        LRUCache(size_t cap = 10) : capacity(cap) {}
        int get(int key)
        {
            if (cm.count(key)) // 存在
            {
                pair<int, int> p = *cm[key];
                cl.erase(cm[key]); // 更新节点位置
                cl.push_front(p);
                cm[key] = cl.begin(); // 更新哈希表节点位置记录
                return p.second;      // 返回值
            }
            return -1;
        }
        void put(int key, int value)
        {
            if (cm.find(key) != cm.end()) // 存在
            {
                cl.erase(cm[key]);           // 更新节点位置
                cl.push_front({key, value}); // 更新节点值
                cm[key] = cl.begin();        // 更新值
                return;
            }
            if (cl.size() == capacity)
            {
                cm.erase(cl.back().first); // 删除哈希表记录
                cl.pop_back();             // 删除最近最少访问节点
            }
            cl.push_front(make_pair(key, value)); // 添加新节点
            cm.insert({key, cl.begin()});         // 添加哈希表记录
        }
    };
}
/*
namespace ns4
{
    template <typename T, typename V>
    class LRUCache
    {
        typename pair<T, V> p;
        //typedef list<pair<T, V>>::iterator it;
        size_t capacity;                                       // 缓存容量
        list<pair<T, V>> cl;                               // 存储对应的key和value
        unordered_map<T, list<p>::iterator> cm; // 存储key和对应链表节点位置
    public:
        LRUCache(size_t cap = 10) : capacity(cap) {}
        V get(T key)
        {
            if (cm.count(key)) // 存在
            {
                pair<T, V> p = *cm[key];
                cl.erase(cm[key]); // 更新节点位置
                cl.push_front(p);
                cm[key] = cl.begin(); // 更新哈希表节点位置记录
                return p.second;      // 返回值
            }
            return V{};
        }
        void put(T key, V value)
        {
            if (cm.find(key) != cm.end()) // 存在
            {
                cl.erase(cm[key]);           // 更新节点位置
                cl.push_front({key, value}); // 更新节点值
                cm[key] = cl.begin();        // 更新值
                return;
            }
            if (cl.size() == capacity)
            {
                cm.erase(cl.back().first); // 删除哈希表记录
                cl.pop_back();             // 删除最近最少访问节点
            }
            cl.push_front(make_pair(key, value)); // 添加新节点
            cm.insert({key, cl.begin()});         // 添加哈希表记录
        }
    };
}
*/
int main()
{
#if 1
    ns2::LRUCache cache(2);
    cache.put(1, 1);
    cout << cache.get(1) << endl;

    cache.put(3, 3);
    cout << cache.get(2) << endl;

    cache.put(1, 4);
    cout << cache.get(1) << endl;
#endif

#if 0
    ns3::LRUCache cache(2);

    cache.put(1, 1);
    cout << cache.get(1) << endl;

    cache.put(3, 3);
    cout << cache.get(2) << endl;

    cache.put(1, 4);
    cout << cache.get(1) << endl;
#endif
    cout << "over\n";
    return 0;
}