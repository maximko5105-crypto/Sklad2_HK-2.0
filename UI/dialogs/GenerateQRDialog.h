#ifndef GENERATEQRDIALOG_H
#define GENERATEQRDIALOG_H

#include <QDialog>

class QComboBox;
class QPushButton;

class GenerateQRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateQRDialog(QWidget *parent = nullptr);

private slots:
    void generateQR();

private:
    QComboBox* productBox;
    QPushButton* generateButton;
};

#endif // GENERATEQRDIALOG_H
