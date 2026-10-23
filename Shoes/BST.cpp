#include "BST.h"
#include <iostream>
using namespace std;
BST::BST() {
    this->TreeRoot = NULL;
}

BST::~BST() {
}

void BST::MinToMax(Node* x){
    if(x!=NULL){
        MinToMax(x->Left);
        x->data.Output();
        MinToMax(x->Right);
    }
}

void BST::MaxToMin(Node* x){
    if(x!=NULL){
        MaxToMin(x->Right);
        x->data.Output();
        MaxToMin(x->Left);
    }
}

Node* BST::Maximum(Node* x){
    while(x->Right!=NULL)
        x=x->Right;
    return x;
}

Node* BST::Minimum(Node* x){
    while(x->Left!=NULL)
        x=x->Left;
    return x;
}

void BST::Insert(Node* n){
    Node* z=new Node;
    z->data=n->data;
    Node* x=this->TreeRoot;
    Node* y=NULL;
    while(x!=NULL){
        y=x;
        if(x->data.GetPrice()>n->data.GetPrice())
            x=x->Left;
        else
            x=x->Right;
    }
    z->Parent=y;
    if(y==NULL)
        this->TreeRoot=z;
    else if(z->data.GetPrice() < y->data.GetPrice())
        y->Left=z;
    else    
        y->Right=z;
}

Node* BST::Successor(Node* x){
    if(x->Right!=NULL){
        return this->Minimum(x->Right);
    }
    Node *y=x->Parent;
    while(y!=NULL && x==y->Right){
        x=y;
        y=y->Parent;
    }
    return y;
}

Node* BST::Find(Node *tmp,const string& ID,const long long& Price){
    if(tmp==NULL || (tmp->data.GetID()==ID && tmp->data.GetPrice()==Price))
        return tmp;
    if(tmp->data.GetPrice() > Price)
        return this->Find(tmp->Left,ID,Price);
    else
        return this->Find(tmp->Right,ID,Price);
}

void BST::Delete(Node* n){
    Node *z=this->Find(this->TreeRoot,n->data.GetID(),n->data.GetPrice());
    Node *x,*y;
    if(z->Left==NULL || z->Right==NULL)
        y=z;
    else
        y=this->Successor(z);
    if(y->Left!=NULL)
        x=y->Left;
    else
        x=y->Right;
    if(x!=NULL)
        x->Parent=y->Parent;
    if(y->Parent==NULL)
        this->TreeRoot=x;
    else if(y->Parent->Left==y)
        y->Parent->Left=x;
    else
        y->Parent->Right=x;
    if(y!=z)
        y->data=z->data;
    delete y;
}

