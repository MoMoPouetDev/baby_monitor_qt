#include <QString>
#include <stdio.h>
#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow() : QWidget()
{
    setFixedSize(480, 320);

    m_buttonPower = new QPushButton("OFF", this);
    m_buttonPower -> move(380,10);
    m_buttonPower -> setFixedWidth(80);

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
    m_progressSound -> setValue(m_soundValue);
    m_progressSound -> setStyleSheet(m_style);
    m_progressSound -> setTextVisible(false);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));

    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_video = new QVideoWidget(this);

    m_player -> setMedia(QUrl::fromLocalFile("/Users/morganvenandy/test1.mp4"));
    m_player -> setVideoOutput(m_video);
    m_video -> setGeometry(10,10, 360, 280);
    m_player -> play();
}

MainWindow::~MainWindow()
{

}
void MainWindow::buttonPlus(void)
{
    if(m_soundValue <= SOUND_MAX)
    {
        m_soundValue += 10;
        m_progressSound->setValue(m_soundValue);
    }
}

void MainWindow::buttonMinus(void)
{

}

void MainWindow::buttonMute(void)
{

}

void MainWindow::buttonPower(void)
{

}
