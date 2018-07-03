#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDir>

#include "manager.h"

class ClientTcp;
class MenuMusicWindow;
class Decoder : public QObject
{
    Q_OBJECT

    public:
        Decoder();
        ~Decoder();
        Decoder* getThisDecoder();
        void decodeString(const QString &message);

    private slots:
        void getThisClient(ClientTcp*);
        void getThisMenuMusicWindow(MenuMusicWindow*);

    signals:
        void isReadyClient(ClientTcp*);
        void isReadyMenuMusicWindow(MenuMusicWindow*);

    private:
        ClientTcp *m_client;
        MenuMusicWindow *m_menuMusicWindow;
};

#endif // DECODER_H
