#include "AuthService.h"
#include "../database/DatabaseService.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

bool AuthService::login(const QString& username,
                        const QString& password,
                        int& userId,
                        QString& role)
{
    QSqlQuery query(DatabaseService::db());

    query.prepare("SELECT id, role FROM users "
                  "WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec())
    {
        qDebug() << "Login query error:"
                 << query.lastError().text();
        return false;
    }

    if (query.next())
    {
        userId = query.value(0).toInt();
        role = query.value(1).toString();
        return true;
    }

    return false;
}

bool AuthService::registerUser(const QString& username,
                               const QString& password,
                               const QString& role)
{
    QSqlQuery query(DatabaseService::db());

    query.prepare("INSERT INTO users (username, password, role) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(role);

    if (!query.exec())
    {
        qDebug() << "Register error:"
                 << query.lastError().text();
        return false;
    }

    return true;
}
