#define ROOT_header
#include "TH1F.h"
#include "TH2F.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TDecompLU.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <time.h>
#include <vector>
#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>

void rfvariables(){
  gStyle->SetOptStat(1111111);
  gROOT->SetBatch(kTRUE);
  gROOT->ForceStyle(); 
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetNdivisions(505);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadLeftMargin(0.08);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadBottomMargin(.14);
  gStyle->SetTitleYOffset(1.09);
  gStyle->SetTitleXOffset(0.855);
  gStyle->SetTitleYSize(0.03);
  gStyle->SetTitleXSize(0.03);
  gStyle->SetLabelFont(62,"X");
  gStyle->SetLabelFont(62,"Y");
  gStyle->SetTitleFont(62,"X");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetLabelSize(0.025,"X");
  gStyle->SetLabelSize(0.025,"Y");
  gStyle->SetPaperSize(23,24);



  TChain *tt = new TChain("T");
  tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/amp_zero_default/coin_replay_production_7800_-1.root");
  // tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_6195_500000.root");
  // tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_6195_-1.root");

  TFile *ff = new TFile("root/rfvariables","RECREATE");   


  Long64_t nentriesD = tt->GetEntries();

  cout<<"data entries = "<<nentriesD<<"  "<<endl;

  Int_t binct =100;
  Int_t loct =25;
  Int_t hict=65;


  Int_t binmult =100;
  Int_t lomult =-2;
  Int_t himult=10;

  Int_t bintdctime =100;
  Int_t lotdctime =-1000;
  Int_t hitdctime=1000;

  Int_t binhitstime =100;
  Int_t lohitstime =-20;
  Int_t hihitstime=200;



  Double_t pionMass = 0.1395701835;   
  Double_t pbeta,hbeta,pdelta,hdelta,hcaletot,pcaletottrack,pcalepr,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,goodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit;
  Double_t phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp ;

  TH1D *hist_ctime = new TH1D("hist_ctime", "hist_ctime (ns)", binct, loct, hict);


  TH1D *phod_rf_tdcmult = new TH1D("phod_rf_tdcmult", "phod_rf_tdcmult", binmult, lomult, himult);
  TH1D *phod_rf_tdctime = new TH1D("phod_rf_tdctime", "phod_rf_tdctime", bintdctime, lotdctime, hitdctime);

  TH1D *prf_tdcmult = new TH1D("prf_tdcmult", "prf_tdcmult", binmult, lomult, himult);
  TH1D *prf_tdctime = new TH1D("prf_tdctime", "prf_tdctime", bintdctime, lotdctime, hitdctime);


  TH1D *hhod_rf_tdcmult = new TH1D("hhod_rf_tdcmult", "hhod_rf_tdcmult", binmult, lomult, himult);
  TH1D *hhod_rf_tdctime = new TH1D("hhod_rf_tdctime", "hhod_rf_tdctime", bintdctime, lotdctime, hitdctime);

  TH1D *hrf_tdcmult = new TH1D("hrf_tdcmult", "hrf_tdcmult", binmult, lomult, himult);
  TH1D *hrf_tdctime = new TH1D("hrf_tdctime", "hrf_tdctime", bintdctime, lotdctime, hitdctime);

  
  TH1D *hhodfp_hitstime = new TH1D("hhodfp_hitstime", "hhodfp_hitstime", binhitstime, lohitstime, hihitstime);
  TH1D *phodfp_hitstime = new TH1D("phodfp_hitstime", "phodfp_hitstime", binhitstime, lohitstime, hihitstime);

  TH1D *rf_minus_phodfp = new TH1D("rf_minus_phodfp ", "rf_minus_phodfp ", 100, -100,100);



  tt->SetBranchAddress("P.gtr.p", &PgtrP); 
  tt->SetBranchAddress("H.gtr.p", &HgtrP); 
  tt->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
  tt->SetBranchAddress("H.gtr.beta", &hbeta); 
  tt->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
  tt->SetBranchAddress("P.gtr.dp", &pdelta);                                                                                
  tt->SetBranchAddress("P.cal.eprtracknorm", &pcalepr);                                                                    
  tt->SetBranchAddress("P.cal.etottracknorm", &pcaletottrack);                                                                  
  tt->SetBranchAddress("P.hgcer.npeSum", &phg);
  tt->SetBranchAddress("P.aero.npeSum", &paeronpe);                                          
  tt->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);                                  
  tt->SetBranchAddress("H.cal.etottracknorm", &hcaletot);       
  tt->SetBranchAddress("P.cal.etotnorm", &pcaletotnorm);                                          
  tt->SetBranchAddress("H.cer.npeSum", &hcernpe); 
  tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
  tt->SetBranchAddress("H.kin.primary.omega", &pkinomega);
  tt->SetBranchAddress("H.hod.goodstarttime", &hhodstarttime);
  tt->SetBranchAddress("P.hod.goodstarttime",&phodstarttime);
  tt->SetBranchAddress("P.dc.InsideDipoleExit",&pdipole);
  tt->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);
  tt->SetBranchAddress("P.hod.goodscinhit", &goodscinhit); 
  tt->SetBranchAddress("P.hod.betanotrack", &betanotrack); 
  tt->SetBranchAddress("P.dc.ntrack", &pdcntrack); 

  tt->SetBranchAddress("T.coin.pHODO_RF_tdcMultiplicity", &phodrftdcmult); 
  tt->SetBranchAddress("T.coin.pHODO_RF_tdcTime", &phodrftdctime); 
  tt->SetBranchAddress("T.coin.pRF_tdcMultiplicity", &prftdcmult); 
  tt->SetBranchAddress("T.coin.pRF_tdcTime", &prftdctime); 


  tt->SetBranchAddress("T.coin.hHODO_RF_tdcMultiplicity", &hhodrftdcmult); 
  tt->SetBranchAddress("T.coin.hHODO_RF_tdcTime", &hhodrftdctime); 
  tt->SetBranchAddress("T.coin.hRF_tdcMultiplicity", &hrftdcmult); 
  tt->SetBranchAddress("T.coin.hRF_tdcTime", &hrftdctime); 

  tt->SetBranchAddress("P.hod.fpHitsTime", &phodfphitstime);                    
  tt->SetBranchAddress("H.hod.fpHitsTime", &hhodfphitstime);                    



  Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc;
 

  /////////////////////////////////////////////////////////PART 1 find Coincidence time peak/////////////////////////////////
  for (int kk=0; kk<nentriesD;  kk++)//original
    //for (int kk=0; kk<50000;  kk++)
   
    {

      tt->GetEntry(kk);

      // if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;

      data_cut =  hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hbeta >0.5 && hbeta <1.5 && pbeta >0.5 && pbeta<1.5 && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1;
  
      if(data_cut)
	{ 

	  phod_rf_tdcmult->Fill(phodrftdcmult);
	  phod_rf_tdctime->Fill(phodrftdctime);
	  prf_tdcmult->Fill(prftdcmult);
	  prf_tdctime->Fill(prftdctime);

	  hist_ctime->Fill(ctime);
	 
	  hhod_rf_tdcmult->Fill(hhodrftdcmult);
	  hhod_rf_tdctime->Fill(hhodrftdctime);
	  hrf_tdcmult->Fill(hrftdcmult);
	  hrf_tdctime->Fill(hrftdctime);

	  phodfp_hitstime->Fill(phodfphitstime);
	  hhodfp_hitstime->Fill(hhodfphitstime);
	  rfminusfp=phodrftdctime-phodfphitstime;
	  rf_minus_phodfp->Fill(rfminusfp);

	}
    }


  //for SHMS
  TCanvas *c1 = new TCanvas("c1", "hms rf_time_variable", 1600,1200); 
  c1->Divide(3,2);
  c1->cd(1);
  hhod_rf_tdcmult->Draw();
  hhod_rf_tdcmult->SetLineWidth(2);
  hhod_rf_tdcmult->GetXaxis()->SetTitle("T.coin.hHODO_RF_tdcMultiplicity");
  hhod_rf_tdcmult->GetXaxis()->CenterTitle();
  hhod_rf_tdcmult->GetYaxis()->SetTitle("Entries");

  c1->cd(2);
  hrf_tdcmult->Draw();
  hrf_tdcmult->SetLineWidth(2);
  hrf_tdcmult->GetXaxis()->SetTitle("T.coin.hRF_tdcMultiplicity");
  hrf_tdcmult->GetXaxis()->CenterTitle();
  hrf_tdcmult->GetYaxis()->SetTitle("Entries");

  c1->cd(3);
  hhod_rf_tdctime->Draw();
  hhod_rf_tdctime->SetLineWidth(2);
  hhod_rf_tdctime->GetXaxis()->SetTitle("T.coin.hHODO_RF_tdcTime");
  hhod_rf_tdctime->GetXaxis()->CenterTitle();
  hhod_rf_tdctime->GetYaxis()->SetTitle("Entries");

  c1->cd(4);
  hrf_tdctime->Draw();
  hrf_tdctime->SetLineWidth(2);
  hrf_tdctime->GetXaxis()->SetTitle("T.coin.hRF_tdcTime");
  hrf_tdctime->GetXaxis()->CenterTitle();
  hrf_tdctime->GetYaxis()->SetTitle("Entries");


  c1->cd(5);
   hhodfp_hitstime->Draw();
   hhodfp_hitstime->SetLineWidth(2);
   hhodfp_hitstime->GetXaxis()->SetTitle("H.hod.fpHitsTime");
   hhodfp_hitstime->GetXaxis()->CenterTitle();
   hhodfp_hitstime->GetYaxis()->SetTitle("Entries");




  TCanvas *c2 = new TCanvas("c2", "shms rf_time_variable", 1600,1200); 
  c2->Divide(3,2);
  c2->cd(1);
  phod_rf_tdcmult->Draw();
  phod_rf_tdcmult->SetLineWidth(2);
  phod_rf_tdcmult->GetXaxis()->SetTitle("T.coin.pHODO_RF_tdcMultiplicity");
  phod_rf_tdcmult->GetXaxis()->CenterTitle();
  phod_rf_tdcmult->GetYaxis()->SetTitle("Entries");

  c2->cd(2);
  prf_tdcmult->Draw();
  prf_tdcmult->SetLineWidth(2);
  prf_tdcmult->GetXaxis()->SetTitle("T.coin.pRF_tdcMultiplicity");
  prf_tdcmult->GetXaxis()->CenterTitle();
  prf_tdcmult->GetYaxis()->SetTitle("Entries");

  c2->cd(3);
  phod_rf_tdctime->Draw();
  phod_rf_tdctime->SetLineWidth(2);
  phod_rf_tdctime->GetXaxis()->SetTitle("T.coin.pHODO_RF_tdcTime");
  phod_rf_tdctime->GetXaxis()->CenterTitle();
  phod_rf_tdctime->GetYaxis()->SetTitle("Entries");

  c2->cd(4);
  prf_tdctime->Draw();
  prf_tdctime->SetLineWidth(2);
  prf_tdctime->GetXaxis()->SetTitle("T.coin.pRF_tdcTime");
  prf_tdctime->GetXaxis()->CenterTitle();
  prf_tdctime->GetYaxis()->SetTitle("Entries");

  c2->cd(5);
  phodfp_hitstime->Draw();
  phodfp_hitstime->SetLineWidth(2);
  phodfp_hitstime->GetXaxis()->SetTitle("P.hod.fpHitsTime");
  phodfp_hitstime->GetXaxis()->CenterTitle();
  phodfp_hitstime->GetYaxis()->SetTitle("Entries");

  c2->cd(6);
   rf_minus_phodfp->Draw();
   rf_minus_phodfp->SetLineWidth(2);
   rf_minus_phodfp->GetXaxis()->SetTitle("prftime-pfptime ");
   rf_minus_phodfp->GetXaxis()->CenterTitle();
   rf_minus_phodfp->GetYaxis()->SetTitle("Entries");





  TCanvas *c3 = new TCanvas ("c3", "c3", 1600,1200);
  hist_ctime->Draw();
  hist_ctime->SetLineWidth(2);
  hist_ctime->GetXaxis()->SetTitle("Coincidence Time");
  hist_ctime->GetXaxis()->CenterTitle();
  hist_ctime->GetYaxis()->SetTitle("Entries");



  c1->SaveAs("pdf1/hms_rf_variables.pdf");
  c2->SaveAs("pdf1/shms_rf_variables.pdf");
  c3->SaveAs("pdf1/ctime.pdf");

  hhod_rf_tdcmult->Write();
  hrf_tdcmult->Write();
  hhod_rf_tdctime->Write();
  hrf_tdctime->Write();
  phod_rf_tdcmult->Write();
  prf_tdcmult->Write();
  phod_rf_tdctime->Write();
  prf_tdctime->Write();
  phodfp_hitstime->Write();
  hhodfp_hitstime->Write();

}















