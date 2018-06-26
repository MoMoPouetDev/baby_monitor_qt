#ifndef MANAGER_H
#define MANAGER_H

#include "mainwindow.h"
#include "clienttcp.h"
#include "menuwindow.h"

class Manager : public QObject
{
    Q_OBJECT

public:
    Manager();
    ~Manager();

public slots:
    void connectionStatus();

private:
    MainWindow *manage_mainWindow,
                *manage_connectingInfo;
    MenuWindow *manage_menuWindow;
    ClientTcp *manage_client;

};

#endif // MANAGER_H
