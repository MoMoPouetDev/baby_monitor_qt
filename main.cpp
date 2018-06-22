#include <QApplication>
#include <QtWidgets>

#include "manager.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    Manager MainManager;

    return app.exec();
}
