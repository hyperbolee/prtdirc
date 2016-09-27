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
	double *shifts;
	ThetaCorr(inreco,1,Form("PID>1000 && abs(diff-%f)<1",diffpeak),shifts);

	for(int i=0; i<15; i++)
		cout << "mcp " << i << "\tshift " << shifts[i] << endl;

	TFile *outfile = new TFile(dir+"../cut/reco_3CS_125.00_cs_avr_spr.root","RECREATE");
	//TTree *outdirc = indirc->CopyTree("");
	//TTree *outhits = inhits->CopyTree("mcp<3");
	TTree *outreco = inreco->CopyTree(Form("abs(diff-%f)<1",diffpeak));
	
	//outhits->Write();
	outfile->Write();
	outfile->Close();
}

/*

TCanvas *canv = new TCanvas("canv","mcp peaks",900,700);
gStyle->SetOptStat(0);
canv->Divide(5,3,0,0);

TSpectrum *spec = new TSpectrum(1);
TTree *reco = (TTree*)_file0->Get("reco");
TH1D *mcp[15];

double mean(0), const(0);

for(int i=0; i<15; i++){
canv->cd(i+1);

char *mcpname = Form("mcp%d",i);
mcp[i] = new TH1D(mcpname,mcpname,40,0.75,0.875);
reco->Project(mcpname,"theta",Form("mcp==%d",i));

if(mcp[i]->GetEntries() < 10) continue;

spec->Search(mcp[i],2,"nodraw");
mean = spec->GetPositionX()[0];
mcp[i]->Fit("gaus","Q","",mean-0.02,mean+0.02);
mcp[i]->Draw();
}

*/
