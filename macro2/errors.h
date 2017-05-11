#include <map>

#include "errors_sim.h"
#include "errors_data.h"

// all map keys are the polar track angle
// map values are the error associated with
// that angle and error type

// single photon resolution
map<double,double> sim_spr_err;
map<double,double> data_spr_err;

// reconstructed theta_C
map<double,double> sim_thc_err;
map<double,double> data_thc_err;

// photon yield
map<double,double> sim_nph_err;
map<double,double> data_nph_err;

double quadAdd(double q1, double q2, double q3 = 0, double q4 = 0)
{
	return TMath::Sqrt(q1*q1 + q2*q2 + q3*q3 + q4*q4);
}

void  totalErrors()
{
	for(double i=20; i<=150; i+=5)
	{
		sim_nph_err[i]  = sim_err::nph_errstat[i];
		data_nph_err[i] = data_err::nph_errstat[i];

		sim_spr_err[i] = quadAdd(sim_err::spr_errstat[i],
								 sim_err::spr_errfit[i],
								 sim_err::spr_errbin[i]);

		data_spr_err[i] = quadAdd(data_err::spr_errstat[i],
								  data_err::spr_errfit[i],
								  data_err::spr_errbin[i]);

		sim_thc_err[i] = quadAdd(sim_err::thc_errstat[i],
								 sim_err::thc_errfit[i],
								 sim_err::thc_errbin[i]);

		data_thc_err[i] = quadAdd(data_err::thc_errstat[i],
								  data_err::thc_errfit[i],
								  data_err::thc_errbin[i]);

	}
}

void setErrors()
{
	sim_err::setErrors();
	data_err::setErrors();

	return;
}

