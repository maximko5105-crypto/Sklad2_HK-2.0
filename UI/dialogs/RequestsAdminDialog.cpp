#include "RequestsAdminDialog.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

RequestsAdminDialog::RequestsAdminDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Заявки пользователей");
    resize(800, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(5);
    m_table->setHorizontalHeaderLabels({
        "ID",
        "Пользователь",
        "Товар",
        "Дата",
        "Статус"
    });

    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(m_table);

    refreshTable();
}

void RequestsAdminDialog::refreshTable()
{
    m_table->setRowCount(0);

    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT r.id, u.username, p.name, r.date_needed, r.status "
                  "FROM requests r "
                  "LEFT JOIN users u ON r.user_id = u.id "
                  "LEFT JOIN products p ON r.product_id = p.id");

    if (!query.exec())
    {
        qDebug() << "Request load error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next())
    {
        m_table->insertRow(row);

        for (int col = 0; col < 5; ++col)
        {
            m_table->setItem(row, col,
                new QTableWidgetItem(query.value(col).toString()));
        }

        row++;
    }
}
