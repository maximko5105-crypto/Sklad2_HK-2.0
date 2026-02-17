#include "HistoryDialog.h"

#include <QVBoxLayout>
#include <QTableView>
#include <QLineEdit>
#include <QSqlQueryModel>

HistoryDialog::HistoryDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("История операций");

    QVBoxLayout *layout = new QVBoxLayout(this);

    filterEdit = new QLineEdit;
    filterEdit->setPlaceholderText("Фильтр по названию товара");

    table = new QTableView;

    layout->addWidget(filterEdit);
    layout->addWidget(table);

    loadHistory();

    connect(filterEdit,&QLineEdit::textChanged,this,[=](const QString& text){
        loadHistory(text);
    });
}

void HistoryDialog::loadHistory(const QString& filter)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString query =
        "SELECT h.id, p.name, h.operation, h.quantity, h.created_at "
        "FROM history h "
        "JOIN products p ON h.product_id = p.id ";

    if(!filter.isEmpty())
        query += "WHERE p.name LIKE '%" + filter + "%' ";

    query += "ORDER BY h.created_at DESC";

    model->setQuery(query);
    table->setModel(model);
}
