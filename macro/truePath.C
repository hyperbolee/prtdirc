

truePath(TString infile, TString runtype="full")
{
	gErrorIgnoreLevel = kWarning; // ignore 'Info in...' messages
	gStyle->SetOptStat(0);   // remove stats box
	TGaxis::SetMaxDigits(4); // put axis in scientific notation

	TFile *f = TFile::Open(infile);
	TTree *t = (TTree*)f->Get("reco"); //Lee's Tree
	TTree *d = (TTree*)f->Get("dirc"); //Roman's Tree

	// set value of lens and alpha from dirc tree
	int lens(0);
	double angle(0);
	d->SetBranchAddress("lens",&lens);
	d->SetBranchAddress("theta",&angle);
	d->GetEntry(0);
	cout << angle << endl;

	char *var = "diff";
	int bins = 100;
	double min = -5;
	double max = 5;
	// full histogram, no cuts
	TH1D *diff_full = new TH1D("diff_full","diff_full",bins,min,max);
	t->Project("diff_full",var);
	diff_full->SetTitle(Form("%.2f deg, lens %d, %s LUT",angle,lens,(char*)runtype));
	diff_full->GetXaxis()->SetTitle("[ns]");
	diff_full->GetYaxis()->SetRangeUser(0,1.15*diff_full->GetMaximum());

	// differing path in simulation and LUT
	TH1D *diff_bg = new TH1D("diff_bg","diff_bg",bins,min,max);
	if(runtype=="full") t->Project("diff_bg",var,"nref!=LUTnref || path!=LUTpath");
	else t->Project("diff_bg",var,"nref!=LUTnref");
	diff_bg->SetLineColor(kGreen);

	// agreeance between LUT and sim
	// if using average LUT, don't include path cut
	TH1D *diff_true = new TH1D("diff_true","diff_true",bins,min,max);
	if(runtype=="full") t->Project("diff_true",var,"nref==LUTnref && path==LUTpath");
	else  t->Project("diff_true",var,"nref==LUTnref");
	diff_true->SetLineColor(kRed);

	TCanvas *c1 = new TCanvas();
	diff_full->Draw();
	diff_bg->Draw("same");
	diff_true->Draw("same");

	c1->Print(Form("../studies/true_paths/tp_%.2f_%s.png",angle,(char*)runtype));
	c1->Print(Form("../studies/true_paths/C/tp_%.2f_%s.C",angle,(char*)runtype));
}
