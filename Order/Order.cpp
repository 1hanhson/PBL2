
#include <iostream>
#include <limits>
#include "Order.h"
using namespace std;

Order::Order(){
    this->OrderID = "";
    this->CustomerID = "";
    this->OrderDate = "";
    this->Status = "";
    this->TotalAmount = 0;
}

Order::Order(const string& OrderID, const string& CustomerID,
             const string& OrderDate, const string& Status,
             const long long& TotalAmount){
    this->OrderID = OrderID;
    this->CustomerID = CustomerID;
    this->OrderDate = OrderDate;
    this->Status = Status;
    this->TotalAmount = TotalAmount;
}

void Order::Input(){
    cout << "Order ID: ";
    getline(cin >> ws, this->OrderID);

    cout << "Customer ID: ";
    getline(cin, this->CustomerID);

    cout << "Order Date: ";
    getline(cin, this->OrderDate);

    cout << "Status: ";
    getline(cin, this->Status);

    cout << "Total Amount: ";
    cin >> this->TotalAmount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Order::Output() const{
    cout << "Order ID: " << this->OrderID << endl;
    cout << "Customer ID: " << this->CustomerID << endl;
    cout << "Order Date: " << this->OrderDate << endl;
    cout << "Status: " << this->Status << endl;
    cout << "Total Amount: " << this->TotalAmount << endl;
}

string Order::GetOrderID() const{
    return this->OrderID;
}

string Order::GetCustomerID() const{
    return this->CustomerID;
}

string Order::GetOrderDate() const{
    return this->OrderDate;
}

string Order::GetStatus() const{
    return this->Status;
}

long long Order::GetTotalAmount() const{
    return this->TotalAmount;
}

void Order::SetOrderID(const string& OrderID){
    this->OrderID = OrderID;
}

void Order::SetCustomerID(const string& CustomerID){
    this->CustomerID = CustomerID;
}

void Order::SetOrderDate(const string& OrderDate){
    this->OrderDate = OrderDate;
}

void Order::SetStatus(const string& Status){
    this->Status = Status;
}

void Order::SetTotalAmount(const long long& TotalAmount){
    this->TotalAmount = TotalAmount;
}
