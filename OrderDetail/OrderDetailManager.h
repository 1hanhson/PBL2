#ifndef ORDER_DETAIL_MANAGER_H
#define ORDER_DETAIL_MANAGER_H
#include "NodeOD.h"

class OrderDetailManager{
    private:
        NodeOD* pL;
        int Nod;//number of order details
    public:
        OrderDetailManager();
        ~OrderDetailManager();
        OrderDetailManager(const OrderDetailManager&) = delete;
        OrderDetailManager& operator=(const OrderDetailManager&) = delete;

        bool Insert(const OrderDetail&, NodeOD* = NULL);
        void Show();
        int ShowByOrder(const string&);

        NodeOD* Search(const string&, const string&);
        bool Delete(NodeOD*);
        int DeleteByOrder(const string&);

        int GetCount();
        int CountByOrder(const string&);
        long long TotalByOrder(const string&);

        bool SaveToFile(const string&);
        int LoadFromFile(const string&);
};

#endif