#include "UserService.h"
#include "../database/DatabaseService.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

User UserService::getById(int id)
{
    User user;

    QSqlQuery query(DatabaseService::db());
    query.prepare("SELECT id, username, role FROM users WHERE id = ?");
    query.addBindValue(id);
    query.exec();

    if (query.next()) {
        user.id = query.value(0).toInt();
        user.username = query.value(1).toString();
        user.role = query.value(2).toString();
    }

    return user;
}

QList<User> UserService::getAllUsers()
{
    QList<User> list;

    QSqlQuery query("SELECT id, username, role FROM users");

    while (query.next()) {
        User u;
        u.id = query.value(0).toInt();
        u.username = query.value(1).toString();
        u.role = query.value(2).toString();
        list.append(u);
    }

    return list;
}

bool UserService::createUser(const QString& username,
                             const QString& password,
                             const QString& role)
{
    QSqlQuery query(DatabaseService::db());

    query.prepare(R"(
        INSERT INTO users (username, password, role)
        VALUES (?, ?, ?)
    )");

    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(role);

    if (!query.exec()) {
        qDebug() << "Create user error:" << query.lastError().text();
        return false;
    }

    return true;
}
