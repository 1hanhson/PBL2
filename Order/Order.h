
#include <string>
using namespace std;

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
};
