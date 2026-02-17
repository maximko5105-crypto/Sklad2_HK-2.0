#include "KPIWidget.h"
#include <QVBoxLayout>
#include <QLabel>

KPIWidget::KPIWidget(const QString &title,
                     const QString &icon,
                     QWidget *parent)
    : QFrame(parent)
{
    setFixedHeight(120);
    setStyleSheet(R"(
        QFrame {
            background-color: #1E293B;
            border-radius: 14px;
        }
    )");

    auto *layout = new QVBoxLayout(this);

    iconLabel = new QLabel(icon);
    iconLabel->setStyleSheet("font-size: 22px;");

    titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: #94A3B8; font-size: 14px;");

    valueLabel = new QLabel("0");
    valueLabel->setStyleSheet(
        "color: white; font-size: 28px; font-weight: bold;");

    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
}

void KPIWidget::setValue(const QString &value)
{
    valueLabel->setText(value);
}
