#include "QueueO.h"

QueueO::QueueO(){
    this->Front=NULL;
    this->Rear=NULL;
    this->Noo=0;
}

QueueO::~QueueO(){
    this->Front = NULL;
    this->Rear = NULL;
    this->Noo = 0;
}

bool QueueO::IsEmpty(){
    return this->Noo==0;
}

bool QueueO::Enqueue(NodeO* NewNode){
    if(NewNode==NULL)
        return false;
    if(this->IsEmpty()){
        this->Front=NewNode;
        this->Rear=NewNode;
    }
    else{
        this->Rear->Next=NewNode;
        this->Rear=NewNode;
    }
    this->Noo++;
    return true;
}

NodeO* QueueO::Dequeue(){
    if(this->IsEmpty())
        return NULL;

    NodeO* tmp = this->Front;

    this->Front = this->Front->Next;

    if(this->Front == NULL)
        this->Rear = NULL;

    tmp->Next = NULL;
    this->Noo--;

    return tmp;
}

void QueueO::Show() const{
    NodeO *tmp=this->Front;
    while(tmp!=NULL){
        tmp->data.Output();
        tmp=tmp->Next;
    }
}