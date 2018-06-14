#include <stdio.h>
#include <QIcon>
#include <QSize>
#include <QString>
#include "mainwindow.h"

MainWindow::MainWindow() : QWidget()
{
    setFixedSize(480, 320);

    m_buttonPower = new QPushButton(this);
    m_iconPower.addFile(m_pathIconPower);
    m_buttonPower->setIcon(m_iconPower);
    m_buttonPower->setGeometry(420, 10, 50, 30);

    m_buttonUp = new QPushButton("+", this);
    m_buttonUp -> move(380, 230);
    m_buttonUp -> setFixedWidth(80);

    m_buttonSound = new QPushButton("Mute", this);
    m_buttonSound -> move(380, 255);
    m_buttonSound -> setFixedWidth(80);

    m_buttonDown = new QPushButton("-", this);
    m_buttonDown -> move(380, 280);
    m_buttonDown -> setFixedWidth(80);

    m_progressSound = new QProgressBar(this);
    m_progressSound -> setGeometry(405, 50, 30, 160);
    m_progressSound -> setOrientation(Qt::Vertical);
    m_progressSound -> setValue(0);
    m_progressSound -> setStyleSheet(getStyle());
    m_progressSound -> setTextVisible(true);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));

    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    QObject::connect(m_player, SIGNAL(volumeChanged(int)), this, SLOT(changeVolumeBar(int)));
    QObject::connect(m_player, SIGNAL(mutedChanged(bool)), this, SLOT(muteVolumeBar(bool)));
    m_video = new QVideoWidget(this);

    m_player -> setMedia(QUrl("rtsp://root:bni@192.168.0.90/axis-media/media.amp?camera=1"));
    m_player -> setVideoOutput(m_video);
    m_video -> setGeometry(10,10, 360, 280);
    m_player -> play();

    m_player->setVolume(50);
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonPlus(void)
{
    if(m_player->isMuted())
    {
        m_player->setMuted(false);
        m_buttonSound->setText("Mute");
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
        m_buttonSound->setText("Mute");
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
        m_player->setMuted(true);
        m_buttonSound->setText("Unmute");
    }
    else
    {
        m_player->setMuted(false);
        m_buttonSound->setText("Mute");
    }
}

void MainWindow::buttonPower(void)
{

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
    }
    else
    {
        m_progressSound->setValue(m_player->volume());
    }
}
