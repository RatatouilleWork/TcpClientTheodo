#ifndef DTUOPERATION_H
#define DTUOPERATION_H

#include <QObject>
#include <qtcpsocket.h>
#include <qhostaddress.h>
#include <qtimer.h>

class DTUOperation : public QObject
{
    Q_OBJECT
public:
    explicit DTUOperation(QObject *parent = nullptr);

public:
	QTcpSocket* m_sock;

signals:

public slots:

public:
	int DTU_init(QHostAddress IP_addr, quint16 port);
	int DTU_read_data(QString& respond);
	void DTU_write_data(QString& msg);
};

#endif // DTUOPERATION_H
