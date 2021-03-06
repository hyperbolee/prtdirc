{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Mar  5 21:12:40 2016) by ROOT version5.34/28
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-6.25,-179072,6.25,1611648);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *diff_full = new TH1D("diff_full","35 deg, lens 3, full LUT",100,-5,5);
   diff_full->SetBinContent(1,56320);
   diff_full->SetBinContent(2,61759);
   diff_full->SetBinContent(3,67300);
   diff_full->SetBinContent(4,72314);
   diff_full->SetBinContent(5,78245);
   diff_full->SetBinContent(6,85257);
   diff_full->SetBinContent(7,93794);
   diff_full->SetBinContent(8,103761);
   diff_full->SetBinContent(9,114366);
   diff_full->SetBinContent(10,122837);
   diff_full->SetBinContent(11,131954);
   diff_full->SetBinContent(12,141295);
   diff_full->SetBinContent(13,150538);
   diff_full->SetBinContent(14,159441);
   diff_full->SetBinContent(15,166980);
   diff_full->SetBinContent(16,174314);
   diff_full->SetBinContent(17,182386);
   diff_full->SetBinContent(18,190446);
   diff_full->SetBinContent(19,197651);
   diff_full->SetBinContent(20,205217);
   diff_full->SetBinContent(21,212142);
   diff_full->SetBinContent(22,216888);
   diff_full->SetBinContent(23,221238);
   diff_full->SetBinContent(24,220947);
   diff_full->SetBinContent(25,221162);
   diff_full->SetBinContent(26,220823);
   diff_full->SetBinContent(27,220123);
   diff_full->SetBinContent(28,219425);
   diff_full->SetBinContent(29,222864);
   diff_full->SetBinContent(30,226007);
   diff_full->SetBinContent(31,232663);
   diff_full->SetBinContent(32,238314);
   diff_full->SetBinContent(33,241655);
   diff_full->SetBinContent(34,241640);
   diff_full->SetBinContent(35,238700);
   diff_full->SetBinContent(36,235663);
   diff_full->SetBinContent(37,231474);
   diff_full->SetBinContent(38,235005);
   diff_full->SetBinContent(39,245256);
   diff_full->SetBinContent(40,273557);
   diff_full->SetBinContent(41,324545);
   diff_full->SetBinContent(42,392059);
   diff_full->SetBinContent(43,482325);
   diff_full->SetBinContent(44,580555);
   diff_full->SetBinContent(45,693910);
   diff_full->SetBinContent(46,822741);
   diff_full->SetBinContent(47,974419);
   diff_full->SetBinContent(48,1125771);
   diff_full->SetBinContent(49,1267699);
   diff_full->SetBinContent(50,1348155);
   diff_full->SetBinContent(51,1364358);
   diff_full->SetBinContent(52,1317001);
   diff_full->SetBinContent(53,1217707);
   diff_full->SetBinContent(54,1074830);
   diff_full->SetBinContent(55,915104);
   diff_full->SetBinContent(56,744219);
   diff_full->SetBinContent(57,592069);
   diff_full->SetBinContent(58,470750);
   diff_full->SetBinContent(59,381767);
   diff_full->SetBinContent(60,323560);
   diff_full->SetBinContent(61,288155);
   diff_full->SetBinContent(62,268443);
   diff_full->SetBinContent(63,262956);
   diff_full->SetBinContent(64,263229);
   diff_full->SetBinContent(65,281504);
   diff_full->SetBinContent(66,304313);
   diff_full->SetBinContent(67,323550);
   diff_full->SetBinContent(68,351751);
   diff_full->SetBinContent(69,365563);
   diff_full->SetBinContent(70,377038);
   diff_full->SetBinContent(71,382996);
   diff_full->SetBinContent(72,388068);
   diff_full->SetBinContent(73,386439);
   diff_full->SetBinContent(74,388840);
   diff_full->SetBinContent(75,385050);
   diff_full->SetBinContent(76,382786);
   diff_full->SetBinContent(77,383379);
   diff_full->SetBinContent(78,381508);
   diff_full->SetBinContent(79,376490);
   diff_full->SetBinContent(80,371348);
   diff_full->SetBinContent(81,370050);
   diff_full->SetBinContent(82,365701);
   diff_full->SetBinContent(83,364857);
   diff_full->SetBinContent(84,356337);
   diff_full->SetBinContent(85,352494);
   diff_full->SetBinContent(86,346577);
   diff_full->SetBinContent(87,337013);
   diff_full->SetBinContent(88,329385);
   diff_full->SetBinContent(89,321835);
   diff_full->SetBinContent(90,311110);
   diff_full->SetBinContent(91,299939);
   diff_full->SetBinContent(92,285013);
   diff_full->SetBinContent(93,270112);
   diff_full->SetBinContent(94,254694);
   diff_full->SetBinContent(95,238301);
   diff_full->SetBinContent(96,225440);
   diff_full->SetBinContent(97,212904);
   diff_full->SetBinContent(98,199133);
   diff_full->SetBinContent(99,189320);
   diff_full->SetBinContent(100,180267);
   diff_full->SetEntries(3.630915e+07);
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
   diff_bg->SetBinContent(1,56319);
   diff_bg->SetBinContent(2,61759);
   diff_bg->SetBinContent(3,67300);
   diff_bg->SetBinContent(4,72314);
   diff_bg->SetBinContent(5,78245);
   diff_bg->SetBinContent(6,85257);
   diff_bg->SetBinContent(7,93794);
   diff_bg->SetBinContent(8,103761);
   diff_bg->SetBinContent(9,114364);
   diff_bg->SetBinContent(10,122837);
   diff_bg->SetBinContent(11,131952);
   diff_bg->SetBinContent(12,141290);
   diff_bg->SetBinContent(13,150538);
   diff_bg->SetBinContent(14,159441);
   diff_bg->SetBinContent(15,166980);
   diff_bg->SetBinContent(16,174314);
   diff_bg->SetBinContent(17,182384);
   diff_bg->SetBinContent(18,190444);
   diff_bg->SetBinContent(19,197648);
   diff_bg->SetBinContent(20,205216);
   diff_bg->SetBinContent(21,212141);
   diff_bg->SetBinContent(22,216885);
   diff_bg->SetBinContent(23,221236);
   diff_bg->SetBinContent(24,220944);
   diff_bg->SetBinContent(25,221162);
   diff_bg->SetBinContent(26,220823);
   diff_bg->SetBinContent(27,220123);
   diff_bg->SetBinContent(28,219425);
   diff_bg->SetBinContent(29,222864);
   diff_bg->SetBinContent(30,226007);
   diff_bg->SetBinContent(31,232663);
   diff_bg->SetBinContent(32,238308);
   diff_bg->SetBinContent(33,241651);
   diff_bg->SetBinContent(34,241630);
   diff_bg->SetBinContent(35,238692);
   diff_bg->SetBinContent(36,235622);
   diff_bg->SetBinContent(37,231361);
   diff_bg->SetBinContent(38,234752);
   diff_bg->SetBinContent(39,244684);
   diff_bg->SetBinContent(40,272266);
   diff_bg->SetBinContent(41,321035);
   diff_bg->SetBinContent(42,383559);
   diff_bg->SetBinContent(43,460883);
   diff_bg->SetBinContent(44,533714);
   diff_bg->SetBinContent(45,598121);
   diff_bg->SetBinContent(46,644611);
   diff_bg->SetBinContent(47,684482);
   diff_bg->SetBinContent(48,714233);
   diff_bg->SetBinContent(49,745272);
   diff_bg->SetBinContent(50,753220);
   diff_bg->SetBinContent(51,754815);
   diff_bg->SetBinContent(52,740993);
   diff_bg->SetBinContent(53,710871);
   diff_bg->SetBinContent(54,671723);
   diff_bg->SetBinContent(55,620553);
   diff_bg->SetBinContent(56,554281);
   diff_bg->SetBinContent(57,483666);
   diff_bg->SetBinContent(58,416695);
   diff_bg->SetBinContent(59,356270);
   diff_bg->SetBinContent(60,312247);
   diff_bg->SetBinContent(61,282335);
   diff_bg->SetBinContent(62,264631);
   diff_bg->SetBinContent(63,260265);
   diff_bg->SetBinContent(64,261099);
   diff_bg->SetBinContent(65,279774);
   diff_bg->SetBinContent(66,302967);
   diff_bg->SetBinContent(67,322368);
   diff_bg->SetBinContent(68,350758);
   diff_bg->SetBinContent(69,364743);
   diff_bg->SetBinContent(70,376357);
   diff_bg->SetBinContent(71,382463);
   diff_bg->SetBinContent(72,387576);
   diff_bg->SetBinContent(73,386016);
   diff_bg->SetBinContent(74,388501);
   diff_bg->SetBinContent(75,384738);
   diff_bg->SetBinContent(76,382516);
   diff_bg->SetBinContent(77,383166);
   diff_bg->SetBinContent(78,381313);
   diff_bg->SetBinContent(79,376307);
   diff_bg->SetBinContent(80,371236);
   diff_bg->SetBinContent(81,369932);
   diff_bg->SetBinContent(82,365583);
   diff_bg->SetBinContent(83,364774);
   diff_bg->SetBinContent(84,356258);
   diff_bg->SetBinContent(85,352434);
   diff_bg->SetBinContent(86,346528);
   diff_bg->SetBinContent(87,336973);
   diff_bg->SetBinContent(88,329350);
   diff_bg->SetBinContent(89,321813);
   diff_bg->SetBinContent(90,311076);
   diff_bg->SetBinContent(91,299918);
   diff_bg->SetBinContent(92,284999);
   diff_bg->SetBinContent(93,270102);
   diff_bg->SetBinContent(94,254685);
   diff_bg->SetBinContent(95,238281);
   diff_bg->SetBinContent(96,225426);
   diff_bg->SetBinContent(97,212903);
   diff_bg->SetBinContent(98,199131);
   diff_bg->SetBinContent(99,189320);
   diff_bg->SetBinContent(100,180264);
   diff_bg->SetEntries(3.132952e+07);
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
   diff_true->SetBinContent(1,1);
   diff_true->SetBinContent(9,2);
   diff_true->SetBinContent(11,2);
   diff_true->SetBinContent(12,5);
   diff_true->SetBinContent(17,2);
   diff_true->SetBinContent(18,2);
   diff_true->SetBinContent(19,3);
   diff_true->SetBinContent(20,1);
   diff_true->SetBinContent(21,1);
   diff_true->SetBinContent(22,3);
   diff_true->SetBinContent(23,2);
   diff_true->SetBinContent(24,3);
   diff_true->SetBinContent(32,6);
   diff_true->SetBinContent(33,4);
   diff_true->SetBinContent(34,10);
   diff_true->SetBinContent(35,8);
   diff_true->SetBinContent(36,41);
   diff_true->SetBinContent(37,113);
   diff_true->SetBinContent(38,253);
   diff_true->SetBinContent(39,572);
   diff_true->SetBinContent(40,1291);
   diff_true->SetBinContent(41,3510);
   diff_true->SetBinContent(42,8500);
   diff_true->SetBinContent(43,21442);
   diff_true->SetBinContent(44,46841);
   diff_true->SetBinContent(45,95789);
   diff_true->SetBinContent(46,178130);
   diff_true->SetBinContent(47,289937);
   diff_true->SetBinContent(48,411538);
   diff_true->SetBinContent(49,522427);
   diff_true->SetBinContent(50,594935);
   diff_true->SetBinContent(51,609543);
   diff_true->SetBinContent(52,576008);
   diff_true->SetBinContent(53,506836);
   diff_true->SetBinContent(54,403107);
   diff_true->SetBinContent(55,294551);
   diff_true->SetBinContent(56,189938);
   diff_true->SetBinContent(57,108403);
   diff_true->SetBinContent(58,54055);
   diff_true->SetBinContent(59,25497);
   diff_true->SetBinContent(60,11313);
   diff_true->SetBinContent(61,5820);
   diff_true->SetBinContent(62,3812);
   diff_true->SetBinContent(63,2691);
   diff_true->SetBinContent(64,2130);
   diff_true->SetBinContent(65,1730);
   diff_true->SetBinContent(66,1346);
   diff_true->SetBinContent(67,1182);
   diff_true->SetBinContent(68,993);
   diff_true->SetBinContent(69,820);
   diff_true->SetBinContent(70,681);
   diff_true->SetBinContent(71,533);
   diff_true->SetBinContent(72,492);
   diff_true->SetBinContent(73,423);
   diff_true->SetBinContent(74,339);
   diff_true->SetBinContent(75,312);
   diff_true->SetBinContent(76,270);
   diff_true->SetBinContent(77,213);
   diff_true->SetBinContent(78,195);
   diff_true->SetBinContent(79,183);
   diff_true->SetBinContent(80,112);
   diff_true->SetBinContent(81,118);
   diff_true->SetBinContent(82,118);
   diff_true->SetBinContent(83,83);
   diff_true->SetBinContent(84,79);
   diff_true->SetBinContent(85,60);
   diff_true->SetBinContent(86,49);
   diff_true->SetBinContent(87,40);
   diff_true->SetBinContent(88,35);
   diff_true->SetBinContent(89,22);
   diff_true->SetBinContent(90,34);
   diff_true->SetBinContent(91,21);
   diff_true->SetBinContent(92,14);
   diff_true->SetBinContent(93,10);
   diff_true->SetBinContent(94,9);
   diff_true->SetBinContent(95,20);
   diff_true->SetBinContent(96,14);
   diff_true->SetBinContent(97,1);
   diff_true->SetBinContent(98,2);
   diff_true->SetBinContent(100,3);
   diff_true->SetEntries(4979634);
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
   TText *text = pt->AddText("35 deg, lens 3, full LUT");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
