#include "Payment.h"

// Constructor mặc định
Payment::Payment() {
    this->paymentId = "";
    this->orderId = "";
    this->amount = 0;
    this->paymentDate = "";
    this->paymentMethod = "";
    this->status = "Wait"; // Mặc định là chờ xử lý
}

Payment::Payment(const string& paymentId, const string& orderId, long long amount, 
                 const string& paymentDate, const string& paymentMethod, const string& status) {
    this->paymentId = paymentId;
    this->orderId = orderId;
    this->amount = amount;
    this->paymentDate = paymentDate;
    this->paymentMethod = paymentMethod;
    this->status = status;
}

void Payment::Output() {
    cout << "Payment ID: " << this->paymentId 
         << " | Order ID: " << this->orderId 
         << " | Amount: " << this->amount 
         << " | Date: " << this->paymentDate 
         << " | Method: " << this->paymentMethod 
         << " | Status: " << this->status << endl;
}

string Payment::getPaymentId() const { return this->paymentId; }
string Payment::getOrderId() const { return this->orderId; }
long long Payment::getAmount() const { return this->amount; }
string Payment::getPaymentDate() const { return this->paymentDate; }
string Payment::getPaymentMethod() const { return this->paymentMethod; }
string Payment::getStatus() const { return this->status; }

void Payment::setPaymentId(const string& paymentId) { this->paymentId = paymentId; }
void Payment::setOrderId(const string& orderId) { this->orderId = orderId; }
void Payment::setAmount(long long amount) { this->amount = amount; }
void Payment::setPaymentDate(const string& paymentDate) { this->paymentDate = paymentDate; }
void Payment::setPaymentMethod(const string& paymentMethod) { this->paymentMethod = paymentMethod; }
void Payment::setStatus(const string& status) { this->status = status; }