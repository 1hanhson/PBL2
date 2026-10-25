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
    if(x==NULL)
        return NULL;
    while(x->Right!=NULL)
        x=x->Right;
    return x;
}

Node* BST::Minimum(Node* x){
    if(x==NULL)
        return NULL;
    while(x->Left!=NULL)
        x=x->Left;
    return x;
}

Node* BST::Successor(Node* x){
    if(x==NULL)
        return NULL;
    if(x->Right!=NULL)
        return this->Minimum(x->Right);
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

void BST::Insert(Node* n){
    if(n==NULL)
        return;
    //node nay co the mang gia tri cu, reset truoc khi gan vao cay
    n->Left=NULL;
    n->Right=NULL;
    n->Parent=NULL;

    Node* x=this->TreeRoot;
    Node* y=NULL;
    while(x!=NULL){
        y=x;
        if(n->data.GetPrice() < x->data.GetPrice())
            x=x->Left;
        else
            x=x->Right;      //gia bang nhau di ve ben phai
    }
    n->Parent=y;
    if(y==NULL)
        this->TreeRoot=n;
    else if(n->data.GetPrice() < y->data.GetPrice())
        y->Left=n;
    else
        y->Right=n;
}

//thay cay con goc u bang cay con goc v (v co the NULL)
void BST::Transplant(Node* u,Node* v){
    if(u->Parent==NULL)
        this->TreeRoot=v;
    else if(u==u->Parent->Left)
        u->Parent->Left=v;
    else
        u->Parent->Right=v;
    if(v!=NULL)
        v->Parent=u->Parent;
}

//go node z khoi cay, KHONG delete z (ShoesManager so huu node)
void BST::Delete(Node* z){
    if(z==NULL)
        return;
    if(z->Left==NULL)
        this->Transplant(z,z->Right);
    else if(z->Right==NULL)
        this->Transplant(z,z->Left);
    else{
        Node* y=this->Minimum(z->Right);   //successor cua z
        if(y->Parent!=z){
            this->Transplant(y,y->Right);
            y->Right=z->Right;
            y->Right->Parent=y;
        }
        this->Transplant(z,y);
        y->Left=z->Left;
        y->Left->Parent=y;
    }
    z->Left=NULL;
    z->Right=NULL;
    z->Parent=NULL;
}