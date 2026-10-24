#ifndef STOCK_TRANSACTION_MANAGER_H
#define STOCK_TRANSACTION_MANAGER_H
#include "StockTransaction.h"

class StockTransactionManager{
    private:
        StockTransaction *List;
        int Size;
        int Capacity;
        void Grow();
    public:
        StockTransactionManager(const int& = 100);
        ~StockTransactionManager();
        int Add(const StockTransaction&);
        int GetCount();
        void Show();
        StockTransaction* Search(const string&);
        int ShowByType(const string&);
        int ShowByShoe(const string&);
        int ShowByDate(const string&);
        void ShowMaxToMin();
        int CountByType(const string&);
        int TotalQuantityByType(const string&);
        int NetQuantityByShoe(const string&);
        long long TotalValueByType(const string&);
        int SaveToFile(const string&);
        int LoadFromFile(const string&);
};

#endif