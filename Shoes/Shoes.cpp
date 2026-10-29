#include <iostream>
#include "Shoes.h"
#include "limits"
#include <sstream>
using namespace std;

Shoes::Shoes(){
    this->ID="";
    this->Name="";
    this->Brand="";
    this->Size=0;
    this->Price=0;
    this->Quantity=0;
    this->Sold = 0;
}

Shoes::Shoes(const string& ID,const string& Name,const string& Brand,const int& Size,const long long& Price,const int& Quantity){
    this->ID=ID;
    this->Name=Name;
    this->Brand=Brand;
    this->Size=Size;
    this->Price=Price;
    this->Quantity=Quantity;
    this->Sold = 0;
}

void Shoes::Input() {
    cout << "ID: ";
    getline(cin >> ws, ID);

    cout << "Name: ";
    getline(cin, Name);

    cout << "Brand: ";
    getline(cin, Brand);

    cout << "Size: ";
    cin >> Size;

    cout << "Price: ";
    cin >> Price;

    cout << "Quantity: ";
    cin >> Quantity;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Shoes::Output() const {
    cout << "ID: " << ID << endl;
    cout << "Name: " << Name << endl;
    cout << "Brand: " << Brand << endl;
    cout << "Size: " << Size << endl;
    cout << "Price: " << Price << endl;
    cout << "Quantity: " << Quantity << endl;
    cout << "Sold: " << Sold << endl;
    cout << endl;
}

string Shoes::GetID() const {
    return ID;
}

string Shoes::GetName() const {
    return Name;
}

string Shoes::GetBrand() const {
    return Brand;
}

int Shoes::GetSize() const {
    return Size;
}

long long Shoes::GetPrice() const {
    return Price;
}

int Shoes::GetQuantity() const {
    return Quantity;
}

int Shoes::GetSold() const {
    return this->Sold;
}

void Shoes::SetID(const string& ID) {
    this->ID = ID;
}

void Shoes::SetName(const string& Name) {
    this->Name = Name;
}

void Shoes::SetBrand(const string& Brand) {
    this->Brand = Brand;
}

void Shoes::SetSize(const int& Size) {
    this->Size = Size;
}

void Shoes::SetPrice(const long long& Price) {
    this->Price = Price;
}

void Shoes::SetQuantity(const int& Quantity) {
    this->Quantity = Quantity;
}

void Shoes::SetSold(const int& Sold) {
    this->Sold = Sold;
}

// ID,Name,Brand,Size,Price,Quantity,Sold
string Shoes::ToLine() const{
    return this->ID + "," + this->Name + "," + this->Brand + "," +
           to_string(this->Size) + "," + to_string(this->Price) + "," +
           to_string(this->Quantity) + "," + to_string(this->Sold);
}

// Thieu truong, so khong hop le, so am hoac thua du lieu thi tra ve false
bool Shoes::FromLine(const string& line, Shoes& s){
    // Loai bo ky tu xuong dong Windows (\r) va khoang trang o cuoi dong de tranh loi doc file
    string cleanLine = line;
    while (!cleanLine.empty() && (cleanLine.back() == '\r' || cleanLine.back() == ' ' || cleanLine.back() == '\t'))
        cleanLine.pop_back();

    stringstream ss(cleanLine);
    string id, name, brand, rest;
    int size, quantity, sold;
    long long price;
    char c1, c2, c3;

    if(!getline(ss, id, ',') || !getline(ss, name, ',') || !getline(ss, brand, ','))
        return false;
    if(!(ss >> size >> c1 >> price >> c2 >> quantity >> c3 >> sold))
        return false;
    if(c1 != ',' || c2 != ',' || c3 != ',')
        return false;
    if(ss >> rest)                      // con ky tu thua sau truong cuoi
        return false;
    if(id.empty() || size < 0 || price < 0 || quantity < 0 || sold < 0)
        return false;

    s = Shoes(id, name, brand, size, price, quantity);
    s.SetSold(sold);                    // constructor luon dat Sold = 0
    return true;
}