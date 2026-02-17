#include "AccountDialog.h"
#include "services/RequestService.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>

AccountDialog::AccountDialog(int userId,
                             const QString& username,
                             QWidget *parent)
    : QDialog(parent),
      m_userId(userId),
      m_username(username)
{
    setWindowTitle("Личный кабинет: " + m_username);
    resize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);

    requestsTable = new QTableWidget(this);
    requestsTable->setColumnCount(4);
    requestsTable->setHorizontalHeaderLabels(
        {"ID", "Товар", "Количество", "Статус"});

    requestsTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(requestsTable);

    QPushButton *refreshBtn = new QPushButton("Обновить", this);
    layout->addWidget(refreshBtn);

    connect(refreshBtn, &QPushButton::clicked,
            this, &AccountDialog::refreshRequests);

    refreshRequests();
}

void AccountDialog::refreshRequests()
{
    requestsTable->setRowCount(0);

    QList<Request> requests =
        RequestService::getRequestsByUser(m_userId);

    for (int i = 0; i < requests.size(); ++i)
    {
        const Request &r = requests[i];

        requestsTable->insertRow(i);

        requestsTable->setItem(i, 0,
            new QTableWidgetItem(QString::number(r.id)));

        requestsTable->setItem(i, 1,
            new QTableWidgetItem(QString::number(r.productId)));

        requestsTable->setItem(i, 2,
            new QTableWidgetItem(QString::number(r.quantity)));

        requestsTable->setItem(i, 3,
            new QTableWidgetItem(r.status));
    }
}
