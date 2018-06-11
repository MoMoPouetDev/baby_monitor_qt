#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>

class MainWindow : public QWidget
{
    public:
    MainWindow();

    private:
    QPushButton *m_buttonPower,
                *m_buttonUp,
                *m_buttonDown,
                *m_buttonSound;

    QProgressBar *m_progressSound;
};

#endif // MAINWINDOW_H
