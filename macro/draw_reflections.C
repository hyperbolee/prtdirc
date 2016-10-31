void draw_reflections(TString infile)
{
	gStyle->SetOptStat(0);
	
	TChain *data = new TChain("data");
	data->Add(infile);

	
	TH2D *direct = new TH2D("d","d",250,-50,200,200,-100,100);
	TH2D *left = new TH2D("l","l",250,-50,200,200,-100,100);
	TH2D *bottom = new TH2D("b","b",250,-50,200,200,-100,100);
   	TH2D *right = new TH2D("r","r",250,-50,200,200,-100,100);
	right->SetTitle(0);
	

	data->Project("r","fHitArray.fGlobalPos.y():fHitArray.fGlobalPos.x()","fHitArray.fPathInPrizm==4");
	data->Project("b","fHitArray.fGlobalPos.y():fHitArray.fGlobalPos.x()","fHitArray.fPathInPrizm==3");
	data->Project("l","fHitArray.fGlobalPos.y():fHitArray.fGlobalPos.x()","fHitArray.fPathInPrizm==2");
	data->Project("d","fHitArray.fGlobalPos.y():fHitArray.fGlobalPos.x()","fHitArray.fPathInPrizm==0");

	direct->SetMarkerColor(kGray+1);
	left->SetMarkerColor(kGreen+2);
	bottom->SetMarkerColor(kBlue);
	right->SetMarkerColor(kMagenta+2);

	TCanvas *canv = new TCanvas();
	right->Draw();
	bottom->Draw("same");
	left->Draw("same");
	direct->Draw("same");
}
