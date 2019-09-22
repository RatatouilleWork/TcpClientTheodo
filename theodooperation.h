#ifndef THEODOOPERATION_H
#define THEODOOPERATION_H

#include <qmath.h>
#include "theodo.h"
#include "dtuoperation.h"

#include <QObject>



class TheodoOperation : public QObject
{
    Q_OBJECT
public:
    explicit TheodoOperation(QObject *parent = nullptr);
	explicit TheodoOperation(Theodo* theodolite, DTUOperation* dtu);

private:
	Theodo* m_theodolite;
	DTUOperation* m_DTUoperation;

	QString m_cmd;
	QString m_respond;

	QStringList m_respond_header;
	QStringList m_respond_data;

public:

	int op_Theodo(Theodo& in_theodo, int (Theodo::* aus_set_user_lock_stat)(Theodo::_Switch), Theodo::_Switch in_on_off= Theodo::ON);
	int op_Theodo(Theodo& in_theodo, int (Theodo::* aut_set_search_area)(double, double, double, double, Theodo::_isEnable), 
		double in_dCenterH, double in_dCenterV, double in_dRangeH, double in_dRangeV, Theodo::_isEnable in_enable = Theodo::ENABLE);
	int op_Theodo(Theodo& in_theodo, int (Theodo::* aut_ps_enable_range)(Theodo::_isEnable), Theodo::_isEnable in_enable = Theodo::ENABLE);
	int op_Theodo(Theodo& in_theodo, int (Theodo::* func) ());
	int op_Theodo(Theodo& in_theodo, int (Theodo::* bap_meas_distance_angle)(Theodo::_BAP_MEASURE_PROG), 
		Theodo::_BAP_MEASURE_PROG in_bap_measure_prog, double& out_dH, double& out_dV, double& out_dist, Theodo::_BAP_MEASURE_PROG& out_dist_mode);
	int op_Theodo(Theodo& in_theodo, int (Theodo::* bap_meas_distance_angle)(Theodo::_BAP_MEASURE_PROG), 
		Theodo::_BAP_MEASURE_PROG in_bap_measure_prog, double& out_x, double& out_y, double& out_z);

	int comm_process(Theodo& theodo);

signals:

public slots:
};

#endif // THEODOOPERATION_H
