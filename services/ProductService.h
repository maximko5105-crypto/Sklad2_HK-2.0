#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include <QString>
#include <QList>

struct Product
{
    int id = 0;
    QString name;
    QString barcode;
    QString category;
    int quantity = 0;
};

class ProductService
{
public:
    static QList<Product> getAllProducts();
    static QList<Product> searchProducts(const QString& text);
    static Product getById(int id);

    static bool addProduct(const QString& name,
                           const QString& category,
                           int quantity);
};

#endif
