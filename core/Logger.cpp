#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

void Logger::log(const QString& message)
{
    QFile file("app.log");
    if(file.open(QIODevice::Append))
    {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
            << message << "\n";
        file.close();
    }
}
