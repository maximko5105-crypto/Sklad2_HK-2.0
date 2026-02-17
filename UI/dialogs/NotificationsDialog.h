#ifndef NOTIFICATIONSDIALOG_H
#define NOTIFICATIONSDIALOG_H

#include <QDialog>

class QTableWidget;
class QPushButton;

class NotificationsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotificationsDialog(int userId,
                                 QWidget *parent = nullptr);

private slots:
    void loadNotifications();
    void markSelectedAsRead();
    void refresh();

private:
    int m_userId;

    QTableWidget* table;
    QPushButton* markReadButton;
    QPushButton* refreshButton;
};

#endif // NOTIFICATIONSDIALOG_H
