#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    bool ok = false;
    m_socket = new QTcpSocket(this);
    m_socket->open(QIODevice::ReadWrite);
    m_socket->connectToHost(QHostAddress::LocalHost, 10000);
    ok = m_socket->waitForConnected();
    if(false == ok)
    {
        qDebug()<<"error";
    }
}



TcpClient::TcpClient(quint16 port)
{
    bool ok = false;
    m_socket = new QTcpSocket(this);
    m_socket->open(QIODevice::ReadWrite);
    m_socket->connectToHost(QHostAddress::Any, port);
    ok = m_socket->waitForConnected();
    if(false == ok)
    {
        qDebug()<<"error";
    }

}

void TcpClient::read_data(QString& respond)
{
    m_socket->waitForReadyRead();
    respond = m_socket->readAll();

    qDebug()<<__LINE__<<__FUNCTION__<<respond;
}

void TcpClient::write_data(QString msg)
{
    m_socket->write(msg.toLatin1(), msg.length());
}
