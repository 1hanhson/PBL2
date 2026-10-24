#include "HashTableO.h"

class QueueO{
    private:
        NodeO *Front;
        NodeO *Rear;
        int Noo;
    public:
        QueueO();
        ~QueueO();
        bool Enqueue(NodeO*);
        NodeO* Dequeue();
        void Show() const;
        bool IsEmpty();
        friend class OrderManager;
};