#include "Customer.h"
#include <sstream>
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

// ID,Name,Phone,Address
string Customer::ToLine() const{
    return this->ID + "," + this->Name + "," + this->Phone + "," + this->Address;
}

bool Customer::FromLine(const string& line, Customer& c){
    stringstream ss(line);
    string id, name, phone, address;

    if(!getline(ss, id, ',') || !getline(ss, name, ',') ||
       !getline(ss, phone, ',') || !getline(ss, address))
        return false;

    if(!address.empty() && address[address.size() - 1] == '\r')   // file Windows
        address.erase(address.size() - 1);
    if(id.empty() || address.find(',') != string::npos)           // thua truong
        return false;

    c = Customer(id, name, phone, address);
    return true;
}