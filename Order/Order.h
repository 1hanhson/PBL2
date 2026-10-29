#ifndef ORDER_H
#define ORDER_H
#include <string>
using namespace std;
namespace OrderStatus {
    const string Pending   = "Cho xu ly";
    const string Processed = "Da xu ly";
    const string Cancelled = "Da huy";
}

class Order{
    private:
        string OrderID;
        string CustomerID;
        string OrderDate;
        string Status;
        long long TotalAmount;

    public:
        Order();
        Order(const string&, const string&, const string&,
              const string&, const long long&);

        void Input();
        void Output() const;

        string GetOrderID() const;
        string GetCustomerID() const;
        string GetOrderDate() const;
        string GetStatus() const;
        long long GetTotalAmount() const;

        void SetOrderID(const string&);
        void SetCustomerID(const string&);
        void SetOrderDate(const string&);
        void SetStatus(const string&);
        void SetTotalAmount(const long long&);
        
        string ToLine() const;
        static bool FromLine(const string&, Order&);
};

#endif