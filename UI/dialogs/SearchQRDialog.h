#ifndef SEARCHQRDIALOG_H
#define SEARCHQRDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;

class SearchQRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchQRDialog(QWidget *parent = nullptr);

private slots:
    void findProduct();

private:
    QLineEdit* inputEdit;
    QPushButton* findButton;
    QLabel* resultLabel;
};

#endif // SEARCHQRDIALOG_H
