#include "QDebug"

#include "manager.h"

Manager::Manager() : QObject()
{
    m_mainWindow = new MainWindow;
    m_menuWindow = new MenuWindow(m_mainWindow);
    m_client = new ClientTcp;

    emit m_mainWindow->isReadyMenu(m_menuWindow);
    emit m_client->isReadyMenu(m_menuWindow);

    m_mainWindow->setShow();
}

Manager::~Manager()
{
    m_mainWindow->deleteLater();
    m_menuWindow->deleteLater();
    m_client->deleteLater();
}

MainWindow* Manager::getInstanceMainWindow()
{
    return m_mainWindow;
}

MenuWindow* Manager::getInstanceMenuWindow()
{
    return m_menuWindow;
}

ClientTcp* Manager::getInstanceClientTcp()
{
    return m_client;
}
