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
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#define NRUNS 4

void plot_amp_int(){
  Int_t runs[NRUNS] = {6482,6483,6484,6485};
gROOT->SetBatch(kTRUE);

  for(Int_t i=0; i<NRUNS; i++){
    TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/amp_zero_default/coin_replay_production_%d_-1.root", runs[i]),"read");
    TFile *f1 = new TFile("root/phodo_amp_int.root","RECREATE");
    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }


    TH1F * pulseamp_pos[4];
    TH1F * pulseamp_neg[4];

    TH1F * pulseint_pos[4];
    TH1F * pulseint_neg[4];

    TTree *T=(TTree *)f->Get("T");
    Double_t nbins =100;
    Double_t lo = -100;
    Double_t hi = 300;
    string p_planes[4] = {"1x","1y","2x","2y"};
    // string p_planes[8] = {"1x.pos","1y.pos","2x.pos","2y.pos","1x.neg","1y.neg","2x.neg","2y.neg"};
    // you can do so, then just draw 2 hist insted of 4 

    double plane =4;

    for (int iplane=0;iplane<4; iplane++){

      pulseamp_pos[iplane] = new TH1F(Form("pulse_amp_%s_pos",p_planes[iplane].c_str()),"",nbins,lo,hi);
      T->Draw(Form("P.hod.%s.posAdcPulseAmp>>pulse_amp_%s_pos",p_planes[iplane].c_str(),p_planes[iplane].c_str()),"");

      pulseint_pos[iplane] = new TH1F(Form("pulse_int_%s_pos",p_planes[iplane].c_str()),"",nbins,lo,hi);
      T->Draw(Form("P.hod.%s.posAdcPulseInt>>pulse_int_%s_pos",p_planes[iplane].c_str(),p_planes[iplane].c_str()),"");

      pulseamp_neg[iplane] = new TH1F(Form("pulse_amp_%s_neg",p_planes[iplane].c_str()),"",nbins,lo,hi);
      T->Draw(Form("P.hod.%s.negAdcPulseAmp>>pulse_amp_%s_neg",p_planes[iplane].c_str(),p_planes[iplane].c_str()),"");

      pulseint_neg[iplane] = new TH1F(Form("pulse_int_%s_neg",p_planes[iplane].c_str()),"",nbins,lo,hi);
      T->Draw(Form("P.hod.%s.negAdcPulseInt>>pulse_int_%s_neg",p_planes[iplane].c_str(),p_planes[iplane].c_str()),"");

    }
    TCanvas *c1 = new TCanvas("c1","Pulse Amp Pos",1600,1200);
    c1->Divide(2,2);
     for (int j=0; j<4;j++){
       c1->cd(j+1);//gPad->SetLogy();
       gPad->SetGridx();
      pulseamp_pos[j]->Draw();
      pulseamp_pos[j]->GetXaxis()->SetTitle("Pulse Amplitude Pos [mV]");
      pulseamp_pos[j]->GetYaxis()->SetTitle("Entries");
      pulseamp_pos[j]->GetXaxis()->CenterTitle("");
      pulseamp_pos[j]->GetYaxis()->CenterTitle("");
      pulseamp_pos[j]->GetYaxis()->SetTitleOffset(1.2);
      pulseamp_pos[j]->Write();
       }


 TCanvas *c2 = new TCanvas("c2","Pulse Int Pos ",1600,1200);
    c2->Divide(2,2);
     for (int j=0; j<4;j++){
       c2->cd(j+1);//gPad->SetLogy();
       gPad->SetGridx();
      pulseint_pos[j]->Draw();
      pulseint_pos[j]->GetXaxis()->SetTitle("Pulse Integral Pos [mV]");
      pulseint_pos[j]->GetYaxis()->SetTitle("Entries");
      pulseint_pos[j]->GetXaxis()->CenterTitle("");
      pulseint_pos[j]->GetYaxis()->CenterTitle("");
      pulseint_pos[j]->GetYaxis()->SetTitleOffset(1.2);
      pulseint_pos[j]->Write();
       }

TCanvas *c3 = new TCanvas("c3","Pulse Amp Neg",1600,1200);
    c3->Divide(2,2);
     for (int j=0; j<4;j++){
       c3->cd(j+1);//gPad->SetLogy();
       gPad->SetGridx();
      pulseamp_neg[j]->Draw();
      pulseamp_neg[j]->GetXaxis()->SetTitle("Pulse Amplitude Neg [mV]");
      pulseamp_neg[j]->GetYaxis()->SetTitle("Entries");
      pulseamp_neg[j]->GetXaxis()->CenterTitle("");
      pulseamp_neg[j]->GetYaxis()->CenterTitle("");
      pulseamp_neg[j]->GetYaxis()->SetTitleOffset(1.2);
      pulseamp_neg[j]->Write();
       }


TCanvas *c4 = new TCanvas("c4","Pulse Int Neg",1600,1200);
    c4->Divide(2,2);
     for (int j=0; j<4;j++){
       c4->cd(j+1);//gPad->SetLogy();
       gPad->SetGridx();
      pulseint_neg[j]->Draw();
      pulseint_neg[j]->GetXaxis()->SetTitle("Pulse Integral [mV]");
      pulseint_neg[j]->GetYaxis()->SetTitle("Entries");
      pulseint_neg[j]->GetXaxis()->CenterTitle("");
      pulseint_neg[j]->GetYaxis()->CenterTitle("");
      pulseint_neg[j]->GetYaxis()->SetTitleOffset(1.2);
      pulseint_neg[j]->Write();
       }
     c1->SaveAs(Form("pdf/pulse_amp_pos_%d.pdf",runs[i]));
     c2->SaveAs(Form("pdf/pulse_int_pos_%d.pdf",runs[i]));
     c3->SaveAs(Form("pdf/pulse_amp_neg_%d.pdf",runs[i]));
     c4->SaveAs(Form("pdf/pulse_int_neg_%d.pdf",runs[i]));


     delete c1;
     delete c2;
     delete c3;
     delete c4; 
  }
}
