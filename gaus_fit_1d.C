//hist->Fit("gaus","O","",0.5,1.5);

#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>
#define NRUNS 3
using namespace std;

void hodo_pim_testfit(){
  Int_t runs[NRUNS] = {6067,6084,6090};//, 6095, 6099, 6103, 6111, 6118, 6122, 6127, 6141, 6241, 6245, 6253, 6257, 6264, 6271, 6277, 6287, 6290, 6293, 6297,6351, 6358, 6360, 6368, 6376, 6381, 6453, 6459, 6465, 6475, 6485, 6489, 6493, 6498};


  TFile *f[NRUNS];
  TTree *t[NRUNS];
  TH1F *h1[NRUNS];
  TH2F *h2[NRUNS];
  TH1F *h3[NRUNS];
  TH2F *h4[NRUNS];
  TCanvas *c1[NRUNS];
  

  for(Int_t i=0; i<NRUNS; i++){

    f[i]=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_hodo_%d_-1.root", runs[i]),"read");
    t[i]=(TTree *)f[i]->Get("T");

    h1[i] = new TH1F(Form("h1[%d]", i), Form(""),100, 0.6, 1.4);
    h1[i]->SetLineWidth(2);
    h1[i]->SetLineColor(kBlue);
    h1[i]->SetTitle(Form("Hms_hodo_#beta_Run_%d",runs[i]));
    h1[i]->GetYaxis()->SetTitle("Entries");
    h1[i]->GetYaxis()->CenterTitle();
    h1[i]->GetXaxis()->SetTitle("H_hod_beta");
    h1[i]->GetXaxis()->CenterTitle();
    h1[i]->GetXaxis()->SetTitleOffset(1.2);

    h2[i] = new TH2F(Form("h2[%d]", i), Form(""),100, 0.6, 1.4, 100, -10, 12);
    h2[i]->SetLineWidth(2);
    h2[i]->SetLineColor(kBlue);
    h2[i]->SetTitle(Form("Hms_#delta_vs_#beta_Run_%d",runs[i]));
    h2[i]->GetYaxis()->SetTitle("hms_delta");
    h2[i]->GetYaxis()->CenterTitle();
    h2[i]->GetXaxis()->SetTitle("H_hod_beta");
    h2[i]->GetXaxis()->CenterTitle();
    h2[i]->GetXaxis()->SetTitleOffset(1.2);

    h3[i] = new TH1F(Form("h3[%d]", i), Form(""),100, 0.6, 1.4);
    h3[i]->SetLineWidth(2);
    h3[i]->SetLineColor(kBlue);
    h3[i]->SetTitle(Form("Shms_hodo_#beta_Run_%d",runs[i]));
    h3[i]->GetYaxis()->SetTitle("Entries");
    h3[i]->GetYaxis()->CenterTitle();
    h3[i]->GetXaxis()->SetTitle("P_hod_beta");
    h3[i]->GetXaxis()->CenterTitle();
    h3[i]->GetXaxis()->SetTitleOffset(1.2);

    h4[i] = new TH2F(Form("h4[%d]", i), Form(""),100, 0.6, 1.4, 100, -10, 20);
    h4[i]->SetLineWidth(2);
    h4[i]->SetLineColor(kBlue);
    h4[i]->SetTitle(Form("Shms_#delta_vs_#beta_Run_%d",runs[i]));
    h4[i]->GetYaxis()->SetTitle("shms_delta");
    h4[i]->GetYaxis()->CenterTitle();
    h4[i]->GetXaxis()->SetTitle("P_hod_beta");
    h4[i]->GetXaxis()->CenterTitle();
    h4[i]->GetXaxis()->SetTitleOffset(1.2);


    gStyle->SetOptFit(1);
    c1[i] = new TCanvas(Form("c%d]", i),"",1000,1000); 
    c1[i]->Divide(2,2); 

    c1[i]->cd(1);gPad->SetGridx();
     t[i]->Draw(Form("H.hod.beta>>h1[%d]", i ),"H.gtr.dp>-10 &&H.gtr.dp <12 && H.cal.etottracknorm >0.7 && H.cal.etottracknorm <1.3");
     h1[i]->Fit("gaus","","",0.9,1.1);

     //the following is the alternative way of gaus fit instead of the above last line
     // TString hist_name = Form("h1[%d]", i);
     // TH1F *hist = (TH1F*)gDirectory->Get(hist_name);
     // hist->Fit("gaus", "","",0.9, 1.1);

     c1[i]->cd(2);gPad->SetGridx();
     t[i]->Draw(Form("H.gtr.dp:H.hod.beta>>h2[%d]", i ), "H.gtr.dp>-10 &&H.gtr.dp <12 && H.cal.etottracknorm >0.7 && H.cal.etottracknorm <1.3 ","colz");

     c1[i]->cd(3);gPad->SetGridx();
     t[i]->Draw(Form("P.hod.beta>>h3[%d]", i ),"P.gtr.dp>-10 &&P.gtr.dp <20 && P.aero.npeSum >2  &&P.cal.eprtracknorm < 0.2 && P.cal.etottracknorm <0.7 ");
     h3[i]->Fit("gaus","","",0.8,1.2);

     c1[i]->cd(4);gPad->SetGridx();
     t[i]->Draw(Form("P.gtr.dp:P.hod.beta>>h4[%d]", i ), "P.gtr.dp>-10 &&P.gtr.dp <20 &&  P.aero.npeSum >2 &&P.cal.eprtracknorm < 0.2 &&P.cal.etottracknorm < 0.7  ","colz");

     c1[i]->SaveAs(Form("pdf/hodo_%d.pdf",runs[i]));
 }
}
