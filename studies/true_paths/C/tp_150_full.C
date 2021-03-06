{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Mar  5 21:08:48 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-6.25,-304278.5,6.25,2738506);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *diff_full = new TH1D("diff_full","150 deg, lens 3, full LUT",100,-5,5);
   diff_full->SetBinContent(1,87);
   diff_full->SetBinContent(2,273);
   diff_full->SetBinContent(3,625);
   diff_full->SetBinContent(4,1168);
   diff_full->SetBinContent(5,1890);
   diff_full->SetBinContent(6,2611);
   diff_full->SetBinContent(7,3161);
   diff_full->SetBinContent(8,3439);
   diff_full->SetBinContent(9,3280);
   diff_full->SetBinContent(10,2787);
   diff_full->SetBinContent(11,2156);
   diff_full->SetBinContent(12,1795);
   diff_full->SetBinContent(13,1791);
   diff_full->SetBinContent(14,2511);
   diff_full->SetBinContent(15,3853);
   diff_full->SetBinContent(16,5771);
   diff_full->SetBinContent(17,8699);
   diff_full->SetBinContent(18,12358);
   diff_full->SetBinContent(19,17148);
   diff_full->SetBinContent(20,23843);
   diff_full->SetBinContent(21,31492);
   diff_full->SetBinContent(22,41330);
   diff_full->SetBinContent(23,54435);
   diff_full->SetBinContent(24,69827);
   diff_full->SetBinContent(25,88480);
   diff_full->SetBinContent(26,110734);
   diff_full->SetBinContent(27,134692);
   diff_full->SetBinContent(28,158741);
   diff_full->SetBinContent(29,184918);
   diff_full->SetBinContent(30,212541);
   diff_full->SetBinContent(31,236914);
   diff_full->SetBinContent(32,260042);
   diff_full->SetBinContent(33,279320);
   diff_full->SetBinContent(34,290353);
   diff_full->SetBinContent(35,306479);
   diff_full->SetBinContent(36,325304);
   diff_full->SetBinContent(37,349684);
   diff_full->SetBinContent(38,377917);
   diff_full->SetBinContent(39,404887);
   diff_full->SetBinContent(40,437515);
   diff_full->SetBinContent(41,479763);
   diff_full->SetBinContent(42,531487);
   diff_full->SetBinContent(43,604309);
   diff_full->SetBinContent(44,720625);
   diff_full->SetBinContent(45,890534);
   diff_full->SetBinContent(46,1136222);
   diff_full->SetBinContent(47,1442751);
   diff_full->SetBinContent(48,1792379);
   diff_full->SetBinContent(49,2109594);
   diff_full->SetBinContent(50,2308011);
   diff_full->SetBinContent(51,2318312);
   diff_full->SetBinContent(52,2133713);
   diff_full->SetBinContent(53,1816726);
   diff_full->SetBinContent(54,1478176);
   diff_full->SetBinContent(55,1202242);
   diff_full->SetBinContent(56,1026471);
   diff_full->SetBinContent(57,965996);
   diff_full->SetBinContent(58,972109);
   diff_full->SetBinContent(59,1001297);
   diff_full->SetBinContent(60,1042068);
   diff_full->SetBinContent(61,1085660);
   diff_full->SetBinContent(62,1115230);
   diff_full->SetBinContent(63,1150002);
   diff_full->SetBinContent(64,1168438);
   diff_full->SetBinContent(65,1166204);
   diff_full->SetBinContent(66,1150386);
   diff_full->SetBinContent(67,1127027);
   diff_full->SetBinContent(68,1089469);
   diff_full->SetBinContent(69,1053543);
   diff_full->SetBinContent(70,1008303);
   diff_full->SetBinContent(71,941491);
   diff_full->SetBinContent(72,886157);
   diff_full->SetBinContent(73,799635);
   diff_full->SetBinContent(74,720375);
   diff_full->SetBinContent(75,643560);
   diff_full->SetBinContent(76,567033);
   diff_full->SetBinContent(77,504289);
   diff_full->SetBinContent(78,449174);
   diff_full->SetBinContent(79,404355);
   diff_full->SetBinContent(80,371412);
   diff_full->SetBinContent(81,342875);
   diff_full->SetBinContent(82,319175);
   diff_full->SetBinContent(83,293869);
   diff_full->SetBinContent(84,267394);
   diff_full->SetBinContent(85,243609);
   diff_full->SetBinContent(86,220744);
   diff_full->SetBinContent(87,195299);
   diff_full->SetBinContent(88,172902);
   diff_full->SetBinContent(89,151293);
   diff_full->SetBinContent(90,134983);
   diff_full->SetBinContent(91,118998);
   diff_full->SetBinContent(92,106643);
   diff_full->SetBinContent(93,95410);
   diff_full->SetBinContent(94,86802);
   diff_full->SetBinContent(95,79894);
   diff_full->SetBinContent(96,74750);
   diff_full->SetBinContent(97,72389);
   diff_full->SetBinContent(98,69996);
   diff_full->SetBinContent(99,68688);
   diff_full->SetBinContent(100,71087);
   diff_full->SetEntries(5.101618e+07);
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
   diff_bg->SetBinContent(1,87);
   diff_bg->SetBinContent(2,273);
   diff_bg->SetBinContent(3,625);
   diff_bg->SetBinContent(4,1168);
   diff_bg->SetBinContent(5,1890);
   diff_bg->SetBinContent(6,2611);
   diff_bg->SetBinContent(7,3161);
   diff_bg->SetBinContent(8,3439);
   diff_bg->SetBinContent(9,3280);
   diff_bg->SetBinContent(10,2786);
   diff_bg->SetBinContent(11,2156);
   diff_bg->SetBinContent(12,1795);
   diff_bg->SetBinContent(13,1791);
   diff_bg->SetBinContent(14,2511);
   diff_bg->SetBinContent(15,3853);
   diff_bg->SetBinContent(16,5769);
   diff_bg->SetBinContent(17,8699);
   diff_bg->SetBinContent(18,12358);
   diff_bg->SetBinContent(19,17148);
   diff_bg->SetBinContent(20,23843);
   diff_bg->SetBinContent(21,31490);
   diff_bg->SetBinContent(22,41329);
   diff_bg->SetBinContent(23,54435);
   diff_bg->SetBinContent(24,69826);
   diff_bg->SetBinContent(25,88475);
   diff_bg->SetBinContent(26,110734);
   diff_bg->SetBinContent(27,134691);
   diff_bg->SetBinContent(28,158738);
   diff_bg->SetBinContent(29,184917);
   diff_bg->SetBinContent(30,212541);
   diff_bg->SetBinContent(31,236914);
   diff_bg->SetBinContent(32,260042);
   diff_bg->SetBinContent(33,279320);
   diff_bg->SetBinContent(34,290344);
   diff_bg->SetBinContent(35,306474);
   diff_bg->SetBinContent(36,325304);
   diff_bg->SetBinContent(37,349684);
   diff_bg->SetBinContent(38,377909);
   diff_bg->SetBinContent(39,404886);
   diff_bg->SetBinContent(40,437467);
   diff_bg->SetBinContent(41,479577);
   diff_bg->SetBinContent(42,530551);
   diff_bg->SetBinContent(43,600356);
   diff_bg->SetBinContent(44,705302);
   diff_bg->SetBinContent(45,841086);
   diff_bg->SetBinContent(46,1009458);
   diff_bg->SetBinContent(47,1170121);
   diff_bg->SetBinContent(48,1306301);
   diff_bg->SetBinContent(49,1389927);
   diff_bg->SetBinContent(50,1408462);
   diff_bg->SetBinContent(51,1370597);
   diff_bg->SetBinContent(52,1302835);
   diff_bg->SetBinContent(53,1203220);
   diff_bg->SetBinContent(54,1093963);
   diff_bg->SetBinContent(55,1002982);
   diff_bg->SetBinContent(56,937602);
   diff_bg->SetBinContent(57,931948);
   diff_bg->SetBinContent(58,959477);
   diff_bg->SetBinContent(59,996389);
   diff_bg->SetBinContent(60,1039807);
   diff_bg->SetBinContent(61,1084452);
   diff_bg->SetBinContent(62,1114448);
   diff_bg->SetBinContent(63,1149512);
   diff_bg->SetBinContent(64,1168064);
   diff_bg->SetBinContent(65,1165990);
   diff_bg->SetBinContent(66,1150263);
   diff_bg->SetBinContent(67,1126950);
   diff_bg->SetBinContent(68,1089415);
   diff_bg->SetBinContent(69,1053521);
   diff_bg->SetBinContent(70,1008292);
   diff_bg->SetBinContent(71,941489);
   diff_bg->SetBinContent(72,886156);
   diff_bg->SetBinContent(73,799635);
   diff_bg->SetBinContent(74,720375);
   diff_bg->SetBinContent(75,643560);
   diff_bg->SetBinContent(76,567033);
   diff_bg->SetBinContent(77,504289);
   diff_bg->SetBinContent(78,449174);
   diff_bg->SetBinContent(79,404355);
   diff_bg->SetBinContent(80,371412);
   diff_bg->SetBinContent(81,342875);
   diff_bg->SetBinContent(82,319172);
   diff_bg->SetBinContent(83,293864);
   diff_bg->SetBinContent(84,267382);
   diff_bg->SetBinContent(85,243603);
   diff_bg->SetBinContent(86,220740);
   diff_bg->SetBinContent(87,195299);
   diff_bg->SetBinContent(88,172899);
   diff_bg->SetBinContent(89,151291);
   diff_bg->SetBinContent(90,134983);
   diff_bg->SetBinContent(91,118996);
   diff_bg->SetBinContent(92,106642);
   diff_bg->SetBinContent(93,95410);
   diff_bg->SetBinContent(94,86802);
   diff_bg->SetBinContent(95,79894);
   diff_bg->SetBinContent(96,74750);
   diff_bg->SetBinContent(97,72389);
   diff_bg->SetBinContent(98,69996);
   diff_bg->SetBinContent(99,68688);
   diff_bg->SetBinContent(100,71087);
   diff_bg->SetEntries(4.531987e+07);
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
   diff_true->SetBinContent(10,1);
   diff_true->SetBinContent(16,2);
   diff_true->SetBinContent(21,2);
   diff_true->SetBinContent(22,1);
   diff_true->SetBinContent(24,1);
   diff_true->SetBinContent(25,5);
   diff_true->SetBinContent(27,1);
   diff_true->SetBinContent(28,3);
   diff_true->SetBinContent(29,1);
   diff_true->SetBinContent(34,9);
   diff_true->SetBinContent(35,5);
   diff_true->SetBinContent(38,8);
   diff_true->SetBinContent(39,1);
   diff_true->SetBinContent(40,48);
   diff_true->SetBinContent(41,186);
   diff_true->SetBinContent(42,936);
   diff_true->SetBinContent(43,3953);
   diff_true->SetBinContent(44,15323);
   diff_true->SetBinContent(45,49448);
   diff_true->SetBinContent(46,126764);
   diff_true->SetBinContent(47,272630);
   diff_true->SetBinContent(48,486078);
   diff_true->SetBinContent(49,719667);
   diff_true->SetBinContent(50,899549);
   diff_true->SetBinContent(51,947715);
   diff_true->SetBinContent(52,830878);
   diff_true->SetBinContent(53,613506);
   diff_true->SetBinContent(54,384213);
   diff_true->SetBinContent(55,199260);
   diff_true->SetBinContent(56,88869);
   diff_true->SetBinContent(57,34048);
   diff_true->SetBinContent(58,12632);
   diff_true->SetBinContent(59,4908);
   diff_true->SetBinContent(60,2261);
   diff_true->SetBinContent(61,1208);
   diff_true->SetBinContent(62,782);
   diff_true->SetBinContent(63,490);
   diff_true->SetBinContent(64,374);
   diff_true->SetBinContent(65,214);
   diff_true->SetBinContent(66,123);
   diff_true->SetBinContent(67,77);
   diff_true->SetBinContent(68,54);
   diff_true->SetBinContent(69,22);
   diff_true->SetBinContent(70,11);
   diff_true->SetBinContent(71,2);
   diff_true->SetBinContent(72,1);
   diff_true->SetBinContent(82,3);
   diff_true->SetBinContent(83,5);
   diff_true->SetBinContent(84,12);
   diff_true->SetBinContent(85,6);
   diff_true->SetBinContent(86,4);
   diff_true->SetBinContent(88,3);
   diff_true->SetBinContent(89,2);
   diff_true->SetBinContent(91,2);
   diff_true->SetBinContent(92,1);
   diff_true->SetEntries(5696308);
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
   TText *text = pt->AddText("150 deg, lens 3, full LUT");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
