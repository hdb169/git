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
void data_acc_substract(Int_t runNum){
  gStyle->SetOptStat(0);
#include "gStyle.h" 
#include "bin.h"
  TFile *f= new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_%d_-1.root",runNum));
   
  TFile *ff = new TFile(Form("root/data_acc_%d.root", runNum),"RECREATE");   

  TTree *tt = (TTree*)f->Get("T");

  Long64_t nentriesD = tt->GetEntries();

  cout<<"data entries = "<<nentriesD<<"  "<<endl;

  Double_t pionMass = 0.1395701835;   
  Double_t pbeta,hbeta,pdelta,hdelta,hcaletot,pcaletottrack,pcalepr,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,goodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit;
 
  TH1D *h_ctime = new TH1D("h_ctime", "h_ctime (ns)", binct, loct, hict);
  TH1D *h_ctime_d = new TH1D("h_ctime_d", "h_ctime_d (ns)", binct, loct, hict);
  TH1D *h_ctime_acc = new TH1D("h_ctime_acc", "h_ctime_acc", binct, loct, hict);


  TH1D *h_z = new TH1D("h_z","h_z", binz, loz, hiz);        
  TH1D *h_z_d = new TH1D("h_z_d","h_z_d", binz, loz, hiz);                                      
  TH1D *h_z_acc = new TH1D("h_z_acc","h_z_acc", binz, loz, hiz);                                      

                              
  TH1D *h_x = new TH1D("h_x","h_x", binx, lox, hix);   
  TH1D *h_x_d = new TH1D("h_x_d","h_x_d", binx, lox, hix);   
  TH1D *h_x_acc = new TH1D("h_x_acc","h_x_acc", binx, lox, hix);                                      

                                 
  TH1D *h_Q2d = new TH1D("h_Q2d","h_Q2d",binq, loq, hiq);  



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

      data_cut = paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.0 &&  pbeta > 0.8 && pbeta < 1.2 &&hbeta > 0.8 &&hbeta < 1.2 && phg>2 && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1;
  
      if(data_cut)
	{    cntsepi++;

	  h_ctime->Fill(ctime);
	  Epi = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	  z = Epi/pkinomega;
	  h_z->Fill(z);
          h_x->Fill(xbj);

	}
    }

  cout <<"events that passed all cuts except ctime = " << cntsepi << endl;

  /////////////////////////////////////////////////////////DATA HISTOGRAM WITH CTIME && PID_CUT/////////////////////////////////

  cout<<"calulating the max peak value of the ctime dist"<<endl;

  Int_t bin_max = h_ctime->GetMaximumBin();
  Double_t max_value = h_ctime->GetBinCenter(bin_max);
  cout<<"ctime peak is at = "<< max_value <<endl;

  for (int ll=0; ll<nentriesD;  ll++){
    tt->GetEntry(ll);
    if (ll % 700000 == 0) cout << ll*100/nentriesD << "   % of data done" << endl;

    pid_cut = paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.0 &&  pbeta > 0.8 && pbeta < 1.2 &&hbeta > 0.8 &&hbeta < 1.2 && phg>2 && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1 && ctime > (max_value-2) && ctime < (max_value+2);
  
    if(pid_cut){
      evts++;
      h_ctime_d->Fill(ctime);
      Epi_d = sqrt(pow(pionMass,2) + pow(PgtrP,2));
      z_d = Epi_d/pkinomega;
      h_z_d->Fill(z_d);
      h_x_d->Fill(xbj);


    }
  }


  /////////////////////////////////////////////////////////DATA HISTOGRAM WITH ONLY ACCIDENTALS/////////////////////////////////

  cout<<"calculating accidental backgrounds"<<endl;

  for (int mm=0; mm<nentriesD;  mm++)  
    //for (int mm=0; mm<50000;  mm++)

    {
      tt->GetEntry(mm);
      if (mm % 700000 == 0) cout << mm*100/nentriesD << "   % of data done" << endl;


      pid_cut_acc = paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.0 &&  pbeta > 0.8 && pbeta < 1.2 &&hbeta > 0.8 &&hbeta < 1.2 && phg>2 && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1 ;

      accR_cut        =   ctime > (max_value-14) && ctime < (max_value-6);
      accL_cut        =   ctime > (max_value+6) && ctime < (max_value+14);
     
      acc_cut    = (accL_cut || accR_cut) && pid_cut_acc;
      if(acc_cut){
	counts++;
	h_ctime_acc->Fill(ctime);
	Epi_acc = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc = Epi_acc/pkinomega;
	h_z_acc->Fill(z_acc);
	h_x_acc->Fill(xbj);



      }
    }    

  gROOT->SetBatch(kFALSE);
  cout<<"plotting the histograms"<<endl;

  
  // ofstream printout("txtfile/acc_sub.txt",ios::app);
  //printout<<"counts with other than ctime cut="<< h_ctime->Integral()<< " counts should ="<< h_ctime_should->Integral()<<" eff = "<<h_ctime_did->Integral()/h_ctime_should->Integral()<<endl;
  cout<<"total counts = "<<nentriesD<<"  "<<endl;
  cout<<"counts other than ctime cut = "<<h_ctime->Integral()<<endl;
  cout<<"counts with ctime cut = "<<h_ctime_d->Integral()<<endl;
  cout<<"counts in accidentals with = "<<h_ctime_acc->Integral()/4.0<<endl;


  TCanvas *c1 = new TCanvas("c1","c1",1600,1200);
 
  c1->Divide(3,3);
  c1->cd(1);
 
  h_ctime->SetLineColor(kRed);
  h_ctime->Draw("");
  h_ctime->SetTitle(" ctime with pid cut");
  h_ctime->SetLineWidth(2);
  c1->cd(2);
 
  h_z->SetLineColor(kBlack);
  h_z->Draw("e,p1");
  h_z->SetTitle("zhadron with pid cut");
  h_z->SetLineWidth(2);   

  c1->cd(3);
  h_ctime_d->SetLineColor(kBlue);
  h_ctime_d->Draw("");
  h_ctime_d->SetTitle("ctime with pid within -2<ctime<2 (ns)");
  h_ctime_d->SetLineWidth(2);	
  

  c1->cd(4);
  h_z_d->SetLineColor(kBlack);
  h_z_d->Draw("e,p1");
  h_z_d->SetTitle("zhadron with ctime cut");
  h_z_d->SetLineWidth(2);   

  c1->cd(5);
  h_z_acc->SetLineColor(kBlack);
  h_z_acc->Draw("e,p1");
  h_z_acc->SetTitle("zhadron with accidental (4 times less counts will be the actual)");
  h_z_acc->SetLineWidth(2);   

  c1->cd(6);
  h_ctime->Draw();
  h_ctime->SetLineColor(kBlue);
  h_ctime_acc->SetLineColor(kRed);
  h_ctime_acc->Draw("same");
  h_ctime_acc->SetTitle("ctime with acc within 8 ns on either side of peak (ns)");
  h_ctime_acc->SetLineWidth(2);	
  

  c1->cd(7);
  TH1D *h_z_d_copy = new TH1D("h_z_d_copy","h_z_d_copy",binz,loz,hiz);
  TH1D *h_z_acc_copy = new TH1D("h_z_acc_copy","h_z_acc_copy",binz,loz,hiz);

  h_z_d_copy= (TH1D*)h_z_d->Clone("h_z_d_copy");//copy of h_z_d
  h_z_acc_copy= (TH1D*)h_z_acc->Clone("h_z_acc_copy");//copy of h_z_acc

  h_z_d_copy->Scale(1.0/4.0);
  h_z_d->Draw("e,p1");
  h_z_d_copy->Draw("same");
  h_z_d_copy->SetLineColor(kRed);


  c1->cd(8);
  TH1D *h_ctime_d_copy = new TH1D("h_ctime_d_copy","h_ctime_d_copy",binct,loct,hict);
  TH1D *h_ctime_acc_copy = new TH1D("h_ctime_acc_copy","h_ctime_acc_copy",binct,loct,hict);

  h_ctime_d_copy= (TH1D*)h_ctime_d->Clone("h_ctime_d_copy");//copy of h_ctime_d
  h_ctime_acc_copy= (TH1D*)h_ctime_acc->Clone("h_ctime_acc_copy");//copy of h_ctime_acc

  h_ctime_d_copy->Scale(1.0/4.0);
  h_ctime_d->Draw("");
  h_ctime_d_copy->Draw("same");
  h_ctime_d_copy->SetLineColor(kRed);

  c1->cd(9);
  
  ////======================do the accidental subtraction: corrected hist-accidental hist=========================================

  TH1D *h_z_final = new TH1D("h_z_final","h_z_final",binz,loz,hiz);
  h_z_final->Add( h_z_d,  h_z_d_copy, 1.0, -1.0);
  h_z_final->Draw();
  h_z_final->SetLineColor(3);
  h_z_final->SetLineWidth(3);

  cout<<"final counts = "<<h_z_final->Integral()<<endl;

  //ofstream printout(Form("txtfile/acc_sub_%d.txt",ios::app,runNum));
  //printout<<"counts with other than ctime cut="<< h_ctime->Integral()<< " counts should ="<< h_ctime_should->Integral()<<" eff = "<<h_ctime_did->Integral()/h_ctime_should->Integral()<<endl;

  ofstream printout(Form("txtfile/data_acc_%d.txt",runNum));// ios::app will keep on adding lines in the txt file.
  printout<<runNum<< " " <<nentriesD<<" "<<  h_z->Integral() << " "<< h_z_d->Integral()<<"  "<< h_z_acc->Integral()<< " "<< h_z_d->Integral() - h_z_acc->Integral()/4.0<<" "<<h_z_final->Integral()<<endl;
  h_z->Write();
  h_z_d->Write();
  h_z_acc->Write();
  h_z_final->Write();
  //ff->cd();
  //ff->Write();
	       
  c1->SaveAs(Form("pdf/data_acc_%d.pdf",runNum));

  		

}















































