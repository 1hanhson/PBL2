#include <string>
#include <iostream>

using namespace std;

class Payment {
private:
    string paymentId;     // Mã giao dịch thanh toán
    string orderId;       // Mã đơn hàng liên quan
    long long amount;     // Tổng số tiền thanh toán (dùng long long đồng bộ với giá giày)
    string paymentDate;   // Ngày/giờ thanh toán
    string paymentMethod; // Phương thức (Tiền mặt, Chuyển khoản, Thẻ...)
    string status;        // Trạng thái (Thành công, Thất bại, Chờ xử lý...)

public:
    Payment();
    Payment(const string& paymentId, const string& orderId, long long amount, 
            const string& paymentDate, const string& paymentMethod, const string& status);

    void Output();

    string getPaymentId() const;
    string getOrderId() const;
    long long getAmount() const;
    string getPaymentDate() const;
    string getPaymentMethod() const;
    string getStatus() const;

    void setPaymentId(const string& paymentId);
    void setOrderId(const string& orderId);
    void setAmount(long long amount);
    void setPaymentDate(const string& paymentDate);
    void setPaymentMethod(const string& paymentMethod);
    void setStatus(const string& status);
};
