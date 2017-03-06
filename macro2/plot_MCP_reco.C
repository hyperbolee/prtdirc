#include "../analysis.C"

void plot_MCP_reco(TString infile, TString type = "sim")
{
//TString infile = _file0->GetName();
//TString type = "sim";
TString save = "mcp_shift/";

double track(0);
TChain *reco = new TChain("reco");
TChain *dirc = new TChain("dirc");
reco->Add(infile);
dirc->Add(infile);
dirc->SetBranchAddress("theta",&track);
dirc->GetEntry(0);
	
double gap = 0.01; // gap between pad/frame & pad/pad
double xs = (1-6*gap)/5; // x step
double ys = (1-4*gap)/3; // y step
gStyle->SetOptFit(1);
//int colors[] = {kRed, kRed+1, kRed+2, kBlue, kBlue+1, kBlue+2, kGray, kGray+1, kGray+2, kGreen, kGreen+1, kGreen+2, kMagenta, kMagenta+1, kMagenta+2}

TString cut = "abs(diff)<1";
int bins = 120;
int PID = 2212;
double trueang = (PID>1000) ? 0.816760 : 0.824869; // 7GeV prot or pion
int entries = reco->GetEntries(Form("PID==%d && %s",PID,cut.Data()));


// print shift info to files
ofstream shifts;
shifts.open(Form("shifts_%d.txt",PID),ofstream::out | ofstream::app);
//shifts << "noshift\tshifted\tdiff" << endl;

TLine line[17];

TCanvas *canv1 = new TCanvas("canv1","canv1",1600,1200);
TSpectrum *spec = new TSpectrum(10);
TPad *pad[15];
TH1D *hist[16];
TH1D *time[15];
hist[15] = new TH1D("MCP_sum","MCP_sum",bins,0.6,1);

for(int r=0; r<3; r++){
for(int c=0; c<5; c++){
canv1->cd();
int id = r+3*c;				
double x1 = (c+1)*gap + c*xs;
double x2 = x1 + xs;
double y1 = (r+1)*gap + r*ys;
double y2 = y1 + ys;
pad[id] = new TPad(Form("pad_%d",id),Form("pad_%d",id),x1,y1,x2,y2);
pad[id]->SetFillColor(kGray);
pad[id]->SetBorderSize(2);
pad[id]->Draw();
pad[id]->cd();

double per = double(reco->GetEntries(Form("PID==%d && mcp==%d && %s",PID,id, cut.Data())))/entries;
//cout << "mcp " << id << ": " << per << endl;

hist[id] = new TH1D(Form("th_prot%d",id),Form("%s MCP %d, PID %d track %.2f",type.Data(),id,PID,track),bins,0.6,1);
time[id] = new TH1D(Form("tm_%d",id),Form("MCP %d time",id),200,-5,5);

reco->Draw(Form("theta>>th_prot%d",id),Form("PID==%d && mcp==%d && %s",PID,id,cut.Data()));

if(per>0.001){

spec->Search(hist[id]);
double meanprot = spec->GetPositionX()[0];
double shiftprot = meanprot - trueang;

reco->Draw(Form("theta-%f>>th_prot%d",shiftprot,id),Form("PID==%d && mcp==%d && %s",PID,id,cut.Data()));
spec->Search(hist[id]);
hist[15]->Add(hist[id]);
shifts << Form("%d\t%.2f\t%d\t%f\t%f\t%f",PID,track,id,meanprot,spec->GetPositionX()[0],shiftprot) << endl;

line[id].SetLineColor(kGreen);
line[id].SetLineWidth(2);
line[id].SetY1(0);
line[id].SetY2(hist[id]->GetMaximum());
line[id].SetX1(trueang);
line[id].SetX2(trueang);
line[id].Draw("same");

pad[id]->SetFillColor(kWhite);
}
}
}
shifts.close();
canv1->SaveAs(save+Form("mcp_%d_%.2f_shifted.png",PID,track));

TF1 *fitorg = new TF1("fitorg","gaus+pol0(3)");
fitorg->SetParLimits(3,0,20000);
TF1 *fitsft = new TF1("fitsft","gaus+pol0(3)");
fitsft->SetParLimits(3,0,20000);

TCanvas *c1 = new TCanvas();
int id = 15;
hist[15]->SetTitle(Form("%s MCP shifted, PID %d track %.2f",type.Data(),PID,track));
hist[15]->Draw();
line[id].SetLineColor(kGreen);
line[id].SetLineWidth(2);
line[id].SetY1(0);
line[id].SetY2(hist[id]->GetMaximum());
line[id].SetX1(trueang);
line[id].SetX2(trueang);
line[id].Draw("same");

fitsft->SetParameters(hist[id]->GetMaximum(),trueang,.01,100);
hist[15]->Fit("fitsft","Q","",trueang-0.03,trueang+0.03);
c1->Print(save+Form("theta_%s_%d_%.2f_shifted.png",type.Data(),PID,track));

TCanvas *c2 = new TCanvas();
reco->Draw(Form("theta>>tmp(%d,0.6,1)",bins),Form("PID==%d && %s",PID,cut.Data()));
id = 16;
line[id].SetLineColor(kGreen);
line[id].SetLineWidth(2);
line[id].SetY1(0);
line[id].SetY2(tmp->GetMaximum());
line[id].SetX1(trueang);
line[id].SetX2(trueang);
line[id].Draw("same");

fitorg->SetParameters(tmp->GetMaximum(),trueang,.01,100);
tmp->Fit("fitorg","Q","",trueang-0.03,trueang+0.03);
tmp->SetTitle(Form("%s MCP no shift, PID %d track %.2f",type.Data(),PID,track));
c2->Print(save+Form("theta_%s_%d_%.2f_noshift.png",type.Data(),PID,track));

}

