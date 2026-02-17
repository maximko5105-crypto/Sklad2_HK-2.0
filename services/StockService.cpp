#include "StockService.h"
#include "database/DatabaseService.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

int StockService::getStock(int productId)
{
    QSqlQuery query(DatabaseService::db());
    query.prepare("SELECT quantity FROM stock WHERE product_id = ?");
    query.addBindValue(productId);

    if (!query.exec())
    {
        qDebug() << "getStock error:" << query.lastError().text();
        return 0;
    }

    if (query.next())
        return query.value(0).toInt();

    return 0;
}

bool StockService::addStock(int productId, int quantity)
{
    QSqlQuery query(DatabaseService::db());
    query.prepare("UPDATE stock SET quantity = quantity + ? WHERE product_id = ?");
    query.addBindValue(quantity);
    query.addBindValue(productId);

    if (!query.exec())
    {
        qDebug() << "addStock error:" << query.lastError().text();
        return false;
    }

    return true;
}

bool StockService::removeStock(int productId, int quantity)
{
    QSqlQuery query(DatabaseService::db());
    query.prepare("UPDATE stock SET quantity = quantity - ? WHERE product_id = ?");
    query.addBindValue(quantity);
    query.addBindValue(productId);

    if (!query.exec())
    {
        qDebug() << "removeStock error:" << query.lastError().text();
        return false;
    }

    return true;
}

QVector<QVariantMap> StockService::getAllProducts()
{
    QVector<QVariantMap> list;

    QSqlQuery query(DatabaseService::db());
    query.prepare("SELECT id, name, quantity FROM stock");

    if (!query.exec())
    {
        qDebug() << "getAllProducts error:" << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        QVariantMap item;
        item["id"] = query.value("id");
        item["name"] = query.value("name");
        item["quantity"] = query.value("quantity");
        list.append(item);
    }

    return list;
}
