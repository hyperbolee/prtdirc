void shiftSim(double track, double &tangle, int pid)
{
	switch(int(track))
	{
	case 130: 
		if(pid==211) tangle += -0.001099;
		if(pid==2212) tangle += -0.002302;
		break;
	case 145: 
		if(pid==211) tangle += -0.000537;
		if(pid==2212) tangle += -0.002049;
		break;
	case 105: 
		if(pid==211) tangle += 0.000756;
		if(pid==2212) tangle += 0.002009;
		break;
	case 140: 
		if(pid==211) tangle += 0.000468;
		if(pid==2212) tangle += -0.002431;
		break;
	case 150: 
		if(pid==211) tangle += -0.000891;
		if(pid==2212) tangle += -0.002459;
		break;
	case 160: 
		if(pid==211) tangle += -0.002392;
		if(pid==2212) tangle += -0.003312;
		break;
	case 120: 
		if(pid==211) tangle += 0.000908;
		if(pid==2212) tangle += 0.000507;
		break;
	case 65: 
		if(pid==211) tangle += 0.001207;
		if(pid==2212) tangle += 0.000867;
		break;
	case 70: 
		if(pid==211) tangle += 0.000511;
		if(pid==2212) tangle += 0.001966;
		break;
	case 80: 
		if(pid==211) tangle += 0.002384;
		if(pid==2212) tangle += 0.001241;
		break;
	case 60: 
		if(pid==211) tangle += 0.000893;
		if(pid==2212) tangle += -0.000249;
		break;
	case 55: 
		if(pid==211) tangle += 0.001005;
		if(pid==2212) tangle += 0.000115;
		break;
	case 40: 
		if(pid==211) tangle += 0.000495;
		if(pid==2212) tangle += -0.001302;
		break;
	case 125: 
		if(pid==211) tangle += 0.001030;
		if(pid==2212) tangle += 0.000550;
		break;
	case 75: 
		if(pid==211) tangle += 0.002013;
		if(pid==2212) tangle += 0.001885;
		break;
	case 35: 
		if(pid==211) tangle += -0.000599;
		if(pid==2212) tangle += -0.001830;
		break;
	case 85: 
		if(pid==211) tangle += 0.000713;
		if(pid==2212) tangle += 0.000441;
		break;
	case 100: 
		if(pid==211) tangle += 0.002236;
		if(pid==2212) tangle += 0.001257;
		break;
	case 30: 
		if(pid==211) tangle += -0.001210;
		if(pid==2212) tangle += -0.002312;
		break;
	case 135: 
		if(pid==211) tangle += -0.000308;
		if(pid==2212) tangle += -0.001816;
		break;
	case 45: 
		if(pid==211) tangle += -0.000651;
		if(pid==2212) tangle += -0.001528;
		break;
	case 110: 
		if(pid==211) tangle += 0.000851;
		if(pid==2212) tangle += 0.001050;
		break;
	case 20: 
		if(pid==211) tangle += -0.002366;
		if(pid==2212) tangle += -0.003067;
		break;
	case 25: 
		if(pid==211) tangle += -0.000287;
		if(pid==2212) tangle += -0.002167;
		break;
	case 115: 
		if(pid==211) tangle += 0.000613;
		if(pid==2212) tangle += 0.001156;
		break;
	case 95: 
		if(pid==211) tangle += 0.002174;
		if(pid==2212) tangle += 0.002462;
		break;
	case 50: 
		if(pid==211) tangle += -0.001291;
		if(pid==2212) tangle += -0.001627;
		break;
	case 90: 
		if(pid==211) tangle += 0.002201;
		if(pid==2212) tangle += 0.000666;
		break;
	}

}

void shiftData(double track, double &tangle, int pid)
{
	switch(int(track))
	{
	case 130: 
		if(pid==211) tangle += 0.003282;
		if(pid==2212) tangle += 0.001451;
		break;
	case 145: 
		if(pid==211) tangle += 0.006805;
		if(pid==2212) tangle += 0.004847;
		break;
	case 105: 
		if(pid==211) tangle += -0.000713;
		if(pid==2212) tangle += -0.002832;
		break;
	case 140: 
		if(pid==211) tangle += 0.005492;
		if(pid==2212) tangle += 0.002431;
		break;
	case 150: 
		if(pid==211) tangle += 0.005978;
		if(pid==2212) tangle += 0.005344;
		break;
	case 160: 
		if(pid==211) tangle += 0.008459;
		if(pid==2212) tangle += 0.008456;
		break;
	case 120: 
		if(pid==211) tangle += 0.002411;
		if(pid==2212) tangle += 0.002029;
		break;
	case 65: 
		if(pid==211) tangle += -0.005367;
		if(pid==2212) tangle += -0.004535;
		break;
	case 70: 
		if(pid==211) tangle += -0.004642;
		if(pid==2212) tangle += -0.004934;
		break;
	case 80: 
		if(pid==211) tangle += -0.006157;
		if(pid==2212) tangle += -0.006880;
		break;
	case 60: 
		if(pid==211) tangle += -0.002648;
		if(pid==2212) tangle += -0.003298;
		break;
	case 55: 
		if(pid==211) tangle += -0.003737;
		if(pid==2212) tangle += -0.003328;
		break;
	case 40: 
		if(pid==211) tangle += 0.001105;
		if(pid==2212) tangle += -0.000870;
		break;
	case 125: 
		if(pid==211) tangle += 0.002429;
		if(pid==2212) tangle += 0.002151;
		break;
	case 75: 
		if(pid==211) tangle += -0.005764;
		if(pid==2212) tangle += -0.006783;
		break;
	case 35: 
		if(pid==211) tangle += 0.001703;
		if(pid==2212) tangle += 0.001478;
		break;
	case 85: 
		if(pid==211) tangle += -0.008438;
		if(pid==2212) tangle += -0.008896;
		break;
	case 100: 
		if(pid==211) tangle += -0.000494;
		if(pid==2212) tangle += -0.000397;
		break;
	case 30: 
		if(pid==211) tangle += 0.001807;
		if(pid==2212) tangle += 0.002996;
		break;
	case 135: 
		if(pid==211) tangle += 0.003859;
		if(pid==2212) tangle += 0.001767;
		break;
	case 45: 
		if(pid==211) tangle += -0.002543;
		if(pid==2212) tangle += -0.004303;
		break;
	case 110: 
		if(pid==211) tangle += 0.001545;
		if(pid==2212) tangle += 0.000001;
		break;
	case 20: 
		if(pid==211) tangle += 0.002805;
		if(pid==2212) tangle += 0.005074;
		break;
	case 25: 
		if(pid==211) tangle += 0.004251;
		if(pid==2212) tangle += 0.005252;
		break;
	case 115: 
		if(pid==211) tangle += 0.000066;
		if(pid==2212) tangle += -0.000359;
		break;
	case 95: 
		if(pid==211) tangle += -0.002639;
		if(pid==2212) tangle += -0.004159;
		break;
	case 50: 
		if(pid==211) tangle += -0.004447;
		if(pid==2212) tangle += -0.003021;
		break;
	case 90: 
		if(pid==211) tangle += -0.004001;
		if(pid==2212) tangle += -0.005913;
		break;
	}
}

double shiftMCPs(double track, int PID, int mcpid)
{
	if( abs(track-100.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 6: return -0.003206;
			case 7: return 0.004519;
			case 9: return -0.001397;
			case 10: return -0.003287;
			case 11: return -0.001224;
			case 13: return -0.003172;
			}
		case 2212:

			switch(mcpid)
			{
			case 6: return -0.002896;
			case 8: return -0.001796;
			case 9: return 0.000277;
			case 10: return -0.004468;
			case 12: return -0.000556;
			case 14: return -0.001162;
			}
		}
	}
	if( abs(track-105.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 7: return -0.001983;
			case 8: return -0.004515;
			case 9: return 0.000746;
			case 10: return 0.002167;
			case 11: return 0.000667;
			case 12: return -0.002265;
			}
		case 2212:

			switch(mcpid)
			{
			case 7: return -0.005223;
			case 8: return -0.003505;
			case 9: return -0.002024;
			case 11: return -0.001507;
			case 12: return 0.071499;
			case 13: return 0.001479;
			case 14: return 0.000714;
			}
		}
	}
	if( abs(track-110.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 3: return -0.001353;
			case 4: return -0.003714;
			case 5: return 0.000008;
			case 6: return -0.000233;
			case 7: return -0.000546;
			case 8: return -0.002320;
			case 9: return -0.002361;
			case 13: return -0.000759;
			}
		case 2212:

			switch(mcpid)
			{
			case 4: return 0.003904;
			case 5: return 0.001823;
			case 6: return 0.000888;
			case 8: return -0.001830;
			case 9: return -0.001472;
			case 11: return -0.000969;
			case 13: return -0.001636;
			}
		}
	}
	if( abs(track-115.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 3: return -0.000017;
			case 5: return 0.000939;
			case 6: return -0.000366;
			case 7: return 0.001046;
			case 8: return 0.000936;
			case 10: return 0.000821;
			}
		case 2212:

			switch(mcpid)
			{
			case 5: return -0.002854;
			case 6: return -0.005299;
			case 7: return -0.002542;
			case 8: return -0.004405;
			case 10: return 0.001432;
			case 11: return 0.001948;
			case 13: return -0.100371;
			}
		}
	}
	if( abs(track-120.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.006931;
			case 2: return 0.000282;
			case 3: return -0.001116;
			case 4: return -0.003167;
			case 6: return 0.001114;
			case 10: return -0.072851;
			}
		case 2212:

			switch(mcpid)
			{
			case 3: return 0.002017;
			case 6: return -0.001302;
			case 10: return -0.071443;
			}
		}
	}
	if( abs(track-125.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.000909;
			case 2: return -0.000732;
			case 3: return -0.001508;
			case 4: return -0.003577;
			case 5: return 0.000672;
			case 6: return 0.001366;
			case 8: return -0.001464;
			case 10: return -0.064003;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.000453;
			case 1: return -0.002924;
			case 2: return -0.001157;
			case 3: return 0.000402;
			case 4: return -0.000161;
			case 5: return 0.000888;
			case 6: return 0.002188;
			case 8: return 0.001073;
			case 10: return -0.000394;
			}
		}
	}
	if( abs(track-130.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.002211;
			case 1: return 0.002731;
			case 2: return 0.004413;
			case 3: return 0.002344;
			case 4: return 0.001788;
			case 5: return 0.001768;
			}
		case 2212:

			switch(mcpid)
			{
			case 1: return 0.005381;
			case 2: return 0.007186;
			case 3: return 0.003631;
			case 4: return 0.001845;
			case 5: return 0.003351;
			case 10: return -0.001325;
			}
		}
	}
	if( abs(track-135.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.001035;
			case 1: return 0.001326;
			case 2: return 0.000612;
			case 3: return 0.003229;
			case 5: return 0.000320;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.007245;
			case 1: return -0.001015;
			case 2: return 0.005805;
			case 4: return -0.000172;
			case 5: return 0.000038;
			}
		}
	}
	if( abs(track-140.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.000566;
			case 1: return 0.002997;
			case 2: return -0.001148;
			case 4: return -0.014451;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.005625;
			case 1: return 0.005682;
			case 2: return 0.003718;
			case 4: return -0.007018;
			}
		}
	}
	if( abs(track-145.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.003417;
			case 1: return -0.000112;
			case 2: return 0.002920;
			case 3: return 0.002658;
			case 4: return 0.005015;
			case 5: return 0.002091;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.005844;
			case 2: return 0.004851;
			case 4: return 0.002448;
			case 5: return 0.002937;
			}
		}
	}
	if( abs(track-150.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.001849;
			case 1: return 0.004082;
			case 2: return 0.001776;
			case 4: return 0.006570;
			case 5: return 0.002775;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.004778;
			case 2: return 0.006082;
			case 3: return 0.002639;
			case 5: return 0.001021;
			}
		}
	}
	if( abs(track-155.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.000497;
			case 2: return 0.002348;
			case 3: return 0.003816;
			case 4: return 0.002700;
			case 5: return 0.003436;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.006270;
			case 2: return 0.008795;
			case 3: return 0.004334;
			case 4: return 0.004344;
			case 5: return 0.004169;
			}
		}
	}

	if( abs(track-55.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 2: return -0.003810;
			case 3: return -0.000729;
			case 4: return -0.001236;
			case 5: return -0.000046;
			case 8: return -0.001703;
			}
		case 2212:

			switch(mcpid)
			{
			case 1: return -0.003276;
			case 2: return -0.001939;
			case 3: return 0.001280;
			case 4: return 0.001939;
			case 5: return 0.000856;
			case 8: return 0.000864;
			}
		}
	}
	if( abs(track-60.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 3: return -0.001007;
			case 4: return -0.001436;
			case 5: return -0.000658;
			case 6: return 0.000944;
			case 8: return 0.001234;
			case 10: return 0.000719;
			}
		case 2212:

			switch(mcpid)
			{
			case 3: return 0.001659;
			case 4: return 0.001218;
			case 5: return -0.000213;
			case 6: return -0.000415;
			case 7: return -0.000463;
			case 8: return 0.000476;
			}
		}
	}
	if( abs(track-65.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 3: return -0.001755;
			case 4: return 0.001645;
			case 5: return -0.001539;
			case 6: return -0.001171;
			case 10: return 0.000908;
			}
		case 2212:

			switch(mcpid)
			{
			case 5: return -0.002309;
			case 6: return -0.003466;
			case 7: return -0.004677;
			case 10: return 0.001310;
			}
		}
	}
	if( abs(track-70.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 3: return -0.001396;
			case 6: return -0.000261;
			case 7: return -0.000800;
			case 8: return -0.001243;
			case 9: return -0.000147;
			case 10: return -0.002077;
			case 11: return 0.000518;
			}
		case 2212:

			switch(mcpid)
			{
			case 3: return 0.000215;
			case 5: return 0.002620;
			case 6: return -0.000583;
			case 7: return -0.001029;
			case 8: return -0.002019;
			case 9: return 0.000796;
			case 10: return -0.005446;
			case 11: return 0.000520;
			}
		}
	}
	if( abs(track-75.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 6: return -0.003323;
			case 7: return -0.003035;
			case 8: return -0.003295;
			case 10: return 0.000691;
			case 11: return -0.001650;
			}
		case 2212:

			switch(mcpid)
			{
			case 6: return -0.002961;
			case 7: return -0.001584;
			case 10: return -0.001466;
			case 11: return -0.001284;
			}
		}
	}
	if( abs(track-80.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 6: return -0.003036;
			case 8: return -0.001679;
			case 9: return -0.001750;
			case 10: return -0.001884;
			case 11: return -0.002536;
			case 12: return -0.001135;
			}
		case 2212:

			switch(mcpid)
			{
			case 6: return -0.001555;
			case 8: return -0.001953;
			case 9: return -0.001881;
			case 10: return -0.001251;
			case 11: return -0.001429;
			case 12: return 0.000027;
			case 13: return -0.002719;
			case 14: return 0.000641;
			}
		}
	}
	if( abs(track-85.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 9: return -0.001694;
			case 10: return -0.002278;
			case 11: return -0.000965;
			case 12: return 0.003545;
			case 13: return 0.000445;
			case 14: return 0.004214;
			}
		case 2212:

			switch(mcpid)
			{
			case 9: return -0.002238;
			case 10: return -0.000617;
			case 11: return -0.004344;
			case 12: return 0.115895;
			case 13: return -0.000595;
			case 14: return 0.002483;
			}
		}
	}
	if( abs(track-90.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 9: return 0.001076;
			case 10: return -0.009765;
			case 11: return 0.001566;
			case 13: return -0.003266;
			case 14: return -0.002347;
			}
		case 2212:

			switch(mcpid)
			{
			case 9: return -0.002594;
			case 10: return 0.002655;
			case 12: return -0.000621;
			case 13: return -0.002001;
			case 14: return -0.000928;
			}
		}
	}
	if( abs(track-95.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 9: return -0.000823;
			case 10: return 0.000380;
			case 11: return 0.000502;
			case 13: return -0.061110;
			case 14: return -0.003383;
			}
		case 2212:

			switch(mcpid)
			{
			case 9: return -0.001365;
			case 10: return 0.006276;
			case 12: return -0.036434;
			case 13: return -0.001800;
			case 14: return -0.003336;
			}
		}
	}
	if( abs(track-20.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 2: return 0.002030;
			case 3: return 0.002289;
			case 4: return -0.000091;
			case 7: return 0.003802;
			case 8: return 0.002852;
			case 10: return 0.002331;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.004796;
			case 2: return 0.005275;
			case 4: return 0.002352;
			case 6: return 0.001272;
			case 7: return 0.007092;
			case 8: return 0.003615;
			}
		}
	}
	if( abs(track-25.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.001184;
			case 2: return 0.001832;
			case 3: return 0.003131;
			case 5: return 0.002859;
			case 6: return 0.007634;
			case 7: return 0.006987;
			case 8: return 0.002884;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.005661;
			case 3: return 0.003401;
			case 4: return 0.003515;
			case 5: return 0.003488;
			case 7: return -0.001914;
			}
		}
	}
	if( abs(track-30.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.002727;
			case 1: return 0.003684;
			case 2: return 0.001214;
			case 3: return 0.001470;
			case 4: return 0.001896;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.003775;
			case 2: return 0.004504;
			case 3: return 0.002402;
			case 4: return 0.007134;
			case 5: return 0.001169;
			}
		}
	}
	if( abs(track-35.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.003244;
			case 1: return 0.000068;
			case 2: return 0.003403;
			case 3: return 0.002780;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.002342;
			case 1: return 0.000118;
			case 2: return 0.003365;
			case 5: return 0.003202;
			}
		}
	}
	if( abs(track-40.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.000940;
			case 1: return 0.002432;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.004998;
			case 1: return 0.002747;
			case 2: return 0.003085;
			}
		}
	}
	if( abs(track-45.00)<1 )
	{
		switch(PID)
		{
		case 211:

			switch(mcpid)
			{
			case 0: return 0.000415;
			case 1: return 0.002054;
			case 2: return 0.000047;
			}
		case 2212:

			switch(mcpid)
			{
			case 0: return 0.003650;
			case 1: return 0.001532;
			case 2: return 0.005192;
			}
		}
	}
	
	return 0;
	
}

double meanShift(bool simulation, double track, double &tangle, int pid, int mcpid)
{
	//cout << "before :" << tangle << endl;
	//if(simulation) shiftSim(track, tangle, pid);
	//else shiftData(track, tangle, pid);

	return shiftMCPs(track,pid,mcpid);

	//cout << "after : " << tangle << endl;
}
