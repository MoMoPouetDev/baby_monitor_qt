#include "QDebug"

#include "manager.h"

Manager::Manager() : QObject()
{
    m_mainWindow = new MainWindow;
    m_menuWindow = new MenuWindow;
    m_client = new ClientTcp;

    QObject::connect(m_client, SIGNAL(connectionStatus()), this, SLOT(connectionStatus()));

    m_mainWindow->setShow();
}

Manager::~Manager()
{
    m_mainWindow->deleteLater();
    m_menuWindow->deleteLater();
    m_client->deleteLater();
}

void Manager::connectionStatus()
{
    m_menuWindow->setConnectionIcon(m_client->getConnectionStatus());
}
