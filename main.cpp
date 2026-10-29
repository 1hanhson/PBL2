// test.cpp - kiem tra cac module hien co cua PBL2 Quan ly ban giay
// Build: target RunTests (xem CMakeLists.txt), chay: ./RunTests
// Tra ve 0 neu tat ca PASS, 1 neu co FAIL.

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <string>

#include "Shoes.h"
#include "Node.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "ShoesManager.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "Order.h"
#include "OrderManager.h"
#include "OrderDetail.h"
#include "OrderDetailManager.h"
#include "Payment.h"
#include "PaymentManager.h"
#include "StockTransaction.h"
#include "StockTransactionManager.h"

using namespace std;

// ---------------------------------------------------------------- tien ich

static int g_pass = 0;
static int g_fail = 0;

static void Check(const string& name, bool ok) {
    if (ok) g_pass++; else g_fail++;
    cout << (ok ? "[PASS] " : "[FAIL] ") << name << '\n';
}

static void Section(const string& title) {
    cout << "\n========== " << title << " ==========\n";
}

static bool Has(const string& s, const string& sub) {
    return s.find(sub) != string::npos;
}

// Vi tri xuat hien dau tien cua sub trong s (string::npos neu khong co)
static size_t Pos(const string& s, const string& sub) {
    return s.find(sub);
}

// Bat toan bo du lieu f() in ra cout de kiem tra (va de man hinh khong bi roi)
template <typename F>
static string Capture(F f) {
    ostringstream oss;
    streambuf* old = cout.rdbuf(oss.rdbuf());
    f();
    cout.rdbuf(old);
    return oss.str();
}

// Gia lap nguoi dung go du lieu vao cin trong luc chay f()
template <typename F>
static void FeedInput(const string& data, F f) {
    istringstream in(data);
    streambuf* old = cin.rdbuf(in.rdbuf());
    f();
    cin.rdbuf(old);
    cin.clear();
}

static void WriteFile(const string& path, const string& content) {
    ofstream f(path.c_str());
    f << content;
}

// ---------------------------------------------------------------- SHOES

static void TestShoes() {
    Section("SHOES");

    Shoes s;
    Check("Shoes constructor mac dinh",
          s.GetID().empty() && s.GetName().empty() && s.GetBrand().empty() &&
          s.GetSize() == 0 && s.GetPrice() == 0 &&
          s.GetQuantity() == 0 && s.GetSold() == 0);

    Shoes a("A1", "Air Max", "Nike", 42, 2500000, 10);
    Check("Shoes constructor co tham so (Sold = 0)",
          a.GetID() == "A1" && a.GetName() == "Air Max" && a.GetBrand() == "Nike" &&
          a.GetSize() == 42 && a.GetPrice() == 2500000 &&
          a.GetQuantity() == 10 && a.GetSold() == 0);

    a.SetSold(4);
    string line = a.ToLine();
    Check("Shoes::ToLine", line == "A1,Air Max,Nike,42,2500000,10,4");

    Shoes b;
    Check("Shoes::FromLine hop le",
          Shoes::FromLine(line, b) && b.GetID() == "A1" && b.GetName() == "Air Max" &&
          b.GetBrand() == "Nike" && b.GetSize() == 42 && b.GetPrice() == 2500000 &&
          b.GetQuantity() == 10 && b.GetSold() == 4);

    Shoes t;
    Check("Shoes::FromLine thieu truong", !Shoes::FromLine("A1,Air,Nike,42,2500000,10", t));
    Check("Shoes::FromLine so am",        !Shoes::FromLine("A1,Air,Nike,42,-5,10,0", t));
    Check("Shoes::FromLine thua truong",  !Shoes::FromLine("A1,Air,Nike,42,2500000,10,4,extra", t));
    Check("Shoes::FromLine ID rong",      !Shoes::FromLine(",Air,Nike,42,1,1,0", t));
    Check("Shoes::FromLine sai so",       !Shoes::FromLine("A1,Air,Nike,abc,1,1,0", t));

    // Yeu cau Buoc 1.6: Input dung getline nen ten co dau cach van doc dung
    Shoes in;
    FeedInput("IN01\nAir Max 90\nBrand B\n39\n650000\n7\n", [&]() {
        Capture([&]() { in.Input(); });
    });
    Check("Shoes::Input (ten co dau cach)",
          in.GetID() == "IN01" && in.GetName() == "Air Max 90" &&
          in.GetBrand() == "Brand B" && in.GetSize() == 39 &&
          in.GetPrice() == 650000 && in.GetQuantity() == 7);
}

// ---------------------------------------------------------------- HASH TABLE

static void TestHashTable() {
    Section("HASH TABLE (Shoes)");

    HashTable ht(101);
    Node n1(Shoes("S012", "A", "B", 1, 1, 1));
    Node n2(Shoes("S021", "C", "D", 2, 2, 2));   // trung bucket voi S012 (cung tong ky tu)

    Check("Insert nullptr", !ht.Insert(NULL));
    Check("Insert n1", ht.Insert(&n1));
    Check("Insert n2 (cung bucket)", ht.Insert(&n2));
    Check("Search n1", ht.Search("S012") == &n1);
    Check("Search n2", ht.Search("S021") == &n2);
    Check("Search khong co", ht.Search("S999") == NULL);

    Check("Delete node cuoi chuoi (n1)", ht.Delete(&n1));
    Check("n1 da bi xoa", ht.Search("S012") == NULL);
    Check("n2 van con", ht.Search("S021") == &n2);
    Check("Delete node dau chuoi (n2)", ht.Delete(&n2));
    Check("n2 da bi xoa", ht.Search("S021") == NULL);
    Check("Delete nullptr", !ht.Delete(NULL));
    Check("Delete node khong co trong bang", !ht.Delete(&n1));
}

// ---------------------------------------------------------------- MAX HEAP

static void TestMaxHeap() {
    Section("MAX HEAP");

    Shoes s1("T001", "Top1", "B", 38, 300000, 10);
    Shoes s2("T002", "Top2", "B", 39, 400000, 10);
    Shoes s3("T003", "Top3", "B", 40, 500000, 10);
    Shoes s4("T004", "Out",  "B", 41, 600000, 10);
    s1.SetSold(10);
    s2.SetSold(25);
    s3.SetSold(15);

    Node n1(s1), n2(s2), n3(s3), n4(s4);
    MaxHeap heap(3);

    Check("Insert nullptr", !heap.Insert(NULL));
    Check("Insert n1", heap.Insert(&n1));
    Check("Insert n2", heap.Insert(&n2));
    Check("Insert n3", heap.Insert(&n3));
    Check("Insert khi heap day", !heap.Insert(&n4));

    Check("IncreaseSold nullptr", !heap.IncreaseSold(NULL, 5));
    Check("IncreaseSold node ngoai heap", !heap.IncreaseSold(&n4, 5));
    Check("IncreaseSold amount <= 0", !heap.IncreaseSold(&n1, 0));
    Check("IncreaseSold n1 +20 (10 -> 30)", heap.IncreaseSold(&n1, 20));

    string top = Capture([&]() { heap.ShowTop(3); });
    Check("ShowTop(3) dung thu tu T001(30) > T002(25) > T003(15)",
          Has(top, "ID: T001") && Has(top, "ID: T002") && Has(top, "ID: T003") &&
          Pos(top, "ID: T001") < Pos(top, "ID: T002") &&
          Pos(top, "ID: T002") < Pos(top, "ID: T003"));

    string top1 = Capture([&]() { heap.ShowTop(1); });
    Check("ShowTop(1) chi co T001", Has(top1, "ID: T001") && !Has(top1, "ID: T002"));

    string top10 = Capture([&]() { heap.ShowTop(10); });
    Check("ShowTop(10) khi chi co 3 SP van in du 3",
          Has(top10, "ID: T001") && Has(top10, "ID: T002") && Has(top10, "ID: T003"));

    string top0 = Capture([&]() { heap.ShowTop(0); });
    Check("ShowTop(0) khong in san pham nao", !Has(top0, "ID: T"));

    // ShowTop khong duoc lam hong heap goc
    string again = Capture([&]() { heap.ShowTop(3); });
    Check("ShowTop khong lam thay doi heap", again == top);

    MaxHeap empty(2);
    string e = Capture([&]() { empty.ShowTop(3); });
    Check("ShowTop tren heap rong", Has(e, "trong"));

    // Remove
    Check("Remove nullptr", !heap.Remove(NULL));
    Check("Remove node ngoai heap", !heap.Remove(&n4));
    Check("Remove n1 (dinh heap)", heap.Remove(&n1));
    string afterRemove = Capture([&]() { heap.ShowTop(3); });
    Check("Sau Remove: con T002 > T003, khong con T001",
          !Has(afterRemove, "ID: T001") &&
          Pos(afterRemove, "ID: T002") < Pos(afterRemove, "ID: T003"));
    Check("Remove lan 2 cung node -> false", !heap.Remove(&n1));
    Check("Insert lai sau khi Remove", heap.Insert(&n4));
}

// ---------------------------------------------------------------- SHOES MANAGER + BST

static void TestShoesManager() {
    Section("SHOES MANAGER / BST");

    ShoesManager m;
    Shoes a("S001", "Alpha", "BrandA", 38, 300000, 10);
    Shoes b("S002", "Beta",  "BrandB", 39, 100000, 8);
    Shoes c("S003", "Gamma", "BrandC", 40, 200000, 6);

    Check("Insert S001", m.Insert(a));
    Check("Insert S002", m.Insert(b));
    Check("Insert S003", m.Insert(c));
    // Yeu cau Buoc 1.5
    Check("Insert trung ID bi tu choi", !m.Insert(a));
    Check("Insert ID rong bi tu choi", !m.Insert(Shoes("", "x", "y", 1, 1, 1)));

    Check("Search S002", m.Search("S002") != NULL);
    Check("Search khong co", m.Search("NOPE") == NULL);

    string list = Capture([&]() { m.Show(); });
    Check("Show co du 3 san pham",
          Has(list, "ID: S001") && Has(list, "ID: S002") && Has(list, "ID: S003"));

    string asc = Capture([&]() { m.ShowMinToMax(); });
    Check("MinToMax theo gia: S002(100k) < S003(200k) < S001(300k)",
          Pos(asc, "ID: S002") < Pos(asc, "ID: S003") &&
          Pos(asc, "ID: S003") < Pos(asc, "ID: S001"));

    string desc = Capture([&]() { m.ShowMaxToMin(); });
    Check("MaxToMin theo gia: S001 > S003 > S002",
          Pos(desc, "ID: S001") < Pos(desc, "ID: S003") &&
          Pos(desc, "ID: S003") < Pos(desc, "ID: S002"));

    // Top ban chay
    Check("IncreaseSold S003 +50", m.IncreaseSold("S003", 50));
    Check("IncreaseSold S001 +20", m.IncreaseSold("S001", 20));
    Check("IncreaseSold ID khong ton tai", !m.IncreaseSold("NOPE", 5));
    Check("IncreaseSold amount <= 0", !m.IncreaseSold("S001", 0));
    string top = Capture([&]() { m.ShowTop(3); });
    Check("ShowTop: S003(50) > S001(20) > S002(0)",
          Pos(top, "ID: S003") < Pos(top, "ID: S001") &&
          Pos(top, "ID: S001") < Pos(top, "ID: S002"));

    // Xoa
    Check("Delete nullptr", !m.Delete(NULL));
    Node* p = m.Search("S002");
    Check("Delete S002", p != NULL && m.Delete(p));
    Check("S002 da bien mat khoi Hash", m.Search("S002") == NULL);
    string afterDel = Capture([&]() { m.ShowMinToMax(); });
    Check("S002 da bien mat khoi BST", !Has(afterDel, "ID: S002"));
    string topDel = Capture([&]() { m.ShowTop(5); });
    Check("S002 da bien mat khoi Heap", !Has(topDel, "ID: S002"));
    Check("IncreaseSold S002 sau khi xoa -> false", !m.IncreaseSold("S002", 1));

    // Xoa node goc co 2 con trong BST
    ShoesManager m2;
    m2.Insert(Shoes("A", "a", "x", 1, 300000, 1));   // goc
    m2.Insert(Shoes("B", "b", "x", 1, 100000, 1));
    m2.Insert(Shoes("C", "c", "x", 1, 400000, 1));
    m2.Insert(Shoes("D", "d", "x", 1, 350000, 1));
    Check("BST: xoa goc co 2 con", m2.Delete(m2.Search("A")));
    string t2 = Capture([&]() { m2.ShowMinToMax(); });
    Check("BST sau khi xoa goc: B < D < C, khong con A",
          !Has(t2, "ID: A") &&
          Pos(t2, "ID: B") < Pos(t2, "ID: D") &&
          Pos(t2, "ID: D") < Pos(t2, "ID: C"));

    // Hai san pham cung gia
    ShoesManager m3;
    m3.Insert(Shoes("X1", "x", "x", 1, 500000, 1));
    m3.Insert(Shoes("X2", "x", "x", 1, 500000, 1));
    Check("BST: 2 SP cung gia deu insert duoc", m3.Search("X1") && m3.Search("X2"));
    Check("BST: xoa X1 khi cung gia", m3.Delete(m3.Search("X1")));
    string t3 = Capture([&]() { m3.ShowMinToMax(); });
    Check("BST: X2 van con sau khi xoa X1", Has(t3, "ID: X2") && !Has(t3, "ID: X1"));

    // Luu / doc file
    const string pathShoes = "test_tmp_shoes.csv";
    Check("ShoesManager::SaveToFile", m.SaveToFile(pathShoes));
    ShoesManager mFile;
    Check("ShoesManager::LoadFromFile doc du san pham", mFile.LoadFromFile(pathShoes) == m.GetCount());
    Check("ShoesManager::LoadFromFile khong ton tai -> -1", mFile.LoadFromFile("khong_co_file.csv") == -1);
    remove(pathShoes.c_str());
}

// ---------------------------------------------------------------- CUSTOMER

static void TestCustomer() {
    Section("CUSTOMER");

    Customer c;
    Check("Customer constructor mac dinh",
          c.GetID().empty() && c.GetName().empty() &&
          c.GetPhone().empty() && c.GetAddress().empty());

    Customer c1("C001", "Nguyen Van A", "0905000001", "12 Le Loi");
    string line = c1.ToLine();
    Check("Customer::ToLine", line == "C001,Nguyen Van A,0905000001,12 Le Loi");

    Customer r;
    Check("Customer::FromLine hop le",
          Customer::FromLine(line, r) && r.GetID() == "C001" && r.GetName() == "Nguyen Van A" &&
          r.GetPhone() == "0905000001" && r.GetAddress() == "12 Le Loi");
    Check("Customer::FromLine co ky tu \\r (file Windows)",
          Customer::FromLine("C2,B,0900,Hue\r", r) && r.GetAddress() == "Hue");
    Check("Customer::FromLine thua truong", !Customer::FromLine("C1,A,090,Addr,extra", r));
    Check("Customer::FromLine thieu truong", !Customer::FromLine("C1,A,090", r));
    Check("Customer::FromLine ID rong", !Customer::FromLine(",A,090,Addr", r));

    Customer in;
    FeedInput("C009\nTran Thi B\n0912345678\n5 Hung Vuong\n", [&]() {
        Capture([&]() { in.Input(); });
    });
    Check("Customer::Input",
          in.GetID() == "C009" && in.GetName() == "Tran Thi B" &&
          in.GetPhone() == "0912345678" && in.GetAddress() == "5 Hung Vuong");

    // Manager
    CustomerManager m;
    Customer c2("C002", "Le Van C", "0905000002", "34 Hai Phong");
    Customer c3("C003", "Pham D",   "0905000003", "56 Ong Ich Khiem");

    Check("Insert C001", m.Insert(c1));
    Check("Insert C002", m.Insert(c2));
    Check("Insert C003", m.Insert(c3));
    Check("Insert trung ID bi tu choi", !m.Insert(c1));
    Check("Search C002", m.Search("C002") != NULL);
    Check("Search khong co", m.Search("NOPE") == NULL);

    string list = Capture([&]() { m.Show(); });
    Check("Show co du 3 khach hang",
          Has(list, "ID: C001") && Has(list, "ID: C002") && Has(list, "ID: C003"));

    // Update
    Check("Update C001 -> C009 (doi ID)",
          m.Update("C001", Customer("C009", "Nguyen Van A2", "0999", "Moi")));
    Check("ID cu C001 khong con", m.Search("C001") == NULL);
    Check("ID moi C009 tim duoc", m.Search("C009") != NULL);
    Check("Update sang ID da thuoc khach khac bi tu choi",
          !m.Update("C009", Customer("C002", "x", "y", "z")));
    Check("Sau khi bi tu choi, C009 va C002 van con",
          m.Search("C009") != NULL && m.Search("C002") != NULL);
    Check("Update ID khong ton tai", !m.Update("NOPE", c1));
    Check("Update giu nguyen ID (chi doi thong tin)",
          m.Update("C002", Customer("C002", "Ten Moi", "111", "Dia chi moi")));
    string afterUpd = Capture([&]() { m.Show(); });
    Check("Thong tin moi da duoc cap nhat", Has(afterUpd, "Ten Moi") && Has(afterUpd, "Dia chi moi"));

    // Delete
    Check("Delete nullptr", !m.Delete(NULL));
    Check("Delete C003", m.Delete(m.Search("C003")));
    Check("C003 da bien mat", m.Search("C003") == NULL);
    string afterDel = Capture([&]() { m.Show(); });
    Check("Show khong con C003", !Has(afterDel, "ID: C003"));
    Check("Insert lai C003 sau khi xoa", m.Insert(c3));

    // Luu / doc file
    const string pathCust = "test_tmp_customer.csv";
    Check("CustomerManager::SaveToFile", m.SaveToFile(pathCust));
    CustomerManager mCust;
    Check("CustomerManager::LoadFromFile doc du khach hang", mCust.LoadFromFile(pathCust) == m.GetCount());
    Check("CustomerManager::LoadFromFile khong ton tai -> -1", mCust.LoadFromFile("khong_co_file.csv") == -1);
    remove(pathCust.c_str());
}

// ---------------------------------------------------------------- ORDER

static void TestOrder() {
    Section("ORDER / QUEUE / HASH");

    Order d;
    Check("Order mac dinh: Status = Cho xu ly (OrderStatus::Pending)",
          d.GetStatus() == OrderStatus::Pending && d.GetTotalAmount() == 0);
    Check("Hang so OrderStatus",
          OrderStatus::Pending == "Cho xu ly" &&
          OrderStatus::Processed == "Da xu ly" &&
          OrderStatus::Cancelled == "Da huy");

    Order o("O1", "C001", "2026-10-23", OrderStatus::Pending, 500000);
    string line = o.ToLine();
    Check("Order::ToLine", line == "O1,C001,2026-10-23,Cho xu ly,500000");

    Order r;
    Check("Order::FromLine hop le",
          Order::FromLine(line, r) && r.GetOrderID() == "O1" && r.GetCustomerID() == "C001" &&
          r.GetOrderDate() == "2026-10-23" && r.GetStatus() == "Cho xu ly" &&
          r.GetTotalAmount() == 500000);
    Check("Order::FromLine thieu truong", !Order::FromLine("O1,C001,2026-10-23,Cho xu ly", r));
    Check("Order::FromLine tong tien am", !Order::FromLine("O1,C001,d,s,-1", r));
    Check("Order::FromLine ID rong", !Order::FromLine(",C001,d,s,10", r));
    Check("Order::FromLine thua truong", !Order::FromLine("O1,C001,d,s,10,extra", r));

    Order in;
    FeedInput("O9\nC9\n2026-10-25\nCho xu ly\n123000\n", [&]() {
        Capture([&]() { in.Input(); });
    });
    Check("Order::Input",
          in.GetOrderID() == "O9" && in.GetCustomerID() == "C9" &&
          in.GetOrderDate() == "2026-10-25" && in.GetStatus() == "Cho xu ly" &&
          in.GetTotalAmount() == 123000);

    // Manager
    OrderManager m;
    Order o1("O1", "C001", "2026-10-23", OrderStatus::Pending, 100000);
    Order o2("O2", "C002", "2026-10-23", OrderStatus::Pending, 200000);
    Order o3("O3", "C003", "2026-10-24", OrderStatus::Pending, 300000);

    Check("Insert O1", m.Insert(o1));
    Check("Insert O2", m.Insert(o2));
    Check("Insert O3", m.Insert(o3));
    Check("Insert trung ma don bi tu choi", !m.Insert(o1));
    Check("Search O2", m.Search("O2") != NULL);
    Check("Search khong co", m.Search("NOPE") == NULL);

    string q = Capture([&]() { m.Show(); });
    Check("Show (queue) dung thu tu FIFO",
          Pos(q, "Order ID: O1") < Pos(q, "Order ID: O2") &&
          Pos(q, "Order ID: O2") < Pos(q, "Order ID: O3"));

    Order out;
    Check("ProcessNext tra ve O1 va doi trang thai",
          m.ProcessNext(out) && out.GetOrderID() == "O1" &&
          out.GetStatus() == OrderStatus::Processed);
    Check("Don da xu ly van con trong lich su (Hash)", m.Search("O1") != NULL);

    string q2 = Capture([&]() { m.Show(); });
    Check("Queue khong con O1", !Has(q2, "Order ID: O1") && Has(q2, "Order ID: O2"));
    string hist = Capture([&]() { m.ShowHistory(); });
    Check("ShowHistory van co ca O1, O2, O3",
          Has(hist, "Order ID: O1") && Has(hist, "Order ID: O2") && Has(hist, "Order ID: O3"));

    Check("Delete nullptr", !m.Delete(NULL));
    Check("Delete don dang cho (O2, giua queue)", m.Delete(m.Search("O2")));
    Check("O2 bien mat khoi Hash", m.Search("O2") == NULL);
    string q3 = Capture([&]() { m.Show(); });
    Check("Queue chi con O3", !Has(q3, "Order ID: O2") && Has(q3, "Order ID: O3"));

    Check("ProcessNext tiep theo la O3",
          m.ProcessNext(out) && out.GetOrderID() == "O3");
    Check("ProcessNext khi queue rong -> false", !m.ProcessNext(out));
    Check("Delete don da xu ly (O1, khong nam trong queue)", m.Delete(m.Search("O1")));
    Check("Sau khi xoa, Insert lai O1 duoc", m.Insert(o1));

    // Luu / doc file
    const string pathOrder = "test_tmp_order.csv";
    Check("OrderManager::SaveToFile", m.SaveToFile(pathOrder));
    OrderManager mOrder;
    Check("OrderManager::LoadFromFile doc du don hang", mOrder.LoadFromFile(pathOrder) == m.GetTotalCount());
    Check("OrderManager::LoadFromFile khong ton tai -> -1", mOrder.LoadFromFile("khong_co_file.csv") == -1);
    remove(pathOrder.c_str());
}

// ---------------------------------------------------------------- ORDER DETAIL

static void TestOrderDetail() {
    Section("ORDER DETAIL");

    OrderDetail def;
    Check("OrderDetail mac dinh",
          def.GetOrderID().empty() && def.GetShoesID().empty() &&
          def.GetQuantity() == 0 && def.GetUnitPrice() == 0 && def.GetSubTotal() == 0);

    OrderDetail d1("O1", "S1", 2, 100000);
    OrderDetail d2("O1", "S2", 1, 500000);
    OrderDetail d3("O2", "S1", 3, 100000);
    Check("GetSubTotal = Quantity * UnitPrice", d1.GetSubTotal() == 200000);
    Check("OrderDetail::ToLine", d1.ToLine() == "O1,S1,2,100000");

    OrderDetail r;
    Check("OrderDetail::FromLine hop le",
          OrderDetail::FromLine("O1,S1,2,100000", r) && r.GetOrderID() == "O1" &&
          r.GetShoesID() == "S1" && r.GetQuantity() == 2 && r.GetUnitPrice() == 100000);
    Check("OrderDetail::FromLine sai so", !OrderDetail::FromLine("O1,S1,abc,1", r));
    Check("OrderDetail::FromLine thieu truong", !OrderDetail::FromLine("O1,S1,2", r));
    Check("OrderDetail::FromLine thua truong", !OrderDetail::FromLine("O1,S1,2,100,extra", r));

    OrderDetail in;
    FeedInput("O7\nS7\n4\n250000\n", [&]() {
        Capture([&]() { in.Input(); });
    });
    Check("OrderDetail::Input",
          in.GetOrderID() == "O7" && in.GetShoesID() == "S7" &&
          in.GetQuantity() == 4 && in.GetUnitPrice() == 250000);

    OrderDetailManager m;
    Check("Insert d1", m.Insert(d1));
    Check("Insert d2", m.Insert(d2));
    Check("Insert d3", m.Insert(d3));
    Check("Insert trung cap (OrderID, ShoesID) bi tu choi", !m.Insert(d1));
    Check("Insert so luong 0 bi tu choi", !m.Insert(OrderDetail("O3", "S1", 0, 1)));
    Check("Insert so luong am bi tu choi", !m.Insert(OrderDetail("O3", "S1", -2, 1)));
    Check("Insert OrderID rong bi tu choi", !m.Insert(OrderDetail("", "S1", 1, 1)));
    Check("Insert ShoesID rong bi tu choi", !m.Insert(OrderDetail("O3", "", 1, 1)));

    Check("GetCount = 3", m.GetCount() == 3);
    Check("CountByOrder(O1) = 2", m.CountByOrder("O1") == 2);
    Check("TotalByOrder(O1) = 700000", m.TotalByOrder("O1") == 700000);
    Check("TotalByOrder don khong ton tai = 0", m.TotalByOrder("NOPE") == 0);
    Check("Search (O1, S2)", m.Search("O1", "S2") != NULL);
    Check("Search cap khong co", m.Search("O9", "S1") == NULL);

    int n = -1;
    string out = Capture([&]() { n = m.ShowByOrder("O1"); });
    Check("ShowByOrder(O1) tra ve 2 va in dung",
          n == 2 && Has(out, "Shoes ID: S1") && Has(out, "Shoes ID: S2") &&
          !Has(out, "Order ID: O2"));

    // Luu / doc file
    const string path = "test_tmp_orderdetail.csv";
    Check("SaveToFile", m.SaveToFile(path));
    OrderDetailManager m2;
    Check("LoadFromFile tra ve 3", m2.LoadFromFile(path) == 3);
    Check("Du lieu sau khi doc lai dung",
          m2.GetCount() == 3 && m2.TotalByOrder("O1") == 700000);
    OrderDetailManager m3;
    Check("LoadFromFile file khong ton tai -> -1", m3.LoadFromFile("khong_co_file.csv") == -1);

    WriteFile(path, "O1,S1,2,100000\nday la dong sai\nO1,S1,5,100\n");
    OrderDetailManager m4;
    Check("LoadFromFile bo qua dong sai va dong trung (chi doc duoc 1)",
          m4.LoadFromFile(path) == 1 && m4.GetCount() == 1);
    remove(path.c_str());

    // Xoa
    Check("Delete nullptr", !m.Delete(NULL));
    Check("DeleteByOrder(O1) xoa 2 dong", m.DeleteByOrder("O1") == 2);
    Check("Sau xoa: GetCount = 1", m.GetCount() == 1);
    Check("Sau xoa: (O1, S1) khong con", m.Search("O1", "S1") == NULL);
    Check("Delete mot dong don le", m.Delete(m.Search("O2", "S1")) && m.GetCount() == 0);
    Check("DeleteByOrder don khong ton tai = 0", m.DeleteByOrder("NOPE") == 0);
}

// ---------------------------------------------------------------- PAYMENT

static void TestPayment() {
    Section("PAYMENT / PAYMENT MANAGER");

    Payment p;
    Check("Payment mac dinh: Status = Wait (PaymentStatus::Wait)",
          p.getPaymentId().empty() && p.getAmount() == 0 &&
          p.getStatus() == PaymentStatus::Wait);
    Check("Hang so PaymentStatus",
          PaymentStatus::Wait == "Wait" && PaymentStatus::Success == "Success" &&
          PaymentStatus::Failed == "Failed");

    // Yeu cau Buoc 1.3: Output() phai la const
    const Payment cp("P0", "O0", 1000, "2026-10-23", "Cash", PaymentStatus::Success);
    string o = Capture([&]() { cp.Output(); });
    Check("Payment::Output() goi duoc tren doi tuong const", Has(o, "P0") && Has(o, "O0"));

    Check("Payment::ToLine", cp.ToLine() == "P0,O0,1000,2026-10-23,Cash,Success");
    Payment r;
    Check("Payment::FromLine hop le",
          Payment::FromLine("P1,O1,800000,2026-10-23,Cash,Success", r) &&
          r.getPaymentId() == "P1" && r.getOrderId() == "O1" && r.getAmount() == 800000 &&
          r.getPaymentDate() == "2026-10-23" && r.getPaymentMethod() == "Cash" &&
          r.getStatus() == "Success");
    Check("Payment::FromLine thieu truong", !Payment::FromLine("P1,O1,800000,2026-10-23,Cash", r));
    Check("Payment::FromLine thua truong", !Payment::FromLine("P1,O1,1,d,m,s,extra", r));
    Check("Payment::FromLine ID rong", !Payment::FromLine(",O1,1,d,m,s", r));

    // Manager (capacity ban dau = 1 de kiem tra Grow)
    PaymentManager m(1);
    Check("Add P1", m.Add(Payment("P1", "O1", 800000, "2026-10-23", "Cash", PaymentStatus::Success)));
    Check("Add P2 (kich hoat Grow)", m.Add(Payment("P2", "O2", 250000, "2026-10-24", "Card", PaymentStatus::Wait)));
    Check("Add P3", m.Add(Payment("P3", "O3", 100000, "2026-10-24", "Card", PaymentStatus::Success)));
    Check("Add P4", m.Add(Payment("P4", "O4", 50000, "2026-10-24", "Cash", PaymentStatus::Failed)));
    Check("Add trung ID bi tu choi", !m.Add(Payment("P1", "O9", 1, "d", "m", "s")));
    Check("Add ID rong bi tu choi", !m.Add(Payment("", "O9", 1, "d", "m", "s")));
    Check("GetCount = 4", m.GetCount() == 4);

    Payment* f = m.Search("P3");
    Check("Search P3", f != NULL && f->getAmount() == 100000);
    Check("Search khong co", m.Search("NOPE") == NULL);

    Check("CountByStatus(Success) = 2", m.CountByStatus(PaymentStatus::Success) == 2);
    Check("CountByStatus(Wait) = 1", m.CountByStatus(PaymentStatus::Wait) == 1);
    Check("TotalRevenue chi tinh Success = 900000", m.TotalRevenue() == 900000);
    Check("RevenueByMethod(Cash) = 800000", m.RevenueByMethod("Cash") == 800000);
    Check("RevenueByMethod(Card) = 100000", m.RevenueByMethod("Card") == 100000);
    Check("RevenueByDate(2026-10-23) = 800000", m.RevenueByDate("2026-10-23") == 800000);
    Check("RevenueByDate(2026-10-24) = 100000", m.RevenueByDate("2026-10-24") == 100000);
    Check("RevenueByDate(2026-10) = 900000 (khop tien to)", m.RevenueByDate("2026-10") == 900000);

    int n = -1;
    string byStatus = Capture([&]() { n = m.ShowByStatus(PaymentStatus::Success); });
    Check("ShowByStatus(Success) tra ve 2", n == 2 && Has(byStatus, "P1") && Has(byStatus, "P3"));
    string byDate = Capture([&]() { n = m.ShowByDate("2026-10-24"); });
    Check("ShowByDate(2026-10-24) tra ve 3", n == 3);

    string sorted = Capture([&]() { m.ShowMaxToMin(); });
    Check("ShowMaxToMin: P1 > P2 > P3 > P4",
          Pos(sorted, "Payment ID: P1") < Pos(sorted, "Payment ID: P2") &&
          Pos(sorted, "Payment ID: P2") < Pos(sorted, "Payment ID: P3") &&
          Pos(sorted, "Payment ID: P3") < Pos(sorted, "Payment ID: P4"));
    string orig = Capture([&]() { m.Show(); });
    Check("ShowMaxToMin khong doi thu tu danh sach goc",
          Pos(orig, "Payment ID: P3") < Pos(orig, "Payment ID: P4") &&
          Pos(orig, "Payment ID: P2") < Pos(orig, "Payment ID: P3"));

    PaymentManager emptyM;
    string e = Capture([&]() { emptyM.Show(); });
    Check("Show tren danh sach rong", Has(e, "Chua co"));

    const string path = "test_tmp_payment.csv";
    Check("SaveToFile", m.SaveToFile(path));
    PaymentManager m2;
    Check("LoadFromFile tra ve 4", m2.LoadFromFile(path) == 4);
    Check("Du lieu sau khi doc lai dung",
          m2.GetCount() == 4 && m2.TotalRevenue() == 900000);
    Check("LoadFromFile file khong ton tai -> -1", m2.LoadFromFile("khong_co_file.csv") == -1);
    remove(path.c_str());
}

// ---------------------------------------------------------------- STOCK TRANSACTION

static void TestStockTransaction() {
    Section("STOCK TRANSACTION / MANAGER");

    StockTransaction def;
    Check("StockTransaction mac dinh (Type = Import, SL = 0)",
          def.GetTransactionId().empty() && def.GetType() == "Import" &&
          def.GetQuantity() == 0 && def.GetTotalValue() == 0);

    StockTransaction t1("T1", "S1", "Import", 10, 100000, "2026-10-23");
    Check("GetTotalValue = SL * Don gia", t1.GetTotalValue() == 1000000);
    Check("StockTransaction::ToLine", t1.ToLine() == "T1,S1,Import,10,100000,2026-10-23");

    StockTransaction r;
    Check("StockTransaction::FromLine hop le",
          StockTransaction::FromLine("T1,S1,Import,10,100000,2026-10-23 10:00", r) &&
          r.GetTransactionId() == "T1" && r.GetShoeId() == "S1" && r.GetType() == "Import" &&
          r.GetQuantity() == 10 && r.GetUnitPrice() == 100000 &&
          r.GetTransactionDate() == "2026-10-23 10:00");
    Check("StockTransaction::FromLine thieu truong", !StockTransaction::FromLine("T1,S1,Import,10", r));
    Check("StockTransaction::FromLine thua truong",
          !StockTransaction::FromLine("T1,S1,Import,10,100000,2026-10-23,extra", r));
    Check("StockTransaction::FromLine ID rong",
          !StockTransaction::FromLine(",S1,Import,10,100000,d", r));

    StockTransactionManager m(1);   // capacity 1 de kiem tra Grow
    Check("Add T1", m.Add(t1));
    Check("Add T2 (Export, kich hoat Grow)",
          m.Add(StockTransaction("T2", "S1", "Export", 3, 150000, "2026-10-24")));
    Check("Add T3", m.Add(StockTransaction("T3", "S2", "Import", 5, 200000, "2026-10-24")));
    Check("Add trung ID bi tu choi", !m.Add(t1));
    Check("Add ID rong bi tu choi", !m.Add(StockTransaction("", "S1", "Import", 1, 1, "d")));
    Check("Add loai khong hop le bi tu choi",
          !m.Add(StockTransaction("T9", "S1", "Sell", 1, 1, "d")));
    Check("Add so luong <= 0 bi tu choi",
          !m.Add(StockTransaction("T9", "S1", "Import", 0, 1, "d")));
    Check("GetCount = 3", m.GetCount() == 3);

    Check("Search T2", m.Search("T2") != NULL && m.Search("T2")->GetType() == "Export");
    Check("Search khong co", m.Search("NOPE") == NULL);

    Check("CountByType(Import) = 2", m.CountByType("Import") == 2);
    Check("CountByType(Export) = 1", m.CountByType("Export") == 1);
    Check("TotalQuantityByType(Import) = 15", m.TotalQuantityByType("Import") == 15);
    Check("TotalQuantityByType(Export) = 3", m.TotalQuantityByType("Export") == 3);
    Check("NetQuantityByShoe(S1) = 10 - 3 = 7", m.NetQuantityByShoe("S1") == 7);
    Check("NetQuantityByShoe(S2) = 5", m.NetQuantityByShoe("S2") == 5);
    Check("TotalValueByType(Import) = 2000000", m.TotalValueByType("Import") == 2000000);
    Check("TotalValueByType(Export) = 450000", m.TotalValueByType("Export") == 450000);

    int n = -1;
    Capture([&]() { n = m.ShowByType("Import"); });
    Check("ShowByType(Import) = 2", n == 2);
    Capture([&]() { n = m.ShowByShoe("S1"); });
    Check("ShowByShoe(S1) = 2", n == 2);
    Capture([&]() { n = m.ShowByDate("2026-10-24"); });
    Check("ShowByDate(2026-10-24) = 2", n == 2);

    string sorted = Capture([&]() { m.ShowMaxToMin(); });
    // T1 = 1,000,000 ; T3 = 1,000,000 ; T2 = 450,000 -> T2 phai o cuoi
    Check("ShowMaxToMin: T2 (gia tri nho nhat) o cuoi",
          Pos(sorted, "Transaction ID: T1") < Pos(sorted, "Transaction ID: T2") &&
          Pos(sorted, "Transaction ID: T3") < Pos(sorted, "Transaction ID: T2"));

    StockTransactionManager emptyM;
    string e = Capture([&]() { emptyM.Show(); });
    Check("Show tren danh sach rong", Has(e, "Chua co"));

    const string path = "test_tmp_stock.csv";
    Check("SaveToFile", m.SaveToFile(path));
    StockTransactionManager m2;
    Check("LoadFromFile tra ve 3", m2.LoadFromFile(path) == 3);
    Check("Du lieu sau khi doc lai dung",
          m2.GetCount() == 3 && m2.NetQuantityByShoe("S1") == 7);
    Check("LoadFromFile file khong ton tai -> -1", m2.LoadFromFile("khong_co_file.csv") == -1);
    remove(path.c_str());
}

// ---------------------------------------------------------------- main

int main() {
    TestShoes();
    TestHashTable();
    TestMaxHeap();
    TestShoesManager();
    TestCustomer();
    TestOrder();
    TestOrderDetail();
    TestPayment();
    TestStockTransaction();

    cout << "\n========== KET QUA ==========\n";
    cout << "PASS: " << g_pass << "\n";
    cout << "FAIL: " << g_fail << "\n";
    return g_fail == 0 ? 0 : 1;
}