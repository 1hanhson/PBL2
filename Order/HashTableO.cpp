
#include "HashTableO.h"

HashTableO::HashTableO(const int& M) {
    this->M = M;
    this->Table = new NodeO*[this->M];

    for (int i = 0; i < this->M; i++) {
        this->Table[i] = NULL;
    }
}

HashTableO::~HashTableO() {
    delete[] this->Table;
}

int HashTableO::HashFunction(const string& ID) const {
    unsigned long long sum = 0;

    for (int i = 0; i < ID.length(); i++) {
        sum += ID[i];
    }

    return sum % this->M;
}

NodeO* HashTableO::Search(const string& ID) const {
    int k = this->HashFunction(ID);
    NodeO* tmp = this->Table[k];

    while (tmp != NULL &&
           tmp->data.GetOrderID() != ID) {
        tmp = tmp->NextHash;
    }

    return tmp;
}

bool HashTableO::Insert(NodeO* p) {
    if (p == NULL)
        return false;

    // Khong cho phep trung ma don hang
    if (this->Search(p->data.GetOrderID()) != NULL)
        return false;

    int k = this->HashFunction(p->data.GetOrderID());

    p->NextHash = this->Table[k];
    this->Table[k] = p;

    return true;
}


bool HashTableO::Delete(NodeO* p) {
    if (p == NULL)
        return false;

    int k = this->HashFunction(p->data.GetOrderID());

    NodeO* tmp = this->Table[k];

    if (tmp == NULL)
        return false;
    else if (tmp == p) {
        this->Table[k] = p->NextHash;
        p->NextHash = NULL;
        return true;
    }

    while (tmp != NULL && tmp->NextHash != p) {
        tmp = tmp->NextHash;
    }

    if (tmp == NULL)
        return false;

    tmp->NextHash = p->NextHash;
    p->NextHash = NULL;

    return true;
}

