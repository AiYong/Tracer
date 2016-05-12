#ifndef _TRACKER_BROKER_H_
#define _TRACKER_BROKER_H_

#include <QString>
#include <QStringList>

class Account;

class Broker
{
public:

    /**
     * @brief Broker
     * @param strId
     * @param strName
     * @param lTradeUrl
     * @param lMarketDataUrl
     */
    Broker(QString const& strId,
        QString const& strName,
        QStringList const& lTradeUrl,
        QStringList const& lMarketDataUrl,
        QString const& strPlatform
        );

    /**
     * @brief Broker
     * @param from
     */
    Broker(Broker const& from);

    /**
     * @brief operator =
     * @param from
     * @return
     */
    Broker& operator=(Broker const& from);

    /**
     *
     */
    ~Broker();

public:

    /**
     * @brief 返回经纪商ID
     * @return
     */
    QString const& GetId() const;

    /**
     * @brief 设置经纪商ID
     * @param strId
     */
    void SetId(QString const& strId);

    /**
     * @brief 返回经济商名称
     * @return
     */
    QString const& GetName() const;

    /**
     * @brief 设置经纪商名称
     * @param strName
     */
    void SetName(QString const& strName);

    /**
     * @brief 返回经纪商交易前端
     * @return
     */
    QStringList const& GetTradeUrl() const;

    /**
     * @brief 设置经济商交易前端
     * @param lTradeUrl
     */
    void SetTradeUrls(QStringList const& lTradeUrl);

    /**
     * @brief 添加经济商交易前端
     * @param strUrl
     */
    void AddTradeUrl(QString const& strTradeUrl);

    /**
     * @brief 移除经纪商交易前端
     * @param strUrl
     */
    void RemoveTradeUrl(QString const& strTradeUrl);

    /**
     * @brief 返回经纪商行情前端
     * @return
     */
    QStringList const& GetMarketDataUrl() const;

    /**
     * @brief 设置经济商行情前端
     * @param lMarketDataUrl
     */
    void SetMarketDataUrl(QStringList const& lMarketDataUrl);

    /**
     * @brief 添加经纪商行情前端
     * @param strMarektDataUrl
     */
    void AddMarketDataUrl(QString const& strMarektDataUrl);

    /**
     * @brief 移除经纪商行情前端
     * @param strMarketDataUrl
     */
    void RemoveMarketDataUrl(QString const& strMarketDataUrl);

    /**
     * @brief GetPlatform
     * @return
     */
    QString const& GetPlatform() const;

    /**
     * @brief SetPlatform
     * @param strPlatform
     */
    void SetPlatform(QString const& strPlatform);

public:

    /**
     * @brief GetAccounts
     * @return
     */
    QList<Account*> const& GetAccounts() const;

    /**
     * @brief AddAccount
     * @param pAccount
     */
    void AddAccount(Account *pAccount);

    /**
     * @brief RemoveAccount
     * @param pAccount
     */
    void RemoveAccount(Account *pAccount);

private:

    QString m_strId;
    QString m_strName;
    QStringList m_lTradeUrl;
    QStringList m_lMarketDataUrl;
    QList<Account*> m_lAccounts;
    QString m_strPlatform;
};

#endif // _TRACKER_BROKER_H_
