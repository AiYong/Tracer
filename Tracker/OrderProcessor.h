#ifndef _TRACKER_ORDERPROCESSOR_H_
#define _TRACKER_ORDERPROCESSOR_H_

#include <QObject>

#include "Order.h"
#include "Account.h"
#include "OrderListener.h"

class OrderProcessor
{
public:

    /**
     * @brief OrderProcessor
     * @param parent
     */
    explicit OrderProcessor(Account *pAccount);

    /**
     * @brief ~OrderProcessor
     */
    virtual ~OrderProcessor();

public:

    /**
     * @brief Submit
     * @param pOrder
     */
    virtual void Submit(Order const* pOrder,OrderListener const*pOrderListener) = 0;

    /**
     * @brief Cancel
     * @param pOrder
     */
    virtual void Cancel(Order const* pOrder) = 0;

protected:

    Account *m_pAccount;


};

#endif // _TRACKER_ORDERPROCESSOR_H_
