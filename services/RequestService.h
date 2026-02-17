#ifndef REQUESTSERVICE_H
#define REQUESTSERVICE_H

#include <QVector>
#include <QString>
#include <QDateTime>

struct Request
{
    int id;
    QString productName;
    int quantity;
    QString status;
    QDateTime createdAt;
};

class RequestService
{
public:
    QVector<Request> getAllRequests();
};

#endif
