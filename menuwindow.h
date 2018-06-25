#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

#include "mainwindow.h"

class MenuWindow : public QObject
{
    //Q_OBJECT

public:
    MenuWindow();
    ~MenuWindow();

private:
    MainWindow *m_mainWindow;
};

#endif // MENUWINDOW_H
