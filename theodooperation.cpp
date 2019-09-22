#include "theodooperation.h"

TheodoOperation::TheodoOperation(QObject *parent) : QObject(parent)
{
	m_DTUoperation = new DTUOperation(this);
	m_DTUoperation->DTU_init(QHostAddress("127.0.0.1"), 10000);


}

TheodoOperation::TheodoOperation(Theodo* theodolite, DTUOperation* dtu)
{
	theodolite = new Theodo(this);
	dtu = new DTUOperation(this);
	m_theodolite = theodolite;
	m_DTUoperation = dtu;
}


int TheodoOperation::op_Theodo(Theodo& in_theodo, int(Theodo::*aus_set_user_lock_stat)(Theodo::_Switch), Theodo::_Switch in_on_off)
{
	(in_theodo.*aus_set_user_lock_stat)(in_on_off);

	return comm_process(in_theodo);
}

int TheodoOperation::op_Theodo(Theodo& in_theodo, int(Theodo::*aut_set_search_area)(double, double, double, double, Theodo::_isEnable), double in_dCenterH, double in_dCenterV, double in_dRangeH, double in_dRangeV, Theodo::_isEnable in_enable)
{
	(in_theodo.*aut_set_search_area)(in_dCenterH, in_dCenterV, in_dRangeH, in_dRangeV, in_enable);
	return comm_process(in_theodo);
}

int TheodoOperation::op_Theodo(Theodo& in_theodo, int(Theodo::*aut_ps_enable_range)(Theodo::_isEnable), Theodo::_isEnable in_enable)
{
	(in_theodo.*aut_ps_enable_range)(in_enable);
	return comm_process(in_theodo);
}

int TheodoOperation::op_Theodo(Theodo& in_theodo, int(Theodo::*func)())
{
	(in_theodo.*func)();
	return comm_process(in_theodo);
}

int TheodoOperation::op_Theodo(Theodo& in_theodo, int(Theodo::*bap_meas_distance_angle)(Theodo::_BAP_MEASURE_PROG), Theodo::_BAP_MEASURE_PROG in_bap_measure_prog, double& out_dH, double& out_dV, double& out_dist, Theodo::_BAP_MEASURE_PROG& out_dist_mode)
{
	(in_theodo.*bap_meas_distance_angle)(in_bap_measure_prog);
	int ret = comm_process(in_theodo);
	if (Theodo::GRC_OK == ret)
	{
		m_respond_data = in_theodo.get_m_feedBackData();

		out_dH = m_respond_data[1].toDouble();
		out_dV = m_respond_data[2].toDouble();
		out_dist = m_respond_data[3].toDouble();

		switch (m_respond_data[4].toInt())
		{
		case 0:
			out_dist_mode = Theodo::BAP_NO_MEAS;
		case 1:
			out_dist_mode = Theodo::BAP_NO_DIST;
		case 2:
			out_dist_mode = Theodo::BAP_DEF_DIST;
		case 5:
			out_dist_mode = Theodo::BAP_CLEAR_DIST;
		case 6:
			out_dist_mode = Theodo::BAP_STOP_TRK;
		}
	}
	
	return ret;
}

int TheodoOperation::op_Theodo(Theodo& in_theodo, int(Theodo::* bap_meas_distance_angle)(Theodo::_BAP_MEASURE_PROG), Theodo::_BAP_MEASURE_PROG in_bap_measure_prog, double& out_x, double& out_y, double& out_z)
{
	(in_theodo.*bap_meas_distance_angle)(in_bap_measure_prog);
	int ret = comm_process(in_theodo);
	if (Theodo::GRC_OK == ret)
	{
		if (Theodo::BAP_DEF_DIST == in_bap_measure_prog)
		{
			m_respond_data = in_theodo.get_m_feedBackData();

			double angle_z = m_respond_data[1].toDouble();
			double angle_x = m_respond_data[2].toDouble();
			double r = m_respond_data[3].toDouble();

			out_z = r * sin(angle_z);
			out_x = r * cos(angle_z) * cos(angle_x);
			out_y = r * cos(angle_z) * sin(angle_x);
		}
	}
	
	return ret;
}

int TheodoOperation::comm_process(Theodo& theodo)
{
	int ret = -1;
	m_cmd = theodo.m_Cmd;
	m_DTUoperation->DTU_write_data(m_cmd);
	m_respond.clear();
	m_DTUoperation->DTU_read_data(m_respond);
	theodo.set_m_feedBack(m_respond);

	ret = theodo.parseFeedback();
	if (ret >= 0)
	{
		qDebug() << __LINE__ << __FILE__ << "RC = " << ret;
	}

	m_respond_header.clear();
	m_respond_header = theodo.get_m_feedBackHeader();
	m_respond_data.clear();
	m_respond_data = theodo.get_m_feedBackData();

	return ret;
}

