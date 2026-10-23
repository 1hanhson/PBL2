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
        int Add(const Payment&);
        int GetCount();
        void Show();
        Payment* Search(const string&);
        int ShowByStatus(const string&);
        int ShowByDate(const string&);
        void ShowMaxToMin();
        int CountByStatus(const string&);
        long long TotalRevenue();
        long long RevenueByMethod(const string&);
        long long RevenueByDate(const string&);
        int SaveToFile(const string&);
        int LoadFromFile(const string&);
};
 
#endif