#ifndef MAX_HEAP_H
#define MAX_HEAP_H
#include "Node.h"

class MaxHeap {
    private:
        Node **Array;
        int Capacity;
        int Size;

        int Parent(int i) const;
        int LeftChild(int i) const;
        int RightChild(int i) const;
        void Swap(Node*& a, Node*& b);

        void HeapifyUp(int i);
        void HeapifyDown(int i);

    public:
        MaxHeap(const int& capacity = 100);
        ~MaxHeap();
        MaxHeap(const MaxHeap&) = delete;
        MaxHeap& operator=(const MaxHeap&) = delete;

        bool Insert(Node* p);
        bool Remove(Node* p);
        bool IncreaseSold(Node* p, const int& amount);
        void ShowTop(const int& k) const;

        friend class ShoesManager;
};

#endif