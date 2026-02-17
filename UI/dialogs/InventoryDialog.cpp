#include "InventoryDialog.h"
#include "../../services/StockService.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QMessageBox>

InventoryDialog::InventoryDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Инвентаризация");

    QVBoxLayout *layout = new QVBoxLayout(this);

    productBox = new QComboBox;
    actualSpin = new QSpinBox;
    actualSpin->setMaximum(100000);

    QPushButton *btn = new QPushButton("Применить");

    layout->addWidget(productBox);
    layout->addWidget(actualSpin);
    layout->addWidget(btn);

    loadProducts();

    connect(btn,&QPushButton::clicked,this,[=](){
        int id = productBox->currentData().toInt();
        StockService::inventory(id, actualSpin->value());
        QMessageBox::information(this,"OK","Инвентаризация выполнена");
        accept();
    });
}

void InventoryDialog::loadProducts()
{
    productBox->clear();
    QSqlQuery q("SELECT id,name FROM products");
    while(q.next())
        productBox->addItem(q.value(1).toString(), q.value(0));
}
