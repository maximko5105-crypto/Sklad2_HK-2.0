#include "CreateOrderDialog.h"
#include "../../services/OrderService.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

CreateOrderDialog::CreateOrderDialog(int userId,
                                     QWidget *parent)
    : QDialog(parent),
      m_userId(userId)
{
    setWindowTitle("Заказ на закупку");
    resize(500, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Что нужно заказать:"));
    descriptionEdit = new QTextEdit();
    layout->addWidget(descriptionEdit);

    layout->addWidget(new QLabel("Количество:"));
    quantitySpin = new QSpinBox();
    quantitySpin->setRange(1, 100000);
    layout->addWidget(quantitySpin);

    layout->addWidget(new QLabel("Срок:"));
    deadlineEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    deadlineEdit->setCalendarPopup(true);
    layout->addWidget(deadlineEdit);

    submitButton = new QPushButton("Отправить заказ");
    submitButton->setMinimumHeight(40);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked,
            this, &CreateOrderDialog::onSubmit);
}

void CreateOrderDialog::onSubmit()
{
    QString description = descriptionEdit->toPlainText().trimmed();
    int quantity = quantitySpin->value();
    QString deadline =
        deadlineEdit->dateTime().toString(Qt::ISODate);

    if (description.isEmpty()) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Введите описание");
        return;
    }

    if (OrderService::createOrder(m_userId,
                                  description,
                                  quantity,
                                  deadline))
    {
        QMessageBox::information(this,
                                 "Успех",
                                 "Заказ отправлен");
        accept();
    }
    else
    {
        QMessageBox::critical(this,
                              "Ошибка",
                              "Не удалось создать заказ");
    }
}
