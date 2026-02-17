#ifndef CREATEORDERDIALOG_H
#define CREATEORDERDIALOG_H

#include <QDialog>

class QTextEdit;
class QSpinBox;
class QDateTimeEdit;
class QPushButton;

class CreateOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateOrderDialog(int userId,
                               QWidget *parent = nullptr);

private slots:
    void onSubmit();

private:
    int m_userId;

    QTextEdit* descriptionEdit;
    QSpinBox* quantitySpin;
    QDateTimeEdit* deadlineEdit;
    QPushButton* submitButton;
};

#endif // CREATEORDERDIALOG_H
