#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>
#include <TGraph.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <TSystem.h>
#include <TString.h>
#include <TCut.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TChain.h>
#include <TTree.h>
#include <TF1.h>

using namespace std;

const Int_t NRUNS1 = 19;

void hcer_eff_mom3_vs1(){

  TFile *f1[NRUNS1];
  TTree *t1[NRUNS1];
  TTree *s1[NRUNS1];


  TH1D *h1[NRUNS1];
  TH1D *h2[NRUNS1];

  Double_t did1[NRUNS1];
  Double_t should1[NRUNS1];
  Double_t efficiency1[NRUNS1];
  Double_t error1[NRUNS1];
TGraphErrors * gr = new TGraphErrors();
  


//Int_t rruns1[NRUNS1] = {7593, 7594, 7595, 7596, 7597, 7599, 7600, 7601, 7602, 7603, 7604, 7635, 7636, 7637, 7638, 7639,7727,7728, 7730, 7733, 7735, 7736, 7765, 7766, 7767, 7768, 7769, 7770, 7771, 7772};

 Int_t rruns1[NRUNS1] = {7593, 7594, 7595, 7596, 7597, 7635, 7636, 7637, 7671, 7672, 7699, 7702, 7703, 7735, 7736, 7768, 7769, 7770, 7771};


  for (int i=0; i<NRUNS1;i++){
    f1[i]= new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/new_perfect/coin_replay_production_%d_-1.root",rruns1[i]),"read");
    t1[i]= (TTree *)f1[i]->Get("TSP");
    s1[i]= (TTree *)f1[i]->Get("T");

    auto nEntries1 = t1[i]->GetEntries();
    t1[i]->GetEntry(nEntries1 -1);

    h1[i] =new TH1D("h1[i]", "h2_Beta",200, 0.6, 1.4);
    h2[i] =new TH1D("h2[i]", "h2_Beta",200, 0.6, 1.4);

    s1[i]->Draw("H.gtr.beta>>h1[i]","P.gtr.dp>-10&&P.gtr.dp<20 && P.cal.etottracknorm> 0.15 && P.cal.etottracknorm<0.4 && P.hgcer.npeSum>0.5 && P.aero.npeSum> 0.5 && P.cal.eprtracknorm>0&&P.cal.eprtracknorm<0.15&& P.gtr.beta>0.7&&P.gtr.beta<1.3 && H.cal.etottracknorm>0.8&&H.cal.etottracknorm<1.2&& H.gtr.dp>-10&&H.gtr.dp<10 && H.gtr.beta>0.7&&H.gtr.beta<1.3 && H.cer.npeSum>0.0","");//did_cut

s1[i]->Draw("H.gtr.beta>>h2[i]","P.gtr.dp>-10&&P.gtr.dp<20 && P.cal.etottracknorm> 0.15 && P.cal.etottracknorm<0.4 && P.hgcer.npeSum>0.5 && P.aero.npeSum> 0.5 && P.cal.eprtracknorm>0&&P.cal.eprtracknorm<0.15&& P.gtr.beta>0.7&&P.gtr.beta<1.3 && H.cal.etottracknorm>0.8&&H.cal.etottracknorm<1.2&& H.gtr.dp>-10&&H.gtr.dp<10 && H.gtr.beta>0.7&&H.gtr.beta<1.3  ","");//did_cut

 did1[i] = h1[i]->GetEntries();
 should1[i] = h2[i]->GetEntries();
 efficiency1[i]= did1[i]/should1[i];
 error1[i]= (1/should1[i]) * sqrt(did1[i]*(1-did1[i]/should1[i]));
 cout<<rruns1[i]<< "   "<</*" Entries = "<<nEntries1<<  "   "<<*/ "did  = "<<did1[i]<<"  "<<"should  = " <<should1[i]<<"  "<<"eff  = "<<  efficiency1[i]<< " " <<"error = " <<error1[i]<<""<<endl;

 gr->SetPoint(i, rruns1[i], efficiency1[i]);
 gr->SetPointError(i, 0, error1[i]);

  }
  TCanvas *c1 =new TCanvas("c1", "", 500, 500);
  gr->Draw("AP*"); 
  c1->SaveAs("pdf/hcer_eff_high_mom.pdf");

}
