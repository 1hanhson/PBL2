#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
using namespace std;

class Customer{
    private:
        string ID;
        string Name;
        string Phone;
        string Address;

    public:
        Customer();
        Customer(const string&, const string&, const string&, const string&);

        void Input();
        void Output() const;

        string GetID() const;
        string GetName() const;
        string GetPhone() const;
        string GetAddress() const;

        void SetID(const string&);
        void SetName(const string&);
        void SetPhone(const string&);
        void SetAddress(const string&);
};

#endif