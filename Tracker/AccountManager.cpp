#include "AccountManager.h"
#include "ObjectPersistManager.h"

#include <algorithm>

AccountManager::AccountManager()
{
    QList<Account*> lAccounts;
    ObjectPersistManager::GetInstance()->Load(this,lAccounts);
    std::for_each(lAccounts.begin(),lAccounts.end(),[this](Account *pAccount){
       this->m_hIDToAccount.insert(pAccount->GetID(),pAccount);
       this->m_hNameToAccount.insert(pAccount->GetName(),pAccount);
    });
}

AccountManager::~AccountManager()
{
    QList<Account*> lAccounts = m_hIDToAccount.values();
    std::for_each(lAccounts.begin(),lAccounts.end(),[this](Account *pAccount){
       delete pAccount;
    });
}

QList<Account*> AccountManager::GetAccounts() const
{
    return m_hIDToAccount.values();
}

Account* AccountManager::GetAccountWithName(QString const& strName)
{
    auto iPos = m_hNameToAccount.find(strName);
    if(iPos != m_hNameToAccount.end())
    {
        return *iPos;
    }
    return nullptr;
}

Account* AccountManager::GetAccountWithID(QString const& strId)
{
    auto iPos = m_hIDToAccount.find(strName);
    if(iPos != m_hIDToAccount.end())
    {
        return *iPos;
    }
    return nullptr;
}

Account* AccountManager::CreateAccount(QString const& strId,QString const& strName,
                    QString const& strPassword,Broker const* pBroker)
{
    Account *pAccount = new Account(strId,strName,strPassword,pBroker);
    ObjectPersistManager::GetInstance()->Save(pAccount);
    m_hIDToAccount.insert(pAccount->GetID(),pAccount);
    m_hNameToAccount.insert(pAccount->GetID(),pAccount);
    return pAccount;
}

void AccountManager::DestroyAccount(Account *pAccount)
{
    m_hIDToAccount.remove(pAccount->GetID());
    m_hNameToAccount.remove(pAccount->GetName());
    pAccount->Clear();
    ObjectPersistManager::GetInstance()->Remove(pAccount);
    delete pAccount;
}
