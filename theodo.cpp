#include "theodo.h"

Theodo::Theodo(QObject *parent) : QObject(parent)
{
    qDebug()<<"Theodolite constructed";

}

// 操作函数

int Theodo::AUS_SetUserLockStat(_Switch onSwitch )
{
    m_Cmd.clear();

    if(Theodo::ON == onSwitch)
    {
        m_Cmd = "%R1Q,18007:1\r\n";
    }
    else
    {
        m_Cmd = "%R1Q,18007:0\r\n";
    }

    //emit cmdSent(QString(__FUNCTION__));
	m_lastCmd = __FUNCTION__;


    return 0;
}

int Theodo::AUT_SetSearchArea(double dCenterH, double dCenterV, double dRangeH, double dRangeV, _isEnable bEnable)
{
	m_Cmd = "%R1Q,9043:" + QString::number(dCenterH) + "," + QString::number(dCenterV) + "," + QString::number(dRangeH) + "," + QString::number(dRangeV) + "," + QString::number(bEnable) + "\r\n";
	m_lastCmd = __FUNCTION__;
	return 0;
}

int Theodo::AUT_PS_EnableRange(_isEnable bEnable)
{
	m_Cmd = "%R1Q,9048:" + QString::number(bEnable) + "\r\n";
	m_lastCmd = __FUNCTION__;
	return 0;
}

int Theodo::AUT_PS_SearchWindow()
{

	m_Cmd = QString("%R1Q,9052:")  + QString("\r\n");
	m_lastCmd = __FUNCTION__;
	return 0;
}

int Theodo::AUT_LockIn()
{
	m_Cmd = QString("%R1Q,9013:")  + QString("\r\n");
	m_lastCmd = __FUNCTION__;
	return 0;
}

int Theodo::BAP_MeasDistanceAngle(_BAP_MEASURE_PROG DistMode)
{
	m_Cmd = "%R1Q,17017:" + QString::number(DistMode) +  "\r\n";
	m_lastCmd = __FUNCTION__;
	return 0;
}

// 辅助函数

int Theodo::set_m_feedBack(QString feedBack)
{
    m_feedBack.clear();
    m_feedBack = feedBack;

    //emit theodoReady();
    return 0;
}

int Theodo::parseFeedback()
{
    if(m_feedBack.isEmpty())
    {
        return -1;
    }
    QStringList respond = m_feedBack.split(':');
	if (respond[0] == "%R1P,0,0" )
	{
		m_feedbackHeader.clear();
		m_feedbackHeader = respond[0].split(',');
		m_feedbackData.clear();
		m_feedbackData = respond[1].split(',');

		int ret = m_feedbackData[0].toInt();
		return ret;
	}
	else
	{
		qDebug() << "not theodolite respond!";
		return -1;
	}

    return 0;

}

QString Theodo::get_m_feedBack()
{
	return m_feedBack;
}

QStringList Theodo::get_m_feedBackHeader()
{
	return  m_feedbackHeader;
}

QStringList Theodo::get_m_feedBackData()
{
	return m_feedbackData;
}
QString Theodo::get_m_lastCmd()
{
	return m_lastCmd;
}
//





































