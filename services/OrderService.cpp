#include "OrderService.h"
#include "../database/DatabaseService.h"
#include "../services/NotificationService.h"
#include "../core/Statuses.h"

#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>

bool OrderService::createOrder(int userId,
                               const QString& description,
                               int quantity,
                               const QString& deadline)
{
    QSqlQuery query(DatabaseService::db());

    query.prepare(R"(
        INSERT INTO orders
        (user_id, description, quantity, deadline, status, created_at)
        VALUES (?, ?, ?, ?, ?, ?)
    )");

    query.addBindValue(userId);
    query.addBindValue(description);
    query.addBindValue(quantity);
    query.addBindValue(deadline);
    query.addBindValue(Statuses::Pending);
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "Create order error:" << query.lastError().text();
        return false;
    }

    // уведомляем админов
    QSqlQuery adminQuery("SELECT id FROM users WHERE role = 'ADMIN'");
    while (adminQuery.next()) {
        int adminId = adminQuery.value(0).toInt();
        NotificationService::create(
            adminId,
            "Новый заказ на закупку",
            "Поступил новый заказ от пользователя"
        );
    }

    return true;
}

QList<Order> OrderService::getAllOrders()
{
    QList<Order> list;

    QSqlQuery query("SELECT id, user_id, description, quantity, deadline, status, created_at FROM orders");

    while (query.next()) {
        Order o;
        o.id = query.value(0).toInt();
        o.userId = query.value(1).toInt();
        o.description = query.value(2).toString();
        o.quantity = query.value(3).toInt();
        o.deadline = query.value(4).toString();
        o.status = query.value(5).toString();
        o.createdAt = query.value(6).toString();
        list.append(o);
    }

    return list;
}

QList<Order> OrderService::getOrdersByUser(int userId)
{
    QList<Order> list;

    QSqlQuery query(DatabaseService::db());
    query.prepare(R"(
        SELECT id, user_id, description, quantity, deadline, status, created_at
        FROM orders
        WHERE user_id = ?
    )");

    query.addBindValue(userId);
    query.exec();

    while (query.next()) {
        Order o;
        o.id = query.value(0).toInt();
        o.userId = query.value(1).toInt();
        o.description = query.value(2).toString();
        o.quantity = query.value(3).toInt();
        o.deadline = query.value(4).toString();
        o.status = query.value(5).toString();
        o.createdAt = query.value(6).toString();
        list.append(o);
    }

    return list;
}

bool OrderService::updateStatus(int orderId,
                                const QString& newStatus)
{
    QSqlQuery query(DatabaseService::db());

    query.prepare("SELECT user_id FROM orders WHERE id = ?");
    query.addBindValue(orderId);
    query.exec();

    if (!query.next())
        return false;

    int userId = query.value(0).toInt();

    QSqlQuery update(DatabaseService::db());
    update.prepare("UPDATE orders SET status = ? WHERE id = ?");
    update.addBindValue(newStatus);
    update.addBindValue(orderId);

    if (!update.exec())
        return false;

    NotificationService::create(
        userId,
        "Статус заказа изменён",
        "Ваш заказ теперь: " + newStatus
    );

    return true;
}
