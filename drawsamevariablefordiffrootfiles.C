
The Line color is wrong, fix it 
#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>

#define NRUNS 5
using namespace std;

void hmscer(){


  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  gStyle->SetPadTopMargin(.15);
  gStyle->SetPadLeftMargin(.15);
  gStyle->SetPadBottomMargin(.15);
  TFile *f[NRUNS];
  TTree *t[NRUNS];
  TH1F *h[NRUNS];
  // Int_t runs[] = {6482,6485,6517,6518,6524};//6091,6104,6142,6256,6285,6300,6315,6326,6334,6350,6359,6385,6417,6419,6429,6448,6449,6473,6482,6485,6517,6518,6524};6482
  Int_t runs[] = {6482,6485,6517,6518,6524};

  for (Int_t i=0;i<NRUNS;i++){
    f[i]=new TFile(Form("ROOTfiles/coin_replay_production_%d_-1.root",runs[i]),"read");
    t[i]= (TTree*)f[i]->Get("T");
    h[i] = new TH1F(Form("h[%d]",i),Form(""),100, -100,8000);
   
    cout<<runs[i]<<endl;
  }
  TCanvas *c1 = new TCanvas("c1","",600,600);
  TLegend *leg = new TLegend(0.8,0.7,0.89,0.9);
  cout<<"I am Good"<<endl;
  c1->cd();gPad->SetLogy();
  t[0]->SetLineColor(kRed);
  //h[0]->SetLineWidth(4);
  t[0]->Draw("T.coin.hFADC_TREF_ROC1_adcPulseTimeRaw>>h[0](100,-100,8000)");
   leg->AddEntry(h[0],"Run_6482", "L");
   leg->Draw();
  cout<<"working"<<endl;
  for (Int_t i=1;i<NRUNS;i++){
    h[i]->SetLineColor(i);
    // h[i]->SetLineWidth(4);
    t[i]->Draw(Form("T.coin.hFADC_TREF_ROC1_adcPulseTimeRaw>>h[%d]",i),"","same");
    
    leg->AddEntry(h[i],Form("Run_%d", runs[i]), "L");
    leg->Draw();
    
  }
  cout<<"done!!"<<endl;

}
