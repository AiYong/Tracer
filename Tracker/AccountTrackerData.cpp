#include "AccountTrackerData.h"
#include "ObjectPersistManager.h"


AccountTrackerData::AccountTrackerData(Account *pAccount)
    :m_pTradeAccount(pAccount)
{
    ObjectPersistManager::GetInstance()->Load(pAccount,m_lTrackerSettings);
}


AccountTrackerData::~AccountTrackerData()
{

}

QString const& AccountTrackerData::GetID() const
{
    return m_pTradeAccount->GetID();
}


QString const& AccountTrackerData::GetName() const
{
    return m_pTradeAccount->GetName();
}

Account const* AccountTrackerData::GetAccount() const
{
    return m_pTradeAccount;
}

AccountTrackerSetting* AccountTrackerData::CreateTrackerSetting()
{
    AccountTrackerSetting *pTrackerSetting = new AccountTrackerSetting(m_pTradeAccount);
    return pTrackerSetting;
}

void AccountTrackerData::AddAccountTrackerSetting(AccountTrackerSetting *pAccountTrackerSetting)
{
    if(!m_lTrackerSettings.contains(pAccountTrackerSetting))
    {
        m_lTrackerSettings.append(pAccountTrackerSetting);
        ObjectPersistManager::GetInstance()->Save(pAccountTrackerSetting);
    }
}

void AccountTrackerData::RemoveAccountTrackerSetting(AccountTrackerSetting *pAccountTrackerSetting)
{
    if(m_lTrackerSettings.contains(pAccountTrackerSetting))
    {
        m_lTrackerSettings.removeOne(pAccountTrackerSetting);
        ObjectPersistManager::GetInstance()->Remove(pAccountTrackerSetting);
    }
}

AccountTrackerSetting* AccountTrackerData::GetAccountTrackerSetting(Account *pAccount) const
{
    AccountTrackerSetting *pTrackerSetting = nullptr;
    for(int nCount = 0 ; nCount < m_lTrackerSettings.size() ; nCount++)
    {
        pTrackerSetting = m_lTrackerSettings[nCount];
        if(pTrackerSetting->GetTrackAccount()->GetID() == pAccount->GetID())
        {
            return pTrackerSetting;
        }
    }
    return nullptr;
}

QList<AccountTrackerSetting*> const& AccountTrackerData::GetAccountTrackerSettings() const
{
    return m_lTrackerSettings;
}
