#include <TSystem.h>
#include <TString.h>
#include "TFile.h"
#include "TTree.h"
#include <TNtuple.h>
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveLabel.h>
#include <TProfile.h>
#include <TPolyLine.h>
#include <TObjArray.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include<math.h>
using namespace std;

#define NRUNS 4
//void make_hist_shms_lumi(TString basename="",Int_t nrun=2043){

void shms_lumi_markversion(){
  Int_t runs[NRUNS] = {5347, 5348, 5349, 5350};

  for (int r=0; r< NRUNS; r++){
 TString filename = Form("/home/hdbhatt/Desktop/lumi/marklumi/ROOTfiles_bcm_flag_edtm/coin_replay_production_%d_-1.root", runs[r]);
    TFile *f = new TFile(filename, "READ");
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }
    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    cout<<"  "<<endl;
    





  
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(1000011);
  gStyle->SetOptFit(11);
  gStyle->SetTitleOffset(1.,"Y");
  gStyle->SetTitleOffset(.7,"X");
  gStyle->SetLabelSize(0.04,"XY");
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetPadLeftMargin(0.12);
 
  TObjArray HList(0);
  //
  TTree *tt = (TTree*) f->Get("T");
  TTree *ss = (TTree*) f->Get("TSP");
  //
  Double_t  Scal_evNumber;
  ss->SetBranchAddress("evNumber",&Scal_evNumber);
  Double_t  Scal_BCM4B_charge;
  ss->SetBranchAddress("P.BCM4B.scalerCharge",&Scal_BCM4B_charge);
  Double_t  Scal_BCM4B_current;
  ss->SetBranchAddress("P.BCM4B.scalerCurrent",&Scal_BCM4B_current);
  Double_t  Scal_BCM1_charge;
  ss->SetBranchAddress("P.BCM1.scalerCharge",&Scal_BCM1_charge);
  Double_t  Scal_BCM1_current;
  ss->SetBranchAddress("P.BCM1.scalerCurrent",&Scal_BCM1_current);
  Double_t  Scal_time;
  ss->SetBranchAddress("P.1MHz.scalerTime",&Scal_time);
  Double_t  Scal_EDTM;
  ss->SetBranchAddress("P.EDTM.scaler",&Scal_EDTM);
  Double_t  Scal_hEL_CLEAN;
  ss->SetBranchAddress("P.pEL_CLEAN.scaler",&Scal_hEL_CLEAN);
  Double_t  Scal_hEL_REAL;
  ss->SetBranchAddress("P.pEL_REAL.scaler",&Scal_hEL_REAL);
  Double_t  Scal_TRIG2;
  ss->SetBranchAddress("P.pTRIG2.scaler",&Scal_TRIG2);
  Double_t  Scal_TRIG3;
  ss->SetBranchAddress("P.pTRIG3.scaler",&Scal_TRIG3);
  Double_t  Scal_TRIG1;
  ss->SetBranchAddress("P.pTRIG1.scaler",&Scal_TRIG1);
  Double_t  Scal_TRIG4;
  ss->SetBranchAddress("P.pTRIG4.scaler",&Scal_TRIG4);
  Double_t  Scal_TRIG5;
  ss->SetBranchAddress("P.pTRIG5.scaler",&Scal_TRIG5);
  Double_t  Scal_TRIG6;
  ss->SetBranchAddress("P.pTRIG6.scaler",&Scal_TRIG6);
  Double_t  Scal_Splane[4];
  ss->SetBranchAddress("P.S1X.scaler",&Scal_Splane[0]);
  ss->SetBranchAddress("P.S1Y.scaler",&Scal_Splane[1]);
  ss->SetBranchAddress("P.S2X.scaler",&Scal_Splane[2]);
  ss->SetBranchAddress("P.S2Y.scaler",&Scal_Splane[3]);
  //loop through scalers
  Int_t nscal_reads=0;
  Int_t nscal_reads_cut=0;
  Double_t prev_read=-1;
  Double_t charge_sum=0;
  Double_t charge_sum_cut=0;
  Double_t prev_charge=0;
  Double_t charge_sum_corr=0;
  Double_t charge_sum_cut_corr=0;
  Double_t prev_charge_corr=0;
  Double_t event_flag[10000];
  Double_t scal_event_number[10000];
  Double_t tot_scal_EDTM=0;
  Double_t tot_scal_cut_EDTM=0;
  Double_t prev_EDTM=0;
  Double_t tot_scal_hEL_CLEAN=0;
  Double_t tot_scal_cut_hEL_CLEAN=0;
  Double_t prev_hEL_CLEAN=0;
  Double_t tot_scal_hEL_REAL=0;
  Double_t tot_scal_cut_hEL_REAL=0;
  Double_t prev_hEL_REAL=0;
  Double_t tot_scal_TRIG2=0;
  Double_t tot_scal_TRIG3=0;
  Double_t prev_TRIG2=0;
  Double_t prev_TRIG3=0;
  Double_t tot_scal_cut_TRIG2=0;
  Double_t tot_scal_cut_TRIG3=0;
  Double_t tot_scal_TRIG1=0;
  Double_t tot_scal_TRIG4=0;
  Double_t prev_TRIG1=0;
  Double_t prev_TRIG4=0;
  Double_t tot_scal_cut_TRIG1=0;
  Double_t tot_scal_cut_TRIG4=0;
  Double_t tot_scal_cut_time=0;
  Double_t tot_scal_TRIG5=0;
  Double_t prev_TRIG5=0;
  Double_t tot_scal_cut_TRIG5=0;
  Double_t tot_scal_TRIG6=0;
  Double_t prev_TRIG6=0;
  Double_t tot_scal_cut_TRIG6=0;
  Double_t threshold_cut=3.;
  //
  Double_t tot_scal_Splane[4]={0,0,0,0};
  Double_t prev_Splane[4]={0,0,0,0};
  Double_t tot_scal_cut_Splane[4]={0,0,0,0};
  //
  Double_t tot_scal_time=0;
  Double_t prev_time=0;
  //
  Long64_t scal_entries = ss->GetEntries();
  cout << " scal ent = " << scal_entries << endl;
  Double_t nlast=float(scal_entries);
  TH1F *h_cur_entry = new TH1F("h_cur_entry","; ENtry;current",nlast,0,nlast);
  TH1F *h_cur = new TH1F("h_cur","; Current ;",200,0,100);
  Long64_t data_entries = tt->GetEntries();
  for (int i = 0; i < scal_entries; i++) {
    ss->GetEntry(i);
    h_cur_entry->Fill(float(i),Scal_BCM1_current);
    if (Scal_BCM1_current > 3) h_cur->Fill(Scal_BCM1_current);
  }
  Double_t peak_current = h_cur->GetBinCenter(h_cur->GetMaximumBin());
  cout << " Peak current = " << peak_current  <<" " <<  h_cur->GetMaximumBin() << endl;
  Double_t Scal_BCM1_charge_corr=0;
  for (int i = 0; i < scal_entries; i++) {
    ss->GetEntry(i);
    event_flag[nscal_reads] = 0;
    scal_event_number[nscal_reads] = Scal_evNumber;
    Double_t BCM1_correction=1.;
    if (Scal_BCM1_current >2.) {
      if (Scal_BCM1_current <= 60) {
	BCM1_correction =1.0 + 0.045* ( log(60.)-log(Scal_BCM1_current))/( log(60.)-log(2.) );
      } else {
	BCM1_correction =1.0 + 0.010*(Scal_BCM1_current-60)/25.;
      } 
    }
    Scal_BCM1_charge_corr+=Scal_BCM1_current*(Scal_time-prev_time)*BCM1_correction;
    //cout << Scal_BCM1_charge << " "  << Scal_BCM1_charge_corr << " " << BCM1_correction << endl;
    if (TMath::Abs(Scal_BCM1_current-peak_current) < threshold_cut) {
      event_flag[nscal_reads] = 1;
      tot_scal_cut_time+=(Scal_time-prev_time);
      tot_scal_cut_EDTM+=(Scal_EDTM-prev_EDTM);
      tot_scal_cut_hEL_CLEAN+=(Scal_hEL_CLEAN-prev_hEL_CLEAN);
      tot_scal_cut_hEL_REAL+=(Scal_hEL_REAL-prev_hEL_REAL);
      tot_scal_cut_TRIG2+=(Scal_TRIG2-prev_TRIG2);
      tot_scal_cut_TRIG3+=(Scal_TRIG3-prev_TRIG3);
      tot_scal_cut_TRIG1+=(Scal_TRIG1-prev_TRIG1);
      tot_scal_cut_TRIG4+=(Scal_TRIG4-prev_TRIG4);
      tot_scal_cut_TRIG5+=(Scal_TRIG5-prev_TRIG5);
      tot_scal_cut_TRIG6+=(Scal_TRIG6-prev_TRIG6);
      for (Int_t s=0;s<4;s++) tot_scal_cut_Splane[s]+=(Scal_Splane[s]-prev_Splane[s]);
      //	     cout << i << " " << tot_scal_cut_Splane[0] << " " << Scal_Splane[0] << " " << prev_Splane[0] << endl;

      charge_sum_cut+=(Scal_BCM1_charge-prev_charge);
      charge_sum_cut_corr+=(Scal_BCM1_charge_corr-prev_charge_corr);
      nscal_reads_cut++;
    }
    prev_charge = Scal_BCM1_charge;
    prev_charge_corr = Scal_BCM1_charge_corr;
    prev_time = Scal_time;
    prev_EDTM = Scal_EDTM;
    prev_hEL_CLEAN = Scal_hEL_CLEAN;
    prev_hEL_REAL = Scal_hEL_REAL;
    prev_TRIG2 = Scal_TRIG2;
    prev_TRIG3 = Scal_TRIG3;
    prev_TRIG1 = Scal_TRIG1;
    prev_TRIG4 = Scal_TRIG4;
    prev_TRIG5 = Scal_TRIG5;
    prev_TRIG6 = Scal_TRIG6;
    for (Int_t s=0;s<4;s++) prev_Splane[s]=Scal_Splane[s];
    // cout <<  nscal_reads <<  " " << Scal_BCM4B_current << " " << event_flag[nscal_reads] << " " << Scal_TRIG1 << endl;
    nscal_reads++;
    charge_sum=Scal_BCM1_charge;
    charge_sum_corr=Scal_BCM1_charge_corr;
    tot_scal_EDTM=Scal_EDTM;
    tot_scal_hEL_CLEAN=Scal_hEL_CLEAN;
    tot_scal_hEL_REAL=Scal_hEL_REAL;
    tot_scal_TRIG2=Scal_TRIG2;
    tot_scal_TRIG3=Scal_TRIG3;
    tot_scal_TRIG1=Scal_TRIG1;
    tot_scal_TRIG4=Scal_TRIG4;
    tot_scal_TRIG5=Scal_TRIG5;
    tot_scal_TRIG6=Scal_TRIG6;
    tot_scal_time=Scal_time;
    for (Int_t s=0;s<4;s++) tot_scal_Splane[s]=Scal_Splane[s];
  }
  cout << "nscal_reads_cut " << nscal_reads_cut<< endl;
  //
  Double_t EDTM_timeraw;
  tt->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&EDTM_timeraw);
  Double_t gevtyp;
  tt->SetBranchAddress("g.evtyp",&gevtyp);
  Double_t gevnum;
  tt->SetBranchAddress("g.evnum",&gevnum);
  Double_t hntrack;
  tt->SetBranchAddress("P.dc.ntrack",&hntrack);
  Double_t hgoodscinhit;
  tt->SetBranchAddress("P.hod.goodscinhit",&hgoodscinhit);
  Double_t hgoodstarttime;
  tt->SetBranchAddress("P.hod.goodstarttime",&hgoodstarttime);
  Double_t hfptime;
  tt->SetBranchAddress("P.hod.fpHitsTime",&hfptime);
  Double_t hstarttime;
  tt->SetBranchAddress("P.hod.starttime",&hstarttime);
  Double_t hTimeHist_StartTime_Peak;
  tt->SetBranchAddress("P.hod.TimeHist_StartTime_Peak",&hTimeHist_StartTime_Peak);
  Double_t hTimeHist_StartTime_NumPeaks;
  tt->SetBranchAddress("P.hod.TimeHist_StartTime_NumPeaks",&hTimeHist_StartTime_NumPeaks);
  Double_t hTimeHist_StartTime_Hits;
  tt->SetBranchAddress("P.hod.TimeHist_StartTime_Hits",&hTimeHist_StartTime_Hits);
  Double_t hbetatrack;
  tt->SetBranchAddress("P.gtr.beta",&hbetatrack);
  Double_t hdelta;
  tt->SetBranchAddress("P.gtr.dp",&hdelta);
  Double_t Hetotnorm;
  tt->SetBranchAddress("P.cal.etotnorm",&Hetotnorm);
  Double_t Hhgcer_npeSum;
  tt->SetBranchAddress("P.hgcer.npeSum",&Hhgcer_npeSum);
  //
  TH1F* h_EDTM_CUT = new TH1F("h_EDTM"," ; EDTM (beam cut)",1000,0.,10000.);
  TH1F* h_EDTM_CUT2 = new TH1F("h_EDTM2"," ; EDTM (beam cut2)",1000,0.,10000.);
  TH1F* h_hStartTime = new TH1F("h_hStartTime",";HMS Starttime",200,0,200.);
  TH1F* h_hStartTime_track = new TH1F("h_hStartTime_track",";HMS Starttime",200,0,200.);
  TH1F* h_hFpTime = new TH1F("h_hFpTime",";HMS Fptime",200,0,200.);
  TH1F* h_etotnorm = new TH1F("h_etotnorm"," ; Etot norm",100,0.,2.);
  TH1F* h_npeSum = new TH1F("h_npeSum"," ; Cer Npe",100,0.,20.);
  TH1F* h_ev2 = new TH1F("h_ev2"," ; hEv2",10,0.,10.);
  TH1F* h_goodev2 = new TH1F("h_goodev2"," ; hgoodEv2",10,0.,10.);
  TH1F* h_goodev = new TH1F("h_goodev"," ; Good ev2 with PID cuts",10,0.,10.);
  TH1F* h_goodevTrack = new TH1F("h_goodevTrack"," ; Good ev2 with PID/track cuts",10,0.,10.);
	
  Int_t nscal_reads_2=0;
  for (int i = 0; i < data_entries; i++) {
    tt->GetEntry(i);
    //
    if (i%500000==0) cout << " Entry = " << i << endl;
    if (event_flag[nscal_reads_2]==1&&gevtyp==1 ) {
      Bool_t GoodEDTM = EDTM_timeraw>0;
      if (GoodEDTM) h_EDTM_CUT->Fill(EDTM_timeraw); 
      if (EDTM_timeraw>0) h_EDTM_CUT2->Fill(EDTM_timeraw); 
      h_ev2->Fill(gevtyp);
      if (!GoodEDTM) h_goodev2->Fill(gevtyp);
      h_etotnorm->Fill(Hetotnorm);
      if (Hetotnorm > .6) h_npeSum->Fill(Hhgcer_npeSum);
      if (Hetotnorm > 0.6&&hgoodscinhit==1 && hgoodstarttime==1) h_hStartTime->Fill(hstarttime);
      if (Hetotnorm > 0.6&&hgoodscinhit==1  && hgoodstarttime==1&& hntrack>0) h_hStartTime_track->Fill(hstarttime);
      if (Hetotnorm > 0.6&&Hhgcer_npeSum>1&& hstarttime!=-1000 &&!GoodEDTM ) {
	h_goodev->Fill(gevtyp);
	if (hntrack>0 && hdelta> -10 && hdelta<25.) {
	  h_goodevTrack->Fill(gevtyp);
	}
      }
      //
    }
    if (gevnum>scal_event_number[nscal_reads_2])  nscal_reads_2++;
  }
  //
  Int_t nev2 = h_ev2->Integral();
  Int_t good_ev2 = h_goodev2->Integral();
  Double_t good_ev2_err = TMath::Sqrt(good_ev2);
  Int_t nEDTM = h_EDTM_CUT->Integral();
  Int_t nEDTM2 = h_EDTM_CUT2->Integral();
  Double_t clt = (good_ev2)/(tot_scal_cut_TRIG2);
  Double_t clt_err = sqrt(tot_scal_cut_TRIG2-good_ev2)/tot_scal_cut_TRIG2;
  Double_t calc_treff= float(h_hStartTime_track->Integral())/float(h_hStartTime->Integral()) ;
  Double_t lt=  nEDTM/tot_scal_cut_EDTM;
  Double_t lt_err = sqrt(tot_scal_cut_EDTM-nEDTM)/tot_scal_cut_EDTM;
  Double_t good_ev = float(h_goodev->Integral())/clt;
  Double_t good_ev_err = TMath::Sqrt(h_goodev->Integral())/clt;
  Double_t good_evTrack = float(h_goodevTrack->Integral())/clt/calc_treff;
  Double_t good_evTrack_err = TMath::Sqrt(h_goodevTrack->Integral())/clt/calc_treff;
  //
  cout << nEDTM << " " << nEDTM2 << " " << tot_scal_cut_EDTM<< " EDTM rate = " << tot_scal_cut_EDTM/tot_scal_cut_time << endl;
  //
  Double_t err_hEL_CLEAN = 1./TMath::Sqrt(tot_scal_cut_hEL_CLEAN);
  Double_t err_hEL_REAL = 1./TMath::Sqrt(tot_scal_cut_hEL_REAL);
  Double_t err_trig2 = 1./TMath::Sqrt(tot_scal_cut_TRIG2);
  Double_t err_trig3 = 1./TMath::Sqrt(tot_scal_cut_TRIG3);
  Double_t err_trig1 = 1./TMath::Sqrt(tot_scal_cut_TRIG1);
  Double_t err_trig4 = 1./TMath::Sqrt(tot_scal_cut_TRIG4);
  Double_t err_trig5 = 1./TMath::Sqrt(tot_scal_cut_TRIG5);
  Double_t err_trig6 = 1./TMath::Sqrt(tot_scal_cut_TRIG6);

  
  cout << " data " << endl;
  cout << runs[r] << " "<< charge_sum_cut/tot_scal_cut_time  << " "<< charge_sum_cut_corr/tot_scal_cut_time << " " << clt << " " << clt_err<< " " << lt<< " " << lt_err  << " " << calc_treff << " " << good_ev2/tot_scal_cut_time << " " << good_ev/charge_sum_cut << " " <<  good_ev_err/charge_sum_cut << " " << good_evTrack/charge_sum_cut << " " <<  good_evTrack_err/charge_sum_cut << " " << tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << err_hEL_CLEAN*tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << tot_scal_cut_hEL_REAL/charge_sum_cut << " " << err_hEL_REAL*tot_scal_cut_hEL_REAL/charge_sum_cut << " " <<tot_scal_cut_hEL_REAL/tot_scal_cut_time<< endl;
  cout << " Scalers " << endl;
  cout << runs[r] << " "<< charge_sum_cut/tot_scal_cut_time<< " "<< charge_sum_cut_corr/tot_scal_cut_time << " " << tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << err_hEL_CLEAN*tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << tot_scal_cut_hEL_REAL/charge_sum_cut << " " << err_hEL_REAL*tot_scal_cut_hEL_REAL/charge_sum_cut << " " <<tot_scal_cut_hEL_CLEAN/tot_scal_cut_time << " " <<tot_scal_cut_hEL_REAL/tot_scal_cut_time  << endl;
  cout <<  runs[r] << " "<<tot_scal_cut_TRIG1/tot_scal_cut_time << endl;

  //
}
}
