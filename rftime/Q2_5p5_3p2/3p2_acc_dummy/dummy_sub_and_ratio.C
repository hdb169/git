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
void ratio_diff_3p2_dummysub() {
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
  TFile *f3 = new TFile("root_yield/yield_pos_3p2dummy_7772.root");//, "READ");
  TFile *f4 = new TFile("root_yield/yield_neg_3p2dummy_7727.root");//, "READ");
  
#include "binz.h"
  
  TFile *f = new TFile("root_yield/ratio_3p2.root", "RECREATE");
  /////////////////////////////////////////////////D2 Target///////////////////////////////////////////////////////
  Double_t qpos= 175.122;
  Double_t qneg= 336.6;
  Double_t dummy_factor = 0.244;
  Double_t qposd= 124.745 / dummy_factor;//Q dummy pos / dummy_factor =>(counts *  0.244) /charge = counts / (charge/0.244) 
  Double_t qnegd= 243.330 / dummy_factor;//Q dummy neg / Dummy factor

  TH1D *pos0 = (TH1D*)f1->Get("h_dataz_cut0");
  TH1D *pos1 = (TH1D*)f1->Get("h_dataz_cut1");
  TH1D *pos2 = (TH1D*)f1->Get("h_dataz_cut2");
  TH1D *pos3 = (TH1D*)f1->Get("h_dataz_cut3");
  TH1D *pos12 = (TH1D*)f1->Get("h_dataz_cut1plus2");
  //dummy ===d
  TH1D *pos0d = (TH1D*)f3->Get("h_dataz_cut0");
  TH1D *pos1d = (TH1D*)f3->Get("h_dataz_cut1");
  TH1D *pos2d = (TH1D*)f3->Get("h_dataz_cut2");
  TH1D *pos3d = (TH1D*)f3->Get("h_dataz_cut3");
  TH1D *pos12d = (TH1D*)f3->Get("h_dataz_cut1plus2");


  TH1D *neg0 = (TH1D*)f2->Get("h_dataz_cut0");
  TH1D *neg1 = (TH1D*)f2->Get("h_dataz_cut1");
  TH1D *neg2 = (TH1D*)f2->Get("h_dataz_cut2");
  TH1D *neg3 = (TH1D*)f2->Get("h_dataz_cut3");
  TH1D *neg12 = (TH1D*)f2->Get("h_dataz_cut1plus2");

  //dummy ===d
  TH1D *neg0d = (TH1D*)f4->Get("h_dataz_cut0");
  TH1D *neg1d = (TH1D*)f4->Get("h_dataz_cut1");
  TH1D *neg2d = (TH1D*)f4->Get("h_dataz_cut2");
  TH1D *neg3d = (TH1D*)f4->Get("h_dataz_cut3");
  TH1D *neg12d = (TH1D*)f4->Get("h_dataz_cut1plus2");


  cout<<"I am good"<<endl;
  
 
  
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
  //gr1->Draw("");


  /////////////////////////////////Fit function done/////////////////////////
  //// ============== data dummy yield calculation======================
  ///////Define copy hist////////
  
  TH1D * pos0_copy  = new TH1D ("pos0_copy","pos0_copy", binz, loz, hiz);
  TH1D * pos1_copy  = new TH1D ("pos1_copy","pos1_copy", binz, loz, hiz);
  TH1D * pos2_copy  = new TH1D ("pos2_copy","pos2_copy", binz, loz, hiz);
  TH1D * pos3_copy  = new TH1D ("pos3_copy","pos3_copy", binz, loz, hiz);
  TH1D * pos12_copy = new TH1D ("pos12_copy","pos12_copy", binz, loz, hiz);

  TH1D * pos0d_copy  = new TH1D ("pos0d_copy","pos0d_copy", binz, loz, hiz);
  TH1D * pos1d_copy  = new TH1D ("pos1d_copy","pos1d_copy", binz, loz, hiz);
  TH1D * pos2d_copy  = new TH1D ("pos2d_copy","pos2d_copy", binz, loz, hiz);
  TH1D * pos3d_copy  = new TH1D ("pos3d_copy","pos3d_copy", binz, loz, hiz);
  TH1D * pos12d_copy = new TH1D ("pos12d_copy","pos12d_copy", binz, loz, hiz);

  TH1D * neg0_copy  = new TH1D ("neg0_copy","neg0_copy", binz, loz, hiz);
  TH1D * neg1_copy  = new TH1D ("neg1_copy","neg1_copy", binz, loz, hiz);
  TH1D * neg2_copy  = new TH1D ("neg2_copy","neg2_copy", binz, loz, hiz);
  TH1D * neg3_copy  = new TH1D ("neg3_copy","neg3_copy", binz, loz, hiz);
  TH1D * neg12_copy = new TH1D ("neg12_copy","neg12_copy", binz, loz, hiz);

  TH1D * neg0d_copy  = new TH1D ("neg0d_copy","neg0d_copy", binz, loz, hiz);
  TH1D * neg1d_copy  = new TH1D ("neg1d_copy","neg1d_copy", binz, loz, hiz);
  TH1D * neg2d_copy  = new TH1D ("neg2d_copy","neg2d_copy", binz, loz, hiz);
  TH1D * neg3d_copy  = new TH1D ("neg3d_copy","neg3d_copy", binz, loz, hiz);
  TH1D * neg12d_copy = new TH1D ("neg12d_copy","neg12d_copy", binz, loz, hiz);


  cout<<"I am still good"<<endl;
  
  ///////Define copy hist done////////

  //for pos data
  pos0_copy  = (TH1D*)pos0->Clone();
  pos1_copy  =  (TH1D*)pos1->Clone();
  pos2_copy  =  (TH1D*)pos2->Clone();
  pos3_copy  =  (TH1D*)pos3->Clone();
  pos12_copy =  (TH1D*)pos12->Clone();

  //for pos dummy
  pos0d_copy  = (TH1D*)pos0d->Clone();
  pos1d_copy  =  (TH1D*)pos1d->Clone();
  pos2d_copy  =  (TH1D*)pos2d->Clone();
  pos3d_copy  =  (TH1D*)pos3d->Clone();
  pos12d_copy =  (TH1D*)pos12d->Clone();

  //for neg data
  neg0_copy  = (TH1D*)neg0->Clone();
  neg1_copy  =  (TH1D*)neg1->Clone();
  neg2_copy  =  (TH1D*)neg2->Clone();
  neg3_copy  =  (TH1D*)neg3->Clone();
  neg12_copy =  (TH1D*)neg12->Clone();

  //for neg dummy
  neg0d_copy  = (TH1D*)neg0d->Clone();
  neg1d_copy  =  (TH1D*)neg1d->Clone();
  neg2d_copy  =  (TH1D*)neg2d->Clone();
  neg3d_copy  =  (TH1D*)neg3d->Clone();
  neg12d_copy =  (TH1D*)neg12d->Clone();


  //////////////////////check start for data dummy counts cloned files //////////////////

  //counts histograms only for data and dummy
  TCanvas *d1 = new TCanvas ("d1","d1",1600,1200);
  d1->Divide(5,2);
  
  d1->cd(1);
  pos0_copy->Draw("e, p1");
  pos0d_copy->Draw("e,same");
  pos0_copy->GetXaxis()->SetTitle("Z_hadron");
  pos0_copy->GetYaxis()->SetTitle("Counts Pi+ Data and Dummy");
  pos0_copy->GetYaxis()->CenterTitle();
  pos0_copy->GetXaxis()->CenterTitle();
  pos0_copy->SetMarkerColor(kBlue);
  pos0_copy->SetMarkerStyle(22);
  pos0_copy->SetLineColor(kBlue);
  pos0_copy->SetLineWidth(2);
  pos0d_copy->SetMarkerColor(kRed);
  pos0d_copy->SetMarkerStyle(22);
  pos0d_copy->SetLineColor(kRed);
  pos0d_copy->SetLineWidth(2);
  
  d1->cd(2);
  pos1_copy->Draw("e,p1");
  pos1d_copy->Draw("e,same");
  pos1_copy->GetXaxis()->SetTitle("Z_hadron");
  pos1_copy->GetYaxis()->SetTitle("Counts Pi+ Data and Dummy");
  pos1_copy->GetYaxis()->CenterTitle();
  pos1_copy->GetXaxis()->CenterTitle();
  pos1_copy->SetMarkerColor(kBlue);
  pos1_copy->SetMarkerStyle(22);
  pos1_copy->SetLineColor(kBlue);
  pos1_copy->SetLineWidth(2);
  pos1d_copy->SetMarkerColor(kRed);
  pos1d_copy->SetMarkerStyle(22);
  pos1d_copy->SetLineColor(kRed);
  pos1d_copy->SetLineWidth(2);
  
  d1->cd(3);
  pos2_copy->Draw("e,p1");
  pos2d_copy->Draw("e,same");
  pos2_copy->GetXaxis()->SetTitle("Z_hadron");
  pos2_copy->GetYaxis()->SetTitle("Counts Pi+ Data and Dummy");
  pos2_copy->GetYaxis()->CenterTitle();
  pos2_copy->GetXaxis()->CenterTitle();
  pos2_copy->SetMarkerColor(kBlue);
  pos2_copy->SetMarkerStyle(22);
  pos2_copy->SetLineColor(kBlue);
  pos2_copy->SetLineWidth(2);
  pos2d_copy->SetMarkerColor(kRed);
  pos2d_copy->SetMarkerStyle(22);
  pos2d_copy->SetLineColor(kRed);
  pos2d_copy->SetLineWidth(2);
  
  d1->cd(4);
  pos3_copy->Draw("e,p1");
  pos3d_copy->Draw("e,same");
  pos3_copy->GetXaxis()->SetTitle("Z_hadron");
  pos3_copy->GetYaxis()->SetTitle("Counts Pi+ Data and Dummy");
  pos3_copy->GetYaxis()->CenterTitle();
  pos3_copy->GetXaxis()->CenterTitle();
  pos3_copy->SetMarkerColor(kBlue);
  pos3_copy->SetMarkerStyle(22);
  pos3_copy->SetLineColor(kBlue);
  pos3_copy->SetLineWidth(2);
  pos3d_copy->SetMarkerColor(kRed);
  pos3d_copy->SetMarkerStyle(22);
  pos3d_copy->SetLineColor(kRed);
  pos3d_copy->SetLineWidth(2);
  
  d1->cd(5);
  pos12_copy->Draw("e,p1");
  pos12d_copy->Draw("e,same");
  pos12_copy->GetXaxis()->SetTitle("Z_hadron");
  pos12_copy->GetYaxis()->SetTitle("Counts Pi+ Data and Dummy");
  pos12_copy->GetYaxis()->CenterTitle();
  pos12_copy->GetXaxis()->CenterTitle();
  pos12_copy->SetMarkerColor(kBlue);
  pos12_copy->SetMarkerStyle(22);
  pos12_copy->SetLineColor(kBlue);
  pos12_copy->SetLineWidth(2);
  pos12d_copy->SetMarkerColor(kRed);
  pos12d_copy->SetMarkerStyle(22);
  pos12d_copy->SetLineColor(kRed);
  pos12d_copy->SetLineWidth(2);
  
  d1->cd(6);
  neg0_copy->Draw("e,p1");
  neg0d_copy->Draw("e,same");
  neg0_copy->GetXaxis()->SetTitle("Z_hadron");
  neg0_copy->GetYaxis()->SetTitle("Counts Pi- Data and Dummy");
  neg0_copy->GetYaxis()->CenterTitle();
  neg0_copy->GetXaxis()->CenterTitle();
  neg0_copy->SetMarkerColor(kBlue);
  neg0_copy->SetMarkerStyle(22);
  neg0_copy->SetLineColor(kBlue);
  neg0_copy->SetLineWidth(2);
  neg0d_copy->SetMarkerColor(kRed);
  neg0d_copy->SetMarkerStyle(22);
  neg0d_copy->SetLineColor(kRed);
  neg0d_copy->SetLineWidth(2);
  
  d1->cd(7);
  neg1_copy->Draw("e,p1");
  neg1d_copy->Draw("e,same");
  neg1_copy->GetXaxis()->SetTitle("Z_hadron");
  neg1_copy->GetYaxis()->SetTitle("Counts Pi- Data and Dummy");
  neg1_copy->GetYaxis()->CenterTitle();
  neg1_copy->GetXaxis()->CenterTitle();
  neg1_copy->SetMarkerColor(kBlue);
  neg1_copy->SetMarkerStyle(22);
  neg1_copy->SetLineColor(kBlue);
  neg1_copy->SetLineWidth(2);
  neg1d_copy->SetMarkerColor(kRed);
  neg1d_copy->SetMarkerStyle(22);
  neg1d_copy->SetLineColor(kRed);
  neg1d_copy->SetLineWidth(2);
  
  d1->cd(8);
  neg2_copy->Draw("e,p1");
  neg2d_copy->Draw("e,same");
  neg2_copy->GetXaxis()->SetTitle("Z_hadron");
  neg2_copy->GetYaxis()->SetTitle("Counts Pi+ Data and Dummy");
  neg2_copy->GetYaxis()->CenterTitle();
  neg2_copy->GetXaxis()->CenterTitle();
  neg2_copy->SetMarkerColor(kBlue);
  neg2_copy->SetMarkerStyle(22);
  neg2_copy->SetLineColor(kBlue);
  neg2_copy->SetLineWidth(2);
  neg2d_copy->SetMarkerColor(kRed);
  neg2d_copy->SetMarkerStyle(22);
  neg2d_copy->SetLineColor(kRed);
  neg2d_copy->SetLineWidth(2);
  
  d1->cd(9);
  neg3_copy->Draw("e,p1");
  neg3d_copy->Draw("e, same");
  neg3_copy->GetXaxis()->SetTitle("Z_hadron");
  neg3_copy->GetYaxis()->SetTitle("Counts Pi- Data and Dummy");
  neg3_copy->GetYaxis()->CenterTitle();
  neg3_copy->GetXaxis()->CenterTitle();
  neg3_copy->SetMarkerColor(kBlue);
  neg3_copy->SetMarkerStyle(22);
  neg3_copy->SetLineColor(kBlue);
  neg3_copy->SetLineWidth(2);
  neg3d_copy->SetMarkerColor(kRed);
  neg3d_copy->SetMarkerStyle(22);
  neg3d_copy->SetLineColor(kRed);
  neg3d_copy->SetLineWidth(2);
  
  d1->cd(10);
  neg12_copy->Draw("e,p1");
  neg12d_copy->Draw("e,same");
  neg12_copy->GetXaxis()->SetTitle("Z_hadron");
  neg12_copy->GetYaxis()->SetTitle("Counts Pi- Data and Dummy");
  neg12_copy->GetYaxis()->CenterTitle();
  neg12_copy->GetXaxis()->CenterTitle();
  neg12_copy->SetMarkerColor(kBlue);
  neg12_copy->SetMarkerStyle(22);
  neg12_copy->SetLineColor(kBlue);
  neg12_copy->SetLineWidth(2);
  neg12d_copy->SetMarkerColor(kRed);
  neg12d_copy->SetMarkerStyle(22);
  neg12d_copy->SetLineColor(kRed);
  neg12d_copy->SetLineWidth(2);

  d1->SaveAs("pdf_yield/Data_dummy_yield_samecanvas.pdf");
  d1->SaveAs("pdf_yield/Data_dummy_yield_samecanvas.png");

  //////////////////////check complete for data dummy counts cloned files //////////////////
 
  
  //for pos data
  pos0_copy->Scale(1/qpos);
  pos1_copy->Scale(1/qpos);
  pos2_copy->Scale(1/qpos);
  pos3_copy->Scale(1/qpos);
  pos12_copy->Scale(1/qpos);

  //for pos dummy already accounted for wall thickness
  pos0d_copy->Scale(1/qposd);//d for dummy
  pos1d_copy->Scale(1/qposd);
  pos2d_copy->Scale(1/qposd);
  pos3d_copy->Scale(1/qposd);
  pos12d_copy->Scale(1/qposd);

  //for neg data
  neg0_copy->Scale(1/qneg);
  neg1_copy->Scale(1/qneg);
  neg2_copy->Scale(1/qneg);
  neg3_copy->Scale(1/qneg);
  neg12_copy->Scale(1/qneg);

  //for neg dummy already accounted for wall thickness
  neg0d_copy->Scale(1/qnegd);//d for dummy
  neg1d_copy->Scale(1/qnegd);
  neg2d_copy->Scale(1/qnegd);
  neg3d_copy->Scale(1/qnegd);
  neg12d_copy->Scale(1/qnegd);

  
  //dummy subtracted pos hist 
  TH1D *pos0_clean_yield  = new TH1D("pos0_clean_yield",  "dummy subtracted yield  cut0 pos",  binz, loz, hiz);
  TH1D *pos1_clean_yield  = new TH1D("pos1_clean_yield",  "dummy subtracted yield  cut1 pos",  binz, loz, hiz);
  TH1D *pos2_clean_yield  = new TH1D("pos2_clean_yield",  "dummy subtracted yield  cut2 pos",  binz, loz, hiz);
  TH1D *pos3_clean_yield  = new TH1D("pos3_clean_yield",  "dummy subtracted yield  cut3 pos",  binz, loz, hiz);
  TH1D *pos12_clean_yield = new TH1D("pos12_clean_yield", "dummy subtracted yield  cut12 pos", binz, loz, hiz);

  //dummy subtracted yield  neg hist
  TH1D *neg0_clean_yield  = new TH1D("neg0_clean_yield",  "dummy subtracted yield  cut0 neg",  binz, loz, hiz);
  TH1D *neg1_clean_yield  = new TH1D("neg1_clean_yield",  "dummy subtracted yield  cut1 neg",  binz, loz, hiz);
  TH1D *neg2_clean_yield  = new TH1D("neg2_clean_yield",  "dummy subtracted yield  cut2 neg",  binz, loz, hiz);
  TH1D *neg3_clean_yield  = new TH1D("neg3_clean_yield",  "dummy subtracted yield  cut3 neg",  binz, loz, hiz);
  TH1D *neg12_clean_yield = new TH1D("neg12_clean_yield", "dummy subtracted yield  cut12 neg", binz, loz, hiz);


  //dummy subtraction pos
  pos0_clean_yield  -> Add(pos0_copy, pos0d_copy,  1.0,-1.0);
  pos1_clean_yield  -> Add(pos1_copy, pos1d_copy,  1.0,-1.0);
  pos2_clean_yield  -> Add(pos2_copy, pos2d_copy,  1.0,-1.0);
  pos3_clean_yield  -> Add(pos3_copy, pos3d_copy,  1.0,-1.0);
  pos12_clean_yield ->  Add(pos12_copy, pos12d_copy, 1.0,-1.0);

  //dummy subtraction neg
  neg0_clean_yield  -> Add(neg0_copy, neg0d_copy,  1.0,-1.0);
  neg1_clean_yield  -> Add(neg1_copy, neg1d_copy,  1.0,-1.0);
  neg2_clean_yield  -> Add(neg2_copy, neg2d_copy,  1.0,-1.0);
  neg3_clean_yield  -> Add(neg3_copy, neg3d_copy,  1.0,-1.0);
  neg12_clean_yield ->  Add(neg12_copy, neg12d_copy, 1.0,-1.0);

  //////////////////////dummy subtraction done/////////

  //Plot the pi+ and pi- yield on same canvas

  TCanvas *can = new TCanvas("can", "can",1600,1200);
  can->Divide(3,2);
  can->cd(1);
  pos0_clean_yield->Draw("e,p1");
  neg0_clean_yield->Draw("e,same");
  pos0_clean_yield->GetXaxis()->SetTitle("Z_hadron");
  pos0_clean_yield->GetYaxis()->SetTitle("Dummy Subtracted Yield Pi+ and Pi-");
  pos0_clean_yield->GetYaxis()->CenterTitle();
  pos0_clean_yield->GetXaxis()->CenterTitle();
  pos0_clean_yield->SetMarkerColor(kBlue);
  pos0_clean_yield->SetMarkerStyle(22);
  pos0_clean_yield->SetLineColor(kBlue);
  pos0_clean_yield->SetLineWidth(2);
  neg0_clean_yield->SetMarkerColor(kRed);
  neg0_clean_yield->SetMarkerStyle(22);
  neg0_clean_yield->SetLineColor(kRed);
  neg0_clean_yield->SetLineWidth(2);
  
  can->cd(2);
  pos1_clean_yield->Draw("e,p1");
  neg1_clean_yield->Draw("e,same");
  pos1_clean_yield->GetXaxis()->SetTitle("Z_hadron");
  pos1_clean_yield->GetYaxis()->SetTitle("Dummy Subtracted Yield Pi+ and Pi-");
  pos1_clean_yield->GetYaxis()->CenterTitle();
  pos1_clean_yield->GetXaxis()->CenterTitle();
  pos1_clean_yield->SetMarkerColor(kBlue);
  pos1_clean_yield->SetMarkerStyle(22);
  pos1_clean_yield->SetLineColor(kBlue);
  pos1_clean_yield->SetLineWidth(2);
  neg1_clean_yield->SetMarkerColor(kRed);
  neg1_clean_yield->SetMarkerStyle(22);
  neg1_clean_yield->SetLineColor(kRed);
  neg1_clean_yield->SetLineWidth(2);

  can->cd(3);
  pos2_clean_yield->Draw("e,p1");
  neg2_clean_yield->Draw("e,same");
  pos2_clean_yield->GetXaxis()->SetTitle("Z_hadron");
  pos2_clean_yield->GetYaxis()->SetTitle("Dummy Subtracted Yield Pi+ and Pi-");
  pos2_clean_yield->GetYaxis()->CenterTitle();
  pos2_clean_yield->GetXaxis()->CenterTitle();
  pos2_clean_yield->SetMarkerColor(kBlue);
  pos2_clean_yield->SetMarkerStyle(22);
  pos2_clean_yield->SetLineColor(kBlue);
  pos2_clean_yield->SetLineWidth(2);
  neg2_clean_yield->SetMarkerColor(kRed);
  neg2_clean_yield->SetMarkerStyle(22);
  neg2_clean_yield->SetLineColor(kRed);
  neg2_clean_yield->SetLineWidth(2);


  can->cd(4);
  pos3_clean_yield->Draw("e,p1");
  neg3_clean_yield->Draw("e,same");
  pos3_clean_yield->GetXaxis()->SetTitle("Z_hadron");
  pos3_clean_yield->GetYaxis()->SetTitle("Dummy Subtracted Yield Pi+ and Pi-");
  pos3_clean_yield->GetYaxis()->CenterTitle();
  pos3_clean_yield->GetXaxis()->CenterTitle();
  pos3_clean_yield->SetMarkerColor(kBlue);
  pos3_clean_yield->SetMarkerStyle(22);
  pos3_clean_yield->SetLineColor(kBlue);
  pos3_clean_yield->SetLineWidth(2);
  neg3_clean_yield->SetMarkerColor(kRed);
  neg3_clean_yield->SetMarkerStyle(22);
  neg3_clean_yield->SetLineColor(kRed);
  neg3_clean_yield->SetLineWidth(2);

  can->cd(5);
  pos12_clean_yield->Draw("e,p1");
  neg12_clean_yield->Draw("e,same");
  pos12_clean_yield->GetXaxis()->SetTitle("Z_hadron");
  pos12_clean_yield->GetYaxis()->SetTitle("Dummy Subtracted Yield Pi+ and Pi-");
  pos12_clean_yield->GetYaxis()->CenterTitle();
  pos12_clean_yield->GetXaxis()->CenterTitle();
  pos12_clean_yield->SetMarkerColor(kBlue);
  pos12_clean_yield->SetMarkerStyle(22);
  pos12_clean_yield->SetLineColor(kBlue);
  pos12_clean_yield->SetLineWidth(2);
  neg12_clean_yield->SetMarkerColor(kRed);
  neg12_clean_yield->SetMarkerStyle(22);
  neg12_clean_yield->SetLineColor(kRed);
  neg12_clean_yield->SetLineWidth(2);

  
  can->SaveAs("pdf_yield/dummy_sub_yield_pos_neg.pdf");

  //////====================dummy yield calcultion done=====================


  ///////Yield Ratio plot///////////
   TCanvas *c1 = new TCanvas ("c1", "c1", 1600, 1200);
     c1->Divide(3,2);gPad->SetGrid();
     c1->cd(1);gPad->SetGrid();
  
     TH1D *new_h00= new TH1D ("new_h00", "new_h00", binz, loz, hiz);
     new_h00->Divide(pos0_clean_yield,neg0_clean_yield);
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
     new_h11->Divide(pos1_clean_yield,neg1_clean_yield);
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
     new_h22->Divide(pos2_clean_yield,neg2_clean_yield);
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
     new_h33->Divide(pos3_clean_yield, neg3_clean_yield);
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
     new_h12->Divide(pos12_clean_yield,neg12_clean_yield);
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
     gr1->Draw("same");

  
    
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
     ////////////////////////////////////// %difference cut12 vs cut1 /////////////// cut12 as a standard and compare with all 

     TH1D * diff_12_11 = new TH1D("diff_12_11","diff_12_11",binz,loz,hiz);
     TH1D * ratio_diff_12_11 = new TH1D("ratio_diff_12_11","ratio_diff_12_11",binz,loz,hiz);

     TCanvas *cc121 = new TCanvas("cc121","percent_diff",1600,1200);
     cc121->Divide(2,2);gPad->SetGrid();
  
     new_h11_copy= (TH1D*)new_h11->Clone();//copy of h11
     new_h12_copy= (TH1D*)new_h12->Clone();//copy 0f cut1plus2

  
     new_h12_copy->Add(new_h11_copy, -1);//diff of cut1plus2 and cut1 = diff
     new_h12_diff = (TH1D*)new_h12_copy->Clone();//copy of diff
  
     ratio_diff_12_11->Divide(new_h12_diff, new_h12);//diff/cut1plus2 = ratio
     ratio_diff_12_11->Scale(100.0);//ratio*100%

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
