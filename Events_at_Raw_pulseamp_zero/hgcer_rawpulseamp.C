//This works for any number of runs
//This script will calulate the number of events in the hgcer as well as all 4 PMTs whose Raw Pulse Amplitude is zero.
//In the txtfile, there are 11 columns,the first is for run num second and third include all events with pulse amp >= 0 and pulse amp ==0 for the hgcer //detector. And 4th and 5th columns have events for pmt1 with amp>=0 and// with amp ==0. 6th,7th ... will include the same for pmt2, 3, and 4.
//have the branch P.hgcer* in DEF-files
//root -l hgcer_rawpulseamp.C
//for NGCER just replace hgcer with ngcer
//for HCER just replace P.hgcer with H.cer and also remove the last 4 histograms for pmt3 and pmt4

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
#define NRUNS 4

void hgcer_rawpulseamp(){
  Int_t runs[NRUNS] = {6482,6483, 6484,6485};

for(Int_t i=0; i<NRUNS; i++){
    TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/amp_zero/coin_replay_production_%d_-1.root", runs[i]),"read");
    
    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }

  Double_t nbins =1000;
  Double_t lo = -1000;
  Double_t hi = 20000;


  TH1D * hgc_all_amp = new TH1D ("hgc_all_amp","hgc_all_amp",nbins, lo,hi);
  TH1D * hgc_all_noamp = new TH1D ("hgc_all_noamp","hgc_all_noamp",nbins, lo,hi);

  TH1D * hgc_pmt1_amp = new TH1D ("hgc_pmt1_amp","hgc_pmt1_amp",nbins, lo,hi);
  TH1D * hgc_pmt1_noamp = new TH1D ("hgc_pmt1_noamp","hgc_pmt1_noamp",nbins, lo,hi);


  TH1D * hgc_pmt2_amp = new TH1D ("hgc_pmt2_amp","hgc_pmt2_amp",nbins, lo,hi);
  TH1D * hgc_pmt2_noamp = new TH1D ("hgc_pmt2_noamp","hgc_pmt2_noamp",nbins, lo,hi);


  TH1D * hgc_pmt3_amp = new TH1D ("hgc_pmt3_amp","hgc_pmt3_amp",nbins, lo,hi);
  TH1D * hgc_pmt3_noamp = new TH1D ("hgc_pmt3_noamp","hgc_pmt3_noamp",nbins, lo,hi);


  TH1D * hgc_pmt4_amp = new TH1D ("hgc_pmt4_amp","hgc_pmt4_amp",nbins, lo,hi);
  TH1D * hgc_pmt4_noamp = new TH1D ("hgc_pmt4_noamp","hgc_pmt4_noamp",nbins, lo,hi);


  
    
    TTree *tt=(TTree *)f->Get("T");
    
   	
	tt->Draw("P.hgcer.adcPedRaw>>hgc_all_amp","P.hgcer.adcPulseAmpRaw>=0");
	tt->Draw("P.hgcer.adcPedRaw>>hgc_all_noamp","P.hgcer.adcPulseAmpRaw==0");
	
	
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt1_amp","P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==1");
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt1_noamp","P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==1");
	
	
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt2_amp","P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==2");
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt2_noamp","P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==2");
	
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt3_amp","P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==3");
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt3_noamp","P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==3");
	
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt4_amp","P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==4");
	tt->Draw("P.hgcer.adcPedRaw>>hgc_pmt4_noamp","P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==4");
	
	

	TCanvas *c1= new TCanvas("c1","c1",1600,1200);
	c1->Divide(1,1);
	c1->cd(1);gPad->SetLogy();
	hgc_all_amp->Draw("");
	hgc_all_amp->SetLineColor(kBlue);
	hgc_all_noamp->Draw("sames");
	hgc_all_noamp->SetLineColor(kRed);
	hgc_all_amp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
	hgc_all_amp->SetTitle(Form("hgcer_all_pmts_%d",runs[i]));
	hgc_all_amp->GetXaxis()->CenterTitle();
	hgc_all_amp->GetXaxis()->SetTitleOffset(1.56);


	TCanvas *c2 = new TCanvas("c2","c2",1600,1200);
	c2->Divide(2,2);gPad->SetLogy();
	c2->cd(1);gPad->SetLogy();
	hgc_pmt1_amp->Draw("");
	hgc_pmt1_noamp->Draw("sames");
	hgc_pmt1_noamp->SetLineColor(kRed);
	hgc_pmt1_amp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
	hgc_pmt1_amp->SetTitle(Form("hgcer_pmt1_%d",runs[i]));
	hgc_pmt1_amp->GetXaxis()->CenterTitle();
     

	c2->cd(2);gPad->SetLogy();

	hgc_pmt2_amp->Draw();
	hgc_pmt2_noamp->Draw("sames");
	hgc_pmt2_noamp->SetLineColor(kRed);
	hgc_pmt2_amp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
	hgc_pmt2_amp->SetTitle(Form("hgcer_pmt2_%d",runs[i]));
	hgc_pmt2_amp->GetXaxis()->CenterTitle();



	c2->cd(3);gPad->SetLogy();

	hgc_pmt3_amp->Draw("");
	hgc_pmt3_noamp->Draw("sames");
	hgc_pmt3_noamp->SetLineColor(kRed);
	hgc_pmt3_amp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
	hgc_pmt3_amp->SetTitle(Form("hgcer_pmt3_%d",runs[i]));
	hgc_pmt3_amp->GetXaxis()->CenterTitle();


	c2->cd(4);gPad->SetLogy();

	hgc_pmt4_amp->Draw("");
	hgc_pmt4_noamp->Draw("sames");
	hgc_pmt4_noamp->SetLineColor(kRed);
	hgc_pmt4_amp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
	hgc_pmt4_amp->SetTitle(Form("hgcer_pmt4_%d",runs[i]));
	hgc_pmt4_amp->GetXaxis()->CenterTitle();

	Double_t evts_hgc_all_amp= hgc_all_amp->GetEntries();
	Double_t evts_hgc_all_noamp= hgc_all_noamp->GetEntries();
	Double_t evts_hgc_pmt1_amp= hgc_pmt1_amp->GetEntries();
	Double_t evts_hgc_pmt1_noamp= hgc_pmt1_noamp->GetEntries();
	Double_t evts_hgc_pmt2_amp= hgc_pmt2_amp->GetEntries();
	Double_t evts_hgc_pmt2_noamp= hgc_pmt2_noamp->GetEntries();
	Double_t evts_hgc_pmt3_amp= hgc_pmt3_amp->GetEntries();
	Double_t evts_hgc_pmt3_noamp= hgc_pmt3_noamp->GetEntries();
	Double_t evts_hgc_pmt4_amp= hgc_pmt4_amp->GetEntries();
	Double_t evts_hgc_pmt4_noamp= hgc_pmt4_noamp->GetEntries();


	ofstream txtfile ("txtfile/hgcer_rawpulse_amp.txt",ios::app);
	txtfile<<runs[i]<<"\t"<<evts_hgc_all_amp<<"\t"<<evts_hgc_all_noamp<<"\t"<<evts_hgc_pmt1_amp<<"\t"<<evts_hgc_pmt1_noamp<<"\t"<<evts_hgc_pmt2_amp<<"\t"<<evts_hgc_pmt2_noamp<<"\t"<<evts_hgc_pmt3_amp<<"\t"<<evts_hgc_pmt3_noamp<<"\t"<<evts_hgc_pmt4_amp<<"\t"<<evts_hgc_pmt4_noamp<<"\t"<<endl;

	c1->SaveAs(Form("pdf/hgcer_allpmts_%d.pdf",runs[i]));
	c2->SaveAs(Form("pdf/hgcer_individual_pmts_%d.pdf",runs[i]));

	delete c1;
	delete c2;


 }


}

