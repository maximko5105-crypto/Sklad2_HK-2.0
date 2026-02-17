#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include <QTableWidget>

class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(int userId,
                           const QString& username,
                           QWidget *parent = nullptr);

private:
    void refreshRequests();

    int m_userId;
    QString m_username;
    QTableWidget *requestsTable;
};

#endif
