#include "RequestService.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

QVector<Request> RequestService::getAllRequests()
{
    QVector<Request> list;

    QSqlQuery query;
    query.exec("SELECT id, product_name, quantity, status, created_at FROM requests");

    if (!query.isActive()) {
        qDebug() << "Request query error:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        Request r;

        r.id = query.value(0).toInt();
        r.productName = query.value(1).toString();
        r.quantity = query.value(2).toInt();
        r.status = query.value(3).toString();
        r.createdAt = query.value(4).toDateTime();

        list.append(r);
    }

    return list;
}
