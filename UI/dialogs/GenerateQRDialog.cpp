#include "GenerateQRDialog.h"
#include "../../services/ProductService.h"
#include "../../services/QRService.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

GenerateQRDialog::GenerateQRDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Создать QR код");
    resize(400, 200);

    QVBoxLayout* layout = new QVBoxLayout(this);

    productBox = new QComboBox();

    QList<Product> products =
        ProductService::getAllProducts();

    for (const Product& p : products)
    {
        productBox->addItem(
            p.name,
            p.id
        );
    }

    layout->addWidget(productBox);

    generateButton = new QPushButton("Сохранить QR");
    generateButton->setMinimumHeight(40);
    layout->addWidget(generateButton);

    connect(generateButton,
            &QPushButton::clicked,
            this,
            &GenerateQRDialog::generateQR);
}

void GenerateQRDialog::generateQR()
{
    int productId =
        productBox->currentData().toInt();

    QString filePath =
        QFileDialog::getSaveFileName(
            this,
            "Сохранить QR",
            "",
            "PNG (*.png)"
        );

    if (filePath.isEmpty())
        return;

    if (QRService::generateProductQR(productId,
                                     filePath))
    {
        QMessageBox::information(
            this,
            "Успех",
            "QR код сохранён");
        accept();
    }
    else
    {
        QMessageBox::critical(
            this,
            "Ошибка",
            "Не удалось создать QR");
    }
}
