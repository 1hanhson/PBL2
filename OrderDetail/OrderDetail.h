#ifndef ORDER_DETAIL_H
#define ORDER_DETAIL_H

#include <string>
#include <iostream>
using namespace std;

class OrderDetail{
    private:
        string OrderID;     // Ma don hang (khop voi Order::OrderID)
        string ShoesID;     // Ma giay (khop voi Shoes::ID)
        int Quantity;       // So luong mua
        long long UnitPrice;// Don gia tai thoi diem dat hang

    public:
        OrderDetail();
        OrderDetail(const string&, const string&, const int&, const long long&);

        void Input();
        void Output() const;

        // Thanh tien = Quantity * UnitPrice
        long long GetSubTotal() const;

        // Doi thanh 1 dong de luu file, cac truong cach nhau bang dau cach
        string ToLine() const;
        // Doc 1 dong tu file, thieu truong hoac sai so thi tra ve false
        static bool FromLine(const string&, OrderDetail&);

        string GetOrderID() const;
        string GetShoesID() const;
        int GetQuantity() const;
        long long GetUnitPrice() const;

        void SetOrderID(const string&);
        void SetShoesID(const string&);
        void SetQuantity(const int&);
        void SetUnitPrice(const long long&);
};

#endif