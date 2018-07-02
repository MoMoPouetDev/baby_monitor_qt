#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDir>

#include "manager.h"

class ClientTcp;
class Decoder : public QObject
{
    //Q_OBJECT

    public:
        Decoder();
        ~Decoder();
        Decoder* getThisDecoder();
        void decodeString(const QString &message);

    private slots:
        void getThisClient(ClientTcp*);

    signals:
        void isReadyClient(ClientTcp*);

    private:
        ClientTcp *m_client;
};

#endif // DECODER_H
