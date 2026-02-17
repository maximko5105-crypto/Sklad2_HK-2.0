#include "NotificationService.h"
#include "../database/DatabaseService.h"

#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

bool NotificationService::create(int userId,
                                 const QString& title,
                                 const QString& message)
{
    QSqlQuery query(DatabaseService::db());

    query.prepare(R"(
        INSERT INTO notifications
        (user_id, title, message, is_read, created_at)
        VALUES (?, ?, ?, 0, ?)
    )");

    query.addBindValue(userId);
    query.addBindValue(title);
    query.addBindValue(message);
    query.addBindValue(
        QDateTime::currentDateTime()
        .toString(Qt::ISODate));

    return query.exec();
}

QList<Notification>
NotificationService::getByUser(int userId)
{
    QList<Notification> list;

    QSqlQuery query(DatabaseService::db());
    query.prepare(R"(
        SELECT id, user_id, title,
               message, is_read, created_at
        FROM notifications
        WHERE user_id = ?
        ORDER BY created_at DESC
    )");

    query.addBindValue(userId);
    query.exec();

    while (query.next())
    {
        Notification n;

        n.id = query.value(0).toInt();
        n.userId = query.value(1).toInt();
        n.title = query.value(2).toString();
        n.message = query.value(3).toString();
        n.isRead = query.value(4).toInt();
        n.createdAt = query.value(5).toString();

        list.append(n);
    }

    return list;
}

bool NotificationService::markAsRead(int notificationId)
{
    QSqlQuery query(DatabaseService::db());

    query.prepare(
        "UPDATE notifications SET is_read = 1 WHERE id = ?");

    query.addBindValue(notificationId);

    return query.exec();
}
