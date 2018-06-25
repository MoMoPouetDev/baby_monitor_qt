#include "QDebug"

#include "manager.h"

Manager::Manager() : QObject()
{
    m_mainWindow = new MainWindow;
    m_client = new ClientTcp;

    QObject::connect(m_client, SIGNAL(connectionStatus()), this, SLOT(connectionStatus()));

    m_mainWindow->setShow();
}

Manager::~Manager()
{
    delete m_mainWindow;
    delete m_client;
}

void Manager::connectionStatus()
{
    m_menuWindow->setConnectionIcon(m_client->getConnectionStatus());
}
