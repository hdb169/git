#define HMSADCGates_cxx
// The class definition in HMSADCGates.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("HMSADCGates.C")
// root> T->Process("HMSADCGates.C","some options")
// root> T->Process("HMSADCGates.C+")
//


#include "HMSADCGates.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>

void HMSADCGates::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

   
  Info("Begin", "Starting HMS Detector ADC Timing Window Script");
}

void HMSADCGates::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  // // h1HCERPulseAmp = new TH2F*[2]; 
  // // h1HCERAdcPulseTime = new TH1F*[2];

  h1HCERAdcPulseTimeStarttimeDiff = new TH1F*[2];
  h1HCERPulseAmpVsPulseTimeStarttimeDiff = new TH2F*[2];
  h1HCERAdcPulseTimeStarttimeDiffMultCal = new TH1F*[2];
  h1HCERPulseAmpVsPulseTimeStarttimeDiffMultCal = new TH2F*[2];
  h1HCERGoodAdcTdcTimeDiffMultCal = new TH1F*[2];
  h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal = new TH2F*[2];

  for (Int_t ipmt=0; ipmt<2; ipmt++)  {
   

    h1HCERAdcPulseTimeStarttimeDiff[ipmt] = new TH1F(Form(" h1HCERAdcPulseTimeStarttimeDiff%d",ipmt+1),Form("ADC Pulse Time PMT%d; -H_cer_adcPulseTime + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);

    h1HCERPulseAmpVsPulseTimeStarttimeDiff[ipmt] = new TH2F(Form(" h1HCERPulseAmpVsPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Amp Vs Pulse Time PMT%d; -H_cer_adcPulseTime + H_hod_starttime (ns); H_cer_adcPulseAmp ",ipmt+1),600,-400,400,600,0,600);
   
    h1HCERAdcPulseTimeStarttimeDiffMultCal[ipmt] = new TH1F(Form(" h1HCERAdcPulseTimeStarttimeDiffMultCal%d",ipmt+1),Form("ADC Pulse Time Mult Cal cut PMT%d; -H_cer_adcPulseTime + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);

    h1HCERPulseAmpVsPulseTimeStarttimeDiffMultCal[ipmt] = new TH2F(Form(" h1HCERPulseAmpVsPulseTimeStarttimeDiffMultCal%d",ipmt+1),Form("Pulse Amp Vs Pulse Time Mult cal cut PMT%d; -H_cer_adcPulseTime + H_hod_starttime (ns); H_cer_adcPulseAmp ",ipmt+1),600,-400,400,600,0,600);
  
    h1HCERGoodAdcTdcTimeDiffMultCal[ipmt] = new TH1F(Form("h1HCERGoodAdcTdcTimeDiffMultCal%d",ipmt+1),Form("Good ADC TDC Time Diff PMT%d; H_cer_goodAdcTdcDiffTime (ns); Counts",ipmt+1),600,-400,400);
    
    h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal[ipmt] = new TH2F(Form(" h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal%d",ipmt+1),Form("ADC Pulse Time Vs Good AdcTdc Time Diff Mult Cal cut PMT%d; H_cer_goodAdcTdcDiffTime (ns); H_Cer_goodAdcPulseAmp",ipmt+1), 600,-400, 400, 600, 0, 600);


    GetOutputList()->Add(h1HCERAdcPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h1HCERPulseAmpVsPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h1HCERAdcPulseTimeStarttimeDiffMultCal[ipmt]); 
    GetOutputList()->Add(h1HCERPulseAmpVsPulseTimeStarttimeDiffMultCal[ipmt]); 
    GetOutputList()->Add(h1HCERGoodAdcTdcTimeDiffMultCal[ipmt]); 
    GetOutputList()->Add(h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal[ipmt]);



  }
 
  
  h1prCALPosAdcPulseTimeStarttimeDiff = new TH1F*[13];
  h1prCALPosPulseAmpVsPulseTimeStarttimeDiff = new TH2F*[13];

  h1prCALPosAdcPulseTimeStarttimeDiffMultCer = new TH1F*[13];
  h1prCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer = new TH2F*[13];

  h1prCALPosgoodAdcTdcDiffTimeMultCer = new TH1F*[13];
  h1prCALgoodPosPulseAmpVsPulseTimeMultCer= new TH2F*[13];

  h1prCALNegAdcPulseTimeStarttimeDiff = new TH1F*[13];
  h1prCALNegPulseAmpVsPulseTimeStarttimeDiff = new TH2F*[13];

  h1prCALNegAdcPulseTimeStarttimeDiffMultCer = new TH1F*[13];
  h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer = new TH2F*[13];

  h1prCALNeggoodAdcTdcDiffTimeMultCer = new TH1F*[13];
  h1prCALgoodNegPulseAmpVsPulseTimeMultCer = new TH2F*[13];


  for (Int_t ipmt=0; ipmt<13; ipmt++)  {

    h1prCALPosAdcPulseTimeStarttimeDiff[ipmt] = new TH1F(Form(" h1prCALPosAdcPulseTimeStarttimeDiff%d",ipmt+1),Form("HCAL 1pr Pos ADC Pulse Time PMT%d; -H_1prcal_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h1prCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt] = new TH2F(Form("h1prCALPosPulseAmpVsPulseTime%d",ipmt+1),Form("HCAL 1pr Pulse Amp Vs Pulse Time PMT%d;  -H_1prcal_posAdcPulseTime  + H_hod_starttime  (ns); H_1prcal_posAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h1prCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt] = new TH1F(Form(" h1prCALPosAdcPulseTimeStarttimeDiffMultCer%d",ipmt+1),Form("HCAL 1pr Pos ADC Pulse Time Mult Cer PMT%d; -H_1prcal_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h1prCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt] = new TH2F(Form("h1prCALPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 1pr Pulse Amp Vs Pulse Time Mult Cer PMT%d;  -H_1prcal_posAdcPulseTime  + H_hod_starttime  (ns); H_1prcal_posAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt] = new TH1F(Form("h1prCALPosgoodAdcTdcDiffTimeMultCer%d",ipmt+1),Form("HCAL 1pr Good Pos ADC TDC TIME DIFF Mult Cer PMT%d;H_cal_1pr_goodPosAdcTdcDiffTime ; Counts",ipmt+1),600,-400,400);
    h1prCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt] = new TH2F(Form("h1prCALgoodPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 1pr Good Pulse Amp Vs good ADC TDC TIME DIFF Mult Cer PMT%d; H_cal_1pr_goodPosAdcTdcDiffTime (ns); H_cal_1pr_goodPosAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);

    h1prCALNegAdcPulseTimeStarttimeDiff[ipmt] = new TH1F(Form(" h1prCALNegAdcPulseTimeStarttimeDiff%d",ipmt+1),Form("HCAL 1pr Neg ADC Pulse Time PMT%d; -H_1prcal_negAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h1prCALNegPulseAmpVsPulseTimeStarttimeDiff[ipmt] = new TH2F(Form("h1prCALNegPulseAmpVsPulseTime%d",ipmt+1),Form("HCAL 1pr Pulse Amp Vs Pulse Time PMT%d;  -H_1prcal_negAdcPulseTime  + H_hod_starttime  (ns); H_1prcal_negAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h1prCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt] = new TH1F(Form(" h1prCALNegAdcPulseTimeStarttimeDiffMultCer%d",ipmt+1),Form("HCAL 1pr Neg ADC Pulse Time Mult Cer PMT%d; -H_1prcal_negAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt] = new TH2F(Form("h1prCALNegPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 1pr Pulse Amp Vs Pulse Time Mult Cer PMT%d;  -H_1prcal_negAdcPulseTime  + H_hod_starttime  (ns); H_1prcal_negAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt] = new TH1F(Form("h1prCALNeggoodAdcTdcDiffTimeMultCer%d",ipmt+1),Form("HCAL 1pr Good Neg ADC TDC TIME DIFF Mult Cer PMT%d;H_cal_1pr_goodNegAdcTdcDiffTime ; Counts",ipmt+1),600,-400,400);
    h1prCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt] = new TH2F(Form("h1prCALgoodNegPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 1pr Good Pulse Amp Vs good ADC TDC TIME DIFF Mult Cer PMT%d; H_cal_1pr_goodNegAdcTdcDiffTime (ns); H_cal_1pr_goodNegAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);



    GetOutputList()->Add(h1prCALNegAdcPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h1prCALPosAdcPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h1prCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h1prCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]);
    GetOutputList()->Add(h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt]);
    GetOutputList()->Add(h1prCALNegPulseAmpVsPulseTimeStarttimeDiff[ipmt]);
    GetOutputList()->Add(h1prCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h1prCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h1prCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]);
    GetOutputList()->Add(h1prCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt]);

  }

  //***********2ta****************


  h2taCALPosAdcPulseTimeStarttimeDiff = new TH1F*[13];
  h2taCALPosPulseAmpVsPulseTimeStarttimeDiff = new TH2F*[13];

  h2taCALPosAdcPulseTimeStarttimeDiffMultCer = new TH1F*[13];
  h2taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer = new TH2F*[13];

  h2taCALPosgoodAdcTdcDiffTimeMultCer = new TH1F*[13];
  h2taCALgoodPosPulseAmpVsPulseTimeMultCer= new TH2F*[13];

  h2taCALNegAdcPulseTimeStarttimeDiff = new TH1F*[13];
  h2taCALNegPulseAmpVsPulseTimeStarttimeDiff = new TH2F*[13];

  h2taCALNegAdcPulseTimeStarttimeDiffMultCer = new TH1F*[13];
  h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer = new TH2F*[13];

  h2taCALNeggoodAdcTdcDiffTimeMultCer = new TH1F*[13];
  h2taCALgoodNegPulseAmpVsPulseTimeMultCer = new TH2F*[13];

  for (Int_t ipmt=0; ipmt<13; ipmt++)  {

    h2taCALPosAdcPulseTimeStarttimeDiff[ipmt] = new TH1F(Form(" h2taCALPosAdcPulseTimeStarttimeDiff%d",ipmt+1),Form("HCAL 2ta Pos ADC Pulse Time PMT%d; -H_cal_2ta_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h2taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt] = new TH2F(Form("h2taCALPosPulseAmpVsPulseTime%d",ipmt+1),Form("HCAL 2ta Pulse Amp Vs Pulse Time PMT%d;  -H_cal_2ta_posAdcPulseTime  + H_hod_starttime  (ns);   H_cal_2ta_posAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);

    h2taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt] = new TH1F(Form(" h2taCALPosAdcPulseTimeStarttimeDiffMultCer%d",ipmt+1),Form("HCAL 2ta Pos ADC Pulse Time Mult Cer PMT%d; -H_cal_2ta_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h2taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt] = new TH2F(Form("h2taCALPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 2ta Pulse Amp Vs Pulse Time Mult Cer PMT%d;  -H_cal_2ta_posAdcPulseTime  + H_hod_starttime  (ns); H_cal_2ta_posAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt] = new TH1F(Form("h2taCALPosgoodAdcTdcDiffTimeMultCer%d",ipmt+1),Form("HCAL 2ta Good Pos ADC TDC TIME DIFF Mult Cer PMT%d;H_cal_2ta_goodPosAdcTdcDiffTime ; Counts",ipmt+1),600,-400,400);
    h2taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt] = new TH2F(Form("h2taCALgoodPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 2ta Good Pulse Amp Vs good ADC TDC TIME DIFF Mult Cer PMT%d; H_cal_2ta_goodPosAdcTdcDiffTime (ns); H_cal_2ta_goodPosAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);

    h2taCALNegAdcPulseTimeStarttimeDiff[ipmt] = new TH1F(Form(" h2taCALNegAdcPulseTimeStarttimeDiff%d",ipmt+1),Form("HCAL 2ta Neg ADC Pulse Time PMT%d; -H_cal_2ta_negAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h2taCALNegPulseAmpVsPulseTimeStarttimeDiff[ipmt] = new TH2F(Form("h2taCALNegPulseAmpVsPulseTime%d",ipmt+1),Form("HCAL 2ta Pulse Amp Vs Pulse Time PMT%d;  -H_cal_2ta_negAdcPulseTime  + H_hod_starttime  (ns); H_cal_2ta_negAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h2taCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt] = new TH1F(Form(" h2taCALNegAdcPulseTimeStarttimeDiffMultCer%d",ipmt+1),Form("HCAL 2ta Neg ADC Pulse Time Mult Cer PMT%d; -H_cal_2ta_negAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt] = new TH2F(Form("h2taCALNegPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 2ta Pulse Amp Vs Pulse Time Mult Cer PMT%d;  -H_cal_2ta_negAdcPulseTime  + H_hod_starttime  (ns); H_cal_2ta_negAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt] = new TH1F(Form("h2taCALNeggoodAdcTdcDiffTimeMultCer%d",ipmt+1),Form("HCAL 2ta Good Neg ADC TDC TIME DIFF Mult Cer PMT%d;H_cal_2ta_goodNegAdcTdcDiffTime ; Counts",ipmt+1),600,-400,400);
    h2taCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt] = new TH2F(Form("h2taCALgoodNegPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 2ta Good Pulse Amp Vs good ADC TDC TIME DIFF Mult Cer PMT%d; H_cal_2ta_goodNegAdcTdcDiffTime (ns); H_cal_2ta_goodNegAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);



    GetOutputList()->Add(h2taCALNegAdcPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h2taCALPosAdcPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h2taCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h2taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]);
    GetOutputList()->Add(h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]);
    GetOutputList()->Add(h2taCALNegPulseAmpVsPulseTimeStarttimeDiff[ipmt]);
    GetOutputList()->Add(h2taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h2taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h2taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]);
    GetOutputList()->Add(h2taCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt]);

  }



  //************2ta done***********
  //*************3ta pos***************
  h3taCALPosAdcPulseTimeStarttimeDiff = new TH1F*[13];
  h3taCALPosPulseAmpVsPulseTimeStarttimeDiff = new TH2F*[13];

  h3taCALPosAdcPulseTimeStarttimeDiffMultCer = new TH1F*[13];
  h3taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer = new TH2F*[13];

  h3taCALPosgoodAdcTdcDiffTimeMultCer = new TH1F*[13];
  h3taCALgoodPosPulseAmpVsPulseTimeMultCer= new TH2F*[13];
  for (Int_t ipmt=0; ipmt<13; ipmt++)  {

    h3taCALPosAdcPulseTimeStarttimeDiff[ipmt] = new TH1F(Form(" h3taCALPosAdcPulseTimeStarttimeDiff%d",ipmt+1),Form("HCAL 3ta Pos ADC Pulse Time PMT%d; -H_cal_3ta_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h3taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt] = new TH2F(Form("h3taCALPosPulseAmpVsPulseTime%d",ipmt+1),Form("HCAL 3ta Pulse Amp Vs Pulse Time PMT%d;  -H_cal_3ta_posAdcPulseTime  + H_hod_starttime  (ns);   H_cal_3ta_posAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);

    h3taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt] = new TH1F(Form(" h3taCALPosAdcPulseTimeStarttimeDiffMultCer%d",ipmt+1),Form("HCAL 3ta Pos ADC Pulse Time Mult Cer PMT%d; -H_cal_3ta_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h3taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt] = new TH2F(Form("h3taCALPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 3ta Pulse Amp Vs Pulse Time Mult Cer PMT%d;  -H_cal_3ta_posAdcPulseTime  + H_hod_starttime  (ns); H_cal_3ta_posAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt] = new TH1F(Form("h3taCALPosgoodAdcTdcDiffTimeMultCer%d",ipmt+1),Form("HCAL 3ta Good Pos ADC TDC TIME DIFF Mult Cer PMT%d;H_cal_3ta_goodPosAdcTdcDiffTime ; Counts",ipmt+1),600,-400,400);
    h3taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt] = new TH2F(Form("h3taCALgoodPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 3ta Good Pulse Amp Vs good ADC TDC TIME DIFF Mult Cer PMT%d; H_cal_3ta_goodPosAdcTdcDiffTime (ns); H_cal_3ta_goodPosAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);

    GetOutputList()->Add(h3taCALPosAdcPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h3taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]);
    GetOutputList()->Add(h3taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h3taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h3taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]);


  }


  //*********4ta pos done**************
  //************4ta pos**************
  h4taCALPosAdcPulseTimeStarttimeDiff = new TH1F*[13];
  h4taCALPosPulseAmpVsPulseTimeStarttimeDiff = new TH2F*[13];

  h4taCALPosAdcPulseTimeStarttimeDiffMultCer = new TH1F*[13];
  h4taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer = new TH2F*[13];

  h4taCALPosgoodAdcTdcDiffTimeMultCer = new TH1F*[13];
  h4taCALgoodPosPulseAmpVsPulseTimeMultCer= new TH2F*[13];
  for (Int_t ipmt=0; ipmt<13; ipmt++)  {

    h4taCALPosAdcPulseTimeStarttimeDiff[ipmt] = new TH1F(Form(" h4taCALPosAdcPulseTimeStarttimeDiff%d",ipmt+1),Form("HCAL 4ta Pos ADC Pulse Time PMT%d; -H_cal_4ta_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h4taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt] = new TH2F(Form("h4taCALPosPulseAmpVsPulseTime%d",ipmt+1),Form("HCAL 4ta Pulse Amp Vs Pulse Time PMT%d;  -H_cal_4ta_posAdcPulseTime  + H_hod_starttime  (ns);   H_cal_4ta_posAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);

    h4taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt] = new TH1F(Form(" h4taCALPosAdcPulseTimeStarttimeDiffMultCer%d",ipmt+1),Form("HCAL 4ta Pos ADC Pulse Time Mult Cer PMT%d; -H_cal_4ta_posAdcPulseTime  + H_hod_starttime (ns); Counts",ipmt+1),600,-400,400);
    h4taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt] = new TH2F(Form("h4taCALPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 4ta Pulse Amp Vs Pulse Time Mult Cer PMT%d;  -H_cal_4ta_posAdcPulseTime  + H_hod_starttime  (ns); H_cal_4ta_posAdcPulseAmp",ipmt+1),600,-400,400,600,0,600);

    h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt] = new TH1F(Form("h4taCALPosgoodAdcTdcDiffTimeMultCer%d",ipmt+1),Form("HCAL 4ta Good Pos ADC TDC TIME DIFF Mult Cer PMT%d;H_cal_4ta_goodPosAdcTdcDiffTime ; Counts",ipmt+1),600,-400,400);
    h4taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt] = new TH2F(Form("h4taCALgoodPosPulseAmpVsPulseTimeMultCer%d",ipmt+1),Form("HCAL 4ta Good Pulse Amp Vs good ADC TDC TIME DIFF Mult Cer PMT%d; H_cal_4ta_goodPosAdcTdcDiffTime (ns); H_cal_4ta_goodPosAdcPulseAmp ",ipmt+1),600,-400,400,600,0,600);

    GetOutputList()->Add(h4taCALPosAdcPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h4taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]);
    GetOutputList()->Add(h4taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]); 
    GetOutputList()->Add(h4taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]);
    GetOutputList()->Add(h4taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]);


  }




  //**********4ta pos done*********









  // for (Int_t ipmt=0; ipmt<13; ipmt++) // {

  //   h1H1prCALNegPulseAmp[ipmt] = new TH2F(Form("H1prCALNegPulseAmp%d",ipmt+1),Form("1 pr CAL Neg PMT%d Adc Pulse time vs Adc Pulse Amp; Adc Pulse Time (ns); Pulse Amp",ipmt+1),600,-200,200,500,0,600);
  //   h1H1prCALPosPulseAmp[ipmt] = new TH2F(Form("H1prCALPosPulseAmp%d",ipmt+1),Form("1 pr CAL Pos PMT%d Adc Pulse time vs Adc Pulse Amp; Adc Pulse Time (ns); Pulse Amp",ipmt+1),600,-200,200,500,0,1000);
     
  //   h1H2taCALNegPulseAmp[ipmt] = new TH2F(Form("H2taCALNegPulseAmp%d",ipmt+1),Form("2 ta CAL Neg PMT%d Adc Pulse time vs Adc Pulse Amp; Adc Pulse Time (ns); Pulse Amp",ipmt+1),1000,-200,200, 500,0,1000);
  //   h1H2taCALPosPulseAmp[ipmt] = new TH2F(Form("H2taCALPosPulseAmp%d",ipmt+1),Form("2 ta CAL Pos PMT%d Adc Pulse time vs Adc Pulse Amp; Adc Pulse Time (ns); Pulse Amp",ipmt+1),1000,-200,200, 500,0,1000);
     
  //   h1H3taCALNegPulseAmp[ipmt] = new TH2F(Form("H3taCALNegPulseAmp%d",ipmt+1),Form("3 ta CAL Neg PMT%d Adc Pulse time vs Adc Pulse Amp; Adc Pulse Time (ns); Pulse Amp",ipmt+1),1000,-200,200, 500,0,1000);
  //   h1H3taCALPosPulseAmp[ipmt] = new TH2F(Form("H3taCALPosPulseAmp%d",ipmt+1),Form("3 ta CAL Pos PMT%d Adc Pulse time vs Adc Pulse Amp; Pulse Amp;",ipmt+1),1000,-200,200, 1000,-200,200);
     
  //   h1H4taCALNegPulseAmp[ipmt] = new TH2F(Form("H4taCALNegPulseAmp%d",ipmt+1),Form("4 ta CAL Neg PMT%d Adc Pulse time vs Adc Pulse Amp; Adc Pulse Time (ns); Pulse Amp",ipmt+1),1000,-200,200, 500,0,1000);
  //   h1H4taCALPosPulseAmp[ipmt] = new TH2F(Form("H4taCALPosPulseAmp%d",ipmt+1),Form("4 ta CAL Pos PMT%d Adc Pulse time vs Adc Pulse Amp; Adc Pulse Time (ns); Pulse Amp",ipmt+1),1000,-200,200, 500,0,1000);



  //   h1H1prCALNegPulseTime[ipmt] = new TH1F(Form("H1prCALNegPulseTime%d",ipmt+1),Form("1 pr CAL Neg PMT%d Adc Pulse time ; Adc Pulse Time (ns); Counts",ipmt+1),1000,-200,200);
  //   h1H1prCALPosPulseTime[ipmt] = new TH1F(Form("H1prCALPosPulseTime%d",ipmt+1),Form("1 pr CAL Pos PMT%d Adc Pulse time ; Adc Pulse Time (ns) Counts",ipmt+1),1000,-200, 200);
     
  //   h1H2taCALNegPulseTime[ipmt] = new TH1F(Form("H2taCALNegPulseTime%d",ipmt+1),Form("2 ta CAL Neg PMT%d Adc Pulse time ; Adc Pulse Time (ns); Counts",ipmt+1),1000,-200,200);
  //   h1H2taCALPosPulseTime[ipmt] = new TH1F(Form("H2taCALPosPulseTime%d",ipmt+1),Form("2 ta CAL Pos PMT%d Adc Pulse time ; Adc Pulse Time (ns); Counts",ipmt+1),1000,-200,200);
     
  //   h1H3taCALNegPulseTime[ipmt] = new TH1F(Form("H3taCALNegPulseTime%d",ipmt+1),Form("3 ta CAL Neg PMT%d Adc Pulse time ; Adc Pulse Time (ns); Counts",ipmt+1),1000,-200,200);
  //   h1H3taCALPosPulseTime[ipmt] = new TH1F(Form("H3taCALPosPulseTime%d",ipmt+1),Form("3 ta CAL Pos PMT%d Adc Pulse time ; Adc Pulse Time (ns); Counts",ipmt+1),1000,-200,200);
     
  //   h1H4taCALNegPulseTime[ipmt] = new TH1F(Form("H4taCALNegPulseTime%d",ipmt+1),Form("4 ta CAL Neg PMT%d Adc Pulse time ; Adc Pulse Time (ns); Counts",ipmt+1),1000,-200,200);
  //   h1H4taCALPosPulseTime[ipmt] = new TH1F(Form("H4taCALPosPulseTime%d",ipmt+1),Form("4 ta CAL Pos PMT%d Adc Pulse time ; Adc Pulse Time (ns); Counts",ipmt+1),1000,-200,200);

  //   GetOutputList()->Add(h1H1prCALNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1H1prCALPosPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1H2taCALNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1H2taCALPosPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1H3taCALNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1H3taCALPosPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1H4taCALNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1H4taCALPosPulseAmp[ipmt]);

     
  //   GetOutputList()->Add(h1H1prCALNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1H1prCALPosPulseTime[ipmt]);
  //   GetOutputList()->Add(h1H2taCALNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1H2taCALPosPulseTime[ipmt]);
  //   GetOutputList()->Add(h1H3taCALNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1H3taCALPosPulseTime[ipmt]);
  //   GetOutputList()->Add(h1H4taCALNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1H4taCALPosPulseTime[ipmt]);

  // }

  // h1HDCRawTdc = new TH1F*[12];
  // for (Int_t ipmt=0; ipmt<12; ipmt++) {
  //   h1HDCRawTdc[ipmt] = new TH1F(Form("PDCRawTdc%d",ipmt+1),"Information for HMS DC Raw TDC;TDC Channel;Counts",250,-15000,-10000);

  //   GetOutputList()->Add(h1HDCRawTdc[ipmt]);
  // }

  // h1HHODO1xNegPulseAmp = new TH2F*[16];
  // h1HHODO1xPosPulseAmp = new TH2F*[16];
  // h1HHODO1yNegPulseAmp = new TH2F*[16];
  // h1HHODO1yPosPulseAmp = new TH2F*[16];
  // h1HHODO2xNegPulseAmp = new TH2F*[16];
  // h1HHODO2xPosPulseAmp = new TH2F*[16];
  // h1HHODO2yNegPulseAmp = new TH2F*[16];
  // h1HHODO2yPosPulseAmp = new TH2F*[16];


  // h1HHODO1xNegPulseTime = new TH1F*[16];
  // h1HHODO1xPosPulseTime = new TH1F*[16];
  // h1HHODO1yNegPulseTime = new TH1F*[16];
  // h1HHODO1yPosPulseTime = new TH1F*[16];
  // h1HHODO2xNegPulseTime = new TH1F*[16];
  // h1HHODO2xPosPulseTime = new TH1F*[16];
  // h1HHODO2yNegPulseTime = new TH1F*[16];
  // h1HHODO2yPosPulseTime = new TH1F*[16];



  // for (Int_t ipmt=0; ipmt<16; ipmt++) // {
  //   h1HHODO1xNegPulseAmp[ipmt] = new TH2F(Form("HHODO1xNegPulseAmp%d",ipmt+1),Form("HODO 1x Neg PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);
  //   h1HHODO1xPosPulseAmp[ipmt] = new TH2F(Form("HHODO1xPosPulseAmp%d",ipmt+1),Form("HODO 1x Pos PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);
  //   h1HHODO1yNegPulseAmp[ipmt] = new TH2F(Form("HHODO1yNegPulseAmp%d",ipmt+1),Form("HODO 1y Neg PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);
  //   h1HHODO1yPosPulseAmp[ipmt] = new TH2F(Form("HHODO1yPosPulseAmp%d",ipmt+1),Form("HODO 1y Pos PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);
  //   h1HHODO2xNegPulseAmp[ipmt] = new TH2F(Form("HHODO2xNegPulseAmp%d",ipmt+1),Form("HODO 2x Neg PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);
  //   h1HHODO2xPosPulseAmp[ipmt] = new TH2F(Form("HHODO2xPosPulseAmp%d",ipmt+1),Form("HODO 2x Pos PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);
  //   h1HHODO2yNegPulseAmp[ipmt] = new TH2F(Form("HHODO2yNegPulseAmp%d",ipmt+1),Form("HODO 2y Neg PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);
  //   h1HHODO2yPosPulseAmp[ipmt] = new TH2F(Form("HHODO2yPosPulseAmp%d",ipmt+1),Form("HODO 2y Pos PMT%d Adc Pulse time vs Adc Pulse Amp;Adc Pulse Time (ns);Pulse Amp",ipmt+1),1000,-200,0,1000,0,1000);



  //   h1HHODO1xNegPulseTime[ipmt] = new TH1F(Form("HHODO1xNegPulseTime%d",ipmt+1),Form("HODO 1x Neg PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);
  //   h1HHODO1xPosPulseTime[ipmt] = new TH1F(Form("HHODO1xPosPulseTime%d",ipmt+1),Form("HODO 1x Pos PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);
  //   h1HHODO1yNegPulseTime[ipmt] = new TH1F(Form("HHODO1yNegPulseTime%d",ipmt+1),Form("HODO 1y Neg PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);
  //   h1HHODO1yPosPulseTime[ipmt] = new TH1F(Form("HHODO1yPosPulseTime%d",ipmt+1),Form("HODO 1y Pos PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);
  //   h1HHODO2xNegPulseTime[ipmt] = new TH1F(Form("HHODO2xNegPulseTime%d",ipmt+1),Form("HODO 2x Neg PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);
  //   h1HHODO2xPosPulseTime[ipmt] = new TH1F(Form("HHODO2xPosPulseTime%d",ipmt+1),Form("HODO 2x Pos PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);
  //   h1HHODO2yNegPulseTime[ipmt] = new TH1F(Form("HHODO2yNegPulseTime%d",ipmt+1),Form("HODO 2y Neg PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);
  //   h1HHODO2yPosPulseTime[ipmt] = new TH1F(Form("HHODO2yPosPulseTime%d",ipmt+1),Form("HODO 2y Pos PMT%d Adc Pulse time; Adc Pulse Time (ns);Counts",ipmt+1),1000,-200,0);




  //   GetOutputList()->Add(h1HHODO1xNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1HHODO1xPosPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1HHODO1yNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1HHODO1yPosPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1HHODO2xNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1HHODO2xPosPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1HHODO2yNegPulseAmp[ipmt]);
  //   GetOutputList()->Add(h1HHODO2yPosPulseAmp[ipmt]);

  //   GetOutputList()->Add(h1HHODO1xNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1HHODO1xPosPulseTime[ipmt]);
  //   GetOutputList()->Add(h1HHODO1yNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1HHODO1yPosPulseTime[ipmt]);
  //   GetOutputList()->Add(h1HHODO2xNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1HHODO2xPosPulseTime[ipmt]);
  //   GetOutputList()->Add(h1HHODO2yNegPulseTime[ipmt]);
  //   GetOutputList()->Add(h1HHODO2yPosPulseTime[ipmt]);


  // }
}

Bool_t HMSADCGates::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStats to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);

  auto tot_entry = 1100000;

  if(entry<1200) {
    if (entry % 100000 == 0) cout << entry*100/tot_entry << "   % of data done" << endl;

  
    //cout << entry << endl;
  
  
    for (Int_t i = 0; i < *Ndata_H_cer_adcPulseTime; i++) {
      // cout << *Ndata_H_cer_adcPulseTime << endl;
      if (H_cer_adcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_cer_adcCounter[i] - 1;
     
     
      h1HCERAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cer_adcPulseTime[i]+ *H_hod_starttime);
      h1HCERPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cer_adcPulseTime[i] + *H_hod_starttime,H_cer_adcPulseAmp[i]);
      if (H_cer_goodAdcMult[current_pmt] == 1) 
	{
	  if(*H_cal_etottracknorm >0.8 && *H_cal_etottracknorm <1.3)
	    {
	      h1HCERAdcPulseTimeStarttimeDiffMultCal[current_pmt]->Fill(-H_cer_adcPulseTime[i]+ *H_hod_starttime);
	      h1HCERPulseAmpVsPulseTimeStarttimeDiffMultCal[current_pmt]->Fill(-H_cer_adcPulseTime[i] + *H_hod_starttime,H_cer_adcPulseAmp[i]);
	    }
	}
    }

    for(Int_t i =0; i<*Ndata_H_cer_goodAdcTdcDiffTime; i++){

      if(H_cer_goodAdcMult[i] ==1)
	{
	  if(*H_cal_etottracknorm >0.8 && *H_cal_etottracknorm<1.3)
	    {
	      h1HCERGoodAdcTdcTimeDiffMultCal[i]->Fill(H_cer_goodAdcTdcDiffTime[i]);
	      h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal[i]->Fill(H_cer_goodAdcTdcDiffTime[i], H_cer_goodAdcPulseAmp[i]);
	    }
	}
      // cout << *Ndata_H_cal_1pr_goodNegAdcTdcDiffTime<<end;

    }


    //*******************Filling HCER Done***************
  
    // cout <<h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->GetEntries()<<endl;
    //cout<<h1prCALNegAdcPulseTimeStarttimeDiffMultCer[10]->GetEntries()<<endl;
    //cout<< H_cal_1pr_goodNegAdcMult[current_pmt]->GetEntries()<<endl;


    // // //**************Filling hcal 1pr Pos *****************//
 
    for (Int_t i = 0; i < *Ndata_H_1prcal_posAdcPulseTime; i++) {
    
      if (H_1prcal_posAdcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_1prcal_posAdcCounter[i] - 1;

      h1prCALPosAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_1prcal_posAdcPulseTime[i] + *H_hod_starttime);
      h1prCALPosPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_1prcal_posAdcPulseTime[i] + *H_hod_starttime ,H_1prcal_posAdcPulseAmp[i]);

      if ( H_cal_1pr_goodPosAdcMult[current_pmt] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    {
	      h1prCALPosAdcPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_1prcal_posAdcPulseTime[i] + *H_hod_starttime);
	      h1prCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_1prcal_posAdcPulseTime[i] + *H_hod_starttime ,H_1prcal_posAdcPulseAmp[i]);
	    }
	}
    }
  
    for(Int_t i =0; i<*Ndata_H_cal_1pr_goodPosAdcTdcDiffTime; i++){
      if (H_1prcal_posAdcErrorFlag[i] == 1) continue;

      if (H_cal_1pr_goodPosAdcMult[i] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    { 
	      h1prCALPosgoodAdcTdcDiffTimeMultCer[i]->Fill(H_cal_1pr_goodPosAdcTdcDiffTime[i]);
	      h1prCALgoodPosPulseAmpVsPulseTimeMultCer[i]->Fill(H_cal_1pr_goodPosAdcTdcDiffTime[i], H_cal_1pr_goodPosAdcPulseAmp[i]);
						  									  
	    }
	}
    }
    //********filling neg 1pr cal***********
    for (Int_t i = 0; i < *Ndata_H_1prcal_negAdcPulseTime; i++) {
    
      if (H_1prcal_negAdcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_1prcal_negAdcCounter[i] - 1;

      h1prCALNegAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_1prcal_negAdcPulseTime[i] + *H_hod_starttime);
      h1prCALNegPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_1prcal_negAdcPulseTime[i] + *H_hod_starttime ,H_1prcal_negAdcPulseAmp[i]);

      if ( H_cal_1pr_goodNegAdcMult[current_pmt] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    {
	      h1prCALNegAdcPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_1prcal_negAdcPulseTime[i] + *H_hod_starttime);
	      h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_1prcal_negAdcPulseTime[i] + *H_hod_starttime ,H_1prcal_negAdcPulseAmp[i]);
	    }
	}
    }
  
    for(Int_t i =0; i<*Ndata_H_cal_1pr_goodNegAdcTdcDiffTime; i++){
      if (H_1prcal_negAdcErrorFlag[i] == 1) continue;

      if (H_cal_1pr_goodNegAdcMult[i] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    { 
	      h1prCALNeggoodAdcTdcDiffTimeMultCer[i]->Fill(H_cal_1pr_goodNegAdcTdcDiffTime[i]);
	      h1prCALgoodNegPulseAmpVsPulseTimeMultCer[i]->Fill(H_cal_1pr_goodNegAdcTdcDiffTime[i], H_cal_1pr_goodNegAdcPulseAmp[i]);
						  									  
	    }
	}
    }
    //**********************Filling 1pr pos neg done***********************************

    //******************************Filling 2ta pos**************************************


 for (Int_t i = 0; i < *Ndata_H_cal_2ta_posAdcPulseTime ; i++) {
    
      if (H_cal_2ta_posAdcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_cal_2ta_posAdcCounter[i] - 1;

      h2taCALPosAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_2ta_posAdcPulseTime[i] + *H_hod_starttime);
      h2taCALPosPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_2ta_posAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_posAdcPulseAmp[i]);

      if ( H_cal_2ta_goodPosAdcMult[current_pmt] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    {
	      h2taCALPosAdcPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_2ta_posAdcPulseTime[i] + *H_hod_starttime);
	      h2taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_2ta_posAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_posAdcPulseAmp[i]);
	    }
	}
    }
  
    for(Int_t i =0; i<*Ndata_H_cal_2ta_goodPosAdcTdcDiffTime; i++){
      if (H_cal_2ta_posAdcErrorFlag[i] == 1) continue;

      if (H_cal_2ta_goodPosAdcMult[i] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    { 
	      h2taCALPosgoodAdcTdcDiffTimeMultCer[i]->Fill(H_cal_2ta_goodPosAdcTdcDiffTime[i]);
	      h2taCALgoodPosPulseAmpVsPulseTimeMultCer[i]->Fill(H_cal_2ta_goodPosAdcTdcDiffTime[i], H_cal_2ta_goodPosAdcPulseAmp[i]);
						  									  
	    }
	}
    }


    //*******************************Filling 2ta neg*****************


 for (Int_t i = 0; i < *Ndata_H_cal_2ta_negAdcPulseTime ; i++) {
    
      if (H_cal_2ta_negAdcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_cal_2ta_negAdcCounter[i] - 1;

       h2taCALNegAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime);
       h2taCALNegPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_negAdcPulseAmp[i]);

      if ( H_cal_2ta_goodNegAdcMult[current_pmt] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    {
	      h2taCALNegAdcPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime);
	      h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_negAdcPulseAmp[i]);
	    }
	}
    }
  
    for(Int_t i =0; i<*Ndata_H_cal_2ta_goodNegAdcTdcDiffTime; i++){
      if (H_cal_2ta_negAdcErrorFlag[i] == 1) continue;

      if (H_cal_2ta_goodNegAdcMult[i] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    { 
	      h2taCALNeggoodAdcTdcDiffTimeMultCer[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i]);
	      h2taCALgoodNegPulseAmpVsPulseTimeMultCer[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i], H_cal_2ta_goodNegAdcPulseAmp[i]);
						  									  
	    }
	}
    }


    //***************2ta pos neg done*************************
    //***************3ta pos*******************************


 for (Int_t i = 0; i < *Ndata_H_cal_3ta_posAdcPulseTime ; i++) {
    
      if (H_cal_3ta_posAdcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_cal_3ta_posAdcCounter[i] - 1;

      h3taCALPosAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_3ta_posAdcPulseTime[i] + *H_hod_starttime);
      h3taCALPosPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_3ta_posAdcPulseTime[i] + *H_hod_starttime ,H_cal_3ta_posAdcPulseAmp[i]);

      if ( H_cal_3ta_goodPosAdcMult[current_pmt] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    {
	      h3taCALPosAdcPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_3ta_posAdcPulseTime[i] + *H_hod_starttime);
	      h3taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_3ta_posAdcPulseTime[i] + *H_hod_starttime ,H_cal_3ta_posAdcPulseAmp[i]);
	    }
	}
    }
  
    for(Int_t i =0; i<*Ndata_H_cal_3ta_goodPosAdcTdcDiffTime; i++){
      if (H_cal_3ta_posAdcErrorFlag[i] == 1) continue;

      if (H_cal_3ta_goodPosAdcMult[i] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    { 
	      h3taCALPosgoodAdcTdcDiffTimeMultCer[i]->Fill(H_cal_3ta_goodPosAdcTdcDiffTime[i]);
	      h3taCALgoodPosPulseAmpVsPulseTimeMultCer[i]->Fill(H_cal_3ta_goodPosAdcTdcDiffTime[i], H_cal_3ta_goodPosAdcPulseAmp[i]);
						  									  
	    }
	}
    }

    //*********************3ta pos done*******************************



 for (Int_t i = 0; i < *Ndata_H_cal_4ta_posAdcPulseTime ; i++) {
    
      if (H_cal_4ta_posAdcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_cal_4ta_posAdcCounter[i] - 1;

      h4taCALPosAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_4ta_posAdcPulseTime[i] + *H_hod_starttime);
      h4taCALPosPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_4ta_posAdcPulseTime[i] + *H_hod_starttime ,H_cal_4ta_posAdcPulseAmp[i]);

      if ( H_cal_4ta_goodPosAdcMult[current_pmt] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    {
	      h4taCALPosAdcPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_4ta_posAdcPulseTime[i] + *H_hod_starttime);
	      h4taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_4ta_posAdcPulseTime[i] + *H_hod_starttime ,H_cal_4ta_posAdcPulseAmp[i]);
	    }
	}
    }
  
    for(Int_t i =0; i<*Ndata_H_cal_4ta_goodPosAdcTdcDiffTime; i++){
      if (H_cal_4ta_posAdcErrorFlag[i] == 1) continue;

      if (H_cal_4ta_goodPosAdcMult[i] ==1)
	{
	  if (*H_cer_npeSum >2.0) 
	    { 
	      h4taCALPosgoodAdcTdcDiffTimeMultCer[i]->Fill(H_cal_4ta_goodPosAdcTdcDiffTime[i]);
	      h4taCALgoodPosPulseAmpVsPulseTimeMultCer[i]->Fill(H_cal_4ta_goodPosAdcTdcDiffTime[i], H_cal_4ta_goodPosAdcPulseAmp[i]);
						  									  
	    }
	}
    }

    //***************HCAL 4ta pos done********************************





    //cout << *Ndata_H_cal_1pr_goodNegAdcTdcDiffTime << endl;
    // cout <<h1prCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer->GetEntries()<<endl;


    // //cout << "ok ! up to here " << endl;

    // //*******************************//
 
    // // --- 1pr cal neg --- // 
    // for (Int_t i = 0; i < *Ndata_H_1prcal_negAdcPulseTime; i++) {
    
    //   if (H_1prcal_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_1prcal_negAdcCounter[i] - 1;
    //   h1H1prCALNegPulseAmp[current_pmt]->Fill(-H_1prcal_negAdcPulseTime[i],H_1prcal_negAdcPulseAmp[i]);
    //   h1H1prCALNegPulseTime[current_pmt]->Fill(-H_1prcal_negAdcPulseTime[i]);
    // }
  
    // // --- 1pr cal pos --- //

    // for (Int_t i = 0; i < *Ndata_H_1prcal_posAdcPulseTime; i++) {
    //   if (H_1prcal_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_1prcal_posAdcCounter[i] - 1;
    //   h1H1prCALPosPulseAmp[current_pmt]->Fill(-H_1prcal_posAdcPulseTime[i],H_1prcal_posAdcPulseAmp[i]); 
    //   h1H1prCALPosPulseTime[current_pmt]->Fill(-H_1prcal_posAdcPulseTime[i]); 
    // }
  
  
    // // ---- 2ta cal neg ---- //

    // for (Int_t i = 0; i < *Ndata_H_2tacal_negAdcPulseTime; i++) {
    //   if (H_2tacal_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_2tacal_negAdcCounter[i] - 1;
    //   h1H2taCALNegPulseAmp[current_pmt]->Fill(-H_2tacal_negAdcPulseTime[i],H_2tacal_negAdcPulseAmp[i]); 
    //   h1H2taCALNegPulseTime[current_pmt]->Fill(-H_2tacal_negAdcPulseTime[i]); 
    // } 
 
    // // ---- 2ta Pos ---- //  
  
    // for (Int_t i = 0; i < *Ndata_H_2tacal_posAdcPulseTime; i++) {
    //   if (H_2tacal_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_2tacal_posAdcCounter[i] - 1;
    //   h1H2taCALPosPulseAmp[current_pmt]->Fill(-H_2tacal_posAdcPulseTime[i],H_2tacal_posAdcPulseAmp[i]);
    //   h1H2taCALPosPulseTime[current_pmt]->Fill(-H_2tacal_posAdcPulseTime[i]);
    // }
  

    // // ---- 3ta Neg ----//
    // for (Int_t i = 0; i < *Ndata_H_3tacal_negAdcPulseTime; i++) {
    //   if (H_3tacal_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_3tacal_negAdcCounter[i] - 1;
    //   h1H3taCALNegPulseAmp[current_pmt]->Fill(-H_3tacal_negAdcPulseTime[i],H_3tacal_negAdcPulseAmp[i]);
    //   h1H3taCALNegPulseTime[current_pmt]->Fill(-H_3tacal_negAdcPulseTime[i]);
    // }
    
    // // ---- 3ta Pos ----//  
    // for (Int_t i = 0; i < *Ndata_H_3tacal_posAdcPulseTime; i++) {
    //   if (H_3tacal_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_3tacal_posAdcCounter[i] - 1;
    //   h1H3taCALPosPulseAmp[current_pmt]->Fill(-H_3tacal_posAdcPulseTime[i],H_3tacal_posAdcPulseAmp[i]); 
    //   h1H3taCALPosPulseTime[current_pmt]->Fill(-H_3tacal_posAdcPulseTime[i]); 
    // }
  
    // // ---- 4ta Neg ---- //  
    // for (Int_t i = 0; i < *Ndata_H_4tacal_negAdcPulseTime; i++) {
    //   if (H_4tacal_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_4tacal_negAdcCounter[i] - 1;
    //   h1H4taCALNegPulseAmp[current_pmt]->Fill(-H_4tacal_negAdcPulseTime[i],H_4tacal_negAdcPulseAmp[i]); 
    //   h1H4taCALNegPulseTime[current_pmt]->Fill(-H_4tacal_negAdcPulseTime[i]); 
    // }
   
    // // ---- 4ta Pos ---- //
   
    // for (Int_t i = 0; i < *Ndata_H_4tacal_posAdcPulseTime; i++) {
    //   if (H_4tacal_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_4tacal_posAdcCounter[i] - 1;
    //   h1H4taCALPosPulseAmp[current_pmt]->Fill(-H_4tacal_posAdcPulseTime[i],H_4tacal_posAdcPulseAmp[i]); 
    //   h1H4taCALPosPulseTime[current_pmt]->Fill(-H_4tacal_posAdcPulseTime[i]); 
    // }
  

    // // --------- //
    // for (Int_t i = 0; i < *Ndata_H_dc_1u1_time; i++) {
    //   h1HDCRawTdc[0]->Fill(H_dc_1u1_rawtdc[i]); 
    //   h1HDCRawTdc[1]->Fill(H_dc_1u2_rawtdc[i]);
    //   h1HDCRawTdc[2]->Fill(H_dc_1v1_rawtdc[i]); 
    //   h1HDCRawTdc[3]->Fill(H_dc_1v2_rawtdc[i]);
    //   h1HDCRawTdc[4]->Fill(H_dc_1x1_rawtdc[i]); 
    //   h1HDCRawTdc[5]->Fill(H_dc_1x2_rawtdc[i]);
    //   h1HDCRawTdc[6]->Fill(H_dc_2u1_rawtdc[i]); 
    //   h1HDCRawTdc[7]->Fill(H_dc_2u2_rawtdc[i]);
    //   h1HDCRawTdc[8]->Fill(H_dc_2v1_rawtdc[i]); 
    //   h1HDCRawTdc[9]->Fill(H_dc_2v2_rawtdc[i]);
    //   h1HDCRawTdc[10]->Fill(H_dc_2x1_rawtdc[i]); 
    //   h1HDCRawTdc[11]->Fill(H_dc_2x2_rawtdc[i]);
    // }
  
    // // ---- HODO ---- //
  
    // for (Int_t i = 0; i < *Ndata_H_hod_1x_negAdcPulseTime; i++) {
    //   if (H_hod_1x_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_1x_negAdcCounter[i] - 1;
    //   h1HHODO1xNegPulseAmp[current_pmt]->Fill(-H_hod_1x_negAdcPulseTime[i], H_hod_1x_negAdcPulseAmp[i]); 
    //   h1HHODO1xNegPulseTime[current_pmt]->Fill(-H_hod_1x_negAdcPulseTime[i]); 
    // }
  
  
    // // --- 1x pos ---- //
  
    // for (Int_t i = 0; i < *Ndata_H_hod_1x_posAdcPulseTime; i++) {
    //   if (H_hod_1x_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_1x_posAdcCounter[i] - 1;
    //   h1HHODO1xPosPulseAmp[current_pmt]->Fill(-H_hod_1x_posAdcPulseTime[i], H_hod_1x_posAdcPulseAmp[i]); 
    //   h1HHODO1xPosPulseTime[current_pmt]->Fill(-H_hod_1x_posAdcPulseTime[i]); 

    // }

    // //----- 1y neg --- ///  
  
    // for (Int_t i = 0; i < *Ndata_H_hod_1y_negAdcPulseTime; i++) {
    //   if (H_hod_1y_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_1y_negAdcCounter[i] - 1;
    //   h1HHODO1yNegPulseAmp[current_pmt]->Fill(-H_hod_1y_negAdcPulseTime[i], H_hod_1y_negAdcPulseTime[i]);
    //   h1HHODO1yNegPulseTime[current_pmt]->Fill(-H_hod_1y_negAdcPulseTime[i]);
    // }

    // //--------1y pos ----- //
  
    // for (Int_t i = 0; i < *Ndata_H_hod_1y_posAdcPulseTime; i++) {
    //   if (H_hod_1y_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_1y_posAdcCounter[i] - 1;
    //   h1HHODO1yPosPulseAmp[current_pmt]->Fill(-H_hod_1y_posAdcPulseTime[i],H_hod_1y_posAdcPulseAmp[i]); 
    //   h1HHODO1yPosPulseTime[current_pmt]->Fill(-H_hod_1y_posAdcPulseTime[i]); 

    // }
  
    // //------- 2x neg ----//  
  
    // for (Int_t i = 0; i < *Ndata_H_hod_2x_negAdcPulseTime; i++) {
    //   if (H_hod_2x_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_2x_negAdcCounter[i] - 1;  
    //   h1HHODO2xNegPulseAmp[current_pmt]->Fill(-H_hod_2x_negAdcPulseTime[i],H_hod_2x_negAdcPulseAmp[i]);
    //   h1HHODO2xNegPulseTime[current_pmt]->Fill(-H_hod_2x_negAdcPulseTime[i]);

    // }

    // //----2x pos ---//
  
    // for (Int_t i = 0; i < *Ndata_H_hod_2x_posAdcPulseTime; i++) {
    //   if (H_hod_2x_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_2x_posAdcCounter[i] - 1;
    //   h1HHODO2xPosPulseAmp[current_pmt]->Fill(-H_hod_2x_posAdcPulseTime[i],H_hod_2x_posAdcPulseAmp[i] ); 
    //   h1HHODO2xPosPulseTime[current_pmt]->Fill(-H_hod_2x_posAdcPulseTime[i]); 

    // }

    // //--- 2y neg ---//
 
    // for (Int_t i = 0; i < *Ndata_H_hod_2y_negAdcPulseTime; i++) {
    //   if (H_hod_2y_negAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_2y_negAdcCounter[i] - 1; 
    //   h1HHODO2yNegPulseAmp[current_pmt]->Fill(-H_hod_2y_negAdcPulseTime[i],H_hod_2y_negAdcPulseAmp[i]);
    //   h1HHODO2yNegPulseTime[current_pmt]->Fill(-H_hod_2y_negAdcPulseTime[i]);
    // }
  

    // //--- 2y pos ---//
  
    // for (Int_t i = 0; i < *Ndata_H_hod_2y_posAdcPulseTime; i++) {
    //   if (H_hod_2y_posAdcErrorFlag[i] == 1) continue;
    //   Int_t current_pmt = H_hod_2y_posAdcCounter[i] - 1;
    //   h1HHODO2yPosPulseAmp[current_pmt]->Fill(-H_hod_2y_posAdcPulseTime[i],H_hod_2y_posAdcPulseAmp[i]);
    //   h1HHODO2yPosPulseTime[current_pmt]->Fill(-H_hod_2y_posAdcPulseTime[i]);

    // }
 

  }//if entry<1000 ended here
  return kTRUE;
}

void HMSADCGates::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

void HMSADCGates::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Branches Sorted, Now Calculating Windows");


  // TH2F* HCERPulseAmp[2];
  // for (Int_t ipmt = 0; ipmt < 2; ipmt++) {
  
  //   HCERPulseAmp[ipmt] = dynamic_cast<TH2F*> (GetOutputList()->FindObject(Form("HCERPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  // }

  // TH1F* H1prCALNEGPULSETIMEDIFF[13];
  // TH1F* H1prCALPOSPULSETIMEDIFF[13];
  // TH1F* H2taCALNEGPULSETIMEDIFF[13];
  // TH1F* H2taCALPOSPULSETIMEDIFF[13];
  // TH1F* H3taCALNEGPULSETIMEDIFF[13];
  // TH1F* H3taCALPOSPULSETIMEDIFF[13];
  // TH1F* H4taCALNEGPULSETIMEDIFF[13];
  // TH1F* H4taCALPOSPULSETIMEDIFF[13];

  // TH1F* H1prCALNEGPULSETIMEDIFF_cut[13];
  // TH1F* H1prCALPOSPULSETIMEDIFF_cut[13];
  // TH1F* H2taCALNEGPULSETIMEDIFF_cut[13];
  // TH1F* H2taCALPOSPULSETIMEDIFF_cut[13];
  // TH1F* H3taCALNEGPULSETIMEDIFF_cut[13];
  // TH1F* H3taCALPOSPULSETIMEDIFF_cut[13];
  // TH1F* H4taCALNEGPULSETIMEDIFF_cut[13];
  // TH1F* H4taCALPOSPULSETIMEDIFF_cut[13];

  // TH1F* H1prCALNEGGOODADCTDCTIMEDIFF[13];
  // TH1F* H1prCALPOSGOODADCTDCTIMEDIFF[13];
  // TH1F* H2taCALNEGGOODADCTDCTIMEDIFF[13];
  // TH1F* H2taCALPOSGOODADCTDCTIMEDIFF[13];
  // TH1F* H3taCALNEGGOODADCTDCTIMEDIFF[13];
  // TH1F* H3taCALPOSGOODADCTDCTIMEDIFF[13];
  // TH1F* H4taCALNEGGOODADCTDCTIMEDIFF[13];
  // TH1F* H4taCALPOSGOODADCTDCTIMEDIFF[13];

  // TH1F* H1prCALNEGGOODADCTDCTIMEDIFF_cut[13];
  // TH1F* H1prCALPOSGOODADCTDCTIMEDIFF_cut[13];
  // TH1F* H2taCALNEGGOODADCTDCTIMEDIFF_cut[13];
  // TH1F* H2taCALPOSGOODADCTDCTIMEDIFF_cut[13];
  // TH1F* H3taCALNEGGOODADCTDCTIMEDIFF_cut[13];
  // TH1F* H3taCALPOSGOODADCTDCTIMEDIFF_cut[13];
  // TH1F* H4taCALNEGGOODADCTDCTIMEDIFF_cut[13];
  // TH1F* H4taCALPOSGOODADCTDCTIMEDIFF_cut[13];

  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) // {
  //   H1prCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   H1prCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALPosPulseTimeStarttimeDiff%d",ipmt+1)));
  //   H2taCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   H2taCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALPosPulseTimeStarttimeDiff%d",ipmt+1)));
  //   H3taCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   H3taCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALPosPulseTimeStarttimeDiff%d",ipmt+1)));
  //   H4taCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   H4taCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALPosPulseTimeStarttimeDiff%d",ipmt+1)));

  //   H1prCALNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   H1prCALPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   H2taCALNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   H2taCALPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   H3taCALNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   H3taCALPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   H4taCALNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   H4taCALPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));


  //   H1prCALNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   H1prCALPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALPosGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   H2taCALNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   H2taCALPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALPosGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   H3taCALNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   H3taCALPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALPosGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   H4taCALNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   H4taCALPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALPosGoodAdcTdcTimeDiff%d",ipmt+1)));
    
  //   H1prCALNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   H1prCALPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   H2taCALNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   H2taCALPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   H3taCALNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   H3taCALPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   H4taCALNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   H4taCALPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  // }
  
  // TH1F* HDCRAWTDC[12];
  // for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
  //   HDCRAWTDC[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PDCRawTdc%d",ipmt+1)));
  // }

  // TH1F* HHODO1xNEGPULSETIMEDIFF[16];
  // TH1F* HHODO1xPOSPULSETIMEDIFF[16];
  // TH1F* HHODO1yNEGPULSETIMEDIFF[16];
  // TH1F* HHODO1yPOSPULSETIMEDIFF[16];
  // TH1F* HHODO2xNEGPULSETIMEDIFF[16];
  // TH1F* HHODO2xPOSPULSETIMEDIFF[16];
  // TH1F* HHODO2yNEGPULSETIMEDIFF[16];
  // TH1F* HHODO2yPOSPULSETIMEDIFF[16];

  // TH1F* HHODO1xNEGPULSETIMEDIFF_cut[16];
  // TH1F* HHODO1xPOSPULSETIMEDIFF_cut[16];
  // TH1F* HHODO1yNEGPULSETIMEDIFF_cut[16];
  // TH1F* HHODO1yPOSPULSETIMEDIFF_cut[16];
  // TH1F* HHODO2xNEGPULSETIMEDIFF_cut[16];
  // TH1F* HHODO2xPOSPULSETIMEDIFF_cut[16];
  // TH1F* HHODO2yNEGPULSETIMEDIFF_cut[16];
  // TH1F* HHODO2yPOSPULSETIMEDIFF_cut[16];

  // TH1F* HHODO1xNEGGOODADCTDCTIMEDIFF[16];
  // TH1F* HHODO1xPOSGOODADCTDCTIMEDIFF[16];
  // TH1F* HHODO1yNEGGOODADCTDCTIMEDIFF[16];
  // TH1F* HHODO1yPOSGOODADCTDCTIMEDIFF[16];
  // TH1F* HHODO2xNEGGOODADCTDCTIMEDIFF[16];
  // TH1F* HHODO2xPOSGOODADCTDCTIMEDIFF[16];
  // TH1F* HHODO2yNEGGOODADCTDCTIMEDIFF[16];
  // TH1F* HHODO2yPOSGOODADCTDCTIMEDIFF[16];

  // TH1F* HHODO1xNEGGOODADCTDCTIMEDIFF_cut[16];
  // TH1F* HHODO1xPOSGOODADCTDCTIMEDIFF_cut[16];
  // TH1F* HHODO1yNEGGOODADCTDCTIMEDIFF_cut[16];
  // TH1F* HHODO1yPOSGOODADCTDCTIMEDIFF_cut[16];
  // TH1F* HHODO2xNEGGOODADCTDCTIMEDIFF_cut[16];
  // TH1F* HHODO2xPOSGOODADCTDCTIMEDIFF_cut[16];
  // TH1F* HHODO2yNEGGOODADCTDCTIMEDIFF_cut[16];
  // TH1F* HHODO2yPOSGOODADCTDCTIMEDIFF_cut[16];


  //for (Int_t ipmt = 0; ipmt < 16; ipmt++) // {
  //   HHODO1xNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   HHODO1xPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xPosPulseTimeStarttimeDiff%d",ipmt+1)));
  //   HHODO1yNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   HHODO1yPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yPosPulseTimeStarttimeDiff%d",ipmt+1)));
  //   HHODO2xNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   HHODO2xPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xPosPulseTimeStarttimeDiff%d",ipmt+1)));
  //   HHODO2yNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yNegPulseTimeStarttimeDiff%d",ipmt+1)));
  //   HHODO2yPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yPosPulseTimeStarttimeDiff%d",ipmt+1)));

  //   HHODO1xNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   HHODO1xPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   HHODO1yNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   HHODO1yPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   HHODO2xNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   HHODO2xPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   HHODO2yNEGPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yNegPulseTimeStarttimeDiff_cut%d",ipmt+1)));
  //   HHODO2yPOSPULSETIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yPosPulseTimeStarttimeDiff_cut%d",ipmt+1)));

  //   HHODO1xNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   HHODO1xPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xPosGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   HHODO1yNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   HHODO1yPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yPosGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   HHODO2xNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   HHODO2xPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xPosGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   HHODO2yNEGGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yNegGoodAdcTdcTimeDiff%d",ipmt+1)));
  //   HHODO2yPOSGOODADCTDCTIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yPosGoodAdcTdcTimeDiff%d",ipmt+1)));

  //   HHODO1xNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   HHODO1xPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   HHODO1yNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   HHODO1yPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   HHODO2xNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   HHODO2xPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   HHODO2yNEGGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yNegGoodAdcTdcTimeDiff_cut%d",ipmt+1)));
  //   HHODO2yPOSGOODADCTDCTIMEDIFF_cut[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yPosGoodAdcTdcTimeDiff_cut%d",ipmt+1)));



  // }
  

  //Begin peak Finding
  gSystem->RedirectOutput("/dev/null","a");
  // Double_t CER_Window[2];
  // for (Int_t ipmt = 0; ipmt < 2; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(HCERPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = HCERPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   CER_Window[ipmt] = *pm->GetX();
  // }

  // Double_t pr1CALNEG_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(H1prCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = H1prCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   pr1CALNEG_Window[ipmt] = *pm->GetX();
  // }

  // Double_t pr1CALPOS_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(H1prCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = H1prCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   pr1CALPOS_Window[ipmt] = *pm->GetX();
  // }

  // Double_t ta2CALNEG_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(H2taCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = H2taCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   ta2CALNEG_Window[ipmt] = *pm->GetX();
  // }

  // Double_t ta2CALPOS_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(H2taCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = H2taCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   ta2CALPOS_Window[ipmt] = *pm->GetX();
  // }

  // Double_t ta3CALNEG_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {/*
  //   if (ipmt > -1 || H3taCALNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(H3taCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = H3taCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     ta3CALNEG_Window[ipmt] = *pm->GetX();
  //     } else {
  //     ta3CALNEG_Window[ipmt] = 1e+38;
  //     }*/
  //   ta3CALNEG_Window[ipmt] = 1e+38;
  // }


  // Double_t ta3CALPOS_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(H3taCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = H3taCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   ta3CALPOS_Window[ipmt] = *pm->GetX();
  // }

  // Double_t ta4CALNEG_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {/*
  //   if (ipmt > -1 || H4taCALNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(H4taCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = H4taCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     ta4CALNEG_Window[ipmt] = *pm->GetX();
  //   } else {
  //     ta4CALNEG_Window[ipmt] = 1e+38;
  //     }*/
  //   ta4CALNEG_Window[ipmt] = 1e+38;
  // }

  // Double_t ta4CALPOS_Window[13];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(H4taCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = H4taCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   ta4CALPOS_Window[ipmt] = *pm->GetX();
  // }

  // Double_t DC_Window[12];
  // for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
  //   TSpectrum *s = new TSpectrum(1);
  //   s->Search(HDCRAWTDC[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //   TList *functions = HDCRAWTDC[ipmt]->GetListOfFunctions();
  //   TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //   DC_Window[ipmt] = *pm->GetX();
  // }
  
  // Double_t HODO1xNeg_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (HHODO1xNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO1xNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO1xNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO1xNeg_Window[ipmt] = *pm->GetX();
  //   } else {
  //     HODO1xNeg_Window[ipmt] = 1e+38;
  //   }
  // }

  // Double_t HODO1xPos_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (HHODO1xPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO1xPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO1xPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO1xPos_Window[ipmt] = *pm->GetX();
  //   } else {
  //     HODO1xPos_Window[ipmt] = 1e+38;
  //   }
  // }

  // Double_t HODO1yNeg_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (ipmt < 10 || HHODO1yNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO1yNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO1yNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO1yNeg_Window[ipmt] = *pm->GetX();
  //   } else {
  //     HODO1yNeg_Window[ipmt] = 1e+38;
  //   }
  // }

  // Double_t HODO1yPos_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (ipmt < 10 || HHODO1yPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO1yPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO1yPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO1yPos_Window[ipmt] = *pm->GetX();
  //   } else {
  //     HODO1yPos_Window[ipmt] = 1e+38;
  //   }
  // }

  // Double_t HODO2xNeg_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (HHODO2xNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO2xNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO2xNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO2xNeg_Window[ipmt] = *pm->GetX();
  //   }    
  //   else {
  //     HODO2xNeg_Window[ipmt] = 1e+38;
  //   }
  // }

  // Double_t HODO2xPos_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (HHODO2xPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO2xPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO2xPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO2xPos_Window[ipmt] = *pm->GetX();
  //   }
  //   else {
  //     HODO2xPos_Window[ipmt] = 1e+38;
  //   }
  // }

  // Double_t HODO2yNeg_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (ipmt < 10 || HHODO2yNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO2yNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO2yNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO2yNeg_Window[ipmt] = *pm->GetX();
  //   }
  //   else {
  //     HODO2yNeg_Window[ipmt] = 1e+38;
  //   }
  // }

  // Double_t HODO2yPos_Window[16];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   if (ipmt < 10 || HHODO2yPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
  //     TSpectrum *s = new TSpectrum(1);
  //     s->Search(HHODO2yPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
  //     TList *functions = HHODO2yPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
  //     TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
  //     HODO2yPos_Window[ipmt] = *pm->GetX();
  //   }
  //   else {
  //     HODO2yPos_Window[ipmt] = 1e+38;
  //   }
  // }
  gSystem->RedirectOutput(0);

  //Begin Calculation of Window Values
 
  // Double_t CERMinPMT1 = CER_Window[0] - 50.0; Double_t CERMaxPMT1 = CER_Window[0] + 50.0;
  // Double_t CERMinPMT2 = CER_Window[1] - 50.0; Double_t CERMaxPMT2 = CER_Window[1] + 50.0;
  
  // Int_t HODOPosMin[64]; Int_t HODOPosMax[64];
  // Int_t HODONegMin[64]; Int_t HODONegMax[64];
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {  
  //   (HHODO1xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt]    = -200 : HODOPosMin[4*ipmt]    = HODO1xPos_Window[ipmt] - 50;
  //   (HHODO1yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt+1]  = -200 : HODOPosMin[4*ipmt+1]  = HODO1yPos_Window[ipmt] - 50;
  //   (HHODO2xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt+2]  = -200 : HODOPosMin[4*ipmt+2]  = HODO2xPos_Window[ipmt] - 50;
  //   (HHODO2yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt+3]  = -200 : HODOPosMin[4*ipmt+3]  = HODO2yPos_Window[ipmt] - 50;
  //   (HHODO1xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt]    = -200 : HODONegMin[4*ipmt]    = HODO1xNeg_Window[ipmt] - 50;
  //   (HHODO1yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt+1]  = -200 : HODONegMin[4*ipmt+1]  = HODO1yNeg_Window[ipmt] - 50;
  //   (HHODO2xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt+2]  = -200 : HODONegMin[4*ipmt+2]  = HODO2xNeg_Window[ipmt] - 50;
  //   (HHODO2yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt+3]  = -200 : HODONegMin[4*ipmt+3]  = HODO2yNeg_Window[ipmt] - 50;
  //   (HHODO1xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt]    = 200 : HODOPosMax[4*ipmt]    = HODO1xPos_Window[ipmt] + 50;
  //   (HHODO1yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt+1]  = 200 : HODOPosMax[4*ipmt+1]  = HODO1yPos_Window[ipmt] + 50;
  //   (HHODO2xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt+2]  = 200 : HODOPosMax[4*ipmt+2]  = HODO2xPos_Window[ipmt] + 50;
  //   (HHODO2yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt+3]  = 200 : HODOPosMax[4*ipmt+3]  = HODO2yPos_Window[ipmt] + 50;
  //   (HHODO1xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt]    = 200 : HODONegMax[4*ipmt]    = HODO1xNeg_Window[ipmt] + 50;
  //   (HHODO1yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt+1]  = 200 : HODONegMax[4*ipmt+1]  = HODO1yNeg_Window[ipmt] + 50;
  //   (HHODO2xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt+2]  = 200 : HODONegMax[4*ipmt+2]  = HODO2xNeg_Window[ipmt] + 50;
  //   (HHODO2yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt+3]  = 200 : HODONegMax[4*ipmt+3]  = HODO2yNeg_Window[ipmt] + 50;
  // }
  
  // Int_t CALPosMin[52]; Int_t CALPosMax[52];
  // Int_t CALNegMin[52]; Int_t CALNegMax[52];
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
  //   (pr1CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt] = -200 : CALPosMin[ipmt] = pr1CALPOS_Window[ipmt] - 50;
  //   (pr1CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt] = -200 : CALNegMin[ipmt] = pr1CALNEG_Window[ipmt] - 50;
  //   (pr1CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt] = 200 : CALPosMax[ipmt] = pr1CALPOS_Window[ipmt] + 50;
  //   (pr1CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt] = 200 : CALNegMax[ipmt] = pr1CALNEG_Window[ipmt] + 50;
  // }
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
  //   (ta2CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt+13] = -200 : CALPosMin[ipmt+13] = ta2CALPOS_Window[ipmt] - 50;
  //   (ta2CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt+13] = -200 : CALNegMin[ipmt+13] = ta2CALNEG_Window[ipmt] - 50;
  //   (ta2CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt+13] = 200  : CALPosMax[ipmt+13] = ta2CALPOS_Window[ipmt] + 50;
  //   (ta2CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt+13] = 200  : CALNegMax[ipmt+13] = ta2CALNEG_Window[ipmt] + 50;
  // }
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
  //   (ta3CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt+26] = -200 : CALPosMin[ipmt+26] = ta3CALPOS_Window[ipmt] - 50;
  //   (ta3CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt+26] = -200 : CALNegMin[ipmt+26] = ta3CALNEG_Window[ipmt] - 50;
  //   (ta3CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt+26] = 200  : CALPosMax[ipmt+26] = ta3CALPOS_Window[ipmt] + 50;
  //   (ta3CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt+26] = 200  : CALNegMax[ipmt+26] = ta3CALNEG_Window[ipmt] + 50;
  // }
  // for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
  //   (ta4CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt+39] = -200 : CALPosMin[ipmt+39] = ta4CALPOS_Window[ipmt] - 50;
  //   (ta4CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt+39] = -200 : CALNegMin[ipmt+39] = ta4CALNEG_Window[ipmt] - 50;
  //   (ta4CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt+39] = 200  : CALPosMax[ipmt+39] = ta4CALPOS_Window[ipmt] + 50;
  //   (ta4CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt+39] = 200  : CALNegMax[ipmt+39] = ta4CALNEG_Window[ipmt] + 50;
  // }  
  
  // Int_t DCMin[12]; Int_t DCMax[12];
  // for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
  //   (DC_Window[ipmt] == 1e+38) ? DCMin[ipmt] = -30000 : DCMin[ipmt] = DC_Window[ipmt] - 3000;
  //   (DC_Window[ipmt] == 1e+38) ? DCMax[ipmt] = +30000 : DCMax[ipmt] = DC_Window[ipmt] + 3000;
  // }
  //Begin Plotting Results 
  /*
    TCanvas *cCER = new TCanvas("cCER","ADC Timing Window for HMS CER");
    cCER->Divide(2,1); 
    cCER->cd(1); HCERPULSETIMEDIFF[0]->Draw();
    cCER->cd(2); HCERPULSETIMEDIFF[1]->Draw();


    TCanvas *cPOSCAL = new TCanvas("cPOSCAL","ADC Timing Window for HMS Positive CAL");
    cPOSCAL->Divide(13,4);
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+1); H1prCALPOSPULSETIMEDIFF[ipmt]->Draw();
    }
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+14); H2taCALPOSPULSETIMEDIFF[ipmt]->Draw();
    }
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+27); H3taCALPOSPULSETIMEDIFF[ipmt]->Draw();
    }
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+40); H4taCALPOSPULSETIMEDIFF[ipmt]->Draw();
    }

    TCanvas *cNEGCAL = new TCanvas("cNEGCAL","ADC Timing Window for HMS Negative CAL");
    cNEGCAL->Divide(13,4);
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+1); H1prCALNEGPULSETIMEDIFF[ipmt]->Draw();
    }
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+14); H2taCALNEGPULSETIMEDIFF[ipmt]->Draw();
    }
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+27); H3taCALNEGPULSETIMEDIFF[ipmt]->Draw();
    }
    for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+40); H4taCALNEGPULSETIMEDIFF[ipmt]->Draw();
    }
  
    TCanvas *DC = new TCanvas("DC","ADC Timing Window for HMS DC");
    DC->Divide(2,6);
    for (Int_t ipmt = 0; ipmt < 6; ipmt++) {
    DC->cd(2*ipmt+1); HDCRAWTDC[2*ipmt]->Draw(); 
    DC->cd(2*ipmt+2); HDCRAWTDC[2*ipmt+1]->Draw(); 
    }
  
    TCanvas *HODONEG = new TCanvas("HODONEG","ADC Timing Window for HMS NEG HODO");
    HODONEG->Divide(4,16);
    for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HODONEG->cd(4*ipmt+1); HHODO1xNEGPULSETIMEDIFF[ipmt]->Draw();
    HODONEG->cd(4*ipmt+2); HHODO1yNEGPULSETIMEDIFF[ipmt]->Draw();
    HODONEG->cd(4*ipmt+3); HHODO2xNEGPULSETIMEDIFF[ipmt]->Draw();
    HODONEG->cd(4*ipmt+4); HHODO2yNEGPULSETIMEDIFF[ipmt]->Draw();
    }

    TCanvas *HODOPOS = new TCanvas("HODOPOS","ADC Timing Window for HMS POS HODO");
    HODOPOS->Divide(4,16);
    for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HODOPOS->cd(4*ipmt+1); HHODO1xPOSPULSETIMEDIFF[ipmt]->Draw();
    HODOPOS->cd(4*ipmt+2); HHODO1yPOSPULSETIMEDIFF[ipmt]->Draw();
    HODOPOS->cd(4*ipmt+3); HHODO2xPOSPULSETIMEDIFF[ipmt]->Draw();
    HODOPOS->cd(4*ipmt+4); HHODO2yPOSPULSETIMEDIFF[ipmt]->Draw();
    }
  */
  //Output Adc Time Window Values into an ascii file
  TString option = GetOption();
  ofstream HMSWindows;
  HMSWindows.open("HMSADCTimingWindows.dat", fstream::trunc);
  HMSWindows << Form(";Values obtained from Run %s",option.Data()) << endl;
  // HMSWindows << Form("hcer_adcTimeWindowMin = %f, %f \nhcer_adcTimeWindowMax = %f, %f\n",CERMinPMT1,CERMinPMT2,CERMaxPMT1,CERMaxPMT2) << endl;
  
  // HMSWindows << Form(";Values obtained from Run %s\nhhodo_PosAdcTimeWindowMin =",option.Data());
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   HMSWindows << Form(" %d, %d, %d, %d\n",HODOPosMin[4*ipmt],HODOPosMin[4*ipmt+1],HODOPosMin[4*ipmt+2],HODOPosMin[4*ipmt+3]);
  // }
  // HMSWindows << "\nhhodo_PosAdcTimeWindowMax =";
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   HMSWindows << Form(" %d, %d, %d, %d\n",HODOPosMax[4*ipmt],HODOPosMax[4*ipmt+1],HODOPosMax[4*ipmt+2],HODOPosMax[4*ipmt+3]);
  // }
  // HMSWindows << "\nhhodo_NegAdcTimeWindowMin =";
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   HMSWindows << Form(" %d, %d, %d, %d\n",HODONegMin[4*ipmt],HODONegMin[4*ipmt+1],HODONegMin[4*ipmt+2],HODONegMin[4*ipmt+3]);
  // }
  // HMSWindows << "\nhhodo_NegAdcTimeWindowMax =";
  // for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  //   HMSWindows << Form(" %d, %d, %d, %d\n",HODONegMax[4*ipmt],HODONegMax[4*ipmt+1],HODONegMax[4*ipmt+2],HODONegMax[4*ipmt+3]);
  // }
  
  // HMSWindows << Form("\n;Values obtained from Run %s\nhcal_pos_AdcTimeWindowMin =  ",option.Data());
  // for (Int_t iplane = 0; iplane < 4; iplane++) {
  //   HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALPosMin[13*iplane],CALPosMin[13*iplane+1],CALPosMin[13*iplane+2],CALPosMin[13*iplane+3],CALPosMin[13*iplane+4],CALPosMin[13*iplane+5],CALPosMin[13*iplane+6],CALPosMin[13*iplane+7],CALPosMin[13*iplane+8],CALPosMin[13*iplane+9],CALPosMin[13*iplane+10],CALPosMin[13*iplane+11],CALPosMin[13*iplane+12]);
  //   }
  // HMSWindows << "hcal_neg_AdcTimeWindowMin =  ";
  // for (Int_t iplane = 0; iplane < 4; iplane++) {
  //   HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALNegMin[13*iplane],CALNegMin[13*iplane+1],CALNegMin[13*iplane+2],CALNegMin[13*iplane+3],CALNegMin[13*iplane+4],CALNegMin[13*iplane+5],CALNegMin[13*iplane+6],CALNegMin[13*iplane+7],CALNegMin[13*iplane+8],CALNegMin[13*iplane+9],CALNegMin[13*iplane+10],CALNegMin[13*iplane+11],CALNegMin[13*iplane+12]);
  //   }
  // HMSWindows << "hcal_pos_AdcTimeWindowMax =  ";
  // for (Int_t iplane = 0; iplane < 4; iplane++) {
  //   HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALPosMax[13*iplane],CALPosMax[13*iplane+1],CALPosMax[13*iplane+2],CALPosMax[13*iplane+3],CALPosMax[13*iplane+4],CALPosMax[13*iplane+5],CALPosMax[13*iplane+6],CALPosMax[13*iplane+7],CALPosMax[13*iplane+8],CALPosMax[13*iplane+9],CALPosMax[13*iplane+10],CALPosMax[13*iplane+11],CALPosMax[13*iplane+12]);
  //   }
  // HMSWindows << "hcal_neg_AdcTimeWindowMax =  ";
  // for (Int_t iplane = 0; iplane < 4; iplane++) {
  //   HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALNegMax[13*iplane],CALNegMax[13*iplane+1],CALNegMax[13*iplane+2],CALNegMax[13*iplane+3],CALNegMax[13*iplane+4],CALNegMax[13*iplane+5],CALNegMax[13*iplane+6],CALNegMax[13*iplane+7],CALNegMax[13*iplane+8],CALNegMax[13*iplane+9],CALNegMax[13*iplane+10],CALNegMax[13*iplane+11],CALNegMax[13*iplane+12]);
  //   }
   

  // HMSWindows << Form("\n;Values obtained from Run %s\nhtdc_win_min =  ",option.Data());
  // for (Int_t iplane = 0; iplane < 2; iplane++) {
  //   HMSWindows << Form("%d, %d, %d, %d, %d, %d\n",DCMin[6*iplane],DCMin[6*iplane+1],DCMin[6*iplane+2],DCMin[6*iplane+3],DCMin[6*iplane+4],DCMin[6*iplane+5]);
  // }
  // HMSWindows << "htdc_win_max =  ";
  // for (Int_t iplane = 0; iplane < 2; iplane++) {
  //   HMSWindows << Form("%d, %d, %d, %d, %d, %d\n",DCMax[6*iplane],DCMax[6*iplane+1],DCMax[6*iplane+2],DCMax[6*iplane+3],DCMax[6*iplane+4],DCMax[6*iplane+5]);
  // }
  // HMSWindows.close();
  
  //Start output of .root file with all histograms
  // TFile *Histogram_file = new TFile(Form("../HISTOGRAMS/HMSADCGates_Run%i.root",option.Atoi()),"RECREATE");
  // TFile *Histogram_file = new TFile(Form("/HISTOGRAMS/HMSADCGates_Run%i.root",option.Atoi()),"RECREATE");

  // TDirectory *DCER = Histogram_file->mkdir("Gas Cherenkov ADC Timing Spectra"); DCER->cd();

 
  // for (Int_t ipmt=0; ipmt < 2; ipmt++) {
  //   TCanvas *c1 = new TCanvas("c1","c1",800,900); 
  //   //c1->cd();
  //   c1->Divide(2,3);
  //   c1->cd(1); 
  //   h1HCERPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1HCERPulseAmp[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1HCERPulseAmp[ipmt]->Draw("colz");
  //   c1->cd(2);
  //   gPad->SetLogy();
  //   h1HCERAdcPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1HCERAdcPulseTime[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1HCERAdcPulseTime[ipmt]->SetLineColor(4);
  //   h1HCERAdcPulseTime[ipmt]->Draw();
  //   TImage *img = TImage::Create();
  //   img->FromPad(c1);
  //   img->WriteImage(Form("hgc_pmt%i.png",ipmt+1));
  // }

  //******************added*************

  TCanvas *c1 = new TCanvas("c1","HCER_LOOSE_WINDOW",600,600); 
  c1->Divide(2,3); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 2; ipmt++) {
  
   
    c1->cd(1);  gPad->SetGrid(); gPad->SetLogy();
    h1HCERAdcPulseTimeStarttimeDiff[ipmt]->Draw();

    c1->cd(2); gPad->SetGrid();
    h1HCERPulseAmpVsPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c1->cd(3);  gPad->SetGrid(); gPad->SetLogy();
    h1HCERAdcPulseTimeStarttimeDiffMultCal[ipmt]->SetLineColor(kRed);
    h1HCERAdcPulseTimeStarttimeDiffMultCal[ipmt]->Draw();

    c1->cd(4); gPad->SetGrid();
    h1HCERPulseAmpVsPulseTimeStarttimeDiffMultCal[ipmt]->Draw("colz");gPad->SetLogz(1);

    c1->cd(5); gPad->SetGrid(); gPad->SetLogy();
    h1HCERGoodAdcTdcTimeDiffMultCal[ipmt]->SetLineColor(kMagenta);
    h1HCERGoodAdcTdcTimeDiffMultCal[ipmt]->Draw();

    c1->cd(6); gPad->SetGrid();  gPad->SetGrid();
    h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal[ipmt]->Draw("colz");gPad->SetLogz(1);

    c1->SaveAs(Form("Plots/HMS_CER_LOOSE_WINDOW_Pmt%d.pdf",ipmt+1));
    // TImage *img = TImage::Create();
    // img->FromPad(c1);
    // img->WriteImage(Form("hgc_pmt%i.png",ipmt+1));
  }


  TCanvas *c2 = new TCanvas("c2","HCER_LOOSE_WINDOW_",600,600); 
  c2->Divide(1,2); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 2; ipmt++) {
  
   
    c2->cd(1); gPad->SetGrid(); gPad->SetLogy();
    h1HCERAdcPulseTimeStarttimeDiff[ipmt]->Draw();
    h1HCERAdcPulseTimeStarttimeDiffMultCal[ipmt]->SetLineColor(kRed);
    h1HCERAdcPulseTimeStarttimeDiffMultCal[ipmt]->Draw("same");
    h1HCERGoodAdcTdcTimeDiffMultCal[ipmt]->SetLineColor(kMagenta);
    h1HCERGoodAdcTdcTimeDiffMultCal[ipmt]->Draw("same");
    
    c2->cd(2); gPad->SetGrid(); //gPad->SetLogy();
    h1HCERPulseAmpVsGoodAdcTdcTimeDiffMultCal[ipmt]->Draw("colz");gPad->SetLogz(1);
   
    c2->SaveAs(Form("Plots/HMS_CER_LOOSE_WINDOW_Pmt%d.pdf",ipmt+1));

    // TImage *img1 = TImage::Create();
    // img1->FromPad(c2);
    // img1->WriteImage(Form("more_hgc_pmt%i.png",ipmt+1));
  }

  //******1pr pos Draw*********
  TCanvas *c3 = new TCanvas("c3", "HCAL_LOOSE_WINDOW_1PR_POS", 600,600);
  c3->Divide(2,3); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 13; ipmt++) {

    c3->cd(1);  gPad->SetGrid(); gPad->SetLogy();
    h1prCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c3->cd(2); gPad->SetGrid();
    h1prCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c3->cd(3);  gPad->SetGrid(); gPad->SetLogy();
    h1prCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h1prCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw();   
        
    c3->cd(4); gPad->SetGrid(); 
    h1prCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c3->cd(5); gPad->SetGrid(); gPad->SetLogy();
    h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw();

    c3->cd(6); gPad->SetGrid();  gPad->SetGrid();
    h1prCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c3->SaveAs(Form("Plots/HMS_CAL_LAYER_1_POS_LOOSE_WINDOW_Pmt%d.pdf",ipmt+1));

  }

TCanvas *c9 = new TCanvas("c9","HCAL_LOOSE_WINDOW_1PR_POS_ALL",600,600); 
  c9->Divide(1,2); gPad->SetGrid();

  for (Int_t ipmt=0; ipmt < 13; ipmt++) {
    c9->cd(1); gPad->SetGrid();gPad->SetLogy();
    h1prCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);
    h1prCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h1prCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw("same");   
    h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");

    c9->cd(2); gPad->SetGrid();
    h1prCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c9->SaveAs(Form("Plots/HMS_CAL_LAYER_1_POS_LOOSE_WINDOW_ALL_Pmt%d.pdf",ipmt+1));
  }


  //*************1pr neg Draw****************
  TCanvas *c4 = new TCanvas("c4", "HCAL_LOOSE_WINDOW_1PR_NEG", 600,600);
  c4->Divide(2,3); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 13; ipmt++) {

    c4->cd(1);  gPad->SetGrid(); gPad->SetLogy();
    h1prCALNegAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c4->cd(2); gPad->SetGrid();
    h1prCALNegPulseAmpVsPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c4->cd(3);  gPad->SetGrid(); gPad->SetLogy();
    h1prCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h1prCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw();   
        
    c4->cd(4); gPad->SetGrid(); 
    h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c4->cd(5); gPad->SetGrid(); gPad->SetLogy();
    h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw();

    c4->cd(6); gPad->SetGrid();  gPad->SetGrid();
    h1prCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c4->SaveAs(Form("Plots/HMS_CAL_LAYER_1_NEG_LOOSE_WINDOW_Pmt%d.pdf",ipmt+1));

  }

TCanvas *c10 = new TCanvas("c10","HCAL_LOOSE_WINDOW_1PR_NEG_ALL",600,600); 
  c10->Divide(1,2); gPad->SetGrid();

  for (Int_t ipmt=0; ipmt < 13; ipmt++) {
    c10->cd(1); gPad->SetGrid();gPad->SetLogy();
    h1prCALNegAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);
    h1prCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h1prCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw("same");   
    h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");

    c10->cd(2); gPad->SetGrid();
    h1prCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c10->SaveAs(Form("Plots/HMS_CAL_LAYER_1_NEG_LOOSE_WINDOW_ALL_Pmt%d.pdf",ipmt+1));
  }






  //**********1pr cal pos neg Draw done*************
  //**********2ta cal pos Draw ***********

 TCanvas *c5 = new TCanvas("c5", "HCAL_LOOSE_WINDOW_2TA_POS", 600,600);
  c5->Divide(2,3); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 13; ipmt++) {

    c5->cd(1);  gPad->SetGrid(); gPad->SetLogy();
    h2taCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c5->cd(2); gPad->SetGrid();
    h2taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c5->cd(3);  gPad->SetGrid(); gPad->SetLogy();
    h2taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h2taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw();   
        
    c5->cd(4); gPad->SetGrid(); 
    h2taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c5->cd(5); gPad->SetGrid(); gPad->SetLogy();
    h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw();

    c5->cd(6); gPad->SetGrid();  gPad->SetGrid();
    h2taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c5->SaveAs(Form("Plots/HMS_CAL_LAYER_2_POS_LOOSE_WIN_Pmt%d.pdf",ipmt+1));

  }


TCanvas *c14 = new TCanvas("c14","HCAL_LOOSE_WINDOW_2ta_POS_ALL",600,600); 
  c14->Divide(1,2); gPad->SetGrid();

  for (Int_t ipmt=0; ipmt < 13; ipmt++) {
    c14->cd(1); gPad->SetGrid();gPad->SetLogy();
    h2taCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);
    h2taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h2taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw("same");   
    h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");

    c14->cd(2); gPad->SetGrid();
    h2taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c14->SaveAs(Form("Plots/HMS_CAL_LAYER_2_POS_LOOSE_WINDOW_ALL_Pmt%d.pdf",ipmt+1));
  }






  //**********2ta cal neg Draw ***********
TCanvas *c6 = new TCanvas("c6", "HCAL_LOOSE_WINDOW_2TA_NEG", 600,600);
  c6->Divide(2,3); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 13; ipmt++) {

    c6->cd(1);  gPad->SetGrid(); gPad->SetLogy();
    h2taCALNegAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c6->cd(2); gPad->SetGrid();
    h2taCALNegPulseAmpVsPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c6->cd(3);  gPad->SetGrid(); gPad->SetLogy();
    h2taCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h2taCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw();   
        
    c6->cd(4); gPad->SetGrid(); 
    h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c6->cd(5); gPad->SetGrid(); gPad->SetLogy();
    h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw();

    c6->cd(6); gPad->SetGrid();  gPad->SetGrid();
    h2taCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c6->SaveAs(Form("Plots/HMS_CAL_LAYER_2_NEG_LOOSE_WINDOW_Pmt%d.pdf",ipmt+1));

  }



TCanvas *c15 = new TCanvas("c15","HCAL_LOOSE_WINDOW_2ta_NEG_ALL",600,600); 
  c15->Divide(1,2); gPad->SetGrid();

  for (Int_t ipmt=0; ipmt < 13; ipmt++) {
    c15->cd(1); gPad->SetGrid();gPad->SetLogy();
    h2taCALNegAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);
    h2taCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h2taCALNegAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw("same");   
    h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");

    c15->cd(2); gPad->SetGrid();
    h2taCALgoodNegPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c15->SaveAs(Form("Plots/HMS_CAL_LAYER_2_NEG_LOOSE_WINDOW_ALL_Pmt%d.pdf",ipmt+1));
  }


  //**********2ta Draw done**********

  //****************3ta pos ***********


 TCanvas *c7 = new TCanvas("c7", "HCAL_LOOSE_WINDOW_3TA_POS", 600,600);
  c7->Divide(2,3); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 13; ipmt++) {

    c7->cd(1);  gPad->SetGrid(); gPad->SetLogy();
    h3taCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c7->cd(2); gPad->SetGrid();
    h3taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c7->cd(3);  gPad->SetGrid(); gPad->SetLogy();
    h3taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h3taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw();   
        
    c7->cd(4); gPad->SetGrid(); 
    h3taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c7->cd(5); gPad->SetGrid(); gPad->SetLogy();
    h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw();

    c7->cd(6); gPad->SetGrid();  gPad->SetGrid();
    h3taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c7->SaveAs(Form("Plots/HMS_CAL_LAYER_3_POS_LOOSE_WINDOW_Pmt%d.pdf",ipmt+1));

  }


TCanvas *c11 = new TCanvas("c11","HCAL_LOOSE_WINDOW_3ta_POS_ALL",600,600); 
  c11->Divide(1,2); gPad->SetGrid();

  for (Int_t ipmt=0; ipmt < 13; ipmt++) {
    c11->cd(1); gPad->SetGrid();gPad->SetLogy();
    h3taCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);
    h3taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h3taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw("same");   
    h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");

    c11->cd(2); gPad->SetGrid();
    h3taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c11->SaveAs(Form("Plots/HMS_CAL_LAYER_3_POS_LOOSE_WINDOW_ALL_Pmt%d.pdf",ipmt+1));
  }





  //**********3ta pos done*************
  //**********4ta pos*****************


 TCanvas *c8 = new TCanvas("c8", "HCAL_LOOSE_WINDOW_4TA_POS", 600,600);
  c8->Divide(2,3); gPad->SetGrid();
  for (Int_t ipmt=0; ipmt < 13; ipmt++) {

    c8->cd(1);  gPad->SetGrid(); gPad->SetLogy();
    h4taCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c8->cd(2); gPad->SetGrid();
    h4taCALPosPulseAmpVsPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);

    c8->cd(3);  gPad->SetGrid(); gPad->SetLogy();
    h4taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h4taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw();   
        
    c8->cd(4); gPad->SetGrid(); 
    h4taCALPosPulseAmpVsPulseTimeStarttimeDiffMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c8->cd(5); gPad->SetGrid(); gPad->SetLogy();
    h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw();

    c8->cd(6); gPad->SetGrid();  gPad->SetGrid();
    h4taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c8->SaveAs(Form("Plots/HMS_CAL_LAYER_4_POS_LOOSE_WINDOW_Pmt%d.pdf",ipmt+1));

  }


TCanvas *c12 = new TCanvas("c12","HCAL_LOOSE_WINDOW_4ta_POS_ALL",600,600); 
  c12->Divide(1,2); gPad->SetGrid();

  for (Int_t ipmt=0; ipmt < 13; ipmt++) {
    c12->cd(1); gPad->SetGrid();gPad->SetLogy();
    h4taCALPosAdcPulseTimeStarttimeDiff[ipmt]->Draw("colz");gPad->SetLogz(1);
    h4taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->SetLineColor(kRed);
    h4taCALPosAdcPulseTimeStarttimeDiffMultCer[ipmt]->Draw("same");   
    h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kMagenta);
    h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");

    c12->cd(2); gPad->SetGrid();
    h4taCALgoodPosPulseAmpVsPulseTimeMultCer[ipmt]->Draw("colz");gPad->SetLogz(1);

    c12->SaveAs(Form("Plots/HMS_CAL_LAYER_4_POS_LOOSE_WINDOW_ALL_Pmt%d.pdf",ipmt+1));
  }

  //************4ta pos done****************

  //***********overlap all on same canvas**************
  
  TCanvas *c16 = new TCanvas("c16","HCAL_LOOSE_WINDOW_GOOD_PULSEAMP_VS_ADCTDC_TIME_DIFF",600,600);
  c16->Divide(1,2);

  for (Int_t ipmt=0;ipmt<13; ipmt++){
    c16->cd(1);gPad->SetGrid();gPad->SetLogy();
    if(ipmt ==0)
      {
	h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw();
	h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
	h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kBlue);
	
	h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
	h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kBlue+3);

	h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
	h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kRed);

	h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
	h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kRed-7);
	h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
	h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->SetLineColor(kBlack);
      }
    if (ipmt ==1)
      {
	
	
    	h1prCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw();
    	h1prCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
    	h2taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
    	h2taCALNeggoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
    	h3taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
    	h4taCALPosgoodAdcTdcDiffTimeMultCer[ipmt]->Draw("same");
	
      }

    //}
  // c16->SaveAs(Form("Plots/HMS_CAL_GOOD_ALL_PMT_pMT%d.pdf",ipmt+1));
  c16->SaveAs("test.pdf");

  }





    //**********done overlap***********************//

  //cout<<h1prCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer->GetEntries()<<endl;



  //***********added done*************
  
  // TDirectory *DCAL = Histogram_file->mkdir("Shower ADC Timing Spectra"); DCAL->cd();
  // for (Int_t ipmt=0; ipmt < 13; ipmt++) {
  //   //pr1 CAL NEG
  //   TCanvas *c1 = new TCanvas("c1","c1",800,900);  
  //   c1->Divide(1,2);
  //   c1->cd(1);
  //   h1H1prCALNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H1prCALNegPulseAmp[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H1prCALNegPulseAmp[ipmt]->Draw("colz");
  //   c1->cd(2);
  //   gPad->SetLogy();
  //   h1H1prCALNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H1prCALNegPulseTime[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H1prCALNegPulseTime[ipmt]->SetLineColor(4);
  //   h1H1prCALNegPulseTime[ipmt]->Draw();
  //   TImage *img1 = TImage::Create();
  //   img1->FromPad(c1);
  //   img1->WriteImage(Form("1pr_cal_neg_pmt%i.png",ipmt+1));

  //   //pr1 CAL POS
  //   TCanvas *c2 = new TCanvas("c2","c2",800,900);  
  //   c2->Divide(1,2);
  //   c2->cd(1);
  //   h1H1prCALPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H1prCALPosPulseAmp[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H1prCALPosPulseAmp[ipmt]->Draw("colz");
  //   c2->cd(2);
  //   gPad->SetLogy();
  //   h1H1prCALPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H1prCALPosPulseTime[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H1prCALPosPulseTime[ipmt]->SetLineColor(4);
  //   h1H1prCALPosPulseTime[ipmt]->Draw();
  //   TImage *img2 = TImage::Create();
  //   img2->FromPad(c2);
  //   img2->WriteImage(Form("1pr_cal_pos_pmt%i.png",ipmt+1));

  //   //ta2 CAL NEG
  //   TCanvas *c3 = new TCanvas("c3","c3",800,900);
  //   c3->Divide(1,2);  
  //   c3->cd(1);
  //   h1H2taCALNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H2taCALNegPulseAmp[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H2taCALNegPulseAmp[ipmt]->Draw("colz");
  //   c3->cd(2);
  //   gPad->SetLogy();
  //   h1H2taCALNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H2taCALNegPulseTime[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H2taCALNegPulseTime[ipmt]->SetLineColor(4);
  //   h1H2taCALNegPulseTime[ipmt]->Draw();
  //   TImage *img3 = TImage::Create();
  //   img3->FromPad(c3);
  //   img3->WriteImage(Form("2ta_cal_neg_pmt%i.png",ipmt+1));

  //   //ta2 CAL POS
  //   TCanvas *c4 = new TCanvas("c4","c4",800,900);
  //   c4->Divide(1,2); 
  //   c4->cd(1);
  //   h1H2taCALPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H2taCALPosPulseAmp[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H2taCALPosPulseAmp[ipmt]->Draw("colz");
  //   c4->cd(2);
  //   gPad->SetLogy();
  //   h1H2taCALPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H2taCALPosPulseTime[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H2taCALPosPulseTime[ipmt]->SetLineColor(4);
  //   h1H2taCALPosPulseTime[ipmt]->Draw();
  //   TImage *img4 = TImage::Create();
  //   img4->FromPad(c4);
  //   img4->WriteImage(Form("2ta_cal_pos_pmt%i.png",ipmt+1));

  //   // H3taCALNEGPULSETIMEDIFF[ipmt]->Write(Form("3ta CAL NEG PMT %i",ipmt+1));

  //   //ta3 CAL POS
  //   TCanvas *c5 = new TCanvas("c5","c5",800,900); 
  //   c5->Divide(1,2);  
  //   c5->cd(1);
  //   h1H3taCALPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H3taCALPosPulseAmp[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H3taCALPosPulseAmp[ipmt]->Draw("colz");
  //   c5->cd(2);
  //   gPad->SetLogy();
  //   h1H3taCALPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H3taCALPosPulseTime[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H3taCALPosPulseTime[ipmt]->SetLineColor(4);
  //   h1H3taCALPosPulseTime[ipmt]->Draw();


  //   TImage *img5 = TImage::Create();
  //   img5->FromPad(c5);
  //   img5->WriteImage(Form("3ta_cal_pos_pmt%i.png",ipmt+1));

  //   // H4taCALNEGPULSETIMEDIFF[ipmt]->Write(Form("4ta CAL NEG PMT %i",ipmt+1));

  //   //ta4 CAL POS
  //   TCanvas *c6 = new TCanvas("c6","c6",800,900); 
  //   c6->Divide(1,2);  
  //   c6->cd(1);
  //   h1H4taCALPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H4taCALPosPulseAmp[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H4taCALPosPulseAmp[ipmt]->Draw("colz");
  //   c6->cd(2);
  //   gPad->SetLogy();
  //   h1H4taCALPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1H4taCALPosPulseTime[ipmt]->GetXaxis()->SetTitleOffset(1.4);
  //   h1H4taCALPosPulseTime[ipmt]->SetLineColor(4);
  //   h1H4taCALPosPulseTime[ipmt]->Draw();
  //   TImage *img6 = TImage::Create();
  //   img6->FromPad(c6);
  //   img6->WriteImage(Form("4ta_cal_pos_pmt%i.png",ipmt+1));

  // }
  
  //  TDirectory *DHODO = Histogram_file->mkdir("Hodoscope ADC Timing Spectra"); DHODO->cd();
  // for (Int_t ipmt=0; ipmt < 16; ipmt++) // {
  //   //1y NEG
  //   TCanvas *c1 = new TCanvas("c1","c1",800,900);   
  //   c1->Divide(1,2);
  //   c1->cd(1);
  //   h1HHODO1yNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1yNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1yNegPulseAmp[ipmt]->Draw("colz"); 
  //   c1->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO1yNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1yNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO1yNegPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO1yNegPulseTime[ipmt]->Draw(); 
  //   TImage *img1 = TImage::Create();
  //   img1->FromPad(c1);
  //   img1->WriteImage(Form("hodo_1y_neg_pmt%i.png",ipmt+1));

  //   //2y NEG
  //   TCanvas *c2 = new TCanvas("c2","c2",800,900);
  //   c2->Divide(1,2);  
  //   c2->cd(1);
  //   h1HHODO2yNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2yNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2yNegPulseAmp[ipmt]->Draw("colz");
  //   c2->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO2yNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2yNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO2yNegPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO2yNegPulseTime[ipmt]->Draw();
  //   TImage *img2 = TImage::Create();
  //   img2->FromPad(c2);
  //   img2->WriteImage(Form("hodo_2y_neg_pmt%i.png",ipmt+1));

  //   //1y POS
  //   TCanvas *c3 = new TCanvas("c3","c3",800,900); 
  //   c3->Divide(1,2);
  //   c3->cd(1);
  //   h1HHODO1yPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1yPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1yPosPulseAmp[ipmt]->Draw("colz");
  //   c3->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO1yPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1yPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO1yPosPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO1yPosPulseTime[ipmt]->Draw();
  //   TImage *img3 = TImage::Create();
  //   img3->FromPad(c3);
  //   img3->WriteImage(Form("hodo_1y_pos_pmt%i.png",ipmt+1));

  //   //2y POS
  //   TCanvas *c4 = new TCanvas("c4","c4",800,900);
  //   c4->Divide(1,2);  
  //   c4->cd(1);
  //   h1HHODO2yPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2yPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2yPosPulseAmp[ipmt]->Draw("colz");
  //   c4->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO2yPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2yPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO2yPosPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO2yPosPulseTime[ipmt]->Draw();
  //   TImage *img4 = TImage::Create();
  //   img4->FromPad(c4);
  //   img4->WriteImage(Form("hodo_2y_pos_pmt%i.png",ipmt+1));

  //   //1x NEG
  //   TCanvas *c5 = new TCanvas("c5","c5",800,900);  
  //   c5->Divide(1,2);
  //   c5->cd(1);
  //   h1HHODO1xNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1xNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1xNegPulseAmp[ipmt]->Draw("colz");
  //   c5->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO1xNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1xNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO1xNegPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO1xNegPulseTime[ipmt]->Draw();
  //   TImage *img5 = TImage::Create();
  //   img5->FromPad(c5);
  //   img5->WriteImage(Form("hodo_1x_neg_pmt%i.png",ipmt+1));

  //   //2x neg
  //   TCanvas *c6 = new TCanvas("c6","c6",800,900); 
  //   c6->Divide(1,2); 
  //   c6->cd(1);
  //   h1HHODO2xNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2xNegPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1HHODO2xNegPulseAmp[ipmt]->Draw("colz");
  //   c6->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO2xNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2xNegPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO2xNegPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO2xNegPulseTime[ipmt]->Draw();
  //   TImage *img6 = TImage::Create();
  //   img6->FromPad(c6);
  //   img6->WriteImage(Form("hodo_2x_neg_pmt%i.png",ipmt+1));

  //   //1x POS
  //   TCanvas *c7 = new TCanvas("c7","c7",800,900);  
  //   c7->Divide(1,2);
  //   c7->cd(1);
  //   h1HHODO1xPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1xPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1HHODO1xPosPulseAmp[ipmt]->Draw("colz"); 
  //   c7->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO1xPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO1xPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO1xPosPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO1xPosPulseTime[ipmt]->Draw();
  //   TImage *img7 = TImage::Create();
  //   img7->FromPad(c7);
  //   img7->WriteImage(Form("hodo_1x_pos_pmt%i.png",ipmt+1));

  //   //2x POS
  //   TCanvas *c8 = new TCanvas("c8","c8",800,900);
  //   c8->Divide(1,2);  
  //   c8->cd(1);
  //   h1HHODO2xPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2xPosPulseAmp[ipmt]->GetYaxis()->SetTitleOffset(1.4);
  //   h1HHODO2xPosPulseAmp[ipmt]->Draw("colz");
  //   c8->cd(2);
  //   gPad->SetLogy();
  //   h1HHODO2xPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4); 
  //   h1HHODO2xPosPulseTime[ipmt]->GetYaxis()->SetTitleOffset(1.4);  
  //   h1HHODO2xPosPulseTime[ipmt]->SetLineColor(4);
  //   h1HHODO2xPosPulseTime[ipmt]->Draw();
  //   TImage *img8 = TImage::Create();
  //   img8->FromPad(c8);
  //   img8->WriteImage(Form("hodo_1y_neg_pmt%i.png",ipmt+1));
  // }

  // TDirectory *DDC = Histogram_file->mkdir("Drift Chamber ADC Timing Spectra"); DDC->cd();
  //for (Int_t iplane = 0; iplane < 2; iplane++) // {
  //   HDCRAWTDC[6*iplane]->Write(Form("DC %du1 Plane",iplane+1));
  //   HDCRAWTDC[6*iplane+1]->Write(Form("DC %dv1 Plane",iplane+1));
  //   HDCRAWTDC[6*iplane+2]->Write(Form("DC %dx1 Plane",iplane+1));
  //   HDCRAWTDC[6*iplane+3]->Write(Form("DC %du2 Plane",iplane+1));
  //   HDCRAWTDC[6*iplane+4]->Write(Form("DC %dv2 Plane",iplane+1));
  //   HDCRAWTDC[6*iplane+5]->Write(Form("DC %dx2 Plane",iplane+1));
  // }
  
  //Histogram_file->Close();
}                  
