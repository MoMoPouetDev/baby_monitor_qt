#include <QApplication>
#include <QPushButton>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget MainWindow;

    QPushButton button("bouton", &MainWindow);

    MainWindow.setFixedSize(480, 320);

    MainWindow.show();

    return app.exec();
}
