// Use MCP shift values from mcp_shift.C
// macro and apply to data to see if these
// values are reasonable to use for both
// *fingers crossed*

#include "../analysis.C"
#include "../meanShift.C"

void mcp_data_shift()
{
	int pid(0);
	double track(0);
	double trueang(0), bfang(0), afang(0);
	//TFile outfile("data_shift.root","recreate");
	
	
	// grab files from data directory
	// TString datadir = "data/151/reco/cs/";
	// TSystemDirectory dir(datadir,datadir);
	// TList *files = dir.GetListOfFiles();
	// TSystemFile *file;
	// TString fname;
	// TIter next(files);

	
}
