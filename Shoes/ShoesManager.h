#ifndef SHOES_MANAGER_H
#define SHOES_MANAGER_H
#include "BST.h"
#include "MaxHeap.h"

class ShoesManager{
    private:
        Node* pL;
        int Nos;//number of shoes
        HashTable Hash;
        BST Tree;
        MaxHeap Heap;
    public:
        ShoesManager();
        ~ShoesManager();
        int Insert(const Shoes&,Node*);
        void Show();
        void ShowMinToMax();
        void ShowMaxToMin();
        void ShowTop(const int&);
        bool IncreaseSold(const string&,const int&);
        int Delete(Node*);
        Node* Search(const string&);
        friend class HashTable;
        friend class BST;
};

#endif