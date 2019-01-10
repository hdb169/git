Do the timing cuts and reference times
Reference Time is in PARAM/SHMS/GEN
#define SHMSADCGates_cxx
// The class definition in SHMSADCGates.h has been generated automatically
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
// root> T->Process("SHMSADCGates.C")
// root> T->Process("SHMSADCGates.C","some options")
// root> T->Process("SHMSADCGates.C+")
//

#include "SHMSADCGates.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>

void SHMSADCGates::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
}

void SHMSADCGates::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  h1PHGCERPulseTimeStarttimeDiff_CalCut = new TH1F*[4];
  
  //****************** HgCer( 4 pmts) **********************************//
  h1PHGCERPulseTime              = new TH1F*[4];
  h1PHGCERPulseTimeStarttimeDiff = new TH1F*[4];
  h1PHGCERPGoodAdcTdcDiffTime = new TH1F*[4];
  h1PHGCERPGoodAdcTdcDiffTime_Mult = new TH1F*[4];
  h1PHGCERPulseTimeVsPulseAmp = new TH2F*[4];
  h1PHGCERPulseTimeStarttimeDiffMult = new TH1F*[4];
  h1PHGCERPulseTimeStarttimeDiffMultCut = new TH1F*[4];
  h1PHGCERPulseTimeVsPulseAmpMultCut = new TH2F*[4];
  //**********ADDED**********
  h1PHGCERLowTimePickShwrVsPrshwr = new TH2F*[4];//added
  h1PHGCERHighTimePickShwrVsPrshwr = new TH2F*[4];//added
  h1DeltawithHigherPulseTime = new TH1F*[4];//added
  h1DeltawithLowerPulseTime = new TH1F*[4];//added

  h1DeltaVsBetaLowerPulseTime = new TH2F*[4];
  h1DeltaVsBetaHigherPulseTime = new TH2F*[4];//P.gtr.dp : P.gtr.beta
  h1PdcyfpVsPdcxfpLowerPulseTime = new TH2F*[4];//P.dc.x_fp
  h1PdcyfpVsPdcxfpHigherPulseTime = new TH2F*[4];
  h1YtarVsXtarLowerPulseTime = new TH2F*[4];//P.gtr.th =ytar
  h1YtarVsXtarHigherPulseTime = new TH2F*[4];//P.gtr.ph =xtar
  h1PdcresidualLowerTime =new TH1F*[12];
  h1PdcresidualHigherTime =new TH1F*[12];


  //**********// 
for (Int_t i = 0; i < 12; i++){
    h1PdcresidualLowerTime[i] = new TH1F(Form("Pdcresidual%d",i+1),Form(" DC RESIDUALS Lower Pulse Time %d; Residual; Counts",i),100,-0.5,0.5);
    h1PdcresidualHigherTime[i] = new TH1F(Form("Pdcresidual%d",i+1),Form(" DC RESIDUALS Higher Pulse Time %d; Residual; Counts",i),100,-0.5,0.5);
  }


  for (Int_t ipmt=0; ipmt<4; ipmt++){
    h1PHGCERPulseTime[ipmt] = new TH1F(Form("PHGCERPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS HGC PMT%d;Time (ns);Counts",ipmt+1),1000,-300,100);

    h1PHGCERPulseTimeVsPulseAmp[ipmt] = new TH2F(Form("PHGCERPulseTimeVsPulseAmp%d",ipmt+1),Form("Pulse Time Vs Pulse Amp PMT%d;PulseTime(ns); Pulse Amp",ipmt+1),1000,-300,100, 1000, 0, 1000);

    h1PHGCERPulseTimeVsPulseAmpMultCut[ipmt] = new TH2F(Form("PHGCERPulseTimeVsPulseAmpMultCut%d",ipmt+1),Form("Pulse Time Vs Pulse Amp PMT MultCut%d;PulseTime(ns); Pulse Amp",ipmt+1),1000,-300,100, 1000, 0, 1000);

    h1PHGCERPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHGCERPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HGC  PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300,100);
    
    h1PHGCERPulseTimeStarttimeDiffMult[ipmt] = new TH1F(Form("PHGCERPulseTimeStarttimeDiffMult%d",ipmt+1),Form("Pulse Time Information for SHMS HGC  PMT Mult=1 %d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300,100);

    h1PHGCERPulseTimeStarttimeDiffMultCut[ipmt] = new TH1F(Form("PHGCERPulseTimeStarttimeDiffMultCut%d",ipmt+1),Form("Pulse Time Information for SHMS HGC  PMT Mult=1&eCut %d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300,100);
    
    h1PHGCERPulseTimeStarttimeDiff_CalCut[ipmt] = new TH1F(Form("PHGCERPulseTimeStarttimeDiff_CalCut%d",ipmt+1),Form("Pulse Time Information for SHMS HGC  PMT%d Start Time Subtracted (CUT);Time (ns);Counts",ipmt+1),1000,-300,100);
    h1PHGCERPGoodAdcTdcDiffTime[ipmt] = new TH1F(Form("PHGCERGoodAdcTdcDiffTime%d",ipmt+1), Form("HGCER Good Adc Tdc Time Diff PMT%d", ipmt+1), 1000, -300, 100);
    h1PHGCERPGoodAdcTdcDiffTime_Mult[ipmt] = new TH1F(Form("PHGCERGoodAdcTdcDiffTimeMult%d",ipmt+1), Form("HGCER Good Adc Tdc Time Diff withMult PMT%d", ipmt+1), 1000, -300, 100);
    //***************ADDED***********    
    h1PHGCERLowTimePickShwrVsPrshwr[ipmt] = new TH2F(Form("PHGCERLowTimePickShwrVsPrshwr%d",ipmt+1),Form("Preshwr vs Shwr with lower time pick PMT%d; Shower; PreShower",ipmt+1),100,0.001,1.8, 100, 0.001, 2);
    h1PHGCERHighTimePickShwrVsPrshwr[ipmt] = new TH2F(Form("PHGCERHighTimePickShwrVsPrshwr%d",ipmt+1),Form("Preshwr vs Shwr with higher time pick PMT%d; Shower; Preshower",ipmt+1),100,0.001,1.8, 100, 0.001, 2);
    h1DeltawithLowerPulseTime[ipmt] = new TH1F(Form("DeltawithLowerPulseTime%d",ipmt+1), Form("SHMS DELTA with Lower Pulse Time PMT%d", ipmt+1), 100, -20,25);
    h1DeltawithHigherPulseTime[ipmt] = new TH1F(Form("DeltawithHigherPulseTime%d",ipmt+1), Form("SHMS DELTA with Higher Pulse Time PMT%d", ipmt+1), 100, -20,25);

    h1DeltaVsBetaHigherPulseTime[ipmt] = new TH2F(Form("DeltaVsBetaHigherPulseTime%d",ipmt+1),Form("Delta Vs Beta Higher Pulse Time PMT%d; BETA; DELTA",ipmt+1),100,0,2,100,-20,25);
    h1DeltaVsBetaLowerPulseTime[ipmt] = new TH2F(Form("DeltaVsBetaLowerPulseTime%d",ipmt+1),Form("Delta Vs Beta Lower Pulse Time PMT%d; BETA; DELTA",ipmt+1),100,0,2,100,-20,25);

    h1PdcyfpVsPdcxfpLowerPulseTime[ipmt] =  new TH2F(Form("YfpVsXfpLowerPulseTime%d",ipmt+1),Form(" X_fp vs Y_fp Lower Pulse Time PMT%d; YFP; XFP",ipmt+1),100,-40,40,100,-40,40);
    h1PdcyfpVsPdcxfpHigherPulseTime[ipmt] =  new TH2F(Form("YfpVsXfpHigherPulseTime%d",ipmt+1),Form("X_fp vs Y_fp Higher Pulse TimePMT%d; YFP; XFP",ipmt+1),100,-40, 40,100,-40,40);

    h1YtarVsXtarLowerPulseTime[ipmt] = new TH2F(Form("YtarVsXtarLowerPulseTime%d",ipmt+1),Form("Xtar Vs Ytar Lower Pulse Time PMT%d; YTar; XTar",ipmt+1),100,-0.08,0.08,100,-0.08,0.08);
    h1YtarVsXtarHigherPulseTime[ipmt] = new TH2F(Form("YtarVsXtarHigherPulseTime%d",ipmt+1),Form("Xtar Vs Ytar Higher Pulse Time PMT%d; YTar; XTar",ipmt+1),100,-0.08,0.08,100,-0.08,0.08);
   

    //  GetOutputList()->Add(h1Pdcresidual[iplane]);
    //****************added done***//

    GetOutputList()->Add(h1PHGCERPulseTime[ipmt]);
    GetOutputList()->Add(h1PHGCERPulseTimeStarttimeDiff[ipmt]);

    
    // }
    // for (Int_t iplane=0; ipmt<12 iplane++)
    //   {
    //   h1Pdcresiduals[iplane] = new TH1F(Form("Pdcresidual%d",iplane+1),Form(" DC RESIDUALS %d; Residual; Counts",iplane+1),100,-0.5,0.5);
    //    GetOutputList()->Add(h1Pdcresidual[iplane]);
  }


 
	//******************************************AEROGEL*******************************************************//

  /* (1)
  h1PAEROPosPulseTime                     = new TH1F*[7];
  h1PAEROPosPulseTimeStarttimeDiff        = new TH1F*[7];
  h1PAEROPosPulseTimeStarttimeDiffMult    = new TH1F*[7];
  h1PAEROPosPulseTimeStarttimeDiffMultCut = new TH1F*[7];
  h1PAEROPosPulseTimeStarttimeDiff_CalCut = new TH1F*[7];
  h1PAEROPosPulseTimeVsPulseAmp           = new TH2F*[7];
  h1PAEROPosPulseTimeVsPulseAmpMultCut    = new TH2F*[7];


  h1PAERONegPulseTime                     = new TH1F*[7];
  h1PAERONegPulseTimeStarttimeDiff        = new TH1F*[7];
  h1PAERONegPulseTimeStarttimeDiffMult    = new TH1F*[7];
  h1PAERONegPulseTimeStarttimeDiffMultCut = new TH1F*[7];
  h1PAERONegPulseTimeStarttimeDiff_CalCut = new TH1F*[7];
  h1PAERONegPulseTimeVsPulseAmp           = new TH2F*[7];
  h1PAERONegPulseTimeVsPulseAmpMultCut    = new TH2F*[7];


  h1PAEROGoodPosAdcTdcDiffTime            = new TH1F*[7];
  h1PAEROGoodNegAdcTdcDiffTime            = new TH1F*[7];
  h1PAEROGoodPosAdcTdcDiffTime_Cut        = new TH1F*[7];
  h1PAEROGoodNegAdcTdcDiffTime_Cut        = new TH1F*[7];

   
  for (Int_t ipmt=0; ipmt<7; ipmt++) {

    h1PAERONegPulseTime[ipmt] = new TH1F(Form("PAERONegPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Neg PMT%d;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAERONegPulseTimeVsPulseAmp[ipmt] = new TH2F(Form("PAERONegPulseTimeVsPulseAmp%d",ipmt+1),Form("Pulse Time Vs Pulse Neg Amp PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-300, 700, 1000, 0, 1000);

    h1PAEROPosPulseTimeVsPulseAmp[ipmt] = new TH2F(Form("PAEROPosPulseTimeVsPulseAmp%d",ipmt+1),Form("Pulse Time Vs Pulse Amp Pos PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-300, 700, 1000, 0, 1000);

    h1PAERONegPulseTimeVsPulseAmpMultCut[ipmt] = new TH2F(Form("PAERONegPulseTimeVsPulseAmpWithMultCut%d",ipmt+1),Form("Pulse Time Vs Pulse Amp NegMultCut PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-300, 700, 1000, 0, 1000);
    
    h1PAEROPosPulseTimeVsPulseAmpMultCut[ipmt] = new TH2F(Form("PAEROPosPulseTimeVsPulseAmpWithMultCut%d",ipmt+1),Form("Pulse Time Vs Pulse Amp PosMultCut PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-300, 700, 1000, 0, 1000);

    h1PAERONegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PAERONegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAERONegPulseTimeStarttimeDiffMult[ipmt] = new TH1F(Form("PAERONegPulseTimeStarttimeDiffMult%d",ipmt+1),Form("Pulse Time with Mult AERO Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAERONegPulseTimeStarttimeDiffMultCut[ipmt] = new TH1F(Form("PAERONegPulseTimeStarttimeDiffMultCut%d",ipmt+1),Form("Pulse Time MultCut for SHMS AERO Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300, 700);

      
    h1PAEROPosPulseTimeStarttimeDiffMult[ipmt] = new TH1F(Form("PAEROPosPulseTimeStarttimeDiffMult%d",ipmt+1),Form("Pulse Time with Mult AERO Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROPosPulseTimeStarttimeDiffMultCut[ipmt] = new TH1F(Form("PAEROPosPulseTimeStarttimeDiffMultCut%d",ipmt+1),Form("Pulse Time MultCut for SHMS AERO Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROPosPulseTime[ipmt] = new TH1F(Form("PAEROPosPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Pos PMT%d;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PAEROPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAERONegPulseTimeStarttimeDiff_CalCut[ipmt] = new TH1F(Form("PAERONegPulseTimeStarttimeDiff_Cut%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Neg PMT%d Start Time Subtracted(cut);Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROPosPulseTimeStarttimeDiff_CalCut[ipmt] = new TH1F(Form("PAEROPosPulseTimeStarttimeDiff_Cut%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Pos PMT%d Start Time Subtracted(cut);Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROGoodPosAdcTdcDiffTime[ipmt] =  new TH1F(Form("PAEROGoodPosAdcTdcDiffTime%d",ipmt+1),Form(" SHMS AERO GOOD Pos Adc Tdc Diff Time%d;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROGoodPosAdcTdcDiffTime_Cut[ipmt] =  new TH1F(Form("PAEROGoodPosAdcTdcDiffTimeCut%d",ipmt+1),Form(" SHMS AERO GOOD Pos Adc Tdc Diff TimeCut%d;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROGoodNegAdcTdcDiffTime[ipmt] =  new TH1F(Form("PAEROGoodNegAdcTdcDiffTime%d",ipmt+1),Form(" SHMS AERO GOOD Neg Adc Tdc Diff Time PMT_%d;Time (ns);Counts",ipmt+1),1000,-300, 700);

    h1PAEROGoodNegAdcTdcDiffTime_Cut[ipmt] =  new TH1F(Form("PAEROGoodNegAdcTdcDiffTimeCut%d",ipmt+1),Form(" SHMS AERO Neg Adc Tdc Diff TimeCut%d;Time (ns);Counts",ipmt+1),1000,-300, 700);

    GetOutputList()->Add(h1PAERONegPulseTime[ipmt]);
    GetOutputList()->Add(h1PAERONegPulseTimeStarttimeDiff[ipmt]);
    GetOutputList()->Add(h1PAEROPosPulseTime[ipmt]);
    GetOutputList()->Add(h1PAEROPosPulseTimeStarttimeDiff[ipmt]);
  }
   
  *///(1)

  //*************************PRESHOWER HISTO ******************************************//

  /*(2)

  h1PPRECALNegPulseTime                     = new TH1F*[14];
  h1PPRECALNegPulseTimeStarttimeDiff        = new TH1F*[14];
  h1PPRECALNegPulseTimeStarttimeDiffMult    = new TH1F*[14];
  h1PPRECALNegPulseTimeStarttimeDiffMultCut = new TH1F*[14];
  h1PPRECALNegPulseTimeStarttimeDiff_CalCut = new TH1F*[14];
  
  h1PPRECALNegPulseTimeVsPulseAmp           = new TH2F*[14];
  h1PPRECALNegPulseTimeVsPulseAmpMultCut    = new TH2F*[14];
 
  h1PPRECALPosPulseTime                     = new TH1F*[14];
  h1PPRECALPosPulseTimeStarttimeDiff        = new TH1F*[14];
  h1PPRECALPosPulseTimeStarttimeDiff_CalCut = new TH1F*[14];
  h1PPRECALPosPulseTimeStarttimeDiffMult    = new TH1F*[14];
  h1PPRECALPosPulseTimeStarttimeDiffMultCut = new TH1F*[14];
    
  h1PPRECALPosPulseTimeVsPulseAmpMultCut    = new TH2F*[14];
  h1PPRECALPosPulseTimeVsPulseAmp           = new TH2F*[14];
  
  h1PPRECALGoodPosAdcTdcDiffTime            = new TH1F*[14];
  h1PPRECALGoodNegAdcTdcDiffTime            = new TH1F*[14];
  h1PPRECALGoodPosAdcTdcDiffTime_Cut        = new TH1F*[14];
  h1PPRECALGoodNegAdcTdcDiffTime_Cut        = new TH1F*[14];

  */
  /////*****************************************PRESHWOR***************************************************

  /*  for (Int_t ipmt=0; ipmt<14; ipmt++) {

    h1PPRECALNegPulseTime[ipmt] = new TH1F(Form("PPRECALNegPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Neg PMT%d;Time (ns);Counts",ipmt+1),1000,-500, 500);

    h1PPRECALNegPulseTimeVsPulseAmp[ipmt] = new TH2F(Form("PreCALNegPulseTimeVsPulseAmp%d",ipmt+1),Form("Pulse Time Vs Pulse Neg Amp PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-500, 500, 1000, 0, 1000);

    h1PPRECALPosPulseTimeVsPulseAmp[ipmt] = new TH2F(Form("PreCALPosPulseTimeVsPulseAmp%d",ipmt+1),Form("Pulse Time Vs Pulse Amp Pos PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-500, 500, 1000, 0, 1000);

    h1PPRECALNegPulseTimeVsPulseAmpMultCut[ipmt] = new TH2F(Form("PreCALNegPulseTimeVsPulseAmpWithMultCut%d",ipmt+1),Form("Pulse Time Vs Pulse Amp NegMultCut PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-500,500, 1000, 0, 1000);
    
    h1PPRECALPosPulseTimeVsPulseAmpMultCut[ipmt] = new TH2F(Form("PreCALPosPulseTimeVsPulseAmpWithMultCut%d",ipmt+1),Form("Pulse Time Vs Pulse Amp PosMultCut PMT%d;Pulse Time(ns); Pulse Amp",ipmt+1),1000,-500, 500, 1000, 0, 1000);

    h1PPRECALNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PPRECALNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALNegPulseTimeStarttimeDiffMult[ipmt] = new TH1F(Form("PPRECALNegPulseTimeStarttimeDiffMult%d",ipmt+1),Form("Pulse Time with Mult PRECAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALNegPulseTimeStarttimeDiffMultCut[ipmt] = new TH1F(Form("PPRECALNegPulseTimeStarttimeDiffMultCut%d",ipmt+1),Form("Pulse Time MultCut for SHMS PRECAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-500,500);

      
    h1PPRECALPosPulseTimeStarttimeDiffMult[ipmt] = new TH1F(Form("PPRECALPosPulseTimeStarttimeDiffMult%d",ipmt+1),Form("Pulse Time with Mult PRECAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALPosPulseTimeStarttimeDiffMultCut[ipmt] = new TH1F(Form("PPRECALPosPulseTimeStarttimeDiffMultCut%d",ipmt+1),Form("Pulse Time MultCut for SHMS PRECAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALPosPulseTime[ipmt] = new TH1F(Form("PPRECALPosPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Pos PMT%d;Time (ns);Counts",ipmt+1),1000,-500, 500);

    h1PPRECALPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PPRECALPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALNegPulseTimeStarttimeDiff_CalCut[ipmt] = new TH1F(Form("PPRECALNegPulseTimeStarttimeDiff_Cut%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Neg PMT%d Start Time Subtracted(cut);Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALPosPulseTimeStarttimeDiff_CalCut[ipmt] = new TH1F(Form("PPRECALPosPulseTimeStarttimeDiff_Cut%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Pos PMT%d Start Time Subtracted(cut);Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALGoodPosAdcTdcDiffTime[ipmt] =  new TH1F(Form("PPRECALGoodPosAdcTdcDiffTime%d",ipmt+1),Form(" SHMS PRECAL GOOD Pos Adc Tdc Diff Time%d;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALGoodPosAdcTdcDiffTime_Cut[ipmt] =  new TH1F(Form("PPRECALGoodPosAdcTdcDiffTimeCut%d",ipmt+1),Form(" SHMS PRECAL GOOD Pos Adc Tdc Diff TimeCut%d;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALGoodNegAdcTdcDiffTime[ipmt] =  new TH1F(Form("PPRECALGoodNegAdcTdcDiffTime%d",ipmt+1),Form(" SHMS PRECAL GOOD Neg Adc Tdc Diff Time PMT_%d;Time (ns);Counts",ipmt+1),1000,-500,500);

    h1PPRECALGoodNegAdcTdcDiffTime_Cut[ipmt] =  new TH1F(Form("PPRECALGoodNegAdcTdcDiffTimeCut%d",ipmt+1),Form(" SHMS PRECAL Neg Adc Tdc Diff TimeCut%d;Time (ns);Counts",ipmt+1),1000,-500,500);

    GetOutputList()->Add(h1PPRECALNegPulseTime[ipmt]);
    GetOutputList()->Add(h1PPRECALNegPulseTimeStarttimeDiff[ipmt]);
    GetOutputList()->Add(h1PPRECALPosPulseTime[ipmt]);
    GetOutputList()->Add(h1PPRECALPosPulseTimeStarttimeDiff[ipmt]);
  }
  
    *////(2)
  //***********************************SHOWER HISTO********************************//


  /* (3)
  h1PCALPulseTime = new TH1F*[224];
  h1PCALPulseTimeStarttimeDiff = new TH1F*[224];
  h1PCALPulseTimeStarttimeDiff_CalCut = new TH1F*[224];
  h1PCALPulseTimeStarttimeDiffMult = new TH1F*[224];
  h1PCALPulseTimeStarttimeDiffMultCut = new TH1F*[224];

  h1PCALGoodAdcTdcDiffTime =  new TH1F*[224];
  h1PCALGoodAdcTdcDiffTime_Cut =  new TH1F*[224];
  
  h1PCALPulseTimeVsPulseAmp = new TH2F*[224];
  h1PCALPulseTimeVsPulseAmpMultCut = new TH2F*[224];
  
  for (Int_t ipmt=0; ipmt<224; ipmt++) {
    
    h1PCALPulseTime[ipmt] = new TH1F(Form("PulseTime%d",ipmt+1),Form("Pulse Time for PMT %d;Time (ns);Counts",ipmt+1),1000,-100,100);

    h1PCALPulseTimeVsPulseAmp[ipmt] = new TH2F(Form("PulseTimeVsPulseAmp%d",ipmt+1),Form("Pulse Time Vs Pulse Amp For PMT %d; Pulse Time  (ns); Pulse Amp",ipmt+1),1000,-100, 100, 1000, 0, 1000);

    h1PCALPulseTimeVsPulseAmpMultCut[ipmt] = new TH2F(Form("PulseTimeVsPulseAmpWithMult&CalCut%d",ipmt+1),Form("Pulse Time Vs Pulse Amp With Mult&Elec PMT %d; Pulse Time  (ns); Pulse Amp",ipmt+1),1000,-100, 100, 1000, 0, 1000);


    h1PCALPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PCALPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-100,100);

    h1PCALPulseTimeStarttimeDiffMult[ipmt] = new TH1F(Form("PCALPulseTimeStarttimeDiffMult%d",ipmt+1),Form("Pulse Time With Mult for SHMS CAL PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-100,100);

    h1PCALPulseTimeStarttimeDiffMultCut[ipmt] = new TH1F(Form("PCALPulseTimeStarttimeDiffMultCut%d",ipmt+1),Form("Pulse Time With Mult & elec for SHMS CAL PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-100,100);



    h1PCALPulseTimeStarttimeDiff_CalCut[ipmt] = new TH1F(Form("PCALPulseTimeStarttimeDiffWithCalCut%d",ipmt+1),Form("Pulse Time Information for PMT%d With CalCut Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-100,100);

    h1PCALGoodAdcTdcDiffTime[ipmt] = new TH1F (Form("PCALGoodAdcTdctimeDiff%d",ipmt+1),Form("Cal Good Adc Tdc TimeDiff%d;Time (ns);Counts",ipmt+1),1000,-100,100);

    h1PCALGoodAdcTdcDiffTime_Cut[ipmt] = new TH1F (Form("PCALGoodAdcTdctimeDiff(Cut)%d",ipmt+1),Form("Cal Good Adc Tdc TimeDiff(Cut)%d;Time (ns);Counts",ipmt+1),1000,-100,100);
 
    GetOutputList()->Add(h1PCALPulseTimeStarttimeDiff[ipmt]);
  }
  
    *////(3) 
}

 
Bool_t SHMSADCGates::Process(Long64_t entry)
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
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);
  if(entry<1600) {//Abort("end of the desired entry");// commented for now
   
  // cout << "\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n" << endl;
  cout << "Entry: " << entry << endl;
  // cout << "\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n" << endl;
  //cout <<"\n";
    
  //**************************** Filling Histograms****************************************////
  //***************************************HGCER*******************************************//
  //********There are 4 pmts. Here we are looping over all hits ***************************//


    
  for (Int_t i = 0; i < *Ndata_P_hgcer_adcPulseTime; i++) {
      
    if (P_hgcer_adcErrorFlag[i] == 1) continue;
    //if (P_hgcer_adcCounter[i] < 1 || P_hgcer_adcCounter[i] > 4) continue;
    Int_t current_pmt = P_hgcer_adcCounter[i] - 1;
      
    // if (entry < 100) cout << entry << "   "  << *Ndata_P_hgcer_adcPulseTime << "   " << P_hgcer_adcCounter[i] << endl;
      
    h1PHGCERPulseTime[current_pmt]->Fill(-P_hgcer_adcPulseTime[i]);
      
    h1PHGCERPulseTimeStarttimeDiff[current_pmt]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime); // all hits
      
    //if(*P_cal_etottracknorm >0.8 && *P_cal_eprtracknorm>0.3)
    if(*P_cal_etottracknorm >0.8 && *P_cal_eprtracknorm>0.3)

      {
	h1PHGCERPulseTimeStarttimeDiff_CalCut[current_pmt]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime); // hits with electron 
	  
      }
      
    h1PHGCERPulseTimeVsPulseAmp[current_pmt]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime,  P_hgcer_adcPulseAmp[i]);


      
    //***************added************************//[i] when the quantity is TTreeReaderArray and nothing when it is TTreeReaderValue only.

    //if(*P_cal_etottracknorm >0.8 && *P_cal_eprtracknorm>0.3 && (-P_hgcer_adcPulseTime [i]+ *P_hod_starttime) <0.0 && ( -P_hgcer_adcPulseTime[i] + *P_hod_starttime) > -30.0)
    if(*P_cal_etottracknorm >0.8  && (-P_hgcer_adcPulseTime [i]+ *P_hod_starttime) <0.0 && ( -P_hgcer_adcPulseTime[i] + *P_hod_starttime) > -30.0)


      {
	h1PHGCERLowTimePickShwrVsPrshwr[current_pmt]->Fill(*P_cal_etottracknorm - *P_cal_eprtracknorm , *P_cal_eprtracknorm);
	h1DeltawithLowerPulseTime[current_pmt]->Fill(*P_gtr_dp);
	h1DeltaVsBetaLowerPulseTime[current_pmt]->Fill( *P_gtr_beta ,*P_gtr_dp);
	h1PdcyfpVsPdcxfpLowerPulseTime[current_pmt]->Fill( *P_dc_y_fp ,*P_dc_x_fp);
	h1YtarVsXtarLowerPulseTime[current_pmt]->Fill( *P_gtr_th , *P_gtr_ph);
	
	h1PdcresidualLowerTime[0]->Fill(P_dc_residual[0]);
      }

    // if(*P_cal_etottracknorm >0.8 && *P_cal_eprtracknorm>0.3 && (-P_hgcer_adcPulseTime[i] + *P_hod_starttime)>0.0 && (-P_hgcer_adcPulseTime[i] + *P_hod_starttime) <30.0)
    if(*P_cal_etottracknorm >0.8  && (-P_hgcer_adcPulseTime[i] + *P_hod_starttime)>0.0 && (-P_hgcer_adcPulseTime[i] + *P_hod_starttime) <30.0)


      {
	h1PHGCERHighTimePickShwrVsPrshwr[current_pmt]->Fill( *P_cal_etottracknorm - *P_cal_eprtracknorm , *P_cal_eprtracknorm);
        h1DeltawithHigherPulseTime[current_pmt]->Fill(*P_gtr_dp);
	h1DeltaVsBetaHigherPulseTime[current_pmt]->Fill( *P_gtr_beta, *P_gtr_dp);
	h1PdcyfpVsPdcxfpHigherPulseTime[current_pmt]->Fill( *P_dc_y_fp, *P_dc_x_fp);
	h1YtarVsXtarHigherPulseTime[current_pmt]->Fill( *P_gtr_th, *P_gtr_ph);
	h1PdcresidualHigherTime[0]->Fill(P_dc_residual[0]);

      }




 //********************************added**done*****************************//
      
    if (P_hgcer_goodAdcMult[current_pmt] == 1) 
      {
	h1PHGCERPulseTimeStarttimeDiffMult[current_pmt]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime);// all hit with elec and mult==1
	//	if(*P_cal_etottracknorm >0.8 && *P_cal_eprtracknorm>0.3)
	if(*P_cal_etottracknorm >0.8 && *P_cal_eprtracknorm>0.3)

	  {
	    h1PHGCERPulseTimeStarttimeDiffMultCut[current_pmt]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime);
	    h1PHGCERPulseTimeVsPulseAmpMultCut[current_pmt]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime,  P_hgcer_adcPulseAmp[i]);
	  }
      }    
  }
    
  for(Int_t i =0; i<*Ndata_P_hgcer_goodAdcTdcDiffTime; i++)
    {
      //Int_t current_pmt = P_hgcer_adcCounter[i] - 1;
      if(P_hgcer_goodAdcMult[i] ==1)
	{
	  // h1PHGCERPulseTimeStarttimeDiffMult[i]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime);
	    
	  h1PHGCERPGoodAdcTdcDiffTime[i]->Fill(P_hgcer_goodAdcTdcDiffTime[i]);
	    
	  if(*P_cal_etottracknorm >0.8 && *P_cal_eprtracknorm>0.3)
	    {
	      h1PHGCERPGoodAdcTdcDiffTime_Mult[i]->Fill(P_hgcer_goodAdcTdcDiffTime[i]);
	      //  h1PHGCERPulseTimeStarttimeDiffMultCut[i]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime);
	    }
	}
    }
    

 //  //**********commented from here******************jan9**********//
 //  //*********************************************************AEROGEL***************************************************************


 // // its one plane and contains 7 paddle. each paddle contains 7pmts on each side. The two side are named as positive and negative side.
 //  //so we  have to loop over each side.
    
 //  //******************** this part is for Negative side of the paddle**************************//
    
  

 // for (Int_t i = 0; i < *Ndata_P_aero_negAdcPulseTime; i++) {
      
 //    if (P_aero_negAdcErrorFlag[i] == 1) continue;
      
 //    //if (P_aero_negAdcCounter[i] < 1 || P_aero_negAdcCounter[i] > 7) continue;
 //    //if (P_aero_negAdcPulseTime[i] == 0) continue;
      
 //    Int_t current_pmt = P_aero_negAdcCounter[i] - 1;
      
 //    h1PAERONegPulseTime[current_pmt]->Fill(-P_aero_negAdcPulseTime[i]);
      
 //    h1PAERONegPulseTimeStarttimeDiff[current_pmt]->Fill(-P_aero_negAdcPulseTime[i] + *P_hod_starttime); // all hits 
      
 //    if (P_aero_goodNegAdcMult[current_pmt] == 1)h1PAERONegPulseTimeStarttimeDiffMult[current_pmt]->Fill(-P_aero_negAdcPulseTime[i] + *P_hod_starttime); // mult cut only
      
 //    if(*P_cal_etottracknorm >0.8)
 //      { 
 // 	h1PAERONegPulseTimeStarttimeDiff_CalCut[current_pmt]->Fill(-P_aero_negAdcPulseTime[i] + *P_hod_starttime);// elec cut
	  
 // 	if (P_aero_goodNegAdcMult[current_pmt] == 1)
 // 	  {
 // 	    h1PAERONegPulseTimeStarttimeDiffMultCut[current_pmt]->Fill(-P_aero_negAdcPulseTime[i] + *P_hod_starttime);// mult and elec cut
 // 	    h1PAERONegPulseTimeVsPulseAmpMultCut[current_pmt]->Fill(-P_aero_negAdcPulseTime[i] + *P_hod_starttime,  P_aero_negAdcPulseAmp[i]);// cal cut with mulitplicity 2D
 // 	  }
	  
 //      }
      
      
 //    h1PAERONegPulseTimeVsPulseAmp[current_pmt]->Fill(-P_aero_negAdcPulseTime[i]+ *P_hod_starttime , P_aero_negAdcPulseAmp[i]);
 //  }
    
  
 //  //*******Good Adc Tdc Diff Time forAERO Negative side **********************//

  
 // for (Int_t i = 0; i <*Ndata_P_aero_goodNegAdcTdcDiffTime; i++){
 //    //  cout << *Ndata_P_aero_goodNegAdcTdcDiffTime << endl;
 //    if (P_aero_goodNegAdcMult[i] == 1)
 //      {
 // 	//cout <<"electron cut: " << *P_cal_etottracknorm << endl;
	  
 // 	h1PAEROGoodNegAdcTdcDiffTime[i]->Fill(P_aero_goodNegAdcTdcDiffTime[i]);
 // 	if(*P_cal_etottracknorm>0.8)
 // 	  {
 // 	    h1PAEROGoodNegAdcTdcDiffTime_Cut[i]->Fill(P_aero_goodNegAdcTdcDiffTime[i]); 
 // 	    // cout << "hi"<<endl;
 // 	  }
 //      }
 //  }
    
    
 //  //This is for the Positive Side of the paddle *********************//
    
 //  for (Int_t i = 0; i < *Ndata_P_aero_posAdcPulseTime; i++) {
 //    if (P_aero_posAdcErrorFlag[i] == 1) continue;
 //    //if (P_aero_posAdcCounter[i] < 1 || P_aero_posAdcCounter[i] > 14) continue;
 //    //if (P_aero_posAdcPulseTime[i] == 0) continue;
 //    Int_t current_pmt = P_aero_posAdcCounter[i] - 1;
 //    h1PAEROPosPulseTime[current_pmt]->Fill(-P_aero_posAdcPulseTime[i]);
      
 //    h1PAEROPosPulseTimeStarttimeDiff[current_pmt]->Fill(-P_aero_posAdcPulseTime[i] + *P_hod_starttime); // all hits 
      
 //    if (P_aero_goodPosAdcMult[current_pmt] == 1) h1PAEROPosPulseTimeStarttimeDiffMult[current_pmt]->Fill(-P_aero_posAdcPulseTime[i] + *P_hod_starttime); // all hits with mult
      
 //    if(*P_cal_etottracknorm >0.8)
 //      {
 // 	h1PAEROPosPulseTimeStarttimeDiff_CalCut[current_pmt]->Fill(-P_aero_posAdcPulseTime[i] + *P_hod_starttime);// all hits with elec
	  
 // 	if (P_aero_goodPosAdcMult[current_pmt] == 1) 
 // 	  {
 // 	    h1PAEROPosPulseTimeStarttimeDiffMultCut[current_pmt]->Fill(-P_aero_posAdcPulseTime[i] + *P_hod_starttime);
 // 	    h1PAEROPosPulseTimeVsPulseAmpMultCut[current_pmt]->Fill(-P_aero_posAdcPulseTime[i] + *P_hod_starttime, P_aero_posAdcPulseAmp[i]); // 2d mult and elec
 // 	  }
 //      }
 //    h1PAEROPosPulseTimeVsPulseAmp[current_pmt]->Fill(-P_aero_posAdcPulseTime[i] + *P_hod_starttime, P_aero_posAdcPulseAmp[i]); // 2d all hits with 
 //  }
    
 //  //**************************GoodAdcTdc Diff time for positive side pmts **************************//
 //  for (Int_t i = 0; i <*Ndata_P_aero_goodPosAdcTdcDiffTime; i++){
 //    if (P_aero_goodPosAdcMult[i] == 1)
 //      {
 // 	h1PAEROGoodPosAdcTdcDiffTime[i]->Fill(P_aero_goodPosAdcTdcDiffTime[i]);
 // 	if(*P_cal_etottracknorm >0.8){h1PAEROGoodPosAdcTdcDiffTime_Cut[i]->Fill(P_aero_goodPosAdcTdcDiffTime[i]); }
 //      }
 //  }
    


 

 //  //*****************************************************AEROGEL DONE***********************************************




 //  //************************************PRE SHOWER ******************************//
 //  // its one plane and contains 14 paddle. each paddle contains 14 pmts on each side. The two side are named as positive and negative side.
 //  //so we  have to loop over each side.
    
 //  //******************** this part is for Negative side of the paddle**************************//
    
 //  for (Int_t i = 0; i < *Ndata_P_precal_negAdcPulseTime; i++) {
      
 //    if (P_precal_negAdcErrorFlag[i] == 1) continue;
      
 //    //if (P_precal_negAdcCounter[i] < 1 || P_precal_negAdcCounter[i] > 14) continue;
 //    //if (P_precal_negAdcPulseTime[i] == 0) continue;
      
 //    Int_t current_pmt = P_precal_negAdcCounter[i] - 1;
      
 //    h1PPRECALNegPulseTime[current_pmt]->Fill(-P_precal_negAdcPulseTime[i]);
      
 //    h1PPRECALNegPulseTimeStarttimeDiff[current_pmt]->Fill(-P_precal_negAdcPulseTime[i] + *P_hod_starttime); // all hits 
      
 //    if (P_precal_goodNegAdcMult[current_pmt] == 1)h1PPRECALNegPulseTimeStarttimeDiffMult[current_pmt]->Fill(-P_precal_negAdcPulseTime[i] + *P_hod_starttime); // mult cut only
      
 //    if(*P_cal_etottracknorm >0.8)
 //      { 
 // 	h1PPRECALNegPulseTimeStarttimeDiff_CalCut[current_pmt]->Fill(-P_precal_negAdcPulseTime[i] + *P_hod_starttime);// elec cut
	  
 // 	if (P_precal_goodNegAdcMult[current_pmt] == 1)
 // 	  {
 // 	    h1PPRECALNegPulseTimeStarttimeDiffMultCut[current_pmt]->Fill(-P_precal_negAdcPulseTime[i] + *P_hod_starttime);// mult and elec cut
 // 	    h1PPRECALNegPulseTimeVsPulseAmpMultCut[current_pmt]->Fill(-P_precal_negAdcPulseTime[i] + *P_hod_starttime,  P_precal_negAdcPulseAmp[i]);// cal cut with mulitplicity 2D
 // 	  }
	  
 //      }
      
      
 //    h1PPRECALNegPulseTimeVsPulseAmp[current_pmt]->Fill(-P_precal_negAdcPulseTime[i]+ *P_hod_starttime , P_precal_negAdcPulseAmp[i]);
 //  }
    
 //  //*******Good Adc Tdc Diff Time for preshower Negative side **********************//
 //  for (Int_t i = 0; i <*Ndata_P_precal_goodNegAdcTdcDiffTime; i++){
 //    //  cout << *Ndata_P_precal_goodNegAdcTdcDiffTime << endl;
 //    if (P_precal_goodNegAdcMult[i] == 1)
 //      {
 // 	//cout <<"electron cut: " << *P_cal_etottracknorm << endl;
	  
 // 	h1PPRECALGoodNegAdcTdcDiffTime[i]->Fill(P_precal_goodNegAdcTdcDiffTime[i]);
 // 	if(*P_cal_etottracknorm>0.8)
 // 	  {
 // 	    h1PPRECALGoodNegAdcTdcDiffTime_Cut[i]->Fill(P_precal_goodNegAdcTdcDiffTime[i]); 
 // 	    // cout << "hi"<<endl;
 // 	  }
 //      }
 //  }
    
    
 //  //This is for the Positive Side of the paddle *********************//
    
 //  for (Int_t i = 0; i < *Ndata_P_precal_posAdcPulseTime; i++) {
 //    if (P_precal_posAdcErrorFlag[i] == 1) continue;
 //    //if (P_precal_posAdcCounter[i] < 1 || P_precal_posAdcCounter[i] > 14) continue;
 //    //if (P_precal_posAdcPulseTime[i] == 0) continue;
 //    Int_t current_pmt = P_precal_posAdcCounter[i] - 1;
 //    h1PPRECALPosPulseTime[current_pmt]->Fill(-P_precal_posAdcPulseTime[i]);
      
 //    h1PPRECALPosPulseTimeStarttimeDiff[current_pmt]->Fill(-P_precal_posAdcPulseTime[i] + *P_hod_starttime); // all hits 
      
 //    if (P_precal_goodPosAdcMult[current_pmt] == 1) h1PPRECALPosPulseTimeStarttimeDiffMult[current_pmt]->Fill(-P_precal_posAdcPulseTime[i] + *P_hod_starttime); // all hits with mult
      
 //    if(*P_cal_etottracknorm >0.8)
 //      {
 // 	h1PPRECALPosPulseTimeStarttimeDiff_CalCut[current_pmt]->Fill(-P_precal_posAdcPulseTime[i] + *P_hod_starttime);// all hits with elec
	  
 // 	if (P_precal_goodPosAdcMult[current_pmt] == 1) 
 // 	  {
 // 	    h1PPRECALPosPulseTimeStarttimeDiffMultCut[current_pmt]->Fill(-P_precal_posAdcPulseTime[i] + *P_hod_starttime);
 // 	    h1PPRECALPosPulseTimeVsPulseAmpMultCut[current_pmt]->Fill(-P_precal_posAdcPulseTime[i] + *P_hod_starttime, P_precal_posAdcPulseAmp[i]); // 2d mult and elec
 // 	  }
 //      }
 //    h1PPRECALPosPulseTimeVsPulseAmp[current_pmt]->Fill(-P_precal_posAdcPulseTime[i] + *P_hod_starttime, P_precal_posAdcPulseAmp[i]); // 2d all hits with 
 //  }
    
 //  //**************************GoodAdcTdc Diff time for positive side pmts **************************//
 //  for (Int_t i = 0; i <*Ndata_P_precal_goodPosAdcTdcDiffTime; i++){
 //    if (P_precal_goodPosAdcMult[i] == 1)
 //      {
 // 	h1PPRECALGoodPosAdcTdcDiffTime[i]->Fill(P_precal_goodPosAdcTdcDiffTime[i]);
 // 	if(*P_cal_etottracknorm >0.8){h1PPRECALGoodPosAdcTdcDiffTime_Cut[i]->Fill(P_precal_goodPosAdcTdcDiffTime[i]); }
 //      }
 //  }
    
    
 //  /////////***********************************Calorimeter  Shower***********************************//
    
 //    for (Int_t i = 0; i < *Ndata_P_cal_adcPulseTime; i++) {
 //      if (P_cal_adcErrorFlag[i] == 1) continue;
 //      //if (P_cal_adcCounter[i] < 1 || P_cal_adcCounter[i] > 255) continue;
 //      //if (P_cal_adcPulseTime[i] == 0) continue;
 //      Int_t current_pmt = P_cal_adcCounter[i] - 1;
      
 //      h1PCALPulseTime[current_pmt]->Fill(-P_cal_adcPulseTime[i]);
      
 //      h1PCALPulseTimeStarttimeDiff[current_pmt]->Fill(-P_cal_adcPulseTime[i] + *P_hod_starttime); // all hits 
      
 //      if(P_cal_goodAdcMult[current_pmt] ==1)h1PCALPulseTimeStarttimeDiffMult[current_pmt]->Fill(-P_cal_adcPulseTime[i] + *P_hod_starttime); // all hits with mult
      
 //      // cout << "Adc Pulse Value: " <<  -P_cal_adcPulseTime[i] << endl;
      
 //      if(*P_cal_etottracknorm >0.8) 
 //    	{
 //    	  h1PCALPulseTimeStarttimeDiff_CalCut[current_pmt]->Fill(-P_cal_adcPulseTime[i] + *P_hod_starttime);// all hits with electron 
	  
 //    	  //	cout << "Pulse vAlue after electron cut: "<< -P_cal_adcPulseTime[i] << endl;
	  
 //    	  if(P_cal_goodAdcMult[current_pmt] ==1)
 //    	    {
 //    	      // cout << "Adc Value after Multiciplity cut "<<  -P_cal_adcPulseTime[i] << endl;
	      
 //    	      h1PCALPulseTimeStarttimeDiffMultCut[current_pmt]->Fill(-P_cal_adcPulseTime[i] + *P_hod_starttime);// all hits with mult and elec cuts
	      
 //    	      h1PCALPulseTimeVsPulseAmpMultCut[current_pmt]->Fill(-P_cal_adcPulseTime[i] + *P_hod_starttime, P_cal_adcPulseAmp[i]); // 2d with mult and electron cuts
	      
 //    	      //cout << "adcPulse value After ALL********* cut "<< -P_cal_adcPulseTime[i] << endl;
 //    	    }
 //    	}
      
 //      h1PCALPulseTimeVsPulseAmp[current_pmt]->Fill(-P_cal_adcPulseTime[i] + *P_hod_starttime, P_cal_adcPulseAmp[i]); // 2d all hits 
 //    }
    
 //  // cout <<"*******  "<< h1PCALPulseTimeVsPulseAmpMultCut[1]->GetEntries()<<endl;
    
 //  // cout << "other HIsto value : " << h1PCALPulseTimeStarttimeDiffMultCut[1]->GetEntries()<<endl;
    
 //  for (Int_t i = 0; i<*Ndata_P_cal_goodAdcTdcTimeDiff; i++)
 //    {
 //      if(P_cal_goodAdcMult[i] ==1)
 // 	{
 // 	  h1PCALGoodAdcTdcDiffTime[i]->Fill(P_cal_goodAdcTdcTimeDiff[i]);
 // 	  if (*P_cal_etottracknorm >0.8){h1PCALGoodAdcTdcDiffTime_Cut[i]->Fill(P_cal_goodAdcTdcTimeDiff[i]);}
 // 	}
 //    }
    

  } //if entry<1000000 ended
  return kTRUE;
}


void SHMSADCGates::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

void SHMSADCGates::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Branches Sorted, Now Calculating Windows");
  

  //Begin peak Finding
  gSystem->RedirectOutput("/dev/null","a");
 
 
  gSystem->RedirectOutput(0);

  //Output Adc Time Window Values into an ascii file
  TString option = GetOption();
  
  
  gStyle->SetOptStat(11111111);
  TCanvas *c1 = new TCanvas("c1", "" , 600, 600);//HGcer canvas
  //c1->Divide(2,2);
  c1->Divide(2,2);

  for (Int_t ipmt=0; ipmt < 4; ipmt++) {
    
    c1->cd(1);  gPad->SetLogy();
  
    h1PHGCERPulseTimeStarttimeDiff[ipmt]->Draw();

    h1PHGCERPulseTimeStarttimeDiff_CalCut[ipmt]->Draw("same");
    h1PHGCERPulseTimeStarttimeDiff_CalCut[ipmt]->SetLineColor(kRed);

    h1PHGCERPulseTimeStarttimeDiffMult[ipmt]->Draw("same");
    h1PHGCERPulseTimeStarttimeDiffMult[ipmt]->SetLineColor(kMagenta);

    h1PHGCERPulseTimeStarttimeDiffMultCut[ipmt]->Draw("same");
    h1PHGCERPulseTimeStarttimeDiffMultCut[ipmt]->SetLineColor(kRed+4);
    // PHGCPULSETIMEDIFFCUT[ipmt]->Draw("same");
    // PHGCPULSETIMEDIFFCUT[ipmt]->SetLineColor(kRed);
    c1->cd(2);
    h1PHGCERPulseTimeVsPulseAmp[ipmt]->Draw("colz");gPad->SetLogz(1);

    c1->cd(4);gPad->SetLogz(1);
    //  h1PHGCERPulseTime[ipmt]->Draw();
    h1PHGCERPulseTimeVsPulseAmpMultCut[ipmt]->Draw("colz");gPad->SetLogz(1);

    c1->cd(3);gPad->SetLogy();
    h1PHGCERPGoodAdcTdcDiffTime[ipmt]->Draw();
    h1PHGCERPGoodAdcTdcDiffTime_Mult[ipmt]->Draw("same");
    h1PHGCERPGoodAdcTdcDiffTime_Mult[ipmt]->SetLineColor(kRed);
    h1PHGCERPGoodAdcTdcDiffTime[ipmt]->GetXaxis()->SetTitle("Time[ns]");
    h1PHGCERPGoodAdcTdcDiffTime[ipmt]->GetYaxis()->SetTitle("Counts");
    h1PHGCERPulseTimeStarttimeDiffMult[ipmt]->Draw("same");
    h1PHGCERPulseTimeStarttimeDiffMult[ipmt]->SetLineColor(kMagenta);
    h1PHGCERPulseTimeStarttimeDiffMultCut[ipmt]->Draw("same");
    h1PHGCERPulseTimeStarttimeDiffMultCut[ipmt]->SetLineColor(kRed+4);

    c1->SaveAs(Form("./HGC_pmt_%i.pdf", ipmt+1));
    
  }



  //*********************************************************ADDED*************************************

  gStyle->SetOptStat(11111111);
 

  for (Int_t ipmt=0; ipmt < 4; ipmt++) {

    TCanvas *c = new TCanvas("c", "" , 600, 600);//HGcer canvas
    //c->Divide(2,2);
    c->Divide(2,5);
    
    c->cd(1);gPad->SetLogz(1);
    h1PHGCERLowTimePickShwrVsPrshwr[ipmt]->Draw("colz");gPad->SetLogz(1);
    c->cd(2);gPad->SetLogz(1);
    h1PHGCERHighTimePickShwrVsPrshwr[ipmt]->Draw("colz");gPad->SetLogz(1);
    c->cd(3);
    h1DeltawithLowerPulseTime[ipmt]->SetLineColor(kMagenta);
    h1DeltawithLowerPulseTime[ipmt]->Draw();
    c->cd(4);
    h1DeltawithHigherPulseTime[ipmt]->SetLineColor(kRed);
    h1DeltawithHigherPulseTime[ipmt]->Draw(); 
    c->cd(5);gPad->SetLogz(1);
    h1DeltaVsBetaLowerPulseTime[ipmt]->Draw("colz");gPad->SetLogz(1);
    c->cd(6);gPad->SetLogz(1);
    h1DeltaVsBetaHigherPulseTime[ipmt]->Draw("colz");gPad->SetLogz(1);
    c->cd(7);gPad->SetLogz(1);
    h1PdcyfpVsPdcxfpLowerPulseTime[ipmt]->Draw("colz");gPad->SetLogz(1);
    c->cd(8);gPad->SetLogz(1);
    h1PdcyfpVsPdcxfpHigherPulseTime[ipmt]->Draw("colz");gPad->SetLogz(1);
    c->cd(9);gPad->SetLogz(1);
    h1YtarVsXtarLowerPulseTime[ipmt]->Draw("colz");gPad->SetLogz(1);
    c->cd(10);gPad->SetLogz(1);
    h1YtarVsXtarHigherPulseTime[ipmt]->Draw("colz");gPad->SetLogz(1);

  c->SaveAs(Form("./HGC_more_pmt_%i.pdf", ipmt+1));
    
  }

 for (Int_t ipmt=0; ipmt < 4; ipmt++) {

    TCanvas *c3 = new TCanvas("c3", "" , 600, 600);//HGcer canvas
    //c->Divide(2,2);
    c3->Divide(2,2);
    
    
    c3->cd(1);
    h1DeltawithLowerPulseTime[ipmt]->Draw();

    c3->cd(2);
    h1DeltawithHigherPulseTime[ipmt]->Draw(); 

    c3->cd(3);
    h1DeltawithHigherPulseTime[ipmt]->SetLineColor(kMagenta);
    h1DeltawithHigherPulseTime[ipmt]->Draw();
    h1DeltawithLowerPulseTime[ipmt]->SetLineColor(kRed);
    h1DeltawithLowerPulseTime[ipmt]->Draw("same");

    c3->cd(4);gPad->SetLogz(1);
    h1YtarVsXtarHigherPulseTime[ipmt]->SetLineColor(kMagenta);
    h1YtarVsXtarHigherPulseTime[ipmt]->Draw();gPad->SetLogz(1);
    h1YtarVsXtarLowerPulseTime[ipmt]->SetLineColor(kRed);
    h1YtarVsXtarLowerPulseTime[ipmt]->Draw("same");gPad->SetLogz(1);

   c3->SaveAs(Form("./HGC_Delta_XYtar_pmt_%i.pdf", ipmt+1));

  }

 TCanvas *c9 = new TCanvas("c9", "", 600,600);
 c9->Divide (1,2);
 c9->cd(1);
 h1PdcresidualLowerTime[1]->Draw();
 c9->cd(2);
 h1PdcresidualHigherTime[1]->Draw();
 //**************************DONE ADDING*****************************************

  //***********************************AEROGEL HISTOGRAM******************************************
 
 //***************commented jan9******************//
  // for (Int_t ipmt=0; ipmt < 7; ipmt++) {
  //   TCanvas *cc = new TCanvas("cc", "AdcTdcNeg" , 600, 600);
  //   cc->Divide(2,2);//negative
  //   cc->cd(1);gPad->SetLogy();
  //   h1PAERONegPulseTimeStarttimeDiff[ipmt]->Draw();
  //   h1PAERONegPulseTimeStarttimeDiff_CalCut[ipmt]->Draw("same");
  //   h1PAERONegPulseTimeStarttimeDiff_CalCut[ipmt]->SetLineColor(kRed);
  //   h1PAERONegPulseTimeStarttimeDiffMult[ipmt]->Draw("same");
  //   h1PAERONegPulseTimeStarttimeDiffMult[ipmt]->SetLineColor(kMagenta);
  //   h1PAERONegPulseTimeStarttimeDiffMultCut[ipmt]->Draw("same");
  //   h1PAERONegPulseTimeStarttimeDiffMultCut[ipmt]->SetLineColor(kRed+4);

  //   cc->cd(2);
  //   h1PAERONegPulseTimeVsPulseAmp[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   cc->cd(4);
  //   h1PAERONegPulseTimeVsPulseAmpMultCut[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   cc->cd(3);gPad->SetLogy();

  //   h1PAEROGoodNegAdcTdcDiffTime[ipmt]->Draw();
  //   cout << "no of entries "<<h1PAEROGoodNegAdcTdcDiffTime[0]->GetEntries()<<endl;
  //   h1PAEROGoodNegAdcTdcDiffTime_Cut[ipmt]->Draw("same");
  //   h1PAEROGoodNegAdcTdcDiffTime_Cut[ipmt]->SetLineColor(kRed);
  //   // h1PAEROGoodNegAdcTdcDiffTime[ipmt]->GetXaxis()->SetTitle("Time[ns]");
  //   // h1PAEROGoodNegAdcTdcDiffTime[ipmt]->GetYaxis()->SetTitle("counts");
  //   //  cc->SaveAs(Form("./AERO_NEG_PMT_%i.pdf",ipmt+1));

  //   TCanvas *cc1 = new TCanvas("cc1", "AdcTdcPos" , 600, 600);// positive 
  //   cc1->Divide(2,2);
  //   cc1->cd(1);gPad->SetLogy();
  //   h1PAEROPosPulseTimeStarttimeDiff[ipmt]->Draw();
  //   h1PAEROPosPulseTimeStarttimeDiff_CalCut[ipmt]->Draw("same");
  //   h1PAEROPosPulseTimeStarttimeDiff_CalCut[ipmt]->SetLineColor(kRed);
  //   h1PAEROPosPulseTimeStarttimeDiffMult[ipmt]->Draw("same"); 
  //   h1PAEROPosPulseTimeStarttimeDiffMult[ipmt]->SetLineColor(kMagenta);
  //   h1PAEROPosPulseTimeStarttimeDiffMultCut[ipmt]->Draw("same"); 
  //   h1PAEROPosPulseTimeStarttimeDiffMultCut[ipmt]->SetLineColor(kRed+4);


  //   cc1->cd(2);
  //   h1PAEROPosPulseTimeVsPulseAmp[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   cc1->cd(4);
  //   h1PAEROPosPulseTimeVsPulseAmpMultCut[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   cc1->cd(3);gPad->SetLogy();
  //   h1PAEROGoodPosAdcTdcDiffTime[ipmt]->Draw();
  //   h1PAEROGoodPosAdcTdcDiffTime_Cut[ipmt]->Draw("same");
  //   h1PAEROGoodPosAdcTdcDiffTime_Cut[ipmt]->SetLineColor(kRed);
  //   h1PAEROGoodPosAdcTdcDiffTime[ipmt]->GetXaxis()->SetTitle("Time[ns]");
  //   h1PAEROGoodPosAdcTdcDiffTime[ipmt]->GetYaxis()->SetTitle("counts");
  //   //cc1->SaveAs(Form("./AERO_POS_PMT_%i.pdf",ipmt+1));
  // }


  // //****************************************AERO HISTO DONE*******************************


  // //*********************PRESHWR CANVAS******************************************

  // //// TDirectory *DPRECAL = Histogram_file->mkdir("Pre-Shower ADC Timing Spectra"); DPRECAL->cd();

  // ///////// //***************************************Preshower ***************************//


  // for (Int_t ipmt=0; ipmt < 14; ipmt++) {
  //   TCanvas *c3 = new TCanvas("c3", "AdcTdcNeg" , 600, 600);
  //   c3->Divide(2,2);//negative
  //   c3->cd(1);gPad->SetLogy();
  //   h1PPRECALNegPulseTimeStarttimeDiff[ipmt]->Draw();
  //   h1PPRECALNegPulseTimeStarttimeDiff_CalCut[ipmt]->Draw("same");
  //   h1PPRECALNegPulseTimeStarttimeDiff_CalCut[ipmt]->SetLineColor(kRed);
  //   h1PPRECALNegPulseTimeStarttimeDiffMult[ipmt]->Draw("same");
  //   h1PPRECALNegPulseTimeStarttimeDiffMult[ipmt]->SetLineColor(kMagenta);
  //   h1PPRECALNegPulseTimeStarttimeDiffMultCut[ipmt]->Draw("same");
  //   h1PPRECALNegPulseTimeStarttimeDiffMultCut[ipmt]->SetLineColor(kRed+4);

  //   c3->cd(2);
  //   h1PPRECALNegPulseTimeVsPulseAmp[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   c3->cd(4);
  //   h1PPRECALNegPulseTimeVsPulseAmpMultCut[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   c3->cd(3);gPad->SetLogy();

  //   h1PPRECALGoodNegAdcTdcDiffTime[ipmt]->Draw();
  //   h1PPRECALGoodNegAdcTdcDiffTime_Cut[ipmt]->Draw("same");
  //   h1PPRECALGoodNegAdcTdcDiffTime_Cut[ipmt]->SetLineColor(kRed);
  //   h1PPRECALGoodNegAdcTdcDiffTime[ipmt]->GetXaxis()->SetTitle("Time[ns]");
  //   h1PPRECALGoodNegAdcTdcDiffTime[ipmt]->GetYaxis()->SetTitle("counts");
  //   //c3->SaveAs(Form("./PRECAL_NEG_PMT_%i.pdf",ipmt+1));

  //   TCanvas *c4 = new TCanvas("c4", "AdcTdcPos" , 600, 600);// positive 
  //   c4->Divide(2,2);
  //   c4->cd(1);gPad->SetLogy();
  //   h1PPRECALPosPulseTimeStarttimeDiff[ipmt]->Draw();
  //   h1PPRECALPosPulseTimeStarttimeDiff_CalCut[ipmt]->Draw("same");
  //   h1PPRECALPosPulseTimeStarttimeDiff_CalCut[ipmt]->SetLineColor(kRed);
  //   h1PPRECALPosPulseTimeStarttimeDiffMult[ipmt]->Draw("same"); 
  //   h1PPRECALPosPulseTimeStarttimeDiffMult[ipmt]->SetLineColor(kMagenta);
  //   h1PPRECALPosPulseTimeStarttimeDiffMultCut[ipmt]->Draw("same"); 
  //   h1PPRECALPosPulseTimeStarttimeDiffMultCut[ipmt]->SetLineColor(kRed+4);


  //   c4->cd(2);
  //   h1PPRECALPosPulseTimeVsPulseAmp[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   c4->cd(4);
  //   h1PPRECALPosPulseTimeVsPulseAmpMultCut[ipmt]->Draw("colz");gPad->SetLogz(1);

  //   c4->cd(3);gPad->SetLogy();
  //   h1PPRECALGoodPosAdcTdcDiffTime[ipmt]->Draw();
  //   h1PPRECALGoodPosAdcTdcDiffTime_Cut[ipmt]->Draw("same");
  //   h1PPRECALGoodPosAdcTdcDiffTime_Cut[ipmt]->SetLineColor(kRed);
  //   h1PPRECALGoodPosAdcTdcDiffTime[ipmt]->GetXaxis()->SetTitle("Time[ns]");
  //   h1PPRECALGoodPosAdcTdcDiffTime[ipmt]->GetYaxis()->SetTitle("counts");
  //   // c4->SaveAs(Form("./PRECAL_POS_PMT_%i.pdf",ipmt+1));
  // }

  // // TDirectory *DCAL = Histogram_file->mkdir("Calorimeter ADC Timing Spectra"); DCAL->cd();

  // //****************************CanVas for Shower ****************************//


  // for (Int_t ipmt=0; ipmt < 224; ipmt++) {
  //   TCanvas *c5 = new TCanvas("c5", "Cal_FlyEye" , 600, 600);c5->Divide(2,2);
  //   c5->cd(1);gPad->SetLogy();
  //   // PCALPULSETIMEDIFF[ipmt]->Draw();
  //   h1PCALPulseTimeStarttimeDiff[ipmt]->Draw();
  //   h1PCALPulseTimeStarttimeDiff_CalCut[ipmt]->Draw("same");
  //   h1PCALPulseTimeStarttimeDiff_CalCut[ipmt]->SetLineColor(kRed);
  //   h1PCALPulseTimeStarttimeDiffMult[ipmt]->Draw("same");
  //   h1PCALPulseTimeStarttimeDiffMult[ipmt]->SetLineColor(kMagenta);
  //   h1PCALPulseTimeStarttimeDiffMultCut[ipmt]->Draw("same");
  //   h1PCALPulseTimeStarttimeDiffMultCut[ipmt]->SetLineColor(kRed+4);
    

  //   c5->cd(2);
  //   h1PCALPulseTimeVsPulseAmp[ipmt]->Draw("colz");gPad->SetLogz(1);


  //   c5->cd(4);
  //   h1PCALPulseTimeVsPulseAmpMultCut[ipmt]->Draw("colz");gPad->SetLogz(1);


  //   c5->cd(3);gPad->SetLogy();
  //   h1PCALGoodAdcTdcDiffTime[ipmt]->Draw();
  //   h1PCALGoodAdcTdcDiffTime_Cut[ipmt]->Draw("same");
  //   h1PCALGoodAdcTdcDiffTime_Cut[ipmt]->SetLineColor(kRed);
  //   h1PCALGoodAdcTdcDiffTime[ipmt]->GetXaxis()->SetTitle("Time[ns]");
  //   h1PCALGoodAdcTdcDiffTime[ipmt]->GetYaxis()->SetTitle("counts");
  //   //c5->SaveAs(Form("CAL_PMT_%i.pdf",ipmt+1));
  // }

 
}                 
