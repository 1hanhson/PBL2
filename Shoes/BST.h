#ifndef BST_H
#define BST_H
#include "HashTable.h"

class BST {
    private:
        Node *TreeRoot;
        void Transplant(Node*,Node*);
    public:
        BST();
        ~BST();     // cay khong so huu node nen khong delete
        void MinToMax(Node*);
        void MaxToMin(Node*);
        Node* Maximum(Node*);
        Node* Minimum(Node*);
        void Insert(Node*);
        Node* Successor(Node*);
        Node* Find(Node*,const string&,const long long&);
        void Delete(Node*);
        friend class ShoesManager;
};

#endif