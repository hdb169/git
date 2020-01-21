root -l
.x data_acc_subtract( 6263)
1)plots raw data distribution
2)plot accidental distribution (4 bunches)
3)scale data with (1/4)
4)subtract data hist and scaled hist->Final_hist

///////////header.h//////////////////
#define ROOT_header
#include "TH1F.h"
#include "TH2F.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TDecompLU.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <time.h>
#include <vector>
#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>
//#include "bin.h"
////////////////////////////gStyle.h//////////////////////////
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kTRUE);
  gROOT->ForceStyle(); 
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetNdivisions(505);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadLeftMargin(0.08);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadBottomMargin(.14);
  gStyle->SetTitleYOffset(1.09);
  gStyle->SetTitleXOffset(0.855);
  gStyle->SetTitleYSize(0.03);
  gStyle->SetTitleXSize(0.03);
  gStyle->SetLabelFont(62,"X");
  gStyle->SetLabelFont(62,"Y");
  gStyle->SetTitleFont(62,"X");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetLabelSize(0.025,"X");
  gStyle->SetLabelSize(0.025,"Y");
  gStyle->SetPaperSize(23,24);
//TChain *tt = new TChain("T");
////////////////////////////////////////////bin.h//////////////////////

Int_t binz = 100.;
Double_t loz = 0.0001;
Double_t hiz = 0.7;

Int_t binct = 200.;
Double_t loct = 20;
Double_t hict = 70;

Int_t binx = 100;
Double_t lox = 0.0001;
Double_t hix = 0.8;


Int_t binq = 20;
Double_t loq = 0.0001;
Double_t hiq = 10;
///////////////////////////////////////////////code/////////////////////////
//this macro reads a few variables from the rootfile and just takes the counts by doing the accidental subtraction which is calculated by using the cointime plot. we will have cut 1 i.e all the cuts execept the accidental subtraction cut and the other is cut 2 with all the cuts plus the accidental cut.
#include "header.h"
//void data_acc(Int_t runNum){//6263 data, 6261 dummy for trial
void data_acc(){
  Int_t runNum = 6263;//first run num here
  gStyle->SetOptStat(1111111);
#include "gStyle.h" 
#include "bin.h"
  TChain *tt = new TChain("T");
  // TFile *f= new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_%d_-1.root",runNum));
     tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_6263_-1.root");

  TFile *ff = new TFile(Form("root/data_acc_%d.root", runNum),"RECREATE");   

  //TTree *tt = (TTree*)f->Get("T");

  Long64_t nentriesD = tt->GetEntries();

  cout<<"data entries = "<<nentriesD<<"  "<<endl;

  Double_t pionMass = 0.1395701835;   
  Double_t pbeta,hbeta,pdelta,hdelta,hcaletot,pcaletottrack,pcalepr,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,goodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit;
 
  TH1D *h_datactime = new TH1D("h_datactime", "h_datactime (ns)", binct, loct, hict);
  TH1D *h_datactime_d = new TH1D("h_datactime_d", "h_datactime_d (ns)", binct, loct, hict);
  TH1D *h_datactime_acc = new TH1D("h_datactime_acc", "h_datactime_acc", binct, loct, hict);


  TH1D *h_dataz = new TH1D("h_dataz","h_dataz", binz, loz, hiz);        
  TH1D *h_dataz_d = new TH1D("h_dataz_d","h_dataz_d", binz, loz, hiz);                                      
  TH1D *h_dataz_acc = new TH1D("h_dataz_acc","h_dataz_acc", binz, loz, hiz);                                      

                              
  TH1D *h_datax = new TH1D("h_datax","h_datax", binx, lox, hix);   
  TH1D *h_datax_d = new TH1D("h_datax_d","h_datax_d", binx, lox, hix);   
  TH1D *h_datax_acc = new TH1D("h_datax_acc","h_datax_acc", binx, lox, hix);                                      

                                 
  TH1D *h_dataQ2d = new TH1D("h_dataQ2d","h_dataQ2d",binq, loq, hiq);  



  Int_t cntsepi=0;
  Int_t evts=0;
  Int_t counts=0;
 
#include "setbranch.h"

  Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc;
 

  /////////////////////////////////////////////////////////PART 1 find Coincidence time peak/////////////////////////////////
  for (int kk=0; kk<nentriesD;  kk++)//original
    //for (int kk=0; kk<50000;  kk++)
   
    {

      tt->GetEntry(kk);

      if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;

      data_cut = paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.7 && pbeta < 1.3 &&hbeta > 0.7 &&hbeta < 1.3  && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1;//no hgcer cut 
  
      if(data_cut)
	{    cntsepi++;

	  h_datactime->Fill(ctime);
	 
	 
	}
    }

  cout <<"events that passed all cuts except ctime = " << cntsepi << endl;

  /////////////////////////////////////////////////////////DATA HISTOGRAM WITH CTIME && PID_CUT/////////////////////////////////

  cout<<"calulating the max peak value of the ctime dist"<<endl;

  Int_t bin_max = h_datactime->GetMaximumBin();
  Double_t max_value = h_datactime->GetBinCenter(bin_max);
  cout<<"ctime peak is at = "<< max_value <<endl;

  for (int ll=0; ll<nentriesD;  ll++){
    tt->GetEntry(ll);
    if (ll % 700000 == 0) cout << ll*100/nentriesD << "   % of data done" << endl;

    pid_cut =  paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.7 && pbeta < 1.3 &&hbeta > 0.7 &&hbeta < 1.3  && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1 && ctime > (max_value-2) && ctime < (max_value+2);
  
    if(pid_cut){
      evts++;
      h_datactime_d->Fill(ctime);
      Epi_d = sqrt(pow(pionMass,2) + pow(PgtrP,2));
      z_d = Epi_d/pkinomega;
      h_dataz_d->Fill(z_d);
      h_datax_d->Fill(xbj);


    }
  }


  /////////////////////////////////////////////////////////DATA HISTOGRAM WITH ONLY ACCIDENTALS/////////////////////////////////

  cout<<"calculating accidental backgrounds"<<endl;

  for (int mm=0; mm<nentriesD;  mm++)  
    //for (int mm=0; mm<50000;  mm++)

    {
      tt->GetEntry(mm);
      if (mm % 700000 == 0) cout << mm*100/nentriesD << "   % of data done" << endl;


      pid_cut_acc =   paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.7 && pbeta < 1.3 &&hbeta > 0.7 &&hbeta < 1.3  && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1;

      accR_cut        =   ctime > (max_value-22) && ctime < (max_value-6);
      accL_cut        =   ctime > (max_value+6) && ctime < (max_value+22);
     
      acc_cut    = (accL_cut || accR_cut) && pid_cut_acc;
      if(acc_cut){
	counts++;
	h_datactime_acc->Fill(ctime);
	Epi_acc = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc = Epi_acc/pkinomega;
	h_dataz_acc->Fill(z_acc);
	h_datax_acc->Fill(xbj);


      }
    }    

  gROOT->SetBatch(kFALSE);
  cout<<"plotting the histograms"<<endl;

  TCanvas *c1 = new TCanvas("c1","c1",1600,1200);
 
  c1->Divide(3,3);
  c1->cd(1);
 
  h_datactime->SetLineColor(kBlue);
  h_datactime->Draw("");
  h_datactime->SetTitle(" ctime with pid cut");
  h_datactime->SetLineWidth(2);
  
  c1->cd(2);
  h_dataz_d->SetLineColor(kBlue);
  h_dataz_d->Draw("e,p1");
  h_dataz_d->SetTitle("zhadron with pid & ctime cut");
  h_dataz_d->SetLineWidth(2); 
  
  c1->cd(3);
  h_dataz_acc->SetLineColor(kRed);
  h_dataz_acc->Draw("e,p1");
  h_dataz_acc->SetTitle("zhadron with accidental in 8. peaks");
  h_dataz_acc->SetLineWidth(2);   

  c1->cd(4);
  h_datactime->Draw();
  h_datactime_acc->SetLineColor(kRed);
  h_datactime_d->Draw("same");
  h_datactime_d->SetFillColor(kPink);
  h_datactime_acc->Draw("same");
  h_datactime_acc->SetFillColor(kYellow);
  h_datactime_acc->SetTitle("ctime with acc within 8. peaks");
  h_datactime_acc->SetLineWidth(2);	
  


  c1->cd(5);
  TH1D *h_dataz_d_copy = new TH1D("h_dataz_d_copy","h_dataz_d_copy",binz,loz,hiz);
  TH1D *h_dataz_acc_copy = new TH1D("h_dataz_acc_copy","h_dataz_acc_copy",binz,loz,hiz);
  h_dataz_d_copy= (TH1D*)h_dataz_d->Clone();//copy of h_dataz_d
  h_dataz_acc_copy= (TH1D*)h_dataz_acc->Clone();//copy of h_dataz_acc
  h_dataz_acc_copy->Scale(1.0/8.0);// scale the accidental plot by 1/8.
  TH1D *h_dataz_acc_scaled= (TH1D*)h_dataz_acc_copy->Clone();
  h_dataz_acc_scaled->Draw();
  h_dataz_acc_scaled->SetLineColor(kRed);
  h_dataz_acc_scaled->SetLineWidth(2);
  h_dataz_acc_scaled->SetTitle("zhadron in scaled hist");


  c1->cd(6);

  h_dataz_d_copy->Draw("e,p1");
  h_dataz_acc_copy->Draw("same");
  h_dataz_d_copy->SetLineColor(kBlue);
  h_dataz_acc_copy->SetLineColor(kRed);



  c1->cd(7);
  
  ////======================do the accidental subtraction: corrected hist-accidental hist=========================================

  TH1D *h_dataz_final = new TH1D("h_dataz_final","h_dataz_final",binz,loz,hiz);// data-accidental
  h_dataz_final->Add( h_dataz_d_copy,  h_dataz_acc_copy, 1.0, -1.0);
  h_dataz_final->Draw("e,p1");
  h_dataz_final->SetLineColor(kBlack);
  h_dataz_final->SetLineWidth(3);


 
  ofstream printout(Form("txtfile/data_acc_%d.txt",runNum));// ios::app will keep on adding lines in the txt file.
  printout<<runNum<<"  "<<nentriesD<<"  "<<h_datactime->Integral()<< "  "<<h_dataz_d->Integral()<<"  "<<h_dataz_acc->Integral()<< "  "<<h_dataz_acc_scaled->Integral()<<"   "<<h_dataz_final->Integral()<<endl;
 
  c1->SaveAs(Form("pdf/data_acc_%d.pdf",runNum));

  cout<<"all entries = "<<nentriesD <<endl;
  cout<<"all without ctime cut = "<< h_datactime->GetEntries()<<endl;	
  cout<<"all with ctime cut = "<<h_dataz_d->GetEntries()<<endl; 	
  cout<<"accidental cuts in 8. peaks = "<<h_dataz_acc->GetEntries()<<endl;;
  cout<<"scaled accidental = "<<h_dataz_acc_scaled->GetEntries()<<endl;;
  cout<<"final good = "<<h_dataz_final->GetEntries()<<endl;

  cout<<" :::::::::::::::::"<<endl;

  cout<<"all entries = "<< nentriesD <<endl;
  cout<<"all without ctime cut = "<< h_datactime->Integral()<<endl;	
  cout<<"all with ctime cut = "<<h_dataz_d->Integral()<<endl; 	
  cout<<"accidental cuts in 8. peaks = "<<h_dataz_acc->Integral()<<endl;
  cout<<"scaled accidental ="<<h_dataz_acc_scaled->Integral()<<endl;
  cout<<"final good = "<<h_dataz_final->Integral()<<endl;
}
///////////////////////////////////////////////done///////////////////////////////////////////















































