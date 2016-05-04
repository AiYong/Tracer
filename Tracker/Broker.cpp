#include "Broker.h"
#include "DatabaseManager.h"
#include "ObjectPersistManager.h"



Broker::Broker(QString const& strId,
    QString const& strName,
    QStringList const& lTradeUrl,
    QStringList const& lMarketDataUrl,
    )
    :m_strId(strId),
     m_strName(strName),
     m_lTradeUrl(lTradeUrl),
     m_lMarketDataUrl(lMarketDataUrl)
{
}

Broker::~Broker()
{
}

QString const& Broker::GetId() const
{
   return m_strId;
}

void Broker::SetId(QString const& strId)
{
    m_strId = strId;
}

QString const& Broker::GetName() const
{
    return m_strName;
}

void Broker::SetName(QString const& strName)
{
    m_strName = strName;
}

QStringList const& Broker::GetTradeUrl() const
{
    return m_lTradeUrl;
}

void Broker::SetTradeUrls(QStringList const& lTradeUrl)
{
    m_lTradeUrl = lTradeUrl;
}

void Broker::AddTradeUrl(QString const& strTradeUrl)
{
    m_lTradeUrl.append(strTradeUrl);
}

void Broker::RemoveTradeUrl(QString const& strTradeUrl)
{
    m_lTradeUrl.removeAll(strTradeUrl);
}

QStringList const& Broker::GetMarketDataUrl() const
{
    return m_lMarketDataUrl;
}

void Broker::SetMarketDataUrl(QStringList const& lMarketDataUrl)
{
    m_lMarketDataUrl = lMarketDataUrl;
}

void Broker::AddMarketDataUrl(QString const& strMarektDataUrl)
{
    m_lMarketDataUrl.append(strMarektDataUrl);
}

void Broker::RemoveMarketDataUrl(QString const& strMarketDataUrl)
{
    m_lMarketDataUrl.removeAll(strMarketDataUrl);
}

QList<Account*> const& Broker::GetAccounts() const
{
    return m_lAccounts;
}


void Broker::AddAccount(Account *pAccount)
{
    m_lAccounts.append(pAccount);
}

void Broker::RemoveAccount(Account *pAccount)
{
    m_lAccounts.removeOne(pAccount);
}

