#ifndef INVENTORYDIALOG_H
#define INVENTORYDIALOG_H

#include <QDialog>

class QComboBox;
class QSpinBox;

class InventoryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InventoryDialog(QWidget *parent = nullptr);

private:
    QComboBox *productBox;
    QSpinBox  *actualSpin;

    void loadProducts();
};

#endif
