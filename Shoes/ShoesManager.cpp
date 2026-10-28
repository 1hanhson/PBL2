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

bool ShoesManager::Insert(const Shoes& s,Node* p){
    if(this->Heap.Size==this->Heap.Capacity)
        return false;
    Node* NewNode=new Node(s);
    if(p==NULL)
        p=this->pL;
    NewNode->Next=p->Next;
    NewNode->Previous=p;
    if(NewNode->Next!=NULL)
        NewNode->Next->Previous=NewNode;
    p->Next=NewNode;
    this->Nos++;

    //insert vo hash, tree, heap
    this->Hash.Insert(NewNode);
    this->Tree.Insert(NewNode);
    this->Heap.Insert(NewNode);
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