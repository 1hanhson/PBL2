#include "Node.h"

class MaxHeap {
    private:
        Node **Array;
        int Capacity;
        int Size;

        int Parent(int i);
        int LeftChild(int i);
        int RightChild(int i);
        void Swap(Node*& a, Node*& b);
        
        void HeapifyUp(int i);
        void HeapifyDown(int i);

    public:
        MaxHeap(const int& capacity = 100);
        ~MaxHeap();

        bool Insert(Node* p);
        bool IncreaseSold(Node* p, const int& amount); 
        void ShowTop(const int& k);
        
        friend class ShoesManager;
};
