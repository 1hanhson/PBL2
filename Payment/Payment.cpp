#include "Payment.h"
#include <sstream>

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
    this->status = PaymentStatus::Wait;
}

void Payment::Output() const {
    cout << "Payment ID: " << this->paymentId 
         << " | Order ID: " << this->orderId 
         << " | Amount: " << this->amount 
         << " | Date: " << this->paymentDate 
         << " | Method: " << this->paymentMethod 
         << " | Status: " << this->status << endl;
}
 
// PaymentID,OrderID,Amount,Date,Method,Status
string Payment::ToLine() const {
    return this->paymentId + "," + this->orderId + "," + to_string(this->amount) + "," +
           this->paymentDate + "," + this->paymentMethod + "," + this->status;
}

bool Payment::FromLine(const string& line, Payment& p) {
    stringstream ss(line);
    string id, order, date, method, status;
    long long amount;
    char c;

    if (!getline(ss, id, ',') || !getline(ss, order, ','))
        return false;
    if (!(ss >> amount >> c) || c != ',')
        return false;
    if (!getline(ss, date, ',') || !getline(ss, method, ',') || !getline(ss, status))
        return false;

    if (!status.empty() && status[status.size() - 1] == '\r')
        status.erase(status.size() - 1);
    if (id.empty() || status.find(',') != string::npos)
        return false;

    p = Payment(id, order, amount, date, method, status);
    return true;
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