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
        StockTransactionManager(const StockTransactionManager&) = delete;
        StockTransactionManager& operator=(const StockTransactionManager&) = delete;

        bool Add(const StockTransaction&);
        int GetCount() const;
        void Show() const;
        StockTransaction* Search(const string&);
        int ShowByType(const string&) const;
        int ShowByShoe(const string&) const;
        int ShowByDate(const string&) const;
        void ShowMaxToMin() const;
        int CountByType(const string&) const;
        int TotalQuantityByType(const string&) const;
        int NetQuantityByShoe(const string&) const;
        long long TotalValueByType(const string&) const;
        bool SaveToFile(const string&) const;
        int LoadFromFile(const string&);
};

#endif