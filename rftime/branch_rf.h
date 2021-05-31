tt->SetBranchAddress("P.cal.eprtracknorm", &pcalepr);                                                                    
//tt->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);                                  
//tt->SetBranchAddress("P.cal.etotnorm", &pcaletotnorm);                                          
//tt->SetBranchAddress("H.kin.primary.omega", &pkinomega);

//tt->SetBranchAddress("P.hod.goodscinhit", &phodgoodscinhit); 
//tt->SetBranchAddress("P.hod.betanotrack", &phodbetanotrack); 
//tt->SetBranchAddress("P.dc.ntrack", &pdcntrack);
//tt->SetBranchAddress("H.hod.goodscinhit", &hhodgoodscinhit); 
//tt->SetBranchAddress("H.hod.betanotrack", &hhodbetanotrack); 
//tt->SetBranchAddress("H.dc.ntrack", &hdcntrack); 
//tt->SetBranchAddress("T.coin.pHODO_RF_tdcMultiplicity", &phodrftdcmult); 
//tt->SetBranchAddress("T.coin.pRF_tdcMultiplicity", &prftdcmult); 
//tt->SetBranchAddress("T.coin.hHODO_RF_tdcMultiplicity", &hhodrftdcmult); 
//tt->SetBranchAddress("T.coin.hHODO_RF_tdcTime", &hhodrftdctime); 
//tt->SetBranchAddress("T.coin.hRF_tdcMultiplicity", &hrftdcmult); 
//tt->SetBranchAddress("T.coin.hRF_tdcTime", &hrftdctime); 
//tt->SetBranchAddress("H.hod.fpHitsTime", &hhodfphitstime);                  
//tt->SetBranchAddress("H.gtr.y", &hgtry);
//tt->SetBranchAddress("P.gtr.y", &pgtry);
//tt->SetBranchAddress("H.cal.etotnorm", &hcaletotnorm);
//tt->SetBranchAddress("P.cal.etotnorm", &pcaletotnorm);
//tt->SetBranchAddress("T.coin.pEDTM_tdcTime",&edtmtdctime);
//tt->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&edtmtdctimeraw);
//tt->SetBranchAddress("T.coin.pEDTM_tdcTime",&edtmtdctime);
//tt->SetBranchAddress("H.kin.primary.x_bj",&dxbj);
//tt->SetBranchAddress("H.kin.primary.Q2",&dQ2);
//tt->SetBranchAddress("H.kin.primary.omega",&domega);//repeated 
/////tt->SetBranchAddress("H.kin.primary.nu",&dnu);
//tt->SetBranchAddress("H.kin.primary.omega",&dnu);
////////tt->SetBranchAddress("H.kin.primary.W2",&dW2);
///////////tt->SetBranchAddress("P.kin.secondary.pmiss",&dpmiss);
//tt->SetBranchAddress("P.kin.secondary.emiss",&demiss);

//tt->SetBranchAddress("P.kin.secondary.th_xq",&thetaq);



tt->SetBranchAddress("P.hod.fpHitsTime", &phodfphitstime);                  
tt->SetBranchAddress("g.evtyp", &eventtype);
tt->SetBranchAddress("g.evnum",&gevnum);
tt->SetBranchAddress("H.gtr.th",&hxptar);
tt->SetBranchAddress("H.gtr.ph",&hyptar);
tt->SetBranchAddress("P.gtr.th",&pxptar);
tt->SetBranchAddress("P.gtr.ph",&pyptar);
tt->SetBranchAddress("T.coin.pRF_tdcTime", &prftdctime); 
tt->SetBranchAddress("T.coin.pHODO_RF_tdcTime", &phodrftdctime); 
tt->SetBranchAddress("H.hod.goodstarttime", &hhodstarttime);
tt->SetBranchAddress("P.hod.goodstarttime",&phodstarttime);
tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
tt->SetBranchAddress("H.cal.etottracknorm", &hcaletottrack);       
tt->SetBranchAddress("P.cal.etottracknorm", &pcaletottrack);                                                                  
tt->SetBranchAddress("P.hgcer.npeSum", &hgcer);
tt->SetBranchAddress("P.aero.npeSum", &paero);
tt->SetBranchAddress("P.gtr.p", &mom); 
tt->SetBranchAddress("P.hgcer.xAtCer", &hgc_xAtCer); 
tt->SetBranchAddress("P.hgcer.yAtCer", &hgc_yAtCer); 
tt->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
tt->SetBranchAddress("P.gtr.dp", &pdelta);         
tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
tt->SetBranchAddress("H.cer.npeSum", &hcernpe); 
tt->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);
tt->SetBranchAddress("P.dc.InsideDipoleExit",&pdipole);
tt->SetBranchAddress("H.gtr.beta", &hbeta); 
tt->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
tt->SetBranchAddress("H.gtr.p", &HgtrP); 














