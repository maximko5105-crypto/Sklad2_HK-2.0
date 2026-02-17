#ifndef QRGENERATOR_H
#define QRGENERATOR_H

#include <QString>
#include <QImage>

class QrGenerator
{
public:
    static QImage generate(const QString& text, int size = 300);
};

#endif
