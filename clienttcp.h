#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QWidget>

#include "manager.h"

class MenuWindow;
class Decoder;
class ClientTcp : public QObject
{
    Q_OBJECT

public:
    ClientTcp();
    ~ClientTcp();
    ClientTcp* getThisClientTcp();
    void connection();
    void sendData(QString);

public slots:
    void receivedData();
    void clientConnected();
    void clientDisconnected();
    void errorSocket(QAbstractSocket::SocketError);
    void getThisMenuWindow(MenuWindow*);
    void getThisDecoder(Decoder*);
    void setConnectionStatus(bool);

signals:
    void connectionStatus(bool);
    void isReadyMenu(MenuWindow*);
    void isReadyDecoder(Decoder*);

private:
    MenuWindow* m_menuWindow;
    Decoder *m_decoder;
    QTcpSocket *m_socketServer;
    quint16 m_packetSize;
};

#endif // CLIENT_H
