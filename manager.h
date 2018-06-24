#ifndef MANAGER_H
#define MANAGER_H

#include "mainwindow.h"
#include "clienttcp.h"

class Manager : public QObject
{
    Q_OBJECT

public:
    Manager();
    ~Manager();

public slots:
    void connectionStatus();

private:
    MainWindow *m_mainWindow,
                *m_connectingInfo;
    ClientTcp *m_client;

};

#endif // MANAGER_H
