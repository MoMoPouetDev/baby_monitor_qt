#include <stdio.h>
#include <QSize>
#include "mainwindow.h"

MainWindow::MainWindow() : QWidget()
{
    this->setFixedSize(480, 320);

    m_buttonPower = new QPushButton(this);
    m_buttonPower->setFlat(true);
    m_iconPower.addFile(m_pathIconPower);
    m_buttonPower->setIcon(m_iconPower);
    m_buttonPower->setIconSize(QSize(30,30));
    m_buttonPower->setGeometry(412, 10, 33, 33);

    m_buttonUp = new QPushButton(this);
    m_buttonUp->setFlat(true);
    m_iconSoundUp.addFile(m_pathIconSoundUp);
    m_buttonUp->setIcon(m_iconSoundUp);
    m_buttonUp->setIconSize(QSize(30,30));
    m_buttonUp->setGeometry(412, 220, 33, 33);

    m_buttonSound = new QPushButton(this);
    m_buttonSound->setFlat(true);
    m_iconNomute.addFile(m_pathIconNomute);
    m_iconMute.addFile(m_pathIconMute);
    m_buttonSound->setIcon(m_iconNomute);
    m_buttonSound->setIconSize(QSize(30,30));
    m_buttonSound->setGeometry(412, 250, 33, 33);

    m_buttonDown = new QPushButton(this);
    m_buttonDown->setFlat(true);
    m_iconSoundDown.addFile(m_pathIconSoundDown);
    m_buttonDown->setIcon(m_iconSoundDown);
    m_buttonDown->setIconSize(QSize(30,30));
    m_buttonDown->setGeometry(412, 280, 33, 33);

    m_progressSound = new QProgressBar(this);
    m_progressSound->setGeometry(415, 50, 30, 160);
    m_progressSound->setOrientation(Qt::Vertical);
    m_progressSound->setValue(0);
    m_progressSound->setStyleSheet(getStyle());
    m_progressSound->setTextVisible(false);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));

    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    QObject::connect(m_player, SIGNAL(volumeChanged(int)), this, SLOT(changeVolumeBar(int)));
    QObject::connect(m_player, SIGNAL(mutedChanged(bool)), this, SLOT(muteVolumeBar(bool)));
    m_video = new QVideoWidget(this);

    m_player->setMedia(QUrl::fromLocalFile(VIDEO_URL));
    m_player->setVideoOutput(m_video);
    m_video->setGeometry(10,10, 360, 280);
    m_player->play();
    m_player->setVolume(50);

    m_process = new QProcess(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonPlus(void)
{
    if(m_player->isMuted())
    {
        m_player->setMuted(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if( m_player->volume() <= SOUND_MAX)
    {
        m_player->setVolume((m_player->volume())+SOUND_MARGIN);
    }
}

void MainWindow::buttonMinus(void)
{
    if(m_player->isMuted())
    {
        m_player->setMuted(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if(m_player->volume() >= SOUND_MIN)
    {
        m_player->setVolume((m_player->volume())-SOUND_MARGIN);
    }
}

void MainWindow::buttonMute(void)
{
    if(!m_player->isMuted())
    {
        m_buttonSound->setIcon(m_iconMute);
        m_player->setMuted(true);
    }
    else
    {
        m_buttonSound->setIcon(m_iconNomute);
        m_player->setMuted(false);
    }
}

void MainWindow::buttonPower(void)
{
    int ret=QMessageBox::warning(this, "Power off", "Are you shure to ShutDown the Rasp ?", QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes)
    {
        //ShutDown
        m_process->start(getReboot());
    }
}

void MainWindow::changeVolumeBar(int volumeValue)
{
    m_progressSound->setValue(volumeValue);
}

void MainWindow::muteVolumeBar(bool muted)
{
    if(muted)
    {
        m_progressSound->setValue(SOUND_MIN);
        m_buttonSound->setIcon(m_iconMute);
    }
    else
    {
        m_progressSound->setValue(m_player->volume());
        m_buttonSound->setIcon(m_iconNomute);
    }
}
