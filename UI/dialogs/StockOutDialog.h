#ifndef STOCKOUTDIALOG_H
#define STOCKOUTDIALOG_H

#include <QDialog>

class QComboBox;
class QSpinBox;

class StockOutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StockOutDialog(QWidget *parent = nullptr);

private:
    QComboBox *productBox;
    QSpinBox  *qtySpin;

    void loadProducts();
};

#endif
