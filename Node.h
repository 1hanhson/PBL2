#include "Shoes.h"

class Node{
    private:
        Shoes data;
        //link list
        Node *Next;
        Node *Previous;

        //hashtable
        Node *NextHash;

        //BST
        Node *Left;
        Node *Right;
        Node *Parent;
    public:
        Node();//header
        Node(const Shoes&);
        Node& operator=(const Node&);
        friend class ShoesManager;
        friend class HashTable;
        friend class BST;
};