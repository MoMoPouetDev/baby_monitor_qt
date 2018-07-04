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
    qDebug()<<"Decder: " + message;

    QRegExp regex("\\;");
    QStringList string = message.split(regex);

    if (string.at(0) == "Library") {
        string.removeFirst();

        m_menuMusicWindow->stringList(string);
    }
}
