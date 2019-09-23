#include "dtuoperation.h"

DTUOperation::DTUOperation(QObject *parent) : QObject(parent)
{
	qDebug() << "DTU operation construted";
	m_sock = new QTcpSocket(this);

}

int DTUOperation::DTU_init(QHostAddress IP_addr, quint16 port)
{
	int ret = -1;
	bool ret_boolean = false;

	do
	{
		ret = m_sock->open(QIODevice::ReadWrite);
		if (ret < 0)
		{
			perror("QIODevice::open");
			break;
		}
		m_sock->connectToHost(IP_addr, port);
        connect(this, SIGNAL(connected()), this, SLOT(slot_connected()));
		ret_boolean = m_sock->waitForConnected();
		if (false == ret_boolean)
		{
			perror("QIODevice::waitForConnected");
			break;
		}

		return 1;
	} while (0);

	return -1;


}

int DTUOperation::DTU_read_data(QString& respond)
{

	QTimer timo;
	timo.singleShot(3000, []() {
		qDebug() << "time out";
		});
	timo.start();

	respond.clear();
	m_sock->waitForReadyRead();
	respond = m_sock->readAll();

	return 0;

}

void DTUOperation::DTU_write_data(QString& msg)
{
	m_sock->write(msg.toLatin1(), msg.length());
}

void DTUOperation::slot_connected()
{
    qDebug()<<"server connected";
}


