#include <QCoreApplication>
#include <tcpclient.h>
#include "dtuoperation.h"
#include "theodo.h"
#include "theodooperation.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Theodo TS60;
	TheodoOperation op;

	QList<std::tuple<double, double, double>> coordinations;

    while(1)
    {
		//qDebug() << "set user lock state:";
		op.op_Theodo(TS60, &Theodo::AUS_SetUserLockStat, Theodo::ON );

        system("pause");

        op.op_Theodo(TS60, &Theodo::AUT_PS_EnableRange, Theodo::ENABLE);

        system("pause");

        op.op_Theodo(TS60, &Theodo::AUT_PS_SearchWindow);

        system("pause");

		//qDebug() << "measure distance and angel:";
        double x = 0, y = 0, z = 0;
		op.op_Theodo(TS60, &Theodo::BAP_MeasDistanceAngle, Theodo::BAP_DEF_DIST, x, y, z);

		coordinations.append(std::tuple<double, double, double>(x, y, z));

        foreach(auto var,  coordinations)
		{
			std::cout << "x = " << get<0>(var) << endl; 
			std::cout << "y = " << get<1>(var) << endl; 
			std::cout << "z = " << get<2>(var) << endl; 

		}

		system("pause");


    }



        //Working loop:

    return a.exec();
}
