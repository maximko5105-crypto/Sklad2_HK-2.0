#ifndef STOCKINDIALOG_H
#define STOCKINDIALOG_H

#include <QDialog>

class QComboBox;
class QSpinBox;
class QLineEdit;
class QPushButton;

class StockInDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StockInDialog(QWidget *parent = nullptr);

private:
    QComboBox *productBox;
    QSpinBox  *qtySpin;
    QLineEdit *newProductEdit;
    QLineEdit *priceEdit;
    QPushButton *addProductBtn;

    void loadProducts();
    void addNewProduct();
};

#endif
