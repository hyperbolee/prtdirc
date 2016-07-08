#include "analysistools.C"

/*
  reprocesses reconstructed data files to apply cuts and calibrations
  so that I don't have to worry about applying them when making plots

  default directory is charge-sharing corrected simulation of 3CS
*/
void recocut( TString dir = "simulation/151/reco/cs/" )
{
	TFile *infile = TFile::Open(dir+"reco_3CS_125.00_cs_avr_spr.root");
	//TTree *indirc = (TTree*)infile->Get("dirc");
	//TTree *inhits = (TTree*)infile->Get("hits");
	TTree *inreco = (TTree*)infile->Get("reco");

	double diffpeak = DiffPeak(inreco);

	TFile *outfile = new TFile(dir+"../cut/reco_3CS_125.00_cs_avr_spr.root","RECREATE");
	//TTree *outdirc = indirc->CopyTree("");
	//TTree *outhits = inhits->CopyTree("mcp<3");
	TTree *outreco = inreco->CopyTree(Form("abs(diff-%f)<1",diffpeak));
	
	//outhits->Write();
	outfile->Write();
	outfile->Close();
}
