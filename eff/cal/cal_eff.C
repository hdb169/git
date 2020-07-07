This is just a trial, may not be correct...because other detectors can not exactly selcet electrons or pions, so need to apply pi to e ratio or similar to get
efficiency....
#include "header.h"

#define NRUNS 204
void cal_eff(){
  //#include "gStyle.h"

  ofstream txtfile6("txtfile_csv/hcal_eff_new.txt",ios::app);
  ofstream txtfile7("txtfile_csv/pcal_eff_new.txt",ios::app);


  Int_t runs[NRUNS]= { 7593, 7594, 7595, 7596, 7597, 7599, 7600, 7601, 7602, 7603, 7604, 7605, 7606, 7607, 7608, 7609, 7610, 7611, 7612, 7613, 7614, 7615, 7616, 7617, 7618, 7619, 7620, 7621, 7622, 7623, 7625, 7626, 7627, 7628, 7629, 7630, 7631, 7632, 7633, 7634, 7635, 7636, 7637, 7638, 7639, 7640, 7641, 7642, 7643, 7644, 7645, 7646, 7647, 7648, 7649, 7650, 7651, 7652, 7654, 7655, 7657, 7658, 7659, 7660, 7661, 7662, 7663, 7666, 7667, 7668, 7669 ,7670 ,7671, 7672, 7673, 7674, 7675, 7676, 7677, 7678, 7679, 7680, 7681, 7682, 7684, 7685, 7686, 7687, 7688, 7689, 7690, 7692, 7694, 7695, 7697, 7698, 7699, 7702, 7703, 7706, 7707, 7708, 7709, 7710, 7711, 7712, 7713, 7714, 7715, 7716, 7717, 7718, 7719, 7720, 7721, 7722, 7723, 7724, 7725, 7727, 7728, 7729, 7730, 7733, 7735, 7736, 7737, 7738, 7739, 7740, 7741, 7742, 7743, 7747, 7748, 7749, 7750, 7751, 7752, 7753, 7754, 7755, 7757, 7758, 7759, 7760, 7762, 7763, 7765, 7766, 7768, 7769, 7770, 7771, 7772, 7773, 7774, 7775, 7776, 7777, 7778, 7779, 7781, 7782, 7783, 7784, 7785, 7786, 7787, 7790, 7791, 7792, 7793, 7794, 7796, 7797, 7798, 7799, 7800, 7801, 7802, 7803, 7804, 7805, 7806, 7807, 7808, 7809, 7811, 7812, 7813, 7814, 7815, 7816, 7817, 7819, 7820  };//, 6428, 6429, 6430, 6431, 6432, 6433, 6456, 6459, 6460, 6461, 6462, 6463, 6464};
  // Int_t runs[NRUNS]= {6427, 6428, 6429, 6430, 6431, 6432, 6433};//, 6456, 6459, 6460, 6461, 6462, 6463, 6464};

  gROOT->SetBatch("TRUE");
  for(Int_t r=0; r<NRUNS; r++){

    TString filename  = Form("/home/hdbhatt/Desktop/lumi/all_ROOTfiles/coin_replay_production_%d_-1.root", runs[r]);

    TFile *f = new TFile(filename, "READ");

    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

#include "binz.h"


    Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,phodgoodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit, phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,rf_pion,hhodgoodscinhit,hhodbetanotrack,hdcntrack,hgtry,pgtry,phodbetanotrack,hcaletotnorm ;

    double scaler_eventnum,bcm1charge,bcm1current,scaler1MHztime,scaler1MHztimecut,bcm1chargecut,s1xscaler,s1yscaler,s2xscaler,s2yscaler,ptrig1scaler,ptrig2scaler,ptrig3scaler,ptrig4scaler,ptrig6scaler,pedtmscaler,pelcleanscaler,pl1acceptscaler,edtmtdctime,edtmtdctimeraw,mult, current_bcmcut, current_nobcmcut,rate1,ptrig1rate,rate,charge   ;
    
    Double_t Epi_dcut0, z_dcut0, Epi_dcut1, z_dcut1, Epi_dcut2, z_dcut2, Epi_dcut3, z_dcut3, Epi_dcut1plus2, z_dcut1plus2; 
    Double_t Epi_acc0, z_acc0, Epi_acc1, z_acc1, Epi_acc2, z_acc2, Epi_acc3, z_acc3, Epi_acc1plus2, z_acc1plus2;

    Bool_t  accR_cut, accL_cut,shms_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, mod4_pioncut, mod4_notpioncut, pcal_cut, ctime_cut, hms_cut, pcal_cut_tight, cuttype1, cuttype1acc, cuttype2, cuttype2acc, cuttype1plus2, cuttype1plus2acc , hgcer_cut_loose,  paero_cut_loose,  cuttype0, cuttype0acc, common_cut, cuttype3, cuttype3acc, accsub_cut, acc_cut, shms_tr_did_cut, shms_tr_should_cut, hms_tr_did_cut, hms_tr_should_cut,basic_cut,basic_cal_aero, hms_cal_should_cut, hms_cal_did_cut, shms_cal_should_cut, shms_cal_did_cut, cal_eff_hms_shms_base_cut  ;

    Double_t ctmin = 1.5;
    Double_t ctmax = 1.5;
    Double_t rfmin = 0.5;
    Double_t rfmax = 1.5;
    Double_t eprmin = 0.0;
    Double_t eprmax = 0.1;
    Double_t pcaletotmin = 0.0;
    Double_t pcaletotmax = 0.6;
    Double_t offsetrf = 399.05;
    // Double_t offsetrf = 400.93;

    TTree * tt = (TTree *)f->Get("T");
    TTree * ss = (TTree *)f->Get("TSP");

   
    TH1F *hcal_tr_did        = new TH1F("hcal_tr_did","",100, 0, 2);
    TH1F *hcal_tr_should     = new TH1F("hcal_tr_should","",100, 0, 2);
    TH1F *pcal_tr_did        = new TH1F("pcal_tr_did","",100, 0, 2);
    TH1F *pcal_tr_should     = new TH1F("pcal_tr_should","",100, 0, 2);
    TH1F *hedtm_trig_acc_all = new TH1F("htrigaccall","",500, 120, 250);
    TH1F *hptrig1rate        = new TH1F("hptrig1rate","",100, 10000 , 600000);
    //---------------Main 1D pid plots------------
    TH1F *hpbeta         = new TH1F("hpbeta","",100, -0.5, 1.5);
    TH1F *hpbetact       = new TH1F("hpbetact","",100, -0.5, 2);
    TH1D *hctime         = new TH1D("hctime", "ctime (ns)", binaccct, loaccct, hiaccct);
    TH1D *hctimect       = new TH1D("hctimect", "ctime (ns)", binaccct, loaccct, hiaccct);
    TH1D *hctimeacc      = new TH1D("hctimeacc", "ctime (ns)", binaccct, loaccct, hiaccct);
    TH1D *hRF            = new TH1D("hRF", "RF = (fmod(-prftdctime+phodfphitstime + offsetrf ,4.008)) ", binrf, binrflo, binrfhi);//(fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008))
    TH1D *hRF_pid        = new TH1D("hRF_pid", "RF_pid = (fmod(-prftdctime+phodfphitstime + offsetrf ,4.008)) ", binrf, binrflo, binrfhi);//(fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008))
    //---------------Basic 2D plots=> hms and shms but not PID------------

    TH2D *ctime_vs_rfb    = new TH2D("ctime_vs_rfb", "CTIME vs RF NOPID", binrf, binrflo, binrfhi, binct, loct, hict);
    TH2D *shwr_vs_rfb     = new TH2D("shwr_vs_rfb", "SHOWER vs RF NOPID", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
    TH2D *epr_vs_rfb      = new TH2D("epr_vs_rfb"," EPR vs RF  NOPID ", binrf, binrflo, binrfhi, bincalepr, localepr, hicalepr);
    TH2D *etot_vs_rfb     = new TH2D("etot_vs_rfb"," ETOTTRACKNORM vs RF NOPID ", binrf, binrflo, binrfhi, bincal, local, hical);
    TH2D *aero_vs_rfb     = new TH2D("aero_vs_rfb","AERO_vs_RF NOPID",binrf, binrflo, binrfhi, binaero, binloaero, binhiaero);
    TH2D *beta_vs_rfb     = new TH2D("beta_vs_rfb","BETA vs RF NOPID",binrf, binrflo, binrfhi, 100, -0.5, 1.5 );
    TH2D *aero_vs_ctb     = new TH2D("hctime_vs_rfb", "AERO vs RF NOPID",binaero, binloaero, binhiaero, binct, loct, hict );
    TH2D *sh_vs_pshb      = new TH2D("sh_vs_pshb","SH_vs_PRESH NOPID",100, 0.0,0.8, 100, 0.0, 1.8);

    //------------ CAL CT AERO
    TH2D *ctime_vs_rf_calaero      = new TH2D("ctime_vs_rf_calaero", "CTIME vs RF NOPID", binrf, binrflo, binrfhi, binct, loct, hict);//no ct cut
    TH2D *shwr_vs_rf_calctaero     = new TH2D("shwr_vs_rf_calctaero", "SHOWER vs RF NOPID", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
    TH2D *epr_vs_rf_calctaero      = new TH2D("epr_vs_rf_calctaero"," EPR vs RF  NOPID ", binrf, binrflo, binrfhi, bincalepr, localepr, hicalepr);
    TH2D *etot_vs_rf_calctaero     = new TH2D("etot_vs_rf_calctaero"," ETOTTRACKNORM vs RF NOPID ", binrf, binrflo, binrfhi, bincal, local, hical);
    TH2D *aero_vs_rf_calctaero     = new TH2D("aero_vs_rf_calctaero","AERO_vs_RF NOPID",binrf, binrflo, binrfhi, binaero, binloaero, binhiaero);
    TH2D *beta_vs_rf_calctaero     = new TH2D("beta_vs_rf_calctaero","BETA vs RF NOPID",binrf, binrflo, binrfhi, 100, -0.5, 1.5 );
    TH2D *aero_vs_ct_calctaero     = new TH2D("hctime_vs_rf_calctaero", "AERO vs RF NOPID",binaero, binloaero, binhiaero, binct, loct, hict );
    TH2D *sh_vs_psh_calctaero      = new TH2D("sh_vs_psh_calctaero","SH_vs_PRESH NOPID",100, 0.0,0.8, 100, 0.0, 1.8);
    
    
    //---------------Main 2D plots=> hms, shms, rf and PID
    TH2D *ctime_vs_rf    = new TH2D("ctime_vs_rf", "CTIME vs RF", binrf, binrflo, binrfhi, binct, loct, hict);
    TH2D *shwr_vs_rf     = new TH2D("shwr_vs_rf", "SHOWER vs RF", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
    TH2D *epr_vs_rf      = new TH2D("epr_vs_rf"," EPR vs RF ", binrf, binrflo, binrfhi, bincalepr, localepr, hicalepr);
    TH2D *etot_vs_rf     = new TH2D("etot_vs_rf"," ETOTTRACKNORM vs RF ", binrf, binrflo, binrfhi, bincal, local, hical);
    TH2D *aero_vs_rf     = new TH2D("aero_vs_rf","AERO_vs_RF",binrf, binrflo, binrfhi, binaero, binloaero, binhiaero);
    TH2D *beta_vs_rf     = new TH2D("beta_vs_rf","BETA vs RF",binrf, binrflo, binrfhi, 100, -0.5, 1.5 );
    TH2D *aero_vs_ct     = new TH2D("hctime_vs_rf", "AERO vs RF",binaero, binloaero, binhiaero, binct, loct, hict );
    TH2D *sh_vs_psh      = new TH2D("sh_vs_psh","SH_vs_PRESH",100, 0.0,0.8, 100, 0.0, 1.8);

    //cal effi
    TH1D *hcal_did       = new TH1D("hcal_did", "hcal_did", 100, 0, 2);
    TH1D *hcal_should    = new TH1D("hcal_should", "hcal_should", 100, 0, 2);
    TH1D *pcal_did       = new TH1D("pcal_did", "pcal_did", 100, 0, 2);
    TH1D *pcal_should    = new TH1D("pcal_should", "pcal_should", 100, 0, 2);


    //----------------------------------------Fill Hist
    #include "branch.h"
/*tt->SetBranchAddress("P.gtr.p", &PgtrP); 
tt->SetBranchAddress("H.gtr.p", &HgtrP); 
tt->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
tt->SetBranchAddress("H.gtr.beta", &hbeta); 
tt->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
tt->SetBranchAddress("P.gtr.dp", &pdelta);                                                                                
tt->SetBranchAddress("P.cal.eprtracknorm", &pcalepr);                                                                    
tt->SetBranchAddress("P.cal.etottracknorm", &pcaletottrack);                                                                  
tt->SetBranchAddress("P.hgcer.npeSum", &hgcer);
tt->SetBranchAddress("P.aero.npeSum", &paero);                                          
tt->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);                                  
tt->SetBranchAddress("H.cal.etottracknorm", &hcaletottrack);       
tt->SetBranchAddress("P.cal.etotnorm", &pcaletotnorm);                                          
tt->SetBranchAddress("H.cer.npeSum", &hcernpe); 
tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
tt->SetBranchAddress("H.kin.primary.omega", &pkinomega);
tt->SetBranchAddress("H.hod.goodstarttime", &hhodstarttime);
tt->SetBranchAddress("P.hod.goodstarttime",&phodstarttime);
tt->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);
tt->SetBranchAddress("H.hod.betanotrack", &hhodbetanotrack); 
tt->SetBranchAddress("H.dc.ntrack", &hdcntrack); 
tt->SetBranchAddress("g.evtyp", &eventtype);
tt->SetBranchAddress("H.gtr.y", &hgtry);
tt->SetBranchAddress("P.gtr.y", &pgtry);
tt->SetBranchAddress("H.cal.etotnorm", &hcaletotnorm);
tt->SetBranchAddress("P.cal.etotnorm", &pcaletotnorm);
tt->SetBranchAddress("T.coin.pEDTM_tdcTime",&edtmtdctime);
tt->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&edtmtdctimeraw);
tt->SetBranchAddress("T.coin.pEDTM_tdcTime",&edtmtdctime);
    ss->SetBranchAddress("evNumber", &scaler_eventnum);
    ss->SetBranchAddress("P.BCM1.scalerCharge", &bcm1charge);
    ss->SetBranchAddress("P.BCM1.scalerCurrent", &bcm1current);
    ss->SetBranchAddress("P.1MHz.scalerTime", &scaler1MHztime);
    ss->SetBranchAddress("P.1MHz.scalerTimeCut",&scaler1MHztimecut);
    ss->SetBranchAddress("P.BCM1.scalerChargeCut",&bcm1chargecut);
    ss->SetBranchAddress("P.S1X.scaler", &s1xscaler);
    ss->SetBranchAddress("P.S1Y.scaler", &s1yscaler);
    ss->SetBranchAddress("P.S2X.scaler", &s2xscaler);
    ss->SetBranchAddress("P.pTRIG3.scaler", &ptrig3scaler);
    ss->SetBranchAddress("P.pTRIG4.scaler", &ptrig4scaler);
    ss->SetBranchAddress("P.pTRIG6.scaler", &ptrig6scaler);
    ss->SetBranchAddress("P.EDTM.scaler",&pedtmscaler);
    ss->SetBranchAddress("P.pEL_CLEAN.scaler", &pelcleanscaler);
    ss->SetBranchAddress("P.pL1ACCP.scaler",&pl1acceptscaler);
    ss->SetBranchAddress("P.pTRIG1.scalerRate",&ptrig1rate);
*/
    
    #include "scalerbranch.h"

    Long64_t nentriesD = tt->GetEntries();
    //livetime
    Long64_t nscalerD = ss->GetEntries();
    for (int j = 0; j < nscalerD; j++){
      ss->GetEntry(j);
      current_bcmcut = bcm1chargecut/scaler1MHztimecut;
      current_nobcmcut = bcm1charge/scaler1MHztime;
      hptrig1rate->Fill(ptrig1rate);
    }
    
    charge= bcm1chargecut*0.001;
    double bin_max_rate = hptrig1rate->GetMaximumBin();
    rate = hptrig1rate->GetBinCenter(bin_max_rate);
    rate1 = rate*0.001;  

    for (int kk=0; kk<nentriesD;  kk++){//---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(kk);
      paero_cut = paero>3.0;
      hgcer_cut = hgcer>1.0;
      rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
      mod4_pioncut = rf_pion > rfmin && rf_pion < rfmax;
      mod4_notpioncut =!mod4_pioncut;
      pcal_cut =  pcaletottrack < pcaletotmax  && pcalepr< eprmax ;	    
      hms_cut  =  hdelta> -10 && hdelta < 10 && hbeta >0.8 && hbeta <1.2 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 && hcaletottrack <1.2 && hcernpe>1.5 ;
      shms_cut =  pdelta >-10 && pdelta < 20   && pbeta <1.5 && phodstarttime == 1  && eventtype > 3 &&  pcal_cut && mod4_pioncut && paero_cut;//&& pdipole ==1
      pid_cut  = hms_cut && shms_cut;
       
      
      if (pid_cut){
	hpbeta->Fill(pbeta);
	hctime->Fill(ctime);
      }
    }
    //cout<<"Step 1: calulating the max peak value of the ctime dist"<<endl;

 
    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
    cout<<"ctime peak is at = "<< max_value <<endl;
    cout<<"Step 2: Now calculating accidental backgrounds"<<endl;
    Bool_t hgcer_cut1 ,paero_cut1 , mod4_pioncut1,  mod4_notpioncut1,   pcal_cut1,   hms_cut1,   shms_cut1, shms_cut2, pid_cut1, ctime_cut1, acc_cut1;
  
     for (int kk=0; kk<nentriesD;  kk++){//-----------------------------------------------------Main Evt Loop
       // for (int kk=0; kk<100;  kk++){//-----------------------------------------------------Main Evt Loop


      tt->GetEntry(kk);

      accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
      accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
      acc_cut1 = (accR_cut || accL_cut);
      ctime_cut1 = ctime > max_value - ctmin && ctime < max_value + ctmax;


      paero_cut1 = paero>3.0;
      hgcer_cut =  hgcer>2.0;
      rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
      mod4_pioncut1 = rf_pion > rfmin && rf_pion < rfmax;
      mod4_notpioncut1 =!mod4_pioncut;
      pcal_cut1 =  pcaletottrack < pcaletotmax  && pcalepr< eprmax ;	    
      hms_cut1  =  hdelta> -10 && hdelta < 10 && hbeta >0.8 && hbeta <1.2 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 && hcaletottrack <1.2 && hcernpe>1.5 ;
      shms_cut1 =  pdelta >-10 && pdelta < 20   && pbeta <1.5 && phodstarttime == 1 && pdipole ==1 && eventtype > 3;//basic
      shms_cut2 =  pcal_cut1 && mod4_pioncut1 && paero_cut1;//main pi+/- pid
      basic_cut = hms_cut1 && shms_cut1;
      basic_cal_aero = hms_cut1 && shms_cut1 &&  pcal_cut1 && paero_cut1;//No RF
      pid_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && ctime_cut1;//-------------------all cut vs1
      acc_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && acc_cut1;

        


      //cal eff
      //  cal_eff_hms_shms_base_cut = hdelta> -10 && hdelta < 10 &&  hbeta> 0.8 &&  hbeta <1.2  && hhodstarttime ==1 && hdipole==1 && hcernpe>1.5 && pdelta > -10 && pdelta < 20   && pbeta <1.5 && phodstarttime == 1 && pdipole ==1 && eventtype > 3 && ctime_cut1 && paero_cut1 &&  mod4_pioncut1 && hgcer >1;//all basic cuts

      //play below
      cal_eff_hms_shms_base_cut = hdelta> -10 && hdelta < 10 &&  hbeta> 0.8 &&  hbeta <1.2  && hhodstarttime ==1 && hdipole==1 && hcernpe>1.5 &&  eventtype > 3 && pdelta > -10 && pdelta < 20   && pbeta <1.5 && phodstarttime == 1 && pdipole ==1 &&   ctime_cut1 && paero_cut1 &&   mod4_pioncut1 ;//&& hgcer >1;

      
																				       
      hms_cal_should_cut       =   cal_eff_hms_shms_base_cut &&  pcaletottrack < 0.75 && pcalepr< 0.15 ;//base + shms cuts 
      hms_cal_did_cut          =   hms_cal_should_cut && hcaletottrack > 0.8 && hcaletottrack < 1.2;//should + hcal cuts


      shms_cal_should_cut     =   cal_eff_hms_shms_base_cut  && hcaletottrack > 0.8 && hcaletottrack < 1.2 ;//base + hms cuts
      shms_cal_did_cut        =   shms_cal_should_cut &&  pcaletottrack < 0.75 && pcalepr< 0.15;// should + pcal_cuts

      //track
     
      // cout<<"1 "<<    hms_cal_did_cut <<endl;
      // cout<<"2 "<<    hms_cal_should_cut <<endl;
      // cout<<"3 "<<    shms_cal_did_cut <<endl;
      // cout<<"4 "<<    shms_cal_should_cut <<endl;



      
      //livetime only========================================================
      if (edtmtdctimeraw != 0){
	hedtm_trig_acc_all->Fill(edtmtdctime);	
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
      //accidental only
      if(acc_cut1){
	hctimeacc->Fill(ctime);
      }
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
	if(hgcer_cut){
	  hRF_pid->Fill(rf_pion);}
      }

      
      //good pid only
      if (pid_cut1){//--------------------------------------all pi+/- pid plots goes here
	hpbetact->Fill(pbeta);
	hctimect->Fill(ctime);
	
	ctime_vs_rf->Fill(rf_pion, ctime);
	shwr_vs_rf->Fill(rf_pion, pcaletottrack - pcalepr);
	epr_vs_rf->Fill(rf_pion, pcalepr);
	etot_vs_rf->Fill(rf_pion,pcaletottrack);
	aero_vs_rf->Fill(rf_pion, paero); 
	beta_vs_rf->Fill(rf_pion, pbeta);
	aero_vs_ct->Fill(ctime, paero);
	
      }

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
    }//entries
  
    double hcal_did_counts    = hcal_did->GetEntries();
    double hcal_should_counts = hcal_should->GetEntries();
    double hcal_eff = hcal_did_counts/hcal_should_counts;
    double hcal_eff_err = (1/hcal_should_counts) * sqrt(hcal_did_counts * (1-hcal_did_counts/hcal_should_counts));

    
    double pcal_did_counts    = pcal_did->GetEntries();
    double pcal_should_counts = pcal_should->GetEntries();
    double pcal_eff = pcal_did_counts/pcal_should_counts;
    double pcal_eff_err = (1/pcal_should_counts) * sqrt(pcal_did_counts * (1-pcal_did_counts/pcal_should_counts));

     cout<< runs[r]<<"   "<<current_bcmcut<<"   "<<rate1<<"   "<<hcal_did_counts<<        "   " <<hcal_should_counts << "   "<< hcal_eff << "   "<<hcal_eff_err<<endl;
     cout<< runs[r]<<"   "<<current_bcmcut<<"   "<<rate1<<"   "<<pcal_did_counts<<        "   " <<pcal_should_counts << "   "<< pcal_eff << "   "<<pcal_eff_err<<endl;

     /* 
    double did_hms = hcal_tr_did->GetEntries();
    double should_hms = hcal_tr_should->GetEntries();
    double tr_eff_hms = did_hms/should_hms;
    double tr_eff_hms_err = (1/should_hms) * sqrt(did_hms*(1-did_hms/should_hms));

    
    double did_shms = pcal_tr_did->GetEntries();
    double should_shms = pcal_tr_should->GetEntries();
    double tr_eff_shms = did_shms/should_shms;
    double tr_eff_shms_err = (1/should_shms) * sqrt(did_shms*(1-did_shms/should_shms));


    //cout<< runs[r]<< " "<<"hdid =  "<<did_hms<<"    "<<"hshould =  " <<should_hms<<"    "<< "htreff =  "   <<tr_eff_hms<<"    "<<"htr_err =  " <<tr_eff_hms_err<< endl;
    //cout<< runs[r]<< " "<<"pdid =  "<<did_shms<<"    "<<"pshould =  " <<should_shms<<"    "<< "ptreff =  "   <<tr_eff_shms<<"    "<<"ptr_err =  " <<tr_eff_shms_err<< endl;

    double entries_pid = hctimect->GetEntries();
    double entries_acc = hctimeacc->GetEntries();
    double counts = entries_pid - entries_acc/4;
    //cout<< " final good counts in the Run "<< runs[r]<< "  = "<< entries_pid << " - "<< entries_acc << " * 1/4  = " << counts <<endl;  
    
    //livetime
    double f_curr  = current_nobcmcut/ current_bcmcut;
    double pedtmtrigacc_all = hedtm_trig_acc_all->GetEntries();
    double rmeas = pedtmtrigacc_all / pedtmscaler ;
    double LT = (rmeas - ( 1.0 - f_curr ))/ f_curr;
    double LT_err= LT * sqrt(1./pedtmtrigacc_all + 1./pedtmscaler);
    //cout<<"LT for "<< runs[r] <<"\t"<<rate1<<"\t"<< current_bcmcut<<"\t" <<pedtmtrigacc_all<<"\t"<<pedtmscaler<<"\t"<<f_curr<<"\t"<<LT<<"\t"<<LT_err<<endl;
    //yield
    double yield_bare = counts/(charge);
    double yield_bare_err = yield_bare * sqrt(1/counts);

    double yield = counts/(charge * tr_eff_hms * tr_eff_shms);//livetime is removed for now
    double yield_err = yield * sqrt(1/counts);

    //cout<< "yield for "<<runs[r]<< " : " << rate1 <<"   "<< current_bcmcut<< "   "<<charge <<"   "<< yield <<"   "<<yield_err<< endl;
    */
     txtfile6<< runs[r]<<"   "<<current_bcmcut<<"   "<<rate1<<"   "<<hcal_did_counts<<        "   " <<hcal_should_counts << "   "<< hcal_eff << "   "<<hcal_eff_err<<endl;
    txtfile7<< runs[r]<<"   "<<current_bcmcut<<"   "<<rate1<<"   "<<pcal_did_counts<<        "   " <<pcal_should_counts << "   "<< pcal_eff << "   "<<pcal_eff_err<<endl;

    //cout<<rate1<<endl;
    /* 
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

    c1->cd(5);//no pid
    hRF->Draw();


    c1->cd(6);//all pid but not RF-----------line draw
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

    */
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
    

    
   
    c5->SaveAs(Form("pdf/cal_eff_%d.pdf",runs[r]));

    double good_evt = hpbeta->GetEntries();
  
 
  delete  c5;


     
    //cout<< "==============================================  " <<endl;
    cout<< "Next Run" <<endl;
    cout<< " "<<endl;
  }//runs
 
}//all


