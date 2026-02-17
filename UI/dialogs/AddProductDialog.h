#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>

class QLineEdit;
class QSpinBox;
class QPushButton;

class AddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductDialog(QWidget *parent = nullptr);

private slots:
    void onAddClicked();

private:
    QLineEdit *m_nameEdit;
    QLineEdit *m_categoryEdit;
    QSpinBox  *m_quantitySpin;
    QPushButton *m_addButton;
};

#endif
