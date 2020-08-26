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
void read_lumi()
{

     std::ifstream infile("txtfile_hms/hms_d2.txt");
     
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
  


  // cout<<"I am good "<<endl;


  

  while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      double a,  b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r;
      if(line[0] == '#') continue;
      
      if (!(iss >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l >> m >> n >> o >> p >> q >> r))
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
      

     
     
    }

  for (int i =0; i< run.size(); i++)
    {
      
      cout<< run[i] <<"    "<<  current[i]<<"    "<< charge[i]<<"    "<<  ptrig3_rate[i]<<"    "<< elclean_rate[i]<<"    "<< elreal_rate[i]<<"    "<< clt[i]<<"    "<< clt_err[i]<<"    "<<  treff[i]<<"    "<< treff_err[i]<<"    "<<  yield_elreal[i]<<"    "<< yield_elreal_err[i]<<"    "<<    yield_elclean[i]<<"    "<< yield_elclean_err[i]<<"    "<< yield_clt_notr[i]<<"    "<< yield_clt_notr_err[i]<<"    "<< yield_clt_tr[i]<<"    "<< yield_clt_tr_err[i]<<"    "<<endl;
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

  cout<<"Hi Bidhan"<<endl;
  
  TCanvas *c1 = new TCanvas ("c1", "c1", 1600, 1200);
  c1->Divide(2,2);
  c1->cd(1);gPad->SetGridx();gPad->SetGridy();
  gr1->Draw("AP");
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3);
  gr1->GetXaxis()->SetTitle("current (uA)");
  gr1->GetYaxis()->SetTitle("Elreal Yield (counts/uC)");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  gr1->Draw("AP");
  gr1->Fit("pol1");

  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(2.5);
  gStyle->SetOptFit();

  TString TarLabel = " =>  Y = Elreal Counts/(Q) :";
  TF1 *fit = gr1->GetFunction("pol1");
  Double_t Ypidslope = fit->GetParameter(1);
  Double_t YpidslopeErr = fit->GetParError(1);
  Double_t Ypidint = fit->GetParameter(0);
  Double_t normSlope=Ypidslope/Ypidint*100*100;
  Double_t normSlopeErr= YpidslopeErr/Ypidint*100*100;

  
  TString ttemp=Form(" Slope 100uA  = %f +/- %f",normSlope,normSlopeErr);
   gr1->SetTitle(ttemp+TarLabel);

   // gr1->CenterTitle(true);

   
  c1->cd(2);gPad->SetGridx();gPad->SetGridy();
  
  gr2->Draw("AP");
  gr2->SetMarkerColor(kBlack);
  gr2->SetLineColor(kBlack);
  gr2->SetLineWidth(3);
  gr2->GetXaxis()->SetTitle("current (uA)");
  gr2->GetYaxis()->SetTitle("Elclean Yield (counts/uC)");
  gr2->GetXaxis()->CenterTitle();
  gr2->GetYaxis()->CenterTitle();
  gr2->Draw("AP");
  gr2->Fit("pol1");

  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel2 = " Y = Elclean Counts/(Q) :";

  TF1 *fit2 = gr2->GetFunction("pol1");
  Double_t Ypidslope2 = fit2->GetParameter(1);
  Double_t YpidslopeErr2 = fit2->GetParError(1);
  Double_t Ypidint2 = fit2->GetParameter(0);
  Double_t normSlope2=Ypidslope2/Ypidint2*100*100;
  Double_t normSlopeErr2= YpidslopeErr2/Ypidint2*100*100;
  TString ttemp2=Form(" Slope %/100uA  = %f +/- %f",normSlope2,normSlopeErr2);
  gr2->SetTitle(ttemp2+TarLabel2);

  c1->cd(3);gPad->SetGridx();gPad->SetGridy();
 
  gr3->Draw("AP");
  gr3->SetMarkerColor(kBlack);
  gr3->SetLineColor(kBlack);
  gr3->SetLineWidth(2);
  gr3->GetXaxis()->SetTitle("current (uA)");
  gr3->GetYaxis()->SetTitle("No Tracking Yield (counts/uC)");
  gr3->GetXaxis()->CenterTitle();
  gr3->GetYaxis()->CenterTitle();
  gr3->Draw("AP");
  gr3->Fit("pol1");

  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel3 = " Y = Good Counts Notrack / (Q * Clt) :";

  TF1 *fit3 = gr3->GetFunction("pol1");
  Double_t Ypidslope3 = fit3->GetParameter(1);
  Double_t YpidslopeErr3 = fit3->GetParError(1);
  Double_t Ypidint3 = fit3->GetParameter(0);
  Double_t normSlope3=Ypidslope3/Ypidint3*100*100;
  Double_t normSlopeErr3= YpidslopeErr3/Ypidint3*100*100;
  TString ttemp3=Form(" Slope %/100uA  = %f +/- %f",normSlope3,normSlopeErr3);
  gr3->SetTitle(ttemp3+TarLabel3);

  c1->cd(4);gPad->SetGridx();gPad->SetGridy();
 
  gr4->Draw("AP");
  gr4->SetMarkerColor(kBlack);
  gr4->SetLineColor(kBlack);
  gr4->SetLineWidth(2);
  gr4->GetXaxis()->SetTitle("current (uA)");
  gr4->GetYaxis()->SetTitle("Tracking Yield (counts/uC)");
  gr4->GetXaxis()->CenterTitle();
  gr4->GetYaxis()->CenterTitle();
  gr4->Draw("AP");
  gr4->Fit("pol1");

  gr4->SetMarkerStyle(20);
  gr4->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel4 = " Y = Good Counts Track / (Q * Clt * TrEff)   :";

  TF1 *fit4 = gr4->GetFunction("pol1");
  Double_t Ypidslope4 = fit4->GetParameter(1);
  Double_t YpidslopeErr4 = fit4->GetParError(1);
  Double_t Ypidint4 = fit4->GetParameter(0);
  Double_t normSlope4=Ypidslope4/Ypidint4*100*100;
  Double_t normSlopeErr4= YpidslopeErr4/Ypidint4*100*100;
  TString ttemp4=Form(" Slope %/100uA  = %f +/- %f",normSlope4,normSlopeErr4);
  gr4->SetTitle(ttemp4+TarLabel4);


  
  TString outputpdf;
  outputpdf = "pdf_hms/hms_d2_all.pdf";
  c1->Print(outputpdf);

  
  
}
