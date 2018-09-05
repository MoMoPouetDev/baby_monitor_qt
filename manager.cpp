#include "QDebug"

#include "manager.h"

Manager::Manager() : QObject()
{
    m_mainWindow = new MainWindow;

    m_menuWindow = new MenuWindow(m_mainWindow);
    emit m_mainWindow->isReadyMenu(m_menuWindow);

    m_menuMusicWindow = new MenuMusicWindow(m_mainWindow);
    emit m_menuWindow->isReadyMusic(m_menuMusicWindow);

    m_client = new ClientTcp;
    emit m_client->isReadyMenu(m_menuWindow);
    emit m_client->isReadyWindow(m_mainWindow);
    emit m_menuMusicWindow->isReadyClient(m_client);
    emit m_mainWindow->isReadyClient(m_client);

    m_decoder = new Decoder;
    emit m_client->isReadyDecoder(m_decoder);
    emit m_decoder->isReadyClient(m_client);
    emit m_decoder->isReadyMenuMusicWindow(m_menuMusicWindow);

    m_mainWindow->setShow();
}

Manager::~Manager()
{
    m_mainWindow->deleteLater();
    m_menuWindow->deleteLater();
    m_menuMusicWindow->deleteLater();
    m_client->deleteLater();
    m_decoder->deleteLater();
}

MainWindow* Manager::getInstanceMainWindow()
{
    return m_mainWindow;
}

MenuWindow* Manager::getInstanceMenuWindow()
{
    return m_menuWindow;
}

MenuMusicWindow* Manager::getInstanceMenuMusicWindow()
{
    return m_menuMusicWindow;
}

ClientTcp* Manager::getInstanceClientTcp()
{
    return m_client;
}

Decoder* Manager::getInstanceDecoder()
{
    return m_decoder;
}
