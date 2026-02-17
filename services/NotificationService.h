#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <QString>
#include <QList>

struct Notification
{
    int id;
    int userId;
    QString title;
    QString message;
    bool isRead;
    QString createdAt;
};

class NotificationService
{
public:
    static bool create(int userId,
                       const QString& title,
                       const QString& message);

    static QList<Notification> getByUser(int userId);

    static bool markAsRead(int notificationId);
};

#endif // NOTIFICATIONSERVICE_H
