#ifndef REQUESTSPAGE_H
#define REQUESTSPAGE_H

#include <QWidget>

class QTableWidget;
class QLineEdit;
class QComboBox;
class QPushButton;
class QStackedWidget;
class QWidget;

class RequestsPage : public QWidget
{
    Q_OBJECT

public:
    explicit RequestsPage(QWidget *parent = nullptr);

private:
    void setupUI();
    void loadRequests();
    void applyFilters();
    void createStatusBadge(int row, const QString &status);

    QStackedWidget *stack;

    // list page
    QWidget *listPage;
    QTableWidget *table;
    QLineEdit *searchEdit;
    QComboBox *statusFilter;
    QPushButton *createButton;
    QPushButton *approveButton;
    QPushButton *rejectButton;

    // form page
    QWidget *formPage;
    QLineEdit *titleEdit;
    QLineEdit *quantityEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif
