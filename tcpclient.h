#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    explicit TcpClient(quint16 port);

    QTcpSocket* m_socket;

signals:

public:
    void read_data(QString& respond);
    //void write_ready()
public:
    void write_data(QString msg);
};

#endif // TCPCLIENT_H
