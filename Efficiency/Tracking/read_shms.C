
#include <sstream>
#include <string>
#include <fstream>
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TPaveLabel.h"

void read_tracking_shms(){

  TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
  c1->SetGrid();

  auto mg = new TMultiGraph("mg","TR Efficiency");
  TFile * f1 = new TFile("root/phcal_eff.root","RECREATE");

 
  //2
  std::ifstream infile2("txtfile_shms/shms_tr_eff_rate_nodelta_hit35.txt");

  std::string line2;
  vector <double> run2; 
  vector <double> rate2;//current
  vector <double> did2;
  vector <double> should2;
  vector <double> eff2;
  vector <double> eff_err2;

  while (std::getline(infile2, line2)){

    std::istringstream iss(line2);
    double a2, b2, c2, d2, e2, f2 ;
    if(line2[0] == '#') continue;

    if (!(iss >> a2 >> b2 >> c2 >> d2 >>e2 >>f2))
      {
           
	break;
           
      } 
       
    run2.push_back(a2);
    rate2.push_back(b2);
    did2.push_back(c2);
    should2.push_back(d2);
    eff2.push_back(e2);
    eff_err2.push_back(f2);

  }
  //3
  std::ifstream infile3("txtfile_shms/shms_tr_eff_rate_hit35.txt");
 std::string line3;
  vector <double> run3; 
  vector <double> rate3;
  vector <double> did3;
  vector <double> should3;
  vector <double> eff3;
  vector <double> eff_err3;

  while (std::getline(infile3, line3)){

    std::istringstream iss(line3);
    double a3, b3, c3, d3, e3, f3 ;
    if(line3[0] == '#') continue;

    if (!(iss >> a3 >> b3 >> c3 >> d3 >>e3 >>f3))
      {
           
	break;
           
      } 
       
    run3.push_back(a3);
    rate3.push_back(b3);
    did3.push_back(c3);
    should3.push_back(d3);
    eff3.push_back(e3);
    eff_err3.push_back(f3);

  }
 
  
 
 

  auto gr2 = new TGraphErrors(run2.size(), &rate2[0], &eff2[0], 0, &eff_err2[0]);
  gr2->SetName("gr2");
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerSize(1.4);
  gr2->SetTitle("35 hits: No Delta Cut (in Did)");
  gr2->SetLineColor(kRed);
  gr2->SetLineWidth(2);
  gr2->SetMarkerColor(kRed);
  gr2->SetFillStyle(0);

  auto gr3 = new TGraphErrors(run2.size(), &rate2[0], &eff3[0], 0, &eff_err3[0]);
  gr3->SetName("gr3");
  gr3->SetMarkerStyle(22);
  gr3->SetMarkerSize(1.4);
  gr3->SetTitle("35 hits: -100< PDELTA < 100 (in Did)");
  gr3->SetLineColor(kBlue);
  gr3->SetMarkerColor(kBlue);
  gr3->SetFillStyle(0);
  gr3->SetLineWidth(2);
  c1->Modified();


  mg->SetMaximum(1.0005);
  mg->SetMinimum(0.955);
  
  mg->Add(gr2);
  mg->Add(gr3);
 
  gr3->Draw("AP");//grlast->Draw();
  mg->Draw("AP");
  mg->Write();//Save as rootfile

  // mg->SetTitle("SHMS TREfficiency; Current (uA) ; SHMS TR EFF");
   mg->SetTitle("SHMS TREfficiency; PTrig1 Rate (kHz) ; SHMS TR EFF");

  //auto legend = new TLegend(0.1,0.7,0.48,0.9);
  
   
  c1->BuildLegend();

  
  mg->GetYaxis()->CenterTitle(true);
  mg->GetXaxis()->CenterTitle(true);
  mg->SaveAs("pdf/ptracking_eff.pdf");
  c1->Print("pdf/ptracking_eff.gif");

}
