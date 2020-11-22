
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

void read_hcal_eff(){

  TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
     c1->SetGrid();

  auto mg = new TMultiGraph("mg","HCAL Efficiency");
  TFile * f1 = new TFile("root/hcal_eff.root","RECREATE");
 
  //2
  std::ifstream infile2("txtfile/hcal_eff_noxptar_10_8.txt");

  std::string line2;
  vector <double> run2; 
  vector <double> mom2;
  vector <double> eff2;
  vector <double> eff_err2;

  while (std::getline(infile2, line2)){

    std::istringstream iss(line2);
    double a2, b2, c2, d2 ;
    if (!(iss >> a2 >> b2 >> c2 >> d2 ))
      {
           
	break;
           
      } 
       
    run2.push_back(a2);
    mom2.push_back(b2);
    eff2.push_back(c2);
    eff_err2.push_back(d2);

  }
  //3
  std::ifstream infile3("txtfile/hcal_eff_xptar_10_8.txt"); 

  std::string line3;
  vector <double> run3; 
  vector <double> mom3;
  vector <double> eff3;
  vector <double> eff_err3;

  while (std::getline(infile3, line3)){

    std::istringstream iss(line3);
    double a3, b3, c3, d3 ;
    if (!(iss >> a3 >> b3 >> c3 >> d3 ))
      {
           
	break;
           
      } 
       
    run3.push_back(a3);
    mom3.push_back(b3);
    eff3.push_back(c3);
    eff_err3.push_back(d3);

  }
  
  //4
  std::ifstream infile4("txtfile/hcal_eff_xptar_12_8.txt"); 

  std::string line4;
  vector <double> run4; 
  vector <double> mom4;
  vector <double> eff4;
  vector <double> eff_err4;

  while (std::getline(infile4, line4)){

    std::istringstream iss(line4);
    double a4, b4, c4, d4 ;
    if (!(iss >> a4 >> b4 >> c4 >> d4 ))
      {
           
	break;
           
      } 
       
    run4.push_back(a4);
    mom4.push_back(b4);
    eff4.push_back(c4);
    eff_err4.push_back(d4);
  }
  //5

  std::ifstream infile5("txtfile/hcal_eff_xptar_10_8_hms0p8_shms0p7.txt");

  std::string line5;
  vector <double> run5; 
  vector <double> mom5;
  vector <double> eff5;
  vector <double> eff_err5;

  while (std::getline(infile5, line5)){

    std::istringstream iss(line5);
    double a5, b5, c5, d5 ;
    if (!(iss >> a5 >> b5 >> c5 >> d5 ))
      {
           
	break;
           
      } 
       
    run5.push_back(a5);
    mom5.push_back(b5);
    eff5.push_back(c5);
    eff_err5.push_back(d5);
  }

  //6

  std::ifstream infile6("txtfile/hcal_eff_xptar_10_8_hms0p8_shms0p8.txt");

  std::string line6;
  vector <double> run6; 
  vector <double> mom6;
  vector <double> eff6;
  vector <double> eff_err6;

  while (std::getline(infile6, line6)){

    std::istringstream iss(line6);
    double a6, b6, c6, d6 ;
    if (!(iss >> a6 >> b6 >> c6 >> d6 ))
      {
           
	break;
           
      } 
       
    run6.push_back(a6);
    mom6.push_back(b6);
    eff6.push_back(c6);
    eff_err6.push_back(d6);
  }
  //7
 std::ifstream infile7("txtfile/hcal_eff_xptar_12_10.txt");

  std::string line7;
  vector <double> run7; 
  vector <double> mom7;
  vector <double> eff7;
  vector <double> eff_err7;

  while (std::getline(infile7, line7)){

    std::istringstream iss(line7);
    double a7, b7, c7, d7 ;
    if (!(iss >> a7 >> b7 >> c7 >> d7 ))
      {
           
	break;
           
      } 
       
    run7.push_back(a7);
    mom7.push_back(b7);
    eff7.push_back(c7);
    eff_err7.push_back(d7);
  }


 
  
  // TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
  // c1->Divide(1,1);
  // c1->cd(1);
  // auto mg = new TMultiGraph("mg","HCAL Efficiency");


  auto gr2 = new TGraphErrors(run2.size(), &mom2[0], &eff2[0], 0, &eff_err2[0]);
  gr2->SetName("gr2");
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerSize(1.4);
  gr2->SetTitle("No_Acc_hcer10_aero8_hcal0p7_pcal0p8");
  gr2->SetLineColor(kRed);
  gr2->SetLineWidth(2);
  gr2->SetMarkerColor(kRed);
  gr2->SetFillStyle(0);

  auto gr3 = new TGraphErrors(run2.size(), &mom2[0], &eff3[0], 0, &eff_err3[0]);
  gr3->SetName("gr3");
  gr3->SetMarkerStyle(22);
  gr3->SetMarkerSize(1.4);
  gr3->SetTitle("Acc_hcer10_aero8_hcal0p7_pcal0p8");
  gr3->SetLineColor(kBlue);
  gr3->SetMarkerColor(kBlue);
  gr3->SetFillStyle(0);
  gr3->SetLineWidth(2);

  auto gr4 = new TGraphErrors(run2.size(), &mom2[0], &eff4[0], 0, &eff_err4[0]);
  gr4->SetName("gr4");
  gr4->SetMarkerStyle(23);
  gr4->SetMarkerSize(1.4);
  gr4->SetTitle("Acc_hcer12_aero8_hcal0p7_pcal0p8 (Best)");
  gr4->SetMarkerColor(kGreen);
  gr4->SetLineColor(kGreen);
  gr4->SetFillStyle(0);
  gr4->SetLineWidth(2);

  auto gr5 = new TGraphErrors(run2.size(), &mom2[0], &eff5[0], 0, &eff_err5[0]);
  gr5->SetName("gr5");
  gr5->SetMarkerStyle(21);
  gr5->SetMarkerSize(1.4);
  gr5->SetTitle("Acc_hcer10_aero8_hcal0p8_pcal0p7");
  gr5->SetLineColor(kBlack);
  gr5->SetMarkerColor(kBlack);
  gr5->SetFillStyle(0);
  gr5->SetLineWidth(2);

  auto gr6 = new TGraphErrors(run2.size(), &mom2[0], &eff6[0], 0, &eff_err6[0]);
  gr6->SetName("gr6");
  gr6->SetMarkerStyle(34);
  gr6->SetMarkerSize(1.4);
  gr6->SetTitle("Acc_hcer10_aero8_hcal0p7_pcal0p7");
  gr6->SetMarkerColor(kMagenta);
  gr6->SetLineColor(kMagenta);
  gr6->SetFillStyle(0);
  gr6->SetLineWidth(2);
  gr6->GetYaxis()->SetLimits(0,1.1);

 auto gr7 = new TGraphErrors(run2.size(), &mom2[0], &eff7[0], 0, &eff_err7[0]);
  gr7->SetName("gr7");
  gr7->SetMarkerStyle(2);
  gr7->SetMarkerSize(1.4);
  gr7->SetTitle("Acc_hcer10_aero10_hcal0p7_pcal0p8");
  gr7->SetMarkerColor(9);
  gr7->SetLineColor(9);
  gr7->SetFillStyle(0);
  gr7->SetLineWidth(2);
  gr7->GetYaxis()->SetLimits(0,1.1);


  
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Add(gr4);
  mg->Add(gr5);
  mg->Add(gr6);
  mg->Add(gr7);
  //grlast->Draw("AP");//IMPORTANT
  gr7->Draw("AP");
  mg->Draw("AP");
  mg->Write();//Save as rootfile

   mg->SetTitle("HCAL Efficiency vs Momentum; Momentum (GeV)  ; HCAL EFF");
 
   //auto legend = new TLegend(0.1,0.7,0.48,0.9);
  
   
    c1->BuildLegend();
  
  
   mg->GetYaxis()->CenterTitle(true);
   mg->GetXaxis()->CenterTitle(true);
   c1->Print("pdf/hcal_eff.gif");
  //mg->Print("name.pdf"), will print all data points

}
