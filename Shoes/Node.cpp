#include "Node.h"

Node::Node(){
    this->Next=NULL;
    this->Previous=NULL;
    this->NextHash=NULL;
    this->Left=NULL;
    this->Right=NULL;
    this->Parent=NULL;
}

Node::Node(const Shoes& s){
    this->data=s;
    this->Next=NULL;
    this->Previous=NULL;
    this->NextHash=NULL;
}

// Node::Node(const Node& n){
//     this->data=n.data;
//     this->Left=NULL;
//     this->Right=NULL;
//     this->Parent=NULL;
//     this->Next=NULL;
//     this->Previous=NULL;
//     this->NextHash=NULL;
// }


Node& Node::operator=(const Node& n){
    this->data=n.data;
    this->Left=NULL;
    this->Right=NULL;
    this->Next=NULL;
    this->Previous=NULL;
    this->NextHash=NULL;
    return *this;
}