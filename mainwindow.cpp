#include <stdio.h>
#include <QDebug>
#include <math.h>
#include <QEasingCurve>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

#include "mainwindow.h"

static qreal getPeakValue(const QAudioFormat &format);
static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

MainWindow::MainWindow(QWidget *parent) : QWidget()
{
    this->setFixedSize(800, 480);

    m_messagePowerOff = new QMessageBox(this);

    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_video = new QVideoWidget(this);
    //m_player->setMedia(QUrl::fromLocalFile(PATH_VIDEO_URL));
    QUrl url(PATH_URI);
    m_player->setMedia(QUrl("rtsp://192.168.1.13:80/live/picam"));
    m_player->setVideoOutput(m_video);
    m_video->setFixedSize(800, 480);
    m_player->play();
    m_player->setVolume(50);

    m_buttonMenuOpen = new QPushButton(this);
    m_iconMenuOpen.addFile(m_pathIconMenuOpen);
    m_buttonMenuOpen->setIcon(m_iconMenuOpen);
    m_buttonMenuOpen->setIconSize(QSize(36,36));
    m_buttonMenuOpen->setGeometry(0, 0, 36, 36);

    m_progressLow = new QProgressBar(this);
    m_progressLow->setGeometry(750, 200, 30, 240);
    m_progressLow->setOrientation(Qt::Vertical);
    m_progressLow->setMinimum(MIN_VALUE_LOW);
    m_progressLow->setMaximum(MAX_VALUE_LOW);
    m_progressLow->setValue(0);
    m_progressLow->setStyleSheet(m_styleLow);
    m_progressLow->setTextVisible(false);

    m_progressMiddle = new QProgressBar(this);
    m_progressMiddle->setGeometry(750, 80, 30, 120);
    m_progressMiddle->setOrientation(Qt::Vertical);
    m_progressMiddle->setMinimum(MIN_VALUE_MIDDLE);
    m_progressMiddle->setMaximum(MAX_VALUE_MIDDLE);
    m_progressMiddle->setValue(0);
    m_progressMiddle->setStyleSheet(m_styleMiddle);
    m_progressMiddle->setTextVisible(false);

    m_progressHigh = new QProgressBar(this);
    m_progressHigh->setGeometry(750, 40, 30, 40);
    m_progressHigh->setOrientation(Qt::Vertical);
    m_progressHigh->setMinimum(MIN_VALUE_HIGH);
    m_progressHigh->setMaximum(MAX_VALUE_HIGH);
    m_progressHigh->setValue(0);
    m_progressHigh->setStyleSheet(m_styleHigh);
    m_progressHigh->setTextVisible(false);

    QObject::connect(m_buttonMenuOpen, SIGNAL(clicked()), this, SLOT(openMenu()));
    QObject::connect(m_player, SIGNAL(volumeChanged(int)), this, SLOT(changeVolumeBar(int)));
    QObject::connect(m_player, SIGNAL(mutedChanged(bool)), this, SLOT(muteVolumeBar(bool)));
    QObject::connect(this, SIGNAL(isReadyMenu(MenuWindow*)), this, SLOT(getThisMenuWindow(MenuWindow*)));
    QObject::connect(this, SIGNAL(isReadyClient(ClientTcp*)), this, SLOT(getThisClient(ClientTcp*)));

    m_process = new QProcess(this);

    m_animationBarLow = new QPropertyAnimation(m_progressLow,"Low");
    m_animationBarMiddle = new QPropertyAnimation(m_progressMiddle,"Middle");
    m_animationBarHigh = new QPropertyAnimation(m_progressHigh,"High");

    m_probe = new QAudioProbe(this);
    QObject::connect(m_probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(const QAudioBuffer&)));
    m_probe->setSource(m_player);
}

MainWindow::~MainWindow()
{
    m_player->deleteLater();
    m_video->deleteLater();
    m_buttonMenuOpen->deleteLater();
    m_progressLow->deleteLater();
    m_progressMiddle->deleteLater();
    m_progressHigh->deleteLater();
    m_process->deleteLater();
    m_probe->deleteLater();
    m_animationBarHigh->deleteLater();
    m_animationBarMiddle->deleteLater();
    m_animationBarLow->deleteLater();
}

MainWindow* MainWindow::getThisMainWindow()
{
    return this;
}

void MainWindow::getThisMenuWindow(MenuWindow *menu)
{
    m_menuWindow = menu;
}

void MainWindow::getThisClient(ClientTcp *client)
{
    m_client = client;
}

void MainWindow::processBuffer(const QAudioBuffer& buffer)
{
    float decibel, decibelLow, decibelMiddle, decibelHigh;

    m_animationBarLow->setDuration(1000);
    m_animationBarLow->setEasingCurve(QEasingCurve::InQuad);

    m_animationBarMiddle->setDuration(1000);
    m_animationBarMiddle->setEasingCurve(QEasingCurve::InQuad);

    m_animationBarHigh->setDuration(1000);
    m_animationBarHigh->setEasingCurve(QEasingCurve::InQuad);

    QVector<qreal> levels = getBufferLevels(buffer);

    decibel = 100 + (20*log10(levels[0]));
    if(decibel <= MIN_VALUE_LOW)
    {
        decibelLow = MIN_VALUE_LOW;
        decibelMiddle = MIN_VALUE_MIDDLE;
        decibelHigh = MIN_VALUE_HIGH;
    }
    else if(decibel > MIN_VALUE_LOW && decibel < MAX_VALUE_LOW)
    {
        decibelLow = decibel;
        decibelMiddle = MIN_VALUE_MIDDLE;
        decibelHigh = MIN_VALUE_HIGH;
    }
    else if(decibel >= MIN_VALUE_MIDDLE && decibel < MAX_VALUE_MIDDLE)
    {
        decibelLow = MAX_VALUE_LOW;
        decibelMiddle = decibel;
        decibelHigh = MIN_VALUE_HIGH;
    }
    else if(decibel >= MIN_VALUE_HIGH && decibel <= MAX_VALUE_HIGH)
    {
        decibelLow = MAX_VALUE_LOW;
        decibelMiddle = MAX_VALUE_MIDDLE;
        decibelHigh = decibel;
    }
    else
    {
        decibelLow = MAX_VALUE_LOW;
        decibelMiddle = MAX_VALUE_MIDDLE;
        decibelHigh = MAX_VALUE_HIGH;
    }

    m_animationBarLow->setStartValue(previousValueRight);
    m_animationBarLow->setEndValue(decibel);
    m_animationBarLow->start();
    m_animationBarMiddle->setStartValue(previousValueRight);
    m_animationBarMiddle->setEndValue(decibel);
    m_animationBarMiddle->start();
    m_animationBarHigh->setStartValue(previousValueRight);
    m_animationBarHigh->setEndValue(decibel);
    m_animationBarHigh->start();
    m_progressLow->setValue(decibelLow);
    m_progressMiddle->setValue(decibelMiddle);
    m_progressHigh->setValue(decibelHigh);

    previousValueRight = decibel;
}

// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
    // Note: Only the most common sample formats are supported
    if (!format.isValid())
        return qreal(0);

    if (format.codec() != "audio/pcm")
        return qreal(0);

    switch (format.sampleType()) {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if (format.sampleSize() != 32) // other sample formats are not supported
            return qreal(0);
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if (format.sampleSize() == 32)
            return qreal(INT_MAX);
        if (format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
    case QAudioFormat::UnSignedInt:
        if (format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if (format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }

    return qreal(0);
}
QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
    QVector<qreal> values;

    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if (buffer.format().codec() != "audio/pcm")
        return values;

    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch (buffer.format().sampleType()) {
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        break;
    case QAudioFormat::Float:
        if (buffer.format().sampleSize() == 32) {
            values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
        }
        break;
    case QAudioFormat::SignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] /= peak_value;
        break;
    }

    return values;
}

template <class T>
QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }

    return max_values;
}

void MainWindow::setShow()
{
    this->showFullScreen();
}

int MainWindow::getVolumeValuePlayer()
{
    return m_player->volume();
}

bool MainWindow::getMutedPlayer()
{
    return m_player->isMuted();
}

void MainWindow::setMutePlayer(bool mute)
{
    m_player->setMuted(mute);
}

void MainWindow::setVolumePlayer(int volume)
{
    m_player->setVolume(volume);
}

void MainWindow::setMessagePowerOff()
{
    int ret=m_messagePowerOff->warning(this, "Power off", "Are you shure to ShutDown the Rasp ?", QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes)
    {
        //ShutDown
        m_client->sendData("PowerOff");
        m_process->startDetached(m_powerOff);
    }
}

void MainWindow::openMenu()
{
    m_menuWindow->openMenu();
}

void MainWindow::changeVolumeBar(int volume)
{
    m_menuWindow->changeVolumeBar(volume);
}

void MainWindow::muteVolumeBar(bool mute)
{
    m_menuWindow->muteVolumeBar(mute);
}
