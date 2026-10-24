#include "NodeO.h"

NodeO::NodeO(){
    this->Next = NULL;
    this->NextHash=NULL;
}

NodeO::NodeO(const Order& o){
    this->data = o;
    this->Next = NULL;
    this->NextHash=NULL;
}
