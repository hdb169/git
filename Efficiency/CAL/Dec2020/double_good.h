Double_t pionmass   = 0.1395701835;    //Gev/c^2
Double_t protonmass = 0.93827231;//GeV/c2
Double_t dxbj, dQ2, dnu,domega,  dW2, dpmiss, demiss,   Mx2a_acccut,Epi_acccut,zhad_acccut,Epi_pidcut,zhad_pidcut,Mx2_pidcut,Epi_cut,zhad_cut,Mx2_cut ;//d = data
Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,phodgoodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit, phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,hhodgoodscinhit,hhodbetanotrack,hdcntrack,hgtry,pgtry,phodbetanotrack,hcaletotnorm,gevnum,hmsxptar,hmsyptar,shmsxptar,shmsyptar ;

double scaler_eventnum,bcm1charge,bcm1current,scaler1MHztime,scaler1MHztimecut,bcm1chargecut,s1xscaler,s1yscaler,s2xscaler,s2yscaler,ptrig1scaler,ptrig2scaler,ptrig3scaler,ptrig4scaler,ptrig6scaler,pedtmscaler,pelcleanscaler,pl1acceptscaler,edtmtdctime,edtmtdctimeraw,mult,ptrig1rate,rate,charge   ;
    
Double_t Epi_dcut0, z_dcut0, Epi_dcut1, z_dcut1, Epi_dcut2, z_dcut2, Epi_dcut3, z_dcut3, Epi_dcut1plus2, z_dcut1plus2; 
Double_t Epi_acc0, z_acc0, Epi_acc1, z_acc1, Epi_acc2, z_acc2, Epi_acc3, z_acc3, Epi_acc1plus2, z_acc1plus2;

Bool_t shms_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, pcal_cut, hms_cut, pcal_cut_tight, cuttype1, cuttype1acc, cuttype2, cuttype2acc, cuttype1plus2, cuttype1plus2acc , hgcer_cut_loose,  paero_cut_loose,  cuttype0, cuttype0acc, common_cut, cuttype3, cuttype3acc, accsub_cut,  shms_tr_did_cut, shms_tr_should_cut, hms_tr_did_cut, hms_tr_should_cut,basic_cut,basic_cal_aero, hms_cal_should_cut, hms_cal_did_cut, shms_cal_should_cut, shms_cal_did_cut, cal_eff_hms_shms_base_cut  ;
Double_t Epi_cut_acc, zhad_cut_acc, Mx2_cut_acc,pcaletrack,hcaletrack;


//cal efff
Double_t rf_pion_pre, mod4_pioncut_pre, mod4_notpioncut_pre, Epi_cut_pre, zhad_cut_pre, Mx2_cut_pre, offsetrf ;
Bool_t  pid_cut_pre;


   
Double_t rf_pion, Epi, zhad, Mx2, hmsshower,shmsshower,ngcer  ;
Bool_t  mod4_pioncut,  mod4_pioncut_loose, mod4_notpioncut,  accL_cut, accR_cut, ctime_cut, base_cut,  base_cut_looserf,hms_etottrack_cut, shms_etottrack_cut,acc_cut , coin_cut;
Bool_t hcal_should_cut_acc, hcal_did_cut_acc, pcal_should_cut_acc , pcal_did_cut_acc,all_acc_cut ,hcal_did_cut_coin, hcal_should_cut_coin, pcal_should_cut_coin, pcal_did_cut_coin, all_coin_cut   ;   
