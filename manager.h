#ifndef MANAGER_H
#define MANAGER_H

#include "mainwindow.h"
#include "clienttcp.h"

class Manager
{
    //Q_OBJECT

public:
    Manager();
    ~Manager();

public slots:

private:
    MainWindow *m_mainWindow;
    ClientTcp *m_client;

};

#endif // MANAGER_H
