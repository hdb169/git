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
void hgcer(){

gROOT->SetBatch(kTRUE);

  Int_t runs[NRUNS] = {6482,6483, 6484,6485};

  for(Int_t i=0; i<NRUNS; i++){
    //TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_%d_20000.root", runs[i]),"read");
     TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/amp_zero/coin_replay_production_%d_-1.root", runs[i]),"read");

    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }
    TTree *tt=(TTree *)f->Get("T");

    Double_t nbins =1000;
    Double_t lo = -1000;
    Double_t hi = 15000;
    ofstream txtfile1 ("txtfile/hgcer_amp_zero_all_pmts.txt",ios::app);
    ofstream txtfile2 ("txtfile/hgcer_amp_zero_individual_pmts.txt",ios::app);

    ///////////for first Canvas which will have info for the whole detector///////////////
    TH1F * hgcer_allpmt_allamp = new TH1F ("hgcer_allpmt_allamp","hgcer_allpmt_allamp",nbins, lo,hi);
    TH1F * hgcer_allpmt_noamp  = new TH1F ("hgcer_allpmt_noamp","hgcer_allpmt_noamp",nbins, lo,hi);

    tt->Draw("P.hgcer.adcPedRaw>>hgcer_allpmt_allamp","P.hgcer.adcPulseAmpRaw>=0");
    tt->Draw("P.hgcer.adcPedRaw>>hgcer_allpmt_noamp","P.hgcer.adcPulseAmpRaw==0");

    ///////////for Second Canvas, which will have info for all the PMTs in the detector///////////////
    TH1F *h1[4];
    TH1F *h2[4];
    Double_t evts_ind_all[4];
    Double_t evts_ind_no[4]; 

    for (int icounter=0; icounter<4; icounter++){
   
      

      h1[icounter] = new TH1F(Form("hgcer_pmt%d_amp",icounter+1),"",nbins, lo, hi);
      h2[icounter] = new TH1F(Form("hgcer_pmt%d_noamp",icounter+1),"",nbins, lo, hi);

      tt->Draw(Form("P.hgcer.adcPedRaw>>hgcer_pmt%d_amp",icounter+1),Form("P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==%d",icounter+1));
      tt->Draw(Form("P.hgcer.adcPedRaw>>hgcer_pmt%d_noamp",icounter+1),Form("P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==%d",icounter+1));

    }


    TCanvas *cc = new TCanvas("cc","all pmts",1600,1200);
   
    cc->Divide(1,1);
    cc->cd(1);gPad->SetLogy();gPad->SetGrid();
    hgcer_allpmt_allamp->Draw("");
    hgcer_allpmt_allamp->SetLineColor(kBlue);
    hgcer_allpmt_noamp->Draw("sames");
    hgcer_allpmt_noamp->SetLineColor(30);
    hgcer_allpmt_allamp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
    hgcer_allpmt_allamp->SetTitle(Form("hgcer_all_pmts_%d",runs[i]));
    hgcer_allpmt_allamp->GetXaxis()->CenterTitle();
    hgcer_allpmt_allamp->GetXaxis()->SetTitleOffset(1.56);
    hgcer_allpmt_allamp->GetXaxis()->SetAxisColor(17);
    hgcer_allpmt_allamp->GetYaxis()->SetAxisColor(17);

    Double_t evts_tot_all = hgcer_allpmt_allamp->GetEntries();
    Double_t evts_tot_no  = hgcer_allpmt_noamp->GetEntries();

    TCanvas * c1 = new TCanvas("c1","hgcer_test",1600,1200);
    c1->Divide(2,2);
    for (int j = 0; j< 4; j++)
      {

	c1->cd(j+1);gPad->SetLogy();gPad->SetGrid();
	h1[j]->Draw();
	h1[j]->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
	h1[j]->SetLineColor(kBlue);
	h2[j]->Draw("sames");
	h2[j]->SetLineColor(30);
	h1[j]->SetTitle(Form("hgcer_pmt_%d_%d",j+1,runs[i]));
	h1[j]->GetXaxis()->SetAxisColor(17);
	h1[j]->GetYaxis()->SetAxisColor(17);

        evts_ind_all[j] = h1[j]->GetEntries();
	evts_ind_no[j] = h2[j]->GetEntries();


	cout<<setprecision(2)<<fixed<<"\t"<<runs[i]<<"\t"<< Form("pmt_%d",j+1)<<"\t"<<evts_ind_all[j]<<"\t"<< evts_ind_no[j]<<"\t"<< evts_ind_no[j]*100./evts_ind_all[j]<<" % "<<"\t"<< endl;
	cout<<"\t"<<endl;
        txtfile2<<setprecision(2)<<fixed<<runs[i]<<"\t"<<Form("pmt_%d",j+1)<<"\t"<<evts_ind_all[j]<<"\t"<< evts_ind_no[j]<<"\t"<<evts_ind_no[j]*100./evts_ind_all[j]<<" % "<<"\t"<<endl;
	txtfile2<<"\t"<<endl;
      }
    cout<<setprecision(2)<<fixed<<runs[i]<<"\t"<<" hgcer_allpmts "<<evts_tot_all<<"\t"<<evts_tot_no<<"\t"<<evts_tot_no *100./evts_tot_all<< " % "<<"\t"<< endl;
    cout<<"\t"<<endl;

    txtfile1<<setprecision(2)<<fixed<<runs[i]<<"\t"<<" hgcer_allpmts "<<evts_tot_all<<"\t"<<evts_tot_no<<"\t"<<evts_tot_no *100./evts_tot_all<< " % "<<endl;
    txtfile1<<"\t"<<endl;




    cc->SaveAs(Form("pdf/hgcer_allpmts_%d.pdf",runs[i]));
    c1->SaveAs(Form("pdf/hgcer_individual_pmts_%d.pdf",runs[i]));
    cc->~TCanvas();
    c1->~TCanvas();

    delete cc;
    delete c1;

  }

}






