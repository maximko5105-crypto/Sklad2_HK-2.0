#include "StockInDialog.h"
#include "../../services/StockService.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlQuery>
#include <QMessageBox>

StockInDialog::StockInDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Приход товара");

    QVBoxLayout *layout = new QVBoxLayout(this);

    productBox = new QComboBox;
    qtySpin = new QSpinBox;
    qtySpin->setMaximum(100000);

    newProductEdit = new QLineEdit;
    newProductEdit->setPlaceholderText("Новый товар");

    priceEdit = new QLineEdit;
    priceEdit->setPlaceholderText("Цена");

    addProductBtn = new QPushButton("Добавить товар");

    QPushButton *stockBtn = new QPushButton("Оформить приход");

    layout->addWidget(productBox);
    layout->addWidget(qtySpin);
    layout->addWidget(newProductEdit);
    layout->addWidget(priceEdit);
    layout->addWidget(addProductBtn);
    layout->addWidget(stockBtn);

    loadProducts();

    connect(addProductBtn,&QPushButton::clicked,this,&StockInDialog::addNewProduct);

    connect(stockBtn,&QPushButton::clicked,this,[=](){
        int id = productBox->currentData().toInt();
        if(StockService::addStock(id, qtySpin->value()))
        {
            QMessageBox::information(this,"OK","Приход добавлен");
            accept();
        }
        else
        {
            QMessageBox::warning(this,"Ошибка","Ошибка прихода");
        }
    });
}

void StockInDialog::loadProducts()
{
    productBox->clear();
    QSqlQuery q("SELECT id,name FROM products");
    while(q.next())
        productBox->addItem(q.value(1).toString(), q.value(0));
}

void StockInDialog::addNewProduct()
{
    QString name = newProductEdit->text();
    double price = priceEdit->text().toDouble();

    if(name.isEmpty())
        return;

    QSqlQuery q;
    q.prepare("INSERT INTO products(name,price) VALUES(?,?)");
    q.addBindValue(name);
    q.addBindValue(price);

    if(q.exec())
    {
        QMessageBox::information(this,"OK","Товар добавлен");
        loadProducts();
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Не удалось добавить товар");
    }
}
