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
#define NRUNS 1//4

void hgcer(){
  Int_t runs[NRUNS] = {6482};//,6483, 6484,6485};

  for(Int_t i=0; i<NRUNS; i++){
    TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_%d_20000.root", runs[i]),"read");
    
    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }
    TTree *tt=(TTree *)f->Get("T");

    Double_t nbins =1000;
    Double_t lo = -1000;
    Double_t hi = 15000;

    ////////////////////start1
    TH1F *h1[4];
    TH1F *h2[4];

    for (int icounter=0; icounter<4; icounter++){
   
      h1[icounter] = new TH1F(Form("hgc_pmt%d_amp",icounter+1),"",nbins, lo, hi);
      h2[icounter] = new TH1F(Form("hgc_pmt%d_noamp",icounter+1),"",nbins, lo, hi);

      cout<<"first hist is : "<<h1[icounter]<<endl;
      cout<<"second hist is : "<<h2[icounter]<<endl;


	
      tt->Draw(Form("P.hgcer.adcPedRaw>>hgc_pmt%d_amp",icounter+1),Form("P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==%d",icounter+1));
      tt->Draw(Form("P.hgcer.adcPedRaw>>hgc_pmt%d_noamp",icounter+1),Form("P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==%d",icounter+1));

      cout<<Form("P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==%d",icounter+1)<<endl;
      cout<<Form("P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==%d",icounter+1)<<endl;

    }
    TCanvas * c1 = new TCanvas("c1","hgcer_test",1600,1200);
    c1->Divide(2,2);
    for (int j = 0; j< 4; j++)
      {

	c1->cd(j+1);gPad->SetLogy();gPad->SetGrid();
	h1[j]->Draw();
	h1[j]->GetXaxis()->SetTitle(Form("hgc_pmt%d_amp_%d",j+1,j));
	h1[j]->SetLineColor(kBlue);
	h2[j]->Draw("sames");
	h2[j]->SetLineColor(kRed);

      }

  }
 c1->SaveAs(Form("pdf/hgcer_individual_pmts_%d.pdf",runs[i]));

}
