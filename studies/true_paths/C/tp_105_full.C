{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Mar  5 21:05:48 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-6.25,-51309.3,6.25,461783.7);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *diff_full = new TH1D("diff_full","105 deg, lens 3, full LUT",100,-5,5);
   diff_full->SetBinContent(16,1);
   diff_full->SetBinContent(17,5);
   diff_full->SetBinContent(18,6);
   diff_full->SetBinContent(19,16);
   diff_full->SetBinContent(20,59);
   diff_full->SetBinContent(21,156);
   diff_full->SetBinContent(22,329);
   diff_full->SetBinContent(23,566);
   diff_full->SetBinContent(24,1010);
   diff_full->SetBinContent(25,1635);
   diff_full->SetBinContent(26,2494);
   diff_full->SetBinContent(27,4010);
   diff_full->SetBinContent(28,6306);
   diff_full->SetBinContent(29,9960);
   diff_full->SetBinContent(30,14831);
   diff_full->SetBinContent(31,21119);
   diff_full->SetBinContent(32,28387);
   diff_full->SetBinContent(33,35840);
   diff_full->SetBinContent(34,42932);
   diff_full->SetBinContent(35,51016);
   diff_full->SetBinContent(36,58360);
   diff_full->SetBinContent(37,64936);
   diff_full->SetBinContent(38,73187);
   diff_full->SetBinContent(39,77165);
   diff_full->SetBinContent(40,80315);
   diff_full->SetBinContent(41,83243);
   diff_full->SetBinContent(42,88580);
   diff_full->SetBinContent(43,98214);
   diff_full->SetBinContent(44,113633);
   diff_full->SetBinContent(45,135089);
   diff_full->SetBinContent(46,162414);
   diff_full->SetBinContent(47,190816);
   diff_full->SetBinContent(48,230392);
   diff_full->SetBinContent(49,280397);
   diff_full->SetBinContent(50,331250);
   diff_full->SetBinContent(51,372762);
   diff_full->SetBinContent(52,390928);
   diff_full->SetBinContent(53,381339);
   diff_full->SetBinContent(54,346605);
   diff_full->SetBinContent(55,296951);
   diff_full->SetBinContent(56,242909);
   diff_full->SetBinContent(57,193844);
   diff_full->SetBinContent(58,160295);
   diff_full->SetBinContent(59,135827);
   diff_full->SetBinContent(60,121875);
   diff_full->SetBinContent(61,110599);
   diff_full->SetBinContent(62,101259);
   diff_full->SetBinContent(63,93996);
   diff_full->SetBinContent(64,84202);
   diff_full->SetBinContent(65,74183);
   diff_full->SetBinContent(66,61516);
   diff_full->SetBinContent(67,52086);
   diff_full->SetBinContent(68,43052);
   diff_full->SetBinContent(69,34548);
   diff_full->SetBinContent(70,28579);
   diff_full->SetBinContent(71,23851);
   diff_full->SetBinContent(72,20249);
   diff_full->SetBinContent(73,17691);
   diff_full->SetBinContent(74,15512);
   diff_full->SetBinContent(75,13850);
   diff_full->SetBinContent(76,13712);
   diff_full->SetBinContent(77,11992);
   diff_full->SetBinContent(78,10764);
   diff_full->SetBinContent(79,9744);
   diff_full->SetBinContent(80,9225);
   diff_full->SetBinContent(81,8423);
   diff_full->SetBinContent(82,8111);
   diff_full->SetBinContent(83,7485);
   diff_full->SetBinContent(84,6989);
   diff_full->SetBinContent(85,7161);
   diff_full->SetBinContent(86,7006);
   diff_full->SetBinContent(87,7273);
   diff_full->SetBinContent(88,6863);
   diff_full->SetBinContent(89,6907);
   diff_full->SetBinContent(90,7140);
   diff_full->SetBinContent(91,6951);
   diff_full->SetBinContent(92,6600);
   diff_full->SetBinContent(93,6308);
   diff_full->SetBinContent(94,6582);
   diff_full->SetBinContent(95,6351);
   diff_full->SetBinContent(96,6495);
   diff_full->SetBinContent(97,6839);
   diff_full->SetBinContent(98,6946);
   diff_full->SetBinContent(99,6850);
   diff_full->SetBinContent(100,6546);
   diff_full->SetEntries(5902440);
   diff_full->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diff_full->SetLineColor(ci);
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
   diff_bg->SetBinContent(16,1);
   diff_bg->SetBinContent(17,5);
   diff_bg->SetBinContent(18,6);
   diff_bg->SetBinContent(19,16);
   diff_bg->SetBinContent(20,59);
   diff_bg->SetBinContent(21,156);
   diff_bg->SetBinContent(22,329);
   diff_bg->SetBinContent(23,566);
   diff_bg->SetBinContent(24,1010);
   diff_bg->SetBinContent(25,1635);
   diff_bg->SetBinContent(26,2494);
   diff_bg->SetBinContent(27,4010);
   diff_bg->SetBinContent(28,6306);
   diff_bg->SetBinContent(29,9960);
   diff_bg->SetBinContent(30,14831);
   diff_bg->SetBinContent(31,21119);
   diff_bg->SetBinContent(32,28385);
   diff_bg->SetBinContent(33,35837);
   diff_bg->SetBinContent(34,42932);
   diff_bg->SetBinContent(35,51016);
   diff_bg->SetBinContent(36,58360);
   diff_bg->SetBinContent(37,64936);
   diff_bg->SetBinContent(38,73187);
   diff_bg->SetBinContent(39,77165);
   diff_bg->SetBinContent(40,80315);
   diff_bg->SetBinContent(41,83231);
   diff_bg->SetBinContent(42,88525);
   diff_bg->SetBinContent(43,97957);
   diff_bg->SetBinContent(44,112478);
   diff_bg->SetBinContent(45,130798);
   diff_bg->SetBinContent(46,148951);
   diff_bg->SetBinContent(47,158149);
   diff_bg->SetBinContent(48,166286);
   diff_bg->SetBinContent(49,178815);
   diff_bg->SetBinContent(50,199873);
   diff_bg->SetBinContent(51,234666);
   diff_bg->SetBinContent(52,273683);
   diff_bg->SetBinContent(53,298816);
   diff_bg->SetBinContent(54,299823);
   diff_bg->SetBinContent(55,275222);
   diff_bg->SetBinContent(56,234587);
   diff_bg->SetBinContent(57,191047);
   diff_bg->SetBinContent(58,159430);
   diff_bg->SetBinContent(59,135618);
   diff_bg->SetBinContent(60,121811);
   diff_bg->SetBinContent(61,110577);
   diff_bg->SetBinContent(62,101250);
   diff_bg->SetBinContent(63,93992);
   diff_bg->SetBinContent(64,84202);
   diff_bg->SetBinContent(65,74183);
   diff_bg->SetBinContent(66,61516);
   diff_bg->SetBinContent(67,52086);
   diff_bg->SetBinContent(68,43052);
   diff_bg->SetBinContent(69,34548);
   diff_bg->SetBinContent(70,28579);
   diff_bg->SetBinContent(71,23851);
   diff_bg->SetBinContent(72,20249);
   diff_bg->SetBinContent(73,17691);
   diff_bg->SetBinContent(74,15512);
   diff_bg->SetBinContent(75,13850);
   diff_bg->SetBinContent(76,13712);
   diff_bg->SetBinContent(77,11992);
   diff_bg->SetBinContent(78,10764);
   diff_bg->SetBinContent(79,9744);
   diff_bg->SetBinContent(80,9225);
   diff_bg->SetBinContent(81,8423);
   diff_bg->SetBinContent(82,8111);
   diff_bg->SetBinContent(83,7485);
   diff_bg->SetBinContent(84,6989);
   diff_bg->SetBinContent(85,7161);
   diff_bg->SetBinContent(86,7006);
   diff_bg->SetBinContent(87,7273);
   diff_bg->SetBinContent(88,6863);
   diff_bg->SetBinContent(89,6907);
   diff_bg->SetBinContent(90,7140);
   diff_bg->SetBinContent(91,6951);
   diff_bg->SetBinContent(92,6600);
   diff_bg->SetBinContent(93,6308);
   diff_bg->SetBinContent(94,6582);
   diff_bg->SetBinContent(95,6351);
   diff_bg->SetBinContent(96,6495);
   diff_bg->SetBinContent(97,6839);
   diff_bg->SetBinContent(98,6946);
   diff_bg->SetBinContent(99,6850);
   diff_bg->SetBinContent(100,6546);
   diff_bg->SetEntries(5134803);
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
   diff_true->SetBinContent(32,2);
   diff_true->SetBinContent(33,3);
   diff_true->SetBinContent(41,12);
   diff_true->SetBinContent(42,55);
   diff_true->SetBinContent(43,257);
   diff_true->SetBinContent(44,1155);
   diff_true->SetBinContent(45,4291);
   diff_true->SetBinContent(46,13463);
   diff_true->SetBinContent(47,32667);
   diff_true->SetBinContent(48,64106);
   diff_true->SetBinContent(49,101582);
   diff_true->SetBinContent(50,131377);
   diff_true->SetBinContent(51,138096);
   diff_true->SetBinContent(52,117245);
   diff_true->SetBinContent(53,82523);
   diff_true->SetBinContent(54,46782);
   diff_true->SetBinContent(55,21729);
   diff_true->SetBinContent(56,8322);
   diff_true->SetBinContent(57,2797);
   diff_true->SetBinContent(58,865);
   diff_true->SetBinContent(59,209);
   diff_true->SetBinContent(60,64);
   diff_true->SetBinContent(61,22);
   diff_true->SetBinContent(62,9);
   diff_true->SetBinContent(63,4);
   diff_true->SetEntries(767637);
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
   
   TPaveText *pt = new TPaveText(0.2931609,0.9339831,0.7068391,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("105 deg, lens 3, full LUT");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
