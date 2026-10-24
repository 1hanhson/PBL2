#include "OrderDetailManager.h"
#include <fstream>

OrderDetailManager::OrderDetailManager(){
    this->pL = new NodeOD;
    this->Nod = 0;
}

OrderDetailManager::~OrderDetailManager(){
    while(this->pL != NULL){
        NodeOD* tmp = this->pL;
        this->pL = this->pL->Next;
        delete tmp;
    }
}

// Them chi tiet don hang, tra ve false neu so luong <= 0,
// ma rong, hoac cap (OrderID, ShoesID) da ton tai
bool OrderDetailManager::Insert(const OrderDetail& d, NodeOD* p){
    if(d.GetOrderID() == "" || d.GetShoesID() == "" || d.GetQuantity() <= 0)
        return false;
    if(this->Search(d.GetOrderID(), d.GetShoesID()) != NULL)
        return false;

    NodeOD* NewNode = new NodeOD(d);

    // Neu khong truyen vi tri, chen sau node dau gia
    if(p == NULL)
        p = this->pL;

    NewNode->Next = p->Next;
    NewNode->Previous = p;

    if(NewNode->Next != NULL)
        NewNode->Next->Previous = NewNode;

    p->Next = NewNode;
    this->Nod++;
    return true;
}

void OrderDetailManager::Show(){
    NodeOD* tmp = this->pL->Next;
    while(tmp != NULL){
        tmp->data.Output();
        tmp = tmp->Next;
    }
}

// In cac chi tiet cua 1 don hang, tra ve so dong tim duoc
int OrderDetailManager::ShowByOrder(const string& OrderID){
    int count = 0;
    NodeOD* tmp = this->pL->Next;
    while(tmp != NULL){
        if(tmp->data.GetOrderID() == OrderID){
            tmp->data.Output();
            count++;
        }
        tmp = tmp->Next;
    }
    return count;
}

NodeOD* OrderDetailManager::Search(const string& OrderID, const string& ShoesID){
    NodeOD* tmp = this->pL->Next;
    while(tmp != NULL){
        if(tmp->data.GetOrderID() == OrderID && tmp->data.GetShoesID() == ShoesID)
            return tmp;
        tmp = tmp->Next;
    }
    return NULL;
}

bool OrderDetailManager::Delete(NodeOD* p){
    if(p == NULL || p == this->pL)
        return false;

    p->Previous->Next = p->Next;
    if(p->Next != NULL)
        p->Next->Previous = p->Previous;

    this->Nod--;
    delete p;
    return true;
}

// Xoa toan bo chi tiet cua 1 don hang, tra ve so dong da xoa
int OrderDetailManager::DeleteByOrder(const string& OrderID){
    int count = 0;
    NodeOD* tmp = this->pL->Next;
    while(tmp != NULL){
        NodeOD* nxt = tmp->Next;
        if(tmp->data.GetOrderID() == OrderID){
            this->Delete(tmp);
            count++;
        }
        tmp = nxt;
    }
    return count;
}

int OrderDetailManager::GetCount(){
    return this->Nod;
}

int OrderDetailManager::CountByOrder(const string& OrderID){
    int count = 0;
    NodeOD* tmp = this->pL->Next;
    while(tmp != NULL){
        if(tmp->data.GetOrderID() == OrderID)
            count++;
        tmp = tmp->Next;
    }
    return count;
}

// Tong tien cua 1 don hang (dung de gan vao Order::TotalAmount)
long long OrderDetailManager::TotalByOrder(const string& OrderID){
    long long sum = 0;
    NodeOD* tmp = this->pL->Next;
    while(tmp != NULL){
        if(tmp->data.GetOrderID() == OrderID)
            sum += tmp->data.GetSubTotal();
        tmp = tmp->Next;
    }
    return sum;
}

// Luu moi chi tiet thanh 1 dong, tra ve false neu khong ghi duoc file
bool OrderDetailManager::SaveToFile(const string& path){
    ofstream f(path.c_str());
    if(!f)
        return false;
    NodeOD* tmp = this->pL->Next;
    while(tmp != NULL){
        f << tmp->data.ToLine() << '\n';
        tmp = tmp->Next;
    }
    return true;
}

// Doc tu file, dong sai dinh dang hoac trung cap (OrderID, ShoesID) thi bo qua
// Tra ve -1 neu khong mo duoc file, nguoc lai tra ve so dong doc duoc
int OrderDetailManager::LoadFromFile(const string& path){
    ifstream f(path.c_str());
    if(!f)
        return -1;
    int count = 0;
    string line;
    while(getline(f, line)){
        OrderDetail d;
        if(OrderDetail::FromLine(line, d) && this->Insert(d))
            count++;
    }
    return count;
}