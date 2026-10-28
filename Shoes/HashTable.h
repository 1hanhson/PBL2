#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Node.h"

class HashTable{
    private:
        Node **Table;
        int M;
        int HashFunction(const string&) const;
    public:
        HashTable(const int& = 101);
        ~HashTable();
        HashTable(const HashTable&) = delete;
        HashTable& operator=(const HashTable&) = delete;

        bool Insert(Node* p);
        bool Delete(Node* p);
        Node* Search(const string& ID);

        friend class ShoesManager;
};

#endif