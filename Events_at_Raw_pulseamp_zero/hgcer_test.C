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
    TH1F * hgc_allpmt_allamp = new TH1F ("hgc_allpmt_allamp","hgc_allpmt_allamp",nbins, lo,hi);
    TH1F * hgc_allpmt_noamp  = new TH1F ("hgc_allpmt_noamp","hgc_allpmt_noamp",nbins, lo,hi);

    tt->Draw("P.hgcer.adcPedRaw>>hgc_allpmt_allamp","P.hgcer.adcPulseAmpRaw>=0");
    tt->Draw("P.hgcer.adcPedRaw>>hgc_allpmt_noamp","P.hgcer.adcPulseAmpRaw==0");

    ///////////for Second Canvas, which will have info for all the PMTs in the detector///////////////
    TH1F *h1[4];
    TH1F *h2[4];

    for (int icounter=0; icounter<4; icounter++){
   
      

      h1[icounter] = new TH1F(Form("hgc_pmt%d_amp",icounter+1),"",nbins, lo, hi);
      h2[icounter] = new TH1F(Form("hgc_pmt%d_noamp",icounter+1),"",nbins, lo, hi);

      tt->Draw(Form("P.hgcer.adcPedRaw>>hgc_pmt%d_amp",icounter+1),Form("P.hgcer.adcPulseAmpRaw>=0&&P.hgcer.adcCounter==%d",icounter+1));
      tt->Draw(Form("P.hgcer.adcPedRaw>>hgc_pmt%d_noamp",icounter+1),Form("P.hgcer.adcPulseAmpRaw==0&&P.hgcer.adcCounter==%d",icounter+1));

    }


    TCanvas *cc = new TCanvas("cc","all pmts",1600,1200);
   
    cc->Divide(1,1);
    cc->cd(1);gPad->SetLogy();gPad->SetGrid();
    hgc_allpmt_allamp->Draw("");
    hgc_allpmt_allamp->SetLineColor(kBlue);
    hgc_allpmt_noamp->Draw("sames");
    hgc_allpmt_noamp->SetLineColor(30);
    hgc_allpmt_allamp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
    hgc_allpmt_allamp->SetTitle(Form("hgcer_all_pmts_%d",runs[i]));
    hgc_allpmt_allamp->GetXaxis()->CenterTitle();
    hgc_allpmt_allamp->GetXaxis()->SetTitleOffset(1.56);
    hgc_allpmt_allamp->GetXaxis()->SetAxisColor(17);
    hgc_allpmt_allamp->GetYaxis()->SetAxisColor(17);


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



      }


    //txtfile1<<runs[i]<<"\t"<<hgc_allpmt_allamp<<"\t"<<hgc_allpmt_noamp<<"\t"<<endl;
    //txtfile2<<runs[i]<<"\t"<<(Form("hgc_pmt%d_amp",j+1))<<"\t"<<(Form("hgc_pmt%d_noamp",j+1))<<"\t"<<endl;

	// Double_t evts_hgc_all_amp= hgc_all_amp->GetEntries();
	// Double_t evts_hgc_all_noamp= hgc_all_noamp->GetEntries();
	// Double_t evts_hgc_pmt1_amp= hgc_pmt1_amp->GetEntries();
	// Double_t evts_hgc_pmt1_noamp= hgc_pmt1_noamp->GetEntries();
	// Double_t evts_hgc_pmt2_amp= hgc_pmt2_amp->GetEntries();
	// Double_t evts_hgc_pmt2_noamp= hgc_pmt2_noamp->GetEntries();
	// Double_t evts_hgc_pmt3_amp= hgc_pmt3_amp->GetEntries();
	// Double_t evts_hgc_pmt3_noamp= hgc_pmt3_noamp->GetEntries();
	// Double_t evts_hgc_pmt4_amp= hgc_pmt4_amp->GetEntries();
	// Double_t evts_hgc_pmt4_noamp= hgc_pmt4_noamp->GetEntries();
     


    cc->SaveAs(Form("pdf/hgcer_allpmts_%d.pdf",runs[i]));
    c1->SaveAs(Form("pdf/hgcer_individual_pmts_%d.pdf",runs[i]));
    cc->~TCanvas();
    c1->~TCanvas();

    delete cc;
    delete c1;

  }

}









	//	txtfile2<<runs[i]<<endl;;//<<"\t"<<(Form("hgc_pmt%d_amp",j+1))<<"\t"<<(Form("hgc_pmt%d_noamp",j+1))<<"\t"<<endl;




    //ofstream txtfile ("txtfile/hgcer_singles.txt",ios::app);
    //txtfile<<runs[i]<<"\t"<<hgc_allpmt_allamp<<"\t"<<hgc_allpmt_noamp<<"\t"<<endl;

 //(Form("hgc_pmt%d_amp",j+1))<<"\t"<<(Form("hgc_pmt%d_noamp",j+1))<<"\t"<<endl;


    //hgc_pmt1_amp<<"\t"<<hgc_pmt1_noamp<<"\t"<<hgc_pmt2_amp<<"\t"<<hgc_pmt2_noamp<<"\t"hgc_pmt3_amp<<"\t"<<hgc_pmt3_noamp<<"\t"hgc_pmt4_amp<<"\t"<<hgc_pmt4_noamp<<"\t"<<endl;

































  /////////////////////////done1








  // TH1D * hgc_all_amp = new TH1D ("hgc_all_amp","hgc_all_amp",nbins, lo,hi);
  // TH1D * hgc_all_noamp = new TH1D ("hgc_all_noamp","hgc_all_noamp",nbins, lo,hi);

  // TH1D * hgc_pmt1_amp = new TH1D ("hgc_pmt1_amp","hgc_pmt1_amp",nbins, lo,hi);
  // TH1D * hgc_pmt1_noamp = new TH1D ("hgc_pmt1_noamp","hgc_pmt1_noamp",nbins, lo,hi);


  // TH1D * hgc_pmt2_amp = new TH1D ("hgc_pmt2_amp","hgc_pmt2_amp",nbins, lo,hi);
  // TH1D * hgc_pmt2_noamp = new TH1D ("hgc_pmt2_noamp","hgc_pmt2_noamp",nbins, lo,hi);


  // TH1D * hgc_pmt3_amp = new TH1D ("hgc_pmt3_amp","hgc_pmt3_amp",nbins, lo,hi);
  // TH1D * hgc_pmt3_noamp = new TH1D ("hgc_pmt3_noamp","hgc_pmt3_noamp",nbins, lo,hi);


  // TH1D * hgc_pmt4_amp = new TH1D ("hgc_pmt4_amp","hgc_pmt4_amp",nbins, lo,hi);
  // TH1D * hgc_pmt4_noamp = new TH1D ("hgc_pmt4_noamp","hgc_pmt4_noamp",nbins, lo,hi);


  
    
  ///////  TTree *tt=(TTree *)f->Get("T");
    
    /////////////start2

    //	tt->Draw("P.hgcer.adcPedRaw>>hgc_all_amp","P.hgcer.adcPulseAmpRaw>=0");

    //	tt->Draw("P.hgcer.adcPedRaw>>hgc_all_noamp","P.hgcer.adcPulseAmpRaw==0");







    //////////////////done2	


    /*

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

Double_t 	hgc_all_amp



	ofstream txtfile ("txtfile/hgcer_singles.txt",ios::app);
	txtfile<<runs[i]<<"\t"<<hgc_all_amp<<"\t"<<hgc_all_noamp<<"\t"<<hgc_pmt1_amp<<"\t"<<hgc_pmt1_noamp<<"\t"<<hgc_pmt2_amp<<"\t"<<hgc_pmt2_noamp<<"\t"hgc_pmt3_amp<<"\t"<<hgc_pmt3_noamp<<"\t"hgc_pmt4_amp<<"\t"<<hgc_pmt4_noamp<<"\t"<<endl;

	c1->SaveAs(Form("pdf/1hgcer_allpmts_%d.pdf",runs[i]));
	c2->SaveAs(Form("pdf/1hgcer_individual_pmts_%d.pdf",runs[i]));

	delete c1;
	delete c2;

   
 }


}

 */
