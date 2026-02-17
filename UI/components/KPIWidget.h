#ifndef KPIWIDGET_H
#define KPIWIDGET_H

#include <QFrame>

class QLabel;

class KPIWidget : public QFrame
{
    Q_OBJECT
public:
    explicit KPIWidget(const QString &title,
                       const QString &icon,
                       QWidget *parent = nullptr);

    void setValue(const QString &value);

private:
    QLabel *titleLabel;
    QLabel *valueLabel;
    QLabel *iconLabel;
};

#endif
