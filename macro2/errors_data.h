namespace data_err
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
		nph_errstat[100.000000] = 1.369965;
		nph_errstat[105.000000] = 1.250467;
		nph_errstat[110.000000] = 1.244499;
		nph_errstat[115.000000] = 1.352266;
		nph_errstat[120.000000] = 1.548781;
		nph_errstat[125.000000] = 1.326405;
		nph_errstat[130.000000] = 1.887274;
		nph_errstat[135.000000] = 1.246275;
		nph_errstat[140.000000] = 1.641230;
		nph_errstat[145.000000] = 1.851212;
		nph_errstat[150.000000] = 1.465154;
		nph_errstat[20.000000] = 1.417114;
		nph_errstat[25.000000] = 1.776860;
		nph_errstat[30.000000] = 1.580420;
		nph_errstat[35.000000] = 1.335239;
		nph_errstat[40.000000] = 1.427682;
		nph_errstat[45.000000] = 1.470841;
		nph_errstat[50.000000] = 1.428556;
		nph_errstat[55.000000] = 1.708407;
		nph_errstat[60.000000] = 1.345272;
		nph_errstat[65.000000] = 1.747540;
		nph_errstat[70.000000] = 1.112633;
		nph_errstat[75.000000] = 1.353071;
		nph_errstat[80.000000] = 1.246243;
		nph_errstat[85.000000] = 1.197254;
		nph_errstat[90.000000] = 1.411917;
		nph_errstat[95.000000] = 1.605403;
		spr_errbin[100.000000] = 0.290009;
		spr_errbin[105.000000] = 0.212764;
		spr_errbin[110.000000] = 0.392945;
		spr_errbin[115.000000] = 0.325637;
		spr_errbin[120.000000] = 0.222162;
		spr_errbin[125.000000] = 0.235222;
		spr_errbin[130.000000] = 0.288272;
		spr_errbin[135.000000] = 0.267703;
		spr_errbin[140.000000] = 0.227217;
		spr_errbin[145.000000] = 0.108234;
		spr_errbin[150.000000] = 0.160261;
		spr_errbin[20.000000] = 0.435130;
		spr_errbin[25.000000] = 0.145067;
		spr_errbin[30.000000] = 0.270412;
		spr_errbin[35.000000] = 0.335748;
		spr_errbin[40.000000] = 0.374572;
		spr_errbin[45.000000] = 0.189247;
		spr_errbin[50.000000] = 0.671755;
		spr_errbin[55.000000] = 0.432430;
		spr_errbin[60.000000] = 0.294512;
		spr_errbin[65.000000] = 0.467227;
		spr_errbin[70.000000] = 0.125118;
		spr_errbin[75.000000] = 2.404803;
		spr_errbin[80.000000] = 0.201947;
		spr_errbin[85.000000] = 0.643959;
		spr_errbin[90.000000] = 0.164649;
		spr_errbin[95.000000] = 0.291999;
		spr_errfit[100.000000] = 1.140429;
		spr_errfit[105.000000] = 0.454561;
		spr_errfit[110.000000] = 0.868256;
		spr_errfit[115.000000] = 1.138635;
		spr_errfit[120.000000] = 0.477292;
		spr_errfit[125.000000] = 0.301961;
		spr_errfit[130.000000] = 0.609425;
		spr_errfit[135.000000] = 0.744683;
		spr_errfit[140.000000] = 0.821502;
		spr_errfit[145.000000] = 0.399926;
		spr_errfit[150.000000] = 0.536510;
		spr_errfit[20.000000] = 1.051238;
		spr_errfit[25.000000] = 0.418060;
		spr_errfit[30.000000] = 0.464688;
		spr_errfit[35.000000] = 0.721035;
		spr_errfit[40.000000] = 1.452184;
		spr_errfit[45.000000] = 0.476537;
		spr_errfit[50.000000] = 1.438531;
		spr_errfit[55.000000] = 1.294380;
		spr_errfit[60.000000] = 0.479441;
		spr_errfit[65.000000] = 1.164814;
		spr_errfit[70.000000] = 0.883363;
		spr_errfit[75.000000] = 3.439284;
		spr_errfit[80.000000] = 0.953373;
		spr_errfit[85.000000] = 0.950122;
		spr_errfit[90.000000] = 0.652759;
		spr_errfit[95.000000] = 0.000000;
		spr_errstat[100.000000] = 1.382642;
		spr_errstat[105.000000] = 0.872909;
		spr_errstat[110.000000] = 1.673291;
		spr_errstat[115.000000] = 0.526306;
		spr_errstat[120.000000] = 0.782368;
		spr_errstat[125.000000] = 0.574997;
		spr_errstat[130.000000] = 0.429279;
		spr_errstat[135.000000] = 0.419238;
		spr_errstat[140.000000] = 2.518622;
		spr_errstat[145.000000] = 0.224814;
		spr_errstat[150.000000] = 0.374898;
		spr_errstat[20.000000] = 0.227823;
		spr_errstat[25.000000] = 0.568467;
		spr_errstat[30.000000] = 0.543831;
		spr_errstat[35.000000] = 0.404046;
		spr_errstat[40.000000] = 1.221183;
		spr_errstat[45.000000] = 0.468078;
		spr_errstat[50.000000] = 1.043279;
		spr_errstat[55.000000] = 0.770138;
		spr_errstat[60.000000] = 0.773115;
		spr_errstat[65.000000] = 1.280536;
		spr_errstat[70.000000] = 0.684477;
		spr_errstat[75.000000] = 1.229600;
		spr_errstat[80.000000] = 1.161578;
		spr_errstat[85.000000] = 1.761713;
		spr_errstat[90.000000] = 1.015731;
		spr_errstat[95.000000] = 1.157631;
		thc_errbin[100.000000] = 0.176314;
		thc_errbin[105.000000] = 0.136112;
		thc_errbin[110.000000] = 0.175488;
		thc_errbin[115.000000] = 0.292136;
		thc_errbin[120.000000] = 0.132775;
		thc_errbin[125.000000] = 0.143469;
		thc_errbin[130.000000] = 0.186232;
		thc_errbin[135.000000] = 0.159506;
		thc_errbin[140.000000] = 0.180702;
		thc_errbin[145.000000] = 0.082307;
		thc_errbin[150.000000] = 0.089715;
		thc_errbin[20.000000] = 0.156576;
		thc_errbin[25.000000] = 0.095488;
		thc_errbin[30.000000] = 0.166770;
		thc_errbin[35.000000] = 0.264338;
		thc_errbin[40.000000] = 0.174335;
		thc_errbin[45.000000] = 0.123640;
		thc_errbin[50.000000] = 0.379557;
		thc_errbin[55.000000] = 0.198304;
		thc_errbin[60.000000] = 0.166698;
		thc_errbin[65.000000] = 0.202360;
		thc_errbin[70.000000] = 0.091696;
		thc_errbin[75.000000] = 0.000000;
		thc_errbin[80.000000] = 0.129414;
		thc_errbin[85.000000] = 0.314500;
		thc_errbin[90.000000] = 0.150492;
		thc_errbin[95.000000] = 0.420793;
		thc_errfit[100.000000] = 0.266327;
		thc_errfit[105.000000] = 0.138640;
		thc_errfit[110.000000] = 0.250633;
		thc_errfit[115.000000] = 0.247303;
		thc_errfit[120.000000] = 0.151192;
		thc_errfit[125.000000] = 0.210205;
		thc_errfit[130.000000] = 0.505814;
		thc_errfit[135.000000] = 0.456081;
		thc_errfit[140.000000] = 0.225784;
		thc_errfit[145.000000] = 0.134964;
		thc_errfit[150.000000] = 0.236490;
		thc_errfit[20.000000] = 0.391845;
		thc_errfit[25.000000] = 0.172576;
		thc_errfit[30.000000] = 0.311284;
		thc_errfit[35.000000] = 0.171486;
		thc_errfit[40.000000] = 0.585381;
		thc_errfit[45.000000] = 0.195664;
		thc_errfit[50.000000] = 3.862499;
		thc_errfit[55.000000] = 0.245850;
		thc_errfit[60.000000] = 0.262132;
		thc_errfit[65.000000] = 0.494141;
		thc_errfit[70.000000] = 0.291336;
		thc_errfit[75.000000] = 0.000000;
		thc_errfit[80.000000] = 0.445479;
		thc_errfit[85.000000] = 0.793722;
		thc_errfit[90.000000] = 0.432654;
		thc_errfit[95.000000] = 0.000000;
		thc_errstat[100.000000] = 0.725581;
		thc_errstat[105.000000] = 0.809273;
		thc_errstat[110.000000] = 0.569068;
		thc_errstat[115.000000] = 0.629066;
		thc_errstat[120.000000] = 0.417288;
		thc_errstat[125.000000] = 0.355193;
		thc_errstat[130.000000] = 0.311164;
		thc_errstat[135.000000] = 0.271243;
		thc_errstat[140.000000] = 0.335154;
		thc_errstat[145.000000] = 0.284122;
		thc_errstat[150.000000] = 0.410792;
		thc_errstat[20.000000] = 0.313362;
		thc_errstat[25.000000] = 0.385279;
		thc_errstat[30.000000] = 0.412645;
		thc_errstat[35.000000] = 0.479995;
		thc_errstat[40.000000] = 0.560585;
		thc_errstat[45.000000] = 0.321229;
		thc_errstat[50.000000] = 0.926392;
		thc_errstat[55.000000] = 0.452110;
		thc_errstat[60.000000] = 0.654761;
		thc_errstat[65.000000] = 0.658725;
		thc_errstat[70.000000] = 0.568901;
		thc_errstat[75.000000] = 0.887975;
		thc_errstat[80.000000] = 0.714488;
		thc_errstat[85.000000] = 1.904372;
		thc_errstat[90.000000] = 0.536561;
		thc_errstat[95.000000] = 1.068636;

	}

}

