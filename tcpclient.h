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

    QTcpSocket* m_socket;

signals:

public slots:
    void read_data();
    //void write_ready()
public:
    void write_data(QString msg);
};

#endif // TCPCLIENT_H
