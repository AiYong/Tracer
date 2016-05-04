#ifndef _TRACKER_POSITIONCREATOR_H_
#define _TRACKER_POSITIONCREATOR_H_

#include <QDateTime>

class Order;
class Position;
class Transaction;

class OrderOperator
{
public:

    Position* Open(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    Transaction* Close(Position *pPosition,Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);
    
    void Cancelled(Order *pOrder);
};

#endif // _TRACKER_POSITIONCREATOR_H_
