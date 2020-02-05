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
void hgcer_ampzero(){
ofstream txtfile ("txtfile/hgcer_amp_zero.txt",ios::app);
txtfile<<"======================================================================="<<endl;
txtfile<<"Run Num"<<"\t"<<"det/pmt"<<"\t"<<"evts_amp >=0"<<"\t"<<"evts_amp = 0"<<"\t"<<"% of zero amp evts"<<"\t"<<endl;
txtfile<<"======================================================================="<<endl;

gROOT->SetBatch(kTRUE);

  Int_t runs[NRUNS] = {6482,6483, 6484,6485};

  for(Int_t i=0; i<NRUNS; i++){
    //TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_%d_20000.root", runs[i]),"read");
     TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/amp_zero/coin_replay_production_%d_-1.root", runs[i]),"read");
     TFile *f1 = new TFile("root/hgcer_hist.root","RECREATE");


    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }
    TTree *tt=(TTree *)f->Get("T");

    Double_t nbins =1000;
    Double_t lo = -1000;
    Double_t hi = 15000;



    ///////////for first Canvas which will have info for the whole detector///////////////
    TH1F * hgcer_allpmt_allamp = new TH1F ("hgcer_allpmt_allamp","hgcer_allpmt_allamp",nbins, lo,hi);//hist for whole detector: amp >=0
    TH1F * hgcer_allpmt_noamp  = new TH1F ("hgcer_allpmt_noamp","hgcer_allpmt_noamp",nbins, lo,hi);//hist for whole detector: amp =0

    tt->Draw("P.hgcer.adcPedRaw>>hgcer_allpmt_allamp","P.hgcer.adcPulseAmpRaw>=0");
    tt->Draw("P.hgcer.adcPedRaw>>hgcer_allpmt_noamp","P.hgcer.adcPulseAmpRaw==0");

    ///////////for Second Canvas, which will have info for all the PMTs in the detector///////////////
    TH1F *h1[4];//hist for 4 pmts in hgcer (for amplitude >=0)
    TH1F *h2[4];//hist for 4 pmts in hgcer (for amplitude ==0 0)
    Double_t evts_ind_all[4];// prints events for 4 pmts  amp >=0
    Double_t evts_ind_no[4]; //prints events for 4 pmts amp ==0

    for (int icounter=0; icounter<4; icounter++){
      //P.hgcer.adcCounter=1=> pmt1 and so on
      

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
    hgcer_allpmt_noamp->SetLineColor(kRed);
    hgcer_allpmt_allamp->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
    hgcer_allpmt_allamp->SetTitle(Form("hgcer_all_pmts_%d",runs[i]));
    hgcer_allpmt_allamp->GetXaxis()->CenterTitle();
    hgcer_allpmt_allamp->GetXaxis()->SetTitleOffset(1.56);
    hgcer_allpmt_allamp->GetXaxis()->SetAxisColor(17);
    hgcer_allpmt_allamp->GetYaxis()->SetAxisColor(17);
    hgcer_allpmt_allamp->Write();
    hgcer_allpmt_noamp->Write();
    Double_t evts_tot_all = hgcer_allpmt_allamp->GetEntries();// for whole detector with amp >=0
    Double_t evts_tot_no  = hgcer_allpmt_noamp->GetEntries();// for whole detector with amp ==0

    txtfile << runs[i]<<"\t"<<std::setprecision(2)<<fixed<<"hgcer"<<"\t"<<evts_tot_all<<"\t"<<evts_tot_no<<"\t"<<evts_tot_no *100./evts_tot_all<< " % "<<endl;

    TCanvas * c1 = new TCanvas("c1","hgcer_test",1600,1200);
    c1->Divide(2,2);
    for (int j = 0; j< 4; j++)
      {

	c1->cd(j+1);gPad->SetLogy();gPad->SetGrid();
	h1[j]->Draw();
	h1[j]->GetXaxis()->SetTitle("P.hgcer.adcPedRaw");
	h1[j]->SetLineColor(kBlue);
	h1[j]->SetTitle(Form("hgcer_pmt_%d_%d",j+1,runs[i]));
	h1[j]->GetXaxis()->SetAxisColor(17);
	h1[j]->GetYaxis()->SetAxisColor(17);
	h2[j]->Draw("sames");
	h2[j]->SetLineColor(kRed);

        evts_ind_all[j] = h1[j]->GetEntries();//for individual pmts with amp >=0
	evts_ind_no[j]  = h2[j]->GetEntries();// for individula pmts with amp ==0
       
	h1[j]->Write();
	h2[j]->Write();

        txtfile<<runs[i]<<"\t"<<std::setprecision(2)<<fixed<<Form("pmt_%d",j+1)<<"\t"<<evts_ind_all[j]<<"\t"<<evts_ind_no[j]<<"\t"<<evts_ind_no[j]*100./evts_ind_all[j]<<" % "<<"\t"<<endl;
      }

    txtfile<<"======================"<<Form("Run Num %d",runs[i])<<" done "<<"========================"<<endl;
    txtfile<<"                                                                                        "<<endl;

    cc->SaveAs(Form("pdf/hgcer_whole_%d.pdf",runs[i]));//just one plot
    c1->SaveAs(Form("pdf/hgcer_pmts_%d.pdf",runs[i]));//for all pmts
    cc->~TCanvas();
    c1->~TCanvas();

    delete cc;
    delete c1;

  }

}






