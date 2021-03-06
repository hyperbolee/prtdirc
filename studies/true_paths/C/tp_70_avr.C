{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Mar  5 21:30:34 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-6.25,-650.5101,6.25,48729.09);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *diff_full = new TH1D("diff_full","70 deg, lens 3, avr LUT",100,-5,5);
   diff_full->SetBinContent(1,7792);
   diff_full->SetBinContent(2,8048);
   diff_full->SetBinContent(3,8307);
   diff_full->SetBinContent(4,8136);
   diff_full->SetBinContent(5,8613);
   diff_full->SetBinContent(6,8647);
   diff_full->SetBinContent(7,8899);
   diff_full->SetBinContent(8,9354);
   diff_full->SetBinContent(9,9800);
   diff_full->SetBinContent(10,10586);
   diff_full->SetBinContent(11,11601);
   diff_full->SetBinContent(12,12436);
   diff_full->SetBinContent(13,13096);
   diff_full->SetBinContent(14,13706);
   diff_full->SetBinContent(15,13669);
   diff_full->SetBinContent(16,13999);
   diff_full->SetBinContent(17,13996);
   diff_full->SetBinContent(18,14128);
   diff_full->SetBinContent(19,14120);
   diff_full->SetBinContent(20,14511);
   diff_full->SetBinContent(21,14190);
   diff_full->SetBinContent(22,14206);
   diff_full->SetBinContent(23,13699);
   diff_full->SetBinContent(24,13096);
   diff_full->SetBinContent(25,12976);
   diff_full->SetBinContent(26,12751);
   diff_full->SetBinContent(27,12677);
   diff_full->SetBinContent(28,12690);
   diff_full->SetBinContent(29,13123);
   diff_full->SetBinContent(30,13217);
   diff_full->SetBinContent(31,13700);
   diff_full->SetBinContent(32,14394);
   diff_full->SetBinContent(33,15208);
   diff_full->SetBinContent(34,16446);
   diff_full->SetBinContent(35,17823);
   diff_full->SetBinContent(36,19226);
   diff_full->SetBinContent(37,21130);
   diff_full->SetBinContent(38,22609);
   diff_full->SetBinContent(39,23866);
   diff_full->SetBinContent(40,24411);
   diff_full->SetBinContent(41,24418);
   diff_full->SetBinContent(42,24251);
   diff_full->SetBinContent(43,23820);
   diff_full->SetBinContent(44,24056);
   diff_full->SetBinContent(45,25109);
   diff_full->SetBinContent(46,27698);
   diff_full->SetBinContent(47,31135);
   diff_full->SetBinContent(48,35314);
   diff_full->SetBinContent(49,38893);
   diff_full->SetBinContent(50,41188);
   diff_full->SetBinContent(51,41910);
   diff_full->SetBinContent(52,41434);
   diff_full->SetBinContent(53,40300);
   diff_full->SetBinContent(54,38412);
   diff_full->SetBinContent(55,36839);
   diff_full->SetBinContent(56,34544);
   diff_full->SetBinContent(57,32242);
   diff_full->SetBinContent(58,30053);
   diff_full->SetBinContent(59,28135);
   diff_full->SetBinContent(60,26457);
   diff_full->SetBinContent(61,23998);
   diff_full->SetBinContent(62,21863);
   diff_full->SetBinContent(63,19683);
   diff_full->SetBinContent(64,17769);
   diff_full->SetBinContent(65,16348);
   diff_full->SetBinContent(66,14752);
   diff_full->SetBinContent(67,14382);
   diff_full->SetBinContent(68,14125);
   diff_full->SetBinContent(69,13606);
   diff_full->SetBinContent(70,13379);
   diff_full->SetBinContent(71,13214);
   diff_full->SetBinContent(72,13032);
   diff_full->SetBinContent(73,13032);
   diff_full->SetBinContent(74,13214);
   diff_full->SetBinContent(75,13150);
   diff_full->SetBinContent(76,13286);
   diff_full->SetBinContent(77,12992);
   diff_full->SetBinContent(78,12789);
   diff_full->SetBinContent(79,12775);
   diff_full->SetBinContent(80,12404);
   diff_full->SetBinContent(81,12070);
   diff_full->SetBinContent(82,11501);
   diff_full->SetBinContent(83,11247);
   diff_full->SetBinContent(84,10864);
   diff_full->SetBinContent(85,10550);
   diff_full->SetBinContent(86,10013);
   diff_full->SetBinContent(87,9715);
   diff_full->SetBinContent(88,9255);
   diff_full->SetBinContent(89,9124);
   diff_full->SetBinContent(90,8525);
   diff_full->SetBinContent(91,8374);
   diff_full->SetBinContent(92,7946);
   diff_full->SetBinContent(93,7751);
   diff_full->SetBinContent(94,7478);
   diff_full->SetBinContent(95,7140);
   diff_full->SetBinContent(96,6837);
   diff_full->SetBinContent(97,6823);
   diff_full->SetBinContent(98,6612);
   diff_full->SetBinContent(99,6349);
   diff_full->SetBinContent(100,6079);
   diff_full->SetEntries(1665136);
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
   diff_bg->SetBinContent(1,5274);
   diff_bg->SetBinContent(2,5496);
   diff_bg->SetBinContent(3,5559);
   diff_bg->SetBinContent(4,5389);
   diff_bg->SetBinContent(5,5591);
   diff_bg->SetBinContent(6,5422);
   diff_bg->SetBinContent(7,5453);
   diff_bg->SetBinContent(8,5560);
   diff_bg->SetBinContent(9,5964);
   diff_bg->SetBinContent(10,6540);
   diff_bg->SetBinContent(11,7316);
   diff_bg->SetBinContent(12,7943);
   diff_bg->SetBinContent(13,8406);
   diff_bg->SetBinContent(14,8630);
   diff_bg->SetBinContent(15,8582);
   diff_bg->SetBinContent(16,8680);
   diff_bg->SetBinContent(17,8550);
   diff_bg->SetBinContent(18,8768);
   diff_bg->SetBinContent(19,8997);
   diff_bg->SetBinContent(20,9424);
   diff_bg->SetBinContent(21,9506);
   diff_bg->SetBinContent(22,9517);
   diff_bg->SetBinContent(23,9239);
   diff_bg->SetBinContent(24,8962);
   diff_bg->SetBinContent(25,8597);
   diff_bg->SetBinContent(26,8396);
   diff_bg->SetBinContent(27,8289);
   diff_bg->SetBinContent(28,8224);
   diff_bg->SetBinContent(29,8483);
   diff_bg->SetBinContent(30,8485);
   diff_bg->SetBinContent(31,8504);
   diff_bg->SetBinContent(32,8656);
   diff_bg->SetBinContent(33,8884);
   diff_bg->SetBinContent(34,9567);
   diff_bg->SetBinContent(35,10412);
   diff_bg->SetBinContent(36,11431);
   diff_bg->SetBinContent(37,12847);
   diff_bg->SetBinContent(38,13971);
   diff_bg->SetBinContent(39,15140);
   diff_bg->SetBinContent(40,15491);
   diff_bg->SetBinContent(41,15700);
   diff_bg->SetBinContent(42,15646);
   diff_bg->SetBinContent(43,15388);
   diff_bg->SetBinContent(44,15704);
   diff_bg->SetBinContent(45,16565);
   diff_bg->SetBinContent(46,18111);
   diff_bg->SetBinContent(47,20407);
   diff_bg->SetBinContent(48,22938);
   diff_bg->SetBinContent(49,25219);
   diff_bg->SetBinContent(50,26441);
   diff_bg->SetBinContent(51,26892);
   diff_bg->SetBinContent(52,26443);
   diff_bg->SetBinContent(53,25756);
   diff_bg->SetBinContent(54,24518);
   diff_bg->SetBinContent(55,23354);
   diff_bg->SetBinContent(56,21930);
   diff_bg->SetBinContent(57,20406);
   diff_bg->SetBinContent(58,19115);
   diff_bg->SetBinContent(59,17809);
   diff_bg->SetBinContent(60,16948);
   diff_bg->SetBinContent(61,15308);
   diff_bg->SetBinContent(62,14100);
   diff_bg->SetBinContent(63,12731);
   diff_bg->SetBinContent(64,11610);
   diff_bg->SetBinContent(65,10684);
   diff_bg->SetBinContent(66,9490);
   diff_bg->SetBinContent(67,9186);
   diff_bg->SetBinContent(68,9091);
   diff_bg->SetBinContent(69,8697);
   diff_bg->SetBinContent(70,8600);
   diff_bg->SetBinContent(71,8553);
   diff_bg->SetBinContent(72,8419);
   diff_bg->SetBinContent(73,8366);
   diff_bg->SetBinContent(74,8463);
   diff_bg->SetBinContent(75,8358);
   diff_bg->SetBinContent(76,8459);
   diff_bg->SetBinContent(77,8210);
   diff_bg->SetBinContent(78,8100);
   diff_bg->SetBinContent(79,8066);
   diff_bg->SetBinContent(80,7889);
   diff_bg->SetBinContent(81,7554);
   diff_bg->SetBinContent(82,7164);
   diff_bg->SetBinContent(83,6908);
   diff_bg->SetBinContent(84,6857);
   diff_bg->SetBinContent(85,6687);
   diff_bg->SetBinContent(86,6436);
   diff_bg->SetBinContent(87,6335);
   diff_bg->SetBinContent(88,6193);
   diff_bg->SetBinContent(89,6168);
   diff_bg->SetBinContent(90,5842);
   diff_bg->SetBinContent(91,5910);
   diff_bg->SetBinContent(92,5613);
   diff_bg->SetBinContent(93,5527);
   diff_bg->SetBinContent(94,5389);
   diff_bg->SetBinContent(95,5108);
   diff_bg->SetBinContent(96,5067);
   diff_bg->SetBinContent(97,5053);
   diff_bg->SetBinContent(98,4902);
   diff_bg->SetBinContent(99,4820);
   diff_bg->SetBinContent(100,4634);
   diff_bg->SetEntries(1069982);
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
   diff_true->SetBinContent(1,2518);
   diff_true->SetBinContent(2,2552);
   diff_true->SetBinContent(3,2748);
   diff_true->SetBinContent(4,2747);
   diff_true->SetBinContent(5,3022);
   diff_true->SetBinContent(6,3225);
   diff_true->SetBinContent(7,3446);
   diff_true->SetBinContent(8,3794);
   diff_true->SetBinContent(9,3836);
   diff_true->SetBinContent(10,4046);
   diff_true->SetBinContent(11,4285);
   diff_true->SetBinContent(12,4493);
   diff_true->SetBinContent(13,4690);
   diff_true->SetBinContent(14,5076);
   diff_true->SetBinContent(15,5087);
   diff_true->SetBinContent(16,5319);
   diff_true->SetBinContent(17,5446);
   diff_true->SetBinContent(18,5360);
   diff_true->SetBinContent(19,5123);
   diff_true->SetBinContent(20,5087);
   diff_true->SetBinContent(21,4684);
   diff_true->SetBinContent(22,4689);
   diff_true->SetBinContent(23,4460);
   diff_true->SetBinContent(24,4134);
   diff_true->SetBinContent(25,4379);
   diff_true->SetBinContent(26,4355);
   diff_true->SetBinContent(27,4388);
   diff_true->SetBinContent(28,4466);
   diff_true->SetBinContent(29,4640);
   diff_true->SetBinContent(30,4732);
   diff_true->SetBinContent(31,5196);
   diff_true->SetBinContent(32,5738);
   diff_true->SetBinContent(33,6324);
   diff_true->SetBinContent(34,6879);
   diff_true->SetBinContent(35,7411);
   diff_true->SetBinContent(36,7795);
   diff_true->SetBinContent(37,8283);
   diff_true->SetBinContent(38,8638);
   diff_true->SetBinContent(39,8726);
   diff_true->SetBinContent(40,8920);
   diff_true->SetBinContent(41,8718);
   diff_true->SetBinContent(42,8605);
   diff_true->SetBinContent(43,8432);
   diff_true->SetBinContent(44,8352);
   diff_true->SetBinContent(45,8544);
   diff_true->SetBinContent(46,9587);
   diff_true->SetBinContent(47,10728);
   diff_true->SetBinContent(48,12376);
   diff_true->SetBinContent(49,13674);
   diff_true->SetBinContent(50,14747);
   diff_true->SetBinContent(51,15018);
   diff_true->SetBinContent(52,14991);
   diff_true->SetBinContent(53,14544);
   diff_true->SetBinContent(54,13894);
   diff_true->SetBinContent(55,13485);
   diff_true->SetBinContent(56,12614);
   diff_true->SetBinContent(57,11836);
   diff_true->SetBinContent(58,10938);
   diff_true->SetBinContent(59,10326);
   diff_true->SetBinContent(60,9509);
   diff_true->SetBinContent(61,8690);
   diff_true->SetBinContent(62,7763);
   diff_true->SetBinContent(63,6952);
   diff_true->SetBinContent(64,6159);
   diff_true->SetBinContent(65,5664);
   diff_true->SetBinContent(66,5262);
   diff_true->SetBinContent(67,5196);
   diff_true->SetBinContent(68,5034);
   diff_true->SetBinContent(69,4909);
   diff_true->SetBinContent(70,4779);
   diff_true->SetBinContent(71,4661);
   diff_true->SetBinContent(72,4613);
   diff_true->SetBinContent(73,4666);
   diff_true->SetBinContent(74,4751);
   diff_true->SetBinContent(75,4792);
   diff_true->SetBinContent(76,4827);
   diff_true->SetBinContent(77,4782);
   diff_true->SetBinContent(78,4689);
   diff_true->SetBinContent(79,4709);
   diff_true->SetBinContent(80,4515);
   diff_true->SetBinContent(81,4516);
   diff_true->SetBinContent(82,4337);
   diff_true->SetBinContent(83,4339);
   diff_true->SetBinContent(84,4007);
   diff_true->SetBinContent(85,3863);
   diff_true->SetBinContent(86,3577);
   diff_true->SetBinContent(87,3380);
   diff_true->SetBinContent(88,3062);
   diff_true->SetBinContent(89,2956);
   diff_true->SetBinContent(90,2683);
   diff_true->SetBinContent(91,2464);
   diff_true->SetBinContent(92,2333);
   diff_true->SetBinContent(93,2224);
   diff_true->SetBinContent(94,2089);
   diff_true->SetBinContent(95,2032);
   diff_true->SetBinContent(96,1770);
   diff_true->SetBinContent(97,1770);
   diff_true->SetBinContent(98,1710);
   diff_true->SetBinContent(99,1529);
   diff_true->SetBinContent(100,1445);
   diff_true->SetEntries(595154);
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
   
   TPaveText *pt = new TPaveText(0.3032184,0.9339831,0.6967816,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("70 deg, lens 3, avr LUT");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
