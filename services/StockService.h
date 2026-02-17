#pragma once

#include <QVector>
#include <QVariantMap>

class StockService
{
public:
    static int getStock(int productId);
    static bool addStock(int productId, int quantity);
    static bool removeStock(int productId, int quantity);

    static QVector<QVariantMap> getAllProducts();
};
