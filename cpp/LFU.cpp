#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

namespace ns1
{
    class LFUCache
    {
    public:
        LFUCache(unsigned long long cap) : capacity(cap) { minFreq = 0; }

        int get(int key)
        {
            if (keyToVal.find(key) != keyToVal.cend())
            {
                increaseFreq(key);
                return keyToVal[key];
            }
            return -1;
        }

        void put(int key, int value)
        {
            if (capacity <= 0)
                return;

            if (keyToVal.find(key) != keyToVal.cend())
            {
                keyToVal[key] = value;
                increaseFreq(key);
                return;
            }

            if (capacity <= keyToVal.size())
                removeMinFreqKey();

            keyToVal[key] = value;
            keyToFreq[key] = 1;
            freqToKeys[1].insert(key);
            minFreq = 1;
        }

    private:
        unsigned long long capacity; // 缓存容量
        unordered_map<int, int> keyToVal;
        unordered_map<int, int> keyToFreq;
        unordered_map<int, set<int>> freqToKeys;
        int minFreq;

        void removeMinFreqKey()
        {
            set<int> &keyList = freqToKeys[minFreq];
            int deletedKey = *keyList.rbegin();
            keyList.erase(deletedKey);
            /*
            if(keyList.empty())
                freqToKeys[minFreq].clear();
            */

            keyToVal.erase(deletedKey);
            keyToFreq.erase(deletedKey);
        }

        void increaseFreq(int key)
        {
            int freq = keyToFreq[key];
            keyToFreq[key] += 1;
            freqToKeys[freq].erase(key);
            freqToKeys[freq + 1].insert(key);
            if (freqToKeys[freq].empty())
            {
                // freqToKeys[freq].clear();
                if (freq == minFreq)
                    minFreq += 1;
            }
            // cout<<minFreq<<endl;
            // cout<<*freqToKeys[minFreq].begin()<<endl;
        }
    };
}

namespace ns2
{

    class LFUCache
    {
    public:
        LFUCache(unsigned long long cap) : capacity(cap) { minFreq = 0; }

        int get(int key)
        {
            if (mapData.find(key) == mapData.end())
                return -1;

            increaseFreq(key);
            return mapData[key].first;
        }

        void put(int key, int value)
        {
            if (capacity <= 0)
                return;

            if (mapData.find(key) != mapData.end())
            {
                // int tmp = mapData[key].second;
                // mapData[key] = make_pair(value, tmp);
                mapData[key].first = value;
                increaseFreq(key);
                return;
            }

            if (capacity <= mapData.size())
                removeMinFreqKey();

            mapData.insert(make_pair(key, make_pair(value, 1)));
            count_sort[1].push_back(key);
            minFreq = 1;

            // if(mapData.size() < capacity){
            //	mapData.insert(make_pair(key, make_pair(value, 0)));
            // }else{
            //	for(unordered_map<int, list<int>>::iterator it = count_sort.begin(); it != count_sort.end(); it++){
            //		if(!it->second.empty()){
            //			int topNum = it->second.front();
            //			it->second.pop_front();
            //			mapData.erase(topNum);
            //			mapData.insert(make_pair(key, make_pair(value, 0)));
            //			break;
            //		}
            //	}
            // }
            // increaseFreq(key);
        }

        // 统一更新访问次数
        void increaseFreq(int key)
        {
            list<int>::iterator it = find(count_sort[mapData[key].second].begin(), count_sort[mapData[key].second].end(), key);
            if (it != count_sort[mapData[key].second].end())
                count_sort[mapData[key].second].erase(it);
            mapData[key].second++;
            count_sort[mapData[key].second].push_back(key);
        }
        void removeMinFreqKey()
        {
            //
            // set<int> &keyList = freqToKeys[minFreq];
            // int deletedKey = *keyList.rbegin();
            // keyList.erase(deletedKey);
            // keyToVal.erase(deletedKey);
            // keyToFreq.erase(deletedKey);
            //
        }

    private:
        unordered_map<int, list<int>> count_sort; // frequency,key of mapData
        int capacity;
        unordered_map<int, pair<int, int>> mapData; // key,value,count
        int minFreq;
    };
}

namespace ns3
{

    class Node
    {
    public:
        Node *next, *prev;
        Node(int k, int v) : key(k), value(v)
        {
            next = NULL;
            prev = NULL;
        }
        int getKey()
        {
            return key;
        }
        int getValue()
        {
            return value;
        }

    private:
        int key;
        int value;
    };

    class DoubleList
    {
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

    private:
        Node *head, *tail;
        int size;
    };

    class LinkedHashSet
    {
    };

    class LFUCache
    {
    public:
        LFUCache(int c) : cap(c) {}
        ~LFUCache()
        {
            removeAll();
        }
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

    private:
        int cap;
        map<int, int> keyToVal;
        map<int, int> keyToFreq;

        map<int, LinkedHashSet *> freqToKeys;
        int minFreq;
        DoubleList cache;
        map<int, Node *> nodeMap;
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
    };
}

int main()
{
#if 0
        ns1::LFUCache cache(2);

        cache.put(1, 10);
        cache.put(2, 20);
        cout<<cache.get(1)<<endl;

        cache.put(3, 30);
        cout<<cache.get(2)<<endl;

        cache.put(2, 120);
        cout<<cache.get(2)<<endl;
#endif

#if 0
    ns2::LFUCache cache(3);
    cache.put(2, 2);
    cache.put(1, 1);
    cout << cache.get(2) <<",";
    cout << cache.get(1) << ",";
    cout << cache.get(2) << ",";
    cache.put(3, 3);
    cache.put(4, 4);
    cout << cache.get(3) << ",";
    cout << cache.get(2) << ",";
    cout << cache.get(1) << ",";
    cout << cache.get(4) << endl;
#endif

#if 0
    ns3::LFUCache cache(2);

        cache.put(1, 10);
        cache.put(2, 20);
        cout << cache.get(1) << endl;

        cache.put(3, 30);
        cout << cache.get(2) << endl;
#endif

    cout << "over\n";
    return 0;
}
