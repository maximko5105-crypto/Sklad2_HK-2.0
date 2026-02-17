#include "ContainerService.h"
#include "StockService.h"
#include "../core/Logger.h"
#include <QSqlQuery>

bool ContainerService::createContainer(const QString& name)
{
    QSqlQuery q;
    q.prepare("INSERT INTO containers(name) VALUES(?)");
    q.addBindValue(name);

    if(!q.exec())
        return false;

    Logger::log("Container created: " + name);
    return true;
}

bool ContainerService::addToContainer(int containerId, int productId, int qty)
{
    if(StockService::getStock(productId) < qty)
        return false;

    QSqlQuery q;
    q.prepare("INSERT INTO container_items(container_id,product_id,quantity) "
              "VALUES(?,?,?) "
              "ON CONFLICT(container_id,product_id) "
              "DO UPDATE SET quantity = quantity + excluded.quantity");
    q.addBindValue(containerId);
    q.addBindValue(productId);
    q.addBindValue(qty);
    q.exec();

    StockService::removeStock(productId, qty);

    Logger::log("Added to container");
    return true;
}
