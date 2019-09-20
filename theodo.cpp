#include "theodo.h"

Theodo::Theodo(QObject *parent) : QObject(parent)
{
    qDebug()<<"Theodolite constructed";

}

// 操作函数

int Theodo::AUS_SetUserLockStat(_Switch onSwitch = Theodo::ON)
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

    emit cmdSent(QString(__FUNCTION__));


    return 0;
}

// 辅助函数

int Theodo::getFeedBack(QString feedBack)
{
    m_feedBack.clear();
    m_feedBack = feedBack;
    qDebug()<<__LINE__<<__FILE__<<__FUNCTION__<<feedBack;
    qDebug()<<__LINE__<<__FILE__<<__FUNCTION__<<m_feedBack;

    emit theodoReady();
    return 0;
}

int Theodo::parseFeedback()
{
    if(m_feedBack.isEmpty())
    {
        qDebug()<<"empty string";
        return -1;
    }
    QStringList respond = m_feedBack.split(':');
    qDebug()<<__LINE__<<__FILE__<<__FUNCTION__<<respond;
    qDebug()<<__LINE__<<__FILE__<<__FUNCTION__<<respond[0];
    qDebug()<<__LINE__<<__FILE__<<__FUNCTION__<<respond[1];
    m_feedbackHeader.clear();
    m_feedbackHeader = respond[0].split(',');
    qDebug()<<__LINE__<<__FILE__<<__FUNCTION__<<m_feedbackHeader;
    m_feedbackData.clear();
    m_feedbackData = respond[1].split(',');
    qDebug()<<__LINE__<<__FILE__<<__FUNCTION__<<m_feedbackData;
    int ret = m_feedbackData[0].toInt();

    return ret;

}

void Theodo::get_m_feedBack(QString& feedBack)
{
    feedBack = m_feedBack;
    return;
}

void Theodo::get_m_feedBackHeader(QStringList& feedBackHeader)
{
    feedBackHeader = m_feedbackHeader;
    return;
}

void Theodo::get_m_feedBackData(QStringList& feedBackData)
{
    feedBackData = m_feedbackData;
    return;
}
//





































