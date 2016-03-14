/*
  bgfit.C
  ---------
  macro for fitting combinatorial background
  of reconstructed angle with higher order
  polynomial to (hopefully) find trend

  Written by Lee Allison: Mar. 9, 2016
 */

bgfit(TString infile)
{
	gErrorIgnoreLevel = kWarning; // ignore 'Info in...' messages
	gStyle->SetOptStat(0);   // remove stats box
	TGaxis::SetMaxDigits(4); // put axis in scientific notation

	// open infile and set trees
	TFile *f = TFile::Open(infile);
	TTree *t = (TTree*)f->Get("reco"); //Lee's Tree
	TTree *d = (TTree*)f->Get("dirc"); //Roman's Tree

	// set value of lens and alpha from dirc tree
	int lens(0);
	double angle(0);
	d->SetBranchAddress("lens",&lens);
	d->SetBranchAddress("theta",&angle);
	d->GetEntry(0);

	char *var = "theta";
	char *cut = "nref!=LUTnref || path!=LUTpath";
	int bins = 200;
	double min = 0.6;
	double max = 1.0;

	// full histogram, no cuts
	TH1D *bg = new TH1D("bg","bg",bins,min,max);
	t->Project("bg",var,cut);

	double area = bg->GetIntegral();
	bg->Scale(1/area);

	bg->SetTitle(Form("%.2f deg, lens %d",angle,lens));
	bg->GetXaxis()->SetTitle("#theta_{C} [rad]");
	bg->GetYaxis()->SetRangeUser(0,1.1*bg->GetMaximum());

	bg->Fit("pol6");
	TF1 *fit = bg->GetFunction("pol6");
	double p0 = fit->GetParameter(0);
	double p1 = fit->GetParameter(1);
	double p2 = fit->GetParameter(2);
	double p3 = fit->GetParameter(3);
	double p4 = fit->GetParameter(4);
	double p5 = fit->GetParameter(5);
	double p6 = fit->GetParameter(6);


	TFile *outfile = new TFile(Form("bgfit_%.2f.root",angle),"recreate");
	TTree *btree = new TTree("btree","fit parameters of comb. background");
	btree->Branch("angle",&angle,"angle/D");
	btree->Branch("p0",&p0,"p0/D");
	btree->Branch("p1",&p1,"p1/D");
	btree->Branch("p2",&p2,"p2/D");
	btree->Branch("p3",&p3,"p3/D");
	btree->Branch("p4",&p4,"p4/D");
	btree->Branch("p5",&p5,"p5/D");
	btree->Branch("p6",&p6,"p6/D");

	btree->Fill();
	btree->Write();
	outfile->Write();
	outfile->Close();

	/*TCanvas *c1 = new TCanvas();
	c1->cd();
	bg->Draw();
	c1->Print(Form("../studies/bgfit/bgfit_%.2f.png",angle));
	c1->Print(Form("../studies/bgfit/C/bgfit_%.2f.C",angle));
	*/
}
