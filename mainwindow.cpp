#include <stdio.h>
#include <QSize>
#include <QDebug>
#include <QAudioProbe>
#include <math.h>

#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QThread>

#include "mainwindow.h"


static qreal getPeakValue(const QAudioFormat &format);
static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

MainWindow::MainWindow() : QWidget()
{
    this->setFixedSize(480, 320);

    m_buttonPower = new QPushButton(this);
    m_buttonPower->setFlat(true);
    m_iconPower.addFile(m_pathIconPower);
    m_buttonPower->setIcon(m_iconPower);
    m_buttonPower->setIconSize(QSize(30,30));
    m_buttonPower->setGeometry(412, 10, 33, 33);

    m_buttonUp = new QPushButton(this);
    m_buttonUp->setFlat(true);
    m_iconSoundUp.addFile(m_pathIconSoundUp);
    m_buttonUp->setIcon(m_iconSoundUp);
    m_buttonUp->setIconSize(QSize(30,30));
    m_buttonUp->setGeometry(412, 220, 33, 33);

    m_buttonSound = new QPushButton(this);
    m_buttonSound->setFlat(true);
    m_iconNomute.addFile(m_pathIconNomute);
    m_iconMute.addFile(m_pathIconMute);
    m_buttonSound->setIcon(m_iconNomute);
    m_buttonSound->setIconSize(QSize(30,30));
    m_buttonSound->setGeometry(412, 250, 33, 33);

    m_buttonDown = new QPushButton(this);
    m_buttonDown->setFlat(true);
    m_iconSoundDown.addFile(m_pathIconSoundDown);
    m_buttonDown->setIcon(m_iconSoundDown);
    m_buttonDown->setIconSize(QSize(30,30));
    m_buttonDown->setGeometry(412, 280, 33, 33);

    m_progressSound = new QProgressBar(this);
    m_progressSound->setGeometry(415, 50, 30, 160);
    m_progressSound->setOrientation(Qt::Vertical);
    m_progressSound->setValue(0);
    m_progressSound->setStyleSheet(getStyle());
    m_progressSound->setTextVisible(false);

    /*m_progressLeft = new QProgressBar(this);
    m_progressLeft->setGeometry(10, 200, 200, 20);
    m_progressLeft->setMinimum(20);
    m_progressLeft->setMaximum(100);
    m_progressLeft->setValue(0);*/

    m_progressRight = new QProgressBar(this);
    m_progressRight->setGeometry(10, 250, 200, 20);
    m_progressRight->setMinimum(20);
    m_progressRight->setMaximum(100);
    m_progressRight->setValue(0);
    m_progressRight->setStyleSheet(m_style2);

    QObject::connect(m_buttonUp, SIGNAL(clicked()), this, SLOT(buttonPlus()));
    QObject::connect(m_buttonDown, SIGNAL(clicked()), this, SLOT(buttonMinus()));
    QObject::connect(m_buttonSound, SIGNAL(clicked()), this, SLOT(buttonMute()));
    QObject::connect(m_buttonPower, SIGNAL(clicked()), this, SLOT(buttonPower()));

    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    QObject::connect(m_player, SIGNAL(volumeChanged(int)), this, SLOT(changeVolumeBar(int)));
    QObject::connect(m_player, SIGNAL(mutedChanged(bool)), this, SLOT(muteVolumeBar(bool)));
    m_video = new QVideoWidget(this);

    m_player->setMedia(QUrl::fromLocalFile(VIDEO_URL));
    m_player->setVideoOutput(m_video);
    m_video->setGeometry(10,10, 260, 180);
    m_player->play();
    m_player->setVolume(100);

    m_process = new QProcess(this);

    QAudioProbe *probe = new QAudioProbe(this);
    QObject::connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(const QAudioBuffer&)));
    probe->setSource(m_player);

    anim = new QPropertyAnimation(m_progressRight,"value");
    anim->setDuration(1000);
    anim->setStartValue(0);
    anim->setEndValue(100);
    anim->setEasingCurve(QEasingCurve::InQuart);
    anim->start();
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
    int ret=QMessageBox::warning(this, "Power off", "Are you shure to ShutDown the Rasp ?", QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes)
    {
        //ShutDown
        m_process->start(getReboot());
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
    float decibelRight, decibelLeft;
    qDebug() << buffer.byteCount();
    qDebug() << sizeof(buffer);
    qDebug() << buffer.frameCount();
    qDebug() << buffer.sampleCount();

    /*QAudioBuffer::S8U *frames = buffer.data<QAudioBuffer::S8U>();
    for (int i=0; i < buffer.frameCount(); i++)
    {
        //qDebug() << frames[i].right << "right" << endl;
        //qDebug() << frames[i].left<< "left" << endl;

        levelRight += frames[i].right;
        //decibel = 20*log10(levelRight);
        //qDebug() << decibel << "dB" << endl;
        //if(decibel<-20.0) decibel=-20.0;
        //progress->setValue(decibel);
    }
    moyenne = abs(levelRight/buffer.frameCount());
    decibel = 100 + 20*log10(moyenne/255);
    //qDebug() << decibel << "dB" << endl;
    //if(decibel<-20.0) decibel=-20.0;*/
    QVector<qreal> levels = getBufferLevels(buffer);
    qDebug() << levels[0];
    if(levels[0] > 0)
    {
        decibelRight = 100 + (20*log10(levels[0]));
    }
    else
    {
        decibelRight = 0;
    }
    //decibelLeft = 100 + (20*log10(levels[1]));

    anim->setStartValue(previousValueRight);
    anim->setEndValue(decibelRight);
    anim->start();
    m_progressRight->setValue(decibelRight);
    //m_progressLeft->setValue(decibelRight);

    previousValueRight = decibelRight;
    //previousValueLeft = decibelLeft;
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

