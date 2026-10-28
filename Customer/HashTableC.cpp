#include "HashTableC.h"

HashTableC::HashTableC(const int& M){
    this->M = M;
    this->Table = new NodeC*[this->M];

    for(int i = 0; i < this->M; i++){
        this->Table[i] = NULL;
    }
}

HashTableC::~HashTableC(){
    delete[] this->Table;
}

int HashTableC::HashFunction(const string& ID) const{
    unsigned long long sum = 0;

    for(int i = 0; i < ID.length(); i++){
        sum += ID[i];
    }

    return sum % this->M;
}

bool HashTableC::Insert(NodeC* p){
    if(p == NULL)
        return false;

    int k = this->HashFunction(p->data.GetID());

    p->NextHash = this->Table[k];
    this->Table[k] = p;

    return true;
}

bool HashTableC::Delete(NodeC* p){
    if(p == NULL)
        return false;

    int k = this->HashFunction(p->data.GetID());
    NodeC* tmp = this->Table[k];

    if(tmp == NULL)
        return false;

    if(tmp == p){
        this->Table[k] = p->NextHash;
        p->NextHash = NULL;
        return true;
    }

    while(tmp != NULL && tmp->NextHash != p){
        tmp = tmp->NextHash;
    }

    if(tmp == NULL)
        return false;

    tmp->NextHash = p->NextHash;
    p->NextHash = NULL;

    return true;
}

NodeC* HashTableC::Search(const string& ID){
    int k = this->HashFunction(ID);
    NodeC* tmp = this->Table[k];

    while(tmp != NULL && tmp->data.GetID() != ID){
        tmp = tmp->NextHash;
    }

    return tmp;
}
