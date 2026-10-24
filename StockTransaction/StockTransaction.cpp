#include "StockTransaction.h"
#include <sstream>

// Constructor mac dinh
StockTransaction::StockTransaction() {
    this->transactionId = "";
    this->shoeId = "";
    this->type = "Import";
    this->quantity = 0;
    this->unitPrice = 0;
    this->transactionDate = "";
}

StockTransaction::StockTransaction(const string& transactionId, const string& shoeId, const string& type,
                                   const int& quantity, const long long& unitPrice,
                                   const string& transactionDate) {
    this->transactionId = transactionId;
    this->shoeId = shoeId;
    this->type = type;
    this->quantity = quantity;
    this->unitPrice = unitPrice;
    this->transactionDate = transactionDate;
}

void StockTransaction::Output() const {
    cout << "Transaction ID: " << this->transactionId
         << " | Shoe ID: " << this->shoeId
         << " | Type: " << this->type
         << " | Quantity: " << this->quantity
         << " | Unit Price: " << this->unitPrice
         << " | Total: " << this->GetTotalValue()
         << " | Date: " << this->transactionDate << endl;
}

//doi thanh 1 dong de luu file, cac truong cach nhau bang dau cach
string StockTransaction::ToLine() const {
    return this->transactionId + " " + this->shoeId + " " + this->type + " " +
           to_string(this->quantity) + " " + to_string(this->unitPrice) + " " +
           this->transactionDate;
}

//doc 1 dong tu file, thieu truong hoac sai so thi tra ve false
bool StockTransaction::FromLine(const string& line, StockTransaction& t) {
    stringstream ss(line);
    string id, shoe, type, date;
    int quantity;
    long long price;
    ss >> id >> shoe >> type >> quantity >> price >> date;
    if (ss.fail())
        return false;
    t = StockTransaction(id, shoe, type, quantity, price, date);
    return true;
}

//tong gia tri giao dich
long long StockTransaction::GetTotalValue() const {
    return (long long)this->quantity * this->unitPrice;
}

string StockTransaction::GetTransactionId() const { return this->transactionId; }
string StockTransaction::GetShoeId() const { return this->shoeId; }
string StockTransaction::GetType() const { return this->type; }
int StockTransaction::GetQuantity() const { return this->quantity; }
long long StockTransaction::GetUnitPrice() const { return this->unitPrice; }
string StockTransaction::GetTransactionDate() const { return this->transactionDate; }

void StockTransaction::SetTransactionId(const string& transactionId) { this->transactionId = transactionId; }
void StockTransaction::SetShoeId(const string& shoeId) { this->shoeId = shoeId; }
void StockTransaction::SetType(const string& type) { this->type = type; }
void StockTransaction::SetQuantity(const int& quantity) { this->quantity = quantity; }
void StockTransaction::SetUnitPrice(const long long& unitPrice) { this->unitPrice = unitPrice; }
void StockTransaction::SetTransactionDate(const string& transactionDate) { this->transactionDate = transactionDate; }