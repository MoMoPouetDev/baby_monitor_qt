#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QProcess>
#include <QPushButton>
#include <QIcon>
#include <QSize>
#include <QMessageBox>
#include <QProcess>
#include <QProgressBar>

//#include "mainwindow.h"

#define PATH_ICON_MENU_CLOSE    "/home/morgan/git/baby_monitor_qt/images/menuClose.png"
#define PATH_ICON_CONNECTION_ON    "/home/morgan/git/baby_monitor_qt/images/connectionOn.png"
#define PATH_ICON_CONNECTION_OFF    "/home/morgan/git/baby_monitor_qt/images/connectionOff.png"
#define PATH_ICON_POWER_OFF "/home/morgan/git/baby_monitor_qt/images/powerOff.png"
#define PATH_ICON_MUTE "/home/morgan/git/baby_monitor_qt/images/soundMute.png"
#define PATH_ICON_NOMUTE "/home/morgan/git/baby_monitor_qt/images/soundNoMute.png"
#define PATH_ICON_SOUND_UP "/home/morgan/git/baby_monitor_qt/images/soundUp.png"
#define PATH_ICON_SOUND_DOWN "/home/morgan/git/baby_monitor_qt/images/soundDown.png"

#define SOUND_MAX       100
#define SOUND_MIN       0
#define SOUND_MARGIN    10
class MainWindow;
class MenuWindow : public QObject
{
    //Q_OBJECT

public:
    MenuWindow();
    ~MenuWindow();
    void setConnectionIcon(bool);
public slots:
    void buttonPlus(void);
    void buttonMinus(void);
    void buttonMute(void);
    void buttonPower(void);
    void changeVolumeBar(int);
    void muteVolumeBar(bool);
    void openMenu();

private:
    MainWindow *menu_mainWindow;

    QDialog *m_menuWindow;

    QGridLayout *m_gridMenu;

    QString m_style = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #4EE34E; height: 10px; margin: 0.5px;}",
            m_pathIconConnectionOn = PATH_ICON_CONNECTION_ON,
            m_pathIconConnectionOff = PATH_ICON_CONNECTION_OFF,
            m_pathIconPower = PATH_ICON_POWER_OFF,
            m_pathIconMute = PATH_ICON_MUTE,
            m_pathIconNomute = PATH_ICON_NOMUTE,
            m_pathIconSoundUp = PATH_ICON_SOUND_UP,
            m_pathIconSoundDown = PATH_ICON_SOUND_DOWN;

    QIcon m_menuIconClose,
            m_iconConnectionOn,
            m_iconConnectionOff,
            m_iconPower,
            m_iconMute,
            m_iconNomute,
            m_iconSoundUp,
            m_iconSoundDown;

    QPushButton *m_buttonMenuClose,
                *m_buttonConnection,
                *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound;

    QProgressBar *m_progressSound;
};

#endif // MENUWINDOW_H
