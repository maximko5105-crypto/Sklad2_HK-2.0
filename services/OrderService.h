#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include <QString>
#include <QList>

struct Order
{
    int id;
    int userId;
    QString description;
    int quantity;
    QString deadline;
    QString status;
    QString createdAt;
};

class OrderService
{
public:
    static bool createOrder(int userId,
                            const QString& description,
                            int quantity,
                            const QString& deadline);

    static QList<Order> getAllOrders();

    static QList<Order> getOrdersByUser(int userId);

    static bool updateStatus(int orderId,
                             const QString& newStatus);
};

#endif // ORDERSERVICE_H
