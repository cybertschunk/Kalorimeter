#include "database.h"

#include <QSqlDriver>

Database::Database(QString name)
{
    dbcon_name = name;
    db = QSqlDatabase::addDatabase("QMYSQL", name);
}

/**
 * Builds up a database connection
 *
 * @brief Database::connect
 * @return
 */

auto Database::connect() -> bool
{
    db.setHostName(DB_HOST);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASS);
    connected = true;
    return db.open();
}

/**
 * Executes a given database query and returns the result.
 *
 * connect must be called first!
 *
 * @brief Database::exec
 * @param query
 * @return
 */

auto Database::exec(QString& queryStr) -> QSqlQuery
{
    QSqlQuery query;
    query = db.exec(queryStr);
    return query;
}

auto Database::readEntries() -> std::vector<Entry>
{
    //Make sure a connection is open.
    if(!connected)
        connect();

    QString query = DB_SELECT;
    QSqlQuery resultQuery = exec(query);
    int size = getSize(resultQuery);
    std::vector<Entry> result(size);
    int i = 0;
    while(resultQuery.next())
    {
        QDateTime ts = resultQuery.value(0).toDateTime();
        double temp1 = resultQuery.value(1).toDouble();
        double temp2 = resultQuery.value(2).toDouble();
        Entry e = Entry(ts,temp1,temp2);
        std::cout << e << std::endl;
        result[i] = e;
        ++i;
    }

    return result;
}

auto Database::getSize(QSqlQuery& query) -> int
{
    if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
        return query.size();
    } else {
        // this can be very slow
        query.last();
        return query.at() + 1;
    }
}

auto Database::close() -> void
{
    db.close();
    connected = false;
}
