#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QString>

class AuthService
{
public:
    bool login(const QString& username,
               const QString& password,
               int& userId,
               QString& role);

    bool registerUser(const QString& username,
                      const QString& password,
                      const QString& role);
};

#endif // AUTHSERVICE_H
