#include "HashTable.h"

class BST {
    private:
        Node *TreeRoot;
    public:
        BST();
        ~BST();
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
