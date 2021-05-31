TH1F *hcal_tr_did        = new TH1F("hcal_tr_did","",100, 0, 2);
TH1F *hcal_tr_should     = new TH1F("hcal_tr_should","",100, 0, 2);
TH1F *pcal_tr_did        = new TH1F("pcal_tr_did","",100, 0, 2);
TH1F *pcal_tr_should     = new TH1F("pcal_tr_should","",100, 0, 2);
TH1F *hedtm_trig_acc_all = new TH1F("htrigaccall","",500, 120, 250);
TH1F *hptrig1rate        = new TH1F("hptrig1rate","",100, 10000 , 600000);
//---------------Main 1D pid plots------------
TH1F *hpbeta         = new TH1F("hpbeta","",100, 0.5, 1.5);
TH1F *hpbetact       = new TH1F("hpbetact","",100, -0.5, 2);
TH1D *hctime         = new TH1D("hctime", "", binaccct, loaccct, hiaccct);
TH1D *hctimect       = new TH1D("hctimect", "ctime (ns)", binaccct, loaccct, hiaccct);
TH1D *hctimeacc      = new TH1D("hctimeacc", "ctime (ns)", binaccct, loaccct, hiaccct);
TH1D *hRF            = new TH1D("hRF", " ", binrf, binrflo, binrfhi);//(fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008))
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
TH1F *aero_1d         = new TH1F("aero_1d","",50, 0, 50);
TH1F *aero_1da         = new TH1F("aero_1da","",50, 0, 50);
TH1F *aero_1dc         = new TH1F("aero_1dc","",50, 0, 50);
TH1F *rf_1d          = new TH1F("rf_1d","",100, 0, 4);
TH1F *rf_1da         = new TH1F("rf_1da","",100, 0, 4);
TH1F *rf_1dc         = new TH1F("rf_1dc","",100, 0, 4);
//z variation Jan 22
TH1F *rf_1d_1          = new TH1F("rf_1d_1","",100, 0, 4);
TH1F *rf_1da_1         = new TH1F("rf_1da_1","",100, 0, 4);
TH1F *rf_1dc_1         = new TH1F("rf_1dc_1","",100, 0, 4);

TH1F *rf_1d_2          = new TH1F("rf_1d_2","",100, 0, 4);
TH1F *rf_1da_2         = new TH1F("rf_1da_2","",100, 0, 4);
TH1F *rf_1dc_2         = new TH1F("rf_1dc_2","",100, 0, 4);

TH1F *rf_1d_3          = new TH1F("rf_1d_3","",100, 0, 4);
TH1F *rf_1da_3         = new TH1F("rf_1da_3","",100, 0, 4);
TH1F *rf_1dc_3         = new TH1F("rf_1dc_3","",100, 0, 4);

TH1F *rf_1d_4          = new TH1F("rf_1d_4","",100, 0, 4);
TH1F *rf_1da_4         = new TH1F("rf_1da_4","",100, 0, 4);
TH1F *rf_1dc_4         = new TH1F("rf_1dc_4","",100, 0, 4);

/* TH1F *zhad_1d          = new TH1F("zhad_1d","",100, 0.2, 0.8); */
/* TH1F *zhad_1da         = new TH1F("zhad_1da","",100, 0.2, 0.8); */
/* TH1F *zhad_1dc         = new TH1F("zhad_1dc","",100, 0.2, 0.8); */
TH1F *zhad_1d          = new TH1F("zhad_1d ","",100, 0., 1.0);
TH1F *zhad_1da         = new TH1F("zhad_1da","",100, 0., 1.0);
TH1F *zhad_1dc         = new TH1F("zhad_1dc","",100, 0., 1.0);


//z variation Jan 22 Done

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
//data simc comp a  acc, d = data

//Int_t binda = 50;
TH1D *d_xbj = new TH1D("d_xbj","d_xbj", binx, lox, hix);
TH1D *d_xbja = new TH1D("d_xbja","d_xbja", binx, lox, hix);
TH1D *d_xbj1 = new TH1D("d_xbj1","d_xbj1", binx, lox, hix);

TH1D *d_zhad_acccut = new TH1D("d_zhad_acccut","d_zhad_acccut", binz, loz, hiz);
TH1D *d_zhad = new TH1D("d_zhad","d_zhad", binz, loz, hiz);
TH1D *d_zhada = new TH1D("d_zhada","d_zhada", binz, loz, hiz);
TH1D *d_zhad1 = new TH1D("d_zhad1","d_zhad1", binz, loz, hiz);

TH1D *d_Q2 = new TH1D("d_Q2","d_Q2", binQ2, loQ2, hiQ2);
TH1D *d_Q2a = new TH1D("d_Q2a","d_Q2a", binQ2, loQ2, hiQ2);
TH1D *d_Q21 = new TH1D("d_Q21","d_Q21", binQ2, loQ2, hiQ2);

TH1D *d_nu = new TH1D("d_nu","d_nu", binnu, lonu, hinu);
TH1D *d_nua = new TH1D("d_nua","d_nua", binnu, lonu, hinu);
TH1D *d_nu1 = new TH1D("d_nu1","d_nu1", binnu, lonu, hinu);

TH1D *d_omega = new TH1D("d_omega","d_omega", binomega, loomega, hiomega);
TH1D *d_omegaa = new TH1D("d_omegaa","d_omegaa", binomega, loomega, hiomega);
TH1D *d_omega1 = new TH1D("d_omega1","d_omega1", binomega, loomega, hiomega);

TH1D *d_W2_acccut = new TH1D("d_W2_acccut","d_W2_acccut", binW2, loW2, hiW2);
TH1D *d_W2 = new TH1D("d_W2","d_W2", binW2, loW2, hiW2);
TH1D *d_W2a = new TH1D("d_W2a","d_W2a", binW2, loW2, hiW2);
TH1D *d_W21 = new TH1D("d_W21","d_W21", binW2, loW2, hiW2);

TH1D *d_Wprime2 = new TH1D("d_Wprime2","d_Wprime2", binWp2, loWp2, hiWp2);
TH1D *d_Wprime2a = new TH1D("d_Wprime2a","d_Wprime2a", binWp2, loWp2, hiWp2);
TH1D *d_Wprime21 = new TH1D("d_Wprime21","d_Wprime21", binWp2, loWp2, hiWp2);

TH1D *d_pmiss = new TH1D("d_pmiss","d_pmiss", binpm, lopm, hipm);
TH1D *d_pmissa = new TH1D("d_pmissa","d_pmissa", binpm, lopm, hipm);
TH1D *d_pmiss1 = new TH1D("d_pmiss1","d_pmiss1", binpm, lopm, hipm);

TH1D *d_emiss = new TH1D("d_emiss","d_emiss", binem, loem, hiem);
TH1D *d_emissa = new TH1D("d_emissa","d_emissa", binem, loem, hiem);
TH1D *d_emiss1 = new TH1D("d_emiss1","d_emiss1", binem, loem, hiem);

    
TH2D *haerorf     = new TH2D("haerorf","AERO_vs_RF NOPID",binrf, binrflo, binrfhi, binaero, binloaero, binhiaero);
TH2D *haeroctime    = new TH2D("haeroctime","AERO_vs_CTIME NOPID",binct, loct, hict, binaero, binloaero, binhiaero);
TH2D *haeropresh    = new TH2D("haeropresh","AERO_vs_PRESH NOPID",100,0, 0.2, binaero, binloaero, binhiaero);
TH2D *haerocal    = new TH2D("haerocal","AERO_vs_Cal NOPID",100,0, 1.2, binaero, binloaero, binhiaero);


   
TH1D *haerodid     = new TH1D("haerodid","haerodid", binaero, binloaero, binhiaero);
TH1D *haeroshould     = new TH1D("haeroshould","haeroshould", binaero, binloaero, binhiaero);
TH1D *rfdid         = new TH1D("rfdid", " ", binrf, binrflo, binrfhi);//(fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008))
TH1D *rfshould         = new TH1D("rfshould", " ", binrf, binrflo, binrfhi);//(fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008))

// TH1F *histcer0 = new TH1F("histcer0","", 100, 0,30);
TH1F *histcer_central[22];
TH1F *histcer_middle[22];
TH1F *histcer_exterior[22];
TH1F *histcer_all[22];
/* TH1F *hpass_all[22]; */
/* TH1F *htotal_all[22]; */

TH2F * hctime_vs_rftime_did[22];
TH2F * hctime_vs_rftime_should[22];

TH2F * hctime_vs_aero_did[22];
TH2F * hctime_vs_aero_should[22];

TH2F * hctime_vs_etot_did[22];
TH2F * hctime_vs_etot_should[22];

TH2F * hctime_vs_epr_did[22];
TH2F * hctime_vs_epr_should[22];


for(int i=1;i<21;i++){
  histcer_central[i]  = new TH1F(Form("histcer_central[%d]",i),"", 50, 0,35); 
  histcer_middle[i]   = new TH1F(Form("histcer_middle[%d]",i),"", 50, 0,35); 
  histcer_exterior[i] = new TH1F(Form("histcer_exterior[%d]",i),"", 50, 0,35);
  histcer_all[i]  = new TH1F(Form("histcer_alll[%d]",i),"", 50, 0,35); 
  hctime_vs_rftime_did[i]  = new TH2F(Form("hctime_vs_rftime_did[%d]",i),"",100, -0.5, 4.5, 100, 42, 48); 
  hctime_vs_rftime_should[i]  = new TH2F(Form("hctime_vs_rftime_should[%d]",i),"",100, -0.5, 4.5, 100, 42, 48); 

  hctime_vs_aero_did[i]  = new TH2F(Form("hctime_vs_aero_did[%d]",i),"",100, 0, 30, 100, 42, 48); 
  hctime_vs_aero_should[i]  = new TH2F(Form("hctime_vs_aero_should[%d]",i),"",100, 0,30, 100, 42, 48); 

  hctime_vs_etot_did[i]  = new TH2F(Form("hctime_vs_etot_did[%d]",i),"",100, 0, 1.5, 100, 42, 48); 
  hctime_vs_etot_should[i]  = new TH2F(Form("hctime_vs_etot_should[%d]",i),"",100, 0, 1.5, 100, 42, 48);

  hctime_vs_epr_did[i]  = new TH2F(Form("hctime_vs_epr_did[%d]",i),"",100, 0, 1.5, 100, 42, 48); 
  hctime_vs_epr_should[i]  = new TH2F(Form("hctime_vs_epr_should[%d]",i),"",100, 0, 1.5, 100, 42, 48);

 }
TH1F * RFhist[115];
for(int i=1;i<115;i++){
  RFhist[i]  = new TH1F(Form("RFhist[%d]",i),"",binrf, binrflo, binrfhi); 
 }
TH1F * RFsum  = new TH1F ("RFsum","RFsum",binrf, binrflo, binrfhi); 

TH1F * hpass_mom_hole_present  = new TH1F( "hpass_mom_hole_present","", 17, 2.9, 4.55); 
TH1F *  htotal_mom_hole_present  = new TH1F("htotal_mom_hole_present","", 17, 2.9, 4.55); 

TH1F * hpass_mom_all  = new TH1F( "hpass_mom_all","Passed (Mom); Momuntum; Entries", 17, 2.9, 4.55); 
TH1F *  htotal_mom_all  = new TH1F("htotal_mom_all","Total (Mom); Momuntum; Entries", 17, 2.9, 4.55);

TH1F  * hpass_delta_all  = new TH1F( "hpass_delta_all","Passed (Delta); Delta; Entries", 17, -10, 20); 
TH1F  * htotal_delta_all  = new TH1F("htotal_delta_all","Total (Delta); Delta; Entries", 17, -10, 20); 

TH1F * hpass_mom_all_acc  = new TH1F( "hpass_mom_all_acc","Passed (Mom); Momuntum; Entries", 17, 2.9, 4.55); 
TH1F *  htotal_mom_all_acc  = new TH1F("htotal_mom_all_acc","Total (Mom); Momuntum; Entries", 17, 2.9, 4.55);

TH1F  * hpass_delta_all_acc  = new TH1F( "hpass_delta_all_acc","Passed (Delta); Delta; Entries", 17, -10, 20); 
TH1F  * htotal_delta_all_acc  = new TH1F("htotal_delta_all_acc","Total (Delta); Delta; Entries", 17, -10, 20); 

/* TH1F * hpass_mom_all_acc_1peak  = new TH1F( "hpass_mom_all_acc_1peak","", 17, 2.9, 4.55);  */
/* TH1F *  htotal_mom_all_acc_1peak  = new TH1F("htotal_mom_all_acc_1peak","", 17, 2.9, 4.55); */

/* TH1F  * hpass_delta_all_acc_1peak  = new TH1F( "hpass_delta_all_acc_1peak","", 17, -10, 20);  */
/* TH1F  * htotal_delta_all_acc_1peak  = new TH1F("htotal_delta_all_acc_1peak","", 17, -10, 20);  */

TH1F * hpass_mom_all_acc_sub  = new TH1F( "hpass_mom_all_acc_sub","Passed (Mom); Momuntum; Entries", 17, 2.9, 4.55); 
TH1F *  htotal_mom_all_acc_sub  = new TH1F("htotal_mom_all_acc_sub","Total (Mom); Momuntum; Entries", 17, 2.9, 4.55);

TH1F  * hpass_delta_all_acc_sub  = new TH1F( "hpass_delta_all_acc_sub","Passed (Delta); Delta; Entries", 17, -10, 20); 
TH1F  * htotal_delta_all_acc_sub  = new TH1F("htotal_delta_all_acc_sub","Total (Delta); Delta; Entries", 17, -10, 20); 




TH1F *  hpass_mom_central  = new TH1F( "hpass_mom_central","", 17, 2.9, 4.55); 
TH1F *  htotal_mom_central  = new TH1F("htotal_mom_central","", 17, 2.9, 4.55); 

TH1F  * hpass_mom_middle  = new TH1F( "hpass_mom_middle","", 17, 2.9, 4.55); 
TH1F  *  htotal_mom_middle  = new TH1F("htotal_mom_middle","", 17, 2.9, 4.55); 

TH1F  *  hpass_mom_exterior  = new TH1F( "hpass_mom_exterior","", 17, 2.9, 4.55); 
TH1F  * htotal_mom_exterior  = new TH1F("htotal_mom_exterior","", 17, 2.9, 4.55);

TH1F  * hpass_delta_hole_present  = new TH1F( "hpass_delta_hole_present","", 17, -10, 20); 
TH1F  * htotal_delta_hole_present  = new TH1F("htotal_delta_hole_present","", 17, -10, 20); 


TH1F  * hpass_delta_central  = new TH1F( "hpass_delta_central","", 17, -10, 20); 
TH1F  * htotal_delta_central  = new TH1F("htotal_delta_central","", 17, -10, 20); 

TH1F *  hpass_delta_middle  = new TH1F( "hpass_delta_middle","", 17, -10, 20); 
TH1F  * htotal_delta_middle  = new TH1F("htotal_delta_middle","", 17, -10, 20); 

TH1F *  hpass_delta_exterior  = new TH1F( "hpass_delta_exterior","", 17, -10, 20); 
TH1F *  htotal_delta_exterior  = new TH1F("htotal_delta_exterior","", 17, -10, 20);

 TH1F * momhist1   = new TH1F( "momhist1","", 17, 2.9, 4.55); 
 TH1F * delhist1   = new TH1F( "delhist1","", 17, -10, 20);

 TH1F * momhist2   = new TH1F( "momhist2","", 17, 2.9, 4.55); 
 TH1F * delhist2   = new TH1F( "delhist2","", 17, -10, 20);

 TH1F * momhist3   = new TH1F( "momhist3","", 17, 2.9, 4.55); 
 TH1F * delhist3   = new TH1F( "delhist3","", 17, -10, 20);

 TH1F * momhist4   = new TH1F( "momhist4","", 17, 2.9, 4.55); 
 TH1F * delhist4   = new TH1F( "delhist4","", 17, -10, 20);


 TH1F * momhist5   = new TH1F( "momhist5","", 17, 2.9, 4.55); 
 TH1F * delhist5   = new TH1F( "delhist5","", 17, -10, 20);

//////////HRF for all runs, acc hRF, acc sub hRF
TH1D *hRF_acc            = new TH1D("hRF_acc", "hRF_acc; RFTime; Counts ", binrf, binrflo, binrfhi);
TH1D *hRF_coin            = new TH1D("hRF_coin", "hRF_coin; RFTime; Counts ", binrf, binrflo, binrfhi);
TH1D *hRF_clean_pos            = new TH1D("hRF_clean_pos", "hRF_clean_pos; RFTime;Counts ", binrf, binrflo, binrfhi);
TH1D *hRF_clean_neg            = new TH1D("hRF_clean_neg", "hRF_clean_neg; RFTime;Counts ", binrf, binrflo, binrfhi);


/*
TEfficiency *pEff_mom_all = new TEfficiency();
pEff_mom_all = new TEfficiency(* hpass_mom_all, *htotal_mom_all); 

 TEfficiency *pEff_mom_central = new TEfficiency();
pEff_mom_central = new TEfficiency(* hpass_mom_central, *htotal_mom_central); 

TEfficiency *pEff_mom_middle = new TEfficiency();
pEff_mom_middle = new TEfficiency(* hpass_mom_middle, *htotal_mom_middle); 


TEfficiency *pEff_mom_exterior = new TEfficiency();
pEff_mom_exterior = new TEfficiency(* hpass_mom_exterior, *htotal_mom_exterior);


TEfficiency *pEff_delta_all = new TEfficiency();
pEff_delta_all = new TEfficiency(* hpass_delta_all, *htotal_delta_all); 

 TEfficiency *pEff_delta_central = new TEfficiency();
pEff_delta_central = new TEfficiency(* hpass_delta_central, *htotal_delta_central); 

TEfficiency *pEff_delta_middle = new TEfficiency();
pEff_delta_middle = new TEfficiency(* hpass_delta_middle, *htotal_delta_middle); 


TEfficiency *pEff_delta_exterior = new TEfficiency();
pEff_delta_exterior = new TEfficiency(* hpass_delta_exterior, *htotal_delta_exterior);

*/

  /* histcer_middle[21]  = new TH1F(Form("histcer_middley[%d]",21),"", 50, 0,35);  */
  /* histcer_middle[21]   = new TH1F(Form("histcer_middle[%d]",21),"", 50, 0,35);  */
  /* histcer_exterior[21] = new TH1F(Form("histcer_exterior[%d]",21),"", 50, 0,35); */
  /* histcer_all[21]  = new TH1F(Form("histcer_alll[%d]",21),"", 50, 0,35);  */



/*TH1F *histcer1 = new TH1F("histcer1","", 100, 0,30);

TH1F *histcer2 = new TH1F("histcer2","", 100, 0,30);
    TH1F *histcer3 = new TH1F("histcer3","", 100, 0,30);
    TH1F *histcer4 = new TH1F("histcer4","", 100, 0,30);
    TH1F *histcer5 = new TH1F("histcer5","", 100, 0,30);
    TH1F *histcer6 = new TH1F("histcer6","", 100, 0,30);
    TH1F *histcer7 = new TH1F("histcer7","", 100, 0,30);
    TH1F *histcer8 = new TH1F("histcer8","", 100, 0,30);
    TH1F *histcer9 = new TH1F("histcer9","", 100, 0,30);
    TH1F *histcer10 = new TH1F("histcer10","", 100, 0,30);
    TH1F *histcer11 = new TH1F("histcer11","", 100, 0,35);
    TH1F *histcer12 = new TH1F("histcer12","", 100, 0,35);
    TH1F *histcer13 = new TH1F("histcer13","", 100, 0,35);
    TH1F *histcer14 = new TH1F("histcer14","", 100, 0,35);
    TH1F *histcer15 = new TH1F("histcer15","", 100, 0,35);
    TH1F *histcer16 = new TH1F("histcer16","", 100, 0,35);
    TH1F *histcer17 = new TH1F("histcer17","", 100, 0,35);
    TH1F *histcer18 = new TH1F("histcer18","", 100, 0,35);
    TH1F *histcer19 = new TH1F("histcer19","", 100, 0,35);
    TH1F *histcer20 = new TH1F("histcer20","", 100, 0,35);

*/
