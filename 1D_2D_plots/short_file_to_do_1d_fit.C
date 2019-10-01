
#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>
#define NRUNS 3
using namespace std;

void test(){
  Int_t runs[NRUNS] = {6359,6545,6524};//

  TFile *f[NRUNS];
  TTree *t[NRUNS];
  TH1F *h1[NRUNS];
  TH1F *h2[NRUNS];

  TCanvas *c1[NRUNS];
  TCanvas *c2[NRUNS];

  for(Int_t i=0; i<NRUNS; i++){
    f[i]=new TFile(Form("coin_replay_production_%d_-1.root", runs[i]),"read");
    t[i]=(TTree *)f[i]->Get("T");

    h1[i] = new TH1F(Form("h1[%d]", i), Form(""),100, 0.5, 1.5);
    h1[i]->SetLineWidth(2);
    h1[i]->SetLineColor(kBlue);
    h1[i]->SetTitle(Form("HMS_H.cal.etottracknorm_Run_%d",runs[i]));
    h1[i]->GetYaxis()->SetTitle("Entries");
    h1[i]->GetYaxis()->CenterTitle();
    h1[i]->GetXaxis()->SetTitle("hcal with -10<dp<10, 0.5<beta<1.5 && hcer>1.5");
    h1[i]->GetXaxis()->CenterTitle();
    h1[i]->GetXaxis()->SetTitleOffset(1.2);



    gStyle->SetOptFit(1);
    c1[i] = new TCanvas(Form("c%d]", i),"",1500,1200); 
    c1[i]->Divide(1,1); 
c1[i]->cd(1);gPad->SetGridx();
    t[i]->Draw(Form("H.cal.etottracknorm>>h1[%d]", i ),"H.gtr.dp>-10&&H.gtr.dp<10 && H.gtr.beta>0.5 && H.gtr.beta< 1.5 && H.cer.npeSum>1.5");
    h1[i]->Fit("gaus","","",0.9, 1.1);

    c1[i]->SaveAs(Form("sept30/hcal_%d.pdf",runs[i]));



    
    
  }

  

}
