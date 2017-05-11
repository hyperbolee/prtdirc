namespace sim_err
{

// single photon resolution
	map<double,double> spr_errbin;   // error from binning
	map<double,double> spr_errfit;   // from varying fitting function
	map<double,double> spr_errstat;  // from in-file fluctuations

// reconstructed theta_C
	map<double,double> thc_errbin;   // error from binning
	map<double,double> thc_errfit;   // from varying fitting function
	map<double,double> thc_errstat;  // from in-file fluctuations

// photon yield
	map<double,double> nph_errstat;  // error from in-file fluctuations

	void setErrors()
	{
		nph_errstat[100.000000] = 0.714948;
		nph_errstat[105.000000] = 0.760837;
		nph_errstat[110.000000] = 0.705549;
		nph_errstat[115.000000] = 0.950910;
		nph_errstat[120.000000] = 0.653095;
		nph_errstat[125.000000] = 0.710632;
		nph_errstat[130.000000] = 0.804065;
		nph_errstat[135.000000] = 0.747828;
		nph_errstat[140.000000] = 0.843473;
		nph_errstat[145.000000] = 1.385865;
		nph_errstat[150.000000] = 1.427846;
		nph_errstat[20.000000] = 2.019043;
		nph_errstat[25.000000] = 0.997695;
		nph_errstat[30.000000] = 1.085947;
		nph_errstat[35.000000] = 0.924906;
		nph_errstat[40.000000] = 1.018069;
		nph_errstat[45.000000] = 1.071016;
		nph_errstat[50.000000] = 0.497366;
		nph_errstat[55.000000] = 0.897566;
		nph_errstat[60.000000] = 0.982357;
		nph_errstat[65.000000] = 0.781862;
		nph_errstat[70.000000] = 0.592532;
		nph_errstat[75.000000] = 0.466169;
		nph_errstat[80.000000] = 0.553620;
		nph_errstat[85.000000] = 0.666669;
		nph_errstat[90.000000] = 0.613311;
		nph_errstat[95.000000] = 0.781460;
		spr_errbin[100.000000] = 0.157531;
		spr_errbin[105.000000] = 0.191424;
		spr_errbin[110.000000] = 0.244103;
		spr_errbin[115.000000] = 0.231399;
		spr_errbin[130.000000] = 0.252363;
		spr_errbin[135.000000] = 0.233804;
		spr_errbin[140.000000] = 0.318771;
		spr_errbin[145.000000] = 0.084685;
		spr_errbin[150.000000] = 0.259294;
		spr_errbin[45.000000] = 0.127071;
		spr_errbin[65.000000] = 0.576905;
		spr_errbin[70.000000] = 0.217389;
		spr_errbin[75.000000] = 0.215281;
		spr_errbin[80.000000] = 0.163167;
		spr_errbin[85.000000] = 0.160859;
		spr_errbin[90.000000] = 0.324943;
		spr_errbin[95.000000] = 0.866944;
		spr_errfit[100.000000] = 0.555187;
		spr_errfit[105.000000] = 0.231857;
		spr_errfit[110.000000] = 0.609973;
		spr_errfit[115.000000] = 0.372030;
		spr_errfit[130.000000] = 0.534061;
		spr_errfit[135.000000] = 0.544344;
		spr_errfit[140.000000] = 0.436552;
		spr_errfit[145.000000] = 0.521207;
		spr_errfit[150.000000] = 0.319381;
		spr_errfit[45.000000] = 0.287122;
		spr_errfit[65.000000] = 0.774808;
		spr_errfit[70.000000] = 0.424391;
		spr_errfit[75.000000] = 0.286049;
		spr_errfit[80.000000] = 0.351743;
		spr_errfit[85.000000] = 0.547985;
		spr_errfit[90.000000] = 0.631783;
		spr_errfit[95.000000] = 1.747426;
		spr_errstat[100.000000] = 0.589391;
		spr_errstat[105.000000] = 0.345941;
		spr_errstat[110.000000] = 0.530908;
		spr_errstat[115.000000] = 0.693102;
		spr_errstat[120.000000] = 0.422334;
		spr_errstat[125.000000] = 0.346609;
		spr_errstat[130.000000] = 0.708479;
		spr_errstat[135.000000] = 0.535455;
		spr_errstat[140.000000] = 0.831277;
		spr_errstat[145.000000] = 0.249839;
		spr_errstat[150.000000] = 0.430198;
		spr_errstat[20.000000] = 0.000000;
		spr_errstat[25.000000] = 1.393203;
		spr_errstat[30.000000] = 0.497015;
		spr_errstat[35.000000] = 0.285574;
		spr_errstat[40.000000] = 0.501642;
		spr_errstat[45.000000] = 0.444219;
		spr_errstat[50.000000] = 0.434577;
		spr_errstat[55.000000] = 0.336541;
		spr_errstat[60.000000] = 0.418804;
		spr_errstat[65.000000] = 0.426672;
		spr_errstat[70.000000] = 0.465418;
		spr_errstat[75.000000] = 0.689170;
		spr_errstat[80.000000] = 0.627286;
		spr_errstat[85.000000] = 1.246231;
		spr_errstat[90.000000] = 0.531475;
		spr_errstat[95.000000] = 1.310797;
		thc_errbin[100.000000] = 0.153459;
		thc_errbin[105.000000] = 0.173903;
		thc_errbin[110.000000] = 0.198879;
		thc_errbin[115.000000] = 0.102538;
		thc_errbin[130.000000] = 0.147554;
		thc_errbin[135.000000] = 0.207985;
		thc_errbin[140.000000] = 0.224600;
		thc_errbin[145.000000] = 0.087002;
		thc_errbin[150.000000] = 0.118661;
		thc_errbin[45.000000] = 0.122650;
		thc_errbin[65.000000] = 0.243047;
		thc_errbin[70.000000] = 0.139198;
		thc_errbin[75.000000] = 0.206834;
		thc_errbin[80.000000] = 0.167632;
		thc_errbin[85.000000] = 0.134795;
		thc_errbin[90.000000] = 0.198953;
		thc_errbin[95.000000] = 0.482066;
		thc_errfit[100.000000] = 0.176236;
		thc_errfit[105.000000] = 0.121971;
		thc_errfit[110.000000] = 0.208319;
		thc_errfit[115.000000] = 0.116189;
		thc_errfit[130.000000] = 0.462481;
		thc_errfit[135.000000] = 0.150522;
		thc_errfit[140.000000] = 0.152475;
		thc_errfit[145.000000] = 0.098364;
		thc_errfit[150.000000] = 0.227375;
		thc_errfit[45.000000] = 0.068264;
		thc_errfit[65.000000] = 0.416853;
		thc_errfit[70.000000] = 0.139443;
		thc_errfit[75.000000] = 0.120812;
		thc_errfit[80.000000] = 0.116362;
		thc_errfit[85.000000] = 0.171467;
		thc_errfit[90.000000] = 0.334298;
		thc_errfit[95.000000] = 0.910375;
		thc_errstat[100.000000] = 0.396867;
		thc_errstat[105.000000] = 0.414110;
		thc_errstat[110.000000] = 0.558573;
		thc_errstat[115.000000] = 0.391330;
		thc_errstat[120.000000] = 0.380967;
		thc_errstat[125.000000] = 0.356276;
		thc_errstat[130.000000] = 0.361504;
		thc_errstat[135.000000] = 0.235812;
		thc_errstat[140.000000] = 0.411669;
		thc_errstat[145.000000] = 0.281765;
		thc_errstat[150.000000] = 0.291570;
		thc_errstat[20.000000] = 1.729660;
		thc_errstat[25.000000] = 3.525315;
		thc_errstat[30.000000] = 0.366342;
		thc_errstat[35.000000] = 0.266441;
		thc_errstat[40.000000] = 0.281779;
		thc_errstat[45.000000] = 0.403950;
		thc_errstat[50.000000] = 0.615153;
		thc_errstat[55.000000] = 0.353450;
		thc_errstat[60.000000] = 0.272518;
		thc_errstat[65.000000] = 0.349993;
		thc_errstat[70.000000] = 0.454879;
		thc_errstat[75.000000] = 0.462611;
		thc_errstat[80.000000] = 0.383716;
		thc_errstat[85.000000] = 0.618669;
		thc_errstat[90.000000] = 0.395811;
		thc_errstat[95.000000] = 2.105331;
	}

}
