#include "ShoesManager.h"
#include <iostream>

using namespace std;

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
    this->Tree.Insert(NewNode);
    this->Heap.Insert(NewNode);
    return TRUE;
}

void ShoesManager::Show(){
    Node* tmp=this->pL->Next;
    while(tmp!=NULL){
        tmp->data.Output();
        tmp=tmp->Next;
    }
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
    return TRUE;
}

Node* ShoesManager::Search(const string& ID){
    return this->Hash.Search(ID);
}

void ShoesManager::ShowPriceLowToHigh() {
    std::cout << "\n--- SAN PHAM THEO GIA (THAP DEN CAO) ---\n";
    this->Tree.ShowLowToHigh(); 
}

void ShoesManager::ShowPriceHighToLow() {
    std::cout << "\n--- SAN PHAM THEO GIA (CAO DEN THAP) ---\n";
    this->Tree.ShowHighToLow(); 
}

void ShoesManager::ShowPriceRange(long long minPrice, long long maxPrice) {
    this->Tree.ShowPriceRange(minPrice, maxPrice);
}

void ShoesManager::SellShoe(const string& ID, const int& amount) {
    Node* target = this->Search(ID); 
    if (target != NULL) {
        int currentQuantity = target->data.GetQuantity();
        if (currentQuantity >= amount) {
            target->data.SetQuantity(currentQuantity - amount); 
            this->Heap.IncreaseSold(target, amount);
            cout << "Da ban " << amount << " doi giay " << ID << endl;
        } else {
            cout << "Khong du so luong ton kho!" << endl;
        }
    } else {
        cout << "Khong tim thay giay!" << endl;
    }
}

void ShoesManager::ShowTopSellers(const int& k) {
    this->Heap.ShowTop(k);
}