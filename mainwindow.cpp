#include <QString>
#include <stdio.h>
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
    m_progressSound -> setFixedSize(30,160);
    m_progressSound -> move(405, 50);
    m_progressSound -> setOrientation(Qt::Vertical);
    m_progressSound -> setValue(50);
    m_progressSound -> setStyleSheet(m_style);
    m_progressSound -> setTextVisible(false);

    m_player = new QMediaPlayer(this);
    m_player -> setMedia(QUrl("/home/morganvenandy/test.mp4"));

    m_video = new QVideoWidget(this);
    m_player -> setVideoOutput(m_video);
    m_video -> move(10, 10);
    m_video -> setFixedSize(320, 280);
    printf("ok");
    if(m_player->isVideoAvailable()){
        m_player -> play();
    }
}
