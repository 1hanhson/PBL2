#include "HashTable.h"

HashTable::HashTable(const int& M){
    this->M=M;
    this->Table=new Node*[this->M];
    for(int i=0;i<this->M;i++){
        this->Table[i]=NULL;
    }
}

HashTable::~HashTable() {
    delete[] this->Table;
}

int HashTable::HashFunction(const string& ID) const {
    unsigned long long sum = 0;

    for (size_t i = 0; i < ID.length(); i++)
        sum+=ID[i];
    return sum % this->M;
}

bool HashTable::Insert(Node *p){
    if(p==NULL)
        return false;
    int k=this->HashFunction(p->data.GetID());
    p->NextHash=this->Table[k];
    this->Table[k]=p;
    return true;
}

bool HashTable::Delete(Node *p){
    if(p==NULL)
        return false;
    int k=this->HashFunction(p->data.GetID());
    Node *tmp=this->Table[k];
    if(tmp==NULL)
        return false;
    if(tmp==p){
        this->Table[k]=p->NextHash;   // sửa: nối bucket với node kế tiếp, không gán NULL
        p->NextHash=NULL;
        return true;
    }
    while(tmp!=NULL && tmp->NextHash!=p){
        tmp=tmp->NextHash;
    }
    if(tmp==NULL)
        return false;
    tmp->NextHash = p->NextHash;
    p->NextHash=NULL;                 // thêm: ngắt node khỏi chuỗi
    return true;
}

Node* HashTable::Search(const string& ID){
    int k=this->HashFunction(ID);
    Node *tmp=this->Table[k];
    while(tmp!=NULL && tmp->data.GetID()!=ID){
        tmp=tmp->NextHash;
    }
    if(tmp==NULL)
        return NULL;
    return tmp;
}