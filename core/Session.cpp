#include "Session.h"

QString Session::m_username = "";
QString Session::m_role = "";

void Session::setUser(const QString& username, const QString& role)
{
    m_username = username;
    m_role = role;
}

QString Session::getUsername()
{
    return m_username;
}

QString Session::getRole()
{
    return m_role;
}

bool Session::hasRole(const QString& requiredRole)
{
    if (m_role == "ADMIN")
        return true;

    if (m_role == requiredRole)
        return true;

    if (m_role == "MANAGER" && requiredRole == "USER")
        return true;

    return false;
}
