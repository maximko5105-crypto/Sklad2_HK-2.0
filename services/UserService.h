#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QString>
#include <QList>

struct User
{
    int id;
    QString username;
    QString role;
};

class UserService
{
public:
    static User getById(int id);

    static QList<User> getAllUsers();

    static bool createUser(const QString& username,
                           const QString& password,
                           const QString& role);
};

#endif // USERSERVICE_H
