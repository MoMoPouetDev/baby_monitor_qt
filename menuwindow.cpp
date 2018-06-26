#include <QDebug>

#include "menuwindow.h"
#include "mainwindow.h"

MenuWindow::MenuWindow() : QObject()
{
    menu_mainWindow = new MainWindow;

 /**********************************************/
    m_menuWindow = new QDialog(menu_mainWindow);
    //secondeFenetre->setWindowModality(Qt::NonModal);



        //QObject::connect(m_buttonConnection, SIGNAL(clicked()), m_menuWindow, SLOT(open()));
        //secondeFenetre->show();

/************************************************************/

    m_buttonConnection = new QPushButton;
    m_buttonConnection->setFlat(true);
    m_iconConnectionOn.addFile(m_pathIconConnectionOn);
    m_iconConnectionOff.addFile(m_pathIconConnectionOff);
    m_buttonConnection->setIcon(m_iconConnectionOff);
    m_buttonConnection->setIconSize(QSize(15,15));
    m_buttonConnection->setGeometry(465, 0, 15, 15);
    m_buttonConnection->setEnabled(true);

    m_buttonPower = new QPushButton();
    m_buttonPower->setFlat(true);
    m_iconPower.addFile(m_pathIconPower);
    m_buttonPower->setIcon(m_iconPower);
    m_buttonPower->setIconSize(QSize(30,30));
    //m_buttonPower->setGeometry(440, 10, 33, 33);

    m_buttonUp = new QPushButton();
    m_buttonUp->setFlat(true);
    m_iconSoundUp.addFile(m_pathIconSoundUp);
    m_buttonUp->setIcon(m_iconSoundUp);
    m_buttonUp->setIconSize(QSize(30,30));
    //m_buttonUp->setGeometry(440, 220, 33, 33);

    m_buttonSound = new QPushButton();
    m_buttonSound->setFlat(true);
    m_iconNomute.addFile(m_pathIconNomute);
    m_iconMute.addFile(m_pathIconMute);
    m_buttonSound->setIcon(m_iconNomute);
    m_buttonSound->setIconSize(QSize(30,30));
    //m_buttonSound->setGeometry(440, 250, 33, 33);

    m_buttonDown = new QPushButton();
    m_buttonDown->setFlat(true);
    m_iconSoundDown.addFile(m_pathIconSoundDown);
    m_buttonDown->setIcon(m_iconSoundDown);
    m_buttonDown->setIconSize(QSize(30,30));
    //m_buttonDown->setGeometry(440, 280, 33, 33);

    m_progressSound = new QProgressBar();
    //m_progressSound->setGeometry(440, 50, 33, 160);
    m_progressSound->setOrientation(Qt::Vertical);
    m_progressSound->setValue(menu_mainWindow->getVolumeValuePlayer());
    m_progressSound->setStyleSheet(m_style);
    m_progressSound->setTextVisible(false);

    m_gridMenu = new QGridLayout;
    m_gridMenu->addWidget(m_buttonMenuClose, 0, 0, 0, 1);
    m_gridMenu->addWidget(m_buttonConnection, 1, 2, 1, 3);
    m_gridMenu->addWidget(m_buttonPower, 1, 4, 1, 5);
    m_gridMenu->addWidget(m_progressSound, 2, 0, 2, 5);
    m_gridMenu->addWidget(m_buttonDown, 3, 1, 3, 2);
    m_gridMenu->addWidget(m_buttonSound, 3, 2, 3, 3);
    m_gridMenu->addWidget(m_buttonUp, 3, 3, 3, 4);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));
}

MenuWindow::~MenuWindow()
{
    //delete menu_mainWindow;
}

void MenuWindow::changeVolumeBar(int volumeValue)
{
    m_progressSound->setValue(volumeValue);
}

void MenuWindow::muteVolumeBar(bool muted)
{
    if(muted)
    {
        m_progressSound->setValue(SOUND_MIN);
        m_buttonSound->setIcon(m_iconMute);
    }
    else
    {
        m_progressSound->setValue(menu_mainWindow->getVolumeValuePlayer());
        m_buttonSound->setIcon(m_iconNomute);
    }
}

void MenuWindow::buttonPlus(void)
{
    if(menu_mainWindow->getMutedPlayer())
    {
        menu_mainWindow->setMutePlayer(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if( menu_mainWindow->getVolumeValuePlayer() <= SOUND_MAX)
    {
        menu_mainWindow->setVolumePlayer((menu_mainWindow->getVolumeValuePlayer())+SOUND_MARGIN);
    }
}

void MenuWindow::buttonMinus(void)
{
    if(menu_mainWindow->getMutedPlayer())
    {
        menu_mainWindow->setMutePlayer(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if(menu_mainWindow->getVolumeValuePlayer() >= SOUND_MIN)
    {
        menu_mainWindow->setVolumePlayer((menu_mainWindow->getVolumeValuePlayer())-SOUND_MARGIN);
    }
}

void MenuWindow::buttonMute(void)
{
    if(!menu_mainWindow->getMutedPlayer())
    {
        m_buttonSound->setIcon(m_iconMute);
        menu_mainWindow->setMutePlayer(true);
    }
    else
    {
        m_buttonSound->setIcon(m_iconNomute);
        menu_mainWindow->setMutePlayer(false);
    }
}

void MenuWindow::buttonPower(void)
{
    menu_mainWindow->setMessagePowerOff();
}

void MenuWindow::openMenu()
{
    qDebug() << "openMenu";
    m_menuWindow->open();
}

void MenuWindow::setConnectionIcon(bool connectionStatus)
{
    if(connectionStatus)
        m_buttonConnection->setIcon(m_iconConnectionOn);
    else
        m_buttonConnection->setIcon(m_iconConnectionOff);
}

