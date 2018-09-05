#include <QDebug>

#include "clienttcp.h"

ClientTcp::ClientTcp() : QObject()
{
    m_socketServer = new QTcpSocket(this);

    this->connection();

    QObject::connect(m_socketServer, SIGNAL(readyRead()), this, SLOT(receivedData()));
    QObject::connect(m_socketServer, SIGNAL(connected()), this, SLOT(clientConnected()));
    QObject::connect(m_socketServer, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    QObject::connect(m_socketServer, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));
    QObject::connect(this, SIGNAL(connectionStatus(bool)), this, SLOT(setConnectionStatus(bool)));
    QObject::connect(this, SIGNAL(isReadyMenu(MenuWindow*)), this, SLOT(getThisMenuWindow(MenuWindow*)));
    QObject::connect(this, SIGNAL(isReadyDecoder(Decoder*)), this, SLOT(getThisDecoder(Decoder*)));
    QObject::connect(this, SIGNAL(isReadyWindow(MainWindow*)), this, SLOT(getThisWindow(MainWindow*)));

    m_packetSize = 0;
}

ClientTcp::~ClientTcp()
{
    m_socketServer->deleteLater();
}

ClientTcp* ClientTcp::getThisClientTcp()
{
    return this;
}

void ClientTcp::connection()
{
    qDebug() << "Connecting...";
    m_socketServer->abort();
    m_socketServer->connectToHost("192.168.1.13", 50885);
}

void ClientTcp::clientConnected()
{
    qDebug() << "Connected";
    emit connectionStatus(true);
}

void ClientTcp::clientDisconnected()
{
    emit connectionStatus(false);
}

void ClientTcp::sendData(QString messageToSend)
{
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    qDebug() << "Client sendData : " + messageToSend;

    out << (quint16) 0;
    out << messageToSend;
    out.device()->seek(0);
    out << (quint16) (packet.size() - sizeof(quint16));

    m_socketServer->write(packet);
}

void ClientTcp::receivedData()
{
    QDataStream in(m_socketServer);

    if (m_packetSize == 0)
    {
        if (m_socketServer->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> m_packetSize;
    }

    if (m_socketServer->bytesAvailable() < m_packetSize)
        return;

    QString receivedMessage;
    in >> receivedMessage;

    qDebug() << "Server received data : "+receivedMessage;

    m_decoder->decodeString(receivedMessage);

    m_packetSize = 0;
}

void ClientTcp::errorSocket(QAbstractSocket::SocketError error)
{
    switch(error)
    {
        case QAbstractSocket::HostNotFoundError:
            qDebug() << "ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            qDebug() << "ERREUR : le serveur a coupé la connexion.";
            break;
        default:
            qDebug() << "ERREUR : " + m_socketServer->errorString();
    }

    this->connection();
}

void ClientTcp::setConnectionStatus(bool status)
{
    m_menuWindow->setConnectionIcon(status);
    emit m_mainWindow->isClientConnected(status);
}

void ClientTcp::getThisMenuWindow(MenuWindow *menu)
{
    m_menuWindow = menu;
}

void ClientTcp::getThisDecoder(Decoder *decoder)
{
    m_decoder = decoder;
}

void ClientTcp::getThisWindow(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}
