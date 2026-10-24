
#include "OrderManager.h"

bool OrderManager::Insert(const Order& o){
    if(this->Hash.Search(o.GetOrderID()) != NULL)
        return false;

    NodeO* p = new NodeO(o);

    if(!this->Hash.Insert(p)){
        delete p;
        return false;
    }

    if(!this->Q.Enqueue(p)){
        this->Hash.Delete(p);
        delete p;
        return false;
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

bool OrderManager::ProcessNext(Order& o){
    NodeO* p = this->Q.Dequeue();

    if(p == NULL)
        return false;

    p->data.SetStatus("Da xu ly");
    o = p->data;

    // Khong xoa khoi HashTable
    // De giu lai don hang trong lich su

    return true;
}
