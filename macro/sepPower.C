// Difference of two functions to find intersection
TF1 *pFit;
TF1 *piFit;
double intersect(double *x, double*par) {
   return TMath::Abs(pFit->EvalPar(x,par) - piFit->EvalPar(x,par));
}

void sepPower(TString infile)
{
	TFile *file = TFile::Open(infile);
	TH1D *pSep = (TH1D*)file->Get("Psep");
	TH1D *piSep = (TH1D*)file->Get("Pisep");
	pSep->Draw();
	piSep->Draw("same");

	pFit = pSep->GetFunction("gaus");
	piFit = piSep->GetFunction("gaus");
	pFit->SetLineColor(kMagenta+2);
	piFit->SetLineColor(kMagenta);
	pFit->Draw("same");
	piFit->Draw("same");
	TF1 *diff = new TF1("diff",intersect,-30,30,0);

	double xlo = TMath::Min(pFit->GetParameter(1),piFit->GetParameter(1));
	double xhi = TMath::Max(pFit->GetParameter(1),piFit->GetParameter(1));
	double xint = diff->GetMinimumX(xlo,xhi);
	cout << "xlo [" << xlo << "]" << endl;
	cout << "xhi [" << xhi << "]" << endl;
	cout << "xmin [" << xint << "]" << endl;

	TMarker *m = new TMarker(xint,pFit->Eval(xint),24);
	m->SetMarkerColor(kRed);
	m->SetMarkerSize(3);
	m->Draw();

	double misIdP = pFit->Integral(xint,30)/pFit->Integral(-30,30);
	double misIdPi = piFit->Integral(-30,xint)/piFit->Integral(-30,30);
	cout << "MisID P as Pi: " << 100*misIdP << "%" << endl;
	cout << "MisID Pi as P: " << 100*misIdPi << "%" << endl;
}
