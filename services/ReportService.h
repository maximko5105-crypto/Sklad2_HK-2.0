#ifndef REPORTSERVICE_H
#define REPORTSERVICE_H

#include <QVector>
#include <QMap>
#include <QString>
#include <QVariant>

class ReportService
{
public:
    void generateWarehouseReport();

private:
    QVector<QMap<QString, QVariant>> getWarehouseData();
};

#endif
