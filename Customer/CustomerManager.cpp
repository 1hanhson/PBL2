#include "CustomerManager.h"
#include <fstream>

CustomerManager::CustomerManager() : Hash(101){
    this->pL = new NodeC;
    this->Noc = 0;
}

CustomerManager::~CustomerManager(){
    while(this->pL != NULL){
        NodeC* tmp = this->pL;
        this->pL = this->pL->Next;
        delete tmp;
    }
}

bool CustomerManager::Insert(const Customer& c, NodeC* p){
    if(c.GetID().empty() || this->Search(c.GetID()) != NULL)
        return false;

    NodeC* NewNode = new NodeC(c);

    if(p == NULL)
        p = this->pL;

    NewNode->Next = p->Next;
    NewNode->Previous = p;

    if(NewNode->Next != NULL)
        NewNode->Next->Previous = NewNode;

    p->Next = NewNode;
    this->Noc++;

    this->Hash.Insert(NewNode);
    return true;
}

void CustomerManager::Show(){
    NodeC* tmp = this->pL->Next;
    while(tmp != NULL){
        tmp->data.Output();
        tmp = tmp->Next;
    }
}

NodeC* CustomerManager::Search(const string& ID){
    return this->Hash.Search(ID);
}

bool CustomerManager::Delete(NodeC* p){
    if(p == NULL || p == this->pL)
        return false;

    if(!this->Hash.Delete(p))
        return false;

    p->Previous->Next = p->Next;
    if(p->Next != NULL)
        p->Next->Previous = p->Previous;

    this->Noc--;
    delete p;
    return true;
}

bool CustomerManager::Update(const string& ID, const Customer& c){
    // Chan loi cap nhat khach hang voi ma ID rong
    if(c.GetID().empty())
        return false;

    NodeC* p = this->Search(ID);
    if(p == NULL)
        return false;

    NodeC* q = this->Search(c.GetID());
    if(q != NULL && q != p)
        return false;

    if(!this->Hash.Delete(p))
        return false;

    p->data.SetID(c.GetID());
    p->data.SetName(c.GetName());
    p->data.SetPhone(c.GetPhone());
    p->data.SetAddress(c.GetAddress());

    this->Hash.Insert(p);
    return true;
}

// Lay tong so luong khach hang trong danh sach
int CustomerManager::GetCount() const{
    return this->Noc;
}

// Luu toan bo danh sach khach hang ra file .txt/.csv theo dinh dang ToLine()
bool CustomerManager::SaveToFile(const string& path) const{
    ofstream f(path.c_str());
    if(!f.is_open())
        return false;
    NodeC* tmp = this->pL->Next;
    while(tmp != NULL){
        f << tmp->data.ToLine() << '\n';
        tmp = tmp->Next;
    }
    return true;
}

// Doc du lieu khach hang tu file .txt/.csv va chen vao danh sach + bang bam
// Tra ve -1 neu mo file that bai, nguoc lai tra ve so khach hang doc duoc
int CustomerManager::LoadFromFile(const string& path){
    ifstream f(path.c_str());
    if(!f.is_open())
        return -1;
    int count = 0;
    string line;
    while(getline(f, line)){
        Customer c;
        if(Customer::FromLine(line, c) && this->Insert(c))
            count++;
    }
    return count;
}
