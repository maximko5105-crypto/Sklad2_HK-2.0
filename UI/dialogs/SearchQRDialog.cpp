#include "SearchQRDialog.h"
#include "../../services/QRService.h"
#include "../../services/ProductService.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

SearchQRDialog::SearchQRDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Поиск по QR");
    resize(400, 250);

    QVBoxLayout* layout = new QVBoxLayout(this);

    inputEdit = new QLineEdit();
    inputEdit->setPlaceholderText(
        "Вставьте текст из QR...");
    layout->addWidget(inputEdit);

    findButton = new QPushButton("Найти");
    layout->addWidget(findButton);

    resultLabel = new QLabel();
    layout->addWidget(resultLabel);

    connect(findButton,
            &QPushButton::clicked,
            this,
            &SearchQRDialog::findProduct);
}

void SearchQRDialog::findProduct()
{
    QString qrText = inputEdit->text();

    int productId =
        QRService::parseProductId(qrText);

    if (productId == -1) {
        resultLabel->setText("Неверный QR код");
        return;
    }

    Product p =
        ProductService::getProductById(productId);

    if (p.id == 0) {
        resultLabel->setText("Товар не найден");
        return;
    }

    resultLabel->setText(
        "Название: " + p.name +
        "\nКатегория: " + p.category +
        "\nКоличество: " + QString::number(p.quantity)
    );
}
