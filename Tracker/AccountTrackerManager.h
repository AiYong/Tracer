#ifndef _TRACKER_ACCOUNTTRACKERSETTINGSMANAGER_H_
#define _TRACKER_ACCOUNTTRACKERSETTINGSMANAGER_H_

#include <QObject>
#include "AccountManager.h"
#include "AccountTrackerSetting.h"

class AccountTrackerSettingsManager : public QObject
{
    Q_OBJECT
public:

    explicit AccountTrackerSettingsManager(AccountManager *pAccountManager,QObject *parent = 0);

public:


};

#endif // _TRACKER_ACCOUNTTRACKERSETTINGSMANAGER_H_
