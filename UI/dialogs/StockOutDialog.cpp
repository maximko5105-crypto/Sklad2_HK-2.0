#include "StockOutDialog.h"
#include "../../services/StockService.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QMessageBox>

StockOutDialog::StockOutDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Списание товара");

    QVBoxLayout *layout = new QVBoxLayout(this);

    productBox = new QComboBox;
    qtySpin = new QSpinBox;
    qtySpin->setMaximum(100000);

    QPushButton *btn = new QPushButton("Списать");

    layout->addWidget(productBox);
    layout->addWidget(qtySpin);
    layout->addWidget(btn);

    loadProducts();

    connect(btn,&QPushButton::clicked,this,[=](){
        int id = productBox->currentData().toInt();

        if(StockService::removeStock(id, qtySpin->value()))
        {
            QMessageBox::information(this,"OK","Списание выполнено");
            accept();
        }
        else
        {
            QMessageBox::warning(this,"Ошибка","Недостаточно товара");
        }
    });
}

void StockOutDialog::loadProducts()
{
    productBox->clear();
    QSqlQuery q("SELECT id,name FROM products");
    while(q.next())
        productBox->addItem(q.value(1).toString(), q.value(0));
}
