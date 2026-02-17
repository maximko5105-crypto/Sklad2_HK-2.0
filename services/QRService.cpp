#include "QRService.h"
#include <QImage>
#include <QPainter>
#include <QDebug>

// ВАЖНО: для полноценного QR лучше подключить библиотеку,
// но сейчас делаем упрощённый вариант (кодируем текст)

bool QRService::generateProductQR(int productId,
                                  const QString& filePath)
{
    QString data = "PRODUCT_ID:" + QString::number(productId);

    QImage image(300, 300, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));

    painter.drawText(image.rect(),
                     Qt::AlignCenter,
                     data);

    painter.end();

    return image.save(filePath);
}

int QRService::parseProductId(const QString& qrText)
{
    if (qrText.startsWith("PRODUCT_ID:"))
    {
        QString idStr = qrText.section(":", 1);
        return idStr.toInt();
    }

    return -1;
}
