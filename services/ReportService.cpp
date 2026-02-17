#include "ReportService.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

QVector<QMap<QString, QVariant>> ReportService::getWarehouseData()
{
    QVector<QMap<QString, QVariant>> list;

    // Временные тестовые данные
    QMap<QString, QVariant> item1;
    item1["name"] = "Product A";
    item1["quantity"] = 50;

    QMap<QString, QVariant> item2;
    item2["name"] = "Product B";
    item2["quantity"] = 120;

    list.append(item1);
    list.append(item2);

    return list;
}

void ReportService::generateWarehouseReport()
{
    auto products = getWarehouseData();

    QFile file("warehouse_report.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot create warehouse_report.txt";
        return;
    }

    QTextStream out(&file);

    out << "=== Warehouse Report ===\n\n";

    for (const auto &p : products) {
        out << "Product: "
            << p.value("name").toString()
            << " | Quantity: "
            << p.value("quantity").toInt()
            << "\n";
    }

    file.close();
}
