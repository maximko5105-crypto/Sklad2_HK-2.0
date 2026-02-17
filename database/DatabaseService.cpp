#include <QApplication>
#include "database/DatabaseService.h"
#include "UI/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!DatabaseService::initialize())
        return -1;

    MainWindow w;
    w.show();

    return app.exec();
}
