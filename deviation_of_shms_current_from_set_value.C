#include <iostream>
#include <fstream>
using namespace std;

void plot_shms(){
  gStyle->SetOptFit(0);
  // gStyle->SetOptStat(1);
  // gStyle->SetPaintTextFormat("5.4g");
  // gStyle->SetTitleFontSize(0.03);
  // gStyle->SetTitleOffset(0.06);
  // gStyle->SetTitleFont(10);
  // gStyle->SetNdivisions(505);
  // gStyle->SetTitleYOffset(0.7);
  // gStyle->SetTitleXOffset(0.7);
  // gStyle->SetTitleYSize(0.05);
  // gStyle->SetTitleXSize(0.05);
  // gStyle->SetLabelFont(20,"X");
  // gStyle->SetLabelFont(20,"Y");
  // gStyle->SetTitleFont(20,"X");
  // gStyle->SetTitleFont(20,"Y");
  // gStyle->SetLabelSize(0.01,"X");
  // gStyle->SetLabelSize(0.01,"Y");
  // gStyle->SetPaperSize(18,22);

  ifstream inputfile;
  inputfile.open("/w/hallc-scifs17exp/c-sidis18/hdbhatt/my_analysis/ang_mom_check/temp/shms_current.txt");
  const  Int_t m1 = 425;
  //  Int_t RN[m1];
  Double_t RN[m1], p[m1],hbo[m1],hbs[m1],q1o[m1],q1s[m1],q3o[m1],q3s[m1],q2o[m1],q2s[m1],dipo[m1],dips[m1];
  Double_t hbplot[m1],q1plot[m1],q2plot[m1],q3plot[m1],dipplot[m1];;
  for(int j = 0;j<m1;j++)

    {
      inputfile>>fixed>>RN[j]>>p[j]>>hbs[j]>>hbo[j]>>q1s[j]>>q1o[j]>>q3s[j]>>q3o[j]>>q2s[j]>>q2o[j]>>dips[j]>>dipo[j];
      hbplot[j] = fabs(((hbs[j] - hbo[j])/hbs[j])*100.);
      q1plot[j] = fabs(((q1s[j] - q1o[j])/q1s[j])*100.);
      q2plot[j] = fabs(((q2s[j] - q2o[j])/q2s[j])*100.);
      q3plot[j] = fabs(((q3s[j] - q3o[j])/q3s[j])*100.);
      dipplot[j] = fabs(((dips[j] - dipo[j])/dips[j])*100.);

      // cout<<hbplot[j]<<endl;
      // cout<<RN[j]<<"(q2set-q2o) ="<< fabs(q2s[j] - q2o[j])<<endl;
      // cout<<RN[j]<<"[(q1set-q1o)/q1set]*100 ="<<(q2plot[j])<<endl;
      cout<<RN[j]<<"  H  I "<<dips[j]<< "Hello "<<dipo[j]<<"hELLO"<< dipplot[j]<< endl;
    }
  inputfile.close();

  //TGraphErrors *t1 = new TGraphErrors (m1,Ep1,R1,eEp1,eR1);
  TGraph *t1 = new TGraph(m1,RN,hbplot);
  t1->SetLineColor(kBlack);
  t1->SetMarkerStyle(22);
  t1->SetMarkerColor(kBlack);
  t1->GetYaxis()->SetTitle("% change of SHMS HB current from set value");
  t1->GetXaxis()->SetTitle("Run Numbers");
  t1->GetXaxis()->CenterTitle();
  t1->SetTitle("(HB_Iset - HB_Iread)/HB_Iset*100");
  t1->Draw("APP");

  // TGraph *t2 = new TGraph(m1,RN,q1plot);
  // t2->SetLineColor(kBlack);
  // t2->SetMarkerStyle(22);
  // t2->SetMarkerColor(kBlack);
  // t2->GetYaxis()->SetTitle("% change of SHMS Q1 current from set value");
  // t2->GetXaxis()->SetTitle("Run Numbers");
  // t2->GetXaxis()->CenterTitle();
  // t2->SetTitle("(Q1_Iset - Q1_Iread)/Q1_Iset*100");
  // t2->Draw("APP");

  // TGraph *t3 = new TGraph(m1,RN,q2plot);
  // t3->SetLineColor(kBlack);
  // t3->SetMarkerStyle(22);
  // t3->SetMarkerColor(kBlack);
  // t3->GetYaxis()->SetTitle("% change of SHMS Q2 current from set value");
  // t3->GetXaxis()->SetTitle("Run Numbers");
  // t3->GetXaxis()->CenterTitle();
  // t3->SetTitle("(Q2_Iset - Q2_Iread)/Q2_Iset*100");
  // t3->Draw("APP");

  // TGraph *t4 = new TGraph(m1,RN,q3plot);
  // t4->SetLineColor(kBlack);
  // t4->SetMarkerStyle(22);
  // t4->SetMarkerColor(kBlack);
  // t4->GetYaxis()->SetTitle("% change of SHMS Q3 current from set value");
  // t4->GetXaxis()->SetTitle("Run Numbers");
  // t4->GetXaxis()->CenterTitle();
  // t4->SetTitle("(Q3_Iset - Q3_Iread)/Q3_Iset*100");
  // t4->Draw("APP");

  // TGraph *t5 = new TGraph(m1,RN,dipplot);
  // t5->SetLineColor(kBlack);
  // t5->SetMarkerStyle(22);
  // t5->SetMarkerColor(kBlack);
  // t5->GetYaxis()->SetTitle("% change of SHMS Dipole current from set value");
  // t5->GetXaxis()->SetTitle("Run Numbers");
  // t5->GetXaxis()->CenterTitle();
  // t5->SetTitle("(Dip_Iset - Dip_Iread)/Dip_Iset*100");
  // t5->Draw("APP");


}
