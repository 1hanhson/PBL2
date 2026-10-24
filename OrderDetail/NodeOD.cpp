#include "NodeOD.h"

NodeOD::NodeOD(){
    this->Next = NULL;
    this->Previous = NULL;
}

NodeOD::NodeOD(const OrderDetail& d){
    this->data = d;
    this->Next = NULL;
    this->Previous = NULL;
}