#include "clienttcp.h"

ClientTcp::ClientTcp()
{
    m_socketServer = new QTcpSocket(this);

    this->connection();

    QObject::connect(m_socketServer, SIGNAL(readyRead()), this, SLOT(receivedData()));
    QObject::connect(m_socketServer, SIGNAL(connected()), this, SLOT(clientConnected()));
    QObject::connect(m_socketServer, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    QObject::connect(m_socketServer, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));

    m_packetSize = 0;
}

ClientTcp::~ClientTcp()
{
}

void ClientTcp::connection()
{

}

void ClientTcp::clientConnected()
{

}

void ClientTcp::clientDisconnected()
{

}

void ClientTcp::receivedData()
{

}

void ClientTcp::errorSocket(QAbstractSocket::SocketError error)
{

}
