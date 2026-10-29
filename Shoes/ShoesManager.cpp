#include "ShoesManager.h"

ShoesManager::ShoesManager() : Hash(101), Heap(1000){
    this->pL=new Node;
    this->Nos=0;
}

ShoesManager::~ShoesManager(){
    while(this->pL!=NULL){
        Node* tmp=this->pL;
        this->pL=this->pL->Next;
        delete tmp;
    }
}

bool ShoesManager::Insert(const Shoes& s, Node* p) {
    // Kiem tra ma giay rong hoac da ton tai trong HashTable
    if (s.GetID().empty() || this->Hash.Search(s.GetID()) != NULL)
        return false;

    // Kiem tra MaxHeap da day chua
    if (this->Heap.Size == this->Heap.Capacity)
        return false;

    // Tao nut moi chua thong tin giay
    Node* NewNode = new Node(s);

    // Neu khong truyen p thi chen sau nut dau danh sach pL
    if (p == NULL)
        p = this->pL;

    // Chen nut moi vao danh sach lien ket kep
    NewNode->Next = p->Next;
    NewNode->Previous = p;

    // Cap nhat lien ket Previous cua nut phia sau
    if (NewNode->Next != NULL)
        NewNode->Next->Previous = NewNode;

    // Cap nhat lien ket Next cua nut p
    p->Next = NewNode;

    // Tang so luong nut trong danh sach
    this->Nos++;

    // Them nut moi vao HashTable de tim kiem theo ma giay
    this->Hash.Insert(NewNode);

    // Them nut moi vao BST de sap xep va tim kiem
    this->Tree.Insert(NewNode);

    // Them nut moi vao MaxHeap de quan ly theo thuoc tinh uu tien
    this->Heap.Insert(NewNode);

    // Them giay thanh cong
    return true;
}

void ShoesManager::Show(){
    Node* tmp=this->pL->Next;
    while(tmp!=NULL){
        tmp->data.Output();
        tmp=tmp->Next;
    }
}

void ShoesManager::ShowMinToMax(){
    this->Tree.MinToMax(this->Tree.TreeRoot);
}

bool ShoesManager::Delete(Node* p){
    if(p==NULL || p==this->pL)
        return false;

    //go khoi cac cau truc phu truoc (chung doc p->data)
    this->Hash.Delete(p);
    this->Tree.Delete(p);
    this->Heap.Remove(p);

    //go khoi danh sach lien ket doi
    p->Previous->Next=p->Next;
    if(p->Next!=NULL)
        p->Next->Previous=p->Previous;
    this->Nos--;

    delete p;
    return true;
}

Node* ShoesManager::Search(const string& ID){
    return this->Hash.Search(ID);
}

void ShoesManager::ShowMaxToMin(){
    this->Tree.MaxToMin(this->Tree.TreeRoot);
}

void ShoesManager::ShowTop(const int& k){
    this->Heap.ShowTop(k);
}

//tang so luong da ban theo ID, heap tu cap nhat
bool ShoesManager::IncreaseSold(const string& ID,const int& amount){
    Node* p=this->Search(ID);
    if(p==NULL)
        return false;
    return this->Heap.IncreaseSold(p,amount);
}