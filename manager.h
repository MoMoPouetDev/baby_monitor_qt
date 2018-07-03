#ifndef MANAGER_H
#define MANAGER_H

#include "mainwindow.h"
#include "clienttcp.h"
#include "menuwindow.h"
#include "menumusicwindow.h"
#include "decoder.h"

class MainWindow;
class MenuWindow;
class MenuMusicWindow;
class ClientTcp;
class Decoder;
class Manager : public QObject
{
    Q_OBJECT

public:
    Manager();
    ~Manager();
    MainWindow* getInstanceMainWindow();
    MenuWindow* getInstanceMenuWindow();
    MenuMusicWindow* getInstanceMenuMusicWindow();
    ClientTcp* getInstanceClientTcp();
    Decoder* getInstanceDecoder();

private:
    MainWindow *m_mainWindow;
    MenuWindow *m_menuWindow;
    MenuMusicWindow *m_menuMusicWindow;
    ClientTcp *m_client;
    Decoder *m_decoder;

};

#endif // MANAGER_H
