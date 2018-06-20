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

#ifdef __APPLE__
    #define VIDEO_URL   "/Users/morganvenandy/test1.mp4"
    #define PATH_ICON_POWER_OFF "/Users/morganvenandy/baby_monitor_qt/images/powerOff.png"
    #define PATH_ICON_MUTE "/Users/morganvenandy/baby_monitor_qt/images/soundMute.png"
    #define PATH_ICON_NOMUTE "/Users/morganvenandy/baby_monitor_qt/images/soundNoMute.png"
    #define PATH_ICON_SOUND_UP "/Users/morganvenandy/baby_monitor_qt/images/soundUp.png"
    #define PATH_ICON_SOUND_DOWN "/Users/morganvenandy/baby_monitor_qt/images/soundDown.png"
#elif __linux__
    #define VIDEO_URL   "/home/morgan/test1.mp4"
#define PATH_ICON_POWER_OFF "/home/morgan/git/baby_monitor_qt/images/powerOff.png"
#define PATH_ICON_MUTE "/home/morgan/git/baby_monitor_qt/images/soundMute.png"
#define PATH_ICON_NOMUTE "/home/morgan/git/baby_monitor_qt/images/soundNoMute.png"
#define PATH_ICON_SOUND_UP "/home/morgan/git/baby_monitor_qt/images/soundUp.png"
#define PATH_ICON_SOUND_DOWN "/home/morgan/git/baby_monitor_qt/images/soundDown.png"
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
    void processBuffer(const QAudioBuffer&);

    private:
    float previousValueRight = 0, previousValueLeft = 0;
    QString m_style = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #4EE34E; height: 10px; margin: 0.5px;}",
            m_style2 = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: qlineargradient(x0: 0, x2: 1, stop: 0 green, stop: 0.6 green, stop: 0.8 orange, stop: 1 red)}",
            m_reboot = "reboot",
            m_pathIconPower = PATH_ICON_POWER_OFF,
            m_pathIconMute = PATH_ICON_MUTE,
            m_pathIconNomute = PATH_ICON_NOMUTE,
            m_pathIconSoundUp = PATH_ICON_SOUND_UP,
            m_pathIconSoundDown = PATH_ICON_SOUND_DOWN;
    QIcon m_iconPower,
            m_iconMute,
            m_iconNomute,
            m_iconSoundUp,
            m_iconSoundDown;
    QSize m_sizeIcon = QSize(50, 50);
    QPushButton *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound;
    QProgressBar *m_progressSound,
                *m_progressLeft,
                *m_progressRight;
    QMediaPlayer *m_player;
    QVideoWidget *m_video;
    QProcess *m_process;
    QPropertyAnimation *anim;

    QString getStyle()
    {
        return m_style;
    }
    QString getReboot()
    {
        return m_reboot;
    }


};

#endif // MAINWINDOW_H
