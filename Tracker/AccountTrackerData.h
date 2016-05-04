#ifndef ACCOUNTTRACKERDATA_H
#define ACCOUNTTRACKERDATA_H

#include "Order.h"
#include "Account.h"
#include "Position.h"
#include "AccountTrackerSetting.h"
#include "AccountTrackerPosition.h"

class AccountTrackerData
{
public:

    AccountTrackerData(Account *pAccount);


    ~AccountTrackerData();

public:

    /**
     * @brief GetID
     * @return
     */
    int GetID() const;

    /**
     * @brief GetName
     * @return
     */
    QString const& GetName() const;

    /**
     * @brief GetAccount
     * @return
     */
    Account const* GetAccount() const;

public:

    /**
     * @brief CreateTrackerSetting
     * @return
     */
    AccountTrackerSetting* CreateTrackerSetting() ;

    /**
     * @brief AddAccountTrackerSetting
     * @param pAccountTrackerSetting
     */
    void AddAccountTrackerSetting(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief DestoryTrackerSetting
     * @param pAccountTrackerSetting
     */
    void RemoveAccountTrackerSetting(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief GetAccountTrackerSetting
     * @param pAccount
     * @return
     */
    AccountTrackerSetting* GetAccountTrackerSetting(Account *pAccount) const;

    /**
     * @brief GetAccountTrackerSetting
     * @return
     */
    QList<AccountTrackerSetting*> const& GetAccountTrackerSettings() const;


private:


};

#endif // ACCOUNTTRACKERDATA_H
