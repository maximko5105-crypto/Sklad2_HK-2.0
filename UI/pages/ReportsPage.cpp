#include "ReportsPage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QFileDialog>
#include <QMessageBox>

#include <QPrinter>
#include <QPainter>

#include "../../services/StockService.h"
#include "../../services/RequestService.h"
#include "../../services/LogService.h"

ReportsPage::ReportsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void ReportsPage::setupUI()
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40,40,40,40);
    layout->setSpacing(20);

    QLabel *title = new QLabel("Отчёты");
    title->setStyleSheet("font-size:26px; font-weight:600;");
    layout->addWidget(title);

    reportTypeBox = new QComboBox;
    reportTypeBox->addItems({
        "Отчёт по складу",
        "Отчёт по заявкам"
    });

    fromDateEdit = new QDateEdit;
    fromDateEdit->setCalendarPopup(true);

    toDateEdit = new QDateEdit;
    toDateEdit->setCalendarPopup(true);

    generateButton = new QPushButton("Сгенерировать PDF");

    layout->addWidget(new QLabel("Тип отчёта:"));
    layout->addWidget(reportTypeBox);
    layout->addWidget(new QLabel("С даты:"));
    layout->addWidget(fromDateEdit);
    layout->addWidget(new QLabel("По дату:"));
    layout->addWidget(toDateEdit);
    layout->addWidget(generateButton);
    layout->addStretch();

    connect(generateButton, &QPushButton::clicked,
            this, &ReportsPage::generateReport);
}

void ReportsPage::generateReport()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить PDF",
        "report.pdf",
        "PDF Files (*.pdf)");

    if (fileName.isEmpty())
        return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter(&printer);

    int y = 100;

    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(100, y, "sklad2_HK - Отчёт");
    y += 60;

    painter.setFont(QFont("Arial", 12));

    QString type = reportTypeBox->currentText();

    if (type == "Отчёт по складу")
    {
        StockService stock;
        auto products = stock.getAllProducts();

        painter.drawText(100, y, "Остатки на складе:");
        y += 40;

        for (const auto &p : products)
        {
            painter.drawText(120, y,
                p.name + " — " +
                QString::number(p.quantity));
            y += 30;
        }
    }
    else
    {
        RequestService request;
        auto requests = request.getAllRequests();

        painter.drawText(100, y, "Заявки:");
        y += 40;

        for (const auto &r : requests)
        {
            painter.drawText(120, y,
                r.title + " — " +
                QString::number(r.quantity) +
                " — " + r.status);
            y += 30;
        }
    }

    painter.end();

    LogService::log("Сформирован PDF отчёт");

    QMessageBox::information(this,
        "Готово",
        "Отчёт успешно создан");
}
