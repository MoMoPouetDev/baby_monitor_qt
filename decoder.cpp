#include "decoder.h"

Decoder::Decoder()
{
    QObject::connect(this, SIGNAL(isReadyClient(ClientTcp*)), this, SLOT(getThisClient(ClientTcp*)));
}

Decoder::~Decoder()
{

}

Decoder* Decoder::getThisDecoder()
{
    return this;
}

void Decoder::decodeString(const QString &message)
{
    qDebug()<<"Decder: " + message;

    if(message == "Library")
    {

    }
    else if(message == "SoundUp")
    {}
    else if(message == "SoundDown")
    {}
    else if(message == "SoundMute")
    {}
    else if(message == "SoundUnmute")
    {}
    else if(message == "PowerOff")
    {}
    else
    {
        /*Parcour List music*/
    }
}
