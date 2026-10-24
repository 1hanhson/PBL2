#include "Order.h"

class NodeO{
    private:
        Order data;
        NodeO* Next;
        NodeO* NextHash;
    public:
        NodeO();
        NodeO(const Order&);
        friend class QueueO;
        friend class HashTableO;
        friend class OrderManager;
};
