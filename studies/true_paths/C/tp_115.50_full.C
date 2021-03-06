{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Mar  8 14:19:11 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-6.25,-83933.48,6.25,755401.2);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *diff_full = new TH1D("diff_full","115.50 deg, lens 3, full LUT",100,-5,5);
   diff_full->SetBinContent(17,1);
   diff_full->SetBinContent(18,1);
   diff_full->SetBinContent(19,6);
   diff_full->SetBinContent(20,5);
   diff_full->SetBinContent(21,37);
   diff_full->SetBinContent(22,89);
   diff_full->SetBinContent(23,208);
   diff_full->SetBinContent(24,451);
   diff_full->SetBinContent(25,1015);
   diff_full->SetBinContent(26,1801);
   diff_full->SetBinContent(27,2986);
   diff_full->SetBinContent(28,4495);
   diff_full->SetBinContent(29,7012);
   diff_full->SetBinContent(30,10276);
   diff_full->SetBinContent(31,13796);
   diff_full->SetBinContent(32,18401);
   diff_full->SetBinContent(33,24414);
   diff_full->SetBinContent(34,30773);
   diff_full->SetBinContent(35,37744);
   diff_full->SetBinContent(36,45942);
   diff_full->SetBinContent(37,53794);
   diff_full->SetBinContent(38,61522);
   diff_full->SetBinContent(39,69320);
   diff_full->SetBinContent(40,79597);
   diff_full->SetBinContent(41,92453);
   diff_full->SetBinContent(42,108374);
   diff_full->SetBinContent(43,126009);
   diff_full->SetBinContent(44,151631);
   diff_full->SetBinContent(45,180894);
   diff_full->SetBinContent(46,224459);
   diff_full->SetBinContent(47,278598);
   diff_full->SetBinContent(48,357351);
   diff_full->SetBinContent(49,446920);
   diff_full->SetBinContent(50,531197);
   diff_full->SetBinContent(51,583885);
   diff_full->SetBinContent(52,570026);
   diff_full->SetBinContent(53,507231);
   diff_full->SetBinContent(54,416741);
   diff_full->SetBinContent(55,323365);
   diff_full->SetBinContent(56,255252);
   diff_full->SetBinContent(57,211476);
   diff_full->SetBinContent(58,187740);
   diff_full->SetBinContent(59,178706);
   diff_full->SetBinContent(60,176882);
   diff_full->SetBinContent(61,173272);
   diff_full->SetBinContent(62,169703);
   diff_full->SetBinContent(63,162406);
   diff_full->SetBinContent(64,148548);
   diff_full->SetBinContent(65,133295);
   diff_full->SetBinContent(66,116389);
   diff_full->SetBinContent(67,101896);
   diff_full->SetBinContent(68,87480);
   diff_full->SetBinContent(69,75963);
   diff_full->SetBinContent(70,67480);
   diff_full->SetBinContent(71,59522);
   diff_full->SetBinContent(72,52343);
   diff_full->SetBinContent(73,46913);
   diff_full->SetBinContent(74,41268);
   diff_full->SetBinContent(75,35236);
   diff_full->SetBinContent(76,30189);
   diff_full->SetBinContent(77,25593);
   diff_full->SetBinContent(78,22650);
   diff_full->SetBinContent(79,20603);
   diff_full->SetBinContent(80,18670);
   diff_full->SetBinContent(81,17874);
   diff_full->SetBinContent(82,16973);
   diff_full->SetBinContent(83,16037);
   diff_full->SetBinContent(84,15211);
   diff_full->SetBinContent(85,14917);
   diff_full->SetBinContent(86,13663);
   diff_full->SetBinContent(87,13262);
   diff_full->SetBinContent(88,12578);
   diff_full->SetBinContent(89,11298);
   diff_full->SetBinContent(90,10665);
   diff_full->SetBinContent(91,9952);
   diff_full->SetBinContent(92,9638);
   diff_full->SetBinContent(93,8650);
   diff_full->SetBinContent(94,7913);
   diff_full->SetBinContent(95,6953);
   diff_full->SetBinContent(96,6352);
   diff_full->SetBinContent(97,5932);
   diff_full->SetBinContent(98,5333);
   diff_full->SetBinContent(99,5183);
   diff_full->SetBinContent(100,5567);
   diff_full->SetMinimum(0);
   diff_full->SetMaximum(671467.8);
   diff_full->SetEntries(8176246);
   diff_full->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diff_full->SetLineColor(ci);
   diff_full->GetXaxis()->SetTitle("[ns]");
   diff_full->GetXaxis()->SetLabelFont(42);
   diff_full->GetXaxis()->SetLabelSize(0.035);
   diff_full->GetXaxis()->SetTitleSize(0.035);
   diff_full->GetXaxis()->SetTitleFont(42);
   diff_full->GetYaxis()->SetLabelFont(42);
   diff_full->GetYaxis()->SetLabelSize(0.035);
   diff_full->GetYaxis()->SetTitleSize(0.035);
   diff_full->GetYaxis()->SetTitleFont(42);
   diff_full->GetZaxis()->SetLabelFont(42);
   diff_full->GetZaxis()->SetLabelSize(0.035);
   diff_full->GetZaxis()->SetTitleSize(0.035);
   diff_full->GetZaxis()->SetTitleFont(42);
   diff_full->Draw("");
   
   TH1D *diff_bg = new TH1D("diff_bg","diff_bg",100,-5,5);
   diff_bg->SetBinContent(17,1);
   diff_bg->SetBinContent(18,1);
   diff_bg->SetBinContent(19,6);
   diff_bg->SetBinContent(20,5);
   diff_bg->SetBinContent(21,37);
   diff_bg->SetBinContent(22,89);
   diff_bg->SetBinContent(23,208);
   diff_bg->SetBinContent(24,451);
   diff_bg->SetBinContent(25,1015);
   diff_bg->SetBinContent(26,1801);
   diff_bg->SetBinContent(27,2986);
   diff_bg->SetBinContent(28,4495);
   diff_bg->SetBinContent(29,7012);
   diff_bg->SetBinContent(30,10276);
   diff_bg->SetBinContent(31,13796);
   diff_bg->SetBinContent(32,18401);
   diff_bg->SetBinContent(33,24414);
   diff_bg->SetBinContent(34,30773);
   diff_bg->SetBinContent(35,37744);
   diff_bg->SetBinContent(36,45942);
   diff_bg->SetBinContent(37,53794);
   diff_bg->SetBinContent(38,61520);
   diff_bg->SetBinContent(39,69320);
   diff_bg->SetBinContent(40,79597);
   diff_bg->SetBinContent(41,92438);
   diff_bg->SetBinContent(42,108306);
   diff_bg->SetBinContent(43,125526);
   diff_bg->SetBinContent(44,149701);
   diff_bg->SetBinContent(45,173963);
   diff_bg->SetBinContent(46,202724);
   diff_bg->SetBinContent(47,228480);
   diff_bg->SetBinContent(48,256410);
   diff_bg->SetBinContent(49,286389);
   diff_bg->SetBinContent(50,326507);
   diff_bg->SetBinContent(51,368625);
   diff_bg->SetBinContent(52,388701);
   diff_bg->SetBinContent(53,382465);
   diff_bg->SetBinContent(54,346828);
   diff_bg->SetBinContent(55,290812);
   diff_bg->SetBinContent(56,243242);
   diff_bg->SetBinContent(57,207531);
   diff_bg->SetBinContent(58,186481);
   diff_bg->SetBinContent(59,178322);
   diff_bg->SetBinContent(60,176760);
   diff_bg->SetBinContent(61,173239);
   diff_bg->SetBinContent(62,169689);
   diff_bg->SetBinContent(63,162403);
   diff_bg->SetBinContent(64,148536);
   diff_bg->SetBinContent(65,133291);
   diff_bg->SetBinContent(66,116388);
   diff_bg->SetBinContent(67,101896);
   diff_bg->SetBinContent(68,87480);
   diff_bg->SetBinContent(69,75963);
   diff_bg->SetBinContent(70,67471);
   diff_bg->SetBinContent(71,59517);
   diff_bg->SetBinContent(72,52343);
   diff_bg->SetBinContent(73,46913);
   diff_bg->SetBinContent(74,41268);
   diff_bg->SetBinContent(75,35236);
   diff_bg->SetBinContent(76,30186);
   diff_bg->SetBinContent(77,25593);
   diff_bg->SetBinContent(78,22650);
   diff_bg->SetBinContent(79,20603);
   diff_bg->SetBinContent(80,18670);
   diff_bg->SetBinContent(81,17874);
   diff_bg->SetBinContent(82,16973);
   diff_bg->SetBinContent(83,16037);
   diff_bg->SetBinContent(84,15211);
   diff_bg->SetBinContent(85,14917);
   diff_bg->SetBinContent(86,13663);
   diff_bg->SetBinContent(87,13262);
   diff_bg->SetBinContent(88,12578);
   diff_bg->SetBinContent(89,11298);
   diff_bg->SetBinContent(90,10665);
   diff_bg->SetBinContent(91,9952);
   diff_bg->SetBinContent(92,9638);
   diff_bg->SetBinContent(93,8650);
   diff_bg->SetBinContent(94,7913);
   diff_bg->SetBinContent(95,6953);
   diff_bg->SetBinContent(96,6352);
   diff_bg->SetBinContent(97,5932);
   diff_bg->SetBinContent(98,5333);
   diff_bg->SetBinContent(99,5183);
   diff_bg->SetBinContent(100,5567);
   diff_bg->SetEntries(6987181);
   diff_bg->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   diff_bg->SetLineColor(ci);
   diff_bg->GetXaxis()->SetLabelFont(42);
   diff_bg->GetXaxis()->SetLabelSize(0.035);
   diff_bg->GetXaxis()->SetTitleSize(0.035);
   diff_bg->GetXaxis()->SetTitleFont(42);
   diff_bg->GetYaxis()->SetLabelFont(42);
   diff_bg->GetYaxis()->SetLabelSize(0.035);
   diff_bg->GetYaxis()->SetTitleSize(0.035);
   diff_bg->GetYaxis()->SetTitleFont(42);
   diff_bg->GetZaxis()->SetLabelFont(42);
   diff_bg->GetZaxis()->SetLabelSize(0.035);
   diff_bg->GetZaxis()->SetTitleSize(0.035);
   diff_bg->GetZaxis()->SetTitleFont(42);
   diff_bg->Draw("same");
   
   TH1D *diff_true = new TH1D("diff_true","diff_true",100,-5,5);
   diff_true->SetBinContent(38,2);
   diff_true->SetBinContent(41,15);
   diff_true->SetBinContent(42,68);
   diff_true->SetBinContent(43,483);
   diff_true->SetBinContent(44,1930);
   diff_true->SetBinContent(45,6931);
   diff_true->SetBinContent(46,21735);
   diff_true->SetBinContent(47,50118);
   diff_true->SetBinContent(48,100941);
   diff_true->SetBinContent(49,160531);
   diff_true->SetBinContent(50,204690);
   diff_true->SetBinContent(51,215260);
   diff_true->SetBinContent(52,181325);
   diff_true->SetBinContent(53,124766);
   diff_true->SetBinContent(54,69913);
   diff_true->SetBinContent(55,32553);
   diff_true->SetBinContent(56,12010);
   diff_true->SetBinContent(57,3945);
   diff_true->SetBinContent(58,1259);
   diff_true->SetBinContent(59,384);
   diff_true->SetBinContent(60,122);
   diff_true->SetBinContent(61,33);
   diff_true->SetBinContent(62,14);
   diff_true->SetBinContent(63,3);
   diff_true->SetBinContent(64,12);
   diff_true->SetBinContent(65,4);
   diff_true->SetBinContent(66,1);
   diff_true->SetBinContent(70,9);
   diff_true->SetBinContent(71,5);
   diff_true->SetBinContent(76,3);
   diff_true->SetEntries(1189065);
   diff_true->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   diff_true->SetLineColor(ci);
   diff_true->GetXaxis()->SetLabelFont(42);
   diff_true->GetXaxis()->SetLabelSize(0.035);
   diff_true->GetXaxis()->SetTitleSize(0.035);
   diff_true->GetXaxis()->SetTitleFont(42);
   diff_true->GetYaxis()->SetLabelFont(42);
   diff_true->GetYaxis()->SetLabelSize(0.035);
   diff_true->GetYaxis()->SetTitleSize(0.035);
   diff_true->GetYaxis()->SetTitleFont(42);
   diff_true->GetZaxis()->SetLabelFont(42);
   diff_true->GetZaxis()->SetLabelSize(0.035);
   diff_true->GetZaxis()->SetTitleSize(0.035);
   diff_true->GetZaxis()->SetTitleFont(42);
   diff_true->Draw("same");
   
   TPaveText *pt = new TPaveText(0.269454,0.9339831,0.730546,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("115.50 deg, lens 3, full LUT");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
