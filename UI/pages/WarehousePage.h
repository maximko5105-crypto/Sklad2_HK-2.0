#ifndef WAREHOUSEPAGE_H
#define WAREHOUSEPAGE_H

#include <QWidget>

class QTableWidget;
class QLineEdit;
class QPushButton;
class QStackedWidget;
class QWidget;

class WarehousePage : public QWidget
{
    Q_OBJECT

public:
    explicit WarehousePage(QWidget *parent = nullptr);

private:
    void setupUI();
    void loadProducts();
    void highlightLowStock(int row, int quantity);

    QStackedWidget *stack;

    // list
    QWidget *listPage;
    QTableWidget *table;
    QLineEdit *searchEdit;
    QPushButton *addButton;
    QPushButton *increaseButton;
    QPushButton *decreaseButton;
    QPushButton *qrButton;

    // form
    QWidget *formPage;
    QLineEdit *nameEdit;
    QLineEdit *quantityEdit;
    QPushButton *saveButton;
    QPushButton *backButton;
};

#endif
