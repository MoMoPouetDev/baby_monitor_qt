#include <QRegExp>
#include <QStringList>

#include "decoder.h"

Decoder::Decoder()
{
    QObject::connect(this, SIGNAL(isReadyClient(ClientTcp*)), this, SLOT(getThisClient(ClientTcp*)));
    QObject::connect(this, SIGNAL(isReadyMenuMusicWindow(MenuMusicWindow*)), this, SLOT(getThisMenuMusicWindow(MenuMusicWindow*)));
}

Decoder::~Decoder()
{

}

Decoder* Decoder::getThisDecoder()
{
    return this;
}

void Decoder::getThisClient(ClientTcp *client)
{
    m_client = client;
}

void Decoder::getThisMenuMusicWindow(MenuMusicWindow *menuMusic)
{
    m_menuMusicWindow = menuMusic;
}

void Decoder::decodeString(const QString &message)
{
    qDebug()<<"Server Decoder: " + message;

    QRegExp regex("\\;");
    QStringList string = message.split(regex);

    if (string.at(0) == "Library") {
        string.removeFirst();

        m_menuMusicWindow->stringList(string);
    }
    else if (string.at(0) == "Volume") {
        string.removeFirst();
        QString volumeString = string[0];
        qDebug() << "Server Decoder : " + volumeString;
        int volume = volumeString.toInt();
        m_menuMusicWindow->setVolumeBar(volume);
    }
    else if (string.at(0) == "Mute") {
        string.removeFirst();
        qDebug() << "Server Decoder : " + string[0];
        if (string[0] == "true") {
            m_menuMusicWindow->setVolumeBar(0);
            m_menuMusicWindow->setIconMute(true);
        }
        else {
            m_client->sendData("Volume");
            m_menuMusicWindow->setIconMute(false);
        }
    }
}
