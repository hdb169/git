TH1F *hist_hmsp        = new TH1F("hist_hmsp","HMS Central Mom ",100, 0, 10);
TH1F *hist_shmsp        = new TH1F("hist_shmsp","SHMS Central Mom ",100, 0, 10);


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
TH1D *hctimeacc      = new TH1D("hctimeacc", "ctime (ns)", binaccct, loaccct, hiaccct);
TH1D *hist_ctime_clean = new TH1D("hist_ctime_clean", "ctime (ns)", binaccct, loaccct, hiaccct);
TH1D *hRF            = new TH1D("hRF", "RF = (fmod(-prftdctime+phodfphitstime + offsetrf ,4.008)) ", binrf, binrflo, binrfhi);//(fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008))
TH1D *hRF_pid        = new TH1D("hRF_pid", "RF_pid = (fmod(-prftdctime+phodfphitstime + offsetrf ,4.008)) ", binrf, binrflo, binrfhi);//(fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008))
TH1D *hctime_pid     = new TH1D("hctime_pid", "ctime (ns)", binaccct, loaccct, hiaccct);
//---------------Basic 2D plots=> hms and shms but not PID------------

TH2D *ctime_vs_rfb    = new TH2D("ctime_vs_rfb", "CTIME vs RF NOPID", binrf, binrflo, binrfhi, binct, loct, hict);
TH2D *shwr_vs_rfb     = new TH2D("shwr_vs_rfb", "SHOWER vs RF NOPID", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
TH2D *epr_vs_rfb      = new TH2D("epr_vs_rfb"," EPR vs RF  NOPID ", binrf, binrflo, binrfhi, bincalepr, localepr, hicalepr);
TH2D *etot_vs_rfb     = new TH2D("etot_vs_rfb"," ETOTTRACKNORM vs RF NOPID ", binrf, binrflo, binrfhi, bincal, local, hical);
TH2D *aero_vs_rfb     = new TH2D("aero_vs_rfb","AERO_vs_RF NOPID",binrf, binrflo, binrfhi, binaero, binloaero, binhiaero);
TH2D *beta_vs_rfb     = new TH2D("beta_vs_rfb","BETA vs RF NOPID",binrf, binrflo, binrfhi, 100, -0.5, 1.5 );
TH2D *aero_vs_ctb     = new TH2D("hctime_vs_rfb", "AERO vs RF NOPID",binaero, binloaero, binhiaero, binct, loct, hict );
TH2D *sh_vs_pshb      = new TH2D("sh_vs_pshb","SH_vs_PRESH NOPID",100, 0.0,0.8, 100, 0.0, 1.8);
///

TH2D *pcalsh_vs_pcaletot      = new TH2D("pcalsh_vs_pcaletot","PCALSH_vs_PCAL ETOT",100, 0.0,2, 100, 0.0, 2);//====================================================here
TH2D *pcalsh_vs_hcaletot      = new TH2D("pcalsh_vs_hcaletot","PCALSH_vs_HCAL ETOT",100, 0.0,2, 100, 0.0, 2);
TH2D *pcalpsh_vs_pcaletot      = new TH2D("pcalpsh_vs_pcaletot","PCALPSH_vs_PCAL ETOT",100, 0.0,2, 100, 0.0, 0.8);//====================================================here
TH2D *pcalpsh_vs_hcaletot      = new TH2D("pcalpsh_vs_hcaletot","PCALPSH_vs_HCAL ETOT",100, 0.0,2, 100, 0.0, 0.8);

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
TH2D *shwr_vs_rf     = new TH2D("shwr_vs_rf", "SHOWER vs RF", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
TH2D *aero_vs_rf     = new TH2D("aero_vs_rf","AERO_vs_RF",binrf, binrflo, binrfhi, binaero, binloaero, binhiaero);
TH2D *beta_vs_rf     = new TH2D("beta_vs_rf","BETA vs RF",binrf, binrflo, binrfhi, 100, -0.5, 1.5 );
TH2D *aero_vs_ct     = new TH2D("hctime_vs_rf", "AERO vs RF",binaero, binloaero, binhiaero, binct, loct, hict );
/////////cal eff Nov 11// all pid including cal

TH2D *hms_sh_vs_psh   = new TH2D("hms_sh_vs_psh","HMS_SH_vs_PRESH ",100, 0.0,1.5, 100, 0.0, 1.5);
TH2D *shms_sh_vs_psh  = new TH2D("shms_sh_vs_psh","SHMS_SH_vs_PRESH ",100, 0.0,1.5, 100, 0.0, 1.5);

TH2D *hms_sh_vs_psh_should_acc   = new TH2D("hms_sh_vs_psh_should_acc","HMS_SH_vs_PRESH SHOULD ACC",100, 0.0,1.5, 100, 0.0, 1.5);
TH2D *shms_sh_vs_psh_should_acc  = new TH2D("shms_sh_vs_psh_should_acc","SHMS_SH_vs_PRESH SHOULD ACC",100, 0.0,1.5, 100, 0.0, 1.5);

TH2D *hms_sh_vs_psh_should_coin   = new TH2D("hms_sh_vs_psh_should_coin","HMS_SH_vs_PRESH SHOULD COIN",100, 0.0,1.5, 100, 0.0, 1.5);
TH2D *shms_sh_vs_psh_should_coin  = new TH2D("shms_sh_vs_psh_should_coin","SHMS_SH_vs_PRESH SHOULD COIN",100, 0.0,1.5, 100, 0.0, 1.5);

TH2D *hms_sh_vs_psh_should_clean   = new TH2D("hms_sh_vs_psh_should_clean","HMS_SH_vs_PRESH SHOULD CLEAN",100, 0.0,1.5, 100, 0.0, 1.5);
TH2D *shms_sh_vs_psh_should_clean  = new TH2D("shms_sh_vs_psh_should_clean","SHMS_SH_vs_PRESH SHOULD CLEAN",100, 0.0,1.5, 100, 0.0, 1.5);




TH2D *ctime_vs_rf     = new TH2D("ctime_vs_rf", "CTIME vs RF", binrf, binrflo, binrfhi, binct, loct, hict);
TH2D *etot_vs_rf      = new TH2D("etot_vs_rf"," shms etottracknorm vs RF ", binrf, binrflo, binrfhi, bincal, local, hical);
TH2D *hms_etot_vs_rf  = new TH2D("hms_etot_vs_rf"," hms etottracknorm vs RF ", binrf, binrflo, binrfhi, bincal, local, hical);
TH2D *epr_vs_rf       = new TH2D("epr_vs_rf"," EPR vs RF ", binrf, binrflo, binrfhi, bincalepr, localepr, hicalepr);
TH2D *sh_vs_rf        = new TH2D("sh_vs_rf "," shms SH vs RF  ", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
TH2D *hmsepr_vs_rf    = new TH2D("hmsepr_vs_rf "," hms EPR vs RF  ", binrf, binrflo, binrfhi, bincalepr, lohcalepr, hihcalepr);
TH2D *hmssh_vs_rf     = new TH2D("hmssh_vs_rf ","   hms SH vs RF  ", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
TH2D *ctime_vs_etot   = new TH2D("ctime_vs_etot", "CTIME vs ETOT", bincal, local, hical, binct, loct, hict);
TH2D *ctime_vs_epr    = new TH2D("ctime_vs_epr", "CTIME vs EPR", bincalepr, localepr, hicalepr, binct, loct, hict);
TH1D *hctimect        = new TH1D("hctimect", "ctime (ns)", binaccct, loaccct, hiaccct);
/////////cal eff Nov 11// all pid NO  cal
TH2D *hms_sh_vs_psh_base   = new TH2D("hms_sh_vs_psh_base","HMS_SH_vs_PRESH base ",100, 0.0,0.8, 100, 0.0, 1.8);
TH2D *shms_sh_vs_psh_base  = new TH2D("shms_sh_vs_psh_base","SHMS_SH_vs_PRESH base ",100, 0.0,0.8, 100, 0.0, 1.8);
TH2D *ctime_vs_rf_base     = new TH2D("ctime_vs_rf_base", "CTIME vs RF base", binrf, binrflo, binrfhi, binct, loct, hict);
TH2D *etot_vs_rf_base      = new TH2D("etot_vs_rf_base"," shms etottracknorm vs RF base ", binrf, binrflo, binrfhi, bincal, local, hical);
TH2D *hms_etot_vs_rf_base  = new TH2D("hms_etot_vs_rf_base"," hms etottracknorm vs RF base ", binrf, binrflo, binrfhi, bincal, local, hical);

TH2D *epr_vs_rf_base       = new TH2D("epr_vs_rf_base"," shms EPR vs RF base ", binrf, binrflo, binrfhi, bincalepr, localepr, hicalepr);
TH2D *sh_vs_rf_base        = new TH2D("sh_vs_rf_base"," shms SH vs RF base ", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
TH2D *hmsepr_vs_rf_base    = new TH2D("hmsepr_vs_rf_base"," hms EPR vs RF base ", binrf, binrflo, binrfhi, bincalepr, lohcalepr, hihcalepr);
TH2D *hmssh_vs_rf_base     = new TH2D("hmssh_vs_rf_base","   hms SH vs RF base ", binrf, binrflo, binrfhi, binshwr, loshwr, hishwr);
TH2D *ctime_vs_etot_base   = new TH2D("ctime_vs_etot_base", "CTIME vs ETOT base", bincal, local, hical, binct, loct, hict);
TH2D *ctime_vs_epr_base    = new TH2D("ctime_vs_epr_base", "CTIME vs EPR base", bincalepr, localepr, hicalepr, binct, loct, hict);
//Nov17

TH2D *hcernpe_vs_hmsp     = new TH2D("hcernpe_vs_hmsp ","HCER NPE vs HMS P  ",100, 3.0, 9, 100, 0, 30);
TH2D *aeronpe_vs_shmsp     = new TH2D("aeronpe_vs_shmsp ","AERO NPE vs SHMS P  ",100, 1.0, 9, 100, 0, 30);
TH2D *hgcernpe_vs_shmsp     = new TH2D("hgcernpe_vs_shmsp ","HGCER NPE vs SHMS P  ",100, 1.0, 9, 100, 0, 30);


//nov19
TH1D *hms_xptar           = new TH1D("hms_xptar", "hms_xptar",100,-0.1,0.1);
TH1D *hms_yptar           = new TH1D("hms_yptar", "hms_yptar",100,-0.06,0.06);
TH1D *shms_xptar          = new TH1D("shms_xptar", "shms_xptar",100,-0.06,0.06);
TH1D *shms_yptar          = new TH1D("shms_yptar", "shms_yptar",100,-0.06,0.06);
TH2D *hms_xptar_vs_yptar  = new TH2D("hms_xptar_vs_yptar","hms_xptar_vs_yptar",100,-0.06,0.06,100,-0.1,0.1);
TH2D *shms_xptar_vs_yptar = new TH2D("shms_xptar_vs_yptar","shms_xptar_vs_yptar",100,-0.06,0.06,100,-0.1,0.1);

TH1D *hms_xptar_noxyptar          = new TH1D("hms_xptar_noxyptar", "hms_xptar",100,-0.1,0.1);
TH1D *hms_yptar_noxyptar          = new TH1D("hms_yptar_noxyptar", "hms_yptar",100,-0.06,0.06);
TH1D *shms_xptar_noxyptar         = new TH1D("shms_xptar_noxyptar", "shms_xptar",100,-0.06,0.06);
TH1D *shms_yptar_noxyptar         = new TH1D("shms_yptar_noxyptar", "shms_yptar",100,-0.06,0.06);
TH2D *hms_xptar_vs_yptar_noxyptar = new TH2D("hms_xptar_vs_yptar_noxyptar","hms_xptar_vs_yptar",100,-0.06,0.06,100,-0.1,0.1);
TH2D *shms_xptar_vs_yptar_noxyptar= new TH2D("shms_xptar_vs_yptar_noxyptar","shms_xptar_vs_yptar",100,-0.06,0.06,100,-0.1,0.1);



//TH1D *hctimect_base        = new TH1D("hctimect_base", "ctime (ns)", binaccct, loaccct, hiaccct);



////////////////////////////////////////////////////////
//cal effi
TH1D *hcal_did            = new TH1D("hcal_did", "hcal_did", 100, 0, 2);
TH1D *hcal_should         = new TH1D("hcal_should", "hcal_should", 100, 0, 2);
TH1D *pcal_did            = new TH1D("pcal_did", "pcal_did", 100, 0, 2);
TH1D *pcal_should         = new TH1D("pcal_should", "pcal_should", 100, 0, 2);
TH1D *pcalsh_did          = new TH1D("pcalsh_did", "pcalsh_did", 100, 0, 0.3);
TH1D *pcalsh_should       = new TH1D("pcalsh_should", "pcalsh_should", 100, 0, 0.3);
///new
TH1D *hcal_did_presh      = new TH1D("hcal_did_presh", "hcal_did_presh", 100, 0, 2);
TH1D *hcal_should_presh   = new TH1D("hcal_should_presh", "hcal_should_presh", 100, 0, 2);
TH1D *hcal_did_sh         = new TH1D("hcal_did_sh", "hcal_did_sh", 100, 0, 2);
TH1D *hcal_should_sh      = new TH1D("hcal_should_sh", "hcal_should_sh", 100, 0, 2);

TH1D *pcal_did_presh      = new TH1D("pcal_did_presh", "pcal_did_presh", 100, 0, 2);
TH1D *pcal_should_presh   = new TH1D("pcal_should_presh", "pcal_should_presh", 100, 0, 2);
TH1D *pcal_did_sh         = new TH1D("pcal_did_sh", "pcal_did_sh", 100, 0, 2);
TH1D *pcal_should_sh      = new TH1D("pcal_should_sh", "pcal_should_sh", 100, 0, 2);


TH1D *hcal_did_rc       = new TH1D("hcal_did_rc", "hcal_did_rc", bincal, local, hical);//rc = rf time, coin time
TH1D *hcal_should_rc    = new TH1D("hcal_should_rc", "hcal_should_rc", bincal, local, hical);
TH1D *pcal_did_rc       = new TH1D("pcal_did_rc", "pcal_did_rc", bincal, local, hical);
TH1D *pcal_should_rc    = new TH1D("pcal_should_rc", "pcal_should_rc", bincal, local, hical);
TH1D *pcalsh_did_rc     = new TH1D("pcalsh_did_rc", "pcalsh_did_rc", 100, 0, 0.3);
TH1D *pcalsh_should_rc  = new TH1D("pcalsh_should_rc", "pcalsh_should_rc", 100, 0, 0.3);
//main hists Nov10
TH1D *hist_hcal_did_acc = new TH1D("hist_hcal_did_acc", "hist_hcal_did_acc", bincal, local, hical);
TH1D *hist_hcal_should_acc = new TH1D("hist_hcal_should_acc", "hist_hcal_should_acc", bincal, local, hical);
TH1D *hist_pcal_did_acc = new TH1D("hist_pcal_did_acc", "hist_pcal_did_acc", bincal, local, hical);
TH1D *hist_pcal_should_acc = new TH1D("hist_pcal_should_acc", "hist_pcal_should_acc", bincal, local, hical);


TH1D *hist_hcal_did_coin = new TH1D("hist_hcal_did_coin", "hist_hcal_did_coin", bincal, local, hical);
TH1D *hist_hcal_should_coin = new TH1D("hist_hcal_should_coin", "hist_hcal_should_coin", bincal, local, hical);
TH1D *hist_pcal_did_coin = new TH1D("hist_pcal_did_coin", "hist_pcal_did_coin", bincal, local, hical);
TH1D *hist_pcal_should_coin = new TH1D("hist_pcal_should_coin", "hist_pcal_should_coin", bincal, local, hical);

TH1D *hist_hcal_did_clean = new TH1D("hist_hcal_did_clean", "hist_hcal_did_clean", bincal, local, hical);
TH1D *hist_hcal_should_clean = new TH1D("hist_hcal_should_clean", "hist_hcal_should_clean", bincal, local, hical);
TH1D *hist_pcal_did_clean = new TH1D("hist_pcal_did_clean", "hist_pcal_did_clean", bincal, local, hical);
TH1D *hist_pcal_should_clean = new TH1D("hist_pcal_should_clean", "hist_pcal_should_clean", bincal, local, hical);

//aero eff
TH1D *hist_pcal_aero_did_acc = new TH1D("hist_pcal_aero_did_acc", "hist_pcal_aero_did_acc", bincal, local, hical);
TH1D *hist_pcal_aero_should_acc = new TH1D("hist_pcal_aero_should_acc", "hist_pcal_aero_should_acc", bincal, local, hical);
TH1D *hist_pcal_aero_did_coin = new TH1D("hist_pcal_aero_did_coin", "hist_pcal_aero_did_coin", bincal, local, hical);
TH1D *hist_pcal_aero_should_coin = new TH1D("hist_pcal_aero_should_coin", "hist_pcal_aero_should_coin", bincal, local, hical);
TH1D *hist_pcal_aero_should_clean = new TH1D("hist_pcal_aero_should_clean", "hist_pcal_aero_should_clean", bincal, local, hical);
TH1D *hist_pcal_aero_did_clean = new TH1D("hist_pcal_aero_did_clean", "hist_pcal_aero_did_clean", bincal, local, hical);


//main hist same as above but in delta

TH1D *hist_hcal_did_delta_acc = new TH1D("hist_hcal_did_delta_acc", "hist_hcal_did_delta_acc", binhdelta, lohdelta,  hihdelta);
TH1D *hist_hcal_should_delta_acc = new TH1D("hist_hcal_should_delta_acc", "hist_hcal_should_delta_acc", binhdelta, lohdelta,  hihdelta);
TH1D *hist_pcal_did_delta_acc = new TH1D("hist_pcal_did_delta_acc", "hist_pcal_did_delta_acc", binpdelta, lopdelta,  hipdelta);
TH1D *hist_pcal_should_delta_acc = new TH1D("hist_pcal_should_delta_acc", "hist_pcal_should_delta_acc", binpdelta, lopdelta,  hipdelta);


TH1D *hist_hcal_did_delta_coin = new TH1D("hist_hcal_did_delta_coin", "hist_hcal_did_delta_coin", binhdelta, lohdelta,  hihdelta);
TH1D *hist_hcal_should_delta_coin = new TH1D("hist_hcal_should_delta_coin", "hist_hcal_should_delta_coin", binhdelta, lohdelta,  hihdelta);
TH1D *hist_pcal_did_delta_coin = new TH1D("hist_pcal_did_delta_coin", "hist_pcal_did_delta_coin", binpdelta, lopdelta,  hipdelta);
TH1D *hist_pcal_should_delta_coin = new TH1D("hist_pcal_should_delta_coin", "hist_pcal_should_delta_coin", binpdelta, lopdelta,  hipdelta);

TH1D *hist_hcal_did_delta_clean = new TH1D("hist_hcal_did_delta_clean", "hist_hcal_did_delta_clean", binhdelta, lohdelta,  hihdelta);
TH1D *hist_hcal_should_delta_clean = new TH1D("hist_hcal_should_delta_clean", "hist_hcal_should_delta_clean", binhdelta, lohdelta,  hihdelta);
TH1D *hist_pcal_did_delta_clean = new TH1D("hist_pcal_did_delta_clean", "hist_pcal_did_delta_clean", binpdelta, lopdelta,  hipdelta);
TH1D *hist_pcal_should_delta_clean = new TH1D("hist_pcal_should_delta_clean", "hist_pcal_should_delta_clean", binpdelta, lopdelta,  hipdelta);
//empty hist to set Range in Y in pEff vs Delta
TH1D *hcal_empty_hist = new TH1D("hcal_empty_histhist", "hcal_empty_hist", binhdelta, lohdelta,  hihdelta);
TH1D *pcal_empty_hist = new TH1D("pcal_empty_histhist", "pcal_empty_hist", binpdelta, lopdelta,  hipdelta);

TH1D *hcal_eff_vs_delta = new TH1D("hcal_eff_vs_delta", "hcal_eff_vs_delta", binhdelta, lohdelta,  hihdelta);
TH1D *pcal_eff_vs_delta = new TH1D("pcal_eff_vs_delta", "pcal_eff_vs_delta", binpdelta, lopdelta,  hipdelta);


////////delta done
//////////hcer eff
TH1D *hist_hcer_did_acc = new TH1D("hist_hcer_did_acc", "hist_hcer_did_acc", 100, 0, 35);
TH1D *hist_hcer_should_acc = new TH1D("hist_hcer_should_acc", "hist_hcer_should_acc", 100, 0, 35);
TH1D *hist_hcer_did_coin = new TH1D("hist_hcer_did_coin", "hist_hcer_did_coin", 100, 0, 35);
TH1D *hist_hcer_should_coin = new TH1D("hist_hcer_should_coin", "hist_hcer_should_coin", 100, 0, 35);
TH1D *hist_hcer_did_clean = new TH1D("hist_hcer_did_clean", "hist_hcer_did_clean", 100, 0, 35);
TH1D *hist_hcer_should_clean = new TH1D("hist_hcer_should_clean", "hist_hcer_should_clean", 100, 0, 35);


////treat shower and preshower separately : acc below++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TH1D *hist_pcal_shower_did_acc = new TH1D("hist_pcal_shower_did_acc", "hist_pcal_shower_did_acc", bincal, local, hical);                          //+
TH1D *hist_pcal_shower_should_acc = new TH1D("hist_pcal_shower_should_acc", "hist_pcal_shower_should_acc", bincal, local, hical);                 //+
TH1D *hist_pcal_pre_shower_did_acc = new TH1D("hist_pcal_pre_shower_did_acc", "hist_pcal_pre_shower_did_acc", bincal, local, hical);
TH1D *hist_pcal_pre_shower_should_acc = new TH1D("hist_pcal_pre_shower_should_acc", "hist_pcal_pre_shower_should_acc", bincal, local, hical);
//Coin
TH1D *hist_pcal_shower_did_coin = new TH1D("hist_pcal_shower_did_coin", "hist_pcal_shower_did_coin", bincal, local, hical);
TH1D *hist_pcal_shower_should_coin = new TH1D("hist_pcal_shower_should_coin", "hist_pcal_shower_should_coin", bincal, local, hical);
TH1D *hist_pcal_pre_shower_did_coin = new TH1D("hist_pcal_pre_shower_did_coin", "hist_pcal_pre_shower_did_coin", bincal, local, hical);
TH1D *hist_pcal_pre_shower_should_coin = new TH1D("hist_pcal_pre_shower_should_coin", "hist_pcal_pre_shower_should_coin", bincal, local, hical);
//clean after acc subtraction
TH1D *hist_pcal_shower_did_clean = new TH1D("hist_pcal_shower_did_clean", "hist_pcal_shower_did_clean", bincal, local, hical);
TH1D *hist_pcal_shower_should_clean = new TH1D("hist_pcal_shower_should_clean", "hist_pcal_shower_should_clean", bincal, local, hical);
TH1D *hist_pcal_pre_shower_did_clean = new TH1D("hist_pcal_pre_shower_did_clean", "hist_pcal_pre_shower_did_clean", bincal, local, hical);         //+
TH1D *hist_pcal_pre_shower_should_clean = new TH1D("hist_pcal_pre_shower_should_clean", "hist_pcal_pre_shower_should_clean", bincal, local, hical);//+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
//TH1D *d_W2 = new TH1D("d_W2","d_W2", binW2, loW2, hiW2);
TH1D *d_W2a = new TH1D("d_W2a","d_W2a", binW2, loW2, hiW2);
TH1D *d_W21 = new TH1D("d_W21","d_W21", binW2, loW2, hiW2);

TH1D *d_W2 = new TH1D("d_W2","d_W2", 100, 0, 10);
TH1D *d_Wprime2 = new TH1D("d_Wprime2","d_Wprime2", 100, 0, 10);

//TH1D *d_Wprime2 = new TH1D("d_Wprime2","d_Wprime2", binWp2, loWp2, hiWp2);
TH1D *d_Wprime2a = new TH1D("d_Wprime2a","d_Wprime2a", binWp2, loWp2, hiWp2);
TH1D *d_Wprime21 = new TH1D("d_Wprime21","d_Wprime21", binWp2, loWp2, hiWp2);

TH1D *d_pmiss = new TH1D("d_pmiss","d_pmiss", binpm, lopm, hipm);
TH1D *d_pmissa = new TH1D("d_pmissa","d_pmissa", binpm, lopm, hipm);
TH1D *d_pmiss1 = new TH1D("d_pmiss1","d_pmiss1", binpm, lopm, hipm);

TH1D *d_emiss = new TH1D("d_emiss","d_emiss", binem, loem, hiem);
TH1D *d_emissa = new TH1D("d_emissa","d_emissa", binem, loem, hiem);
TH1D *d_emiss1 = new TH1D("d_emiss1","d_emiss1", binem, loem, hiem);

    
