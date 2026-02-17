#ifndef SESSION_H
#define SESSION_H

#include <QString>

class Session
{
public:
    static void setUser(const QString& username, const QString& role);
    static QString getUsername();
    static QString getRole();
    static bool hasRole(const QString& requiredRole);

private:
    static QString m_username;
    static QString m_role;
};

#endif
