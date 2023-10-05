// optimised solution
// DS used : Linked Lists and HashMaps
//-----------------------------------
//           CONSIDERATIONS
//-----------------------------------
//start of LL (ater head) Most recent element
//End of LL(before tail) Least used element

#include <bits/stdc++.h>
using namespace std;

class Cache
{
public:
    int cap;
    // int size;

    virtual int evict_key_and_return(){}; // virtual [keyword] : compulsory for derived classes to implement
    virtual int get(int key){};
    virtual void put(int key, int value){};
};

class LRUcache : public Cache
{
public:
    class node
    {
    public:
        int key;
        int val;
        node *next;
        node *prev;

        node(int _key, int _value)
        {
            key = _key;
            val = _value;
        }
    };
    node *head = new node(-1, -1);
    node *tail = new node(-1, -1);

    unordered_map<int, node *> mp;
    LRUcache(int _capacity)
    {
        cap = _capacity;
        mp.clear();
        head->next = tail;
        tail->prev = head;
    }
    void addnode(node *newnode)
    {
        node *temp = head->next;
        newnode->next = temp;
        newnode->prev = head;
        head->next = newnode;
        temp->prev = newnode;
    }
    void deletenode(node *delnode)
    {
        node *delprev = delnode->prev;
        node *delnext = delnode->next;

        delprev->next = delnext;
        delnext->prev = delprev;
    }

    int evict_key_and_return()
    {
        int x = tail->prev->key;
        mp.erase(tail->prev->key);
        deletenode(tail->prev);

        return x;
    }

    int get(int key_)
    {
        if (mp.find(key_) != mp.end())
        {
            node *foundnode = mp[key_];
            int found = foundnode->val;
            mp.erase(key_);
            deletenode(foundnode);
            addnode(foundnode);

            mp[key_] = head->next;
            return found;
        }

        return -1;
    }

    void put(int key_, int value_)
    {
        if (mp.find(key_) != mp.end())
        {
            node *existingnode = mp[key_];
            mp.erase(key_);
            deletenode(existingnode);
        }
        if (mp.size() == cap)
        {
            evict_key_and_return();
        }

        addnode(new node(key_, value_));
        mp[key_] = head->next;
    }
};

int main()
{

    LRUcache lr = LRUcache(3);
    cout << lr.get(1) << endl;
    lr.put(-3, 5);
    lr.put(1, 4);
    lr.put(1, 7);
    cout << lr.get(1) << endl;
    lr.put(45, 1);
    lr.put(7, 1);
    cout << lr.get(-3) << endl;
    cout << lr.get(7) << endl;
    assert(1 == lr.get(45));

    return 0;
}
