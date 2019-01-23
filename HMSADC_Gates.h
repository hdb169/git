//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 13 11:12:03 2018 by ROOT version 6.10/02
// from TTree T/Hall A Analyzer Output DST
// found on file: ../../ROOTfiles/coin_replay_production_3423_-1.root
//////////////////////////////////////////////////////////

#ifndef HMSADCGates_h
#define HMSADCGates_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class HMSADCGates : public TSelector {
 public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  // Declaration of histograms
  TH2F          **h1HCERPulseAmp;
  TH1F          **h1HCERAdcPulseTime;
  TH1F          **h1HDCRawTdc;

  //*******************added for CER *************
  TH1F          **h1HCERAdcPulseTimeStarttimeDiff;
  TH2F          **h1HCERPulseAmpVsPulseTimeStarttimeDiff;
  TH1F          **h1HCERAdcPulseTimeStarttimeDiffMultCal ;
  TH2F          **h1HCERPulseAmpVsPulseTimeStarttimeDiffMultCal;
  TH1F          **h1HCERGoodAdcTdcTimeDiffMultCal ;
  TH2F          **h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal;


  //*******************added for HCAL 1pr pos*************

  TH1F          **h1prCALPosAdcPulseTimeStarttimeDiff;
  TH2F          **h1prCALPosPulseAmpVsPulseTimeStarttimeDiff;

  TH1F          **h1prCALPosAdcPulseTimeStarttimeDiffMultCer;
  TH2F          **h1prCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer;


  TH1F          **h1prCALPosgoodAdcTdcDiffTimeMultCer;
  TH2F          **h1prCALgoodPosPulseAmpVsPulseTimeMultCer;

  //*******************added for HCAL 1pr neg*************


  TH1F          **h1prCALNegAdcPulseTimeStarttimeDiff;
  TH2F          **h1prCALNegPulseAmpVsPulseTimeStarttimeDiff;

  TH1F          **h1prCALNegAdcPulseTimeStarttimeDiffMultCer; 
  TH2F          **h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer;

  TH1F          **h1prCALNeggoodAdcTdcDiffTimeMultCer; 
  TH2F          **h1prCALgoodNegPulseAmpVsPulseTimeMultCer;


  //*************HCAL_2ta pos*********************
  TH1F          **h2taCALPosAdcPulseTimeStarttimeDiff;
  TH2F          **h2taCALPosPulseAmpVsPulseTimeStarttimeDiff;

  TH1F          **h2taCALPosAdcPulseTimeStarttimeDiffMultCer; 
  TH2F          **h2taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer;


  TH1F          **h2taCALPosgoodAdcTdcDiffTimeMultCer;
  TH2F          **h2taCALgoodPosPulseAmpVsPulseTimeMultCer;

 //*******************added for HCAL 2ta neg*************


  TH1F          **h2taCALNegAdcPulseTimeStarttimeDiff;
  TH2F          **h2taCALNegPulseAmpVsPulseTimeStarttimeDiff;

  TH1F          **h2taCALNegAdcPulseTimeStarttimeDiffMultCer; 
  TH2F          **h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer;

  TH1F          **h2taCALNeggoodAdcTdcDiffTimeMultCer; 
  TH2F          **h2taCALgoodNegPulseAmpVsPulseTimeMultCer;

  //********************2ta done *******************************
  //*****************HCAL 3ta pos*****************

 
  TH1F          **h3taCALPosAdcPulseTimeStarttimeDiff;
  TH2F          **h3taCALPosPulseAmpVsPulseTimeStarttimeDiff;

  TH1F          **h3taCALPosAdcPulseTimeStarttimeDiffMultCer; 
  TH2F          **h3taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer;


  TH1F          **h3taCALPosgoodAdcTdcDiffTimeMultCer;
  TH2F          **h3taCALgoodPosPulseAmpVsPulseTimeMultCer;


  //HCAL 3ta pos done ****there is no neg 3ta*******

  TH1F          **h4taCALPosAdcPulseTimeStarttimeDiff;
  TH2F          **h4taCALPosPulseAmpVsPulseTimeStarttimeDiff;

  TH1F          **h4taCALPosAdcPulseTimeStarttimeDiffMultCer; 
  TH2F          **h4taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer;


  TH1F          **h4taCALPosgoodAdcTdcDiffTimeMultCer;
  TH2F          **h4taCALgoodPosPulseAmpVsPulseTimeMultCer;




  //HCAL 4ta pos done****there is no neg 4ta*******









  //CAL//
  TH2F          **h1H1prCALNegPulseAmp;
  TH2F          **h1H1prCALPosPulseAmp;
  TH2F          **h1H2taCALNegPulseAmp;
  TH2F          **h1H2taCALPosPulseAmp;
  TH2F          **h1H3taCALNegPulseAmp;
  TH2F          **h1H3taCALPosPulseAmp;
  TH2F          **h1H4taCALNegPulseAmp;
  TH2F          **h1H4taCALPosPulseAmp;

  TH1F          **h1H1prCALNegPulseTime;
  TH1F          **h1H1prCALPosPulseTime;
  TH1F          **h1H2taCALNegPulseTime;
  TH1F          **h1H2taCALPosPulseTime;
  TH1F          **h1H3taCALNegPulseTime;
  TH1F          **h1H3taCALPosPulseTime;
  TH1F          **h1H4taCALNegPulseTime;
  TH1F          **h1H4taCALPosPulseTime;
   
  //HODO//1

  TH2F          **h1HHODO1xNegPulseAmp;
  TH2F          **h1HHODO1xPosPulseAmp;
  TH2F          **h1HHODO1yNegPulseAmp;
  TH2F          **h1HHODO1yPosPulseAmp;
  TH2F          **h1HHODO2xNegPulseAmp;
  TH2F          **h1HHODO2xPosPulseAmp;
  TH2F          **h1HHODO2yNegPulseAmp;
  TH2F          **h1HHODO2yPosPulseAmp;


  TH1F          **h1HHODO1xNegPulseTime;
  TH1F          **h1HHODO1xPosPulseTime;
  TH1F          **h1HHODO1yNegPulseTime;
  TH1F          **h1HHODO1yPosPulseTime;
  TH1F          **h1HHODO2xNegPulseTime;
  TH1F          **h1HHODO2xPosPulseTime;
  TH1F          **h1HHODO2yNegPulseTime;
  TH1F          **h1HHODO2yPosPulseTime;


  //*************added************
   TTreeReaderValue<Double_t> H_cer_npeSum = {fReader, "H.cer.npeSum"};

  TTreeReaderValue<Int_t> Ndata_H_cer_adcPulseAmp = {fReader, "Ndata.H.cer.adcPulseAmp"};
  TTreeReaderArray<Double_t> H_cer_goodAdcPulseAmp = {fReader, "H.cer.goodAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_cal_1pr_goodNegAdcMult = {fReader, "Ndata.H.cal.1pr.goodNegAdcMult"};
  TTreeReaderValue<Int_t> Ndata_H_cal_1pr_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.cal.1pr.goodNegAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> H_cal_1pr_goodNegAdcTdcDiffTime = {fReader, "H.cal.1pr.goodNegAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> H_cal_1pr_goodNegAdcPulseAmp = {fReader, "H.cal.1pr.goodNegAdcPulseAmp"};


  TTreeReaderValue<Int_t> Ndata_H_cal_1pr_goodPosAdcMult = {fReader, "Ndata.H.cal.1pr.goodPosAdcMult"};
  TTreeReaderValue<Int_t> Ndata_H_cal_1pr_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.cal.1pr.goodPosAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> H_cal_1pr_goodPosAdcPulseAmp = {fReader, "H.cal.1pr.goodPosAdcPulseAmp"};


  //************2ta pos****************
  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodPosAdcMult = {fReader, "Ndata.H.cal.2ta.goodPosAdcMult"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodPosAdcMult = {fReader, "H.cal.2ta.goodPosAdcMult"};

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodPosAdcPulseAmp = {fReader, "Ndata.H.cal.2ta.goodPosAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodPosAdcPulseAmp = {fReader, "H.cal.2ta.goodPosAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodPosAdcPulseTime = {fReader, "Ndata.H.cal.2ta.goodPosAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodPosAdcPulseTime = {fReader, "H.cal.2ta.goodPosAdcPulseTime"};

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.cal.2ta.goodPosAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.2ta.goodPosAdcTdcDiffTime"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_posAdcErrorFlag = {fReader, "Ndata.H.cal.2ta.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_cal_2ta_posAdcErrorFlag = {fReader, "H.cal.2ta.posAdcErrorFlag"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_posAdcPulseAmp = {fReader, "Ndata.H.cal.2ta.posAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_2ta_posAdcPulseAmp = {fReader, "H.cal.2ta.posAdcPulseAmp"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_posAdcPulseTime = {fReader, "Ndata.H.cal.2ta.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_2ta_posAdcPulseTime = {fReader, "H.cal.2ta.posAdcPulseTime"};
 
  TTreeReaderArray<Double_t> H_cal_2ta_posAdcCounter = {fReader, "H.cal.2ta.posAdcCounter"};


  //********2ta neg ****************

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodNegAdcMult = {fReader, "Ndata.H.cal.2ta.goodNegAdcMult"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodNegAdcMult = {fReader, "H.cal.2ta.goodNegAdcMult"};
   
  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodNegAdcPulseAmp = {fReader, "Ndata.H.cal.2ta.goodNegAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodNegAdcPulseAmp = {fReader, "H.cal.2ta.goodNegAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodNegAdcPulseTime = {fReader, "Ndata.H.cal.2ta.goodNegAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodNegAdcPulseTime = {fReader, "H.cal.2ta.goodNegAdcPulseTime"};

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.cal.2ta.goodNegAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> H_cal_2ta_goodNegAdcTdcDiffTime = {fReader, "H.cal.2ta.goodNegAdcTdcDiffTime"};
   
  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_negAdcErrorFlag = {fReader, "Ndata.H.cal.2ta.negAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_cal_2ta_negAdcErrorFlag = {fReader, "H.cal.2ta.negAdcErrorFlag"};

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_negAdcPulseAmp = {fReader, "Ndata.H.cal.2ta.negAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_2ta_negAdcPulseAmp = {fReader, "H.cal.2ta.negAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_cal_2ta_negAdcPulseTime = {fReader, "Ndata.H.cal.2ta.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_2ta_negAdcPulseTime = {fReader, "H.cal.2ta.negAdcPulseTime"};
   
  TTreeReaderArray<Double_t> H_cal_2ta_negAdcCounter = {fReader, "H.cal.2ta.negAdcCounter"};

   
  //*************added 2ta done done ************
  //***********3ta pos******************


 TTreeReaderValue<Int_t> Ndata_H_cal_3ta_goodPosAdcMult = {fReader, "Ndata.H.cal.3ta.goodPosAdcMult"};
  TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcMult = {fReader, "H.cal.3ta.goodPosAdcMult"};

  TTreeReaderValue<Int_t> Ndata_H_cal_3ta_goodPosAdcPulseAmp = {fReader, "Ndata.H.cal.3ta.goodPosAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcPulseAmp = {fReader, "H.cal.3ta.goodPosAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_cal_3ta_goodPosAdcPulseTime = {fReader, "Ndata.H.cal.3ta.goodPosAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcPulseTime = {fReader, "H.cal.3ta.goodPosAdcPulseTime"};

  TTreeReaderValue<Int_t> Ndata_H_cal_3ta_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.cal.3ta.goodPosAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.3ta.goodPosAdcTdcDiffTime"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_3ta_posAdcErrorFlag = {fReader, "Ndata.H.cal.3ta.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_cal_3ta_posAdcErrorFlag = {fReader, "H.cal.3ta.posAdcErrorFlag"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_3ta_posAdcPulseAmp = {fReader, "Ndata.H.cal.3ta.posAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_3ta_posAdcPulseAmp = {fReader, "H.cal.3ta.posAdcPulseAmp"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_3ta_posAdcPulseTime = {fReader, "Ndata.H.cal.3ta.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_3ta_posAdcPulseTime = {fReader, "H.cal.3ta.posAdcPulseTime"};
 
  TTreeReaderArray<Double_t> H_cal_3ta_posAdcCounter = {fReader, "H.cal.3ta.posAdcCounter"};




  //*********3ta done**************
  //*********4ta pos******************



 TTreeReaderValue<Int_t> Ndata_H_cal_4ta_goodPosAdcMult = {fReader, "Ndata.H.cal.4ta.goodPosAdcMult"};
  TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcMult = {fReader, "H.cal.4ta.goodPosAdcMult"};

  TTreeReaderValue<Int_t> Ndata_H_cal_4ta_goodPosAdcPulseAmp = {fReader, "Ndata.H.cal.4ta.goodPosAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcPulseAmp = {fReader, "H.cal.4ta.goodPosAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_cal_4ta_goodPosAdcPulseTime = {fReader, "Ndata.H.cal.4ta.goodPosAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcPulseTime = {fReader, "H.cal.4ta.goodPosAdcPulseTime"};

  TTreeReaderValue<Int_t> Ndata_H_cal_4ta_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.cal.4ta.goodPosAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.4ta.goodPosAdcTdcDiffTime"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_4ta_posAdcErrorFlag = {fReader, "Ndata.H.cal.4ta.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_cal_4ta_posAdcErrorFlag = {fReader, "H.cal.4ta.posAdcErrorFlag"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_4ta_posAdcPulseAmp = {fReader, "Ndata.H.cal.4ta.posAdcPulseAmp"};
  TTreeReaderArray<Double_t> H_cal_4ta_posAdcPulseAmp = {fReader, "H.cal.4ta.posAdcPulseAmp"};
  
  TTreeReaderValue<Int_t> Ndata_H_cal_4ta_posAdcPulseTime = {fReader, "Ndata.H.cal.4ta.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_cal_4ta_posAdcPulseTime = {fReader, "H.cal.4ta.posAdcPulseTime"};
 
  TTreeReaderArray<Double_t> H_cal_4ta_posAdcCounter = {fReader, "H.cal.4ta.posAdcCounter"};





  //************4ta CAL  done


  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<Int_t> Ndata_H_cer_adcPulseTime = {fReader, "Ndata.H.cer.adcPulseTime"};
  TTreeReaderArray<Double_t> H_cer_adcCounter = {fReader, "H.cer.adcCounter"};
  TTreeReaderArray<Double_t> H_cer_adcErrorFlag = {fReader, "H.cer.adcErrorFlag"};
  TTreeReaderArray<Double_t> H_cer_adcPulseTime = {fReader, "H.cer.adcPulseTime"};
  TTreeReaderArray<Double_t> H_cer_adcPulseAmp = {fReader, "H.cer.adcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_1prcal_negAdcPulseTime = {fReader, "Ndata.H.cal.1pr.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_1prcal_negAdcCounter = {fReader, "H.cal.1pr.negAdcCounter"};
  TTreeReaderArray<Double_t> H_1prcal_negAdcErrorFlag = {fReader, "H.cal.1pr.negAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_1prcal_negAdcPulseTime = {fReader, "H.cal.1pr.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_1prcal_negAdcPulseAmp = {fReader, "H.cal.1pr.negAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_1prcal_posAdcPulseTime = {fReader, "Ndata.H.cal.1pr.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_1prcal_posAdcCounter = {fReader, "H.cal.1pr.posAdcCounter"};
  TTreeReaderArray<Double_t> H_1prcal_posAdcErrorFlag = {fReader, "H.cal.1pr.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_1prcal_posAdcPulseTime = {fReader, "H.cal.1pr.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_1prcal_posAdcPulseAmp = {fReader, "H.cal.1pr.posAdcPulseAmp"};

  /* TTreeReaderValue<Int_t> Ndata_H_2tacal_negAdcPulseTime = {fReader, "Ndata.H.cal.2ta.negAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_negAdcCounter = {fReader, "H.cal.2ta.negAdcCounter"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_negAdcErrorFlag = {fReader, "H.cal.2ta.negAdcErrorFlag"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_negAdcPulseTime = {fReader, "H.cal.2ta.negAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_negAdcPulseAmp = {fReader, "H.cal.2ta.negAdcPulseAmp"}; */

  /* TTreeReaderValue<Int_t> Ndata_H_2tacal_posAdcPulseTime = {fReader, "Ndata.H.cal.2ta.posAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_posAdcCounter = {fReader, "H.cal.2ta.posAdcCounter"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_posAdcErrorFlag = {fReader, "H.cal.2ta.posAdcErrorFlag"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_posAdcPulseTime = {fReader, "H.cal.2ta.posAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_2tacal_posAdcPulseAmp = {fReader, "H.cal.2ta.posAdcPulseAmp"}; */

  /* TTreeReaderValue<Int_t> Ndata_H_3tacal_negAdcPulseTime = {fReader, "Ndata.H.cal.3ta.negAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_negAdcCounter = {fReader, "H.cal.3ta.negAdcCounter"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_negAdcErrorFlag = {fReader, "H.cal.3ta.negAdcErrorFlag"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_negAdcPulseTime = {fReader, "H.cal.3ta.negAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_negAdcPulseAmp = {fReader, "H.cal.3ta.negAdcPulseAmp"}; */

  /* TTreeReaderValue<Int_t> Ndata_H_3tacal_posAdcPulseTime = {fReader, "Ndata.H.cal.3ta.posAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_posAdcCounter = {fReader, "H.cal.3ta.posAdcCounter"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_posAdcErrorFlag = {fReader, "H.cal.3ta.posAdcErrorFlag"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_posAdcPulseTime = {fReader, "H.cal.3ta.posAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_3tacal_posAdcPulseAmp = {fReader, "H.cal.3ta.posAdcPulseAmp"}; */

  /* TTreeReaderValue<Int_t> Ndata_H_4tacal_negAdcPulseTime = {fReader, "Ndata.H.cal.4ta.negAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_negAdcCounter = {fReader, "H.cal.4ta.negAdcCounter"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_negAdcErrorFlag = {fReader, "H.cal.4ta.negAdcErrorFlag"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_negAdcPulseTime = {fReader, "H.cal.4ta.negAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_negAdcPulseAmp = {fReader, "H.cal.4ta.negAdcPulseAmp"}; */

  /* TTreeReaderValue<Int_t> Ndata_H_4tacal_posAdcPulseTime = {fReader, "Ndata.H.cal.4ta.posAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_posAdcCounter = {fReader, "H.cal.4ta.posAdcCounter"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_posAdcErrorFlag = {fReader, "H.cal.4ta.posAdcErrorFlag"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_posAdcPulseTime = {fReader, "H.cal.4ta.posAdcPulseTime"}; */
  /* TTreeReaderArray<Double_t> H_4tacal_posAdcPulseAmp = {fReader, "H.cal.4ta.posAdcPulseAmp"}; */

  TTreeReaderValue<Int_t> Ndata_H_dc_1u1_time = {fReader, "Ndata.H.dc.1u1.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_1u1_rawtdc = {fReader, "H.dc.1u1.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_1u2_rawtdc = {fReader, "H.dc.1u2.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_1v1_rawtdc = {fReader, "H.dc.1v1.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_1v2_rawtdc = {fReader, "H.dc.1v2.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_1x1_rawtdc = {fReader, "H.dc.1x1.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_1x2_rawtdc = {fReader, "H.dc.1x2.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_2u1_rawtdc = {fReader, "H.dc.2u1.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_2u2_rawtdc = {fReader, "H.dc.2u2.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_2v1_rawtdc = {fReader, "H.dc.2v1.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_2v2_rawtdc = {fReader, "H.dc.2v2.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_2x1_rawtdc = {fReader, "H.dc.2x1.rawtdc"};
  TTreeReaderArray<Double_t> H_dc_2x2_rawtdc = {fReader, "H.dc.2x2.rawtdc"};

  TTreeReaderValue<Int_t> Ndata_H_hod_1x_negAdcPulseTime = {fReader, "Ndata.H.hod.1x.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1x_negAdcCounter = {fReader, "H.hod.1x.negAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_1x_negAdcErrorFlag = {fReader, "H.hod.1x.negAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_1x_negAdcPulseTime = {fReader, "H.hod.1x.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1x_negAdcPulseAmp = {fReader, "H.hod.1x.negAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_hod_1y_negAdcPulseTime = {fReader, "Ndata.H.hod.1y.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1y_negAdcCounter = {fReader, "H.hod.1y.negAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_1y_negAdcErrorFlag = {fReader, "H.hod.1y.negAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_1y_negAdcPulseTime = {fReader, "H.hod.1y.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1y_negAdcPulseAmp = {fReader, "H.hod.1y.negAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_hod_2x_negAdcPulseTime = {fReader, "Ndata.H.hod.2x.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2x_negAdcCounter = {fReader, "H.hod.2x.negAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_2x_negAdcErrorFlag = {fReader, "H.hod.2x.negAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_2x_negAdcPulseTime = {fReader, "H.hod.2x.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2x_negAdcPulseAmp = {fReader, "H.hod.2x.negAdcPulseAmp"}; 

  TTreeReaderValue<Int_t> Ndata_H_hod_2y_negAdcPulseTime = {fReader, "Ndata.H.hod.2y.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2y_negAdcCounter = {fReader, "H.hod.2y.negAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_2y_negAdcErrorFlag = {fReader, "H.hod.2y.negAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_2y_negAdcPulseTime = {fReader, "H.hod.2y.negAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2y_negAdcPulseAmp = {fReader, "H.hod.2y.negAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_hod_1x_posAdcPulseTime = {fReader, "Ndata.H.hod.1x.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1x_posAdcCounter = {fReader, "H.hod.1x.posAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_1x_posAdcErrorFlag = {fReader, "H.hod.1x.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_1x_posAdcPulseTime = {fReader, "H.hod.1x.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1x_posAdcPulseAmp = {fReader, "H.hod.1x.posAdcPulseAmp"}; 

  TTreeReaderValue<Int_t> Ndata_H_hod_1y_posAdcPulseTime = {fReader, "Ndata.H.hod.1y.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1y_posAdcCounter = {fReader, "H.hod.1y.posAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_1y_posAdcErrorFlag = {fReader, "H.hod.1y.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_1y_posAdcPulseTime = {fReader, "H.hod.1y.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_1y_posAdcPulseAmp = {fReader, "H.hod.1y.posAdcPulseAmp"}; 

  TTreeReaderValue<Int_t> Ndata_H_hod_2x_posAdcPulseTime = {fReader, "Ndata.H.hod.2x.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2x_posAdcCounter = {fReader, "H.hod.2x.posAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_2x_posAdcErrorFlag = {fReader, "H.hod.2x.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_2x_posAdcPulseTime = {fReader, "H.hod.2x.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2x_posAdcPulseAmp = {fReader, "H.hod.2x.posAdcPulseAmp"};

  TTreeReaderValue<Int_t> Ndata_H_hod_2y_posAdcPulseTime = {fReader, "Ndata.H.hod.2y.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2y_posAdcCounter = {fReader, "H.hod.2y.posAdcCounter"};
  TTreeReaderArray<Double_t> H_hod_2y_posAdcErrorFlag = {fReader, "H.hod.2y.posAdcErrorFlag"};
  TTreeReaderArray<Double_t> H_hod_2y_posAdcPulseTime = {fReader, "H.hod.2y.posAdcPulseTime"};
  TTreeReaderArray<Double_t> H_hod_2y_posAdcPulseAmp = {fReader, "H.hod.2y.posAdcPulseAmp"};   

  TTreeReaderValue<Double_t> H_hod_starttime = {fReader, "H.hod.starttime"};
  TTreeReaderValue<Double_t> H_cal_etottracknorm = {fReader, "H.cal.etottracknorm"};

  //// AdcTdcDiffTime branches define here
  TTreeReaderValue<Int_t> Ndata_H_cer_goodAdcTdcDiffTime = {fReader, "Ndata.H.cer.goodAdcTdcDiffTime"}; // change 2 
  TTreeReaderArray<Double_t> H_cer_goodAdcTdcDiffTime = {fReader, "H.cer.goodAdcTdcDiffTime"}; // change 2

  // TTreeReaderArray<Double_t> H_cal_1pr_goodNegAdcTdcDiffTime = {fReader, "H.cal.1pr.goodNegAdcTdcDiffTime"};

  // TTreeReaderValue<Int_t> Ndata_H_cal_1pr_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.cal.1pr.goodPosAdcTdcDiffTime"}; 
  TTreeReaderArray<Double_t> H_cal_1pr_goodPosAdcTdcDiffTime = {fReader, "H.cal.1pr.goodPosAdcTdcDiffTime"};

 
  /* TTreeReaderValue<Int_t> Ndata_H_cal_3ta_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.cal.3ta.goodNegAdcTdcDiffTime"};  */
  /* TTreeReaderArray<Double_t> H_cal_3ta_goodNegAdcTdcDiffTime = {fReader, "H.cal.3ta.goodNegAdcTdcDiffTime"}; */
   
  /* TTreeReaderValue<Int_t> Ndata_H_cal_3ta_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.cal.3ta.goodPosAdcTdcDiffTime"};  */
  /* TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.3ta.goodPosAdcTdcDiffTime"}; */

  /* TTreeReaderValue<Int_t> Ndata_H_cal_4ta_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.cal.4ta.goodNegAdcTdcDiffTime"};  */
  /* TTreeReaderArray<Double_t> H_cal_4ta_goodNegAdcTdcDiffTime = {fReader, "H.cal.4ta.goodNegAdcTdcDiffTime"}; */
   
  /* TTreeReaderValue<Int_t> Ndata_H_cal_4ta_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.cal.4ta.goodPosAdcTdcDiffTime"};  */
  /* TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.4ta.goodPosAdcTdcDiffTime"}; */

  // HODO
  TTreeReaderValue<Int_t> Ndata_H_hod_1x_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.hod.1x.GoodNegAdcTdcDiffTime"}; 
  TTreeReaderArray<Double_t> H_hod_1x_goodNegAdcTdcDiffTime = {fReader, "H.hod.1x.GoodNegAdcTdcDiffTime"};
   
  TTreeReaderValue<Int_t> Ndata_H_hod_1x_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.hod.1x.GoodPosAdcTdcDiffTime"}; 
  TTreeReaderArray<Double_t> H_hod_1x_goodPosAdcTdcDiffTime = {fReader, "H.hod.1x.GoodPosAdcTdcDiffTime"};

  TTreeReaderValue<Int_t> Ndata_H_hod_1y_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.hod.1y.GoodNegAdcTdcDiffTime"};   
  TTreeReaderArray<Double_t> H_hod_1y_goodNegAdcTdcDiffTime = {fReader, "H.hod.1y.GoodNegAdcTdcDiffTime"};
   
  TTreeReaderValue<Int_t> Ndata_H_hod_1y_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.hod.1y.GoodPosAdcTdcDiffTime"}; 
  TTreeReaderArray<Double_t> H_hod_1y_goodPosAdcTdcDiffTime = {fReader, "H.hod.1y.GoodPosAdcTdcDiffTime"};

  TTreeReaderValue<Int_t> Ndata_H_hod_2x_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.hod.2x.GoodNegAdcTdcDiffTime"}; 
  TTreeReaderArray<Double_t> H_hod_2x_goodNegAdcTdcDiffTime = {fReader, "H.hod.2x.GoodNegAdcTdcDiffTime"};

  TTreeReaderValue<Int_t> Ndata_H_hod_2x_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.hod.2x.GoodPosAdcTdcDiffTime"}; 
  TTreeReaderArray<Double_t> H_hod_2x_goodPosAdcTdcDiffTime = {fReader, "H.hod.2x.GoodPosAdcTdcDiffTime"};

  TTreeReaderValue<Int_t> Ndata_H_hod_2y_goodNegAdcTdcDiffTime = {fReader, "Ndata.H.hod.2y.GoodNegAdcTdcDiffTime"};   
  TTreeReaderArray<Double_t> H_hod_2y_goodNegAdcTdcDiffTime = {fReader, "H.hod.2y.GoodNegAdcTdcDiffTime"};
   
  TTreeReaderValue<Int_t> Ndata_H_hod_2y_goodPosAdcTdcDiffTime = {fReader, "Ndata.H.hod.2y.GoodPosAdcTdcDiffTime"};  
  TTreeReaderArray<Double_t> H_hod_2y_goodPosAdcTdcDiffTime = {fReader, "H.hod.2y.GoodPosAdcTdcDiffTime"};

  //Multiplicity branches define here //
  TTreeReaderArray<Double_t> H_cer_goodAdcMult = {fReader, "H.cer.goodAdcMult"};
  TTreeReaderArray<Double_t> H_cal_1pr_goodNegAdcMult = {fReader, "H.cal.1pr.goodNegAdcMult"};
  TTreeReaderArray<Double_t> H_cal_1pr_goodPosAdcMult = {fReader, "H.cal.1pr.goodPosAdcMult"};
  /* TTreeReaderArray<Double_t> H_cal_2ta_goodNegAdcMult = {fReader, "H.cal.2ta.goodNegAdcMult"}; */
  /* TTreeReaderArray<Double_t> H_cal_2ta_goodPosAdcMult = {fReader, "H.cal.2ta.goodPosAdcMult"}; */
  /* TTreeReaderArray<Double_t> H_cal_3ta_goodNegAdcMult = {fReader, "H.cal.3ta.goodNegAdcMult"}; */
  /* TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcMult = {fReader, "H.cal.3ta.goodPosAdcMult"}; */
  /* TTreeReaderArray<Double_t> H_cal_4ta_goodNegAdcMult = {fReader, "H.cal.4ta.goodNegAdcMult"}; */
  /* TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcMult = {fReader, "H.cal.4ta.goodPosAdcMult"}; */
  TTreeReaderArray<Double_t> H_hod_1x_goodNegAdcMult = {fReader, "H.hod.1x.GoodNegAdcMult"};
  TTreeReaderArray<Double_t> H_hod_1x_goodPosAdcMult = {fReader, "H.hod.1x.GoodPosAdcMult"};
  TTreeReaderArray<Double_t> H_hod_1y_goodNegAdcMult = {fReader, "H.hod.1y.GoodNegAdcMult"};
  TTreeReaderArray<Double_t> H_hod_1y_goodPosAdcMult = {fReader, "H.hod.1y.GoodPosAdcMult"};
  TTreeReaderArray<Double_t> H_hod_2x_goodNegAdcMult = {fReader, "H.hod.2x.GoodNegAdcMult"};
  TTreeReaderArray<Double_t> H_hod_2x_goodPosAdcMult = {fReader, "H.hod.2x.GoodPosAdcMult"};
  TTreeReaderArray<Double_t> H_hod_2y_goodNegAdcMult = {fReader, "H.hod.2y.GoodNegAdcMult"};
  TTreeReaderArray<Double_t> H_hod_2y_goodPosAdcMult = {fReader, "H.hod.2y.GoodPosAdcMult"};
   
  HMSADCGates(TTree * /*tree*/ =0) {h1HCERPulseAmp=0,h1H1prCALNegPulseAmp=0,h1H1prCALPosPulseAmp=0,h1H2taCALNegPulseAmp=0,h1H2taCALPosPulseAmp=0,h1H3taCALNegPulseAmp=0,h1H3taCALPosPulseAmp=0,h1H4taCALNegPulseAmp=0,h1H4taCALPosPulseAmp=0,h1HDCRawTdc=0,h1HHODO1xNegPulseAmp=0,h1HHODO1xPosPulseAmp=0,h1HHODO1yNegPulseAmp=0,h1HHODO1yPosPulseAmp=0,h1HHODO2xNegPulseAmp=0,h1HHODO2xPosPulseAmp=0,h1HHODO2yNegPulseAmp=0,h1HHODO2yPosPulseAmp=0,h1HDCRawTdc=0, h1HCERAdcPulseTime=0,h1H1prCALNegPulseTime=0,h1H1prCALPosPulseTime=0,h1H2taCALNegPulseTime=0,h1H2taCALPosPulseTime=0,h1H3taCALNegPulseTime=0,h1H3taCALPosPulseTime=0,h1H4taCALNegPulseTime=0,h1H4taCALPosPulseTime=0,h1HHODO1xNegPulseTime=0,h1HHODO1xPosPulseTime=0,h1HHODO1yNegPulseTime=0,h1HHODO1yPosPulseTime=0,h1HHODO2xNegPulseTime=0,h1HHODO2xPosPulseTime=0,h1HHODO2yNegPulseTime=0,h1HHODO2yPosPulseTime=0;}
  virtual ~HMSADCGates() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();

  ClassDef(HMSADCGates,0);

};

#endif

#ifdef HMSADCGates_cxx
void HMSADCGates::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t HMSADCGates::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef HMSADCGates_cxx
