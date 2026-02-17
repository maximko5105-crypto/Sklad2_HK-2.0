#include "ProductService.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>

QList<Product> ProductService::getAllProducts()
{
    QList<Product> list;

    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT id, name, barcode, category, quantity FROM products");

    if (!query.exec())
    {
        qDebug() << "Error loading products:" << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        Product p;
        p.id = query.value(0).toInt();
        p.name = query.value(1).toString();
        p.barcode = query.value(2).toString();
        p.category = query.value(3).toString();
        p.quantity = query.value(4).toInt();

        list.append(p);
    }

    return list;
}

QList<Product> ProductService::searchProducts(const QString& text)
{
    QList<Product> list;

    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT id, name, barcode, category, quantity "
                  "FROM products WHERE name LIKE :text OR category LIKE :text");

    query.bindValue(":text", "%" + text + "%");

    if (!query.exec())
    {
        qDebug() << "Search error:" << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        Product p;
        p.id = query.value(0).toInt();
        p.name = query.value(1).toString();
        p.barcode = query.value(2).toString();
        p.category = query.value(3).toString();
        p.quantity = query.value(4).toInt();

        list.append(p);
    }

    return list;
}

Product ProductService::getById(int id)
{
    Product p;

    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT id, name, barcode, category, quantity "
                  "FROM products WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Get product error:" << query.lastError().text();
        return p;
    }

    if (query.next())
    {
        p.id = query.value(0).toInt();
        p.name = query.value(1).toString();
        p.barcode = query.value(2).toString();
        p.category = query.value(3).toString();
        p.quantity = query.value(4).toInt();
    }

    return p;
}

bool ProductService::addProduct(const QString& name,
                                const QString& category,
                                int quantity)
{
    QSqlQuery query(QSqlDatabase::database());

    query.prepare("INSERT INTO products (name, barcode, category, quantity) "
                  "VALUES (:name, '', :category, :quantity)");

    query.bindValue(":name", name);
    query.bindValue(":category", category);
    query.bindValue(":quantity", quantity);

    if (!query.exec())
    {
        qDebug() << "Add product error:" << query.lastError().text();
        return false;
    }

    return true;
}
