#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
{
    QSqlDatabase oDatabase = QSqlDatabase::addDatabase("QSQLITE","Tracker");
    oDatabase.setDatabaseName("Tracker.db");
    bool b = oDatabase.open();
	b = false;
}

DatabaseManager::~DatabaseManager()
{

}

DatabaseManager* DatabaseManager::GetInstance()
{
    static DatabaseManager oInstance;
    return &oInstance;
}

QSqlDatabase DatabaseManager::GetDatabase()
{
    return QSqlDatabase::database("Tracker");
}

