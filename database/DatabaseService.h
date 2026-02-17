#pragma once

#include <QSqlDatabase>

class DatabaseService
{
public:
    static bool initialize();
    static QSqlDatabase& db();
    static void close();

private:
    static QSqlDatabase m_db;
};
