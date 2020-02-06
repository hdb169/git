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
void phodo_2y_neg_ampzero(){
ofstream txtfile ("txtfile/phodo_2y_neg_amp_zero.txt",ios::app);
txtfile<<"======================================================================="<<endl;
txtfile<<"Run Num"<<"\t"<<"det/pmt"<<"\t"<<"evts_amp >=0"<<"\t"<<"evts_amp = 0"<<"\t"<<"% of zero amp evts"<<"\t"<<endl;
txtfile<<"======================================================================="<<endl;

gROOT->SetBatch(kTRUE);

 Int_t runs[NRUNS] = {6482,6483,6484,6485};

  for(Int_t i=0; i<NRUNS; i++){
    //TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_%d_20000.root", runs[i]),"read");
     TFile *f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/amp_zero/coin_replay_production_%d_-1.root", runs[i]),"read");
     TFile *f1 = new TFile("root/phodo_2y_neg_hist.root","RECREATE");


    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }
    TTree *tt=(TTree *)f->Get("T");

    Double_t nbins =1000;
    Double_t lo = -1000;
    Double_t hi = 15000;



    ///////////for first Canvas which will have info for the whole detector///////////////
    TH1F * phodo_2y_neg_allpmt_allamp = new TH1F ("phodo_2y_neg_allpmt_allamp","phodo_2y_neg_allpmt_allamp",nbins, lo,hi);//hist for whole detector: amp >=0
    TH1F * phodo_2y_neg_allpmt_noamp  = new TH1F ("phodo_2y_neg_allpmt_noamp","phodo_2y_neg_allpmt_noamp",nbins, lo,hi);//hist for whole detector: amp =0

    tt->Draw("P.hod.2y.negAdcPedRaw>>phodo_2y_neg_allpmt_allamp","P.hod.2y.negAdcPulseAmpRaw>=0");
    tt->Draw("P.hod.2y.negAdcPedRaw>>phodo_2y_neg_allpmt_noamp","P.hod.2y.negAdcPulseAmpRaw==0");

    ///////////for Second Canvas, which will have info for all the PMTs in the detector///////////////

    TH1F *h1[21];//hist for 21 pmts  (for amplitude >=0)
    TH1F *h2[21];//hist for 21 pmts  (for amplitude ==0 0)
    Double_t evts_ind_all[21];// prints events for 21 pmts  amp >=0
    Double_t evts_ind_no[21]; //prints events for 21 pmts amp ==0

    for (int icounter=0; icounter<21; icounter++){
      //P.hod.2y.negAdcCounter=1=> pmt1 and so on
      

      h1[icounter] = new TH1F(Form("phodo_2y_neg_pmt%d_amp",icounter+1),"",nbins, lo, hi);
      h2[icounter] = new TH1F(Form("phodo_2y_neg_pmt%d_noamp",icounter+1),"",nbins, lo, hi);

      tt->Draw(Form("P.hod.2y.negAdcPedRaw>>phodo_2y_neg_pmt%d_amp",icounter+1),Form("P.hod.2y.negAdcPulseAmpRaw>=0&&P.hod.2y.negAdcCounter==%d",icounter+1));
      tt->Draw(Form("P.hod.2y.negAdcPedRaw>>phodo_2y_neg_pmt%d_noamp",icounter+1),Form("P.hod.2y.negAdcPulseAmpRaw==0&&P.hod.2y.negAdcCounter==%d",icounter+1));

    }


    TCanvas *cc = new TCanvas("cc","all pmts",1600,1200);
   
    cc->Divide(1,1);
    cc->cd(1);gPad->SetLogy();gPad->SetGrid();
    phodo_2y_neg_allpmt_allamp->Draw("");
    cc->Update();
    //////////////
   
    phodo_2y_neg_allpmt_allamp->SetLineColor(kBlue);
    phodo_2y_neg_allpmt_allamp->GetXaxis()->SetTitle("P.hod.2y.negAdcPedRaw");
    phodo_2y_neg_allpmt_allamp->SetTitle(Form("phodo_2y_neg_all_pmts_%d",runs[i]));
    phodo_2y_neg_allpmt_allamp->GetXaxis()->CenterTitle();
    phodo_2y_neg_allpmt_allamp->GetXaxis()->SetTitleOffset(1.56);
    phodo_2y_neg_allpmt_allamp->GetXaxis()->SetAxisColor(17);
    phodo_2y_neg_allpmt_allamp->GetYaxis()->SetAxisColor(17);
    phodo_2y_neg_allpmt_noamp->Draw("sames");
    phodo_2y_neg_allpmt_noamp->SetLineColor(kRed);
    
    /////////////////statxbox all evts: blue, zero amp evts: red//////////
    gPad->Update();
    TPaveStats *p1 = (TPaveStats*) phodo_2y_neg_allpmt_allamp->FindObject("stats");
    p1->SetY1NDC(.68);
    p1->SetY2NDC(.93);
    p1->SetX1NDC(.75); 
    p1->SetX2NDC(0.9);
    p1->SetLineColor(kBlue);
    p1->SetLineWidth(2);
    p1->SetTextColor(kBlue);
    gPad->Update();
    TPaveStats *p2 = (TPaveStats*) phodo_2y_neg_allpmt_noamp->FindObject("stats");
    p2->SetY1NDC(.5);
    p2->SetY2NDC(.65);
    p2->SetX1NDC(.75); 
    p2->SetX2NDC(0.9);
    p2->SetLineColor(kRed);
    p2->SetLineWidth(2);
    p2->SetTextColor(kRed);
    gPad->Update();
    /////////////////////////////statbox done //////////////


  
    phodo_2y_neg_allpmt_allamp->Write();
    phodo_2y_neg_allpmt_noamp->Write();
    Double_t evts_tot_all = phodo_2y_neg_allpmt_allamp->GetEntries();// for whole detector with amp >=0
    Double_t evts_tot_no  = phodo_2y_neg_allpmt_noamp->GetEntries();// for whole detector with amp ==0
 
    txtfile << runs[i]<<"\t"<<std::setprecision(2)<<fixed<<"phodo_2y_neg"<<"\t\t"<<evts_tot_all<<"\t"<<evts_tot_no<<"\t\t"<<evts_tot_no *100./evts_tot_all<< " % "<<endl;

    TCanvas * c1 = new TCanvas("c1","individulal_pmts",1600,1200);
    c1->Divide(5,5);
    for (int j = 0; j< 21; j++)//for all pmts
      {

	c1->cd(j+1);gPad->SetLogy();gPad->SetGrid();
	h1[j]->Draw();
	h1[j]->GetXaxis()->SetTitle("P.hod.2y.negAdcPedRaw");
	h1[j]->SetLineColor(kBlue);
	h1[j]->SetTitle(Form("phodo_2y_neg_pmt_%d_%d",j+1,runs[i]));
	h1[j]->GetXaxis()->SetAxisColor(17);
	h1[j]->GetYaxis()->SetAxisColor(17);
	h2[j]->Draw("sames");
	h2[j]->SetLineColor(kRed);

        evts_ind_all[j] = h1[j]->GetEntries();//for individual pmts with amp >=0
	evts_ind_no[j]  = h2[j]->GetEntries();// for individula pmts with amp ==0
       
	h1[j]->Write();
	h2[j]->Write();

        txtfile<<runs[i]<<"\t"<<std::setprecision(2)<<fixed<<Form("pmt_%d",j+1)<<"\t"<<evts_ind_all[j]<<"\t\t"<<evts_ind_no[j]<<"\t\t"<<evts_ind_no[j]*100./evts_ind_all[j]<<" % "<<"\t"<<endl;
      }

    txtfile<<"======================"<<Form("Run Num %d",runs[i])<<" done "<<"========================"<<endl;
    txtfile<<"                                                                                        "<<endl;

    cc->SaveAs(Form("pdf/phodo_2y_neg_whole_%d.pdf",runs[i]));//just one plot
    c1->SaveAs(Form("pdf/phodo_2y_neg_pmts_%d.pdf",runs[i]));//for all pmts
    cc->~TCanvas();
    c1->~TCanvas();

    delete cc;
    delete c1;

  }

}






