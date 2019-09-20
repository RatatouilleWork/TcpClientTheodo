#include <QCoreApplication>
#include <tcpclient.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpClient client;
    QString s;
    QTextStream in(stdin);

    while(1)
    {
        //Working loop:

    }
    return a.exec();
}
