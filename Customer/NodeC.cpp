#include "NodeC.h"

NodeC::NodeC(){
    this->Next = NULL;
    this->Previous = NULL;
    this->NextHash = NULL;
}

NodeC::NodeC(const Customer& c){
    this->data = c;
    this->Next = NULL;
    this->Previous = NULL;
    this->NextHash = NULL;
}
