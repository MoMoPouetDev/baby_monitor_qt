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

MainWindow::MainWindow() : QWidget()
{
    this->setFixedSize(480, 320);

    m_messagePowerOff = new QMessageBox(this);

    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_video = new QVideoWidget(this);
    m_player->setMedia(QUrl::fromLocalFile(VIDEO_URL));
    m_player->setVideoOutput(m_video);
    m_video->setGeometry(10, 13, 380, 214);
    m_player->play();
    m_player->setVolume(50);

    m_buttonConnection = new QPushButton(this);
    m_buttonConnection->setFlat(true);
    m_iconConnectionOn.addFile(m_pathIconConnectionOn);
    m_iconConnectionOff.addFile(m_pathIconConnectionOff);
    m_buttonConnection->setIcon(m_iconConnectionOff);
    m_buttonConnection->setIconSize(QSize(15,15));
    m_buttonConnection->setGeometry(465, 0, 15, 15);
    m_buttonConnection->setEnabled(true);

    QDialog *secondeFenetre = new QDialog(this);
    //secondeFenetre->setWindowModality(Qt::NonModal);
    QPushButton *test = new QPushButton("buttonTest", secondeFenetre);



        QObject::connect(m_buttonConnection, SIGNAL(clicked()), secondeFenetre, SLOT(open()));
        //secondeFenetre->show();

    m_buttonPower = new QPushButton(this);
    m_buttonPower->setFlat(true);
    m_iconPower.addFile(m_pathIconPower);
    m_buttonPower->setIcon(m_iconPower);
    m_buttonPower->setIconSize(QSize(30,30));
    m_buttonPower->setGeometry(440, 10, 33, 33);

    m_buttonUp = new QPushButton(this);
    m_buttonUp->setFlat(true);
    m_iconSoundUp.addFile(m_pathIconSoundUp);
    m_buttonUp->setIcon(m_iconSoundUp);
    m_buttonUp->setIconSize(QSize(30,30));
    m_buttonUp->setGeometry(440, 220, 33, 33);

    m_buttonSound = new QPushButton(this);
    m_buttonSound->setFlat(true);
    m_iconNomute.addFile(m_pathIconNomute);
    m_iconMute.addFile(m_pathIconMute);
    m_buttonSound->setIcon(m_iconNomute);
    m_buttonSound->setIconSize(QSize(30,30));
    m_buttonSound->setGeometry(440, 250, 33, 33);

    m_buttonDown = new QPushButton(this);
    m_buttonDown->setFlat(true);
    m_iconSoundDown.addFile(m_pathIconSoundDown);
    m_buttonDown->setIcon(m_iconSoundDown);
    m_buttonDown->setIconSize(QSize(30,30));
    m_buttonDown->setGeometry(440, 280, 33, 33);

    m_progressSound = new QProgressBar(this);
    m_progressSound->setGeometry(440, 50, 33, 160);
    m_progressSound->setOrientation(Qt::Vertical);
    m_progressSound->setValue(m_player->volume());
    m_progressSound->setStyleSheet(getStyle());
    m_progressSound->setTextVisible(false);

    m_progressLow = new QProgressBar(this);
    m_progressLow->setGeometry(10, 270, 240, 30);
    m_progressLow->setMinimum(MIN_VALUE_LOW);
    m_progressLow->setMaximum(MAX_VALUE_LOW);
    m_progressLow->setValue(0);
    m_progressLow->setStyleSheet(m_styleLow);
    m_progressLow->setTextVisible(false);

    m_progressMiddle = new QProgressBar(this);
    m_progressMiddle->setGeometry(247, 270, 120, 30);
    m_progressMiddle->setMinimum(MIN_VALUE_MIDDLE);
    m_progressMiddle->setMaximum(MAX_VALUE_MIDDLE);
    m_progressMiddle->setValue(0);
    m_progressMiddle->setStyleSheet(m_styleMiddle);
    m_progressMiddle->setTextVisible(false);

    m_progressHigh = new QProgressBar(this);
    m_progressHigh->setGeometry(364, 270, 40, 30);
    m_progressHigh->setMinimum(MIN_VALUE_HIGH);
    m_progressHigh->setMaximum(MAX_VALUE_HIGH);
    m_progressHigh->setValue(0);
    m_progressHigh->setStyleSheet(m_styleHigh);
    m_progressHigh->setTextVisible(false);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));

    QObject::connect(m_player, SIGNAL(volumeChanged(int)), this, SLOT(changeVolumeBar(int)));
    QObject::connect(m_player, SIGNAL(mutedChanged(bool)), this, SLOT(muteVolumeBar(bool)));

    m_process = new QProcess(this);

    m_probe = new QAudioProbe(this);
    QObject::connect(m_probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(const QAudioBuffer&)));
    m_probe->setSource(m_player);

    m_animationBarLow = new QPropertyAnimation(m_progressLow,"Low");
    m_animationBarLow->setDuration(1000);
    m_animationBarLow->setStartValue(0);
    m_animationBarLow->setEndValue(100);
    m_animationBarLow->setEasingCurve(QEasingCurve::InQuad);
    m_animationBarLow->start();

    m_animationBarMiddle = new QPropertyAnimation(m_progressMiddle,"Middle");
    m_animationBarMiddle->setDuration(1000);
    m_animationBarMiddle->setStartValue(0);
    m_animationBarMiddle->setEndValue(100);
    m_animationBarMiddle->setEasingCurve(QEasingCurve::InQuad);
    m_animationBarMiddle->start();

    m_animationBarHigh = new QPropertyAnimation(m_progressHigh,"High");
    m_animationBarHigh->setDuration(1000);
    m_animationBarHigh->setStartValue(0);
    m_animationBarHigh->setEndValue(100);
    m_animationBarHigh->setEasingCurve(QEasingCurve::InQuad);
    m_animationBarHigh->start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonPlus(void)
{
    if(m_player->isMuted())
    {
        m_player->setMuted(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if( m_player->volume() <= SOUND_MAX)
    {
        m_player->setVolume((m_player->volume())+SOUND_MARGIN);
    }
}

void MainWindow::buttonMinus(void)
{
    if(m_player->isMuted())
    {
        m_player->setMuted(false);
        m_buttonSound->setIcon(m_iconNomute);
    }
    if(m_player->volume() >= SOUND_MIN)
    {
        m_player->setVolume((m_player->volume())-SOUND_MARGIN);
    }
}

void MainWindow::buttonMute(void)
{
    if(!m_player->isMuted())
    {
        m_buttonSound->setIcon(m_iconMute);
        m_player->setMuted(true);
    }
    else
    {
        m_buttonSound->setIcon(m_iconNomute);
        m_player->setMuted(false);
    }
}

void MainWindow::buttonPower(void)
{
    int ret=m_messagePowerOff->warning(this, "Power off", "Are you shure to ShutDown the Rasp ?", QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes)
    {
        //ShutDown
        m_process->startDetached(getReboot());
    }
}

void MainWindow::changeVolumeBar(int volumeValue)
{
    m_progressSound->setValue(volumeValue);
}

void MainWindow::muteVolumeBar(bool muted)
{
    if(muted)
    {
        m_progressSound->setValue(SOUND_MIN);
        m_buttonSound->setIcon(m_iconMute);
        qDebug()<<m_player->isAudioAvailable();
    }
    else
    {
        m_progressSound->setValue(m_player->volume());
        m_buttonSound->setIcon(m_iconNomute);
    }
}

void MainWindow::processBuffer(const QAudioBuffer& buffer)
{
    float decibel, decibelLow, decibelMiddle, decibelHigh;

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
    this->show();
}

void MainWindow::setConnectionIcon(bool connectionStatus)
{
    if(connectionStatus)
        m_buttonConnection->setIcon(m_iconConnectionOn);
    else
        m_buttonConnection->setIcon(m_iconConnectionOff);
}

