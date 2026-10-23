#ifndef SHOES_H
#define SHOES_H

#include <string>
#include <iostream>
using namespace std;

class Shoes{
    private:
        string ID;
        string Name;
        string Brand;
        int Size;
        long long Price;
        int Quantity;
        int Sold;
    public:
        Shoes();
        Shoes(const string&,const string&,const string&,const int&,const double&,const int&);
        void Input();
        void Output();

        string GetID();
        string GetName();
        string GetBrand();
        int GetSize();
        long long GetPrice();
        int GetQuantity();

        void SetID(const string&);
        void SetName(const string&);
        void SetBrand(const string&);
        void SetSize(const int&);
        void SetPrice(const double&);
        void SetQuantity(const int&);

        int GetSold();
        void SetSold(const int&);
};

#endif