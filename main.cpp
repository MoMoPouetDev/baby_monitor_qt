#include <QApplication>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtWidgets>

#include "mainwindow.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow MainWindow;

    MainWindow.show();

    return app.exec();
}
