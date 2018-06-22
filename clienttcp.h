#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>

class ClientTcp
{
    Q_OBJECT

public:
    ClientTcp();
    ~ClientTcp();
    void connection();

public slots:
    void receivedData();
    void clientConnected();
    void clientDisconnected();
    void errorSocket(QAbstractSocket::SocketError);

private:
    QTcpSocket *m_socketServer;
    quint16 m_packetSize;

};

#endif // CLIENT_H
