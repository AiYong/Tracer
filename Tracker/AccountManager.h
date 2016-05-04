#ifndef _TRACKER_ACCOUNTMANAGER_H_
#define _TRACKER_ACCOUNTMANAGER_H_

#include <QList>
#include <QString>

class Broker;
class Account;

class AccountManager
{
public:

    AccountManager();

    /**
     *
     */
    ~AccountManager();

public:

    /**
     * @brief GetInstance
     * @return
     */
    static AccountManager* GetInstance();

public:

    /**
     * @brief 返回所有账号
     * @return
     */
    QList<Account*> GetAccounts() const;

    /**
     * @brief 返回指定名称账号
     * @param strName
     * @return
     */
    Account* GetAccountWithName(QString const& strName);

    /**
     * @brief 返回指定Id账号
     * @param strId
     * @return
     */
    Account* GetAccountWithID(QString const& strId);

public:

    /**
     * @brief 创建新账号
     * @param strId
     * @param strName
     * @param strPassword
     * @param pBroker
     * @return
     */
    Account* CreateAccount(QString const& strId,QString const& strName,
                        QString const& strPassword,Broker const* pBroker);

    /**
     * @brief DestroyAccount
     * @param pAccount
     */
    void DestroyAccount(Account *pAccount);



private:

};

#endif // _TRACKER_ACCOUNTMANAGER_H_
