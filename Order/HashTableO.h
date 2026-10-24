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

        bool Insert(NodeO*);
        NodeO* Search(const string&) const;
        bool Delete(NodeO*);

        friend class OrderManager;
};