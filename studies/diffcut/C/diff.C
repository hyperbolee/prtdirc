{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Feb 10 22:53:42 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",130,107,700,502);
   c1->Range(-9.750003,-0.5000001,177.75,4.5);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TGraph *graph = new TGraph(26);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   graph->SetMarkerColor(4);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,20,0.6044518635);
   graph->SetPoint(1,25,0.5697240603);
   graph->SetPoint(2,30,0.4880899141);
   graph->SetPoint(3,35,0.448985528);
   graph->SetPoint(4,39.93534356,0.4348158533);
   graph->SetPoint(5,45,0.4333219383);
   graph->SetPoint(6,50,0.4711081184);
   graph->SetPoint(7,55,0.496303618);
   graph->SetPoint(8,60,0.6397626315);
   graph->SetPoint(9,65,0.6414258865);
   graph->SetPoint(10,70,0.7246916824);
   graph->SetPoint(11,75,0.8851954072);
   graph->SetPoint(12,80,0.8767192644);
   graph->SetPoint(13,85,3.519767494);
   graph->SetPoint(14,90,0.9348269095);
   graph->SetPoint(15,95,0.8864750856);
   graph->SetPoint(16,100,0.8264772962);
   graph->SetPoint(17,105,0.6305448225);
   graph->SetPoint(18,110,0.7473277244);
   graph->SetPoint(19,115,0.3952652372);
   graph->SetPoint(20,120,0.6120161198);
   graph->SetPoint(21,125,0.4626400584);
   graph->SetPoint(22,130,0.4155010511);
   graph->SetPoint(23,135,0.5455797102);
   graph->SetPoint(24,140,0.5313389164);
   graph->SetPoint(25,145,0.407085638);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,7.5,157.5);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(4);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("bar angle [deg]");
   Graph_Graph1->GetXaxis()->SetRange(2,101);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("#sigma (t_{m}-t_{e}) [ns]");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("APC");
   
   TPaveText *pt = new TPaveText(0.4397126,0.9342405,0.5602874,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
