#include <QDebug>

#include "menuwindow.h"

MenuWindow::MenuWindow(MainWindow *parent) : QWidget()
{
    m_mainWindow = qobject_cast<MainWindow*>(parent);
    m_menuWindow = new QWidget(parent, Qt::FramelessWindowHint);
    m_menuWindow->setHidden(true);
    m_menuWindow->setStyleSheet(m_styleWidget);
    m_menuWindow->setFixedSize(100, 240);
    m_menuWindow->move(0,0);
    m_menuWindow->setObjectName("Menu");

    m_buttonMenuClose = new QPushButton(m_menuWindow);
    m_buttonMenuClose->setFlat(true);
    m_iconMenuClose.addFile(m_pathIconMenuClose);
    m_buttonMenuClose->setIcon(m_iconMenuClose);
    m_buttonMenuClose->setIconSize(QSize(30,30));
    m_buttonMenuClose->setGeometry(0, 0, 30, 30);

    m_buttonConnection = new QPushButton(m_menuWindow);
    m_buttonConnection->setFlat(true);
    m_iconConnectionOn.addFile(m_pathIconConnectionOn);
    m_iconConnectionOff.addFile(m_pathIconConnectionOff);
    m_buttonConnection->setIcon(m_iconConnectionOff);
    m_buttonConnection->setIconSize(QSize(20,20));
    m_buttonConnection->setGeometry(45, 5, 20, 20);
    m_buttonConnection->setEnabled(false);

    m_buttonPower = new QPushButton(m_menuWindow);
    m_buttonPower->setFlat(true);
    m_iconPower.addFile(m_pathIconPower);
    m_buttonPower->setIcon(m_iconPower);
    m_buttonPower->setIconSize(QSize(20,20));
    m_buttonPower->setGeometry(70, 5, 20, 20);

    m_buttonMusicLibrary = new QPushButton(m_menuWindow);
    m_buttonMusicLibrary->setFlat(true);
    m_iconMusicLibrary.addFile(m_pathIconMusicLibrary);
    m_buttonMusicLibrary->setIcon(m_iconMusicLibrary);
    m_buttonMusicLibrary->setIconSize(QSize(20,20));
    m_buttonMusicLibrary->setGeometry(60, 60, 20, 20);

    m_buttonUp = new QPushButton(m_menuWindow);
    m_buttonUp->setFlat(true);
    m_iconSoundUp.addFile(m_pathIconSoundUp);
    m_buttonUp->setIcon(m_iconSoundUp);
    m_buttonUp->setIconSize(QSize(20,20));
    m_buttonUp->setGeometry(60, 90, 20, 20);

    m_buttonSound = new QPushButton(m_menuWindow);
    m_buttonSound->setFlat(true);
    m_iconNomute.addFile(m_pathIconNomute);
    m_iconMute.addFile(m_pathIconMute);
    m_buttonSound->setIcon(m_iconNomute);
    m_buttonSound->setIconSize(QSize(20,20));
    m_buttonSound->setGeometry(60, 120, 20, 20);

    m_buttonDown = new QPushButton(m_menuWindow);
    m_buttonDown->setFlat(true);
    m_iconSoundDown.addFile(m_pathIconSoundDown);
    m_buttonDown->setIcon(m_iconSoundDown);
    m_buttonDown->setIconSize(QSize(20,20));
    m_buttonDown->setGeometry(60, 150, 20, 20);

    m_progressSound = new QProgressBar(m_menuWindow);
    m_progressSound->setGeometry(20, 40, 20, 160);
    m_progressSound->setOrientation(Qt::Vertical);
    m_progressSound->setValue(getVolumeValuePlayer());
    //m_progressSound->setValue(m_mainWindow->getVolumeValuePlayer());
    m_progressSound->setStyleSheet(m_style);
    m_progressSound->setTextVisible(false);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));
    QObject::connect(m_buttonMenuClose, SIGNAL(clicked()), this, SLOT(closeMenu()));
}

MenuWindow::~MenuWindow()
{
}

MenuWindow* MenuWindow::getThisMenuWindow()
{
    return this;
}

void MenuWindow::changeVolumeBar(int volumeValue)
{
    qDebug() << "change volume";
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
        m_progressSound->setValue(getVolumeValuePlayer());
        m_buttonSound->setIcon(m_iconNomute);
    }
}

void MenuWindow::buttonPlus(void)
{
    if(getMutedPlayer())
    {
        setMutedPlayer(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if( getVolumeValuePlayer() <= SOUND_MAX)
    {
        setVolumePlayer((getVolumeValuePlayer())+SOUND_MARGIN);
    }
}

void MenuWindow::buttonMinus(void)
{
    if(getMutedPlayer())
    {
        setMutedPlayer(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if(getVolumeValuePlayer() >= SOUND_MIN)
    {
        setVolumePlayer((getVolumeValuePlayer())-SOUND_MARGIN);
    }
}

void MenuWindow::buttonMute(void)
{
    if(!getMutedPlayer())
    {
        m_buttonSound->setIcon(m_iconMute);
        setMutedPlayer(true);
    }
    else
    {
        m_buttonSound->setIcon(m_iconNomute);
        setMutedPlayer(false);
    }
}

void MenuWindow::buttonPower(void)
{
    m_mainWindow->setMessagePowerOff();
}

void MenuWindow::openMenu()
{
    qDebug() << "openMenu";
    m_menuWindow->show();
}

void MenuWindow::closeMenu()
{
    m_menuWindow->hide();
}

void MenuWindow::setConnectionIcon(bool connectionStatus)
{
    if(connectionStatus)
        m_buttonConnection->setIcon(m_iconConnectionOn);
    else
        m_buttonConnection->setIcon(m_iconConnectionOff);
}

int MenuWindow::getVolumeValuePlayer()
{
    int volume;
    volume = m_mainWindow->getVolumeValuePlayer();
    return volume;
}

bool MenuWindow::getMutedPlayer()
{
    bool mute;
    mute = m_mainWindow->getMutedPlayer();
    return mute;
}

void MenuWindow::setMutedPlayer(bool mute)
{
    m_mainWindow->setMutePlayer(mute);
}

void MenuWindow::setVolumePlayer(int volume)
{
    m_mainWindow->setVolumePlayer(volume);
}
