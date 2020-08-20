#define ROOT_header
#include "TH1F.h"
#include "TH2F.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TDecompLU.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <time.h>
#include <vector>
#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>
#include <sstream>
#include <string>
#include <fstream>

void read_yield_clt_untr_vs_rate()//------------------------------6
{
#include "gStyle.h"
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);

  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(1000011);
  // gStyle->SetOptFit(0);
  gStyle->SetTitleOffset(1.2,"Y");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetLabelSize(0.04,"XY");
  gStyle->SetTitleSize(0.04,"XY");
  gStyle->SetPadLeftMargin(0.16);
  
  std::ifstream infile3("../txtfile_shms/shms_yield_notrack_clt.txt");//------------------------5

 
  std::string line3;
  vector <double> run3;
  vector <double> current;
  vector <double> rate;
  vector <double> yield;
  vector <double> error;

  while (std::getline(infile3, line3))
    {
      std::istringstream iss(line3);
      double a3, b3, c3, d3, e3;
      if(line3[0] == '#') continue;

      
      if (!(iss >> a3>> b3 >>c3 >>d3>>e3 ))
        {
           
	  break;
           
        } 
       
      run3.push_back(a3);
      current.push_back(b3);
      rate.push_back(c3);
      yield.push_back(d3);
      error.push_back(e3);


    }

  for (int i =0; i< run3.size(); i++)
    {
      cout<< run3[i] <<endl;
     
    }
  cout<< "I am good"<<endl;
  auto gr1 = new TGraphErrors(run3.size(), &rate[0], &yield[0], 0, &error[0]);//-----------------4


  TCanvas *c3 = new TCanvas ("c3", "c3", 1300, 700);
  c3->cd();gPad->SetGridx();gPad->SetGridy();
  gr1->Draw("AP");
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3);
  gr1->GetXaxis()->SetTitle("PTRIG2 Rate (kHz)");//----------------------------------------------1
  gr1->GetYaxis()->SetTitle("Yield (Untracked)  Clt  (counts/uC)");//---------------2
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  gr1->Draw("AP");
  gr1->Fit("pol1");

  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString title = "SHMS (e-) : D2: 5347-5350:  Yield = Good Counts no track/(Q *clt)  :";//-------------------------3

  TF1 *fit = gr1->GetFunction("pol1");
  Double_t p1 = fit->GetParameter(1);
  Double_t p1_err = fit->GetParError(1);
  Double_t p0 = fit->GetParameter(0);
  Double_t slope_per100=p1/p0*100*100;
  Double_t slope_per100_err= p1_err/p0*100*100;
  TString slop=Form(" Slope per 100uA  = %f +/- %f",slope_per100,slope_per100_err);
  gr1->SetTitle(title+slop);
  cout<<slop<<endl;
  c3->Print("pdf/yield_shms_5347_5350_clt_untr_vs_rate.pdf");//---------------------------------------7


}
