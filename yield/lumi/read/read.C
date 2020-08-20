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

void read()
{
 
 std::ifstream infile3("../txtfile_shms/shms_yield_elclean_elt.txt");


  // std::ifstream infile3("trash.txt"); 
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
      if (!(iss >> a3>> b3 >>c3 >>d3>>e3 ))
        {
           
	  break;
           
        } // error
       
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
 

  TCanvas *c3 = new TCanvas ("c3", "c3", 800, 500);
  c3->cd();gPad->SetGridx();gPad->SetGridy();
   
  //auto mg = new TMultiGraph();
  //auto *gr3 = new TGraph(100, z, ratio_fit);//to plot Yield rati

  auto gr2 = new TGraphErrors(run3.size(), &current[0], &yield[0], 0, &error[0]);

  // auto gr2 = new TGraphErrors(run3.size(), &rate[0], &yield[0], 0, &error[0]);
  gr2->Draw("AP");
  gr2->SetMarkerColor(kBlack);
  gr2->SetLineColor(kBlack);
  gr2->SetLineWidth(3);
  gr2->SetMarkerSize(3);
  
   gr2->GetXaxis()->SetTitle("current (uA)");

  // gr2->GetXaxis()->SetTitle("ELReal Rate (kHz)");
  //gr2->GetYaxis()->SetTitle("SHMS Yield (counts/uC)");
   //  gr2->SetTitle("SHMS Yield : Counts/(Q * Clt * Tr. Eff. * ELT)");
   gr2->SetTitle("SHMS Yield 5347-5350 : Counts/(Q * Clt * Tr. Eff.)");
  // gr2->SetTitle("SHMS Yield 5347-5350 : Elreal Counts/Charge");
    gr2->SetTitle("SHMS Yield 5347-5350 : Elreal Counts/Charge");

  // gr2->GetYaxis()->SetRangeUser(1.5, 1.9);
  //gr2->GetYaxis()->SetRangeUser(1, 2.2);
  gr2->GetXaxis()->CenterTitle();
  gr2->GetYaxis()->CenterTitle();
  //gr2->GetXaxis()->SetLimits(0.35, 0.75);
  //gr2->SetName("gr2");
   gr2->Fit("pol1");
  gr2->Draw("AP");
  gr2->SetMarkerStyle(20);
  gStyle->SetOptFit();
  // gr2->SaveAs("pdf/shms_singles_5347_50_counts_QLTTR.pdf");
  TString outputpdf;
  outputpdf = "pdf/yield_clt_tr.pdf";
  c3->Print(outputpdf);
}
