#ifndef USERDASHBOARDDIALOG_H
#define USERDASHBOARDDIALOG_H

#include <QDialog>

class QTableWidget;

class UserDashboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDashboardDialog(int userId,
                                 QWidget *parent = nullptr);

private:
    void loadData();

    int m_userId;
    QTableWidget *m_table;
};

#endif
