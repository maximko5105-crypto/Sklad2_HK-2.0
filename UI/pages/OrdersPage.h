#ifndef ORDERSPAGE_H
#define ORDERSPAGE_H

#include <QWidget>

class QTableWidget;
class QLineEdit;
class QPushButton;
class QComboBox;
class QStackedWidget;
class QWidget;

class OrdersPage : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersPage(QWidget *parent = nullptr);

private:
    void setupUI();
    void loadOrders();
    void createStatusBadge(int row, const QString &status);

    QStackedWidget *stack;

    // list page
    QWidget *listPage;
    QTableWidget *table;
    QLineEdit *searchEdit;
    QPushButton *createButton;
    QPushButton *deliverButton;
    QPushButton *cancelButton;

    // form page
    QWidget *formPage;
    QLineEdit *productEdit;
    QLineEdit *quantityEdit;
    QPushButton *saveButton;
    QPushButton *backButton;
};

#endif
