#include <QDebug>

#include "menuwindow.h"

MenuWindow::MenuWindow() : QWidget()
{
    m_menuWindow = getWindow();
    m_menuWindow->setHidden(true);
    m_menuWindow->setStyleSheet(m_styleWidget);
    m_menuWindow->setFixedSize(100, 240);
    m_menuWindow->move(0,0);

    m_buttonConnection = new QPushButton(this);
    m_buttonConnection->setFlat(true);
    m_iconConnectionOn.addFile(m_pathIconConnectionOn);
    m_iconConnectionOff.addFile(m_pathIconConnectionOff);
    m_buttonConnection->setIcon(m_iconConnectionOff);
    m_buttonConnection->setIconSize(QSize(15,15));
    m_buttonConnection->setGeometry(465, 0, 15, 15);
    m_buttonConnection->setEnabled(true);

    m_buttonPower = new QPushButton(this);
    m_buttonPower->setFlat(true);
    m_iconPower.addFile(m_pathIconPower);
    m_buttonPower->setIcon(m_iconPower);
    m_buttonPower->setIconSize(QSize(30,30));
    //m_buttonPower->setGeometry(440, 10, 33, 33);

    m_buttonUp = new QPushButton(this);
    m_buttonUp->setFlat(true);
    m_iconSoundUp.addFile(m_pathIconSoundUp);
    m_buttonUp->setIcon(m_iconSoundUp);
    m_buttonUp->setIconSize(QSize(30,30));
    //m_buttonUp->setGeometry(440, 220, 33, 33);

    m_buttonSound = new QPushButton(this);
    m_buttonSound->setFlat(true);
    m_iconNomute.addFile(m_pathIconNomute);
    m_iconMute.addFile(m_pathIconMute);
    m_buttonSound->setIcon(m_iconNomute);
    m_buttonSound->setIconSize(QSize(30,30));
    //m_buttonSound->setGeometry(440, 250, 33, 33);

    m_buttonDown = new QPushButton(this);
    m_buttonDown->setFlat(true);
    m_iconSoundDown.addFile(m_pathIconSoundDown);
    m_buttonDown->setIcon(m_iconSoundDown);
    m_buttonDown->setIconSize(QSize(30,30));
    //m_buttonDown->setGeometry(440, 280, 33, 33);

    m_progressSound = new QProgressBar(this);
    //m_progressSound->setGeometry(440, 50, 33, 160);
    m_progressSound->setOrientation(Qt::Vertical);
    m_progressSound->setValue(getVolumeValuePlayer());
    //m_progressSound->setValue(m_mainWindow->getVolumeValuePlayer());
    m_progressSound->setStyleSheet(m_style);
    m_progressSound->setTextVisible(false);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));
}

MenuWindow::~MenuWindow()
{
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
    MainWindow *m_mainWindow = new MainWindow;
    m_mainWindow->setMessagePowerOff();
    m_mainWindow->deleteLater();
}

void MenuWindow::openMenu()
{
    qDebug() << "openMenu";
    m_menuWindow->show();
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
    MainWindow *m_mainWindow = new MainWindow;
    volume = m_mainWindow->getVolumeValuePlayer();
    m_mainWindow->deleteLater();
    return volume;
}

bool MenuWindow::getMutedPlayer()
{
    bool mute;
    MainWindow *m_mainWindow = new MainWindow;
    mute = m_mainWindow->getMutedPlayer();
    m_mainWindow->deleteLater();
    return mute;
}

void MenuWindow::setMutedPlayer(bool mute)
{
    MainWindow *m_mainWindow = new MainWindow;
    m_mainWindow->setMutePlayer(mute);
    m_mainWindow->deleteLater();
}

void MenuWindow::setVolumePlayer(int volume)
{
    MainWindow *m_mainWindow = new MainWindow;
    m_mainWindow->setVolumePlayer(volume);
    m_mainWindow->deleteLater();
}

QWidget* MenuWindow::getWindow()
{
    MainWindow *m_mainWindow = new MainWindow;
    QWidget *widget = m_mainWindow->getWindow();
    m_mainWindow->deleteLater();
    return widget;
}
