#include "AccountTracker.h"

AccountTracker::AccountTracker(QObject *parent)
    : QObject(parent)
{

}

int AccountTracker::GetID() const
{
    return m_pData->GetID();
}

QString const& AccountTracker::GetName() const
{
    return m_pData->GetName();
}

Account const* AccountTracker::GetAccount() const
{
    return m_pData->GetAccount();
}

AccountTrackerSetting* AccountTracker::CreateTrackerSetting()
{
    return m_pData->CreateTrackerSetting();
}

void AccountTracker::AddAccountTrackerSetting(AccountTrackerSetting *pAccountTrackerSetting)
{
    return m_pData->AddAccountTrackerSetting(pAccountTrackerSetting);
}

void AccountTracker::RemoveTrackerSetting(AccountTrackerSetting *pAccountTrackerSetting)
{
    return m_pData->RemoveAccountTrackerSetting(pAccountTrackerSetting);
}


void AccountTracker::Start()
{
    m_pTrackerEventProcessor->setAutoDelete(false);
    QThreadPool::globalInstance()->start(m_pTrackerEventProcessor);
}

void AccountTracker::Stop()
{
    m_pTrackerEventProcessor->Stop();
}

void AccountTracker::StartTrack(AccountTrackerSetting *pAccountTrackerSetting)
{
    m_pTrackerEventProcessor->StartTrack(pAccountTrackerSetting);
}

void AccountTracker::StopTrack(AccountTrackerSetting *pAccountTrackerSetting)
{
    m_pTrackerEventProcessor->StopTrack(pAccountTrackerSetting);
}

void AccountTracker::StartAllTrack()
{
    QList<AccountTrackerSetting*> lTrackerSettings = m_pData->GetAccountTrackerSettings();
    for(int nCount = 0; nCount < lTrackerSettings.size() ; nCount++)
    {
        m_pTrackerEventProcessor->StartTrack(lTrackerSettings[nCount]);
    }
}

void AccountTracker::StopAllTrack()
{
    QList<AccountTrackerSetting*> lTrackerSettings = m_pData->GetAccountTrackerSettings();
    for(int nCount = 0; nCount < lTrackerSettings.size() ; nCount++)
    {
        m_pTrackerEventProcessor->StopTrack(lTrackerSettings[nCount]);
    }
}
