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
#include <sstream>
#include <string>
#include <fstream>

void read_all()
{
 
  std::ifstream infile("../txtfile_shms/shms_all.txt");
  //std::ifstream infile("../txtfile_shms/trash.txt");

 
  std::string line;
  vector <double> run;
  vector <double> current;
  vector <double> charge;
  vector <double> ptrig2_rate;
  vector <double> elclean_rate;
  vector <double> elreal_rate;
  vector <double> clt;
  vector <double> clt_err;
  vector <double> edtmlt;
  vector <double> edtmlt_err;
  vector <double> treff;
  vector <double> treff_err;
  vector <double> yield_clt_tr;
  vector <double> yield_clt_tr_err;
  vector <double> yield_clt_tr_elt;
  vector <double> yield_clt_tr_elt_err;
  vector <double> yield_edtmlt_tr;
  vector <double> yield_edtmlt_tr_err;
  vector <double> yield_edtmlt_tr_elt;
  vector <double> yield_edtmlt_tr_elt_err;
  vector <double> yield_elclean;
  vector <double> yield_elclean_err;
  vector <double> yield_elclean_elt;
  vector <double> yield_elclean_elt_err;
  vector <double> yield_elreal;
  vector <double> yield_elreal_err;
  vector <double> yield_elreal_elt;
  vector <double> yield_elreal_elt_err;
  vector <double> factor_elt;
  vector <double> factor_hgcer_elt;
  
  



  

  while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      double a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a1, b1, c1, d1;
      if(line[0] == '#') continue;
      
      if (!(iss >> a>> b >>c >>d>>e>> f>> g>> h>> i>> j>> k>> l>> m>> n>> o>> p>> q>> r>> s>> t>> u>> v>> w>> x>> y>> z>> a1>> b1>> c1>> d1 ))
        {
           
	  break;
           
        } 
       
      run.push_back(a);
      current.push_back(b);
      charge.push_back(c);
      ptrig2_rate.push_back(d);
      elclean_rate.push_back(e);
      elreal_rate.push_back(f);
      clt.push_back(g);
      clt_err.push_back(h);
      edtmlt.push_back(i);
      edtmlt_err.push_back(j);
      treff.push_back(k);
      treff_err.push_back(l);
      yield_clt_tr.push_back(m);
      yield_clt_tr_err.push_back(n);
      yield_clt_tr_elt.push_back(o);
      yield_clt_tr_elt_err.push_back(p);
      yield_edtmlt_tr.push_back(q);
      yield_edtmlt_tr_err.push_back(r);
      yield_edtmlt_tr_elt.push_back(s);
      yield_edtmlt_tr_elt_err.push_back(t);   
      yield_elclean.push_back(u);
      yield_elclean_err.push_back(v);
      yield_elclean_elt.push_back(w);
      yield_elclean_elt_err.push_back(x);
      yield_elreal.push_back(y);
      yield_elreal_err.push_back(z);
      yield_elreal_elt.push_back(a1);
      yield_elreal_elt_err.push_back(b1);
      factor_elt.push_back(c1);
      factor_hgcer_elt.push_back(d1);
      
    }

  for (int i =0; i< run.size(); i++)
    {
      cout<< run[i] <<"    "<<  current[i]<<"    "<< charge[i]<<"    "<<  ptrig2_rate[i]<<"    "<< elclean_rate[i]<<"    "<< elreal_rate[i]<<"    "<< clt[i]<<"    "<< clt_err[i]<<"    "<<  edtmlt[i]<<"    "<< edtmlt_err[i]<<"    "<< treff[i]<<"    "<< treff_err[i]<<"    "<< yield_clt_tr[i]<<"    "<< yield_clt_tr_err[i]<<"    "<< yield_clt_tr_elt[i]<<"    "<< yield_clt_tr_elt_err[i]<<"    "<< yield_edtmlt_tr[i]<<"    "<< yield_edtmlt_tr_err[i]<<"    "<< yield_edtmlt_tr_elt[i]<<"    "<< yield_edtmlt_tr_elt_err[i]<<"    "<<        yield_elclean[i]<<"    "<< yield_elclean_err[i]<<"    "<< yield_elclean_elt[i]<<"    "<< yield_elclean_elt_err[i]<<"    "<< yield_elreal[i]<<"    "<< yield_elreal_err[i]<<"    "<< yield_elreal_elt[i]<<"    "<< yield_elreal_elt_err[i]<<"    "<< factor_elt[i]<<"    "<< factor_hgcer_elt[i]<< endl;
    }
  cout<< "I am good"<<endl;

  //clt
  auto gr1 = new TGraphErrors(run.size(), &current[0], &yield_clt_tr[0], 0, &yield_clt_tr_err[0]);
  auto gr11= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_clt_tr[0], 0, &yield_clt_tr_err[0]);

  auto gr1a = new TGraphErrors(run.size(), &current[0], &yield_clt_tr_elt[0], 0, &yield_clt_tr_elt_err[0]);
  auto gr11a= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_clt_tr_elt[0], 0, &yield_clt_tr_elt_err[0]);
  //edtmlt
  
  auto gr2 = new TGraphErrors(run.size(), &current[0], &yield_edtmlt_tr[0], 0, &yield_edtmlt_tr_err[0]);
  auto gr22= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_edtmlt_tr[0], 0, &yield_edtmlt_tr_err[0]);
  
  auto gr2a = new TGraphErrors(run.size(), &current[0], &yield_edtmlt_tr_elt[0], 0, &yield_edtmlt_tr_elt_err[0]);
  auto gr22a= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_edtmlt_tr_elt[0], 0, &yield_edtmlt_tr_elt_err[0]);
  //elreal
  auto gr3 = new TGraphErrors(run.size(), &current[0], &yield_elreal[0], 0, &yield_elreal_err[0]);
  auto gr33= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_elreal[0], 0, &yield_elreal_err[0]);
  
  auto gr3a = new TGraphErrors(run.size(), &current[0], &yield_elreal_elt[0], 0, &yield_elreal_elt_err[0]);
  auto gr33a= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_elreal_elt[0], 0, &yield_elreal_elt_err[0]);
  //elclean
  auto gr4 = new TGraphErrors(run.size(), &current[0], &yield_elclean[0], 0, &yield_elclean_err[0]);
  auto gr44= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_elclean[0], 0, &yield_elclean_err[0]);
  
  auto gr4a = new TGraphErrors(run.size(), &current[0], &yield_elclean_elt[0], 0, &yield_elclean_elt_err[0]);
  auto gr44a= new TGraphErrors(run.size(), &ptrig2_rate[0], &yield_elclean_elt[0], 0, &yield_elclean_elt_err[0]);
  
  TCanvas *c1 = new TCanvas ("c1", "c1", 1000, 600);
  c1->Divide(2,2);
  c1->cd(1);gPad->SetGridx();gPad->SetGridy();
  
  gr1->Draw("AP");
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3);
  gr1->GetXaxis()->SetTitle("current (uA)");
  gr1->GetYaxis()->SetTitle("Yield (counts/uC)");
  // gr1->SetTitle("SHMS Yield 5347-5350 : Counts / (Q * edtmlt * Tr. Eff.)");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  gr1->Draw("AP");
  gr1->Fit("pol1");

  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(2.5);
  gStyle->SetOptFit();

  TString TarLabel = "Y = Good Counts/(Q*CompLT*Tr)    :";
  TF1 *fit = gr1->GetFunction("pol1");
  Double_t Ypidslope = fit->GetParameter(1);
  Double_t YpidslopeErr = fit->GetParError(1);
  Double_t Ypidint = fit->GetParameter(0);
  Double_t normSlope=Ypidslope/Ypidint*100*100;
  Double_t normSlopeErr= YpidslopeErr/Ypidint*100*100;
  TString ttemp=Form(" Slope/100uA  = %f +/- %f",normSlope,normSlopeErr);
  gr1->SetTitle(TarLabel+ttemp);


c1->cd(2);gPad->SetGridx();gPad->SetGridy();
  
  gr2->Draw("AP");
  gr2->SetMarkerColor(kBlack);
  gr2->SetLineColor(kBlack);
  gr2->SetLineWidth(3);
  gr2->GetXaxis()->SetTitle("current (uA)");
  gr2->GetYaxis()->SetTitle("Yield (counts/uC)");
  gr2->GetXaxis()->CenterTitle();
  gr2->GetYaxis()->CenterTitle();
  gr2->Draw("AP");
  gr2->Fit("pol1");

  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel2 = "Y = Good Counts/(Q*EdtmLT*Tr)    :";

  TF1 *fit2 = gr2->GetFunction("pol1");
  Double_t Ypidslope2 = fit2->GetParameter(1);
  Double_t YpidslopeErr2 = fit2->GetParError(1);
  Double_t Ypidint2 = fit2->GetParameter(0);
  Double_t normSlope2=Ypidslope2/Ypidint2*100*100;
  Double_t normSlopeErr2= YpidslopeErr2/Ypidint2*100*100;
  TString ttemp2=Form(" Slope/100uA  = %f +/- %f",normSlope2,normSlopeErr2);
  gr2->SetTitle(TarLabel2+ttemp2);

  c1->cd(3);gPad->SetGridx();gPad->SetGridy();
 
  gr3->Draw("AP");
  gr3->SetMarkerColor(kBlack);
  gr3->SetLineColor(kBlack);
  gr3->SetLineWidth(2);
  gr3->GetXaxis()->SetTitle("current (uA)");
  gr3->GetYaxis()->SetTitle("Yield (counts/uC)");
  gr3->GetXaxis()->CenterTitle();
  gr3->GetYaxis()->CenterTitle();
  gr3->Draw("AP");
  gr3->Fit("pol1");

  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel3 = "Y = Elreal Counts / Q    :";

  TF1 *fit3 = gr3->GetFunction("pol1");
  Double_t Ypidslope3 = fit3->GetParameter(1);
  Double_t YpidslopeErr3 = fit3->GetParError(1);
  Double_t Ypidint3 = fit3->GetParameter(0);
  Double_t normSlope3=Ypidslope3/Ypidint3*100*100;
  Double_t normSlopeErr3= YpidslopeErr3/Ypidint3*100*100;
  TString ttemp3=Form(" Slope/100uA  = %f +/- %f",normSlope3,normSlopeErr3);
  gr3->SetTitle(TarLabel3+ttemp3);

c1->cd(4);gPad->SetGridx();gPad->SetGridy();
 
  gr4->Draw("AP");
  gr4->SetMarkerColor(kBlack);
  gr4->SetLineColor(kBlack);
  gr4->SetLineWidth(2);
  gr4->GetXaxis()->SetTitle("current (uA)");
  gr4->GetYaxis()->SetTitle("Yield (counts/uC)");
  gr4->GetXaxis()->CenterTitle();
  gr4->GetYaxis()->CenterTitle();
  gr4->Draw("AP");
  gr4->Fit("pol1");

  gr4->SetMarkerStyle(20);
  gr4->SetMarkerSize(2.5);
  gStyle->SetOptFit();
  TString TarLabel4 = "Y = Elclean Counts / Q    :";

  TF1 *fit4 = gr4->GetFunction("pol1");
  Double_t Ypidslope4 = fit4->GetParameter(1);
  Double_t YpidslopeErr4 = fit4->GetParError(1);
  Double_t Ypidint4 = fit4->GetParameter(0);
  Double_t normSlope4=Ypidslope4/Ypidint4*100*100;
  Double_t normSlopeErr4= YpidslopeErr4/Ypidint4*100*100;
  TString ttemp4=Form(" Slope/100uA  = %f +/- %f",normSlope4,normSlopeErr4);
  gr4->SetTitle(TarLabel4+ttemp4);


  
  TString outputpdf;
  outputpdf = "pdf/shms_yield_5347_5350_all.pdf";
  c1->Print(outputpdf);
  
}
