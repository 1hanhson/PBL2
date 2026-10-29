#include "OrderManager.h"
#include <fstream>

OrderManager::OrderManager(){}

// HashTable chứa MỌI đơn (kể cả đã xử lý), Queue chỉ là tập con
// => duyệt HashTable để delete, tránh delete 2 lần.
OrderManager::~OrderManager(){
    for(int i = 0; i < this->Hash.M; i++){
        NodeO* p = this->Hash.Table[i];
        while(p != NULL){
            NodeO* nxt = p->NextHash;
            delete p;
            p = nxt;
        }
        this->Hash.Table[i] = NULL;
    }
}

bool OrderManager::Insert(const Order& o){
    if(this->Hash.Search(o.GetOrderID()) != NULL)
        return false;

    NodeO* p = new NodeO(o);

    if(!this->Hash.Insert(p)){
        delete p;
        return false;
    }

    // Chi cho don hang dang o trang thai Pending ("Cho xu ly") vao Queue de xu ly;
    // Cac don da xu ly chi luu vao HashTable de tra cuu lich su, tranh bi xu ly lap lai
    if(o.GetStatus() == OrderStatus::Pending){
        if(!this->Q.Enqueue(p)){
            this->Hash.Delete(p);
            delete p;
            return false;
        }
    }

    return true;
}

void OrderManager::Show() const{
    this->Q.Show();
}

void OrderManager::ShowHistory() const{
    for(int i = 0; i < this->Hash.M; i++){
        NodeO* p = this->Hash.Table[i];

        while(p != NULL){
            p->data.Output();
            p = p->NextHash;
        }
    }
}

NodeO* OrderManager::Search(const string& ID){
    return this->Hash.Search(ID);
}

bool OrderManager::Delete(NodeO* p){
    if(p == NULL)
        return false;

    NodeO* tmp = this->Q.Front;
    NodeO* prev = NULL;

    while(tmp != NULL && tmp != p){
        prev = tmp;
        tmp = tmp->Next;
    }

    // Neu don dang cho xu ly thi go khoi Queue
    if(tmp != NULL){
        if(prev == NULL)
            this->Q.Front = p->Next;
        else
            prev->Next = p->Next;

        if(this->Q.Rear == p)
            this->Q.Rear = prev;

        this->Q.Noo--;
    }

    // Go khoi HashTable
    if(!this->Hash.Delete(p))
        return false;

    delete p;
    return true;
}

bool OrderManager::ProcessNext(Order& o) {
    NodeO* p = this->Q.Dequeue();

    if (p == NULL)
        return false;

    p->data.SetStatus(OrderStatus::Processed);
    o = p->data;

    // Khong xoa khoi HashTable de giu lai don hang trong lich su
    return true;
}

// Lay so luong don hang dang cho xu ly trong Queue
int OrderManager::GetPendingCount() const {
    return this->Q.Noo;
}

// Lay tong so luong don hang trong toan bo lich su (HashTable)
int OrderManager::GetTotalCount() const {
    int total = 0;
    for(int i = 0; i < this->Hash.M; i++){
        NodeO* p = this->Hash.Table[i];
        while(p != NULL){
            total++;
            p = p->NextHash;
        }
    }
    return total;
}

// Luu toan bo lich su don hang ra file .txt/.csv theo dinh dang ToLine()
bool OrderManager::SaveToFile(const string& path) const {
    ofstream f(path.c_str());
    if(!f.is_open())
        return false;
    for(int i = 0; i < this->Hash.M; i++){
        NodeO* p = this->Hash.Table[i];
        while(p != NULL){
            f << p->data.ToLine() << '\n';
            p = p->NextHash;
        }
    }
    return true;
}

// Doc lich su don hang tu file .txt/.csv va tu dong phan loai vao Queue va HashTable
// Tra ve -1 neu mo file that bai, nguoc lai tra ve so don hang da doc duoc
int OrderManager::LoadFromFile(const string& path) {
    ifstream f(path.c_str());
    if(!f.is_open())
        return -1;
    int count = 0;
    string line;
    while(getline(f, line)){
        Order o;
        if(Order::FromLine(line, o) && this->Insert(o))
            count++;
    }
    return count;
}
