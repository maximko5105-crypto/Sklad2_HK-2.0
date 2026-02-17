#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>

class QPushButton;

class ReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportDialog(QWidget *parent = nullptr);

private slots:
    void generateReport();

private:
    QPushButton* generateButton;
};

#endif // REPORTDIALOG_H
