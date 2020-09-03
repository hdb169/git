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
void read_lumi_txtfile_sept1()
{

  
  std::ifstream infile("txtfile_hms/hms_yield_all.txt");
  // std::ifstream infile("txtfile_shms/shms_yield_all.txt");

  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(1000011);
  gStyle->SetOptFit(0);
  gStyle->SetTitleOffset(2.2,"Y");//1.2
  gStyle->SetTitleOffset(1.1,"X");//0.7
  gStyle->SetLabelSize(0.05,"XY");//0.05
  gStyle->SetTitleSize(0.04,"XY");//06
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetTitleFontSize(0.04);//05
  gStyle->GetAttDate()->SetTextAlign();
  gStyle->SetTitleX(0.5f);
  gStyle->SetTitleW(0.8f);

  std::string line;
  vector <double> run;
  vector <double> current;
  vector <double> charge;
  vector <double> ptrig3_rate;
  vector <double> elclean_rate;
  vector <double> elreal_rate;
  vector <double> clt;
  vector <double> clt_err;
  vector <double> treff;
  vector <double> treff_err;
  vector <double> yield_elreal;
  vector <double> yield_elreal_err;
  vector <double> yield_elclean;
  vector <double> yield_elclean_err;
  
  vector <double> yield_clt_notr;
  vector <double> yield_clt_notr_err;
  vector <double> yield_clt_tr;
  vector <double> yield_clt_tr_err;
  
  vector <double> yield_plt_notr;
  vector <double> yield_plt_notr_err;
  vector <double> yield_plt_tr;
  vector <double> yield_plt_tr_err;

  vector <double> yield_tlt_notr;
  vector <double> yield_tlt_notr_err;
  vector <double> yield_tlt_tr;
  vector <double> yield_tlt_tr_err;


  // cout<<"I am good "<<endl;


  

  while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      double a,  b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r,s, t, u, v, w, x, y, z;
      if(line[0] == '#') continue;
      
      if (!(iss >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l >> m >> n >> o >> p >> q >> r>>s >>t >>u >>v >>w >>x >>y >>z))
        {
           
	  break;
           
        } 
       
      run.push_back(a);
      current.push_back(b);
      charge.push_back(c);
      ptrig3_rate.push_back(d);
      elclean_rate.push_back(e);
      elreal_rate.push_back(f);
      clt.push_back(g);
      clt_err.push_back(h);
      treff.push_back(i);
      treff_err.push_back(j);
      
      yield_elreal.push_back(k);
      yield_elreal_err.push_back(l);
      
      yield_elclean.push_back(m);
      yield_elclean_err.push_back(n);
      
      yield_clt_notr.push_back(o);
      yield_clt_notr_err.push_back(p);  
      yield_clt_tr.push_back(q);
      yield_clt_tr_err.push_back(r);
      
      yield_plt_notr.push_back(s);
      yield_plt_notr_err.push_back(t);  
      yield_plt_tr.push_back(u);
      yield_plt_tr_err.push_back(v);
      
      yield_tlt_notr.push_back(w);
      yield_tlt_notr_err.push_back(x);  
      yield_tlt_tr.push_back(y);
      yield_tlt_tr_err.push_back(z);
      
     
    }

  for (int i =0; i< run.size(); i++)
    {
      
      cout<< run[i] <<"    "<<  current[i]<<"    "<< charge[i]<<"    "<<  ptrig3_rate[i]<<"    "<< elclean_rate[i]<<"    "<< elreal_rate[i]<<"    "<< clt[i]<<"    "<< clt_err[i]<<"    "<<  treff[i]<<"    "<< treff_err[i]<<"    "<<  yield_elreal[i]<<"    "<< yield_elreal_err[i]<<"    "<<    yield_elclean[i]<<"    "<< yield_elclean_err[i]<<"    "<< yield_clt_notr[i]<<"    "<< yield_clt_notr_err[i]<<"    "<< yield_clt_tr[i]<<"    "<< yield_clt_tr_err[i]<<"    "<< yield_plt_notr[i]<<"    "<< yield_plt_notr_err[i]<<"    "<< yield_plt_tr[i]<<"    "<< yield_plt_tr_err[i]<<"    "<< yield_tlt_notr[i]<<"    "<< yield_tlt_notr_err[i]<<"    "<< yield_tlt_tr[i]<<"    "<< yield_tlt_tr_err[i]<<"    "<<   endl;
      cout<<"I am good"<<endl;

    }

  
  cout<< "I am good"<<endl;
  
  auto gr1 = new TGraphErrors(run.size(), &current[0], &yield_elreal[0], 0, &yield_elreal_err[0]);
  auto gr11= new TGraphErrors(run.size(), &elreal_rate[0], &yield_elreal[0], 0, &yield_elreal_err[0]);
 
  
  auto gr2 = new TGraphErrors(run.size(), &current[0], &yield_elclean[0], 0, &yield_elclean_err[0]);
  auto gr22= new TGraphErrors(run.size(), &elclean_rate[0], &yield_elclean[0], 0, &yield_elclean_err[0]);
  
  auto gr3 = new TGraphErrors(run.size(), &current[0], &yield_clt_notr[0], 0, &yield_clt_notr_err[0]);
  auto gr33= new TGraphErrors(run.size(), &ptrig3_rate[0], &yield_clt_notr[0], 0, &yield_clt_notr_err[0]);

 
  auto gr4 = new TGraphErrors(run.size(), &current[0], &yield_clt_tr[0], 0, &yield_clt_tr_err[0]);
  auto gr44= new TGraphErrors(run.size(), &ptrig3_rate[0], &yield_clt_tr[0], 0, &yield_clt_tr_err[0]);


  auto gr5 = new TGraphErrors(run.size(), &current[0], &yield_plt_notr[0], 0, &yield_plt_notr_err[0]);
  auto gr55= new TGraphErrors(run.size(), &ptrig3_rate[0], &yield_plt_notr[0], 0, &yield_plt_notr_err[0]);

  auto gr6 = new TGraphErrors(run.size(), &current[0], &yield_plt_tr[0], 0, &yield_plt_tr_err[0]);
  auto gr66= new TGraphErrors(run.size(), &ptrig3_rate[0], &yield_plt_tr[0], 0, &yield_plt_tr_err[0]);

  auto gr7 = new TGraphErrors(run.size(), &current[0], &yield_tlt_notr[0], 0, &yield_tlt_notr_err[0]);
  auto gr77= new TGraphErrors(run.size(), &ptrig3_rate[0], &yield_tlt_notr[0], 0, &yield_tlt_notr_err[0]);

  auto gr8 = new TGraphErrors(run.size(), &current[0], &yield_tlt_tr[0], 0, &yield_tlt_tr_err[0]);
  auto gr88= new TGraphErrors(run.size(), &ptrig3_rate[0], &yield_tlt_tr[0], 0, &yield_tlt_tr_err[0]);

 
  

  cout<<"Hi Bidhan"<<endl;
  
  TCanvas *c1 = new TCanvas ("c1", "c1", 1600, 1200);//--------------------------------------------------------1
  c1->Divide(3,2);
  c1->cd(1);gPad->SetGridx();gPad->SetGridy();
  gr3->Draw("AP");
  gr3->SetMarkerColor(kBlack);
  gr3->SetLineColor(kBlack);
  gr3->SetLineWidth(3);
  gr3->GetXaxis()->SetTitle("current (uA)");
  gr3->GetYaxis()->SetTitle("CLT NoTrack Yield (counts/uC)");
  gr3->GetXaxis()->CenterTitle();
  gr3->GetYaxis()->CenterTitle();
  gr3->Draw("AP");
  gr3->Fit("pol1");

  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(2.5);
  gStyle->SetOptFit();

  TString TarLabel = " =>  Y = CLT NoTrack Counts/(Q * CLT) :";
  TF1 *fit = gr3->GetFunction("pol1");
  Double_t Ypidslope = fit->GetParameter(1);
  Double_t YpidslopeErr = fit->GetParError(1);
  Double_t Ypidint = fit->GetParameter(0);
  Double_t normSlope=Ypidslope/Ypidint*100*100;
  Double_t normSlopeErr= YpidslopeErr/Ypidint*100*100;

  
  TString ttemp=Form(" Slope %/100uA  = %f +/- %f",normSlope,normSlopeErr);
  gr3->SetTitle(ttemp+TarLabel);


   
  c1->cd(2);gPad->SetGridx();gPad->SetGridy();//-----------------------------------------------------------------------2
  
  gr4->Draw("AP");
  gr4->SetMarkerColor(kBlack);
  gr4->SetLineColor(kBlack);
  gr4->SetLineWidth(3);
  gr4->GetXaxis()->SetTitle("current (uA)");
  gr4->GetYaxis()->SetTitle("CLT Track Yield (counts/uC)");
  gr4->GetXaxis()->CenterTitle();
  gr4->GetYaxis()->CenterTitle();
  gr4->Draw("AP");
  gr4->Fit("pol1");

  gr4->SetMarkerStyle(20);
  gr4->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel2 = " Y = CLT Track Counts/(Q * CLT * TrEff.) :";

  TF1 *fit2 = gr4->GetFunction("pol1");
  Double_t Ypidslope2 = fit2->GetParameter(1);
  Double_t YpidslopeErr2 = fit2->GetParError(1);
  Double_t Ypidint2 = fit2->GetParameter(0);
  Double_t normSlope2=Ypidslope2/Ypidint2*100*100;
  Double_t normSlopeErr2= YpidslopeErr2/Ypidint2*100*100;
  TString ttemp2=Form(" Slope %/100uA  = %f +/- %f",normSlope2,normSlopeErr2);
  gr4->SetTitle(ttemp2+TarLabel2);

  c1->cd(3);gPad->SetGridx();gPad->SetGridy();//-----------------------------------------------------------------------3
 
  gr5->Draw("AP");
  gr5->SetMarkerColor(kBlack);
  gr5->SetLineColor(kBlack);
  gr5->SetLineWidth(2);
  gr5->GetXaxis()->SetTitle("current (uA)");
  gr5->GetYaxis()->SetTitle("PLT NoTrack Yield (counts/uC)");
  gr5->GetXaxis()->CenterTitle();
  gr5->GetYaxis()->CenterTitle();
  gr5->Draw("AP");
   gr5->Fit("pol1","Q","",10, 80);
  //gr5->Fit("pol1","Q","",10, 60);

  gr5->SetMarkerStyle(20);
  gr5->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  //TString TarLabel3 = " Y = Good Counts Notrack / (Q * CLT_Phy) :";
  // TString TarLabel3 = " Y = Good Counts Notrack / (Q * CLT_All) :";
  TString TarLabel3 = " Y = PLT NoTrack Counts / (Q * PLT) :";



   
  TF1 *fit3 = gr5->GetFunction("pol1");
  Double_t Ypidslope3 = fit3->GetParameter(1);
  Double_t YpidslopeErr3 = fit3->GetParError(1);
  Double_t Ypidint3 = fit3->GetParameter(0);
  Double_t normSlope3=Ypidslope3/Ypidint3*100*100;
  Double_t normSlopeErr3= YpidslopeErr3/Ypidint3*100*100;
  TString ttemp3=Form(" Slope %/100uA  = %f +/- %f",normSlope3,normSlopeErr3);
  gr5->SetTitle(ttemp3+TarLabel3);

  c1->cd(4);gPad->SetGridx();gPad->SetGridy();//-----------------------------------------------------------------------4
 
  gr6->Draw("AP");
  gr6->SetMarkerColor(kBlack);
  gr6->SetLineColor(kBlack);
  gr6->SetLineWidth(2);
  gr6->GetXaxis()->SetTitle("current (uA)");
  gr6->GetYaxis()->SetTitle("PLT Track Yield (counts/uC)");
  gr6->GetXaxis()->CenterTitle();
  gr6->GetYaxis()->CenterTitle();
  gr6->Draw("AP");
  gr6->Fit("pol1","Q","",10, 80);
  //gr6->Fit("pol1","Q","",10, 60);

  gr6->SetMarkerStyle(20);
  gr6->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  // TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_Phy * TrEff * Hodo_eff)   :";
  // TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_All * TrEff * Hodo_eff)   :";
  // TString TarLabel4 = " Y = Good Counts Track / (Q * LT_Total * TrEff * Hodo_eff)   :";

  //NO HODO
  // TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_Phy * TrEff )   :";
  //   TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_All * TrEff )   :";
  TString TarLabel4 = " Y = PLT Track Counts / (Q * PLT * TrEff )   :";
   
  TF1 *fit4 = gr6->GetFunction("pol1");
  Double_t Ypidslope4 = fit4->GetParameter(1);
  Double_t YpidslopeErr4 = fit4->GetParError(1);
  Double_t Ypidint4 = fit4->GetParameter(0);
  Double_t normSlope4=Ypidslope4/Ypidint4*100*100;
  Double_t normSlopeErr4= YpidslopeErr4/Ypidint4*100*100;
  TString ttemp4=Form(" Slope %/100uA  = %f +/- %f",normSlope4,normSlopeErr4);
  gr6->SetTitle(ttemp4+TarLabel4);

  c1->cd(5);gPad->SetGridx();gPad->SetGridy();//-----------------------------------------------------------------------5

  gr7->Draw("AP");
  gr7->SetMarkerColor(kBlack);
  gr7->SetLineColor(kBlack);
  gr7->SetLineWidth(2);
  gr7->GetXaxis()->SetTitle("current (uA)");
  gr7->GetYaxis()->SetTitle("TLT NoTrack Yield(counts/uC)");
  gr7->GetXaxis()->CenterTitle();
  gr7->GetYaxis()->CenterTitle();
  gr7->Draw("AP");
  //gr7->Fit("pol1","Q","",10, 80);
  gr7->Fit("pol1","Q","",10, 60);

  gr7->SetMarkerStyle(20);
  gr7->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  // TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_Phy * TrEff * Hodo_eff)   :";
  // TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_All * TrEff * Hodo_eff)   :";
  // TString TarLabel4 = " Y = Good Counts Track / (Q * LT_Total * TrEff * Hodo_eff)   :";

  //NO HODO
  // TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_Phy * TrEff )   :";
  //   TString TarLabel4 = " Y = Good Counts Track / (Q * CLT_All * TrEff )   :";
  TString TarLabel5 = " Y = PLT NoTrack Counts / (Q * PLT )   :";
   
  TF1 *fit5 = gr7->GetFunction("pol1");
  Double_t Ypidslope5 = fit5->GetParameter(1);
  Double_t YpidslopeErr5 = fit5->GetParError(1);
  Double_t Ypidint5 = fit5->GetParameter(0);
  Double_t normSlope5=Ypidslope5/Ypidint5*100*100;
  Double_t normSlopeErr5= YpidslopeErr5/Ypidint5*100*100;
  TString ttemp5=Form(" Slope %/100uA  = %f +/- %f",normSlope5,normSlopeErr5);
  gr7->SetTitle(ttemp5+TarLabel5);

  c1->cd(6);gPad->SetGridx();gPad->SetGridy();//-----------------------------------------------------------------------6

  gr8->Draw("AP");
  gr8->SetMarkerColor(kBlack);
  gr8->SetLineColor(kBlack);
  gr8->SetLineWidth(2);
  gr8->GetXaxis()->SetTitle("current (uA)");
  gr8->GetYaxis()->SetTitle("TLT Track Yield (counts/uC)");
  gr8->GetXaxis()->CenterTitle();
  gr8->GetYaxis()->CenterTitle();
  gr8->Draw("AP");
  //gr8->Fit("pol1","Q","",10, 80);
  gr8->Fit("pol1","Q","",10, 60);

  gr8->SetMarkerStyle(20);
  gr8->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  // TString TarLabel6 = " Y = Good Counts Track / (Q * CLT_Phy * TrEff * Hodo_eff)   :";
  // TString TarLabel6 = " Y = Good Counts Track / (Q * CLT_All * TrEff * Hodo_eff)   :";
  // TString TarLabel6 = " Y = Good Counts Track / (Q * LT_Total * TrEff * Hodo_eff)   :";

  //NO HODO
  // TString TarLabel6 = " Y = Good Counts Track / (Q * CLT_Phy * TrEff )   :";
  //   TString TarLabel6 = " Y = Good Counts Track / (Q * CLT_All * TrEff )   :";
  TString TarLabel6 = " Y = TLT Track Counts / (Q * TLT * TrEff )   :";
   
  TF1 *fit6 = gr8->GetFunction("pol1");
  Double_t Ypidslope6 = fit6->GetParameter(1);
  Double_t YpidslopeErr6 = fit6->GetParError(1);
  Double_t Ypidint6 = fit6->GetParameter(0);
  Double_t normSlope6=Ypidslope6/Ypidint6*100*100;
  Double_t normSlopeErr6= YpidslopeErr6/Ypidint6*100*100;
  TString ttemp6=Form(" Slope %/100uA  = %f +/- %f",normSlope6,normSlopeErr6);
  gr8->SetTitle(ttemp6+TarLabel6);


  
  TString outputpdf;
  outputpdf = "pdf_hms/hms_all.pdf";
  c1->Print(outputpdf);
  
    TCanvas *c2 = new TCanvas ("c2", "c2", 1600, 1200);//--------------------------------------------------------1
    c2->Divide(2,2);
  c2->cd(1);gPad->SetGridx();gPad->SetGridy();
  gr1->Draw("AP");
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3);
  gr1->GetXaxis()->SetTitle("current (uA)");
  gr1->GetYaxis()->SetTitle("ELReal Yield (counts/uC)");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  gr1->Draw("AP");
  gr1->Fit("pol1");

  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(2.5);
  gStyle->SetOptFit();

  TString TarLabel7 = " =>  Y = ELReal Counts/(Q) :";
  TF1 *fit7 = gr1->GetFunction("pol1");
  Double_t Ypidslope7 = fit->GetParameter(1);
  Double_t YpidslopeErr7 = fit->GetParError(1);
  Double_t Ypidint7 = fit->GetParameter(0);
  Double_t normSlope7=Ypidslope7/Ypidint7*100*100;
  Double_t normSlopeErr7= YpidslopeErr7/Ypidint7*100*100;

  
  TString ttemp7=Form(" Slope %/100uA  = %f +/- %f",normSlope7,normSlopeErr7);
  gr1->SetTitle(ttemp7+TarLabel7);


   
  c2->cd(2);gPad->SetGridx();gPad->SetGridy();//-----------------------------------------------------------------------2
  
  gr2->Draw("AP");
  gr2->SetMarkerColor(kBlack);
  gr2->SetLineColor(kBlack);
  gr2->SetLineWidth(3);
  gr2->GetXaxis()->SetTitle("current (uA)");
  gr2->GetYaxis()->SetTitle("ELClean Yield (counts/uC)");
  gr2->GetXaxis()->CenterTitle();
  gr2->GetYaxis()->CenterTitle();
  gr2->Draw("AP");
  gr2->Fit("pol1");

  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel8 = " Y = ELClean Counts/(Q) :";

  TF1 *fit8 = gr2->GetFunction("pol1");
  Double_t Ypidslope8 = fit8->GetParameter(1);
  Double_t YpidslopeErr8 = fit8->GetParError(1);
  Double_t Ypidint8 = fit8->GetParameter(0);
  Double_t normSlope8=Ypidslope8/Ypidint8*100*100;
  Double_t normSlopeErr8= YpidslopeErr8/Ypidint8*100*100;
  TString ttemp8=Form(" Slope %/100uA  = %f +/- %f",normSlope8,normSlopeErr8);
  gr2->SetTitle(ttemp8+TarLabel8);

  
}
