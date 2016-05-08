#ifndef _TRACKER_POSITIONCREATOR_H_
#define _TRACKER_POSITIONCREATOR_H_

#include <QDateTime>
#include "OrderStatus.h"

class Order;
class Position;
class Transaction;

class OrderOperator
{
public:

    /**
     * @brief Open
     * @param pOrder
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */
    Position* Open(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    /**
     * @brief Close
     * @param pPosition
     * @param pOrder
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */
    Transaction* Close(Position *pPosition,Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);
    
    /**
     * @brief UpdateOrderStatus
     * @param pOrder
     * @param eStatus
     */
    void UpdateOrderStatus(Order *pOrder,OrderStatus eStatus);

};

#endif // _TRACKER_POSITIONCREATOR_H_
