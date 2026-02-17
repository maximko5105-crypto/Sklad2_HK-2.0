#ifndef PRODUCTLISTDIALOG_H
#define PRODUCTLISTDIALOG_H

#include <QDialog>
#include <QList>
#include "../../services/ProductService.h"

class QTableWidget;
class QLineEdit;
class QComboBox;

class ProductListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductListDialog(QWidget *parent = nullptr);

private slots:
    void searchProducts();
    void filterByCategory();

private:
    void loadProducts();
    void updateTable(const QList<Product> &list);

    QTableWidget *m_table;
    QLineEdit *m_searchEdit;
    QComboBox *m_categoryBox;

    QList<Product> m_products;
};

#endif
