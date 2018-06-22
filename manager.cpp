#include "manager.h"

Manager::Manager()
{
    m_mainWindow = new MainWindow;

    m_client = new ClientTcp;

    m_mainWindow->show();
}

Manager::~Manager()
{
    delete m_mainWindow;
    delete m_client;
}
