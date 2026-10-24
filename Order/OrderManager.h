#include "QueueO.h"

class OrderManager{
    private:
        QueueO Q;
        HashTableO Hash;

    public:
        bool Insert(const Order&);
        void Show() const;
        void ShowHistory() const;
        NodeO* Search(const string&);
        bool Delete(NodeO*);
        bool ProcessNext(Order&);
};
