#ifndef CREATEREQUESTDIALOG_H
#define CREATEREQUESTDIALOG_H

#include <QDialog>
#include "../../services/ProductService.h"

class QComboBox;
class QSpinBox;
class QDateTimeEdit;
class QPushButton;

class CreateRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRequestDialog(int userId,
                                 QWidget *parent = nullptr);

private slots:
    void onSubmit();

private:
    int m_userId;

    QComboBox* productCombo;
    QSpinBox* quantitySpin;
    QDateTimeEdit* dateTimeEdit;
    QPushButton* submitButton;

    QList<Product> products;
};

#endif // CREATEREQUESTDIALOG_H
