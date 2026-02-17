#ifndef QRSERVICE_H
#define QRSERVICE_H

#include <QString>

class QRService
{
public:
    static bool generateProductQR(int productId,
                                  const QString& filePath);

    static int parseProductId(const QString& qrText);
};

#endif // QRSERVICE_H
