#ifndef REPORTSPAGE_H
#define REPORTSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

#include "services/RequestService.h"
#include "services/ReportService.h"

class ReportsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ReportsPage(QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QPushButton *generateBtn;
    QTextEdit *output;

    RequestService requestService;
    ReportService reportService;

private slots:
    void generateReport();
};

#endif
