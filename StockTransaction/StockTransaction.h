#ifndef STOCK_TRANSACTION_H
#define STOCK_TRANSACTION_H
#include <string>
#include <iostream>

using namespace std;

class StockTransaction {
private:
    string transactionId;   // Ma giao dich kho
    string shoeId;          // Ma giay lien quan
    string type;            // Loai giao dich: Import (nhap kho) / Export (xuat kho)
    int quantity;           // So luong nhap/xuat
    long long unitPrice;    // Don gia (dung long long dong bo voi gia giay)
    string transactionDate; // Ngay/gio giao dich

public:
    StockTransaction();
    StockTransaction(const string& transactionId, const string& shoeId, const string& type,
                     const int& quantity, const long long& unitPrice,
                     const string& transactionDate);

    void Output() const;
    string ToLine() const;
    static bool FromLine(const string& line, StockTransaction& t);

    long long GetTotalValue() const;   // quantity * unitPrice

    string GetTransactionId() const;
    string GetShoeId() const;
    string GetType() const;
    int GetQuantity() const;
    long long GetUnitPrice() const;
    string GetTransactionDate() const;

    void SetTransactionId(const string&);
    void SetShoeId(const string&);
    void SetType(const string&);
    void SetQuantity(const int&);
    void SetUnitPrice(const long long&);
    void SetTransactionDate(const string&);
};

#endif