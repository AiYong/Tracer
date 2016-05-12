#ifndef _TRACKER_ACCOUNTTRACKER_H_
#define _TRACKER_ACCOUNTTRACKER_H_

#include <QObject>


#include <QThreadPool>

#include "Account.h"
#include "MarketData.h"
#include "Transaction.h"
#include "AccountTrackerData.h"
#include "AccountTrackerSetting.h"
#include "AccountTrackerEventProcessor.h"

class AccountTracker : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief AccountTracker
     * @param parent
     */
    AccountTracker(QObject *parent = 0);

    /**
     * @brief ~AccountTracker
     */
    ~AccountTracker();

public:

    /**
     * @brief GetID
     * @return
     */
    QString const& GetID() const;

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
     * @brief Start
     */
    void Start();

    /**
     * @brief Stop
     */
    void Stop();

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
    void RemoveTrackerSetting(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief StartTrack
     * @param pAccountTrackerSetting
     */
    void StartTrack(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief StopTrack
     * @param pAccountTrackerSetting
     */
    void StopTrack(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief StartAllTrack
     */
    void StartAllTrack();

    /**
     * @brief StopAllTrack
     */
    void StopAllTrack();

public:

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
    QList<AccountTrackerSetting*> const& GetAccountTrackerSetting() const;


signals:

    /**
     * @brief TrackStarting
     * @param pAccountTrackerSetting
     */
    void TrackStarting(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief TrackStarted
     * @param pAccountTrackerSetting
     */
    void TrackStarted(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief TrackOpen
     * @param pAccountTrackerSetting
     * @param pPosition
     */
    void TrackOpen(AccountTrackerSetting *pAccountTrackerSetting,Position *pPosition);

    /**
     * @brief TrackClose
     * @param pAccountTrackerSetting
     * @param pTransaction
     */
    void TrackClose(AccountTrackerSetting *pAccountTrackerSetting,Transaction *pTransaction);

    /**
     * @brief TrackPositionUpdated
     * @param pAccountTrackerSetting
     * @param pPosition
     */
    void TrackPositionUpdated(AccountTrackerSetting *pAccountTrackerSetting,Position *pPosition);


private:

    AccountTrackerData *m_pData;
    AccountTrackerEventProcessor *m_pTrackerEventProcessor;

};

#endif // _TRACKER_ACCOUNTTRACKER_H_
