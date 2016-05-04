#ifndef _TRACKER_DATABASEMANAGER_H_
#define _TRACKER_DATABASEMANAGER_H_

#include <QtSql>

class DatabaseManager
{
public:

    DatabaseManager();

    ~DatabaseManager();

public:

    static DatabaseManager* GetInstance();

public:

    QSqlDatabase GetDatabase();

};

#endif // _TRACKER_DATABASEMANAGER_H_
