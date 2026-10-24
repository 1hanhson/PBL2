#ifndef NODE_OD_H
#define NODE_OD_H
#include "OrderDetail.h"

class NodeOD{
    private:
        OrderDetail data;
        NodeOD* Next;
        NodeOD* Previous;
    public:
        NodeOD();//header
        NodeOD(const OrderDetail&);
        friend class OrderDetailManager;
};

#endif