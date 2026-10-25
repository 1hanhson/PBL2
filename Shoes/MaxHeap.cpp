#include "MaxHeap.h"
#include <iostream>

using namespace std;

MaxHeap::MaxHeap(const int& capacity) {
    this->Capacity = capacity;
    this->Size = 0;
    this->Array = new Node*[this->Capacity];
}

MaxHeap::~MaxHeap() {
    delete[] this->Array;
}

int MaxHeap::Parent(int i) { return (i - 1) / 2; }
int MaxHeap::LeftChild(int i) { return (2 * i) + 1; }
int MaxHeap::RightChild(int i) { return (2 * i) + 2; }

void MaxHeap::Swap(Node*& a, Node*& b) {
    Node* temp = a;
    a = b;
    b = temp;
}

void MaxHeap::HeapifyUp(int i) {
    while (i != 0 && this->Array[Parent(i)]->data.GetSold() < this->Array[i]->data.GetSold()) {
        Swap(this->Array[i], this->Array[Parent(i)]);
        i = Parent(i);
    }
}

void MaxHeap::HeapifyDown(int i) {
    int largest = i;
    int left = LeftChild(i);
    int right = RightChild(i);

    if (left < this->Size && this->Array[left]->data.GetSold() > this->Array[largest]->data.GetSold()) {
        largest = left;
    }
    if (right < this->Size && this->Array[right]->data.GetSold() > this->Array[largest]->data.GetSold()) {
        largest = right;
    }

    if (largest != i) {
        Swap(this->Array[i], this->Array[largest]);
        HeapifyDown(largest);
    }
}

bool MaxHeap::Insert(Node* p) {
    if (p == NULL || this->Size == this->Capacity) {
        return false;
    }

    this->Array[this->Size] = p;
    int current = this->Size;
    this->Size++;

    HeapifyUp(current);
    return true;
}

bool MaxHeap::IncreaseSold(Node* p, const int& amount) {
    if (p == NULL) return false;

    for (int i = 0; i < this->Size; i++) {
        if (this->Array[i] == p) {
            int currentSold = p->data.GetSold();
            p->data.SetSold(currentSold + amount);
            HeapifyUp(i); 
            return true;
        }
    }
    return false;
}

void MaxHeap::ShowTop(const int& k) {
    if (this->Size == 0) {
        cout << "Danh sach trong!" << endl;
        return;
    }

    MaxHeap copyHeap(this->Capacity);
    copyHeap.Size = this->Size;
    for (int i = 0; i < this->Size; i++) {
        copyHeap.Array[i] = this->Array[i];
    }

    cout << "\n--- TOP " << k << " SAN PHAM BAN CHAY NHAT ---\n";
    int count = 0;
    while (copyHeap.Size > 0 && count < k) {
        Node* topNode = copyHeap.Array[0];
        
        cout << count + 1 << ". ";
        topNode->data.Output();
        
        copyHeap.Array[0] = copyHeap.Array[copyHeap.Size - 1];
        copyHeap.Size--;
        copyHeap.HeapifyDown(0);
        count++;
    }
}

//go node p khoi heap (khong delete p). Tra ve false neu p khong co trong heap
bool MaxHeap::Remove(Node* p) {
    if (p == NULL) return false;

    for (int i = 0; i < this->Size; i++) {
        if (this->Array[i] == p) {
            this->Size--;
            if (i != this->Size) {
                //lay phan tu cuoi lap vao cho trong, roi sua lai the heap
                this->Array[i] = this->Array[this->Size];
                HeapifyUp(i);
                HeapifyDown(i);
            }
            return true;
        }
    }
    return false;
}