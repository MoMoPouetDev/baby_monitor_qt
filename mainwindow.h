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

#ifdef __APPLE__
    #define VIDEO_URL   "/Users/morganvenandy/test1.mp4"
#elif __linux__
    #define VIDEO_URL   "/home/morgan/test.mp4"
    #define PATH_ICON_POWER "/home/morgan/git/baby_monitor_qt/images/power.png"
#endif

#define SOUND_MAX       100
#define SOUND_MIN       0
#define SOUND_MARGIN    10

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
    MainWindow();
    ~MainWindow();

    public slots:
    void buttonPlus(void);
    void buttonMinus(void);
    void buttonMute(void);
    void buttonPower(void);
    void changeVolumeBar(int);
    void muteVolumeBar(bool);

    private:
    QString m_style = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #4EE34E; height: 10px; margin: 0.5px;}";
    QString m_pathIconPower = PATH_ICON_POWER;
    QIcon m_iconPower;
    QSize m_sizeIcon = QSize(50, 50);
    QPushButton *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound;
    QProgressBar *m_progressSound;
    QMediaPlayer *m_player;
    QVideoWidget *m_video;

    QString getStyle()
    {
        return m_style;
    }

};

#endif // MAINWINDOW_H
