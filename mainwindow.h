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
    /*void buttonPlus(void);
    void buttonMinus(void);
    void buttonMute(void);
    void buttonPower(void);
    void changeVolumeBar(int);
    void muteVolumeBar(bool);*/
    void processBuffer(const QAudioBuffer&);

    private:
    float previousValueRight = 0, previousValueLeft = 0;
    QString //m_style = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #4EE34E; height: 10px; margin: 0.5px;}",
            m_styleLow = "QProgressBar {border-top: 2px solid grey; border-left: 2px solid grey; border-bottom: 2px solid grey; border-top-left-radius: 5px; border-bottom-left-radius: 5px;} QProgressBar::chunk {background-color: green; width: 3px; margin: 0.5px;}",
            m_styleMiddle = "QProgressBar {border-top: 2px solid grey; border-bottom: 2px solid grey;} QProgressBar::chunk {background-color: orange; width: 3px; margin: 0.5px;}",
            m_styleHigh = "QProgressBar {border-top: 2px solid grey; border-right: 2px solid grey; border-bottom: 2px solid grey; border-top-right-radius: 5px; border-bottom-right-radius: 5px;} QProgressBar::chunk {background-color: red; width: 3px; margin: 0.5px;}";
            /*m_reboot = "/sbin/reboot",
            m_pathIconConnectionOn = PATH_ICON_CONNECTION_ON,
            m_pathIconConnectionOff = PATH_ICON_CONNECTION_OFF,
            m_pathIconPower = PATH_ICON_POWER_OFF,
            m_pathIconMute = PATH_ICON_MUTE,
            m_pathIconNomute = PATH_ICON_NOMUTE,
            m_pathIconSoundUp = PATH_ICON_SOUND_UP,
            m_pathIconSoundDown = PATH_ICON_SOUND_DOWN;*/
    QIcon m_iconConnectionOn,
            m_iconConnectionOff,
            m_iconPower,
            m_iconMute,
            m_iconNomute,
            m_iconSoundUp,
            m_iconSoundDown;
    QPushButton *m_buttonConnection,
                *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound;
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
