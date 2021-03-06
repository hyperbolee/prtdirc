{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Mar  5 21:30:18 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-6.25,-27974.79,6.25,327450.5);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *diff_full = new TH1D("diff_full","30 deg, lens 3, avr LUT",100,-5,5);
   diff_full->SetBinContent(1,20463);
   diff_full->SetBinContent(2,22558);
   diff_full->SetBinContent(3,24401);
   diff_full->SetBinContent(4,26147);
   diff_full->SetBinContent(5,27631);
   diff_full->SetBinContent(6,28949);
   diff_full->SetBinContent(7,30804);
   diff_full->SetBinContent(8,32449);
   diff_full->SetBinContent(9,34233);
   diff_full->SetBinContent(10,36848);
   diff_full->SetBinContent(11,38527);
   diff_full->SetBinContent(12,40416);
   diff_full->SetBinContent(13,41760);
   diff_full->SetBinContent(14,43198);
   diff_full->SetBinContent(15,42855);
   diff_full->SetBinContent(16,42389);
   diff_full->SetBinContent(17,40811);
   diff_full->SetBinContent(18,40191);
   diff_full->SetBinContent(19,38604);
   diff_full->SetBinContent(20,38099);
   diff_full->SetBinContent(21,38425);
   diff_full->SetBinContent(22,39993);
   diff_full->SetBinContent(23,42048);
   diff_full->SetBinContent(24,43780);
   diff_full->SetBinContent(25,46660);
   diff_full->SetBinContent(26,46958);
   diff_full->SetBinContent(27,48855);
   diff_full->SetBinContent(28,50336);
   diff_full->SetBinContent(29,51400);
   diff_full->SetBinContent(30,53977);
   diff_full->SetBinContent(31,55995);
   diff_full->SetBinContent(32,58652);
   diff_full->SetBinContent(33,61346);
   diff_full->SetBinContent(34,63156);
   diff_full->SetBinContent(35,65583);
   diff_full->SetBinContent(36,67505);
   diff_full->SetBinContent(37,69690);
   diff_full->SetBinContent(38,72681);
   diff_full->SetBinContent(39,77634);
   diff_full->SetBinContent(40,85591);
   diff_full->SetBinContent(41,96141);
   diff_full->SetBinContent(42,109249);
   diff_full->SetBinContent(43,124209);
   diff_full->SetBinContent(44,141237);
   diff_full->SetBinContent(45,163360);
   diff_full->SetBinContent(46,188026);
   diff_full->SetBinContent(47,216420);
   diff_full->SetBinContent(48,245158);
   diff_full->SetBinContent(49,267523);
   diff_full->SetBinContent(50,278368);
   diff_full->SetBinContent(51,277578);
   diff_full->SetBinContent(52,267265);
   diff_full->SetBinContent(53,245476);
   diff_full->SetBinContent(54,217078);
   diff_full->SetBinContent(55,184110);
   diff_full->SetBinContent(56,153713);
   diff_full->SetBinContent(57,125930);
   diff_full->SetBinContent(58,105235);
   diff_full->SetBinContent(59,91250);
   diff_full->SetBinContent(60,83360);
   diff_full->SetBinContent(61,78247);
   diff_full->SetBinContent(62,77471);
   diff_full->SetBinContent(63,76880);
   diff_full->SetBinContent(64,78649);
   diff_full->SetBinContent(65,80265);
   diff_full->SetBinContent(66,82348);
   diff_full->SetBinContent(67,84396);
   diff_full->SetBinContent(68,84689);
   diff_full->SetBinContent(69,86178);
   diff_full->SetBinContent(70,85746);
   diff_full->SetBinContent(71,84798);
   diff_full->SetBinContent(72,83709);
   diff_full->SetBinContent(73,83059);
   diff_full->SetBinContent(74,83796);
   diff_full->SetBinContent(75,85119);
   diff_full->SetBinContent(76,85672);
   diff_full->SetBinContent(77,87589);
   diff_full->SetBinContent(78,89197);
   diff_full->SetBinContent(79,91043);
   diff_full->SetBinContent(80,91978);
   diff_full->SetBinContent(81,91747);
   diff_full->SetBinContent(82,93086);
   diff_full->SetBinContent(83,92272);
   diff_full->SetBinContent(84,91903);
   diff_full->SetBinContent(85,91953);
   diff_full->SetBinContent(86,91796);
   diff_full->SetBinContent(87,90789);
   diff_full->SetBinContent(88,89815);
   diff_full->SetBinContent(89,88190);
   diff_full->SetBinContent(90,87202);
   diff_full->SetBinContent(91,84466);
   diff_full->SetBinContent(92,81909);
   diff_full->SetBinContent(93,78557);
   diff_full->SetBinContent(94,76887);
   diff_full->SetBinContent(95,73081);
   diff_full->SetBinContent(96,70092);
   diff_full->SetBinContent(97,67157);
   diff_full->SetBinContent(98,64713);
   diff_full->SetBinContent(99,61613);
   diff_full->SetBinContent(100,59388);
   diff_full->SetEntries(8719729);
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
   diff_bg->SetBinContent(1,15686);
   diff_bg->SetBinContent(2,17152);
   diff_bg->SetBinContent(3,18641);
   diff_bg->SetBinContent(4,19886);
   diff_bg->SetBinContent(5,20771);
   diff_bg->SetBinContent(6,21408);
   diff_bg->SetBinContent(7,22434);
   diff_bg->SetBinContent(8,23690);
   diff_bg->SetBinContent(9,24952);
   diff_bg->SetBinContent(10,27008);
   diff_bg->SetBinContent(11,28376);
   diff_bg->SetBinContent(12,30181);
   diff_bg->SetBinContent(13,31500);
   diff_bg->SetBinContent(14,32957);
   diff_bg->SetBinContent(15,33150);
   diff_bg->SetBinContent(16,33329);
   diff_bg->SetBinContent(17,32027);
   diff_bg->SetBinContent(18,31993);
   diff_bg->SetBinContent(19,30430);
   diff_bg->SetBinContent(20,29636);
   diff_bg->SetBinContent(21,29673);
   diff_bg->SetBinContent(22,30359);
   diff_bg->SetBinContent(23,32084);
   diff_bg->SetBinContent(24,33123);
   diff_bg->SetBinContent(25,35296);
   diff_bg->SetBinContent(26,34896);
   diff_bg->SetBinContent(27,35612);
   diff_bg->SetBinContent(28,35914);
   diff_bg->SetBinContent(29,36087);
   diff_bg->SetBinContent(30,36632);
   diff_bg->SetBinContent(31,37276);
   diff_bg->SetBinContent(32,38726);
   diff_bg->SetBinContent(33,40278);
   diff_bg->SetBinContent(34,41155);
   diff_bg->SetBinContent(35,42777);
   diff_bg->SetBinContent(36,44058);
   diff_bg->SetBinContent(37,45232);
   diff_bg->SetBinContent(38,47230);
   diff_bg->SetBinContent(39,50611);
   diff_bg->SetBinContent(40,56520);
   diff_bg->SetBinContent(41,63642);
   diff_bg->SetBinContent(42,73070);
   diff_bg->SetBinContent(43,83560);
   diff_bg->SetBinContent(44,95767);
   diff_bg->SetBinContent(45,110761);
   diff_bg->SetBinContent(46,128252);
   diff_bg->SetBinContent(47,148908);
   diff_bg->SetBinContent(48,169761);
   diff_bg->SetBinContent(49,186993);
   diff_bg->SetBinContent(50,196503);
   diff_bg->SetBinContent(51,197262);
   diff_bg->SetBinContent(52,191121);
   diff_bg->SetBinContent(53,177065);
   diff_bg->SetBinContent(54,156693);
   diff_bg->SetBinContent(55,133180);
   diff_bg->SetBinContent(56,111713);
   diff_bg->SetBinContent(57,91663);
   diff_bg->SetBinContent(58,76113);
   diff_bg->SetBinContent(59,65887);
   diff_bg->SetBinContent(60,60212);
   diff_bg->SetBinContent(61,56209);
   diff_bg->SetBinContent(62,55551);
   diff_bg->SetBinContent(63,55471);
   diff_bg->SetBinContent(64,56381);
   diff_bg->SetBinContent(65,57346);
   diff_bg->SetBinContent(66,58971);
   diff_bg->SetBinContent(67,60354);
   diff_bg->SetBinContent(68,61336);
   diff_bg->SetBinContent(69,62129);
   diff_bg->SetBinContent(70,61538);
   diff_bg->SetBinContent(71,60576);
   diff_bg->SetBinContent(72,59227);
   diff_bg->SetBinContent(73,58396);
   diff_bg->SetBinContent(74,58496);
   diff_bg->SetBinContent(75,59258);
   diff_bg->SetBinContent(76,59148);
   diff_bg->SetBinContent(77,59916);
   diff_bg->SetBinContent(78,60879);
   diff_bg->SetBinContent(79,61693);
   diff_bg->SetBinContent(80,62178);
   diff_bg->SetBinContent(81,62020);
   diff_bg->SetBinContent(82,63670);
   diff_bg->SetBinContent(83,64177);
   diff_bg->SetBinContent(84,65415);
   diff_bg->SetBinContent(85,67391);
   diff_bg->SetBinContent(86,68458);
   diff_bg->SetBinContent(87,69360);
   diff_bg->SetBinContent(88,69583);
   diff_bg->SetBinContent(89,69540);
   diff_bg->SetBinContent(90,69731);
   diff_bg->SetBinContent(91,67589);
   diff_bg->SetBinContent(92,66047);
   diff_bg->SetBinContent(93,63333);
   diff_bg->SetBinContent(94,62014);
   diff_bg->SetBinContent(95,58768);
   diff_bg->SetBinContent(96,56380);
   diff_bg->SetBinContent(97,54113);
   diff_bg->SetBinContent(98,51754);
   diff_bg->SetBinContent(99,49433);
   diff_bg->SetBinContent(100,47681);
   diff_bg->SetEntries(6258382);
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
   diff_true->SetBinContent(1,4777);
   diff_true->SetBinContent(2,5406);
   diff_true->SetBinContent(3,5760);
   diff_true->SetBinContent(4,6261);
   diff_true->SetBinContent(5,6860);
   diff_true->SetBinContent(6,7541);
   diff_true->SetBinContent(7,8370);
   diff_true->SetBinContent(8,8759);
   diff_true->SetBinContent(9,9281);
   diff_true->SetBinContent(10,9840);
   diff_true->SetBinContent(11,10151);
   diff_true->SetBinContent(12,10235);
   diff_true->SetBinContent(13,10260);
   diff_true->SetBinContent(14,10241);
   diff_true->SetBinContent(15,9705);
   diff_true->SetBinContent(16,9060);
   diff_true->SetBinContent(17,8784);
   diff_true->SetBinContent(18,8198);
   diff_true->SetBinContent(19,8174);
   diff_true->SetBinContent(20,8463);
   diff_true->SetBinContent(21,8752);
   diff_true->SetBinContent(22,9634);
   diff_true->SetBinContent(23,9964);
   diff_true->SetBinContent(24,10657);
   diff_true->SetBinContent(25,11364);
   diff_true->SetBinContent(26,12062);
   diff_true->SetBinContent(27,13243);
   diff_true->SetBinContent(28,14422);
   diff_true->SetBinContent(29,15313);
   diff_true->SetBinContent(30,17345);
   diff_true->SetBinContent(31,18719);
   diff_true->SetBinContent(32,19926);
   diff_true->SetBinContent(33,21068);
   diff_true->SetBinContent(34,22001);
   diff_true->SetBinContent(35,22806);
   diff_true->SetBinContent(36,23447);
   diff_true->SetBinContent(37,24458);
   diff_true->SetBinContent(38,25451);
   diff_true->SetBinContent(39,27023);
   diff_true->SetBinContent(40,29071);
   diff_true->SetBinContent(41,32499);
   diff_true->SetBinContent(42,36179);
   diff_true->SetBinContent(43,40649);
   diff_true->SetBinContent(44,45470);
   diff_true->SetBinContent(45,52599);
   diff_true->SetBinContent(46,59774);
   diff_true->SetBinContent(47,67512);
   diff_true->SetBinContent(48,75397);
   diff_true->SetBinContent(49,80530);
   diff_true->SetBinContent(50,81865);
   diff_true->SetBinContent(51,80316);
   diff_true->SetBinContent(52,76144);
   diff_true->SetBinContent(53,68411);
   diff_true->SetBinContent(54,60385);
   diff_true->SetBinContent(55,50930);
   diff_true->SetBinContent(56,42000);
   diff_true->SetBinContent(57,34267);
   diff_true->SetBinContent(58,29122);
   diff_true->SetBinContent(59,25363);
   diff_true->SetBinContent(60,23148);
   diff_true->SetBinContent(61,22038);
   diff_true->SetBinContent(62,21920);
   diff_true->SetBinContent(63,21409);
   diff_true->SetBinContent(64,22268);
   diff_true->SetBinContent(65,22919);
   diff_true->SetBinContent(66,23377);
   diff_true->SetBinContent(67,24042);
   diff_true->SetBinContent(68,23353);
   diff_true->SetBinContent(69,24049);
   diff_true->SetBinContent(70,24208);
   diff_true->SetBinContent(71,24222);
   diff_true->SetBinContent(72,24482);
   diff_true->SetBinContent(73,24663);
   diff_true->SetBinContent(74,25300);
   diff_true->SetBinContent(75,25861);
   diff_true->SetBinContent(76,26524);
   diff_true->SetBinContent(77,27673);
   diff_true->SetBinContent(78,28318);
   diff_true->SetBinContent(79,29350);
   diff_true->SetBinContent(80,29800);
   diff_true->SetBinContent(81,29727);
   diff_true->SetBinContent(82,29416);
   diff_true->SetBinContent(83,28095);
   diff_true->SetBinContent(84,26488);
   diff_true->SetBinContent(85,24562);
   diff_true->SetBinContent(86,23338);
   diff_true->SetBinContent(87,21429);
   diff_true->SetBinContent(88,20232);
   diff_true->SetBinContent(89,18650);
   diff_true->SetBinContent(90,17471);
   diff_true->SetBinContent(91,16877);
   diff_true->SetBinContent(92,15862);
   diff_true->SetBinContent(93,15224);
   diff_true->SetBinContent(94,14873);
   diff_true->SetBinContent(95,14313);
   diff_true->SetBinContent(96,13712);
   diff_true->SetBinContent(97,13044);
   diff_true->SetBinContent(98,12959);
   diff_true->SetBinContent(99,12180);
   diff_true->SetBinContent(100,11707);
   diff_true->SetEntries(2461347);
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
   TText *text = pt->AddText("30 deg, lens 3, avr LUT");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
