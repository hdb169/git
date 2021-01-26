#include "header.h"
#include <iostream>
#include <string>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TPaveText.h"
#define NRUNS 1//15//4//25//4
double c = 299792458;//speed of light
double shms_length = 20.1; //distance for SHMS arm from fp to target
double t_e(double p){
  double m = 0.000511;
  //1e9 is for unit convert, s to ns
  return (shms_length*std::sqrt(p*p+m*m)*1e9)/(c*p);
}
double t_pi(double p){
  double m = 0.139;
  return (shms_length*std::sqrt(p*p+m*m)*1e9)/(c*p);
}
double t_K(double p){
  double m = 0.493;
  return (shms_length*std::sqrt(p*p+m*m)*1e9)/(c*p);
}
double t_proton(double p){
  double m = 0.938;
  return (shms_length*std::sqrt(p*p+m*m)*1e9)/(c*p);
}



void plot_rftime_eff_4bins_7699_nohgc(){
  
  //#include "gStyle.h"
  // gStyle->SetOptStat(100011111);
  // gStyle->SetOptStat(1000011);//integral
  gStyle->SetOptStat(1111111);//integral

  ofstream txtfile1("txtfile_csv/livetime_csv.txt",ios::app);
  ofstream txtfile2("txtfile_csv/hms_tr_csv.txt",ios::app);
  ofstream txtfile3("txtfile_csv/shms_tr_csv.txt",ios::app);
  ofstream txtfile4("txtfile_csv/yield_bare_csv.txt",ios::app);
  ofstream txtfile5("txtfile_csv/yield_lttr_csv.txt",ios::app);
  ofstream txtfile6("txtfile_csv/hcal_eff.txt",ios::app);
  ofstream txtfile7("txtfile_csv/pcal_eff.txt",ios::app);
  ofstream txtfile8("txtfile_csv/all.txt",ios::app);
  ofstream txtfile9("txtfile_csv/all_uneedis.txt",ios::app);
  ofstream txtfile10("txtfile_csv/ctpeak_rfoffset.txt",ios::app);
  ofstream txtfile11("txtfile_csv/counts_info.txt",ios::app);
  // ofstream txtfile12("txtfile_csv/run_charge.txt",ios::app);//run num + charge
  // ofstream txtfile13("txtfile_csv/run_livetime.txt",ios::app);//run Num + lt

  // Int_t runs[NRUNS]={7635,7638,7593,7600};//+d2,+dum -d2 -dum
  // Double_t qcharge[NRUNS]={195380,132116,526204,300350  };
  // Double_t ltime[NRUNS]={0.994,0.998,0.992,0.998 };
  // Double_t teffhms[NRUNS]={0.998, 0.998,0.998, 0.999 };
  // Double_t teffshms[NRUNS]={0.98,0.98,0.974, 0.98  };
  // Int_t runs[NRUNS]={7808,7809,7811,7796,7797,7793,7794,    7813,7814,7812,7798,7799,7801,7802};//+d2,+dum -d2 -dum//all good

  //kin40-1.39-1
  // Int_t runs[NRUNS]={7808, 7811, 7796, 7793};//+d2,+dum -d2 -dum//all good
  // Double_t qcharge[NRUNS]={163335,103661,286669,200561 };
  // Double_t ltime[NRUNS]={0.987, 0.997, 0.985, 0.997 };
  // Double_t teffhms[NRUNS]={0.998, 0.999, 0.998,0.999 };
  // Double_t teffshms[NRUNS]={0.972, 0.984, 0.966, 0.978  }; //new below
  //Double_t teffshms[NRUNS]={0.38,0.41,0.52, 0.595  };
  //.//  //Double_t teffshms[NRUNS]={0.898, 0.891,0.88, 0.898  }; //new below

  Int_t runs[NRUNS]={7699};//, 7671};//7808,  7796 };//+d2,+dum -d2 -dum//all good
  Double_t qcharge[NRUNS]={163335};//,286669};
  Double_t ltime[NRUNS]={0.987};//,  0.985};
  Double_t teffhms[NRUNS]={0.998};//,  0.998 };
  Double_t teffshms[NRUNS]={0.972};//,  0.966  }; //new below
 

  // cout<<runs[r]<<
  gROOT->SetBatch("kTRUE");
  for(Int_t r=0; r<NRUNS; r++){

    cout<<runs[r]<<"  "<< qcharge[r]*  ltime[r]*  teffhms[r]*  teffshms[r]<<endl;
    // TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/added_%d.root", runs[r]);//7702+7703 only 7699 has different RF offset
    TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/coin_replay_production_%d_-1.root", runs[r]);

    TFile *f = new TFile(filename, "READ");
    // TFile * f11 = new TFile(Form("root_tree_new/charge_norm_data_hist_%d.root",runs[r]),"RECREATE");
    TFile * f11 = new TFile(Form("root_zbin/rfplot_zbins_%d.root",runs[r]),"RECREATE");

    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

    //#include "binkin391_401.h"
#include "bin7808.h"

    
    Double_t pionmass   = 0.1395701835;    //Gev/c^2 
    Double_t protonmass = 0.93827231;//GeV/c2
    Double_t dxbj, dQ2, dnu,domega,  dW2, dpmiss, demiss,  zhad, Mx2,Mx2a_acccut,Epi_acccut,zhad_acccut,Epi_pidcut,zhad_pidcut,Mx2_pidcut,Epi_cut,zhad_cut,Mx2_cut ;//d = data
    Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,phodgoodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit, phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,rf_pion,hhodgoodscinhit,hhodbetanotrack,hdcntrack,hgtry,pgtry,phodbetanotrack,hcaletotnorm,gevnum,hxptar,hyptar,pxptar,pyptar ;

    double scaler_eventnum,bcm1charge,bcm1current,scaler1MHztime,scaler1MHztimecut,bcm1chargecut,s1xscaler,s1yscaler,s2xscaler,s2yscaler,ptrig1scaler,ptrig2scaler,ptrig3scaler,ptrig4scaler,ptrig6scaler,pedtmscaler,pelcleanscaler,pl1acceptscaler,edtmtdctime,edtmtdctimeraw,mult,ptrig1rate,rate,charge   ;
    
    Double_t Epi_dcut0, z_dcut0, Epi_dcut1, z_dcut1, Epi_dcut2, z_dcut2, Epi_dcut3, z_dcut3, Epi_dcut1plus2, z_dcut1plus2; 
    Double_t Epi_acc0, z_acc0, Epi_acc1, z_acc1, Epi_acc2, z_acc2, Epi_acc3, z_acc3, Epi_acc1plus2, z_acc1plus2;

    Bool_t  accR_cut, accL_cut,shms_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, mod4_pioncut, mod4_notpioncut, pcal_cut, ctime_cut, hms_cut, pcal_cut_tight, cuttype1, cuttype1acc, cuttype2, cuttype2acc, cuttype1plus2, cuttype1plus2acc , hgcer_cut_loose,  paero_cut_loose,  cuttype0, cuttype0acc, common_cut, cuttype3, cuttype3acc, accsub_cut, acc_cut, shms_tr_did_cut, shms_tr_should_cut, hms_tr_did_cut, hms_tr_should_cut,basic_cut,basic_cal_aero, hms_cal_should_cut, hms_cal_did_cut, shms_cal_should_cut, shms_cal_did_cut, cal_eff_hms_shms_base_cut  ;

    Double_t Epi_cut_acc, zhad_cut_acc, Mx2_cut_acc;
    Double_t ctmin = 1.6;//1.5
    Double_t ctmax = 1.6;//1.5
    Double_t rfmin = 0.4;//0.5;
    Double_t rfmax = 1.6;//1.5;
    Double_t eprmin = 0.0;
    Double_t eprmax = 0.2;//0.15;
    Double_t pcaletotmin = 0.0;
    Double_t pcaletotmax = 0.75;
    Double_t offsetrf;
     
   
#include "offsetrf.h"
    TTree * tt = (TTree *)f->Get("T");
    TTree * ss = (TTree *)f->Get("TSP");
#include "define_histogram.h"

   

    //----------------------------------------Fill Hist
#include "branch.h"
    //#include "scalerbranch.h"

    Long64_t nentriesD = tt->GetEntries();
    //livetime
    // Long64_t nscalerD = ss->GetEntries();
    // for (int j = 0; j < nscalerD; j++){
    //   ss->GetEntry(j);
    //   current_bcmcut = bcm1chargecut/scaler1MHztimecut;
    //   current_nobcmcut = bcm1charge/scaler1MHztime;
    //   hptrig1rate->Fill(ptrig1rate);
    // }
    
    // charge= bcm1chargecut*0.001;
    // double bin_max_rate = hptrig1rate->GetMaximumBin();
    // rate = hptrig1rate->GetBinCenter(bin_max_rate);
    // PTRIG1_Rate = rate*0.001;
   
#include "scaler_branch.h"
    Long64_t scal_entries = ss->GetEntries();
#include "scaler_analysis.h"

    Int_t nscaler_reads_acc=0;
    for (int kk=0; kk<nentriesD;  kk++){//---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(kk);

      if (event_flag[nscaler_reads_acc]==1) {
	paero_cut = paero>3.0;
	hgcer_cut = hgcer>1.0;
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut = rf_pion > rfmin && rf_pion < rfmax;
	mod4_notpioncut =!mod4_pioncut;
	pcal_cut =  pcaletottrack < pcaletotmax ;// && pcalepr< eprmax ;

	Epi_cut_acc = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut_acc = Epi_cut_acc/dnu;//variable name is same between acc abd real, but histogram name is different
	Mx2_cut_acc=(protonmass + dnu - zhad_cut_acc*dnu) *  (protonmass + dnu - zhad_cut_acc*dnu) - abs(dpmiss)*abs(dpmiss);
	 


	
	hms_cut  =  hdelta> -8 && hdelta < 8  && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hcernpe>1.0 &&dW2>4 && Mx2_cut_acc > 1.6  ;//&& hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04;
	shms_cut =  pdelta >-10 && pdelta < 20   && phodstarttime == 1  && eventtype > 3 &&  pcal_cut && mod4_pioncut && paero_cut && pdipole ==1 ;//&& pxptar>-0.05&&pxptar<0.05&&pyptar>-0.04&&pyptar<0.04;
	pid_cut  = hms_cut && shms_cut;
       
      
	if (pid_cut){//Note this is not the accidental, cut see below for the accidental cut section.
	  hpbeta->Fill(pbeta);
	  hctime->Fill(ctime);
	}  
	 
      }
      
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;
    }//ctimepeak done 
    //cout<<"Step 1: calulating the max peak value of the ctime dist"<<endl;

    Double_t counts_betaa=hpbeta->GetEntries();
    Double_t counts_W2a=d_W2a->GetEntries();

    //cout<< "countscomp = " <<counts_betaa <<"    "<<  counts_W2a<<endl;
    
    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
    //cout<<"ctime peak is at = "<< max_value <<endl;
    //cout<<"Opening Run = "<<runs[r]<<"    "<<"ctime peak at = "<< max_value<<"   "<< "offsetrf =   "<<offsetrf<<"     "<<"Total Entries = "<<tt->GetEntries()<<endl;
    //cout<< "  "<<endl;


    
    //cout<<"Step 2: Now calculating accidental backgrounds"<<endl;
    Bool_t hgcer_cut1 ,paero_cut1 , mod4_pioncut1,  mod4_notpioncut1,   pcal_cut1,   hms_cut1,   shms_cut1, shms_cut2, pid_cut1, ctime_cut1, acc_cut1, acc_cut1hardcut,acc_cut_norf;

    Int_t nscaler_reads=0;

    
    for (int kk=0; kk<nentriesD;  kk++){//-----------------------------------------------------Main Evt Loop
      // for (int kk=0; kk<100;  kk++){//-----------------------------------------------------Main Evt Loop
      tt->GetEntry(kk);
      if (event_flag[nscaler_reads]==1) {
	////////Mx2 cut///////

	// d_W2_acccut->Fill(dW2);//
	// Epi_acccut = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	// zhad_acccut = Epi_acccut/dnu;//variable name is same between acc abd real, but histogram name is different
	// d_zhad_acccut->Fill(zhad_acccut);
	// Mx2a_acccut=(protonmass + dnu - zhad_acccut*dnu) *  (protonmass + dnu - zhad_acccut*dnu) - abs(dpmiss)*abs(dpmiss);
	 
	Epi_cut = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut = Epi_cut/dnu;//variable name is same between acc abd real, but histogram name is different
	Mx2_cut=(protonmass + dnu - zhad_cut*dnu) *  (protonmass + dnu - zhad_cut*dnu) - abs(dpmiss)*abs(dpmiss);
	 





	////////////////Mx2 cut/////heredone

	accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
	accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
	acc_cut1hardcut = (accR_cut || accL_cut);
	ctime_cut1 = ctime > max_value - ctmin && ctime < max_value + ctmax;


	paero_cut1 = paero>3.0;
	hgcer_cut =  hgcer>2.0;
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut1 = rf_pion > rfmin && rf_pion < rfmax;
	mod4_notpioncut1 =!mod4_pioncut;
	pcal_cut1 =  pcaletottrack < pcaletotmax;//  && pcalepr< eprmax ;	    //W2 cut is here





	//////////NO W2 Mx2 cutssssssss////////////

	
	hms_cut1  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hcernpe>1.0 &&dW2>4&&Mx2_cut>1.6 ;//&&  hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04  && dW2>4;//------>
	shms_cut1 =  pdelta >-10 && pdelta < 20   && phodstarttime == 1 && pdipole ==1 && eventtype > 3 ;//&& pxptar>-0.05&&pxptar<0.05&&pyptar>-0.04&&pyptar<0.04;//basic//------------>
	shms_cut2 =  pcal_cut1 && mod4_pioncut1 && paero_cut1;//main pi+/- pid
	basic_cut = hms_cut1 && shms_cut1;
	basic_cal_aero = hms_cut1 && shms_cut1 &&  pcal_cut1 && paero_cut1;//No RF
	pid_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && ctime_cut1;//-------------------all cut vs1
	acc_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && acc_cut1hardcut;//final accidental cut----------------------------------------->
	//acc cut when you doot have RF time
	acc_cut_norf = hms_cut1 && shms_cut1 && pcal_cut1 &&  paero_cut1  && acc_cut1hardcut;
 

	//////efficiencies==============================

       
	shms_tr_should_cut  = (phodgoodscinhit==1  && pcaletotnorm < 0.75  && phodstarttime==1 && eventtype > 3   &&  paero_cut1 )  ;  
	shms_tr_did_cut     = ( shms_tr_should_cut &&  pdcntrack >0 ) ;  

	 
	hms_tr_should_cut   = (hhodgoodscinhit==1  && hcaletotnorm > 0.75  && hhodstarttime==1   && eventtype > 3 && hcernpe > 1.0);
	hms_tr_did_cut      = ( hms_tr_should_cut && hdcntrack >0) ;  



	//cal eff
	//  cal_eff_hms_shms_base_cut = hdelta> -10 && hdelta < 10 &&  hbeta> 0.8 &&  hbeta <1.2  && hhodstarttime ==1 && hdipole==1 && hcernpe>1.5 && pdelta > -10 && pdelta < 20   && pbeta <1.5 && phodstarttime == 1 && pdipole ==1 && eventtype > 3 && ctime_cut1 && paero_cut1 &&  mod4_pioncut1 && hgcer >1;//all basic cuts

	//play below
	cal_eff_hms_shms_base_cut = hdelta> -8 && hdelta < 8&&    hhodstarttime ==1 && hdipole==1 &&  eventtype > 3 && pdelta > -10 && pdelta < 20 && phodstarttime == 1 && pdipole ==1 &&   ctime_cut1 && paero_cut1 &&   mod4_pioncut1 ;//&& hgcer >1;

      
																				       
	hms_cal_should_cut       =   cal_eff_hms_shms_base_cut &&  pcaletottrack < 0.75 && pcalepr< 0.15 &&hcernpe>1.0;//base + shms cuts 
	hms_cal_did_cut          =   hms_cal_should_cut && hcaletottrack > 0.8;//should + hcal cuts


	shms_cal_should_cut     =   cal_eff_hms_shms_base_cut  && hcaletottrack > 0.8 ;//base + hms cuts
	shms_cal_did_cut        =   shms_cal_should_cut &&  pcaletottrack < 0.75 && pcalepr< 0.15;// should + pcal_cuts

      

      
	//livetime only========================================================
	if (edtmtdctimeraw > 0){
	  hedtm_trig_acc_all->Fill(edtmtdctimeraw);	
	}
      
	//tracking only
	if(hms_tr_did_cut){
	  hcal_tr_did->Fill(hcaletotnorm);
	}
	if(hms_tr_should_cut){
	  hcal_tr_should->Fill(hcaletotnorm);
	}

	if(shms_tr_did_cut){
	  pcal_tr_did->Fill(pcaletotnorm);
	}
	if(shms_tr_should_cut){
	  pcal_tr_should->Fill(pcaletotnorm);
	}
	//accidental only/////////------------------------------------------------------------------------->ACCIDENTALS ONLY------------------------------start
	if(acc_cut1){

	 
	  
	  // if(Mx2a_acccut>2.4){//========================Mx2a cut
	  hctimeacc->Fill(ctime);
	  d_xbja->Fill(dxbj);
	  Epi = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	  zhad = Epi/dnu;//variable name is same between acc abd real, but histogram name is different
	  d_zhada->Fill(zhad);
	  d_Q2a->Fill(dQ2);
	  d_nua->Fill(dnu);
	  d_omegaa->Fill(domega);
	  d_W2a->Fill(dW2);
	  d_Wprime2a->Fill(Mx2_cut);
	  d_pmissa->Fill(dpmiss);
	  d_emissa->Fill(demiss);

	 
	  //}//=========Mx2a cut
	}	//accidental only   Done/////////------------------------------------------------------------------------->ACCIDENTALS ONLY----------------done

	
	//basic cut = hms all + pbeta delta
	if(basic_cut){
	  ctime_vs_rfb->Fill(rf_pion, ctime);
	  shwr_vs_rfb->Fill(rf_pion, pcaletottrack - pcalepr);//b = basic
	  epr_vs_rfb->Fill(rf_pion, pcalepr);
	  etot_vs_rfb->Fill(rf_pion,pcaletottrack);
	  aero_vs_rfb->Fill(rf_pion, paero); 
	  beta_vs_rfb->Fill(rf_pion, pbeta);
	  aero_vs_ctb->Fill(ctime, paero);
	  hRF->Fill(rf_pion);
	}
	if(basic_cal_aero){
	  ctime_vs_rf_calaero->Fill(rf_pion, ctime);//
	}
	if(basic_cal_aero && ctime_cut1){
	  shwr_vs_rf_calctaero->Fill(rf_pion, pcaletottrack - pcalepr);
	  epr_vs_rf_calctaero->Fill(rf_pion, pcalepr);
	  etot_vs_rf_calctaero->Fill(rf_pion,pcaletottrack);
	  aero_vs_rf_calctaero->Fill(rf_pion, paero); 
	  beta_vs_rf_calctaero->Fill(rf_pion, pbeta);
	  aero_vs_ct_calctaero->Fill(ctime, paero);
	  //	if(hgcer_cut){
	  hRF_pid->Fill(rf_pion);//}
	}

      
	//good pid only
	if (pid_cut1){//--------------------------------------all pi+/- pid plots goes here//Mx2>2.4 and W2>4 are already defined as a base cut in pid_cut1
	  //Epi_pidcut = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	  //zhad_pidcut = Epi_pidcut/dnu;
	  //Mx2_pidcut = (protonmass + dnu - zhad_pidcut*dnu) *  (protonmass + dnu - zhad_pidcut*dnu) - abs(dpmiss)*abs(dpmiss);

	  // if(Mx2_pidcut>2.4){//======================Mx2 cut in data start

	  hpbetact->Fill(pbeta);
	  hctimect->Fill(ctime);
	
	  ctime_vs_rf->Fill(rf_pion, ctime);
	  shwr_vs_rf->Fill(rf_pion, pcaletottrack - pcalepr);
	  epr_vs_rf->Fill(rf_pion, pcalepr);
	  etot_vs_rf->Fill(rf_pion,pcaletottrack);
	  aero_vs_rf->Fill(rf_pion, paero); 
	  beta_vs_rf->Fill(rf_pion, pbeta);
	  aero_vs_ct->Fill(ctime, paero);
	  d_xbj->Fill(dxbj);
	  Epi = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	  zhad = Epi/dnu;
	  d_zhad->Fill(zhad);
	  d_Q2->Fill(dQ2);
	  d_nu->Fill(dnu);
	  d_omega->Fill(domega);
	  d_W2->Fill(dW2);
	  // Mx2=(protonmass + dnu - zhad*dnu) *  (protonmass + dnu - zhad*dnu) - abs(dpmiss)*abs(dpmiss);
	  d_Wprime2->Fill(Mx2_cut);
	  d_pmiss->Fill(dpmiss);
	  d_emiss->Fill(demiss);
	 
	  // }////======================Mx2 cut in data end
	}
	//for aero eff by fit



	if(hms_cut1 && shms_cut1 && pcal_cut1 && mod4_pioncut1 && acc_cut1 && hgcer > 2){//accidental without aerogel to find aero eff from fit
	  aero_1da->Fill(paero);//accidental aeroNpe
	}
	if(hms_cut1 && shms_cut1 &&  pcal_cut1 && mod4_pioncut1 && ctime_cut1  && hgcer >2){//-------------------all cut vs1 but not aerogel cut to find aero eff from fit in aeronpe cut
	  aero_1d->Fill(paero);//---------------------------------------->find aero efficiency
	}
	//for aero eff by fit done
	//For RF time Cut Efficiency: or kaon contamination//
	// if(acc_cut_norf && paero > 4 && zhad_cut>0.50 && zhad_cut<0.70){//accidental in RF
	//   rf_1da->Fill(rf_pion);//rf cut for acc for whole run
	// }
	// if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4 && zhad_cut>0.50 && zhad_cut<0.70  ){
	//   rf_1d->Fill(rf_pion);//rf cut for coin for whole run
	// }


	////Now divide 1 run into 4 z bins by diferent z cuts here, and 4 acc hist & 4 coin hist,  ==========================Jan 22 from here
	// if(acc_cut_norf && paero > 4 && hgcer > 3  && zhad_cut < 0.55 ){ rf_1da_1->Fill(rf_pion);}//no lower limit in z
	// if(acc_cut_norf && paero > 4 && hgcer > 3  && zhad_cut>0.55 && zhad_cut <0.60 ){ rf_1da_2->Fill(rf_pion);}
	// if(acc_cut_norf && paero > 4 && hgcer > 3  && zhad_cut>0.60 && zhad_cut <0.65 ){ rf_1da_3->Fill(rf_pion);}
	// if(acc_cut_norf && paero > 4 && hgcer > 3  && zhad_cut>0.65  ){ rf_1da_4->Fill(rf_pion);}//no upper limit in z
      	// if(acc_cut_norf && paero > 4 && hgcer > 3   ){ rf_1da->Fill(rf_pion);}//whole run1 z//no z cut 
	// if(acc_cut_norf && paero > 4 && hgcer > 3  && mod4_pioncut1){ zhad_1da->Fill(zhad_cut);}

	
	// if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4 && hgcer > 3   && zhad_cut <0.55  ){ rf_1d_1->Fill(rf_pion);}//no lower limit in z
	// if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4 && hgcer > 3   && zhad_cut>0.55 &&zhad_cut <0.60  ){ rf_1d_2->Fill(rf_pion);}
	// if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4 && hgcer > 3   && zhad_cut>0.60 &&zhad_cut <0.65  ){ rf_1d_3->Fill(rf_pion);}
	// if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4 && hgcer > 3   && zhad_cut>0.65  ){ rf_1d_4->Fill(rf_pion);}//no upper limitin z
	// if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4 && hgcer > 3    ){ rf_1d->Fill(rf_pion);}//whole run1 z = all z
	// if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4 && hgcer > 3  && mod4_pioncut1){ zhad_1d->Fill(zhad_cut);}//whole run1 z

	if(acc_cut_norf && paero > 4    && zhad_cut < 0.55 ){ rf_1da_1->Fill(rf_pion);}//no lower limit in z
	if(acc_cut_norf && paero > 4    && zhad_cut>0.55 && zhad_cut <0.60 ){ rf_1da_2->Fill(rf_pion);}
	if(acc_cut_norf && paero > 4    && zhad_cut>0.60 && zhad_cut <0.65 ){ rf_1da_3->Fill(rf_pion);}
	if(acc_cut_norf && paero > 4    && zhad_cut>0.65  ){ rf_1da_4->Fill(rf_pion);}//no upper limit in z
      	if(acc_cut_norf && paero > 4     ){ rf_1da->Fill(rf_pion);}//whole run1 z//no z cut 
	if(acc_cut_norf && paero > 4    && mod4_pioncut1){ zhad_1da->Fill(zhad_cut);}

	
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4     && zhad_cut <0.55  ){ rf_1d_1->Fill(rf_pion);}//no lower limit in z
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4     && zhad_cut>0.55 &&zhad_cut <0.60  ){ rf_1d_2->Fill(rf_pion);}
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4     && zhad_cut>0.60 &&zhad_cut <0.65  ){ rf_1d_3->Fill(rf_pion);}
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4     && zhad_cut>0.65  ){ rf_1d_4->Fill(rf_pion);}//no upper limitin z
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4      ){ rf_1d->Fill(rf_pion);}//whole run1 z = all z
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4    && mod4_pioncut1){ zhad_1d->Fill(zhad_cut);}//whole run1 z



	
	//////////////////////////////////////////////////////////////===========================================done jan22	
	////////
	
	//done kaon contamination
	if(hms_cal_did_cut){
	  hcal_did->Fill(hcaletottrack);
	}
	if(hms_cal_should_cut){
	  hcal_should->Fill(hcaletottrack);
	}	
     
	if(shms_cal_did_cut){
	  pcal_did->Fill(pcaletottrack);
	}
	if(shms_cal_should_cut){
	  pcal_should->Fill(pcaletottrack);
	}	 
      }	//entries data scal
      if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;

    }//entries

    //testing
   
    //testing done
    //accdental sub copied 
    TH1D *  d_xbjac = (TH1D*)d_xbja->Clone();
    TH1D *  d_zhadac = (TH1D*)d_zhada->Clone();
    TH1D *  d_Q2ac = (TH1D*)d_Q2a->Clone();
    TH1D *  d_nuac = (TH1D*)d_nua->Clone();
    TH1D *  d_omegaac = (TH1D*)d_omegaa->Clone();
    TH1D *  d_W2ac = (TH1D*)d_W2a->Clone();
    TH1D *  d_Wprime2ac = (TH1D*)d_Wprime2a->Clone();
    TH1D *  d_pmissac = (TH1D*)d_pmissa->Clone();
    TH1D *  d_emissac = (TH1D*)d_emissa->Clone();

    //////////from here working to find aero efficiency from fit
    TH1D *  aero_1dac = (TH1D*)aero_1da->Clone();//aero npe 
    if (aero_1d->GetSumw2N() == 0) aero_1d->Sumw2(kTRUE);
    if (aero_1da->GetSumw2N() == 0) aero_1da->Sumw2(kTRUE);
    TH1D *  rf_1dac = (TH1D*)rf_1da->Clone();//rf kaon cont

    TCanvas * ae = new TCanvas("ae","aerogel NpeSum", 1000, 800);
    ae->Divide(4,2);
    ae->cd(1);gPad->SetGridx();
    aero_1d->Draw("hist");//D2 run 

    ae->cd(2);gPad->SetGridx();
    aero_1da->Draw("hist");// D2 run acc

   
    ae->cd(3);gPad->SetGridx();//just copy of aero_1da
    aero_1dac->Draw("hist");// D2 acc copy 
    aero_1dac->Scale((ctmin+ctmax)/16.0);

    aero_1dc->Add(aero_1d,aero_1dac,1.0,-1.0);//1dc = clean//
    if (aero_1dc->GetSumw2N() == 0) aero_1dc->Sumw2(kTRUE);//accidental subtracted
    
    ae->cd(4);gPad->SetGridx();
    aero_1dc->Draw("hist");
    //rf kaon 
    ae->cd(5);gPad->SetGridx();
    rf_1d->Draw("hist");//D2 run 

    ae->cd(6);gPad->SetGridx();
    rf_1da->Draw("hist");// D2 run acc

   
    ae->cd(7);gPad->SetGridx();;//just copy of rf_1da
    rf_1dac->Draw("hist");// D2 acc copy 
    rf_1dac->Scale((ctmin+ctmax)/16.0);

    rf_1dc->Add(rf_1d,rf_1dac,1.0,-1.0);//1dc = clean//
    if (rf_1dc->GetSumw2N() == 0) rf_1dc->Sumw2(kTRUE);//accidental subtracted
    
    ae->cd(8);gPad->SetGridx();
    rf_1dc->Draw("hist");
    //counts in clean aero 
    cout<<"==================================================================================="<<endl;
    cout<<"aero acc integral and counts = "<< aero_1dc->Integral()<<"   "<<aero_1dc->GetEntries()<<endl;
    cout<<"RF acc integral and counts   = "<< rf_1dc->Integral()  <<"   "<<rf_1dc->GetEntries()<<endl;

    cout<<"aero acc integral and counts by FindBin = "<< aero_1dc->Integral(aero_1dc->FindBin(0),aero_1dc->FindBin(50))<<"   "<<aero_1dc->GetEntries()<<endl;
    cout<<"RF acc integral and counts by FindBin  = "<< rf_1dc->Integral(rf_1dc->FindBin(0),rf_1dc->FindBin(4))  <<"   "<<rf_1dc->GetEntries()<<endl;
    cout<<"==================================================================================="<<endl;


    
    ae->SaveAs(Form("pdf/aero_rf_1d_%d.pdf", runs[r]));
    /////////////aero eff done/////////////
    





    /////////////////////Jan 22 start for z bins variation of RF cut eff

    //4zbins jan22
    TH1D *  rf_1dac_1 = (TH1D*)rf_1da_1->Clone();
    TH1D *  rf_1dac_2 = (TH1D*)rf_1da_2->Clone();
    TH1D *  rf_1dac_3 = (TH1D*)rf_1da_3->Clone();
    TH1D *  rf_1dac_4 = (TH1D*)rf_1da_4->Clone();
    TH1D *  zhad_1dac = (TH1D*)zhad_1da->Clone();

    rf_1dac_1->Scale((ctmin+ctmax)/16.0);
    rf_1dac_2->Scale((ctmin+ctmax)/16.0);
    rf_1dac_3->Scale((ctmin+ctmax)/16.0);
    rf_1dac_4->Scale((ctmin+ctmax)/16.0);
    zhad_1dac->Scale((ctmin+ctmax)/16.0);

    rf_1dc_1->Add(rf_1d_1,rf_1dac_1,1.0,-1.0);//1dc = clean//
    if (rf_1dc_1->GetSumw2N() == 0) rf_1dc_1->Sumw2(kTRUE);//accidental subtracted

    rf_1dc_2->Add(rf_1d_2,rf_1dac_2,1.0,-1.0);
    if (rf_1dc_2->GetSumw2N() == 0) rf_1dc_2->Sumw2(kTRUE);

    rf_1dc_3->Add(rf_1d_3,rf_1dac_3,1.0,-1.0);
    if (rf_1dc_3->GetSumw2N() == 0) rf_1dc_3->Sumw2(true);

    rf_1dc_4->Add(rf_1d_4,rf_1dac_4,1.0,-1.0);
    if (rf_1dc_4->GetSumw2N() == 0) rf_1dc_4->Sumw2(kTRUE);

    zhad_1dc->Add(zhad_1d,zhad_1dac,1.0,-1.0);
    if (zhad_1dc->GetSumw2N() == 0) zhad_1dc->Sumw2(kTRUE);

    TCanvas * zbin = new TCanvas("zbin","zbin", 1000, 800);
    zbin->Divide(3,2);
    zbin->cd(1);
    rf_1d_1->Draw("hist ");
    rf_1dc_1->Draw("hist same ");
    rf_1dc_1->SetLineWidth(2);
    rf_1d_1->SetLineColor(kGreen);
    rf_1dac_1->Draw("hist same");
    rf_1dac_1->SetLineColor(kRed);
    rf_1d_1->GetXaxis()->SetTitle(Form("RF Time %d z(< 0.55)",runs[r]));

    zbin->cd(2);
    rf_1d_2->Draw("hist ");
    rf_1dc_2->Draw("hist same");
    rf_1dc_2->SetLineWidth(2);
    rf_1d_2->SetLineColor(kGreen);
    rf_1dac_2->Draw("hist same");
    rf_1dac_2->SetLineColor(kRed);
    rf_1d_2->GetXaxis()->SetTitle(Form("RF Time %d z(0.55-0.60)",runs[r]));

 
    zbin->cd(3);
    rf_1d_3->Draw("hist ");
    rf_1dc_3->Draw("hist same");
    rf_1dc_3->SetLineWidth(2);
    rf_1d_3->SetLineColor(kGreen);
    rf_1dac_3->Draw("hist same");
    rf_1dac_3->SetLineColor(kRed);
    rf_1d_3->GetXaxis()->SetTitle(Form("RF Time %d z(0.60-0.65)",runs[r]));


    zbin->cd(4);
    rf_1d_4->Draw("hist ");
    rf_1dc_4->Draw("hist same ");
    rf_1dc_4->SetLineWidth(2);
    rf_1d_4->SetLineColor(kGreen);
    rf_1dac_4->Draw("hist same");
    rf_1dac_4->SetLineColor(kRed);
    rf_1d_4->GetXaxis()->SetTitle(Form("RF Time %d z(> 0.65)",runs[r]));


    zbin->cd(5);
    rf_1d->Draw("hist ");
    rf_1dc->Draw("hist same ");
    rf_1dc->SetLineWidth(2);
    rf_1d->SetLineColor(kGreen);
    rf_1dac->Draw("hist same");
    rf_1dac->SetLineColor(kRed);
    rf_1d->GetXaxis()->SetTitle(Form("RF Time  z = 0.6 %d ",runs[r]));

    zbin->cd(6);
    zhad_1d->Draw("hist ");
    zhad_1dc->Draw("hist same ");
    zhad_1dc->SetLineWidth(2);
    zhad_1d->SetLineColor(kGreen);
    zhad_1dac->Draw("hist same");
    zhad_1dac->SetLineColor(kRed);
    zhad_1d->GetXaxis()->SetTitle(Form("Z_hadron z = 0.6 %d ",runs[r]));


    rf_1dc_1->Write();
    rf_1dc_2->Write();
    rf_1dc_3->Write();
    rf_1dc_4->Write();
    rf_1dc->Write();
    zhad_1d->Write();

    zbin->SaveAs(Form("pdf_zbin/fourz_bins_%d.pdf",runs[r]));










    
    /////////////////////Jan 22 done for z bins variation of RF cut eff
    
   
    TCanvas * ac = new TCanvas ("ac", "ac", 1000, 800);
    ac->Divide(3,3);
    ac->cd(1);
    if (d_xbj->GetSumw2N() == 0) d_xbj->Sumw2(kTRUE);
    if (d_xbja->GetSumw2N() == 0) d_xbja->Sumw2(kTRUE);
    if (d_xbjac->GetSumw2N() == 0) d_xbjac->Sumw2(kTRUE);

    d_xbj->Draw("e, p1");
    d_xbj->SetMarkerStyle(8);
    d_xbj->SetMarkerColor(kBlue);
    d_xbjac->Scale((ctmax+ctmin)/16.0);//took 1/4 when we took the accidentals for 4ns ctpeak
    d_xbjac->Draw("e, p1 sames");
    d_xbjac->SetMarkerStyle(8);
    Double_t data_ent = d_xbj->GetEntries();
    Double_t acc_ent4 = d_xbja->GetEntries();
    Double_t acc_ent = d_xbjac->GetEntries();

    //cout<<"events ="<< runs[r]<< "   "<<data_ent<<"    "<< acc_ent/4.0<<endl;
    
    ac->cd(2);
    if (d_zhad->GetSumw2N() == 0) d_zhad->Sumw2(kTRUE);
    if (d_zhada->GetSumw2N() == 0) d_zhada->Sumw2(kTRUE);
    if (d_zhadac->GetSumw2N() == 0) d_zhadac->Sumw2(kTRUE);

    d_zhad->Draw("e, p1");
    d_zhad->SetMarkerStyle(8);
    d_zhad->SetMarkerColor(kBlue);
    d_zhadac->Scale((ctmin+ctmax)/16);
    d_zhadac->Draw("e, p1 sames");
    d_zhadac->SetMarkerStyle(8);

    ac->cd(3);
    if (d_Q2->GetSumw2N() == 0) d_Q2->Sumw2(kTRUE);
    if (d_Q2a->GetSumw2N() == 0) d_Q2a->Sumw2(kTRUE);
    if (d_Q2ac->GetSumw2N() == 0) d_Q2ac->Sumw2(kTRUE);

    d_Q2->Draw("e, p1");
    d_Q2->SetMarkerStyle(8);
    d_Q2->SetMarkerColor(kBlue);

    d_Q2ac->Scale((ctmin+ctmax)/16.0);
    d_Q2ac->Draw("e, p1 sames");
    d_Q2ac->SetMarkerStyle(8);

    ac->cd(4);
    if (d_nu->GetSumw2N() == 0) d_nu->Sumw2(kTRUE);
    if (d_nua->GetSumw2N() == 0) d_nua->Sumw2(kTRUE);
    if (d_nuac->GetSumw2N() == 0) d_nuac->Sumw2(kTRUE);

    d_nu->Draw("e, p1");
    d_nu->SetMarkerStyle(8);
    d_nu->SetMarkerColor(kBlue);

    d_nuac->Scale((ctmin+ctmax)/16.0);
    d_nuac->Draw("e, p1 sames ");
    d_nuac->SetMarkerStyle(8);

    ac->cd(5);
    if (d_omega->GetSumw2N() == 0) d_omega->Sumw2(kTRUE);
    if (d_omegaa->GetSumw2N() == 0) d_omegaa->Sumw2(kTRUE);
    if (d_omegaac->GetSumw2N() == 0) d_omegaac->Sumw2(kTRUE);

    d_omega->Draw("e, p1");
    d_omega->SetMarkerStyle(8);
    d_omega->SetMarkerColor(kBlue);

    d_omegaac->Scale((ctmin+ctmax)/16.0);
    d_omegaac->Draw("e, p1 sames ");
    d_omegaac->SetMarkerStyle(8);

    
    ac->cd(6);
    if (d_W2->GetSumw2N() == 0) d_W2->Sumw2(kTRUE);
    if (d_W2a->GetSumw2N() == 0) d_W2a->Sumw2(kTRUE);
    if (d_W2ac->GetSumw2N() == 0) d_W2ac->Sumw2(kTRUE);

    d_W2->Draw("e, p1");
    d_W2->SetMarkerStyle(8);
    d_W2->SetMarkerColor(kBlue);

    d_W2ac->Scale((ctmin+ctmax)/16.0);
    d_W2ac->Draw("e, p1 sames");
    d_W2ac->SetMarkerStyle(8);

    ac->cd(7);
    if (d_Wprime2->GetSumw2N() == 0) d_Wprime2->Sumw2(kTRUE);
    if (d_Wprime2a->GetSumw2N() == 0) d_Wprime2a->Sumw2(kTRUE);
    if (d_Wprime2ac->GetSumw2N() == 0) d_Wprime2ac->Sumw2(kTRUE);

    d_Wprime2->Draw("e, p1");
    d_Wprime2->SetMarkerStyle(8);
    d_Wprime2->SetMarkerColor(kBlue);

    d_Wprime2ac->Scale((ctmin+ctmax)/16.0);
    d_Wprime2ac->Draw("e, p1 sames");
    d_Wprime2ac->SetMarkerStyle(8);

    ac->cd(8);
    if (d_pmiss->GetSumw2N() == 0) d_pmiss->Sumw2(kTRUE);
    if (d_pmissa->GetSumw2N() == 0) d_pmissa->Sumw2(kTRUE);
    if (d_pmissac->GetSumw2N() == 0) d_pmissac->Sumw2(kTRUE);

    d_pmiss->Draw("e, p1");
    d_pmiss->SetMarkerStyle(8);
    d_pmiss->SetMarkerColor(kBlue);

    d_pmissac->Scale((ctmin+ctmax)/16.0);
    d_pmissac->Draw("e, p1 sames");
    d_pmissac->SetMarkerStyle(8);

    
    ac->cd(9);
    if (d_emiss->GetSumw2N() == 0) d_emiss->Sumw2(kTRUE);
    if (d_emissa->GetSumw2N() == 0) d_emissa->Sumw2(kTRUE);
    if (d_emissac->GetSumw2N() == 0) d_emissac->Sumw2(kTRUE);

    d_emiss->Draw("e, p1");
    d_emiss->SetMarkerStyle(8);
    d_emiss->SetMarkerColor(kBlue);
    d_emissac->Scale((ctmin+ctmax)/16.0);
    d_emissac->Draw("e, p1 sames");
    d_emissac->SetMarkerStyle(8);

    ac->SaveAs(Form("pdf_new_W2/pid_and_accidental_%d.pdf",runs[r]));
    //accidental done 
    
    //Accidental Subtraction here========================================>
    d_xbj1->Add(d_xbj,d_xbjac,1.0,-1.0);
    d_zhad1->Add(d_zhad,d_zhadac,1.0,-1.0);
    d_Q21->Add(d_Q2,d_Q2ac,1.0,-1.0);
    d_nu1->Add(d_nu,d_nuac,1.0,-1.0);
    d_omega1->Add(d_omega,d_omegaac,1.0,-1.0);
    d_W21->Add(d_W2,d_W2ac,1.0,-1.0);
    d_Wprime21->Add(d_Wprime2,d_Wprime2ac,1.0,-1.0);
    d_pmiss1->Add(d_pmiss,d_pmissac,1.0,-1.0);
    d_emiss1->Add(d_emiss,d_emissac,1.0,-1.0);

    Double_t final_entries = d_xbj1->GetEntries();
    Double_t final_integral = d_xbj1->Integral();

    Double_t before = d_xbj->Integral();
    double acccc= d_xbjac->Integral();

    cout<<runs[r]<<"   "<<"int = "<< before<<"    "<<acccc<< "    "<<final_integral<<endl;
    cout<<runs[r]<<"   "<<"ent = "<< "    "<<final_entries<<endl;

    //   cout<<"Run = "<<runs[r]<<"  "<<"Total = "<<tt->GetEntries()<< "   "<<"bef_acc = "<< data_ent<<"    "<<"acc = "<<  acc_ent*(ctmin+ctmax)/16.0 <<"   "<<"final = "<<final_entries<< endl;
    cout<< "  "<<endl;

    
    
    if (d_xbj1->GetSumw2N() == 0) d_xbj1->Sumw2(kTRUE);
    if (d_zhad1->GetSumw2N() == 0) d_zhad1->Sumw2(kTRUE);
    if (d_Q21->GetSumw2N() == 0) d_Q21->Sumw2(kTRUE);
    if (d_nu1->GetSumw2N() == 0) d_nu1->Sumw2(kTRUE);
    if (d_omega1->GetSumw2N() == 0) d_omega1->Sumw2(kTRUE);
    if (d_W21->GetSumw2N() == 0) d_W21->Sumw2(kTRUE);
    if (d_Wprime21->GetSumw2N() == 0) d_Wprime21->Sumw2(kTRUE);
    if (d_pmiss1->GetSumw2N() == 0) d_pmiss1->Sumw2(kTRUE);
    if (d_emiss1->GetSumw2N() == 0) d_emiss1->Sumw2(kTRUE);

 
    
    ///plot accidental subtracracted hist/////////////////////////

    TCanvas * clean = new TCanvas ("clean", "clean", 1000, 800);
    clean->Divide(3,3);
    clean->cd(1);
    d_xbj1->Draw("e, p1");
    d_xbj1->SetMarkerStyle(8);
    d_xbj1->SetMarkerColor(kBlue);

    clean->cd(2);
    d_zhad1->Draw("e, p1");
    d_zhad1->SetMarkerStyle(8);
    d_zhad1->SetMarkerColor(kBlue);

    
    clean->cd(3);
    d_Q21->Draw("e, p1");
    d_Q21->SetMarkerStyle(8);
    d_Q21->SetMarkerColor(kBlue);
      
    clean->cd(4);
    d_nu1->Draw("e, p1");
    d_nu1->SetMarkerStyle(8);
    d_nu1->SetMarkerColor(kBlue);
    
    clean->cd(5);
    d_omega1->Draw("e, p1");
    d_omega1->SetMarkerStyle(8);
    d_omega1->SetMarkerColor(kBlue);
    
    clean->cd(6);
    d_W21->Draw("e, p1");
    d_W21->SetMarkerStyle(8);
    d_W21->SetMarkerColor(kBlue);
    
    clean->cd(7);
    d_Wprime21->Draw("e, p1");
    d_Wprime21->SetMarkerStyle(8);
    d_Wprime21->SetMarkerColor(kBlue);

 
    clean->cd(8);
    d_pmiss1->Draw("e, p1");
    d_pmiss1->SetMarkerStyle(8);
    d_pmiss1->SetMarkerColor(kBlue);
    
    
    clean->cd(9);
    d_emiss1->Draw("e, p1");
    d_emiss1->SetMarkerStyle(8);
    d_emiss1->SetMarkerColor(kBlue);
    

    
    clean->SaveAs(Form("pdf_new_W2/clean_hist_data_before_chargenorm_%d.pdf",runs[r]));
    ///////////////clone hist to normalize by charge/////////////

    TH1D *  d_xbjn = (TH1D*)d_xbj1->Clone();//n = chage Normalized, efficiency corrcted
    TH1D *  d_zhadn = (TH1D*)d_zhad1->Clone();
    TH1D *  d_Q2n = (TH1D*)d_Q21->Clone();
    TH1D *  d_nun = (TH1D*)d_nu1->Clone();
    TH1D *  d_omegan = (TH1D*)d_omega1->Clone();
    TH1D *  d_W2n = (TH1D*)d_W21->Clone();
    TH1D *  d_Wprime2n = (TH1D*)d_Wprime21->Clone();
    TH1D *  d_pmissn = (TH1D*)d_pmiss1->Clone();
    TH1D *  d_emissn = (TH1D*)d_emiss1->Clone();

    if (d_zhadn->GetSumw2N() == 0) d_zhadn->Sumw2(kTRUE);
    if (d_Q2n->GetSumw2N() == 0) d_Q2n->Sumw2(kTRUE);
    if (d_nun->GetSumw2N() == 0) d_nun->Sumw2(kTRUE);
    if (d_omegan->GetSumw2N() == 0) d_omegan->Sumw2(kTRUE);
    if (d_W2n->GetSumw2N() == 0) d_W2n->Sumw2(kTRUE);
    if (d_Wprime2n->GetSumw2N() == 0) d_Wprime2n->Sumw2(kTRUE);
    if (d_pmissn->GetSumw2N() == 0) d_pmissn->Sumw2(kTRUE);
    if (d_emissn->GetSumw2N() == 0) d_emissn->Sumw2(kTRUE);


    /////////Define a factor which is f_qelt = charge * LT * HMS TR * SHMS TR These has to define
    ////at the bottom of this page /////////
    
    ///  Double_t f_qelt = charge_sum_cut * LT * tr_eff_hms * tr_eff_shms;
    /////cout << "Run: "<< runs[r]<<"   "<<f_qelt = data Normfac <<f_qelt<<endl;
    
    ////////////////////////////Accidenal done////////////////////
    
    double hcal_did_counts    = hcal_did->GetEntries();
    double hcal_should_counts = hcal_should->GetEntries();
    double hcal_eff = hcal_did_counts/hcal_should_counts;
    double hcal_eff_err = (1/hcal_should_counts) * sqrt(hcal_did_counts * (1-hcal_did_counts/hcal_should_counts));

    
    double pcal_did_counts    = pcal_did->GetEntries();
    double pcal_should_counts = pcal_should->GetEntries();
    double pcal_eff = pcal_did_counts/pcal_should_counts;
    double pcal_eff_err = (1/pcal_should_counts) * sqrt(pcal_did_counts * (1-pcal_did_counts/pcal_should_counts));

    // cout<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<pcal_did_counts<<        "   " <<pcal_should_counts << "   "<< pcal_eff << "   "<<pcal_eff_err<<endl;

     
    double did_hms = hcal_tr_did->GetEntries();
    double should_hms = hcal_tr_should->GetEntries();
    double tr_eff_hms = did_hms/should_hms;
    double tr_eff_hms_err = (1/should_hms) * sqrt(did_hms*(1-did_hms/should_hms));

    
    double did_shms = pcal_tr_did->GetEntries();
    double should_shms = pcal_tr_should->GetEntries();
    double tr_eff_shms = did_shms/should_shms;
    double tr_eff_shms_err = (1/should_shms) * sqrt(did_shms*(1-did_shms/should_shms));
    Double_t current_bcmcut  = charge_sum_cut/tot_scal_cut_time;
    Double_t current_nobcmcut  = charge_sum_cut/tot_scal_cut_time;//==============================================================>Please see it..........just to run script


    //cout<< runs[r]<< " "<<"hdid =  "<<did_hms<<"    "<<"hshould =  " <<should_hms<<"    "<< "htreff =  "   <<tr_eff_hms<<"    "<<"htr_err =  " <<tr_eff_hms_err<< endl;
    //cout<< runs[r]<< " "<<"pdid =  "<<did_shms<<"    "<<"pshould =  " <<should_shms<<"    "<< "ptreff =  "   <<tr_eff_shms<<"    "<<"ptr_err =  " <<tr_eff_shms_err<< endl;

    double entries_pid = hctimect->GetEntries();
    double entries_acc1 = hctimeacc->GetEntries();
    double entries_acc = entries_acc1 * (ctmin+ctmax)/16.;//if ctmin+ctmax = 4ns, then ctmin_ctmax = 1/4, so for 3 ns it will be 16/3

    double counts = entries_pid - entries_acc;
    //cout<< " final good counts in the Run "<< runs[r]<< "  = "<< entries_pid << " - "<< entries_acc << " * 1/4  = " << counts <<endl;  
    
    //livetime
    Double_t nEDTM = 	hedtm_trig_acc_all->Integral();

    // double f_curr  = current_nobcmcut/ current_nobcmcut;//==========================================================================Pleae see it=========>JUST FOR FUN-------------------->
    double pedtmtrigacc_all = hedtm_trig_acc_all->GetEntries();
    double rmeas = pedtmtrigacc_all / tot_scal_cut_EDTM ;
    // double LT = (rmeas - ( 1.0 - f_curr ))/ f_curr;===========================================>commented
    double LT = rmeas;
    Double_t LT_err = sqrt((1-LT) *  LT/tot_scal_cut_EDTM);

    // double LT_err= LT * sqrt(1./pedtmtrigacc_all + 1./pedtmscaler);
    //cout<<"LT for "<< runs[r] <<"\t"<<PTRIG1_Rate<<"\t"<< current_bcmcut<<"\t" <<pedtmtrigacc_all<<"\t"<<pedtmscaler<<"\t"<<f_curr<<"\t"<<LT<<"\t"<<LT_err<<endl;
    //yield
   
    //cout<< "yield for "<<runs[r]<< " : " << PTRIG1_Rate <<"   "<< current_bcmcut<< "   "<<charge_sum_cut <<"   "<< yield <<"   "<<yield_err<< endl;
    
    


    double yield_bare = counts/(charge_sum_cut/1000.);
    double yield_bare_err = yield_bare * sqrt(1/counts);

    double yield = counts/(charge_sum_cut/1000. * tr_eff_hms * tr_eff_shms * hcal_eff * pcal_eff * LT );//livetime is removed for now
    double yield_err = yield * sqrt(1/counts);

    double yield_lttr = counts/(charge_sum_cut/1000. * tr_eff_hms * tr_eff_shms  * LT );//livetime is removed for now
    double yield_lttr_err = yield_lttr * sqrt(1/counts);

    //cout<<"counts = "<< entries_pid <<"    "<<entries_acc<<endl;
    //cout<<"yield = "<<runs[r]<<"   "<<yield_lttr<<"    "<<yield_lttr_err<<endl;
    //cout<<"cur, charge , Rate= "<<runs[r]<<"   "<<current_bcmcut<<"    "<<charge_sum_cut/1000.<<"    "<<PTRIG1_Rate<< endl;
    //cout<<"hms tr = "<<runs[r]<<"   "<<tr_eff_hms<<   "   " <<tr_eff_hms_err << endl;
    //cout<<"shms tr = "<<runs[r]<<"   "<<tr_eff_shms<<   "   " <<tr_eff_shms_err << endl;
    //cout<<"edtm LT = "<<runs[r]<<"   "<<LT<<   "   " <<LT_err << endl;
    //////////////////////clean data hist weighted by charge *LT *Treff//////////////////
    Double_t f_qelt = qcharge[r]/1000.0 * ltime[r] * teffhms[r] * teffshms[r];//0.001 to convert to mC

    //old, new is above
    //Double_t f_qelt = charge_sum_cut*0.001 * LT * tr_eff_hms * tr_eff_shms;//0.001 to convert to mC
    //cout << "Run: "<< runs[r]<<"   "<<"f_qelt = data Normfac = " <<f_qelt<<endl;
    ///plot accidental subtracracted hist/////////////////////////

    TCanvas * fin = new TCanvas ("fin", "fin", 1000, 800);
    fin->Divide(3,3);
    fin->cd(1);
    d_xbjn->Scale(1./f_qelt);
    if (d_xbjn->GetSumw2N() == 0) d_xbjn->Sumw2(kTRUE);
    d_xbjn->Draw("e, p1");
    d_xbjn->SetMarkerStyle(8);
    d_xbjn->SetMarkerColor(kBlue);

    // Double_t final_entries = d_xbjn->GetEntries();
    // Double_t final_integral = d_xbjn->Integral();
    // cout<<"Run = "<<runs[r]<<"  "<<"Total = "<<tt->GetEntries()<< "   "<<"bef_acc = "<< data_ent<<"    "<<"acc = "<<  acc_ent*(ctmin+ctmax)/16.0 <<"   "<<"final = "<<final_entries<< endl;
    // cout<< "  "<<endl;

    fin->cd(2);
    d_zhadn->Scale(1./f_qelt);
    d_zhadn->Draw("e, p1");
    d_zhadn->SetMarkerStyle(8);
    d_zhadn->SetMarkerColor(kBlue);

    
    fin->cd(3);
    d_Q2n->Scale(1./f_qelt);
    d_Q2n->Draw("e, p1");
    d_Q2n->SetMarkerStyle(8);
    d_Q2n->SetMarkerColor(kBlue);
      
    fin->cd(4);
    d_nun->Scale(1./f_qelt);
    d_nun->Draw("e, p1");
    d_nun->SetMarkerStyle(8);
    d_nun->SetMarkerColor(kBlue);
   
    fin->cd(5);
    d_omegan->Scale(1./f_qelt);
    d_omegan->Draw("e, p1");
    d_omegan->SetMarkerStyle(8);
    d_omegan->SetMarkerColor(kBlue);

    
    fin->cd(6);
    d_W2n->Scale(1./f_qelt);
    d_W2n->Draw("e, p1");
    d_W2n->SetMarkerStyle(8);
    d_W2n->SetMarkerColor(kBlue);
    
    fin->cd(7);
    d_Wprime2n->Scale(1./f_qelt);
    d_Wprime2n->Draw("e, p1");
    d_Wprime2n->SetMarkerStyle(8);
    d_Wprime2n->SetMarkerColor(kBlue);

    fin->cd(8);
    d_pmissn->Scale(1./f_qelt);
    d_pmissn->Draw("e, p1");
    d_pmissn->SetMarkerStyle(8);
    d_pmissn->SetMarkerColor(kBlue);

    fin->cd(9);
    d_emissn->Scale(1./f_qelt);
    d_emissn->Draw("e, p1");
    d_emissn->SetMarkerStyle(8);
    d_emissn->SetMarkerColor(kBlue);
    
    d_xbjn->Write();
    d_zhadn->Write();
    d_Q2n->Write();
    d_nun->Write();
    d_omegan->Write();
    d_W2n->Write();
    d_Wprime2n->Write();
    d_pmissn->Write();
    d_emissn->Write();
    aero_1dc->Write();
    rf_1dc->Write();

    fin->SaveAs(Form("pdf_new_W2/final_data_hist_normalized_%d.pdf",runs[r]));

    ///////////////Final Hist are these/////////////







    /////////////////////////////////////Clean data hist final/////////////////////
    
    /*  cout<<"cur+rate+charge_sum_cut+hcaleff+pcaleff = "<<"   "<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<  "   "<< hcal_eff << "   "<<hcal_eff_err<<"   "<< pcal_eff << "   "<<pcal_eff_err<<endl;

	cout<<" tot_cts+counts+acc             ="<< runs[r]<<"   "<< counts << "   "<<entries_pid<< "   "<< entries_acc/4. <<"  "<<endl;

	cout<< runs[r] <<"   "<< yield_bare <<"   "<< yield <<"   "<<  charge_sum_cut <<"   "<< tr_eff_hms << "   "<< tr_eff_shms <<"   "<< hcal_eff <<"   "<<pcal_eff<<"   "<<LT<<endl;
	//cout<<PTRIG1_Rate<<endl;
	*/
    
    TCanvas * c1 = new TCanvas ("c1", "c1", 600, 400);
    c1->Divide(3,2);
 
    c1->cd(1);
    hpbeta->Draw();
    hpbeta->SetTitle(Form("Run Number: %d", runs[r]));
    hpbeta->GetXaxis()->SetTitle("P.gtr.beta");
    hpbeta->SetLineWidth(2);


    c1->cd(2);
    hctime->Draw();
    hctime->SetLineWidth(2);
    hctimeacc->Draw("same");
    hctimeacc->SetLineColor(kRed);
    hctimeacc->SetLineWidth(2);
   
    c1->cd(3);
    hpbetact->Draw();
    hpbetact->SetLineWidth(2);


    c1->cd(4);
    hctimect->Draw();
    hctimect->SetLineWidth(2);

    c1->cd(5);gPad->SetGrid();//no pid
    hRF->Draw();


    c1->cd(6);gPad->SetGrid();//all pid but not RF-----------line draw
    hRF_pid->Draw();

      

    TCanvas * c2 = new TCanvas ("c2", "ctime", 600, 400);
    c2->Divide(2,2);
  
    //canvas 1)basic BW  2)basic + calaero 3) colz 4) pid colz 

    c2->cd(1);
    ctime_vs_rfb->Draw();

    c2->cd(2);
    ctime_vs_rf_calaero->Draw("");

    c2->cd(3);gPad->SetLogz();
    ctime_vs_rf_calaero->Draw("colz");


    c2->cd(4);gPad->SetLogz();
    ctime_vs_rf->Draw("colz");

    TCanvas * c3 = new TCanvas ("c3", "epr", 600, 400);
    //1)basic Black , 2)basic color 3)basic logz 4) pid black 5)pid colz 6)pid logz
    c3->Divide(3,2);
    c3->cd(1);
    epr_vs_rfb->Draw();

    c3->cd(2);
    epr_vs_rfb->Draw("colz");


    c3->cd(3);gPad->SetLogz();
    epr_vs_rfb->Draw("colz");

    c3->cd(4);
    epr_vs_rf->Draw();


    c3->cd(5);
    epr_vs_rf->Draw("colz");

    c3->cd(6);gPad->SetLogz();
    epr_vs_rf->Draw("colz");
    TCanvas * c4 = new TCanvas ("c4", "eptot_shms_tr", 600, 400);
    c4->Divide(2,1);
    
    c4->cd(1);
    pcal_tr_did->Draw();
    pcal_tr_did->SetTitle("pcal_pr_did");
    c4->cd(2);
    pcal_tr_should->Draw();
    pcal_tr_should->SetTitle("pcal_pr_should");

   
    TCanvas * c5 = new TCanvas ("c5", "hcal_pcal_eff", 600, 400);
    c5->Divide(2,2);
    c5->cd(1);
    hcal_did->Draw();
    hcal_did->SetTitle(Form("hcal_did_%d",runs[r]));
    
    c5->cd(2);
    hcal_should->Draw();
    hcal_should->SetTitle("hcal_should");

    c5->cd(3);
    pcal_did->Draw();
    pcal_did->SetTitle("Pcal_did");
    
    c5->cd(4);
    pcal_should->Draw();
    pcal_should->SetTitle("Pcal_should");
    
    txtfile1<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<LT<<           "   " <<LT_err << endl;
    txtfile2<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<tr_eff_hms<<   "   " <<tr_eff_hms_err << endl;
    txtfile3<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<tr_eff_shms<<  "   " <<tr_eff_shms_err << endl;
    txtfile4<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<yield_bare<<   "   " <<yield_bare_err << endl;
    txtfile5<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<yield<<        "   " <<yield_err << endl;
    txtfile6<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<hcal_did_counts<<        "   " <<hcal_should_counts << "   "<< hcal_eff << "   "<<hcal_eff_err<<endl;
    txtfile7<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<pcal_did_counts<<        "   " <<pcal_should_counts << "   "<< pcal_eff << "   "<<pcal_eff_err<<endl;
    txtfile8<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut<<"   "<<counts<< "   "<<yield_bare<<"   " <<yield_bare_err<<"   "<<yield_lttr<<"   "<<yield_lttr_err<<"   "<<yield<<"   "<<yield_err<< "   "<< LT <<"   "<< tr_eff_hms<<"   "<< tr_eff_shms<< hcal_eff << "   "<<pcal_eff<<endl;

    txtfile9<<runs[r]<<"\t\t\t"<< counts<<"\t\t\t"<< yield_lttr <<"\t\t\t"<< yield_lttr_err <<endl;
    txtfile10<< runs[r]<<"\t\t"<<max_value<<"\t\t"<<ctmin+ctmax<<"\t\t"<<max_value-ctmin<<"\t\t" << max_value+ctmax<<"\t\t"<<offsetrf<< endl;
    txtfile11<<runs[r]<<"      "<<tt->GetEntries()<< "        "<< data_ent<<"          "<<  acc_ent/4.0 <<"          "<<final_entries<< endl;

    c1->SaveAs(Form("pdf_new_W2/good_ev_csv_%d.pdf",runs[r]));
    c2->SaveAs(Form("pdf_new_W2/ctime_vs_rf_%d.pdf",runs[r]));
    c3->SaveAs(Form("pdf_new_W2/presh_vs_rf_%d.pdf",runs[r]));
    c4->SaveAs(Form("pdf_new_W2/shms_tracking_%d.pdf",runs[r]));
    c5->SaveAs(Form("pdf_new_W2/cal_eff_%d.pdf",runs[r]));

    double good_evt = hpbeta->GetEntries();
  
    
    delete  c1;
    delete  c2;
    delete  c3;
    delete  c4;
    delete  c5;

   
     
    //cout<< "==============================================  " <<endl;
    //cout<< "Next Run" <<endl;
    //cout<< " "<<endl;
  }//runs
 
}//all


