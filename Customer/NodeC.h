#ifndef NODE_C_H
#define NODE_C_H
#include "Customer.h"

class NodeC{
    private:
        Customer data;
        NodeC* Next;
        NodeC* Previous;

        // HashTable
        NodeC* NextHash;

    public:
        NodeC();
        NodeC(const Customer&);

        friend class CustomerManager;
        friend class HashTableC;
};

#endif