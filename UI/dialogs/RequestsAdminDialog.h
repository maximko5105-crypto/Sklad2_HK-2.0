#ifndef REQUESTSADMINDIALOG_H
#define REQUESTSADMINDIALOG_H

#include <QDialog>

class QTableWidget;

class RequestsAdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RequestsAdminDialog(QWidget *parent = nullptr);

private:
    void refreshTable();

    QTableWidget *m_table;
};

#endif
