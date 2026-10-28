#ifndef PAYMENT_MANAGER_H
#define PAYMENT_MANAGER_H
#include "Payment.h"
 
class PaymentManager{
    private:
        Payment *List;
        int Size;
        int Capacity;
        void Grow();
    public:
        PaymentManager(const int& = 100);
        ~PaymentManager();
        PaymentManager(const PaymentManager&) = delete;
        PaymentManager& operator=(const PaymentManager&) = delete;

        bool Add(const Payment&);
        int GetCount() const;
        void Show() const;
        Payment* Search(const string&);
        int ShowByStatus(const string&) const;
        int ShowByDate(const string&) const;
        void ShowMaxToMin() const;
        int CountByStatus(const string&) const;
        long long TotalRevenue() const;
        long long RevenueByMethod(const string&) const;
        long long RevenueByDate(const string&) const;
        bool SaveToFile(const string&) const;
        int LoadFromFile(const string&);
};
 
#endif