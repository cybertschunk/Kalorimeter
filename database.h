#ifndef DATABASE_H
#define DATABASE_H

#include "entry.h"

#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QString>

#include <vector>

//database config
#define DB_HOST "192.168.2.110"
#define DB_USER "testuser"
#define DB_PASS "abc"
#define DB_NAME "kalorimeter"

//database query
#define DB_SELECT "SELECT timestamp, temp1, temp2 FROM `values` ORDER BY timestamp ASC"


class Database
{
public:
    Database(QString name);
    Database() = default;
    auto connect() -> bool;
    auto readEntries() -> std::vector<Entry>;
    auto close() -> void;

private:
    auto getSize(QSqlQuery& query) -> int;
    auto exec(QString&) -> QSqlQuery;

    QSqlDatabase db;
    QString dbcon_name;
    bool connected = false;

};

#endif // DATABASE_H
