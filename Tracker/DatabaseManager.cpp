#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
{
    QSqlDatabase oDatabase = QSqlDatabase::addDatabase("QSQLITE");
    oDatabase.setDatabaseName("Tracker.db");
    oDatabase.open();
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
    return QSqlDatabase::database();
}

