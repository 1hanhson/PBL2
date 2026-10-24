
#include <limits>
#include "Customer.h"
using namespace std;

Customer::Customer(){
    this->ID = "";
    this->Name = "";
    this->Phone = "";
    this->Address = "";
}

Customer::Customer(const string& ID, const string& Name,
                   const string& Phone, const string& Address){
    this->ID = ID;
    this->Name = Name;
    this->Phone = Phone;
    this->Address = Address;
}

void Customer::Input(){
    cout << "ID: ";
    getline(cin >> ws, this->ID);

    cout << "Name: ";
    getline(cin, this->Name);

    cout << "Phone: ";
    getline(cin, this->Phone);

    cout << "Address: ";
    getline(cin, this->Address);
}

void Customer::Output() const{
    cout << "ID: " << this->ID << endl;
    cout << "Name: " << this->Name << endl;
    cout << "Phone: " << this->Phone << endl;
    cout << "Address: " << this->Address << endl;
    cout << endl;
}

string Customer::GetID() const{
    return this->ID;
}

string Customer::GetName() const{
    return this->Name;
}

string Customer::GetPhone() const{
    return this->Phone;
}

string Customer::GetAddress() const{
    return this->Address;
}

void Customer::SetID(const string& ID){
    this->ID = ID;
}

void Customer::SetName(const string& Name){
    this->Name = Name;
}

void Customer::SetPhone(const string& Phone){
    this->Phone = Phone;
}

void Customer::SetAddress(const string& Address){
    this->Address = Address;
}
