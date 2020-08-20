//do dummy subtraction//For 5347 to 5350 SHMS singles D2 and 5361, 62 SHMS singles Dummy ps =0, PTRIG2, ELreal trigger, evt typ =1

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

#define NRUNS 5
/*
ofstream txtfile("txtfile_shms/shms_all.txt");
ofstream txtfile1("txtfile_shms/shms_livetime_comp.txt");//,ios::app to rewrite at the end of file
ofstream txtfile2("txtfile_shms/shms_livetime_edtm.txt");
ofstream txtfile3("txtfile_shms/shms_tracking_eff_pid.txt");

ofstream txtfile4("txtfile_shms/shms_yield_track_edtmlt.txt");
ofstream txtfile5("txtfile_shms/shms_yield_track_clt.txt");
ofstream txtfile6("txtfile_shms/shms_yield_elclean.txt");
ofstream txtfile7("txtfile_shms/shms_yield_elreal.txt");

ofstream txtfile8("txtfile_shms/shms_yield_track_edtmlt_elt.txt");
ofstream txtfile9("txtfile_shms/shms_yield_track_clt_elt.txt");
ofstream txtfile10("txtfile_shms/shms_yield_elclean_elt.txt");
ofstream txtfile11("txtfile_shms/shms_yield_elreal_elt.txt");

ofstream txtfile12("txtfile_shms/shms_current_cut.txt");*/
ofstream txtfile13("txtfile_shms/shms_yield_notrack_edtmlt.txt");
ofstream txtfile14("txtfile_shms/shms_yield_notrack_clt.txt");



void shms_D2_5347_50(){
  Int_t runs[NRUNS] = {5347, 5348, 5349, 5350, 5361};
  // Int_t runs[NRUNS] = {6482, 6483, 6484, 6485};
  Int_t ps[NRUNS] = {1, 1, 1, 1, 1 };

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
    Double_t  Scal_pHGCER;
    ss->SetBranchAddress("P.HCER.scaler",&Scal_pHGCER);
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
    Double_t tot_scal_pHGCER=0;
    Double_t tot_scal_cut_pHGCER=0;
    Double_t prev_pHGCER=0;
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
    // cout << " scal ent = " << scal_entries << endl;
    Double_t nlast=float(scal_entries);
    TH1F *h_cur_entry = new TH1F("h_cur_entry","; ENtry;current",nlast,0,nlast);
    TH1F *h_cur = new TH1F("h_cur","; Current ;",200,0,100);
    //  Long64_t data_entries = tt->GetEntries();
    for (int i = 0; i < scal_entries; i++) {
      ss->GetEntry(i);
      h_cur_entry->Fill(float(i),Scal_BCM1_current);
      if (Scal_BCM1_current > 3) h_cur->Fill(Scal_BCM1_current);
    }
    /*
    TCanvas * c1 = new TCanvas("c1","hms_current",1000, 600);
    c1->Divide(2,1);
    c1->cd(1);
    h_cur_entry->Draw("");
    h_cur_entry->GetYaxis()->SetRangeUser(-10,80);
  
    c1->cd(2);gPad->SetLogy();
    h_cur->Draw("");
    h_cur->SetLineWidth(3);
    c1->SaveAs(Form("pdf_shms/shms_bcm_current_%d.pdf",runs[r]));

    delete c1;
  */
    Double_t peak_current = h_cur->GetBinCenter(h_cur->GetMaximumBin());
    //cout << " Peak current = " << peak_current  <<" " <<  h_cur->GetMaximumBin() << endl;
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
	tot_scal_cut_pHGCER+=(Scal_pHGCER-prev_pHGCER);
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
      prev_pHGCER = Scal_pHGCER;
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
      tot_scal_pHGCER=Scal_pHGCER;
      for (Int_t s=0;s<4;s++) tot_scal_Splane[s]=Scal_Splane[s];
    }
    // cout << "nscal_reads_cut " << nscal_reads_cut<< endl;
    //
    Double_t EDTM_timeraw;
    tt->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&EDTM_timeraw);
    Double_t gevtyp;
    tt->SetBranchAddress("g.evtyp",&gevtyp);
    Double_t gevnum;
    tt->SetBranchAddress("g.evnum",&gevnum);
    Double_t hbetanotrack;
    tt->SetBranchAddress("P.hod.betanotrack",&hbetanotrack);
  
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
    Double_t Hcer_npeSum;
    //tt->SetBranchAddress("P.hgcer.npeSum",&Hhgcer_npeSum);
    tt->SetBranchAddress("P.hgcer.npeSum",&Hcer_npeSum);

    //
    TH1F* h_typ2_evts = new TH1F(" h_typ2_evts"," ;  h_typ2_evts ",100, -2, 8.);
    TH1F* h_good_evts = new TH1F(" h_good_evts"," ;  h_typ2_evts ",100, -2, 8.);

    
    TH1F* h_edtm_accepted = new TH1F("h_edtm_accepted"," ; h_edtm_accepted ",1000, 0.,10000.);// Note check 10000 is ok for scaler counts
    TH1F* h_noedtm = new TH1F("h_noedtm"," ; h_noedtm ",1000, 0., 1000.);//edtm ==0
    
    TH1F* h_did_nopid = new TH1F("h_did_no_pid"," ; did_nopid ",100, 0., 2.);//beta
    TH1F* h_should_nopid = new TH1F("h_should_nopid"," ; should_nopid ",100, 0., 2.);//beta
    TH1F* h_did_pid = new TH1F("h_did_pid"," ; did_pid ",100, 0., 2.);//beta
    TH1F* h_should_pid = new TH1F("h_should_pid"," ; should_pid ",100, 0., 2.);//beta
    
    TH1F* h_good_counts_notrack = new TH1F("h_good_counts_notrack"," ; h_good_counts_notrack ",100, 0., 2.);//beta
    TH1F* h_good_counts_track = new TH1F("h_good_counts_track"," ; h_good_counts_track ",100, -20, 30.);//beta

    Long64_t data_entries = tt->GetEntries();	
    Int_t nscaler_reads=0;
    for (int i = 0; i < data_entries; i++) {
      tt->GetEntry(i);
      if (event_flag[nscaler_reads]==1  && gevtyp==1 ) {
	    
	h_typ2_evts->Fill(gevtyp);

	if(EDTM_timeraw==0){
	  h_good_evts->Fill(gevtyp);
	}
	    
	if (EDTM_timeraw>0){
	  h_edtm_accepted->Fill(EDTM_timeraw);
	}
	    
	if (hgoodscinhit==1 && hgoodstarttime==1){
	  h_should_nopid->Fill(hbetanotrack);
	}
	if (hgoodscinhit==1 && hgoodstarttime==1 && hntrack>0){
	  h_did_nopid->Fill(hbetanotrack);
	}
	//
	if (hgoodscinhit==1 && hgoodstarttime==1 && Hetotnorm> 0.6 &&  Hcer_npeSum > 1 && EDTM_timeraw==0){
	  h_should_pid->Fill(hbetanotrack);
	}
	    
	if (hgoodscinhit==1 && hgoodstarttime==1 && Hetotnorm> 0.6 &&  Hcer_npeSum > 1 &&EDTM_timeraw==0 &&   hntrack>0 ){
	  h_did_pid->Fill(hbetanotrack);
	}
	//
	if (Hetotnorm > 0.6&&Hcer_npeSum>1&& hstarttime!=-1000 && EDTM_timeraw==0) {
	  h_good_counts_notrack->Fill(hbetanotrack);
	}
	    
	if (Hetotnorm > 0.6&&Hcer_npeSum>1&& hstarttime!=-1000 && EDTM_timeraw==0 && hntrack>0 && hdelta> -10 && hdelta <25 ) {
	  h_good_counts_track->Fill(hdelta);}
      }

      if (gevnum > scal_event_number[nscaler_reads])  nscaler_reads++;
    }



    Double_t typ2_evts = h_typ2_evts->Integral();
    Double_t good_evts = h_good_evts->Integral();
    Double_t nEDTM =  h_edtm_accepted->Integral();
   
    Double_t treff_did_pid = h_did_pid->Integral();
    Double_t treff_should_pid = h_should_pid->Integral();

    Double_t tr_eff = treff_did_pid/treff_should_pid;
    Double_t tr_eff_err =  (1/treff_should_pid) * sqrt(treff_did_pid *( 1 - treff_did_pid/treff_should_pid)); ;

    // cout<<runs[r]<< "    "<<treff_did_pid<<"    "<<treff_should_pid<<endl;
    //  cout<<runs[r]<< " " << tr_eff_nopid<<"   "<< treff_did_nopid<<"    "<<  treff_should_nopid<<"             "<< tr_eff<<"   "<<treff_did_pid<< "   "<< treff_should_pid << endl;

    
    Double_t cut_current  = charge_sum_cut/tot_scal_cut_time;

    Double_t good_counts_notrack = h_good_counts_notrack->Integral();//no delta and no ntrack>0 but cal, cer
    Double_t good_counts_track = h_good_counts_track->Integral();//delta and ntrack>0 & cal, cer


    Double_t comp_lt = good_evts*ps[r]/(tot_scal_cut_TRIG2) ;//Trig2 for peter, trig1 for 6482-85
    Double_t comp_lt_err = comp_lt * sqrt(1./good_evts) ;

    Double_t edtm_lt = nEDTM/tot_scal_cut_EDTM;
    Double_t edtm_lt_err = edtm_lt * sqrt(1./nEDTM);

    //////////////////no track
    Double_t yield_clt_notrack = good_counts_notrack*ps[r]/(charge_sum_cut* comp_lt);//no delta and no ntrack>0 cut
    Double_t yield_clt_notrack_err =yield_clt_notrack * sqrt(1./good_counts_notrack);

    Double_t yield_edtmlt_notrack = good_counts_notrack*ps[r]/(charge_sum_cut* edtm_lt);//no delta and no ntrack>0 cut
    Double_t yield_edtmlt_notrack_err =yield_edtmlt_notrack * sqrt(1./good_counts_notrack);
    //////////////////no track


    
    Double_t yield_clt_track  = good_counts_track*ps[r]/(charge_sum_cut* comp_lt * tr_eff);//delta and ntrack>0 
    Double_t yield_clt_track_err = yield_clt_track  * sqrt(1./good_counts_track);

    Double_t yield_edtmlt_track  = good_counts_track*ps[r]/(charge_sum_cut* edtm_lt * tr_eff);//delta and ntrack>0 
    Double_t yield_edtmlt_track_err = yield_edtmlt_track  * sqrt(1./good_counts_track);
   

    Double_t yield_elclean = tot_scal_cut_hEL_CLEAN/charge_sum_cut; 
    Double_t yield_elclean_err =  yield_elclean *sqrt(1./tot_scal_cut_hEL_CLEAN);


    Double_t yield_elreal = tot_scal_cut_hEL_REAL/charge_sum_cut;
    Double_t yield_elreal_err = yield_elreal * sqrt(1./ tot_scal_cut_hEL_REAL);

    //Rate
    Double_t Elclean_Rate = tot_scal_cut_hEL_CLEAN/(tot_scal_cut_time*1000);
    Double_t Elreal_Rate = tot_scal_cut_hEL_REAL/(tot_scal_cut_time*1000);
    Double_t PTRIG2_Rate = tot_scal_cut_TRIG2/(tot_scal_cut_time*1000);
    Double_t hgcer_trig_rate =  tot_scal_cut_pHGCER/(tot_scal_cut_time*1000);//kHz
    Double_t PTRIG1_Rate = tot_scal_cut_TRIG1/(tot_scal_cut_time*1000);



    ///electronic LT correction
    Double_t PTrig1_rate_elt = (tot_scal_cut_TRIG1*50e-9)/(tot_scal_cut_time);//time sec
    Double_t PHGCER_rate_elt = (tot_scal_cut_pHGCER*100e-9)/(tot_scal_cut_time);//time sec-------------->For Pions

    Double_t factor_ptig1_ele_lt = 1 -  PTrig1_rate_elt;//electronic livetime
    Double_t factor_hgcer_ele_lt = 1 -  PHGCER_rate_elt;//electronic livetime HGCER

    Double_t yield_elreal_elt = tot_scal_cut_hEL_REAL/(charge_sum_cut * factor_ptig1_ele_lt) ;//bare yield
    Double_t yield_elreal_elt_err = yield_elreal_elt * sqrt(1./ tot_scal_cut_hEL_REAL);

   
    Double_t yield_elclean_elt = tot_scal_cut_hEL_CLEAN/(charge_sum_cut * factor_ptig1_ele_lt) ;//bare yield
    Double_t yield_elclean_elt_err = yield_elclean_elt * sqrt(1./ tot_scal_cut_hEL_CLEAN);

    Double_t yield_clt_track_elt  = good_counts_track*ps[r]/(charge_sum_cut* comp_lt * tr_eff * factor_ptig1_ele_lt );//delta and ntrack>0 
    Double_t yield_clt_track_elt_err = yield_clt_track_elt  * sqrt(1./good_counts_track);

    Double_t yield_edtmlt_track_elt  = good_counts_track*ps[r]/(charge_sum_cut* edtm_lt * tr_eff * factor_ptig1_ele_lt );
    Double_t yield_edtmlt_track_elt_err = yield_edtmlt_track_elt  * sqrt(1./good_counts_track);



    
  
    Double_t err_hEL_CLEAN = 1./TMath::Sqrt(tot_scal_cut_hEL_CLEAN);
    Double_t err_hEL_REAL = 1./TMath::Sqrt(tot_scal_cut_hEL_REAL);
    Double_t err_trig2 = 1./TMath::Sqrt(tot_scal_cut_TRIG2);
    Double_t err_trig3 = 1./TMath::Sqrt(tot_scal_cut_TRIG3);
    Double_t err_trig1 = 1./TMath::Sqrt(tot_scal_cut_TRIG1);
    Double_t err_trig4 = 1./TMath::Sqrt(tot_scal_cut_TRIG4);
    Double_t err_trig5 = 1./TMath::Sqrt(tot_scal_cut_TRIG5);
    Double_t err_trig6 = 1./TMath::Sqrt(tot_scal_cut_TRIG6);
    Double_t err_pHGCER = 1./TMath::Sqrt(tot_scal_cut_pHGCER);
    /*

    TCanvas * c2 = new TCanvas ("c2","c2", 1200, 800);
    c2->Divide(3,3);
    c2->cd(1);
    h_typ2_evts->Draw();

    c2->cd(2);gPad->SetLogy();
    h_edtm_accepted->Draw();

    c2->cd(3);
    h_should_nopid->Draw();
    c2->cd(3);
    h_did_nopid->Draw();

    c2->cd(4);
    h_should_pid->Draw();

    c2->cd(5);
    h_did_pid->Draw();

    c2->cd(6);
    h_good_counts_notrack->Draw();

    c2->cd(7);
    h_good_counts_track->Draw();

    c2->SaveAs(Form("pdf_shms/plots_run_%d.pdf",runs[r]));

    delete c2;
    */


    /*  txtfile1<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG2_Rate<<        "    "<< comp_lt<<                 "    "<< comp_lt_err<<endl;
    txtfile2<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG2_Rate<<        "    "<< edtm_lt <<                "    "<< edtm_lt_err<< endl;
    txtfile3<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG2_Rate<<        "    "<< tr_eff <<             "    "<< tr_eff_err<<endl;

    txtfile4<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG2_Rate<<        "    "<< yield_edtmlt_track << "    "<< yield_edtmlt_track_err<<endl;
    txtfile5<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG2_Rate<<        "    "<< yield_clt_track << "    "<< yield_clt_track_err<<endl;
    txtfile6<< runs[r]<<"    "<< cut_current<<"    "<<Elclean_Rate<<        "    "<< yield_elclean << "    "<< yield_elclean_err<<endl;
    txtfile7<< runs[r]<<"    "<< cut_current<<"    "<<Elreal_Rate<<        "    "<< yield_elreal << "    "<< yield_elreal_err<<endl;

    txtfile8<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG2_Rate<<        "    "<< yield_edtmlt_track_elt <<    "    "<< yield_edtmlt_track_elt_err<<endl;
    txtfile9<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG2_Rate<<        "    "<< yield_clt_track_elt <<    "    "<< yield_clt_track_elt_err<<endl;
    txtfile10<< runs[r]<<"    "<< cut_current<<"    "<<Elclean_Rate<<        "    "<<  yield_elclean_elt   <<"    "<<   yield_elclean_elt_err  <<endl;
    txtfile11<< runs[r]<<"    "<< cut_current<<"    "<<Elreal_Rate<<        "    "<<  yield_elreal_elt   <<"    "<<   yield_elreal_elt_err  <<endl;

    txtfile12<< runs[r]<<"    "<<cut_current<< "    "<<Elreal_Rate<<        "    "<<charge_sum_cut<<endl;*/
    txtfile13<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG2_Rate<<        "    "<< yield_edtmlt_notrack << "    "<< yield_edtmlt_notrack_err<<endl;
    txtfile14<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG2_Rate<<        "    "<< yield_clt_notrack << "    "<< yield_clt_notrack_err<<endl;
    

    
    // txtfile<< runs[r]<<"    "<< cut_current <<"    "<<charge_sum_cut<<"    "<< PTRIG2_Rate << "    "<< Elclean_Rate << "    "<< Elreal_Rate<<"    "<<comp_lt <<"    "<< comp_lt_err<<"    "<< edtm_lt<<"    "<< edtm_lt_err<<"    "<<tr_eff<<"    "<< tr_eff_err<<"    "<< yield_clt_track<<"    "<< yield_clt_track_err<<"    "<< yield_clt_track_elt<<  "    "<<yield_clt_track_elt_err<<"    "<<  yield_edtmlt_track<<"    "<< yield_edtmlt_track_err<<"    "<< yield_edtmlt_track_elt<<  "    "<<yield_edtmlt_track_elt_err<<"    "<<           yield_elclean<<"    "<< yield_elclean_err<<"    "<<  yield_elclean_elt <<"    "<< yield_elclean_elt_err<<"    "<< yield_elreal << "    "<< yield_elreal_err<<"    "<< yield_elreal_elt  <<"    "<<yield_elreal_elt_err<<"   "<<factor_ptig1_ele_lt<<"    "<< factor_hgcer_ele_lt <<endl;
  }
}





































    /*
      txtfile1<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< comp_lt<<                 "    "<< comp_lt_err<<endl;
      txtfile2<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< edtm_lt <<                "    "<< edtm_lt_err<< endl;
      txtfile3<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< tr_eff <<             "    "<< tr_eff_err<<endl;
      txtfile4<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<< yield_clt_track <<    "    "<< yield_clt_track_err<<endl;
      txtfile5<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<< yield_edtmlt_track << "    "<< yield_edtmlt_track_err<<endl;
      txtfile6<< runs[r]<<"    "<<cut_current<< "    "<<PTRIG1_Rate<<        "    "<<charge_sum_cut<<endl;
      txtfile7<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<<  yield_elreal   <<"    "<<   yield_elreal_err  <<endl;
      txtfile8<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<<  yield_elclean   <<"    "<<   yield_elclean_err  <<endl;
    */

    
    // txtfile1<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< comp_lt<<                 "    "<< comp_lt_err<<endl;
    // txtfile2<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< edtm_lt <<                "    "<< edtm_lt_err<< endl;
    // txtfile3<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< tr_eff <<             "    "<< tr_eff_err<<endl;
    // txtfile5<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<< yield_edtmlt_track << "    "<< yield_edtmlt_track_err<<endl;
    // txtfile6<< runs[r]<<"    "<<cut_current<< "    "<<PTRIG1_Rate<<        "    "<<charge_sum_cut<<endl;



    
    // txtfile4<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<< yield_clt_track_elt <<    "    "<< yield_clt_track_elt_err<<endl;
    // txtfile7<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<<  yield_elreal_elt   <<"    "<<   yield_elreal_elt_err  <<endl;
    // txtfile8<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<<  yield_elclean_elt   <<"    "<<   yield_elclean_elt_err  <<endl;

    // cout<<runs[r]<<"  "<<Elreal_rate<<endl;

    /*

      txtfile1<< runs[r]<<"    "<< cut_current<< "    "<<<<        "    "<< comp_lt<<                 "    "<< comp_lt_err<<endl;
      txtfile2<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< edtm_lt <<                "    "<< edtm_lt_err<< endl;
      txtfile3<< runs[r]<<"    "<< cut_current<< "    "<<PTRIG1_Rate<<        "    "<< tr_eff <<             "    "<< tr_eff_err<<endl;
      txtfile5<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<< yield_edtmlt_track << "    "<< yield_edtmlt_track_err<<endl;
      txtfile6<< runs[r]<<"    "<<cut_current<< "    "<<PTRIG1_Rate<<        "    "<<charge_sum_cut<<endl;



    
      txtfile4<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<< yield_clt_track_elt <<    "    "<< yield_clt_track_elt_err<<endl;
      txtfile7<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<<  yield_elreal_elt   <<"    "<<   yield_elreal_elt_err  <<endl;
      txtfile8<< runs[r]<<"    "<< cut_current<<"    "<<PTRIG1_Rate<<        "    "<<  yield_elclean_elt   <<"    "<<   yield_elclean_elt_err  <<endl;



    */





    


    /*
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

      cout<<  nEDTM <<"   "<<  nEDTM2<<endl;
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
    */
    //
 
