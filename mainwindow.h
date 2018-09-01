#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QSize>
#include <QProgressBar>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMessageBox>
#include <QProcess>
#include <QAudioBuffer>
#include <QVector>
#include <QPropertyAnimation>
#include <QAudioProbe>

#include "menuwindow.h"
#include "manager.h"

#define PATH_ICON_MENU_OPEN    "/home/pi/sourcesQt/pictures/menuOpen.png"
#define PATH_VIDEO_URL  "/home/pi/sourcesQt/video/test1.mp4"
#define PATH_URI    "rtsp://192.168.1.13:80/live/picam"

#define MIN_VALUE_LOW   20
#define MAX_VALUE_LOW   60
#define MIN_VALUE_MIDDLE    60
#define MAX_VALUE_MIDDLE    90
#define MIN_VALUE_HIGH  90
#define MAX_VALUE_HIGH  100

class Manager;
class MenuWindow;
class ClientTcp;
class MainWindow : public QWidget
{
    Q_OBJECT

    public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();
    MainWindow* getThisMainWindow();
    void setShow();
    int getVolumeValuePlayer();
    bool getMutedPlayer();
    void setMutePlayer(bool);
    void setVolumePlayer(int);
    void setMessagePowerOff();

    public slots:
    void processBuffer(const QAudioBuffer&);
    void openMenu();
    void changeVolumeBar(int);
    void muteVolumeBar(bool);
    void getThisMenuWindow(MenuWindow*);
    void getThisClient(ClientTcp*);

    signals:
    void isReadyMenu(MenuWindow*);
    void isReadyClient(ClientTcp*);

    private:
    Manager *m_manager;
    MenuWindow *m_menuWindow;
    ClientTcp *m_client;

    float previousValueRight = 0, previousValueLeft = 0;

    QString m_styleLow = "QProgressBar {border-right: 2px solid grey; border-left: 2px solid grey; border-bottom: 2px solid grey; border-bottom-right-radius: 5px; border-bottom-left-radius: 5px; background: transparente;} QProgressBar::chunk {background-color: #4EE34E; height: 3px; margin: 0.5px;}",
            m_styleMiddle = "QProgressBar {border-right: 2px solid grey; border-left: 2px solid grey; background: transparente;} QProgressBar::chunk {background-color: #FFC200; height: 3px; margin: 0.5px;}",
            m_styleHigh = "QProgressBar {border-top: 2px solid grey; border-right: 2px solid grey; border-left: 2px solid grey; border-top-right-radius: 5px; border-top-left-radius: 5px; background: transparente;} QProgressBar::chunk {background-color: red; height: 3px; margin: 0.5px;}",
            m_pathIconMenuOpen = PATH_ICON_MENU_OPEN,
            m_powerOff = "/sbin/shutdown now";

    QIcon m_iconMenuOpen;

    QPushButton *m_buttonMenuOpen;

    QProgressBar *m_progressLow,
                *m_progressMiddle,
                *m_progressHigh;

    QMediaPlayer *m_player;

    QVideoWidget *m_video;

    QMessageBox *m_messagePowerOff;

    QProcess *m_process;

    QPropertyAnimation *m_animationBarLow,
                        *m_animationBarMiddle,
                        *m_animationBarHigh;

    QAudioProbe *m_probe;
};

#endif // MAINWINDOW_H
