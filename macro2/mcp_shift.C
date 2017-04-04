#include "TCanvas.h"
#include "TCollection.h"
#include "TError.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TList.h"
#include "TROOT.h"
#include "TSpectrum.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TTree.h"
#include "TChain.h"

#include "../analysis.C"

void mcp_shift()
{
	gROOT->SetBatch(1);
	// variables for out tree
	int pid(0);
	double track(0); // particle track angle
	double trueang(0), bfang(0), afang(0); // true angle, angle before shift, angle after shift

	// Out file and out tree for analysis
	TString save = "mcp_shift/";
	TString pdfpath = "../data/151/reco/cs/";//"../pdfs/reco/";
	//TFile outfile(pdfpath+"shifts160.root","recreate");
	TFile outfile("shifts_data.root","recreate");
	TTree outtree("data","MCP correction data");
	outtree.Branch("track",&track,"track/D");
	outtree.Branch("pid",&pid,"pid/I");
	outtree.Branch("trueang",&trueang,"trueang/D");
	outtree.Branch("bfang",&bfang,"bfang/D");
	outtree.Branch("afang",&afang,"afang/D");

	// histogram for storing reconstrcuted thetaC for MCPs and full spectrum
	int bins = 40;
	double xlo = 0.750;
	double xhi = 0.850;
	TH1D *mcps_hist = new TH1D("mcps_hist","mcps_hist",bins,xlo,xhi);
	TH1D *full_hist = new TH1D("full_hist","full_hist",bins,xlo,xhi);
	TH1D *shft_hist = new TH1D("shft_hist","shft_hist",bins,xlo,xhi);

	// For finding files in pdfpath and looping over them
	TSystemDirectory dir(pdfpath,pdfpath);
	TList *files = dir.GetListOfFiles(); files->Sort();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	//TCanvas canv1("canv1","canv1",800,600);
	//TCanvas canv2("canv2","canv2",800,600);

	// output text files for MCP shifts
	// ofstream shift_out;
	// shift_out.open("shift_mcps100.txt",ios::app );

	// loop over all relevant files in dir
	int n(0); // counter
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith("spr.root") )
			continue; // don't process directories or non-root files

		// Get chains and track information
		TChain *reco = new TChain("reco");
		TChain *dirc = new TChain("dirc");
		reco->Add(pdfpath+fname);
		dirc->Add(pdfpath+fname);
		dirc->SetBranchAddress("theta",&track);
		dirc->GetEntry(0);

		//if(160<track || track<100) continue;

		cout << "Processing " << track << ": " << fname << endl;

		// shift_out << Form("if( abs(track-%.2f)<1 )\n{",track) << endl;
		// shift_out << "switch(PID)\n{" << endl;
		
		// loop over pions and protons
		for(pid=211; pid<=2212; pid+=2001)
		{
			TString pidstring = (pid>1000) ? "proton" : "pion";
			trueang = (pid>1000) ? 0.816760 : 0.824869; // 7 GeV prot or pion

			cout << "\t" << pidstring << endl;

			// shift_out << Form("case %d:\n",pid) << endl;
			// shift_out << "switch(mcpid)\n{" << endl;

			// find timing difference peak and project to full_hist
			double timediff;
			findPeak(reco,timediff,-1,pid);
			full_hist->Reset();
			int entries = reco->Project("full_hist","theta",Form("PID==%d && abs(diff-%f)<1",pid,timediff));

			// get peak of spectrum
			TF1 *full_fit = new TF1("full_fit","gaus+pol0(3)");
			fitPeak(full_hist,full_fit);
			bfang = full_fit->GetParameter(1);
			delete full_fit;
				
			cout << "\t\tbefore:" << bfang << endl;

			// full_hist->Draw();
			// canv.WaitPrimitive();

			// loop over each MCP
			shft_hist->Reset();
			for(int mcp=0; mcp<15; mcp++)
			{
				mcps_hist->Reset();
				
				
				int mcpentries = reco->Project("mcps_hist","theta",Form("PID==%d && abs(diff-%f)<1 && mcp==%d",pid,timediff,mcp));
				
				TF1 *mcps_fit = new TF1("mcps_fit","gaus+pol0(3)");
				int peaks = fitPeak(mcps_hist,mcps_fit);
				
				
				if(peaks<1) continue;
				if(double(mcpentries)/entries<0.05) continue;
				
				// mcps_hist->Draw();
				// canv.WaitPrimitive();
				
				double mcppeak = mcps_fit->GetParameter(1);
				double mcpshft = mcppeak - trueang;
				delete mcps_fit;

				// shift_out << Form("case %d: tangle -= %f;",mcp,mcpshft) << endl;

				// if(pid<1000 && mcp==6)
				// {
				// 	mcps_hist->Draw();
				// 	canv.WaitPrimitive();
				// }

				// cout << "\t\tmcp " << mcp << " before: " << mcppeak << endl;

				//mcps_hist->GetXaxis()->SetLimits(0.6,1);
				reco->Project("mcps_hist",Form("theta-%f",mcpshft),Form("PID==%d && abs(diff-%f)<1 && mcp==%d",pid,timediff,mcp));
				shft_hist->Add(mcps_hist);

				// spec.Search(mcps_hist);
				// cout << "\t\tmcp " << mcp << "  after: " << spec.GetPositionX()[0] << endl;

				
			}

			// shift_out << "}" << endl;

			TF1 *shft_fit = new TF1("shft_fit","gaus+pol0(3)");
			fitPeak(shft_hist,shft_fit,0.03,track);
			afang = shft_fit->GetParameter(1);
			cout << "\t\tafter: " << afang << endl;

			// canv1.cd();
			// full_hist->Draw();
			// canv2.cd();
			// shft_hist->Draw();
			// canv2.WaitPrimitive();
			delete shft_fit;

			// shft_hist->Draw();
			// canv.WaitPrimitive();

			outtree.Fill();
		}

		reco->Delete();
		dirc->Delete();

		// shift_out << "}\n}" << endl;
			
		n++;
		//if(n>0) break; // testing
	}

	outfile.Write();

	delete mcps_hist;
	delete full_hist;
	delete shft_hist;
}
