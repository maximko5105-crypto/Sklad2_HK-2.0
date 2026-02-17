#include "CreateRequestDialog.h"
#include "../../services/RequestService.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

CreateRequestDialog::CreateRequestDialog(int userId,
                                         QWidget *parent)
    : QDialog(parent),
      m_userId(userId)
{
    setWindowTitle("Создать заявку");
    setMinimumWidth(400);

    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Выберите товар:"));

    productCombo = new QComboBox();
    products = ProductService::getAllProducts();

    for (const Product& p : products) {
        productCombo->addItem(
            p.name + " (" + QString::number(p.quantity) + " шт)",
            p.id
        );
    }

    layout->addWidget(productCombo);

    layout->addWidget(new QLabel("Количество:"));
    quantitySpin = new QSpinBox();
    quantitySpin->setRange(1, 100000);
    layout->addWidget(quantitySpin);

    layout->addWidget(new QLabel("Когда нужно:"));
    dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    dateTimeEdit->setCalendarPopup(true);
    layout->addWidget(dateTimeEdit);

    submitButton = new QPushButton("Отправить заявку");
    submitButton->setMinimumHeight(40);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked,
            this, &CreateRequestDialog::onSubmit);
}

void CreateRequestDialog::onSubmit()
{
    int productId = productCombo->currentData().toInt();
    int quantity = quantitySpin->value();
    QString dateTime = dateTimeEdit->dateTime().toString(Qt::ISODate);

    if (RequestService::createRequest(m_userId,
                                      productId,
                                      quantity,
                                      dateTime)) {
        QMessageBox::information(this,
                                 "Успех",
                                 "Заявка отправлена");
        accept();
    } else {
        QMessageBox::critical(this,
                              "Ошибка",
                              "Не удалось создать заявку");
    }
}
