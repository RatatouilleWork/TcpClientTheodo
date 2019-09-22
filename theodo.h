#ifndef THEODO_H
#define THEODO_H

#include <QObject>
#include <QDebug>
#include <QString>

class Theodo : public QObject
{
    Q_OBJECT

// Constructor:
public:
    explicit Theodo(QObject *parent = nullptr);

// Macros and enumerations:
public:

    // Enumerations:
    enum _Switch
    {
        OFF = 0,
        ON = 1
    }Switch;

    enum _isEnable
    {
        DISABLE = 0,
        ENABLE = 1
    }isEnable;

    enum _BAP_MEASURE_PROG
    {
        BAP_NO_MEAS = 0,
        BAP_NO_DIST = 1,
        BAP_DEF_DIST = 2,

        BAP_CLEAR_DIST = 5,
        BAP_STOP_TRK = 6
    }BAP_MEASURE_PROG;

    // Macros:
    static const uint GRC_OK = 0;
    static const uint GRC_NOT_IMPL = 5;
    static const uint GRC_NA = 27;

    static const uint GRC_AUT_SIDECOVER_ERR = 8723;
    static const uint GRC_AUT_NO_WORKING_AREA = 8720;
    static const uint GRC_AUT_NOTARGET = 8710;
    static const uint GRC_AUT_MOTOR_ERROR = 8707;
    static const uint GRC_AUT_DETECTOR_ERROR = 8713;
    static const uint GRC_AUT_NO_TARGET = 517;
    static const uint GRC_AUT_BAD_ENVIRONMENT = 8712;
    static const uint GRC_ATA_STRANGE_LIGHT = 524;

// Member properties:
public:
    QString m_Cmd;

private:
    QString m_feedBack;
    QStringList m_feedbackHeader;
    QStringList m_feedbackData;
	QString m_lastCmd;

// Signals and slots:
signals:
   void cmdSent(QString cmd);

public slots:
    int set_m_feedBack(QString feedBack);

// Theodolite functions:
public:
    int AUS_SetUserLockStat(_Switch onSwitch = ON);
    int AUT_SetSearchArea(double dCenterH, double dCenterV, double dRangeH, double dRangeV, _isEnable bEnable = ENABLE);
    int AUT_PS_EnableRange(_isEnable bEnable = ENABLE);
    int AUT_PS_SearchWindow();
    int AUT_LockIn();
    int BAP_MeasDistanceAngle(_BAP_MEASURE_PROG DistMode = BAP_DEF_DIST);

// Member methods:
public:
    int parseFeedback();
    QString get_m_feedBack();
    QStringList get_m_feedBackHeader();
    QStringList get_m_feedBackData();
	QString get_m_lastCmd();

};

#endif // THEODO_H





































