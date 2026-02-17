#include "ContainerDialog.h"
#include "../../services/ContainerService.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QMessageBox>

ContainerDialog::ContainerDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Контейнер");

    QVBoxLayout *layout = new QVBoxLayout(this);

    containerBox = new QComboBox;
    productBox = new QComboBox;
    qtySpin = new QSpinBox;
    qtySpin->setMaximum(100000);

    QPushButton *btn = new QPushButton("Добавить");

    layout->addWidget(containerBox);
    layout->addWidget(productBox);
    layout->addWidget(qtySpin);
    layout->addWidget(btn);

    loadData();

    connect(btn,&QPushButton::clicked,this,[=](){
        int cid = containerBox->currentData().toInt();
        int pid = productBox->currentData().toInt();

        if(ContainerService::addToContainer(cid,pid,qtySpin->value()))
        {
            QMessageBox::information(this,"OK","Добавлено в контейнер");
            accept();
        }
        else
        {
            QMessageBox::warning(this,"Ошибка","Недостаточно товара");
        }
    });
}

void ContainerDialog::loadData()
{
    QSqlQuery c("SELECT id,name FROM containers");
    while(c.next())
        containerBox->addItem(c.value(1).toString(), c.value(0));

    QSqlQuery p("SELECT id,name FROM products");
    while(p.next())
        productBox->addItem(p.value(1).toString(), p.value(0));
}
