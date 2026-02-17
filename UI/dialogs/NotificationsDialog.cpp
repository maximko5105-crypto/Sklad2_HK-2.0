#include "NotificationsDialog.h"
#include "../../services/NotificationService.h"

#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QBrush>

NotificationsDialog::NotificationsDialog(int userId,
                                         QWidget *parent)
    : QDialog(parent),
      m_userId(userId)
{
    setWindowTitle("Центр уведомлений");
    resize(800, 600);

    QVBoxLayout* layout = new QVBoxLayout(this);

    table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({
        "ID",
        "Заголовок",
        "Сообщение",
        "Дата"
    });

    table->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(table);

    markReadButton =
        new QPushButton("Отметить как прочитано");
    markReadButton->setMinimumHeight(40);

    refreshButton =
        new QPushButton("Обновить");
    refreshButton->setMinimumHeight(40);

    layout->addWidget(markReadButton);
    layout->addWidget(refreshButton);

    connect(markReadButton,
            &QPushButton::clicked,
            this,
            &NotificationsDialog::markSelectedAsRead);

    connect(refreshButton,
            &QPushButton::clicked,
            this,
            &NotificationsDialog::refresh);

    loadNotifications();
}

void NotificationsDialog::refresh()
{
    loadNotifications();
}

void NotificationsDialog::loadNotifications()
{
    table->setRowCount(0);

    QList<Notification> list =
        NotificationService::getByUser(m_userId);

    for (int i = 0; i < list.size(); ++i)
    {
        const Notification& n = list[i];

        table->insertRow(i);

        table->setItem(i, 0,
            new QTableWidgetItem(
                QString::number(n.id)));

        table->setItem(i, 1,
            new QTableWidgetItem(n.title));

        table->setItem(i, 2,
            new QTableWidgetItem(n.message));

        table->setItem(i, 3,
            new QTableWidgetItem(n.createdAt));

        // 🔴 Непрочитанные выделяем
        if (!n.isRead)
        {
            for (int col = 0; col < 4; ++col)
            {
                table->item(i, col)
                    ->setBackground(
                        QBrush(QColor(255, 230, 230)));
            }
        }
    }
}

void NotificationsDialog::markSelectedAsRead()
{
    int row = table->currentRow();

    if (row < 0)
        return;

    int notificationId =
        table->item(row, 0)->text().toInt();

    NotificationService::markAsRead(notificationId);

    loadNotifications();
}
