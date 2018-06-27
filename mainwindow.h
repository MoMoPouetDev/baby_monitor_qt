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

#define PATH_ICON_MENU_OPEN    "/home/morgan/git/baby_monitor_qt/images/menuOpen.png"
#define PATH_VIDEO_URL  "/home/morgan/test1.mp4"

#define MIN_VALUE_LOW   20
#define MAX_VALUE_LOW   60
#define MIN_VALUE_MIDDLE    60
#define MAX_VALUE_MIDDLE    90
#define MIN_VALUE_HIGH  90
#define MAX_VALUE_HIGH  100

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
    MainWindow();
    ~MainWindow();
    void setShow();
    int getVolumeValuePlayer();
    bool getMutedPlayer();
    void setMutePlayer(bool);
    void setVolumePlayer(int);
    void setMessagePowerOff();
    QWidget *getWindow();

    public slots:
    void processBuffer(const QAudioBuffer&);
    void openMenu();
    void changeVolumeBar(int);
    void muteVolumeBar(bool);

    private:
    QWidget *menu;
    float previousValueRight = 0, previousValueLeft = 0;

    QString m_styleLow = "QProgressBar {border-top: 2px solid grey; border-left: 2px solid grey; border-bottom: 2px solid grey; border-top-left-radius: 5px; border-bottom-left-radius: 5px;} QProgressBar::chunk {background-color: green; width: 3px; margin: 0.5px;}",
            m_styleMiddle = "QProgressBar {border-top: 2px solid grey; border-bottom: 2px solid grey;} QProgressBar::chunk {background-color: orange; width: 3px; margin: 0.5px;}",
            m_styleHigh = "QProgressBar {border-top: 2px solid grey; border-right: 2px solid grey; border-bottom: 2px solid grey; border-top-right-radius: 5px; border-bottom-right-radius: 5px;} QProgressBar::chunk {background-color: red; width: 3px; margin: 0.5px;}",
            m_pathIconMenuOpen = PATH_ICON_MENU_OPEN,
            m_reboot = "/sbin/reboot";

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

    QString getReboot()
    {
        return m_reboot;
    }
};

#endif // MAINWINDOW_H
