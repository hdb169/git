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
void ratio_diff_3p2() {
  gStyle->SetOptStat(1111111);
  gStyle->SetErrorX(0);

  gROOT->ForceStyle(); 
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetNdivisions(505);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadLeftMargin(0.08);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadBottomMargin(.14);
  gStyle->SetTitleYOffset(0.98);//
  gStyle->SetTitleXOffset(1.00);//
  gStyle->SetTitleYSize(0.035);
  gStyle->SetTitleXSize(0.035);
  gStyle->SetLabelFont(62,"X");
  gStyle->SetLabelFont(62,"Y");
  gStyle->SetTitleFont(62,"X");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetLabelSize(0.035,"X");//
  gStyle->SetLabelSize(0.035,"Y");//
  gStyle->SetLabelFont(72);
  gStyle->SetPaperSize(23,24);
  gStyle->SetLineWidth(2);
  TFile *f1 = new TFile("root_yield/yield_pos_3p2_7767.root");//, "READ");
  TFile *f2 = new TFile("root_yield/yield_neg_3p2_7735.root");//, "READ");

#include "binz.h"
  
  TFile *f = new TFile("root_yield/ratio_3p2.root", "RECREATE");
  /////////////////////////////////////////////////D2 Target///////////////////////////////////////////////////////
  Double_t qpos= 175.122;
  Double_t qneg= 336.6;

  TH1D *pos0 = (TH1D*)f1->Get("h_dataz_cut0");
  TH1D *pos1 = (TH1D*)f1->Get("h_dataz_cut1");
  TH1D *pos2 = (TH1D*)f1->Get("h_dataz_cut2");
  TH1D *pos3 = (TH1D*)f1->Get("h_dataz_cut3");
  TH1D *pos12 = (TH1D*)f1->Get("h_dataz_cut1plus2");


  TH1D *neg0 = (TH1D*)f2->Get("h_dataz_cut0");
  TH1D *neg1 = (TH1D*)f2->Get("h_dataz_cut1");
  TH1D *neg2 = (TH1D*)f2->Get("h_dataz_cut2");
  TH1D *neg3 = (TH1D*)f2->Get("h_dataz_cut3");
  TH1D *neg12 = (TH1D*)f2->Get("h_dataz_cut1plus2");

  pos0->Scale(1/qpos);
  pos1->Scale(1/qpos);
  pos2->Scale(1/qpos);
  pos3->Scale(1/qpos);
  pos12->Scale(1/qpos);



  neg0->Scale(1/qneg);
  neg1->Scale(1/qneg);
  neg2->Scale(1/qneg);
  neg3->Scale(1/qneg);
  neg12->Scale(1/qneg);

  
  ///////////////////////////////////////////////////////Fit function  Start////////////////////



 
  double z[100];
  double Rd;
  double R_D[100];
  double ratio[100];
  double rd_ratio[100];


 


  for (int i = 0; i < 100; i++)//taking all int numbers from 0 t0 1
    {
      z[i] = i/100.0;//made each number 0.1, 0.2, 0.3, ..
    
      R_D[i] = pow((1.0-z[i]),0.083583)/pow((1.0+z[i]),1.9838);//Rd

      ratio[i]= (R_D[i]+4)/ (4*R_D[i]+1);//pi+/pi-
      // cout << z[i]<< endl;

      rd_ratio[i] = (4 - ratio [i]) / (ratio[i] - 1);//Rd_measured (4-R)/(R-1)


    }
  // TCanvas *c2=new TCanvas("c2","c2",1600,1200);
  //c2->cd();
  TGraph *gr1 = new TGraph(100, z, ratio);//to plot Yield ratio
  gr1->SetLineWidth(2);
  gr1->SetLineColor(kRed); 
  // gr1->Draw("");





  /////////////////////////////////Fit function done/////////////////////////

  TCanvas *c1 = new TCanvas ("c1", "c1", 1600, 1200);
  c1->Divide(3,2);gPad->SetGrid();
  c1->cd(1);gPad->SetGrid();
  
  TH1D *new_h00= new TH1D ("new_h00", "new_h00", binz, loz, hiz);
  new_h00->Divide(pos0,neg0);
  new_h00->SetTitle("Yield ratio #pi+/#pi- cut0");
  new_h00->Draw("e,p1");
  new_h00->SetLineWidth(2);
  new_h00->GetYaxis()->SetRangeUser(0.5,3.0);
  new_h00->GetXaxis()->SetTitle("Z_hadron");
  new_h00->GetYaxis()->SetTitle("Ratio");
  new_h00->GetYaxis()->CenterTitle();
  new_h00->GetXaxis()->CenterTitle();
  new_h00->SetMarkerColor(kBlue);
  new_h00->SetMarkerStyle(22);
  new_h00->SetLineColor(kBlue);
  gr1->Draw("same");

  c1->cd(2);gPad->SetGrid();

  TH1D *new_h11= new TH1D ("new_h11", "new_h11", binz, loz, hiz);
  new_h11->Divide(pos1,neg1);
  new_h11->SetTitle("Yield ratio #pi+/#pi- cut1");
  new_h11->Draw("e,p1");
  new_h11->SetLineWidth(2);
  new_h11->GetYaxis()->SetRangeUser(0.5,3.0);
  new_h11->GetXaxis()->SetTitle("Z_hadron");
  new_h11->GetYaxis()->SetTitle("Ratio");
  new_h11->GetYaxis()->CenterTitle();
  new_h11->GetXaxis()->CenterTitle();
  new_h11->SetMarkerColor(kGreen);
  new_h11->SetMarkerStyle(22);
  new_h11->SetLineColor(kGreen);
  gr1->Draw("same");


  c1->cd(3);gPad->SetGrid();

  TH1D *new_h22= new TH1D ("new_h22", "new_h22", binz, loz, hiz);
  new_h22->Divide(pos2,neg2);
  new_h22->SetTitle("Yield ratio #pi+/#pi- cut2");
  new_h22->Draw("e,p1");
  new_h22->SetLineWidth(2);
  new_h22->GetYaxis()->SetRangeUser(0.5,3.0);
  new_h22->GetXaxis()->SetTitle("Z_hadron");
  new_h22->GetYaxis()->SetTitle("Ratio");
  new_h22->GetYaxis()->CenterTitle();
  new_h22->GetXaxis()->CenterTitle();
  new_h22->SetMarkerColor(kBlack);
  new_h22->SetMarkerStyle(22);
  new_h22->SetLineColor(kBlack);
  gr1->Draw("same");


  c1->cd(4);gPad->SetGrid();
  TH1D *new_h33 = new TH1D ("new_h33", "new_h33", binz, loz, hiz);
  new_h33->Divide(pos3,neg3);
  new_h33->SetTitle("Yield ratio #pi+/#pi-  cut3");
  new_h33->Draw("e,p1");
  new_h33->SetLineWidth(2);
  new_h33->GetYaxis()->SetRangeUser(0.5,3.0);
  new_h33->GetXaxis()->SetTitle("Z_hadron");
  new_h33->GetYaxis()->SetTitle("Ratio");
  new_h33->GetYaxis()->CenterTitle();
  new_h33->GetXaxis()->CenterTitle();
  new_h33->SetMarkerColor(kRed);
  new_h33->SetMarkerStyle(22);
  new_h33->SetLineColor(kRed);
  gr1->Draw("same");

  c1->cd(5);gPad->SetGrid();

  TH1D *new_h12= new TH1D ("new_h12", "new_h12", binz, loz, hiz);
  new_h12->Divide(pos12,neg12);
  new_h12->SetTitle("Yield ratio #pi+/#pi-  cut1plus2");
  new_h12->Draw("e,p1");
  new_h12->SetLineWidth(2);
  new_h12->GetYaxis()->SetRangeUser(0.5,3.0);
  new_h12->GetXaxis()->SetTitle("Z_hadron");
  new_h12->GetYaxis()->SetTitle("Ratio");
  new_h12->GetYaxis()->CenterTitle();
  new_h12->GetXaxis()->CenterTitle();
  new_h12->SetLineColor(6);
  new_h12->SetMarkerColor(6);
  new_h12->SetMarkerStyle(22);
  gr1->Draw("same");

  c1->cd(6);gPad->SetGrid();
  TH1D *all = new TH1D ("all", "all", binz, loz, hiz);
  all->Draw();
  all->SetTitle("Yield ratio #pi+/#pi- All Cuts");
  new_h00->Draw("");
  new_h00->SetLineWidth(2);
  new_h00->GetYaxis()->SetRangeUser(0.5,3.0);
  new_h00->GetXaxis()->SetTitle("Z_hadron");
  new_h00->GetYaxis()->SetTitle("Ratio");
  new_h00->GetYaxis()->CenterTitle();
  new_h00->GetXaxis()->CenterTitle();
  new_h11->Draw("e,same");
  new_h22->Draw("e,same");
  new_h33->Draw("e,same");
  new_h12->Draw("e,same");
  all->Draw("e, same");
  all->SetTitle("Yield ratio #pi+/#pi- All Cuts");

  
    
  TLegend* leg = new TLegend(0.1,0.7,0.3,0.9);
  leg->AddEntry( new_h00,"cut0","L");
  leg->AddEntry( new_h11,"cut1","L");
  leg->AddEntry( new_h22,"cut2","L");
  leg->AddEntry( new_h33,"cut3","L");
  leg->AddEntry( new_h12,"cut1plus2","L");
  leg->Draw("Same");
  gPad->Update();
  c1->SaveAs("pdf_yield/ratio_allcuts.pdf");
  c1->SaveAs("pdf_yield/ratio_allcuts.png");

  ////////////////////////////////////// %difference cut12 vs cut0 ///////////////

  TH1D * diff_12_00 = new TH1D("diff_12_00","diff_12_00",binz,loz,hiz);
  TH1D * ratio_diff_12_00 = new TH1D("ratio_diff_12_00","ratio_diff_12_00",binz,loz,hiz);

  TCanvas *cc120 = new TCanvas("cc120","percent_diff",1600,1200);
  cc120->Divide(2,2);gPad->SetGrid();
  
  new_h00_copy= (TH1D*)new_h00->Clone();//copy of h00
  new_h12_copy= (TH1D*)new_h12->Clone();//copy 0f cut1plus2

  
  new_h12_copy->Add(new_h00_copy, -1);//diff of cut1plus2 and cut0 = diff
  new_h12_diff = (TH1D*)new_h12_copy->Clone();//copy of diff
  
  ratio_diff_12_00->Divide(new_h12_diff, new_h12);//diff/cut1plus2 = ratio
  ratio_diff_12_00->Scale(100.0);//ratio*100%

  cc120->cd(1);gPad->SetGrid();
  new_h00->Draw("e,p1");
 
  cc120->cd(2);gPad->SetGrid();
  new_h12->Draw("e,p1");
 
  cc120->cd(3);gPad->SetGrid();
  if(!(new_h12_diff->GetSumw2N()>0))new_h12_diff->Sumw2(kTRUE);
  new_h12_diff->Draw("e,p1");
  new_h12_diff->SetMarkerStyle(22);
  new_h12_diff->SetLineColor(kBlue);//same as diff
  new_h12_diff->SetTitle("cut1plus2 - cut0");
  new_h12_diff->GetXaxis()->SetTitle("Z_hadron");
  new_h12_diff->GetYaxis()->SetTitle("Diff.");
  new_h12_diff->GetXaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->SetRangeUser(-0.4,0.4);

  cc120->cd(4);gPad->SetGrid();
  if(!(ratio_diff_12_00->GetSumw2N()>0))ratio_diff_12_00->Sumw2(kTRUE);
  ratio_diff_12_00->Draw("e,p1");
  ratio_diff_12_00->SetMarkerStyle(22);
  ratio_diff_12_00->SetLineColor(kGreen);
  ratio_diff_12_00->SetTitle("[(cut1plus2 - cut0)/ cut1plus2]*100 (%)");
  ratio_diff_12_00->GetXaxis()->SetTitle("Z_hadron");
  ratio_diff_12_00->GetYaxis()->SetTitle("% Diff.");
  ratio_diff_12_00->GetXaxis()->CenterTitle();
  ratio_diff_12_00->GetYaxis()->CenterTitle();
  ratio_diff_12_00->GetYaxis()->SetRangeUser(-35,35); 

  cc120->SaveAs("pdf_yield/percent_diff_cut12_vs_cut0.pdf");
  cc120->SaveAs("pdf_yield/percent_diff_cut12_vs_cut0.png");

  //////////////////cu12-cut0 done///////////////

  ///////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// %difference cut12 vs cut1 ///////////////

  TH1D * diff_12_11 = new TH1D("diff_12_11","diff_12_11",binz,loz,hiz);
  TH1D * ratio_diff_12_11 = new TH1D("ratio_diff_12_11","ratio_diff_12_11",binz,loz,hiz);

  TCanvas *cc121 = new TCanvas("cc121","percent_diff",1600,1200);
  cc121->Divide(2,2);gPad->SetGrid();
  
  new_h11_copy= (TH1D*)new_h11->Clone();//copy of h11
  new_h12_copy= (TH1D*)new_h12->Clone();//copy 0f cut1plus2

  
  new_h12_copy->Add(new_h11_copy, -1);//diff of cut1plus2 and cut1 = diff
  new_h12_diff = (TH1D*)new_h12_copy->Clone();//copy of diff
  
  ratio_diff_12_11->Divide(new_h12_diff, new_h12);//diff/cut1plus2 = ratio
  ratio_diff_12_11->Scale(100.0);//ratio*111%

  cc121->cd(1);gPad->SetGrid();
  new_h11->Draw("e,p1");
 
  cc121->cd(2);gPad->SetGrid();
  new_h12->Draw("e,p1");
 
  cc121->cd(3);gPad->SetGrid();
  if(!(new_h12_diff->GetSumw2N()>0))new_h12_diff->Sumw2(kTRUE);
  new_h12_diff->Draw("e,p1");
  new_h12_diff->SetMarkerStyle(22);
  new_h12_diff->SetLineColor(kBlue);//same as diff
  new_h12_diff->SetTitle("cut1plus2 - cut1");
  new_h12_diff->GetXaxis()->SetTitle("Z_hadron");
  new_h12_diff->GetYaxis()->SetTitle("Diff.");
  new_h12_diff->GetXaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->SetRangeUser(-0.4,0.4);

  cc121->cd(4);gPad->SetGrid();
  if(!(ratio_diff_12_11->GetSumw2N()>0))ratio_diff_12_11->Sumw2(kTRUE);
  ratio_diff_12_11->Draw("e,p1");
  ratio_diff_12_11->SetMarkerStyle(22);
  ratio_diff_12_11->SetLineColor(kGreen);
  ratio_diff_12_11->SetTitle("[(cut1plus2 - cut1)/ cut1plus2]*100 (%)");
  ratio_diff_12_11->GetXaxis()->SetTitle("Z_hadron");
  ratio_diff_12_11->GetYaxis()->SetTitle("% Diff.");
  ratio_diff_12_11->GetXaxis()->CenterTitle();
  ratio_diff_12_11->GetYaxis()->CenterTitle();
  ratio_diff_12_11->GetYaxis()->SetRangeUser(-35,35); 
  
  cc121->SaveAs("pdf_yield/percent_diff_cut12_vs_cut1.pdf");
  cc121->SaveAs("pdf_yield/percent_diff_cut12_vs_cut1.png");

  //////////////////cu12-cut1 done///////////////


  ////////////////////////////////////// %difference cut12 vs cut2 ///////////////

  TH1D * diff_12_22 = new TH1D("diff_12_22","diff_12_22",binz,loz,hiz);
  TH1D * ratio_diff_12_22 = new TH1D("ratio_diff_12_22","ratio_diff_12_22",binz,loz,hiz);

  TCanvas *cc122 = new TCanvas("cc122","percent_diff",1600,1200);
  cc122->Divide(2,2);gPad->SetGrid();
  
  new_h22_copy= (TH1D*)new_h22->Clone();//copy of h22
  new_h12_copy= (TH1D*)new_h12->Clone();//copy 0f cut1plus2

  
  new_h12_copy->Add(new_h22_copy, -1);//diff of cut1plus2 and cut2 = diff
  new_h12_diff = (TH1D*)new_h12_copy->Clone();//copy of diff
  
  ratio_diff_12_22->Divide(new_h12_diff, new_h12);//diff/cut1plus2 = ratio
  ratio_diff_12_22->Scale(100.0);//ratio*221%

  cc122->cd(1);gPad->SetGrid();
  new_h22->Draw("e,p1");
 
  cc122->cd(2);gPad->SetGrid();
  new_h12->Draw("e,p1");
 
  cc122->cd(3);gPad->SetGrid();
  if(!(new_h12_diff->GetSumw2N()>0))new_h12_diff->Sumw2(kTRUE);
  new_h12_diff->Draw("e,p1");
  new_h12_diff->SetMarkerStyle(22);
  new_h12_diff->SetLineColor(kBlue);//same as diff
  new_h12_diff->SetTitle("cut1plus2 - cut2");
  new_h12_diff->GetXaxis()->SetTitle("Z_hadron");
  new_h12_diff->GetYaxis()->SetTitle("Diff.");
  new_h12_diff->GetXaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->SetRangeUser(-0.4,0.4);

  cc122->cd(4);gPad->SetGrid();
  if(!(ratio_diff_12_22->GetSumw2N()>0))ratio_diff_12_22->Sumw2(kTRUE);
  ratio_diff_12_22->Draw("e,p1");
  ratio_diff_12_22->SetMarkerStyle(22);
  ratio_diff_12_22->SetLineColor(kGreen);
  ratio_diff_12_22->SetTitle("[(cut1plus2 - cut2)/ cut1plus2]*100 (%)");
  ratio_diff_12_22->GetXaxis()->SetTitle("Z_hadron");
  ratio_diff_12_22->GetYaxis()->SetTitle("% Diff.");
  ratio_diff_12_22->GetXaxis()->CenterTitle();
  ratio_diff_12_22->GetYaxis()->CenterTitle();
  ratio_diff_12_22->GetYaxis()->SetRangeUser(-35,35); 
  
  cc122->SaveAs("pdf_yield/percent_diff_cut12_vs_cut2.pdf");
  cc122->SaveAs("pdf_yield/percent_diff_cut12_vs_cut2.png");

  //////////////////cu12-cut2 done///////////////

  
  ////////////////////////////////////// %difference cut12 vs cut3 ///////////////

  TH1D * diff_12_33 = new TH1D("diff_12_33","diff_12_33",binz,loz,hiz);
  TH1D * ratio_diff_12_33 = new TH1D("ratio_diff_12_33","ratio_diff_12_33",binz,loz,hiz);

  TCanvas *cc123 = new TCanvas("cc123","percent_diff",1600,1200);
  cc123->Divide(2,2);gPad->SetGrid();
  
  new_h33_copy= (TH1D*)new_h33->Clone();//copy of h33
  new_h12_copy= (TH1D*)new_h12->Clone();//copy 0f cut1plus2

  
  new_h12_copy->Add(new_h33_copy, -1);//diff of cut1plus2 and cut3 = diff
  new_h12_diff = (TH1D*)new_h12_copy->Clone();//copy of diff
  
  ratio_diff_12_33->Divide(new_h12_diff, new_h12);//diff/cut1plus2 = ratio
  ratio_diff_12_33->Scale(100.0);//ratio*331%

  cc123->cd(1);gPad->SetGrid();
  new_h33->Draw("e,p1");
 
  cc123->cd(2);gPad->SetGrid();
  new_h12->Draw("e,p1");
 
  cc123->cd(3);gPad->SetGrid();
  if(!(new_h12_diff->GetSumw2N()>0))new_h12_diff->Sumw2(kTRUE);
  new_h12_diff->Draw("e,p1");
  new_h12_diff->SetMarkerStyle(22);
  new_h12_diff->SetLineColor(kBlue);//same as diff
  new_h12_diff->SetTitle("cut1plus2 - cut3");
  new_h12_diff->GetXaxis()->SetTitle("Z_hadron");
  new_h12_diff->GetYaxis()->SetTitle("Diff.");
  new_h12_diff->GetXaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->CenterTitle();
  new_h12_diff->GetYaxis()->SetRangeUser(-0.4,0.4);

  cc123->cd(4);gPad->SetGrid();
  if(!(ratio_diff_12_33->GetSumw2N()>0))ratio_diff_12_33->Sumw2(kTRUE);
  ratio_diff_12_33->Draw("e,p1");
  ratio_diff_12_33->SetMarkerStyle(22);
  ratio_diff_12_33->SetLineColor(kGreen);
  ratio_diff_12_33->SetTitle("[(cut1plus2 - cut3)/ cut1plus2]*100 (%)");
  ratio_diff_12_33->GetXaxis()->SetTitle("Z_hadron");
  ratio_diff_12_33->GetYaxis()->SetTitle("% Diff.");
  ratio_diff_12_33->GetXaxis()->CenterTitle();
  ratio_diff_12_33->GetYaxis()->CenterTitle();
  ratio_diff_12_33->GetYaxis()->SetRangeUser(-35,35); 
  
  cc123->SaveAs("pdf_yield/percent_diff_cut12_vs_cut3.pdf");
  cc123->SaveAs("pdf_yield/percent_diff_cut12_vs_cut3.png");

  //////////////////cu12-cut3 done///////////////

  ////////Final fourplots
  TCanvas *cc12_0123 = new TCanvas("cc0123","percent_diff",1600,1200);
  cc12_0123->Divide(2,2);
  cc12_0123->cd(1);gPad->SetGrid();
  ratio_diff_12_00->Draw("e,p1");

  cc12_0123->cd(2);gPad->SetGrid();
  ratio_diff_12_11->Draw("e,p1");

  cc12_0123->cd(3);gPad->SetGrid();
  ratio_diff_12_22->Draw("e,p1");

  cc12_0123->cd(4);gPad->SetGrid();
  ratio_diff_12_33->Draw("e,p1");

  cc12_0123->SaveAs("pdf_yield/percent_diff_cut12_vs_cut0123.pdf");
  cc12_0123->SaveAs("pdf_yield/percent_diff_cut12_vs_cut0123.png");

 

}
