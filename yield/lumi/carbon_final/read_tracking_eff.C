#include <TSystem.h>
#include <TString.h>
#include "TFile.h"
#include "TTree.h"
#include <TNtuple.h>
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TText.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TROOT.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveLabel.h>
#include <TProfile.h>
#include <TPolyLine.h>
#include <TObjArray.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include<math.h>
void read_tracking_eff()
{

  //std::ifstream infile("txtfile_hms/hms_tracking_eff_pid.txt");
  std::ifstream infile("txtfile_shms/shms_tracking_eff_pid.txt");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(1000011);
  gStyle->SetOptFit(0);
  gStyle->SetTitleOffset(1.4,"Y");
  gStyle->SetTitleOffset(0.85,"X");
  gStyle->SetLabelSize(0.05,"XY");
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetTitleFontSize(0.05);
  gStyle->GetAttDate()->SetTextAlign();
  gStyle->SetTitleX(0.5f);
  gStyle->SetTitleW(0.8f);

  std::string line;
  vector <double> run;
  vector <double> current;
  vector <double> rate;
  vector <double> treff;
  vector <double> treff_err;
  
  // cout<<"I am good "<<endl;


  

  while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      double a,  b, c, d, e;
      if(line[0] == '#') continue;
      
      if (!(iss >> a >> b >> c >> d >> e))
        {
           
	  break;
           
        } 
       
      run.push_back(a);
      current.push_back(b);
      rate.push_back(c);
      treff.push_back(d);
      treff_err.push_back(e);
      
     
      

     
     
    }

  for (int i =0; i< run.size(); i++)
    {
      
      cout<< run[i] <<"    "<<  current[i]<<"    "<<endl;
      cout<<"I am good"<<endl;

    }
  cout<< "I am good"<<endl;
  
  auto gr1 = new TGraphErrors(run.size(), &current[0], &treff[0], 0, &treff_err[0]);
 
  auto gr2 = new TGraphErrors(run.size(), &rate[0], &treff[0], 0, &treff_err[0]);
  

  auto mg = new TMultiGraph();

  TCanvas *c1 = new TCanvas ("c1", "c1", 1600, 1200);
  c1->Divide(2,2);
  c1->cd(1);gPad->SetGrid();
  gr1->SetName("gr1");
  gr1->SetTitle("Tracking Eff vs Current");
  gr1->SetMarkerStyle(4);//24
  gr1->SetDrawOption("AP");
  gr1->SetLineColor(2);
  gr1->SetMarkerColor(2);
  gr1->SetMarkerSize(2);
  gr1->SetLineWidth(2);
  gr1->SetFillStyle(0);
  gr1->GetXaxis()->SetAxisColor(17);
  gr1->GetYaxis()->SetAxisColor(17);
  gr1->GetXaxis()->SetTitle("Current(uA)");
  gr1->GetYaxis()->SetTitle("Tracking Efficiency");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();

  gr1->Draw("AP");

  c1->cd(2);gPad->SetGrid();
  gr2->SetName("gr2");
  gr2->SetTitle("Tracking Eff vs Rate ");
  gr2->SetMarkerStyle(4);//24
  gr2->SetDrawOption("AP");
  gr2->SetLineColor(2);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerSize(2);
  gr2->SetLineWidth(2);
  gr2->SetFillStyle(0);
  gr2->GetXaxis()->SetAxisColor(17);
  gr2->GetYaxis()->SetAxisColor(17);
  gr2->GetXaxis()->SetTitle("ElReal Rate(kHz)");
  gr2->GetYaxis()->SetTitle("Tracking Efficiency");
  gr2->GetXaxis()->CenterTitle();
  gr2->GetYaxis()->CenterTitle();

  gr2->Draw("AP");




  
 
}
