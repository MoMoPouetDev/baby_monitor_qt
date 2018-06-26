#include "QDebug"

#include "manager.h"

Manager::Manager() : QObject()
{
    manage_mainWindow = new MainWindow;
    manage_menuWindow = new MenuWindow;
    manage_client = new ClientTcp;

    QObject::connect(manage_client, SIGNAL(connectionStatus()), this, SLOT(connectionStatus()));

    manage_mainWindow->setShow();
}

Manager::~Manager()
{
    //delete main_mainWindow;
    //delete m_client;
}

void Manager::connectionStatus()
{
    manage_menuWindow->setConnectionIcon(manage_client->getConnectionStatus());
}
