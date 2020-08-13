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
void hms_lumi_markcode(){
  
  ofstream txtfile1("txtfile/hms_livetime.txt",ios::app);
  ofstream txtfile2("txtfile/hms_tracking_eff.txt",ios::app);
  ofstream txtfile3("txtfile/hms_yield.txt",ios::app);

  Int_t runs[NRUNS] = {5342, 5343, 5344, 5345, 5346};

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
    TTree *ss = (TTree*) f->Get("TSH");
    //
    Double_t  Scal_evNumber;
    ss->SetBranchAddress("evNumber",&Scal_evNumber);
    Double_t  Scal_BCM1_charge;
    ss->SetBranchAddress("H.BCM1.scalerCharge",&Scal_BCM1_charge);
    Double_t  Scal_BCM1_current;
    ss->SetBranchAddress("H.BCM1.scalerCurrent",&Scal_BCM1_current);
    Double_t  Scal_time;
    ss->SetBranchAddress("H.1MHz.scalerTime",&Scal_time);
    Double_t  Scal_EDTM;
    ss->SetBranchAddress("H.EDTM.scaler",&Scal_EDTM);
    Double_t  Scal_hEL_CLEAN;
    ss->SetBranchAddress("H.hEL_CLEAN.scaler",&Scal_hEL_CLEAN);
    Double_t  Scal_hEL_REAL;
    ss->SetBranchAddress("H.hEL_REAL.scaler",&Scal_hEL_REAL);
    Double_t  Scal_TRIG2;
    ss->SetBranchAddress("H.pTRIG2.scaler",&Scal_TRIG2);
    Double_t  Scal_TRIG3;
    ss->SetBranchAddress("H.pTRIG3.scaler",&Scal_TRIG3);
    Double_t  Scal_TRIG1;
    ss->SetBranchAddress("H.pTRIG1.scaler",&Scal_TRIG1);
    Double_t  Scal_TRIG4;
    ss->SetBranchAddress("H.pTRIG4.scaler",&Scal_TRIG4);
    Double_t  Scal_TRIG5;
    ss->SetBranchAddress("H.pTRIG5.scaler",&Scal_TRIG5);
    Double_t  Scal_TRIG6;
    ss->SetBranchAddress("H.pTRIG6.scaler",&Scal_TRIG6);
    Double_t  Scal_Splane[4];
    ss->SetBranchAddress("H.S1X.scaler",&Scal_Splane[0]);
    ss->SetBranchAddress("H.S1Y.scaler",&Scal_Splane[1]);
    ss->SetBranchAddress("H.S2X.scaler",&Scal_Splane[2]);
    ss->SetBranchAddress("H.S2Y.scaler",&Scal_Splane[3]);
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
    Double_t event_flag[10000];//---------------------------->Need to check for production Runs
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
    Double_t threshold_cut=3.;//uA
    
    Double_t tot_scal_Splane[4]={0,0,0,0};
    Double_t prev_Splane[4]={0,0,0,0};
    Double_t tot_scal_cut_Splane[4]={0,0,0,0};
    
    Double_t tot_scal_time=0;
    Double_t prev_time=0;
   
    Long64_t scal_entries = ss->GetEntries();
    cout << " scal ent = " << scal_entries << endl;
    Double_t nlast=float(scal_entries);//To get the total entries as a binsize
    
    TH1F *h_cur_entry = new TH1F("h_cur_entry","; Entry Num ( No Current Cut)  ;current (uA) ",nlast,0,nlast);
    TH1F *h_cur = new TH1F("h_cur","; Current (uA)[ > 3 uA only] ; counts ;",200,-10,100);
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
    c1->SaveAs(Form("pdf/hms_bcm_current_%d.pdf",runs[r]));

    delete c1;
    */
    Double_t peak_current = h_cur->GetBinCenter(h_cur->GetMaximumBin());
    cout << " Peak current = " << peak_current  <<" " <<  h_cur->GetMaximumBin() << endl;
    Double_t Scal_BCM1_charge_corr=0;

    cout<< " Total Data Entries = " <<tt->GetEntries()<<endl;
    cout<< " Total Scaler Entries = "<< ss->GetEntries()<<endl;

    for (int i = 0; i < scal_entries; i++) {
      ss->GetEntry(i);
      //if (i%100000==0) cout << " Entry = " << i << endl;
      event_flag[nscal_reads] = 0;//initially set this to zero
      scal_event_number[nscal_reads] = Scal_evNumber;//to be continued only upto the last scal evt


      //cout<< "i = "<< i<< "  "<<event_flag[nscal_reads] <<"   "<< scal_event_number[nscal_reads] <<"    "<< Scal_evNumber<<endl;
      Double_t BCM1_correction=1.;//initially
      if (Scal_BCM1_current >2.) {
	if (Scal_BCM1_current <= 60) {
	  BCM1_correction =1.0 + 0.045* (log(60.)-log(Scal_BCM1_current))/(log(60.)-log(2.) );
	} else {
	  BCM1_correction =1.0 + 0.010*(Scal_BCM1_current-60)/25.;
	} 
      }
      Scal_BCM1_charge_corr+=Scal_BCM1_current*(Scal_time-prev_time)*BCM1_correction;

      // cout<< "  i = "<< i<<"    "<< "Scal_time = " <<Scal_time<< "  "<< "prev_time = "<<prev_time<<"  "<< " Bcm1_curr_corr = "<<"   "<<BCM1_correction<<"  " << "Charge_corr = "<<"  "<< Scal_BCM1_charge_corr << endl; 

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

      // cout << "nscal_reads++ =" <<nscal_reads<<endl;
      //Followings are for : no bcm cut
      charge_sum=Scal_BCM1_charge;
      charge_sum_corr=Scal_BCM1_charge_corr;
      tot_scal_EDTM=Scal_EDTM;
      tot_scal_hEL_CLEAN=Scal_hEL_CLEAN;
      tot_scal_hEL_REAL=Scal_hEL_REAL;
      tot_scal_TRIG2=Scal_TRIG2;
      tot_scal_TRIG3=Scal_TRIG3;//------------------>HMS singles scaler events
      tot_scal_TRIG1=Scal_TRIG1;
      tot_scal_TRIG4=Scal_TRIG4;
      tot_scal_TRIG5=Scal_TRIG5;
      tot_scal_TRIG6=Scal_TRIG6;
      tot_scal_time=Scal_time;
      for (Int_t s=0;s<4;s++) tot_scal_Splane[s]=Scal_Splane[s];
    }
    //  cout << "nscal_reads_cut " << nscal_reads_cut<< endl;
    //
    Double_t EDTM_timeraw;
    tt->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&EDTM_timeraw);
    Double_t gevtyp;
    tt->SetBranchAddress("g.evtyp",&gevtyp);
    Double_t gevnum;
    tt->SetBranchAddress("g.evnum",&gevnum);
    Double_t hntrack;
    tt->SetBranchAddress("H.dc.ntrack",&hntrack);
    Double_t hgoodscinhit;
    tt->SetBranchAddress("H.hod.goodscinhit",&hgoodscinhit);
    Double_t hgoodstarttime;
    tt->SetBranchAddress("H.hod.goodstarttime",&hgoodstarttime);
    Double_t hfptime;
    tt->SetBranchAddress("H.hod.fpHitsTime",&hfptime);
    Double_t hstarttime;
    tt->SetBranchAddress("H.hod.starttime",&hstarttime);
    Double_t hTimeHist_StartTime_Peak;
    tt->SetBranchAddress("H.hod.TimeHist_StartTime_Peak",&hTimeHist_StartTime_Peak);
    Double_t hTimeHist_StartTime_NumPeaks;
    tt->SetBranchAddress("H.hod.TimeHist_StartTime_NumPeaks",&hTimeHist_StartTime_NumPeaks);
    Double_t hTimeHist_StartTime_Hits;
    tt->SetBranchAddress("H.hod.TimeHist_StartTime_Hits",&hTimeHist_StartTime_Hits);
    Double_t hbetatrack;
    tt->SetBranchAddress("H.gtr.beta",&hbetatrack);
    Double_t hbetanotrack;
    tt->SetBranchAddress("H.hod.betanotrack",&hbetanotrack);
    Double_t hdelta;
    tt->SetBranchAddress("H.gtr.dp",&hdelta);
    Double_t Hetotnorm;
    tt->SetBranchAddress("H.cal.etotnorm",&Hetotnorm);
    Double_t Hcer_npeSum;
    tt->SetBranchAddress("H.cer.npeSum",&Hcer_npeSum);
    //
    //my variables

    TH1F* h_typ2_evts = new TH1F(" h_typ2_evts"," ;  h_typ2_evts ",100, -2, 8.);
    TH1F* h_good_evts = new TH1F(" h_good_evts"," ;  h_typ2_evts ",100, -2, 8.);

    
    TH1F* h_edtm_accepted = new TH1F("h_edtm_accepted"," ; h_edtm_accepted ",1000, 0.,10000.);// Note check 10000 is ok for scaler counts
    TH1F* h_noedtm = new TH1F("h_noedtm"," ; h_noedtm ",1000, 0., 1000.);//edtm ==0
    
    TH1F* h_did_nopid = new TH1F("h_did_no_pid"," ; did_nopid ",100, 0., 2.);//beta
    TH1F* h_should_nopid = new TH1F("h_should_nopid"," ; should_nopid ",100, 0., 2.);//beta
    TH1F* h_did_pid = new TH1F("h_did_pid"," ; did_pid ",100, 0., 2.);//beta
    TH1F* h_should_pid = new TH1F("h_should_pid"," ; should_pid ",100, 0., 2.);//beta
    
    TH1F* h_good_counts_notrack = new TH1F("h_good_counts_notrack"," ; h_good_counts_notrack ",100, 0., 2.);//beta
    TH1F* h_good_counts_track = new TH1F("h_good_counts_track"," ; h_good_counts_track ",100, 0., 2.);//beta

    Long64_t data_entries = tt->GetEntries();	
    Int_t nscaler_reads=0;
    for (int i = 0; i < data_entries; i++) {
      tt->GetEntry(i);
      if (event_flag[nscaler_reads]==1  && gevtyp==2 ) {
	    
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
	    
	if (Hetotnorm > 0.6&&Hcer_npeSum>1&& hstarttime!=-1000 && EDTM_timeraw==0 && hntrack>0 && abs(hdelta) < 8) {
	  h_good_counts_track->Fill(hbetanotrack);}
      }

      if (gevnum > scal_event_number[nscaler_reads])  nscaler_reads++;
    }



    Double_t typ2_evts = h_typ2_evts->Integral();
    Double_t good_evts = h_good_evts->Integral();
    Double_t nEDTM =  h_edtm_accepted->Integral();
    
    Double_t treff_did_nopid = h_did_nopid->Integral();
    Double_t treff_should_nopid = h_should_nopid->Integral();
    Double_t tr_eff_nopid = treff_did_nopid/treff_should_nopid;//calc_treff
    Double_t tr_eff_nopid_err = (1/treff_should_nopid) * sqrt(treff_did_nopid *( 1 - treff_did_nopid/treff_should_nopid)); 

    Double_t treff_did_pid = h_did_pid->Integral();
    Double_t treff_should_pid = h_should_pid->Integral();
    Double_t tr_eff_pid = treff_did_pid/treff_should_pid;
    Double_t tr_eff_pid_err =  (1/treff_should_pid) * sqrt(treff_did_pid *( 1 - treff_did_pid/treff_should_pid)); ;

    // cout<<runs[r]<< "    "<<treff_did_pid<<"    "<<treff_should_pid<<endl;
    //  cout<<runs[r]<< " " << tr_eff_nopid<<"   "<< treff_did_nopid<<"    "<<  treff_should_nopid<<"             "<< tr_eff_pid<<"   "<<treff_did_pid<< "   "<< treff_should_pid << endl;

    
    Double_t cut_current_uncorr = charge_sum_cut/tot_scal_cut_time;
    Double_t cut_current_corr = charge_sum_cut_corr/tot_scal_cut_time;

    Double_t good_counts_notrack = h_good_counts_notrack->Integral();//no delta and no ntrack>0 but cal, cer
    Double_t good_counts_track = h_good_counts_track->Integral();//delta and ntrack>0 & cal, cer


    Double_t comp_lt = good_evts/(tot_scal_cut_TRIG3) ;
    Double_t comp_lt_err = comp_lt * sqrt(1./good_evts) ;

    Double_t edtm_lt = nEDTM/tot_scal_cut_EDTM;
    Double_t edtm_lt_err = edtm_lt * sqrt(1./nEDTM);

    
    Double_t yield_lt_notrack = good_counts_notrack/(charge_sum_corr* comp_lt);//no delta and no ntrack>0 cut
    Double_t yield_lt_notrack_err =yield_lt_notrack * sqrt(1./good_counts_notrack);


    Double_t yield_lt_track = good_counts_track/(charge_sum_corr* comp_lt * tr_eff_nopid);//delta and ntrack>0 
    Double_t yield_lt_track_err = yield_lt_track * sqrt(1./good_counts_track);

   

    Double_t Elclean_yield = tot_scal_cut_hEL_CLEAN/charge_sum_cut; //bare yield
    Double_t Elclean_yield_err =  Elclean_yield *sqrt(1./tot_scal_cut_hEL_CLEAN);


    Double_t Elreal_yield = tot_scal_cut_hEL_REAL/charge_sum_cut;//bare yield
    Double_t Elreal_yield_err = Elreal_yield * sqrt(1./ tot_scal_cut_hEL_REAL);


    
      
    Double_t err_hEL_CLEAN = 1./TMath::Sqrt(tot_scal_cut_hEL_CLEAN);
    Double_t err_hEL_REAL = 1./TMath::Sqrt(tot_scal_cut_hEL_REAL);
    Double_t err_trig2 = 1./TMath::Sqrt(tot_scal_cut_TRIG2);
    Double_t err_trig3 = 1./TMath::Sqrt(tot_scal_cut_TRIG3);
    Double_t err_trig1 = 1./TMath::Sqrt(tot_scal_cut_TRIG1);
    Double_t err_trig4 = 1./TMath::Sqrt(tot_scal_cut_TRIG4);
    Double_t err_trig5 = 1./TMath::Sqrt(tot_scal_cut_TRIG5);
    Double_t err_trig6 = 1./TMath::Sqrt(tot_scal_cut_TRIG6);

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

    c2->SaveAs(Form("pdf/plots_run_%d.pdf",runs[r]));

    delete c2;
    */


    txtfile1<< runs[r]<<"    "<< comp_lt<<"    "<< comp_lt_err<< "    "<< edtm_lt <<"    "<< edtm_lt_err<< endl;
    txtfile2<< runs[r]<<"    "<< tr_eff_nopid<<"    "<< tr_eff_nopid_err <<"    "<<  tr_eff_pid << "    "<<  tr_eff_pid_err<<endl;
    txtfile3<< runs[r]<<"    "<< yield_lt_notrack << "    "<< yield_lt_notrack_err <<"    "<<  yield_lt_track << "    "<< yield_lt_track_err <<"    "<< Elclean_yield <<"    "<<  Elclean_yield_err <<"    "<<  Elreal_yield <<"    "<<Elreal_yield_err<<endl;

  }
}


    

    /*
    Mark good_ev/charge_sum_cut = Hem good_counts_notrack/charge_sum_cut;(line 358)
Mark good_evTrack/charge_sum_cut = Hem good_counts_track/charge_sum_cut
Mark good_evTrack_err/charge_sum_cut = yield_lt_track
     */

    

















 
