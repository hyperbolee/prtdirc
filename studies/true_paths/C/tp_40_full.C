{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Mar  5 21:13:02 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-6.25,-163860.5,6.25,1474745);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *diff_full = new TH1D("diff_full","40 deg, lens 3, full LUT",100,-5,5);
   diff_full->SetBinContent(1,36145);
   diff_full->SetBinContent(2,39582);
   diff_full->SetBinContent(3,42722);
   diff_full->SetBinContent(4,47656);
   diff_full->SetBinContent(5,54035);
   diff_full->SetBinContent(6,60523);
   diff_full->SetBinContent(7,67793);
   diff_full->SetBinContent(8,74684);
   diff_full->SetBinContent(9,80743);
   diff_full->SetBinContent(10,84869);
   diff_full->SetBinContent(11,88419);
   diff_full->SetBinContent(12,90805);
   diff_full->SetBinContent(13,92479);
   diff_full->SetBinContent(14,95126);
   diff_full->SetBinContent(15,100227);
   diff_full->SetBinContent(16,106351);
   diff_full->SetBinContent(17,113867);
   diff_full->SetBinContent(18,122601);
   diff_full->SetBinContent(19,128424);
   diff_full->SetBinContent(20,131864);
   diff_full->SetBinContent(21,133572);
   diff_full->SetBinContent(22,134590);
   diff_full->SetBinContent(23,138739);
   diff_full->SetBinContent(24,147175);
   diff_full->SetBinContent(25,161668);
   diff_full->SetBinContent(26,175146);
   diff_full->SetBinContent(27,189299);
   diff_full->SetBinContent(28,201461);
   diff_full->SetBinContent(29,209528);
   diff_full->SetBinContent(30,216542);
   diff_full->SetBinContent(31,219947);
   diff_full->SetBinContent(32,222318);
   diff_full->SetBinContent(33,219147);
   diff_full->SetBinContent(34,210886);
   diff_full->SetBinContent(35,201901);
   diff_full->SetBinContent(36,191600);
   diff_full->SetBinContent(37,184395);
   diff_full->SetBinContent(38,181917);
   diff_full->SetBinContent(39,185296);
   diff_full->SetBinContent(40,198335);
   diff_full->SetBinContent(41,224111);
   diff_full->SetBinContent(42,260499);
   diff_full->SetBinContent(43,317190);
   diff_full->SetBinContent(44,400514);
   diff_full->SetBinContent(45,517811);
   diff_full->SetBinContent(46,674735);
   diff_full->SetBinContent(47,851797);
   diff_full->SetBinContent(48,1033758);
   diff_full->SetBinContent(49,1168328);
   diff_full->SetBinContent(50,1248461);
   diff_full->SetBinContent(51,1239684);
   diff_full->SetBinContent(52,1166907);
   diff_full->SetBinContent(53,1040888);
   diff_full->SetBinContent(54,890026);
   diff_full->SetBinContent(55,732322);
   diff_full->SetBinContent(56,581139);
   diff_full->SetBinContent(57,463085);
   diff_full->SetBinContent(58,379811);
   diff_full->SetBinContent(59,321948);
   diff_full->SetBinContent(60,289191);
   diff_full->SetBinContent(61,272651);
   diff_full->SetBinContent(62,264768);
   diff_full->SetBinContent(63,261983);
   diff_full->SetBinContent(64,262122);
   diff_full->SetBinContent(65,271939);
   diff_full->SetBinContent(66,278361);
   diff_full->SetBinContent(67,283487);
   diff_full->SetBinContent(68,290564);
   diff_full->SetBinContent(69,286122);
   diff_full->SetBinContent(70,279303);
   diff_full->SetBinContent(71,272609);
   diff_full->SetBinContent(72,262533);
   diff_full->SetBinContent(73,256654);
   diff_full->SetBinContent(74,253526);
   diff_full->SetBinContent(75,249553);
   diff_full->SetBinContent(76,258669);
   diff_full->SetBinContent(77,259601);
   diff_full->SetBinContent(78,272291);
   diff_full->SetBinContent(79,280004);
   diff_full->SetBinContent(80,288552);
   diff_full->SetBinContent(81,293875);
   diff_full->SetBinContent(82,289789);
   diff_full->SetBinContent(83,283709);
   diff_full->SetBinContent(84,269218);
   diff_full->SetBinContent(85,256265);
   diff_full->SetBinContent(86,240026);
   diff_full->SetBinContent(87,221062);
   diff_full->SetBinContent(88,205805);
   diff_full->SetBinContent(89,190488);
   diff_full->SetBinContent(90,179946);
   diff_full->SetBinContent(91,168983);
   diff_full->SetBinContent(92,159251);
   diff_full->SetBinContent(93,152589);
   diff_full->SetBinContent(94,148120);
   diff_full->SetBinContent(95,142717);
   diff_full->SetBinContent(96,139960);
   diff_full->SetBinContent(97,136727);
   diff_full->SetBinContent(98,134143);
   diff_full->SetBinContent(99,131046);
   diff_full->SetBinContent(100,126378);
   diff_full->SetEntries(2.845997e+07);
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
   diff_bg->SetBinContent(1,36140);
   diff_bg->SetBinContent(2,39580);
   diff_bg->SetBinContent(3,42721);
   diff_bg->SetBinContent(4,47656);
   diff_bg->SetBinContent(5,54035);
   diff_bg->SetBinContent(6,60520);
   diff_bg->SetBinContent(7,67792);
   diff_bg->SetBinContent(8,74683);
   diff_bg->SetBinContent(9,80743);
   diff_bg->SetBinContent(10,84869);
   diff_bg->SetBinContent(11,88418);
   diff_bg->SetBinContent(12,90804);
   diff_bg->SetBinContent(13,92479);
   diff_bg->SetBinContent(14,95126);
   diff_bg->SetBinContent(15,100227);
   diff_bg->SetBinContent(16,106351);
   diff_bg->SetBinContent(17,113867);
   diff_bg->SetBinContent(18,122600);
   diff_bg->SetBinContent(19,128420);
   diff_bg->SetBinContent(20,131864);
   diff_bg->SetBinContent(21,133569);
   diff_bg->SetBinContent(22,134586);
   diff_bg->SetBinContent(23,138737);
   diff_bg->SetBinContent(24,147172);
   diff_bg->SetBinContent(25,161665);
   diff_bg->SetBinContent(26,175144);
   diff_bg->SetBinContent(27,189295);
   diff_bg->SetBinContent(28,201455);
   diff_bg->SetBinContent(29,209523);
   diff_bg->SetBinContent(30,216537);
   diff_bg->SetBinContent(31,219947);
   diff_bg->SetBinContent(32,222318);
   diff_bg->SetBinContent(33,219146);
   diff_bg->SetBinContent(34,210886);
   diff_bg->SetBinContent(35,201887);
   diff_bg->SetBinContent(36,191568);
   diff_bg->SetBinContent(37,184327);
   diff_bg->SetBinContent(38,181750);
   diff_bg->SetBinContent(39,184847);
   diff_bg->SetBinContent(40,197368);
   diff_bg->SetBinContent(41,221736);
   diff_bg->SetBinContent(42,254689);
   diff_bg->SetBinContent(43,302364);
   diff_bg->SetBinContent(44,364564);
   diff_bg->SetBinContent(45,440973);
   diff_bg->SetBinContent(46,530520);
   diff_bg->SetBinContent(47,614850);
   diff_bg->SetBinContent(48,692730);
   diff_bg->SetBinContent(49,733715);
   diff_bg->SetBinContent(50,750876);
   diff_bg->SetBinContent(51,728107);
   diff_bg->SetBinContent(52,676729);
   diff_bg->SetBinContent(53,618353);
   diff_bg->SetBinContent(54,552454);
   diff_bg->SetBinContent(55,488245);
   diff_bg->SetBinContent(56,424586);
   diff_bg->SetBinContent(57,376132);
   diff_bg->SetBinContent(58,337081);
   diff_bg->SetBinContent(59,302435);
   diff_bg->SetBinContent(60,280246);
   diff_bg->SetBinContent(61,267843);
   diff_bg->SetBinContent(62,261885);
   diff_bg->SetBinContent(63,259753);
   diff_bg->SetBinContent(64,260458);
   diff_bg->SetBinContent(65,270531);
   diff_bg->SetBinContent(66,277161);
   diff_bg->SetBinContent(67,282583);
   diff_bg->SetBinContent(68,289789);
   diff_bg->SetBinContent(69,285455);
   diff_bg->SetBinContent(70,278728);
   diff_bg->SetBinContent(71,272144);
   diff_bg->SetBinContent(72,262168);
   diff_bg->SetBinContent(73,256335);
   diff_bg->SetBinContent(74,253241);
   diff_bg->SetBinContent(75,249318);
   diff_bg->SetBinContent(76,258409);
   diff_bg->SetBinContent(77,259400);
   diff_bg->SetBinContent(78,272118);
   diff_bg->SetBinContent(79,279825);
   diff_bg->SetBinContent(80,288391);
   diff_bg->SetBinContent(81,293756);
   diff_bg->SetBinContent(82,289677);
   diff_bg->SetBinContent(83,283621);
   diff_bg->SetBinContent(84,269132);
   diff_bg->SetBinContent(85,256190);
   diff_bg->SetBinContent(86,239985);
   diff_bg->SetBinContent(87,221011);
   diff_bg->SetBinContent(88,205774);
   diff_bg->SetBinContent(89,190459);
   diff_bg->SetBinContent(90,179932);
   diff_bg->SetBinContent(91,168973);
   diff_bg->SetBinContent(92,159240);
   diff_bg->SetBinContent(93,152580);
   diff_bg->SetBinContent(94,148115);
   diff_bg->SetBinContent(95,142709);
   diff_bg->SetBinContent(96,139957);
   diff_bg->SetBinContent(97,136723);
   diff_bg->SetBinContent(98,134139);
   diff_bg->SetBinContent(99,131044);
   diff_bg->SetBinContent(100,126378);
   diff_bg->SetEntries(2.432694e+07);
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
   diff_true->SetBinContent(1,5);
   diff_true->SetBinContent(2,2);
   diff_true->SetBinContent(3,1);
   diff_true->SetBinContent(6,3);
   diff_true->SetBinContent(7,1);
   diff_true->SetBinContent(8,1);
   diff_true->SetBinContent(11,1);
   diff_true->SetBinContent(12,1);
   diff_true->SetBinContent(18,1);
   diff_true->SetBinContent(19,4);
   diff_true->SetBinContent(21,3);
   diff_true->SetBinContent(22,4);
   diff_true->SetBinContent(23,2);
   diff_true->SetBinContent(24,3);
   diff_true->SetBinContent(25,3);
   diff_true->SetBinContent(26,2);
   diff_true->SetBinContent(27,4);
   diff_true->SetBinContent(28,6);
   diff_true->SetBinContent(29,5);
   diff_true->SetBinContent(30,5);
   diff_true->SetBinContent(33,1);
   diff_true->SetBinContent(35,14);
   diff_true->SetBinContent(36,32);
   diff_true->SetBinContent(37,68);
   diff_true->SetBinContent(38,167);
   diff_true->SetBinContent(39,449);
   diff_true->SetBinContent(40,967);
   diff_true->SetBinContent(41,2375);
   diff_true->SetBinContent(42,5810);
   diff_true->SetBinContent(43,14826);
   diff_true->SetBinContent(44,35950);
   diff_true->SetBinContent(45,76838);
   diff_true->SetBinContent(46,144215);
   diff_true->SetBinContent(47,236947);
   diff_true->SetBinContent(48,341028);
   diff_true->SetBinContent(49,434613);
   diff_true->SetBinContent(50,497585);
   diff_true->SetBinContent(51,511577);
   diff_true->SetBinContent(52,490178);
   diff_true->SetBinContent(53,422535);
   diff_true->SetBinContent(54,337572);
   diff_true->SetBinContent(55,244077);
   diff_true->SetBinContent(56,156553);
   diff_true->SetBinContent(57,86953);
   diff_true->SetBinContent(58,42730);
   diff_true->SetBinContent(59,19513);
   diff_true->SetBinContent(60,8945);
   diff_true->SetBinContent(61,4808);
   diff_true->SetBinContent(62,2883);
   diff_true->SetBinContent(63,2230);
   diff_true->SetBinContent(64,1664);
   diff_true->SetBinContent(65,1408);
   diff_true->SetBinContent(66,1200);
   diff_true->SetBinContent(67,904);
   diff_true->SetBinContent(68,775);
   diff_true->SetBinContent(69,667);
   diff_true->SetBinContent(70,575);
   diff_true->SetBinContent(71,465);
   diff_true->SetBinContent(72,365);
   diff_true->SetBinContent(73,319);
   diff_true->SetBinContent(74,285);
   diff_true->SetBinContent(75,235);
   diff_true->SetBinContent(76,260);
   diff_true->SetBinContent(77,201);
   diff_true->SetBinContent(78,173);
   diff_true->SetBinContent(79,179);
   diff_true->SetBinContent(80,161);
   diff_true->SetBinContent(81,119);
   diff_true->SetBinContent(82,112);
   diff_true->SetBinContent(83,88);
   diff_true->SetBinContent(84,86);
   diff_true->SetBinContent(85,75);
   diff_true->SetBinContent(86,41);
   diff_true->SetBinContent(87,51);
   diff_true->SetBinContent(88,31);
   diff_true->SetBinContent(89,29);
   diff_true->SetBinContent(90,14);
   diff_true->SetBinContent(91,10);
   diff_true->SetBinContent(92,11);
   diff_true->SetBinContent(93,9);
   diff_true->SetBinContent(94,5);
   diff_true->SetBinContent(95,8);
   diff_true->SetBinContent(96,3);
   diff_true->SetBinContent(97,4);
   diff_true->SetBinContent(98,4);
   diff_true->SetBinContent(99,2);
   diff_true->SetEntries(4133034);
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
   TText *text = pt->AddText("40 deg, lens 3, full LUT");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
