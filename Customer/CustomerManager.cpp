#include "CustomerManager.h"

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
    // Kiem tra ma khach hang da ton tai
    if(this->Search(c.GetID()) != NULL)
        return false;

    NodeC* NewNode = new NodeC(c);

    // Neu khong truyen vi tri, chen sau node dau gia
    if(p == NULL)
        p = this->pL;

    // Chen vao danh sach lien ket doi
    NewNode->Next = p->Next;
    NewNode->Previous = p;

    if(NewNode->Next != NULL)
        NewNode->Next->Previous = NewNode;

    p->Next = NewNode;
    this->Noc++;

    // Chen vao Hash Table
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

    // Xoa khoi Hash Table
    if(!this->Hash.Delete(p))
        return false;

    // Xoa khoi danh sach lien ket doi
    p->Previous->Next = p->Next;

    if(p->Next != NULL)
        p->Next->Previous = p->Previous;

    this->Noc--;

    delete p;

    return true;
}

bool CustomerManager::Update(const string& ID, const Customer& c){
    NodeC* p = this->Search(ID);

    if(p == NULL)
        return false;

    // Neu ID moi da thuoc ve khach hang khac thi khong cap nhat
    NodeC* q = this->Search(c.GetID());

    if(q != NULL && q != p)
        return false;

    // Xoa node khoi Hash Table truoc khi sua ID
    if(!this->Hash.Delete(p))
        return false;

    // Cap nhat thong tin khach hang
    p->data.SetID(c.GetID());
    p->data.SetName(c.GetName());
    p->data.SetPhone(c.GetPhone());
    p->data.SetAddress(c.GetAddress());

    // Chen lai vao Hash Table voi ID moi
    this->Hash.Insert(p);

    return true;
}
