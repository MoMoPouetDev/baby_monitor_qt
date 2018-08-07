#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QProgressBar>
#include <QGroupBox>

#include "manager.h"

#define PATH_ICON_MUSIC_LIBRARY "/home/pi/sourcesQt/pictures/musicLibrary.png"
#define PATH_ICON_MENU_CLOSE    "/home/pi/sourcesQt/pictures/menuClose.png"
#define PATH_ICON_CONNECTION_ON    "/home/pi/sourcesQt/pictures/connectionOn.png"
#define PATH_ICON_CONNECTION_OFF    "/home/pi/sourcesQt/pictures/connectionOff.png"
#define PATH_ICON_POWER_OFF "/home/pi/sourcesQt/pictures/powerOff.png"
#define PATH_ICON_MUTE "/home/pi/sourcesQt/pictures/soundMute.png"
#define PATH_ICON_NOMUTE "/home/pi/sourcesQt/pictures/soundNoMute.png"
#define PATH_ICON_SOUND_UP "/home/pi/sourcesQt/pictures/soundUp.png"
#define PATH_ICON_SOUND_DOWN "/home/pi/sourcesQt/pictures/soundDown.png"

#define SOUND_MAX       100
#define SOUND_MIN       0
#define SOUND_MARGIN    10

class MainWindow;
class MenuMusicWindow;
class Manager;
class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    MenuWindow(MainWindow* parent);
    ~MenuWindow();
    MenuWindow* getThisMenuWindow();
    void setConnectionIcon(bool);
    int getVolumeValuePlayer();
    bool getMutedPlayer();
    void setMutedPlayer(bool);
    void setVolumePlayer(int);
    void openMenu();

public slots:
    void buttonPlus(void);
    void buttonMinus(void);
    void buttonMute(void);
    void buttonPower(void);
    void buttonLibrary(void);
    void closeMenu(void);
    void changeVolumeBar(int);
    void muteVolumeBar(bool);
    void getThisMenuMusicWindow(MenuMusicWindow*);

signals:
    void isReadyMusic(MenuMusicWindow*);

private:
    bool isLibraryOpen = false;
    QWidget *m_menuWindow;
    MainWindow *m_mainWindow;
    MenuMusicWindow *m_menuMusicWindow;

    QGroupBox *m_groupPlayer;

    QString m_style = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #4EE34E; height: 10px; margin: 0.5px;}",
            m_styleWidget = "QWidget#Menu {border: 2px solid grey; border-radius: 5px; background-color : white}",
            m_pathIconConnectionOn = PATH_ICON_CONNECTION_ON,
            m_pathIconConnectionOff = PATH_ICON_CONNECTION_OFF,
            m_pathIconPower = PATH_ICON_POWER_OFF,
            m_pathIconMute = PATH_ICON_MUTE,
            m_pathIconNomute = PATH_ICON_NOMUTE,
            m_pathIconSoundUp = PATH_ICON_SOUND_UP,
            m_pathIconSoundDown = PATH_ICON_SOUND_DOWN,
            m_pathIconMenuClose = PATH_ICON_MENU_CLOSE,
            m_pathIconMusicLibrary = PATH_ICON_MUSIC_LIBRARY;

    QIcon m_iconMenuClose,
        m_iconConnectionOn,
        m_iconConnectionOff,
        m_iconPower,
        m_iconMute,
        m_iconNomute,
        m_iconSoundUp,
        m_iconSoundDown,
        m_iconMusicLibrary;

    QPushButton *m_buttonMenuClose,
                *m_buttonConnection,
                *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound,
                *m_buttonMusicLibrary;

    QProgressBar *m_progressSound;
};

#endif // MENUWINDOW_H
