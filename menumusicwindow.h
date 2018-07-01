#ifndef MENUMUSIC_H
#define MENUMUSIC_H

#include <QWidget>
#include <QString>

#include "manager.h"

#define PATH_ICON_MUTE "/home/morgan/git/baby_monitor_qt/images/soundMute.png"
#define PATH_ICON_NOMUTE "/home/morgan/git/baby_monitor_qt/images/soundNoMute.png"
#define PATH_ICON_SOUND_UP "/home/morgan/git/baby_monitor_qt/images/soundUp.png"
#define PATH_ICON_SOUND_DOWN "/home/morgan/git/baby_monitor_qt/images/soundDown.png"

class MainWindow;
class MenuWindow;
class MenuMusicWindow : public QWidget
{
    Q_OBJECT

public:
    MenuMusicWindow(MainWindow* parent);
    ~MenuMusicWindow();
    MenuMusicWindow* getThisMenuMusicWindow();
    void openMenu();
    void closeMenu();

public slots:
    void index(QModelIndex);

private:
    QWidget* m_menuMusicWindow;
    MainWindow* m_mainWindow;

    QGroupBox *m_groupMusic;

    QString m_style = "QWidget#Library {border: 2px solid grey; border-radius: 5px; background-color : white}",
            m_styleProgress = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #30BCC6; width: 10px; margin: 0.5px;}",
            m_styleWidget = "QWidget {border: 2px solid grey; border-radius: 5px; background-color : white}",
            m_pathIconMute = PATH_ICON_MUTE,
            m_pathIconNomute = PATH_ICON_NOMUTE,
            m_pathIconSoundUp = PATH_ICON_SOUND_UP,
            m_pathIconSoundDown = PATH_ICON_SOUND_DOWN;

    QIcon m_iconMute,
        m_iconNomute,
        m_iconSoundUp,
        m_iconSoundDown;

    QPushButton *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound;

    QProgressBar *m_progressSound;

};


#endif // MENUMUSIC_H
