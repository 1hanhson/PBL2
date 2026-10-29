#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H
#include "QueueO.h"

class OrderManager{
    private:
        QueueO Q;
        HashTableO Hash;

    public:
        OrderManager();
        ~OrderManager();
        OrderManager(const OrderManager&) = delete;
        OrderManager& operator=(const OrderManager&) = delete;
        bool Insert(const Order&);
        void Show() const;
        void ShowHistory() const;
        NodeO* Search(const string&);
        bool Delete(NodeO*);
        bool ProcessNext(Order&);

        int GetPendingCount() const;
        int GetTotalCount() const;
        bool SaveToFile(const string&) const;
        int LoadFromFile(const string&);
};

#endif
