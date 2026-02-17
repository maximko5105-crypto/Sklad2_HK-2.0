#include "QrGenerator.h"
#include "../qrcodegen/cpp/qrcodegen.hpp"
using namespace qrcodegen;


using qrcodegen::QrCode;

QImage QrGenerator::generate(const QString& text, int size)
{
    QrCode qr = QrCode::encodeText(text.toStdString().c_str(),
                                   QrCode::Ecc::LOW);

    int qrSize = qr.getSize();
    int scale = size / qrSize;

    QImage image(qrSize*scale, qrSize*scale, QImage::Format_RGB32);
    image.fill(Qt::white);

    for(int y=0; y<qrSize; y++)
    {
        for(int x=0; x<qrSize; x++)
        {
            if(qr.getModule(x,y))
            {
                for(int dy=0; dy<scale; dy++)
                    for(int dx=0; dx<scale; dx++)
                        image.setPixel(x*scale+dx, y*scale+dy, qRgb(0,0,0));
            }
        }
    }

    return image;
}
