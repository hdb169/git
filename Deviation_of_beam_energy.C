#include <iostream>
#include <fstream>
using namespace std;

void beam_energ_vs_Run(){
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(1);
  gStyle->SetPaintTextFormat("5.4g");
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetTitleOffset(0.03);
  gStyle->SetTitleFont(10);
  gStyle->SetNdivisions(505);
  gStyle->SetTitleYOffset(0.9);
  gStyle->SetTitleXOffset(0.7);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleXSize(0.05);
  gStyle->SetLabelFont(20,"X");
  gStyle->SetLabelFont(20,"Y");
  gStyle->SetTitleFont(20,"X");
  gStyle->SetTitleFont(20,"Y");
  gStyle->SetLabelSize(0.03,"X");
  gStyle->SetLabelSize(0.03,"Y");
  gStyle->SetPaperSize(18,22);

  ifstream inputfile;
  inputfile.open("/w/hallc-scifs17exp/c-sidis18/hdbhatt/my_analysis/ang_mom_check/temp/beam_energy.txt");
  const  Int_t m1 = 525;
  //  Int_t RN[m1];
  Double_t RN[m1], BE[m1],diff[m1];
  Double_t BEplot[m1];
  for(int j = 0;j<m1;j++)

    {
      inputfile>>fixed>>RN[j]>>BE[j]>>diff[j];
      BEplot[j]=BE[j];
      // cout<<RN[j]<<"  H  I "<<BE[j]<< "Hello "<< endl;
      cout<<RN[j]<<"Hello"<<BEplot[j]<<endl;

    }
  inputfile.close();

  //TGraphErrors *t1 = new TGraphErrors (m1,Ep1,R1,eEp1,eR1);
  TGraph *t1 = new TGraph(m1,RN,BEplot);
  t1->SetLineColor(kBlack);
  t1->SetMarkerStyle(22);
  t1->SetMarkerColor(kBlack);
  t1->GetYaxis()->SetTitle("Beam Energy");
  t1->GetXaxis()->SetTitle("Run Numbers");
  t1->GetXaxis()->CenterTitle();
  t1->GetYaxis()->CenterTitle();
  t1->SetTitle("Beam Energy (MeV)");
  // t1->GetYaxis()->SetRangeUser(10590,10610);
  t1->Draw("APP");

}
