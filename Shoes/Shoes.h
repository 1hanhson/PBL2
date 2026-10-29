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
        Shoes(const string&,const string&,const string&,const int&,const long long&,const int&);
        void Input();
        void Output() const;

        string GetID() const;
        string GetName() const;
        string GetBrand() const;
        int GetSize() const;
        long long GetPrice() const;
        int GetQuantity() const;

        void SetID(const string&);
        void SetName(const string&);
        void SetBrand(const string&);
        void SetSize(const int&);
        void SetPrice(const long long&);
        void SetQuantity(const int&);

        int GetSold() const;
        void SetSold(const int&);

        string ToLine() const;
        static bool FromLine(const string&, Shoes&);
};

#endif