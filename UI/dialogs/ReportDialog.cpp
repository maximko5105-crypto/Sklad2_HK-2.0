#include "ReportDialog.h"
#include "services/ReportService.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

ReportDialog::ReportDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Отчет по складу");
    resize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *btn = new QPushButton("Сформировать отчет", this);
    layout->addWidget(btn);

    connect(btn, &QPushButton::clicked,
            this, &ReportDialog::generateReport);
}

void ReportDialog::generateReport()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет",
        "report.pdf",
        "PDF (*.pdf)");

    if (filePath.isEmpty())
        return;

    if (ReportService::generateWarehouseReport(filePath))
        QMessageBox::information(this, "Готово", "Отчет создан");
    else
        QMessageBox::warning(this, "Ошибка", "Ошибка создания отчета");
}
