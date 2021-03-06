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

 
void pos_2p2_7783(){
  gStyle->SetOptStat(1);
  // gStyle->SetOptStat(0);

  // gROOT->SetBatch(kTRUE);
  gROOT->ForceStyle(); 
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetNdivisions(505);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadLeftMargin(0.08);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadBottomMargin(.14);
  gStyle->SetTitleYOffset(0.855);
  gStyle->SetTitleXOffset(0.855);
  gStyle->SetTitleYSize(0.03);
  gStyle->SetTitleXSize(0.03);
  gStyle->SetLabelFont(62,"X");
  gStyle->SetLabelFont(62,"Y");
  gStyle->SetTitleFont(62,"X");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetLabelSize(0.02,"X");
  gStyle->SetLabelSize(0.02,"Y");
  gStyle->SetPaperSize(23,24);
  gStyle->SetLineWidth(2);
  TChain *tt = new TChain("T");

  //pi+ 6194,95
 
  //tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_3p2pos_7767.root");
    tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_2p2pos_7783.root");
  //tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_2p2pos_6215.root");

  TFile *ff = new TFile("root/pos_2p2pos_7783.root","RECREATE");   


  Long64_t nentriesD = tt->GetEntries();

  cout<<"data entries = "<<nentriesD<<"  "<<endl;

  Int_t binct =100;
  Int_t loct =35;
  Int_t hict=55;


  Int_t binmult =100;
  Int_t lomult =-2;
  Int_t himult=10;

  Int_t bintdctime =100;
  Int_t lotdctime =-1000;
  Int_t hitdctime=1000;

  Int_t bindiff =100;
  Int_t lodiff =-1000;
  Int_t hidiff =3000;

  Int_t binhitstime =100;
  Int_t lohitstime = -1000;
  Int_t hihitstime=1000;

  Int_t bincal=100;
  Int_t local = 0;
  Double_t hical = 1.2;

  Int_t bincalepr=100;
  Double_t localepr = 0;
  Double_t hicalepr = 0.5;

  Double_t pionMass = 0.1395701835;   
  Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,goodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit;
  Double_t phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,rf_pion ;

  TH1D *cointime = new TH1D("cointime", "cointime (ns)", binct, loct, hict);
  TH1D *cointime_pi = new TH1D("cointime_pi", "cointime_pi (ns)", binct, loct, hict);
  TH1D *cointime_notpi = new TH1D("cointime_nopi", "cointime_nopi (ns)", binct, loct, hict);
  TH1D *beta_did_hms_shms_cuts = new TH1D("beta_did_hms_shms_cuts", "beta_did_hms_shms_cuts", 50, 0.7, 1.3);
  TH1D *beta_should_hms_shms_cuts = new TH1D("beta_should_hms_shms_cuts", "beta_should_hms_shms_cuts", 50, 0.7, 1.3);


  TH1D *prf_tdctime = new TH1D("prf_tdctime", "prf_tdctime", bintdctime, lotdctime, hitdctime);//T.coin.pRF_tdcTime 
  TH1D *phodfp_hitstime = new TH1D("phodfp_hitstime", "phodfp_hitstime", binhitstime, lohitstime, hihitstime);//P.hod.fpHitsTime

  TH1D *rf_minus_fp = new TH1D("rf_minus_fp ", "rf_minus_fp ",bindiff, lodiff, hidiff);

  TH1D *rf_minus_phodfp_mod4 = new TH1D("rf_minus_phodfp_mod4 ", "rf_minus_phodfp_mod4 ", 100, -0.5, 4.5);//T.coin.pRF_tdcTime-P.hod.fpHitsTime
  TH2D *beta_vs_rf = new TH2D("beta_vs_rf","beta_vs_rf",100, -0.5, 4.5, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_notpion = new TH2D("beta_vs_rf_notpion","beta_vs_rf_notpion",100, -0.5, 4.5, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_calctaero = new TH2D("beta_vs_rf_calctaero","beta_vs_rf_calctaero",100, -0.5, 4.5, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_allpid_rfcut_did = new TH2D("beta_vs_rf_allpid_rfcut_did","beta_vs_rf_allpid_rfcut_did",100, -0.5, 4.5, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_allpid_should = new TH2D("beta_vs_rf_allpid_should","beta_vs_rf_allpid_should",100, -0.5, 4.5, 100, 0.8, 1.2);
  TH2D *shower_vs_preshower = new TH2D("shower_vs_preshower","shower_vs_preshower",100, 0.0001,0.8, 100, 0.0001, 1.8);
  TH2D *shower_vs_preshower_rf = new TH2D("shower_vs_preshower_rf","shower_vs_preshower_rf",100, 0.0001,0.8, 100, 0.0001, 1.8);

  TH2D *aero_vs_rf = new TH2D("aero_vs_rf","aero_vs_rf",100, -0.5, 4.5, 100, 0.00001, 30);
  TH2D *aero_vs_rf_ctcut = new TH2D("aero_vs_rf_ctcut","aero_vs_rf_ctcut",100, -0.5, 4.5, 100, 0.00001, 30);

  TH1D *pcal = new TH1D("pcal", "pcal", bincal, local, hical);

  TH1D *pcal_epr = new TH1D("pcal_epr", "pcal_epr", bincal, local, hical);
  TH1D *pcal_epr_rf = new TH1D("pcal_epr_rf", "pcal_epr_rf", bincalepr, localepr, hicalepr);


  TH1D *pcal_etot = new TH1D("pcal_etot", "pcal_etot", bincal, local, hical);
  TH1D *pcal_etot_rf = new TH1D("pcal_etot_rf", "pcal_etot_rf", bincal, local, hical);
  TH1D *pcal_etot_notpion = new TH1D("pcal_etot_notpion", "pcal_etot_notpion", bincal, local, hical);
  TH1F *hTotal = new TH1F("hTotal", " ", 30, -10, 20); //delta                        
  TH1F *hPass = new TH1F("hpass", " ", 30, -10, 20); //delta                       
  TH2F *h = new TH2F("h","RF Efficiency (pion) vs SHMS Delta",100,-10, 20 ,100, 0, 1); 

  tt->SetBranchAddress("P.gtr.p", &PgtrP); 
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
  tt->SetBranchAddress("g.evtyp", &eventtype);


  Bool_t  acc_cut, accR_cut, accL_cut,data_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, mod4_pioncut, mod4_notpioncut, cal_cut, ctime_cut, hms_cut;
 

  /////////////////////////////////////////////////////////PART 1 find Coincidence time peak/////////////////////////////////
  for (int kk=0; kk<nentriesD;  kk++)//original
    //for (int kk=0; kk<10000;  kk++)
   
    {

      tt->GetEntry(kk);

      // if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;
      hms_cut =  hdelta> -10 && hdelta < 10 && hbeta >0.8 && hbeta <1.2 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 && hcaletottrack <1.2 && hcernpe>2.0 ;
      data_cut =  pdelta >-10 && pdelta < 20   && pbeta >0.8 && pbeta<1.2 && phodstarttime == 1 && pdipole ==1 && eventtype==4;
      hgcer_cut = hgcer>2.0;
      paero_cut = paero>6.0;
      rf_pion = (fmod(prftdctime-phodfphitstime+1000+1.0,4.008));
      mod4_pioncut = rf_pion >0.5 && rf_pion < 1.8;

      mod4_notpioncut =!mod4_pioncut;
      cal_cut = pcaletottrack> 0.0 && pcaletottrack < 1 && pcalepr > 0.00001 && pcalepr<0.2 ;
      ctime_cut = ctime>42.0 && ctime<44.0;
      if(data_cut)
	{ 
	  cointime->Fill(ctime);
	  prf_tdctime->Fill(prftdctime);
	  phodfp_hitstime->Fill(phodfphitstime);
	  rf_minus_fp->Fill(prftdctime-phodfphitstime+1001);
	  if(ctime_cut){
	    rf_minus_phodfp_mod4->Fill(rf_pion);
	  }
	  shower_vs_preshower->Fill(pcalepr,pcaletottrack-pcalepr);
	  beta_vs_rf->Fill(rf_pion,pbeta);
	  aero_vs_rf->Fill(rf_pion,paero);
	  pcal->Fill(pcaletottrack);
	  pcal_epr->Fill(pcalepr);
	  if(mod4_pioncut && cal_cut && paero_cut){
	    cointime_pi->Fill(ctime);//green

	  }
	  if(mod4_notpioncut && cal_cut){
	    cointime_notpi->Fill(ctime);//red
	  }


	  if(cal_cut && ctime_cut && paero_cut){
	    beta_vs_rf_allpid_should->Fill(rf_pion,pbeta);
	    pcal_etot->Fill(pcaletottrack);
	    hTotal->Fill(pdelta);
	    if(hms_cut){
	      beta_should_hms_shms_cuts->Fill(pbeta);
	      if(mod4_pioncut){
		beta_did_hms_shms_cuts->Fill(pbeta);
	      }
	    }
	    if( mod4_pioncut ){
	      beta_vs_rf_allpid_rfcut_did->Fill(rf_pion,pbeta);
	      pcal_epr_rf->Fill(pcalepr);
	      pcal_etot_rf->Fill(pcaletottrack);
	      hPass->Fill(pdelta);
	      shower_vs_preshower_rf->Fill(pcalepr,pcaletottrack-pcalepr);

	    }
	  }
	  if(cal_cut && ctime_cut && paero_cut && mod4_notpioncut){//not pion
	    pcal_etot_notpion->Fill(pcaletottrack);
	    beta_vs_rf_notpion->Fill(rf_pion,pbeta);
	  }

	  if(ctime_cut && cal_cut){
	    aero_vs_rf_ctcut->Fill(rf_pion,paero);
	    if(paero_cut){
	      beta_vs_rf_calctaero->Fill(rf_pion,pbeta);
	    }
	  }
	}
    }
  TEfficiency *pEff = new TEfficiency();
  pEff = new TEfficiency(*hPass, *hTotal);
  TCanvas *ceff = new  TCanvas("ceff","",1600,1200);ceff->SetGrid();
  h->Draw();
  h->GetXaxis()->SetTitle("shms delta (%)");
  h->GetYaxis()->SetTitle("Efficiency");
  h->GetYaxis()->SetRangeUser(0.7,1);
  pEff->Draw("same");

  cout<< "Eff = "<<"\t"<< hPass->Integral() *100 /hTotal->Integral()<< " %"<<endl;
  ceff->SaveAs("pdf/pos_2p2pos_7783_eff.pdf");


  TCanvas *c1 = new TCanvas("c1", "c1", 1600,1200);
  c1->Divide(4,2);
  c1->cd(1);
  cointime->Draw("");
  cointime->SetLineWidth(2);
  cointime->GetXaxis()->SetTitle("Cointime [ns]");
  cointime->GetYaxis()->SetTitle("Counts");
  cointime->GetXaxis()->CenterTitle();
  cointime->GetYaxis()->CenterTitle();
  cointime_pi->Draw("same");
  cointime_pi->SetLineWidth(2);
  cointime_pi->SetLineColor(kGreen);
  cointime_notpi->Draw("Same");
  cointime_notpi->SetLineWidth(2);
  cointime_notpi->SetLineColor(kRed);
  TLegend* leg0 = new TLegend(0.6,0.6,0.9,0.9);
  leg0->AddEntry(cointime,"#beta, #delta cuts only","L");
  leg0->AddEntry(cointime_pi," #beta, #delta, CAL, AERO, RF cuts for pion (All Cuts)","L");
  leg0->AddEntry(cointime_notpi,"#beta, #delta, CAL, !RF only (!Pi) ","L");
  leg0->Draw("Same");
  gPad->Update();



  c1->cd(2);
  prf_tdctime->Draw();
  prf_tdctime->SetLineWidth(2);
  prf_tdctime->GetXaxis()->SetTitle("T.coin.pRF_tdcTime");
  prf_tdctime->GetYaxis()->SetTitle("Counts");
  prf_tdctime->GetXaxis()->CenterTitle();
  prf_tdctime->GetYaxis()->CenterTitle();

  c1->cd(3);
  rf_minus_fp->Draw();
  rf_minus_fp->SetLineWidth(2);
  rf_minus_fp->GetXaxis()->SetTitle("RFtdctime-FPhitstime+1001");
  rf_minus_fp->GetYaxis()->SetTitle("Counts");
  rf_minus_fp->GetXaxis()->CenterTitle();
  rf_minus_fp->GetYaxis()->CenterTitle();


  c1->cd(4);
  rf_minus_phodfp_mod4->Draw();
  rf_minus_phodfp_mod4->SetLineWidth(2);
  rf_minus_phodfp_mod4->GetXaxis()->SetTitle("fmod(pRF-fpHitsTime + 1001, 4.008): #beta, #delta and CT cut");
  rf_minus_phodfp_mod4->GetYaxis()->SetTitle("Counts");
  rf_minus_phodfp_mod4->GetXaxis()->CenterTitle();
  rf_minus_phodfp_mod4->GetYaxis()->CenterTitle();

 

  c1->cd(5);
  beta_vs_rf->Draw();
  beta_vs_rf->SetLineWidth(2);
  beta_vs_rf->GetXaxis()->SetTitle("Pbeta vs  RF");
  beta_vs_rf->GetYaxis()->SetTitle("Counts");
  beta_vs_rf->GetXaxis()->CenterTitle();
  beta_vs_rf->GetYaxis()->CenterTitle();

  c1->cd(6);
  beta_vs_rf_allpid_should->Draw();
  beta_vs_rf_allpid_should->SetLineWidth(2);
  beta_vs_rf_allpid_should->GetXaxis()->SetTitle("Pbeta vs RF:#beta, #delta, CT, calcut, aero");
  beta_vs_rf_allpid_should->GetYaxis()->SetTitle("Counts");
  beta_vs_rf_allpid_should->GetXaxis()->CenterTitle();
  beta_vs_rf_allpid_should->GetYaxis()->CenterTitle();
 

  c1->cd(7);
  beta_vs_rf_allpid_rfcut_did->Draw();
  beta_vs_rf_allpid_rfcut_did->SetLineWidth(2);
  beta_vs_rf_allpid_rfcut_did->GetXaxis()->SetTitle("Pbeta vs  RF: #beta, #delta, CT and RF");
  beta_vs_rf_allpid_rfcut_did->GetYaxis()->SetTitle("Counts");
  beta_vs_rf_allpid_rfcut_did->GetXaxis()->CenterTitle();
  beta_vs_rf_allpid_rfcut_did->GetYaxis()->CenterTitle();




  c1->cd(8);
  pcal_etot->Draw("");
  pcal_etot->SetLineWidth(2);
  pcal_etot->GetXaxis()->SetTitle("Pcal: #beta, #delta, CT, calcut, aero, (Gr=RF,Red= antiRF)");
  pcal_etot->GetYaxis()->SetTitle("Counts");
  pcal_etot->GetXaxis()->CenterTitle();
  pcal_etot->GetYaxis()->CenterTitle();
  pcal_etot_rf->Draw("same");
  pcal_etot_rf->SetLineWidth(2);
  pcal_etot_rf->SetLineColor(kGreen);
  pcal_etot_notpion->Draw("same");
  pcal_etot_notpion->SetLineWidth(2);
  pcal_etot_notpion->SetLineColor(kRed);

  TLegend* leg = new TLegend(0.6,0.3,0.9,0.6);
  leg->AddEntry(pcal_etot,"beta,delta,CT cuts","L");
  leg->AddEntry(pcal_etot_rf," beta, delta, CT + RF cuts for pion","L");
  leg->AddEntry(pcal_etot_notpion,"beta, delta, CT + RF cut for not pion","L");
  leg->Draw("Same");
  gPad->Update();



  TCanvas *c2 = new TCanvas ("c2", "SHMS beta vs RF time" , 1600,1200);gPad->SetLogz();
  c2->Divide(2,1);
  c2->cd(1);
  beta_vs_rf->Draw("colz");
  beta_vs_rf->SetLineWidth(2);
  beta_vs_rf->GetXaxis()->SetTitle("Pbeta vs RF: #beta, #delta only ");
  beta_vs_rf->GetYaxis()->SetTitle("Counts");
  beta_vs_rf->GetXaxis()->CenterTitle();
  beta_vs_rf->GetYaxis()->CenterTitle();
  c2->cd(2);
  beta_vs_rf_calctaero->Draw("colz");
  beta_vs_rf_calctaero->SetLineWidth(2);
  beta_vs_rf_calctaero->GetXaxis()->SetTitle("Pbeta vs  RF: #beta, #delta, cal, CT, aero");
  beta_vs_rf_calctaero->GetYaxis()->SetTitle("Counts");
  beta_vs_rf_calctaero->GetXaxis()->CenterTitle();
  beta_vs_rf_calctaero->GetYaxis()->CenterTitle();


  TCanvas *c3 = new TCanvas ("c3", "AERO  vs RF time" , 1600,1200);gPad->SetLogz();
  c3->Divide(2,1);
  c3->cd(1);
  aero_vs_rf->Draw("colz");
  aero_vs_rf->SetLineWidth(2);
  aero_vs_rf->GetXaxis()->SetTitle("Paero vs RF: #beta and #delta cuts only");
  aero_vs_rf->GetYaxis()->SetTitle("Counts");
  aero_vs_rf->GetXaxis()->CenterTitle();
  aero_vs_rf->GetYaxis()->CenterTitle();
  c3->cd(2);
  aero_vs_rf_ctcut->Draw("colz");
  aero_vs_rf_ctcut->SetLineWidth(2);
  aero_vs_rf_ctcut->GetXaxis()->SetTitle("Paero vs RF: #beta, #delta, CAL, CT");
  aero_vs_rf_ctcut->GetYaxis()->SetTitle("Counts");
  aero_vs_rf_ctcut->GetXaxis()->CenterTitle();
  aero_vs_rf_ctcut->GetYaxis()->CenterTitle();

  TCanvas *c4 = new TCanvas ("c4", "Coin Time" , 1600,1200);
  cointime->Draw("");
  cointime->SetLineWidth(2);
  cointime->GetXaxis()->SetTitle("Cointime [ns]");
  cointime->GetYaxis()->SetTitle("Counts");
  cointime->GetXaxis()->CenterTitle();
  cointime->GetYaxis()->CenterTitle();
  cointime_pi->Draw("same");
  cointime_pi->SetLineWidth(2);
  cointime_pi->SetLineColor(kGreen);
  cointime_notpi->Draw("Same");
  cointime_notpi->SetLineWidth(2);
  cointime_notpi->SetLineColor(kRed);

  TLegend* leg1 = new TLegend(0.7,0.6,0.9,0.9);
  leg1->AddEntry(cointime,"#beta, #delta cuts only","L");
  leg1->AddEntry(cointime_pi," #beta, #delta, CAL, AERO, RF cuts for pion (All Cuts)","L");
  leg1->AddEntry(cointime_notpi,"#beta, #delta, CAL, !RF only (!Pi) ","L");
  leg1->Draw("Same");
  gPad->Update();

  TCanvas *c5 = new TCanvas ("c5", "Pcaletot and Pcal_epr" , 1600,1200);
  c5->Divide(2,2);
  c5->cd(1);//gPad->SetLogy();
  pcal->Draw("");
  pcal->SetLineWidth(2);
  pcal->GetXaxis()->SetTitle("Pcaletottracknorm");
  pcal->GetYaxis()->SetTitle("Counts");
  pcal->GetXaxis()->CenterTitle();
  pcal->GetYaxis()->CenterTitle();
  pcal_etot_rf->Draw("same");
  pcal_etot_rf->SetLineWidth(2);
  pcal_etot_rf->SetLineColor(kGreen);
  pcal_etot_notpion->Draw("same");
  pcal_etot_notpion->SetLineWidth(2);
  pcal_etot_notpion->SetLineColor(kRed);
  TLegend* leg2 = new TLegend(0.6,0.6,0.9,0.9);
  leg2->AddEntry(pcal,"beta and delta cut only","L");
  leg2->AddEntry(pcal_etot_rf,"#beta, #delta, CT, CAL, AERO, RF","L");
  leg2->AddEntry(pcal_etot_notpion,"#beta, #delta, CT, CAL, AERO, NOT RF","L");

  leg2->Draw("Same");
  gPad->Update();



  c5->cd(2);//gPad->SetLogy();
  pcal_epr->Draw("");
  pcal_epr->SetLineWidth(2);
  pcal_epr->GetXaxis()->SetTitle("Pcal_epr. cut");
  pcal_epr->GetYaxis()->SetTitle("Counts");
  pcal_epr->GetXaxis()->CenterTitle();
  pcal_epr->GetYaxis()->CenterTitle();
  pcal_epr_rf->Draw("same");
  pcal_epr_rf->SetLineWidth(2);
  pcal_epr_rf->SetLineColor(kGreen);
  TLegend* leg3 = new TLegend(0.6,0.6,0.9,0.9);
  leg3->AddEntry(pcal_epr,"beta and delta cut only","L");
  leg3->AddEntry(pcal_epr_rf," all cuts and RF cut","L");
  leg3->Draw("Same");
  gPad->Update();

  c5->cd(3);gPad->SetLogz();
  shower_vs_preshower->Draw("colz");
  shower_vs_preshower->SetLineWidth(2);
  shower_vs_preshower->GetXaxis()->SetTitle("preshower :#beta, #delta");
  shower_vs_preshower->GetYaxis()->SetTitle("Shower");
  shower_vs_preshower->GetXaxis()->CenterTitle();
  shower_vs_preshower->GetYaxis()->CenterTitle();

  c5->cd(4);gPad->SetLogz();
  shower_vs_preshower_rf->Draw("colz");
  shower_vs_preshower_rf->SetLineWidth(2);
  shower_vs_preshower_rf->GetXaxis()->SetTitle("preshower with all and RF cut");
  shower_vs_preshower_rf->GetYaxis()->SetTitle("Shower");
  shower_vs_preshower_rf->GetXaxis()->CenterTitle();
  shower_vs_preshower_rf->GetYaxis()->CenterTitle();

  TCanvas *c6 = new TCanvas ("c6", "pbeta with HMS  and SHMS Cuts" , 1600,1200);
  beta_should_hms_shms_cuts->Draw("");
  beta_should_hms_shms_cuts->SetLineWidth(2);
  beta_should_hms_shms_cuts->SetLineColor(kRed);
  beta_should_hms_shms_cuts->SetTitle("SHMS BETA");
  beta_should_hms_shms_cuts->GetXaxis()->SetTitle("Pbeta:  HMS and SHMS Cuts ");
  beta_should_hms_shms_cuts->GetYaxis()->SetTitle("Counts");
  beta_should_hms_shms_cuts->GetXaxis()->CenterTitle();
  beta_should_hms_shms_cuts->GetYaxis()->CenterTitle();
  beta_did_hms_shms_cuts->Draw("same");
  beta_did_hms_shms_cuts->SetLineWidth(2);
  beta_did_hms_shms_cuts->SetLineColor(kGreen);
  beta_did_hms_shms_cuts->GetXaxis()->SetTitle(" Pbeta HMS and SHMS Cuts ");
  beta_did_hms_shms_cuts->GetYaxis()->SetTitle("Counts");
  beta_did_hms_shms_cuts->GetXaxis()->CenterTitle();
  beta_did_hms_shms_cuts->GetYaxis()->CenterTitle();
 TLegend* leg4 = new TLegend(0.6,0.6,0.9,0.9);
  leg4->AddEntry( beta_should_hms_shms_cuts," all hms and shms cuts","L");
  leg4->AddEntry( beta_did_hms_shms_cuts,"RF & all hms and shms cuts ","L");
  leg4->Draw("Same");
  gPad->Update();



	ofstream txtfile ("txtfile/pos_2p2pos_7783.txt",ios::app);
	txtfile<<"pos_2p2pos_7783"<<"\t\t"<< "did =  "<<"\t"<< pcal_etot_rf->Integral() << "\t"<< "should = "<<"\t"<< pcal_etot->Integral() << "\t"<<"eff_of rf = "<<"\t"<< (pcal_etot_rf->Integral() / pcal_etot->Integral())*100 <<" % " <<endl;
	txtfile<<"with hms and shms :"<<"\t"<<"did ="<<"\t"<<beta_did_hms_shms_cuts->Integral()<<"\t"<<"should = "<<"\t"<< beta_should_hms_shms_cuts->Integral()<<"\t"<<"eff_of_rf = "<<"\t"<< beta_did_hms_shms_cuts->Integral() *100 / beta_should_hms_shms_cuts->Integral()<<"\t"<<"%"<<endl;



  cout<< "did =  "<<"\t"<< pcal_etot_rf->Integral() << "\t"<< "should = "<<"\t"<< pcal_etot->Integral() << "\t"<<"eff_of rf = "<<"\t"<< (pcal_etot_rf->Integral() / pcal_etot->Integral())*100 <<" % " <<endl;
  cout<<"No pion_entries = "<<"\t"<< pcal_etot_notpion->Integral()<<endl;
 
  cout<< "with hms & shms :"<<"\t"<<"did :"<<"\t"<<beta_did_hms_shms_cuts->Integral()<<"\t"<<" should: "<<"\t"<< beta_should_hms_shms_cuts->Integral()<<"\t"<<" Eff = "<<"\t"<< beta_did_hms_shms_cuts->Integral() *100 / beta_should_hms_shms_cuts->Integral()<<"\t"<<"%"<<endl;

  c1->SaveAs("pdf/pos_2p2pos_7783.pdf");
  c2->SaveAs("pdf/pos_2p2pos_7783_beta_vs_rf.pdf");
  c3->SaveAs("pdf/pos_2p2pos_7783_aero_vs_rf.pdf");
  c4->SaveAs("pdf/pos_2p2pos_7783_ctime.pdf");
  c5->SaveAs("pdf/pos_2p2pos_7783_cal.pdf");
  c5->SaveAs("pdf/pos_2p2pos_7783_hmsshms_cuts.pdf");




  cointime->Write();
  prf_tdctime->Write();
  phodfp_hitstime->Write();
  rf_minus_phodfp_mod4->Write();
  beta_vs_rf->Write();
  beta_vs_rf_notpion->Write();
  aero_vs_rf->Write();
  cointime_pi->Write();
  cointime_notpi->Write();
  pcal_etot->Write(0);
  pcal_etot_rf->Write();
  pcal_etot_notpion->Write();
  hTotal->Write();
  hPass->Write();
  pEff->Write();
  beta_vs_rf_allpid_should->Write();
  beta_vs_rf_calctaero->Write();
  aero_vs_rf_ctcut->Write();
  pcal->Write();
  pcal_epr->Write();
  beta_did_hms_shms_cuts->Write();
  beta_should_hms_shms_cuts->Write();




}








