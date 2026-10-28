#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H
#include "HashTableC.h"

class CustomerManager{
    private:
        NodeC* pL;
        int Noc;
        HashTableC Hash;

    public:
        CustomerManager();
        ~CustomerManager();
        CustomerManager(const CustomerManager&) = delete;
        CustomerManager& operator=(const CustomerManager&) = delete;

        bool Insert(const Customer&, NodeC* = NULL);
        void Show();

        NodeC* Search(const string&);
        bool Delete(NodeC*);
        bool Update(const string&, const Customer&);

        friend class HashTableC;
};

#endif
