#include <QDebug>
#include <QListView>
#include <QStringListModel>
#include <QModelIndex>
#include <QDir>

#include "menumusicwindow.h"

MenuMusicWindow::MenuMusicWindow(MainWindow *parent) : QWidget()
{
    m_mainWindow = qobject_cast<MainWindow*>(parent);
    m_menuMusicWindow = new QWidget(parent, Qt::FramelessWindowHint);
    m_menuMusicWindow->setHidden(true);
    m_menuMusicWindow->setStyleSheet(m_style);
    m_menuMusicWindow->setFixedSize(150, 240);
    m_menuMusicWindow->move(0,240);
    m_menuMusicWindow->setObjectName("Library");

    m_groupMusic = new QGroupBox("Server", m_menuMusicWindow);
    m_groupMusic->setGeometry(5, 5, 140, 230);

    m_buttonUp = new QPushButton(m_menuMusicWindow);
    m_buttonUp->setFlat(true);
    m_iconSoundUp.addFile(m_pathIconSoundUp);
    m_buttonUp->setIcon(m_iconSoundUp);
    m_buttonUp->setIconSize(QSize(20,20));
    m_buttonUp->setGeometry(95, 65, 20, 20);

    m_buttonSound = new QPushButton(m_menuMusicWindow);
    m_buttonSound->setFlat(true);
    m_iconNomute.addFile(m_pathIconNomute);
    m_iconMute.addFile(m_pathIconMute);
    m_buttonSound->setIcon(m_iconNomute);
    m_buttonSound->setIconSize(QSize(20,20));
    m_buttonSound->setGeometry(65, 65, 20, 20);

    m_buttonDown = new QPushButton(m_menuMusicWindow);
    m_buttonDown->setFlat(true);
    m_iconSoundDown.addFile(m_pathIconSoundDown);
    m_buttonDown->setIcon(m_iconSoundDown);
    m_buttonDown->setIconSize(QSize(20,20));
    m_buttonDown->setGeometry(35, 65, 20, 20);

    m_progressSound = new QProgressBar(m_menuMusicWindow);
    m_progressSound->setGeometry(10, 35, 130, 20);
    //m_progressSound->setOrientation(Qt::Vertical);
    m_progressSound->setValue(100);
    m_progressSound->setStyleSheet(m_styleProgress);
    m_progressSound->setTextVisible(false);

    /************* TEST LIST VIEW *******/
    QStringListModel *mode = new QStringListModel(m_menuMusicWindow);
    QStringList liste(QDir("/home/morgan/git/baby_monitor_qt/images/").entryList());
    QStringList list = liste.filter(".png");
    /*list << "test"
            << "test1";*/
    QString lstring = list.join(";");
    qDebug() << lstring;
    mode->setStringList(list);

    QListView *m_List = new QListView(m_menuMusicWindow);
    m_List->setSelectionRectVisible(true);
    m_List->setGeometry(10, 95, 130, 135);
    m_List->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_List->setModel(mode);

    QObject::connect(m_List, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(index(QModelIndex)));

    /***************************************************/
}

MenuMusicWindow::~MenuMusicWindow()
{
}

MenuMusicWindow* MenuMusicWindow::getThisMenuMusicWindow()
{
    return this;
}

void MenuMusicWindow::openMenu()
{
    m_menuMusicWindow->show();
}

void MenuMusicWindow::closeMenu()
{
    m_menuMusicWindow->hide();
}

void MenuMusicWindow::index(QModelIndex index)
{
    qDebug() << index.row();
}
