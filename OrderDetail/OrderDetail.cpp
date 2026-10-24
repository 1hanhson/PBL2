#include <iostream>
#include <limits>
#include <sstream>
#include "OrderDetail.h"
using namespace std;

OrderDetail::OrderDetail(){
    this->OrderID = "";
    this->ShoesID = "";
    this->Quantity = 0;
    this->UnitPrice = 0;
}

OrderDetail::OrderDetail(const string& OrderID, const string& ShoesID,
                         const int& Quantity, const long long& UnitPrice){
    this->OrderID = OrderID;
    this->ShoesID = ShoesID;
    this->Quantity = Quantity;
    this->UnitPrice = UnitPrice;
}

void OrderDetail::Input(){
    cout << "Order ID: ";
    getline(cin >> ws, this->OrderID);

    cout << "Shoes ID: ";
    getline(cin, this->ShoesID);

    cout << "Quantity: ";
    cin >> this->Quantity;

    cout << "Unit Price: ";
    cin >> this->UnitPrice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void OrderDetail::Output() const{
    cout << "Order ID: " << this->OrderID << endl;
    cout << "Shoes ID: " << this->ShoesID << endl;
    cout << "Quantity: " << this->Quantity << endl;
    cout << "Unit Price: " << this->UnitPrice << endl;
    cout << "Sub Total: " << this->GetSubTotal() << endl;
    cout << endl;
}

long long OrderDetail::GetSubTotal() const{
    return (long long)this->Quantity * this->UnitPrice;
}

string OrderDetail::ToLine() const{
    return this->OrderID + " " + this->ShoesID + " " +
           to_string(this->Quantity) + " " + to_string(this->UnitPrice);
}

bool OrderDetail::FromLine(const string& line, OrderDetail& d){
    stringstream ss(line);
    string order, shoes;
    int quantity;
    long long price;
    ss >> order >> shoes >> quantity >> price;
    if(ss.fail())
        return false;
    d = OrderDetail(order, shoes, quantity, price);
    return true;
}

string OrderDetail::GetOrderID() const{
    return this->OrderID;
}

string OrderDetail::GetShoesID() const{
    return this->ShoesID;
}

int OrderDetail::GetQuantity() const{
    return this->Quantity;
}

long long OrderDetail::GetUnitPrice() const{
    return this->UnitPrice;
}

void OrderDetail::SetOrderID(const string& OrderID){
    this->OrderID = OrderID;
}

void OrderDetail::SetShoesID(const string& ShoesID){
    this->ShoesID = ShoesID;
}

void OrderDetail::SetQuantity(const int& Quantity){
    this->Quantity = Quantity;
}

void OrderDetail::SetUnitPrice(const long long& UnitPrice){
    this->UnitPrice = UnitPrice;
}