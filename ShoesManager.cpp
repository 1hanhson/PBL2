#include "ShoesManager.h"
const int TRUE=1;
const int FALSE=0;

ShoesManager::ShoesManager() : Hash(101){
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

int ShoesManager::Insert(const Shoes& s,Node* p){
    Node* NewNode=new Node(s);
    if(NewNode==NULL)
        return FALSE;
    if(p==NULL)
        p=this->pL;
    NewNode->Next=p->Next;
    NewNode->Previous=p;
    if(NewNode->Next!=NULL)
        NewNode->Next->Previous=NewNode;
    p->Next=NewNode;
    this->Nos++;

    //insert vo hash
    this->Hash.Insert(NewNode);
    //insert vo tree
    this->Tree.Insert(NewNode);
    return TRUE;
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

int ShoesManager::Delete(Node* p){
    if(p==NULL || p==this->pL)
        return FALSE;
    p->Previous->Next=p->Next;
    if(p->Next!=NULL)
        p->Next->Previous=p->Previous;
    this->Nos--;

    //delete khoi hash
    this->Hash.Delete(p);

    //delete khoi tree
    this->Tree.Delete(p);
    return TRUE;
}

Node* ShoesManager::Search(const string& ID){
    return this->Hash.Search(ID);
}