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
#include <QDialog>
#include <QGridLayout>
#include <QFileDialog>

#ifdef __APPLE__
    #define VIDEO_URL   "/Users/morganvenandy/test1.mp4"
    #define PATH_ICON_POWER_OFF "/Users/morganvenandy/baby_monitor_qt/images/powerOff.png"
    #define PATH_ICON_MUTE "/Users/morganvenandy/baby_monitor_qt/images/soundMute.png"
    #define PATH_ICON_NOMUTE "/Users/morganvenandy/baby_monitor_qt/images/soundNoMute.png"
    #define PATH_ICON_SOUND_UP "/Users/morganvenandy/baby_monitor_qt/images/soundUp.png"
    #define PATH_ICON_SOUND_DOWN "/Users/morganvenandy/baby_monitor_qt/images/soundDown.png"
#elif __linux__
    #define VIDEO_URL   "/home/morgan/test1.mp4"
#define PATH_ICON_MUSIC_LIBRARY "/home/morgan/git/baby_monitor_qt/images/musicLibrary.png"
#define PATH_ICON_MENU_OPEN "/home/morgan/git/baby_monitor_qt/images/menuOpen.png"
#define PATH_ICON_MENU_CLOSE "/home/morgan/git/baby_monitor_qt/images/menuClose.png"
#define PATH_ICON_CONNECTION_ON    "/home/morgan/git/baby_monitor_qt/images/connectionOn.png"
#define PATH_ICON_CONNECTION_OFF    "/home/morgan/git/baby_monitor_qt/images/connectionOff.png"
#define PATH_ICON_POWER_OFF "/home/morgan/git/baby_monitor_qt/images/powerOff.png"
#define PATH_ICON_MUTE "/home/morgan/git/baby_monitor_qt/images/soundMute.png"
#define PATH_ICON_NOMUTE "/home/morgan/git/baby_monitor_qt/images/soundNoMute.png"
#define PATH_ICON_SOUND_UP "/home/morgan/git/baby_monitor_qt/images/soundUp.png"
#define PATH_ICON_SOUND_DOWN "/home/morgan/git/baby_monitor_qt/images/soundDown.png"
#endif

#define SOUND_MAX       100
#define SOUND_MIN       0
#define SOUND_MARGIN    10

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
    void setConnectionIcon(bool);

    public slots:
    void buttonPlus(void);
    void buttonMinus(void);
    void buttonMute(void);
    void buttonPower(void);
    void changeVolumeBar(int);
    void muteVolumeBar(bool);
    void processBuffer(const QAudioBuffer&);
    void open();
    void close();
    void selectMusic();

    private:
    float previousValueRight = 0, previousValueLeft = 0;

    QString m_style = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #4EE34E; height: 5px; margin: 0.5px;}",
            m_styleWidget = "QWidget {background-color : white}",
            m_styleLow = "QProgressBar {border-right: 2px solid grey; border-left: 2px solid grey; border-bottom: 2px solid grey; border-bottom-right-radius: 5px; border-bottom-left-radius: 5px; background: transparente;} QProgressBar::chunk {background-color: #4EE34E; height: 3px; margin: 0.5px;}",
            m_styleMiddle = "QProgressBar {border-right: 2px solid grey; border-left: 2px solid grey; background: transparente;} QProgressBar::chunk {background-color: #FFC200; height: 3px; margin: 0.5px;}",
            m_styleHigh = "QProgressBar {border-top: 2px solid grey; border-right: 2px solid grey; border-left: 2px solid grey; border-top-right-radius: 5px; border-top-left-radius: 5px; background: transparente;} QProgressBar::chunk {background-color: red; height: 3px; margin: 0.5px;}",
            m_reboot = "/sbin/reboot",
            m_pathIconConnectionOn = PATH_ICON_CONNECTION_ON,
            m_pathIconConnectionOff = PATH_ICON_CONNECTION_OFF,
            m_pathIconPower = PATH_ICON_POWER_OFF,
            m_pathIconMute = PATH_ICON_MUTE,
            m_pathIconNomute = PATH_ICON_NOMUTE,
            m_pathIconSoundUp = PATH_ICON_SOUND_UP,
            m_pathIconSoundDown = PATH_ICON_SOUND_DOWN,
            m_pathIconMenuOpen = PATH_ICON_MENU_OPEN,
            m_pathIconMenuClose = PATH_ICON_MENU_CLOSE,
            m_pathIconMusicLibrary = PATH_ICON_MUSIC_LIBRARY;

    QIcon m_iconConnectionOn,
            m_iconConnectionOff,
            m_iconPower,
            m_iconMute,
            m_iconNomute,
            m_iconSoundUp,
            m_iconSoundDown,
            m_iconMenuOpen,
            m_iconMenuClose,
            m_iconMusicLibrary;

    QPushButton *m_buttonConnection,
                *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound,
                *m_buttonMenuOpen,
                *m_buttonMenuClose,
                *m_buttonMusicLibrary;

    QProgressBar *m_progressSound,
                *m_progressLow,
                *m_progressMiddle,
                *m_progressHigh;

    QMediaPlayer *m_player;

    QVideoWidget *m_video;

    QMessageBox *m_messagePowerOff,
                *m_messageConnection;

    QProcess *m_process;

    QPropertyAnimation *m_animationBarLow,
                        *m_animationBarMiddle,
                        *m_animationBarHigh;

    QAudioProbe *m_probe;

    QWidget *m_menuWindow;

    QGridLayout *m_gridMenu;

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
