#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QMediaPlayer>
#include <QVideoWidget>

#define SOUND_MAX   100

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

    private:
    int m_soundValue = 50;
    QPushButton *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound;
    QString m_style = "QProgressBar {border: 2px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #CD96CD; height: 10px; margin: 0.5px;}";
    QProgressBar *m_progressSound;
    QMediaPlayer *m_player;
    QVideoWidget *m_video;
};

#endif // MAINWINDOW_H
