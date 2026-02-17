#include "UserDashboardDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlDatabase>

UserDashboardDialog::UserDashboardDialog(int userId, QWidget *parent)
    : QDialog(parent), m_userId(userId)
{
    setWindowTitle("Кабинет пользователя");
    resize(800, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Мои заявки", this);
    layout->addWidget(title);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels({
        "ID",
        "Товар",
        "Дата",
        "Статус"
    });

    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(m_table);

    loadData();
}

void UserDashboardDialog::loadData()
{
    m_table->setRowCount(0);

    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT r.id, p.name, r.date_needed, r.status "
                  "FROM requests r "
                  "LEFT JOIN products p ON r.product_id = p.id "
                  "WHERE r.user_id = :uid");

    query.bindValue(":uid", m_userId);
    query.exec();

    int row = 0;
    while (query.next())
    {
        m_table->insertRow(row);

        for (int col = 0; col < 4; ++col)
        {
            m_table->setItem(row, col,
                new QTableWidgetItem(query.value(col).toString()));
        }

        row++;
    }
}
