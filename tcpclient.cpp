#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    bool ok = false;
    m_socket = new QTcpSocket(this);
    m_socket->open(QIODevice::ReadWrite);
    m_socket->connectToHost("127.0.0.1", 10086);
    ok = m_socket->waitForConnected();
    if(false == ok)
    {
        qDebug()<<"error";
    }
}

void TcpClient::read_data()
{
    m_socket->waitForReadyRead();
    QString msg;
    msg = m_socket->readAll();

    qDebug()<<msg;
}

void TcpClient::write_data(QString msg)
{
    m_socket->write(msg.toLatin1(), msg.length());
}
