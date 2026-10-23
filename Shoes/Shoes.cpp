#include <iostream>
#include "Shoes.h"
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

Shoes::Shoes(const string& ID,const string& Name,const string& Brand,const int& Size,const double& Price,const int& Quantity){
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
    cin >> ID;

    cout << "Name: ";
    cin >> Name;

    cout << "Brand: ";
    cin >> Brand;

    cout << "Size: ";
    cin >> Size;

    cout << "Price: ";
    cin >> Price;

    cout << "Quantity: ";
    cin >> Quantity;
}

void Shoes::Output() {
    cout << "ID: " << ID << endl;
    cout << "Name: " << Name << endl;
    cout << "Brand: " << Brand << endl;
    cout << "Size: " << Size << endl;
    cout << "Price: " << Price << endl;
    cout << "Quantity: " << Quantity << endl;
    cout << "Sold: " << Sold << endl;
    cout << endl;
}

string Shoes::GetID() {
    return ID;
}

string Shoes::GetName() {
    return Name;
}

string Shoes::GetBrand() {
    return Brand;
}

int Shoes::GetSize() {
    return Size;
}

long long Shoes::GetPrice() {
    return Price;
}

int Shoes::GetQuantity() {
    return Quantity;
}

int Shoes::GetSold() {
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

void Shoes::SetPrice(const double& Price) {
    this->Price = Price;
}

void Shoes::SetQuantity(const int& Quantity) {
    this->Quantity = Quantity;
}

void Shoes::SetSold(const int& Sold) {
    this->Sold = Sold;
}