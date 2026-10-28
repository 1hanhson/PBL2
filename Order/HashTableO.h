#ifndef HASH_TABLE_O_H
#define HASH_TABLE_O_H
#include "NodeO.h"
#include <iostream>
using namespace std;

class HashTableO{
    private:
        NodeO** Table;
        int M;

        int HashFunction(const string& ID) const;

    public:
        HashTableO(const int& = 101);
        ~HashTableO();
        HashTableO(const HashTableO&) = delete;
        HashTableO& operator=(const HashTableO&) = delete;

        bool Insert(NodeO*);
        NodeO* Search(const string&) const;
        bool Delete(NodeO*);

        friend class OrderManager;
};

#endif