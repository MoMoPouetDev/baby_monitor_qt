#include <QDebug>

#include "menuwindow.h"

MenuWindow::MenuWindow() : QObject()
{
    m_mainWindow = new MainWindow;
}

MenuWindow::~MenuWindow()
{
    delete m_mainWindow;
}
