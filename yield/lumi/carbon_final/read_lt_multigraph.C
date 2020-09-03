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
void read_lt_multigraph()
{

  // std::ifstream infile("txtfile_hms/hms_livetime_clt_edtmlt_edtmsublt.txt");
   std::ifstream infile("txtfile_shms/shms_livetime_clt_edtmlt_edtmsublt.txt");

  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(1000011);
  gStyle->SetOptFit(0);
  gStyle->SetTitleOffset(1.2,"Y");
  gStyle->SetTitleOffset(.7,"X");
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
  vector <double> edtmlt;
  vector <double> edtmlt_err;
  vector <double> clt;
  vector <double> clt_err;
  vector <double> edtm_sub_lt;
  vector <double> edtm_sub_lt_err;
 

  // cout<<"I am good "<<endl;


  

  while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      double a,  b, c, d, e, f, g, h, i;
      if(line[0] == '#') continue;
      
      if (!(iss >> a >> b >> c >> d >> e >> f >> g >> h >>i))
        {
           
	  break;
           
        } 
       
      run.push_back(a);
      current.push_back(b);
      rate.push_back(c);
      edtmlt.push_back(d);
      edtmlt_err.push_back(e);
      clt.push_back(f);
      clt_err.push_back(g);
      edtm_sub_lt.push_back(h);
      edtm_sub_lt_err.push_back(i);
     
      

     
     
    }

  for (int i =0; i< run.size(); i++)
    {
      
      cout<< run[i] <<"    "<<  current[i]<<"    "<<endl;
      cout<<"I am good"<<endl;

    }
  cout<< "I am good"<<endl;
  
  auto gr1 = new TGraphErrors(run.size(), &current[0], &edtmlt[0], 0, &edtmlt_err[0]);
 
  auto gr2 = new TGraphErrors(run.size(), &current[0], &clt[0], 0, &clt_err[0]);
  
  auto gr3 = new TGraphErrors(run.size(), &current[0], &edtm_sub_lt[0], 0, &edtm_sub_lt_err[0]);

  auto mg = new TMultiGraph();

  TCanvas *c1 = new TCanvas ("c1", "c1", 1600, 1200);
  //c1->Divide(1,1);
  c1->cd();gPad->SetGrid();
  //auto gr1 = new TGraph( size, px, py1 );
  gr1->SetName("gr1");
  gr1->SetTitle("Total LT");
  gr1->SetMarkerStyle(4);//24
  gr1->SetDrawOption("AP");
  gr1->SetLineColor(2);
  gr1->SetMarkerColor(2);
  gr1->SetMarkerSize(2);
  gr1->SetLineWidth(2);
  gr1->SetFillStyle(0);
  gr1->GetXaxis()->SetAxisColor(17);
  gr1->GetYaxis()->SetAxisColor(17);
  
  // auto gr2 = new TGraph( size, px, py2 );
  gr2->SetName("gr2");
  gr2->SetTitle("CLT for all Events");
  gr2->SetMarkerStyle(4);//25
  gr2->SetLineColor(3);
  gr2->SetMarkerColor(3);
  gr2->SetDrawOption("P");
  gr2->SetLineWidth(2);
  gr2->SetFillStyle(0);
  gr2->SetMarkerSize(2);

  //auto gr3 = new TGraph( size, px, py3 );
  gr3->SetName("gr3");
  gr3->SetTitle("CLT for Physics Events");
  gr3->SetMarkerStyle(4);//16
  gr3->SetMarkerSize(3);
  gr3->SetLineColor(4);
  gr3->SetMarkerColor(4);
  gr3->SetLineWidth(2);
  gr3->SetFillStyle(0);
  gr3->SetMarkerSize(2);
  //mg->Add( gr1 );
  //mg->Add( gr2 );
  //gr3->Draw("AP");
  mg->Add( gr2 );
  mg->Add( gr3 );
  gr1->Draw("AP");
  
  mg->Draw("P");
  gr1->GetYaxis()->SetTitle("LT");
  gr1->GetXaxis()->SetTitle("Current (uA)");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  mg->SetTitle("Live Time vs Current");
  c1->BuildLegend();
  
 
}
