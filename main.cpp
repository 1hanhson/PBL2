#include <iostream>
#include <sstream>

#include "Shoes.h"
#include "Node.h"
#include "ShoesManager.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "Payment.h"

using namespace std;

void Check(const char* name, bool passed) {
    cout << (passed ? "[PASS] " : "[FAIL] ") << name << '\n';
}

int main() {
    cout << "========== TEST SHOES ==========\n";

    Shoes shoe;
    Check("Shoes constructor mac dinh",
          shoe.GetID().empty() &&
          shoe.GetName().empty() &&
          shoe.GetBrand().empty() &&
          shoe.GetSize() == 0 &&
          shoe.GetPrice() == 0 &&
          shoe.GetQuantity() == 0 &&
          shoe.GetSold() == 0);

    shoe.SetID("TEST01");
    shoe.SetName("Runner");
    shoe.SetBrand("BrandA");
    shoe.SetSize(40);
    shoe.SetPrice(500000);
    shoe.SetQuantity(12);
    shoe.SetSold(3);

    Check("Shoes setters/getters",
          shoe.GetID() == "TEST01" &&
          shoe.GetName() == "Runner" &&
          shoe.GetBrand() == "BrandA" &&
          shoe.GetSize() == 40 &&
          shoe.GetPrice() == 500000 &&
          shoe.GetQuantity() == 12 &&
          shoe.GetSold() == 3);

    cout << "\nShoes::Output():\n";
    shoe.Output();

    // Input() dùng cin >> nên dữ liệu nhập thử không có khoảng trắng.
    Shoes inputShoe;
    istringstream input("IN01 Sneaker BrandB 39 650000 7");
    streambuf* oldCinBuffer = cin.rdbuf(input.rdbuf());
    inputShoe.Input();
    cin.rdbuf(oldCinBuffer);

    Check("Shoes::Input",
          inputShoe.GetID() == "IN01" &&
          inputShoe.GetName() == "Sneaker" &&
          inputShoe.GetBrand() == "BrandB" &&
          inputShoe.GetSize() == 39 &&
          inputShoe.GetPrice() == 650000 &&
          inputShoe.GetQuantity() == 7);

    cout << "\n========== TEST HASH TABLE ==========\n";

    Shoes hashShoe("H001", "HashShoe", "BrandH", 41, 400000, 5);
    Node hashNode(hashShoe);
    HashTable hashTable(101);

    Check("HashTable::Insert", hashTable.Insert(&hashNode));
    Check("HashTable::Search tim thay",
          hashTable.Search("H001") == &hashNode);
    Check("HashTable::Search khong tim thay",
          hashTable.Search("UNKNOWN") == nullptr);
    Check("HashTable::Delete", hashTable.Delete(&hashNode));
    Check("HashTable::Search sau khi xoa",
          hashTable.Search("H001") == nullptr);

    cout << "\n========== TEST SHOES MANAGER / BST ==========\n";

    ShoesManager manager;

    Shoes shoeA("S001", "Alpha", "BrandA", 38, 300000, 10);
    Shoes shoeB("S002", "Beta",  "BrandB", 39, 100000, 8);
    Shoes shoeC("S003", "Gamma", "BrandC", 40, 200000, 6);

    Check("ShoesManager::Insert shoeA", manager.Insert(shoeA, nullptr) != 0);
    Check("ShoesManager::Insert shoeB", manager.Insert(shoeB, nullptr) != 0);
    Check("ShoesManager::Insert shoeC", manager.Insert(shoeC, nullptr) != 0);

    Check("ShoesManager::Search tim thay",
          manager.Search("S002") != nullptr);
    Check("ShoesManager::Search khong tim thay",
          manager.Search("NOT_FOUND") == nullptr);

    cout << "\nDanh sach san pham:\n";
    manager.Show();

    cout << "\nBST MinToMax (theo gia):\n";
    manager.ShowMinToMax();

    Node* shoeToDelete = manager.Search("S002");
    Check("ShoesManager::Delete",
          shoeToDelete != nullptr && manager.Delete(shoeToDelete) != 0);
    Check("Search sau khi xoa",
          manager.Search("S002") == nullptr);

    cout << "\nDanh sach sau khi xoa S002:\n";
    manager.Show();

    cout << "\n========== TEST MAX HEAP ==========\n";

    Shoes topShoe1("T001", "Top1", "BrandT", 38, 300000, 10);
    Shoes topShoe2("T002", "Top2", "BrandT", 39, 400000, 10);
    Shoes topShoe3("T003", "Top3", "BrandT", 40, 500000, 10);
    Shoes outsideShoe("T004", "Outside", "BrandT", 41, 600000, 10);

    topShoe1.SetSold(10);
    topShoe2.SetSold(25);
    topShoe3.SetSold(15);

    Node topNode1(topShoe1);
    Node topNode2(topShoe2);
    Node topNode3(topShoe3);
    Node outsideNode(outsideShoe);

    MaxHeap heap(3);

    Check("MaxHeap::Insert nullptr", !heap.Insert(nullptr));
    Check("MaxHeap::IncreaseSold nullptr",
          !heap.IncreaseSold(nullptr, 5));
    Check("MaxHeap::IncreaseSold node ngoai heap",
          !heap.IncreaseSold(&outsideNode, 5));

    Check("MaxHeap::Insert node 1", heap.Insert(&topNode1));
    Check("MaxHeap::Insert node 2", heap.Insert(&topNode2));
    Check("MaxHeap::Insert node 3", heap.Insert(&topNode3));
    Check("MaxHeap::Insert khi heap day", !heap.Insert(&outsideNode));

    Check("MaxHeap::IncreaseSold node trong heap",
          heap.IncreaseSold(&topNode1, 20));

    cout << "\nTop 3 (du kien Sold: 30, 25, 15):\n";
    heap.ShowTop(3);

    cout << "\nTop 10 khi chi co 3 san pham:\n";
    heap.ShowTop(10);

    cout << "\nShowTop(0):\n";
    heap.ShowTop(0);

    MaxHeap emptyHeap(2);
    cout << "\nShowTop tren heap rong:\n";
    emptyHeap.ShowTop(3);

    cout << "\n========== TEST PAYMENT ==========\n";

    Payment payment;
    Check("Payment constructor mac dinh",
          payment.getPaymentId().empty() &&
          payment.getOrderId().empty() &&
          payment.getAmount() == 0 &&
          payment.getStatus() == "Wait");

    payment.setPaymentId("P001");
    payment.setOrderId("O001");
    payment.setAmount(800000);
    payment.setPaymentDate("2026-10-23");
    payment.setPaymentMethod("Cash");
    payment.setStatus("Success");

    Check("Payment setters/getters",
          payment.getPaymentId() == "P001" &&
          payment.getOrderId() == "O001" &&
          payment.getAmount() == 800000 &&
          payment.getPaymentDate() == "2026-10-23" &&
          payment.getPaymentMethod() == "Cash" &&
          payment.getStatus() == "Success");

    cout << "\nPayment::Output():\n";
    payment.Output();

    Payment secondPayment(
        "P002", "O002", 250000, "2026-10-24", "Card", "Wait"
    );

    cout << "\nPayment constructor co tham so:\n";
    secondPayment.Output();

    cout << "\n========== KET THUC TEST ==========\n";
    return 0;
}