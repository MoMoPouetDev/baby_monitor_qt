#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QWidget>

class ClientTcp : public QObject
{
    Q_OBJECT

public:
    ClientTcp();
    ~ClientTcp();
    void connection();
    void sendData(QString);
    void setConnectionStatus(bool);
    bool getConnectionStatus();

public slots:
    void receivedData();
    void clientConnected();
    void clientDisconnected();
    void errorSocket(QAbstractSocket::SocketError);

signals:
    void connectionStatus();

private:
    QTcpSocket *m_socketServer;
    quint16 m_packetSize;
    bool m_connectionStatus = false;
};

#endif // CLIENT_H
