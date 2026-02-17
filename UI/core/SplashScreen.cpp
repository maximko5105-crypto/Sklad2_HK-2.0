#include "SplashScreen.h"

#include <QPainter>
#include <QFont>
#include <QApplication>
#include <QThread>

SplashScreen::SplashScreen()
{
    QPixmap pixmap(600, 350);
    pixmap.fill(QColor("#0f172a")); // глубокий синий

    QPainter painter(&pixmap);

    // Название
    painter.setPen(QColor("#38bdf8")); // небесный
    painter.setFont(QFont("Segoe UI", 28, QFont::Bold));
    painter.drawText(pixmap.rect(),
                     Qt::AlignCenter,
                     "sklad2_HK");

    // Подзаголовок
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 12));
    painter.drawText(0, 250,
                     pixmap.width(),
                     50,
                     Qt::AlignCenter,
                     "Warehouse Management System");

    setPixmap(pixmap);
}

void SplashScreen::showSplash(int durationMs)
{
    show();
    QApplication::processEvents();
    QThread::msleep(durationMs);
}
