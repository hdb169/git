#include "header.h"
#include <iostream>
#include <string>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TPaveText.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TTree.h>
#include <TArc.h>
#include <TCutG.h>
#include <TExec.h>
#include <TColor.h>
#define NRUNS 2//34//56


void eff_hgc_xynpe_vijay(){
 gStyle->SetPalette(1,0);
 gStyle->SetOptStat(1000011);
 gStyle->SetOptFit(11);
 gStyle->SetTitleOffset(1.,"Y");
 gStyle->SetTitleOffset(.7,"X");
 gStyle->SetLabelSize(0.04,"XY");
 gStyle->SetTitleSize(0.06,"XY");
 gStyle->SetPadLeftMargin(0.12);  
  //#include "gStyle.h"
  // gStyle->SetOptStat(100011111);
  gStyle->SetOptStat(1000011);//integral
  // gStyle->SetOptStat(1111111);//integral


  Int_t runs[NRUNS]={6194, 6245};
   
  Double_t mom[NRUNS] ={ 3.936, 3.936};
  // gROOT->SetBatch("kTRUE");
  for(Int_t r=0; r<NRUNS; r++){

    TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/hgcer/added_%d.root", runs[r]);
    //TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/hgcer/coin_replay_production_%d_-1.root", runs[r]);
    // TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/coin_replay_production_%d_7796.root", runs[r]);

    TFile *f = new TFile(filename, "READ");
    TFile * f11 = new TFile(Form("root_rfeff/rfplot_zbins_%d.root",runs[r]),"RECREATE");

    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

    //#include "binkin391_401.h"
#include "bin7808.h"

    
    Double_t pionmass   = 0.1395701835;    //Gev/c^2 
    Double_t protonmass = 0.93827231;//GeV/c2
    Double_t dxbj, dQ2, dnu,domega,  dW2, dpmiss, demiss,  zhad, Mx2,Mx2a_acccut,Epi_acccut,zhad_acccut,Epi_pidcut,zhad_pidcut,Mx2_pidcut,Epi_cut,zhad_cut,Mx2_cut ;//d = data
    Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,phodgoodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit, phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,rf_pion,hhodgoodscinhit,hhodbetanotrack,hdcntrack,hgtry,pgtry,phodbetanotrack,hcaletotnorm,gevnum,hxptar,hyptar,pxptar,pyptar ;

    double scaler_eventnum,bcm1charge,bcm1current,scaler1MHztime,scaler1MHztimecut,bcm1chargecut,s1xscaler,s1yscaler,s2xscaler,s2yscaler,ptrig1scaler,ptrig2scaler,ptrig3scaler,ptrig4scaler,ptrig6scaler,pedtmscaler,pelcleanscaler,pl1acceptscaler,edtmtdctime,edtmtdctimeraw,mult,ptrig1rate,rate,charge,hgc_xAtCer,hgc_yAtCer   ;
    
    Double_t Epi_dcut0, z_dcut0, Epi_dcut1, z_dcut1, Epi_dcut2, z_dcut2, Epi_dcut3, z_dcut3, Epi_dcut1plus2, z_dcut1plus2; 
    Double_t Epi_acc0, z_acc0, Epi_acc1, z_acc1, Epi_acc2, z_acc2, Epi_acc3, z_acc3, Epi_acc1plus2, z_acc1plus2;

    Bool_t  accR_cut, accL_cut,shms_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, mod4_pioncut, mod4_notpioncut, pcal_cut, ctime_cut, hms_cut, pcal_cut_tight, cuttype1, cuttype1acc, cuttype2, cuttype2acc, cuttype1plus2, cuttype1plus2acc , hgcer_cut_loose,  paero_cut_loose,  cuttype0, cuttype0acc, common_cut, cuttype3, cuttype3acc, accsub_cut, acc_cut, shms_tr_did_cut, shms_tr_should_cut, hms_tr_did_cut, hms_tr_should_cut,basic_cut,basic_cal_aero, hms_cal_should_cut, hms_cal_did_cut, shms_cal_should_cut, shms_cal_did_cut, cal_eff_hms_shms_base_cut  ;

    Double_t Epi_cut_acc, zhad_cut_acc, Mx2_cut_acc;
    Double_t ctmin = 2.0;//1.5
    Double_t ctmax = 2.0;//1.5
    Double_t rfmin = 0.5;//0.5;
    Double_t rfmax = 1.5;//1.5;
    Double_t eprmin = 0.0;
    Double_t eprmax = 0.2;//0.15;
    Double_t pcaletotmin = 0.0;
    Double_t pcaletotmax = 0.75;
    Double_t offsetrf;

    TH2D *h2_XYAtCer1                    = new TH2D("h2_XYAtCer1","HGC, P_hgcer_npeSum 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer;", 300, -40, 40, 300, -40, 40 );
    TH3D *h3_XYAtCer_npeSum1             = new TH3D("h3_XYAtCer_npeSum1","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_2p0             = new TH3D("h3_XYAtCer_npeSum1_2p0","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_5p0             = new TH3D("h3_XYAtCer_npeSum1_5p0","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_7p0             = new TH3D("h3_XYAtCer_npeSum1_7p0","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_gt7             = new TH3D("h3_XYAtCer_npeSum1_gt7","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);

    TH1F *hTotal2 = new TH1F ("hTotal2","",20,-10,20);                                                                                                                                     
    TH1F *hPass2 = new TH1F("hpass2","",20,-10,20);                                                                                                                                            
    TH2F *h2 = new TH2F("h2","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal5 = new TH1F ("hTotal5","",20,-10,20);                                                                                                                                     
    TH1F *hPass5 = new TH1F("hpass5","",20,-10,20);                                                                                                                                            
    TH2F *h5 = new TH2F("h5","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal7 = new TH1F ("hTotal7","",20,-10,20);                                                                                                                                     
    TH1F *hPass7 = new TH1F("hpass7","",20,-10,20);                                                                                                                                            
    TH2F *h7 = new TH2F("h7","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal7plus = new TH1F ("hTotal7plus","",20,-10,20);                                                                                                                                     
    TH1F *hPass7plus = new TH1F("hpass7plus","",20,-10,20);                                                                                                                                            
    TH2F *h7plus = new TH2F("h7plus","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal = new TH1F ("hTotal","",20,-10,20);                                                                                                                                     
    TH1F *hPass = new TH1F("hpass","",20,-10,20);                                                                                                                                            
    TH2F *h = new TH2F("h","Efficiency vs Delta",20,-10,20,100,0,1);

    
#include "offsetrf.h"
    TTree * tt = (TTree *)f->Get("T");
    TTree * ss = (TTree *)f->Get("TSP");
#include "define_histogram.h"

   

    //----------------------------------------Fill Hist
#include "branch.h"

    Long64_t nentriesD = tt->GetEntries();
   
   
#include "scaler_branch.h"
    Long64_t scal_entries = ss->GetEntries();
#include "scaler_analysis.h"

    Int_t nscaler_reads_acc=0;
    for (int kk=0; kk<nentriesD;  kk++){//---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(kk);

      if (event_flag[nscaler_reads_acc]==1) {
	paero_cut = paero>3.0;
	hgcer_cut = hgcer>1.0;
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut = rf_pion > rfmin && rf_pion < rfmax;
	mod4_notpioncut =!mod4_pioncut;
	pcal_cut =  pcaletottrack < pcaletotmax ;// && pcalepr< eprmax ;

	Epi_cut_acc = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut_acc = Epi_cut_acc/dnu;//variable name is same between acc abd real, but histogram name is different
	Mx2_cut_acc=(protonmass + dnu - zhad_cut_acc*dnu) *  (protonmass + dnu - zhad_cut_acc*dnu) - abs(dpmiss)*abs(dpmiss);
	 


	
	hms_cut  =  hdelta> -8 && hdelta < 8  && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hcernpe>1.0 &&dW2>4 && Mx2_cut_acc > 1.6    && hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04;
	shms_cut =  pdelta >-10 && pdelta < 20   && phodstarttime == 1 /* && eventtype > 3*/ &&  pcal_cut && mod4_pioncut && paero_cut && pdipole ==1  && pxptar>-0.05&&pxptar<0.05&&pyptar>-0.04&&pyptar<0.04;
	pid_cut  = hms_cut && shms_cut;
       
      
	if (pid_cut){//Note this is not the accidental, cut see below for the accidental cut section.
	  hpbeta->Fill(pbeta);
	  hctime->Fill(ctime);
	}  
	 
      }
      
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;
    }

    
    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
   
    Bool_t hgcer_cut1 ,paero_cut1 , mod4_pioncut1,  mod4_notpioncut1,   pcal_cut1,   hms_cut1,   shms_cut1, shms_cut2, pid_cut1, ctime_cut1, acc_cut1, acc_cut1hardcut,acc_cut_norf;

    Int_t nscaler_reads=0;

    
    for (int kk=0; kk<nentriesD;  kk++){//-----------------------------------------------------Main Evt Loop
      tt->GetEntry(kk);
      if (event_flag[nscaler_reads]==1) {

	 
	Epi_cut = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut = Epi_cut/dnu;//variable name is same between acc abd real, but histogram name is different
	Mx2_cut=(protonmass + dnu - zhad_cut*dnu) *  (protonmass + dnu - zhad_cut*dnu) - abs(dpmiss)*abs(dpmiss);

	accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
	accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
	acc_cut1hardcut = (accR_cut || accL_cut);
	ctime_cut1 = ctime > max_value - ctmin && ctime < max_value + ctmax;


	paero_cut1 = paero>3.0;
	hgcer_cut =  hgcer>2.0;
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut1 = rf_pion > rfmin && rf_pion < rfmax;
	mod4_notpioncut1 =!mod4_pioncut;
	pcal_cut1 =  pcaletottrack < pcaletotmax;

	
	hms_cut1  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hcernpe>1.0 &&dW2>4&&Mx2_cut>1.6 ;
	shms_cut1 =  pdelta >-10 && pdelta < 20   && phodstarttime == 1 && pdipole ==1 ;
	shms_cut2 =  pcal_cut1 && mod4_pioncut1 && paero_cut1;
	basic_cut = hms_cut1 && shms_cut1;
	basic_cal_aero = hms_cut1 && shms_cut1 &&  pcal_cut1 && paero_cut1;//No RF
	pid_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && ctime_cut1;//-------------------all cut vs1
	acc_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && acc_cut1hardcut;//final accidental cut----------------------------------------->
	//acc cut when you doot have RF time
	acc_cut_norf = hms_cut1 && shms_cut1 && pcal_cut1 &&  paero_cut1  && acc_cut1hardcut;
 
      	/////////////////hgcer eff//////////////////////////////////==============================================================================================


	
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4    && mod4_pioncut1){
	  h2_XYAtCer1->Fill(hgc_yAtCer,hgc_xAtCer);
	  hTotal->Fill(pdelta);

	  if(hgcer>0 ){
	    h3_XYAtCer_npeSum1->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	  }
	  
	  if(hgcer>0 && hgcer<=2){
	    h3_XYAtCer_npeSum1_2p0->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    // hPass2->Fill(pdelta);

	  }
	  
	  if(hgcer>2 && hgcer<=5){
	    h3_XYAtCer_npeSum1_5p0->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    // hPass5->Fill(pdelta);

	  }

	  if(hgcer>5 && hgcer<=7){
	    h3_XYAtCer_npeSum1_7p0->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    // hPass7->Fill(pdelta);

	  }
	  
	  if(hgcer>7){
	    h3_XYAtCer_npeSum1_gt7->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    //hPass7plus->Fill(pdelta);

	  }
	  if(hgcer>0){hPass->Fill(pdelta);}
	  if(hgcer>2){hPass2->Fill(pdelta);}
	  if(hgcer>5){hPass5->Fill(pdelta);}
	  if(hgcer>7){hPass7->Fill(pdelta);}




	  
	  
	}//coincut
      }	//entries data scal
      if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;

    }//entries
    TEfficiency *pEff = new TEfficiency();                                                                                                                                                                    pEff = new TEfficiency(*hPass, *hTotal); 

    TEfficiency *pEff2 = new TEfficiency();                                                                                                                                                                    pEff2 = new TEfficiency(*hPass2, *hTotal);
 
    TEfficiency *pEff5 = new TEfficiency();                                                                                                                                                                    pEff5 = new TEfficiency(*hPass5, *hTotal);

    TEfficiency *pEff7 = new TEfficiency();                                                                                                                                                                    pEff7 = new TEfficiency(*hPass7, *hTotal);

    TCanvas *c1 = new TCanvas("c1", "", 500,500);                                                                                                                                                             c1->Divide(2,2);
    c1->cd(1);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");
    
    h->Draw("");                                                                                                                                                                            
    pEff->Draw("same");

    c1->cd(2);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");                                                                                                                                                  
    h->Draw("");                                                                                                                                                                            
    pEff2->Draw("same");

    c1->cd(3);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");                                                                                                                                                  
    h->Draw("");                                                                                                                                                                            
    pEff5->Draw("same");


    c1->cd(4);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");                                                                                                                                                  
    h->Draw("");                                                                                                                                                                            
    pEff7->Draw("same");#include "header.h"
#include <iostream>
#include <string>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TPaveText.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TTree.h>
#include <TArc.h>
#include <TCutG.h>
#include <TExec.h>
#include <TColor.h>
#define NRUNS 2//34//56


void eff_hgc_xynpe_vijay(){
 gStyle->SetPalette(1,0);
 gStyle->SetOptStat(1000011);
 gStyle->SetOptFit(11);
 gStyle->SetTitleOffset(1.,"Y");
 gStyle->SetTitleOffset(.7,"X");
 gStyle->SetLabelSize(0.04,"XY");
 gStyle->SetTitleSize(0.06,"XY");
 gStyle->SetPadLeftMargin(0.12);  
  //#include "gStyle.h"
  // gStyle->SetOptStat(100011111);
  gStyle->SetOptStat(1000011);//integral
  // gStyle->SetOptStat(1111111);//integral


  Int_t runs[NRUNS]={6194, 6245};
   
  Double_t mom[NRUNS] ={ 3.936, 3.936};
  // gROOT->SetBatch("kTRUE");
  for(Int_t r=0; r<NRUNS; r++){

    TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/hgcer/added_%d.root", runs[r]);
    //TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/hgcer/coin_replay_production_%d_-1.root", runs[r]);
    // TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/coin_replay_production_%d_7796.root", runs[r]);

    TFile *f = new TFile(filename, "READ");
    TFile * f11 = new TFile(Form("root_rfeff/rfplot_zbins_%d.root",runs[r]),"RECREATE");

    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

    //#include "binkin391_401.h"
#include "bin7808.h"

    
    Double_t pionmass   = 0.1395701835;    //Gev/c^2 
    Double_t protonmass = 0.93827231;//GeV/c2
    Double_t dxbj, dQ2, dnu,domega,  dW2, dpmiss, demiss,  zhad, Mx2,Mx2a_acccut,Epi_acccut,zhad_acccut,Epi_pidcut,zhad_pidcut,Mx2_pidcut,Epi_cut,zhad_cut,Mx2_cut ;//d = data
    Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,phodgoodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit, phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,rf_pion,hhodgoodscinhit,hhodbetanotrack,hdcntrack,hgtry,pgtry,phodbetanotrack,hcaletotnorm,gevnum,hxptar,hyptar,pxptar,pyptar ;

    double scaler_eventnum,bcm1charge,bcm1current,scaler1MHztime,scaler1MHztimecut,bcm1chargecut,s1xscaler,s1yscaler,s2xscaler,s2yscaler,ptrig1scaler,ptrig2scaler,ptrig3scaler,ptrig4scaler,ptrig6scaler,pedtmscaler,pelcleanscaler,pl1acceptscaler,edtmtdctime,edtmtdctimeraw,mult,ptrig1rate,rate,charge,hgc_xAtCer,hgc_yAtCer   ;
    
    Double_t Epi_dcut0, z_dcut0, Epi_dcut1, z_dcut1, Epi_dcut2, z_dcut2, Epi_dcut3, z_dcut3, Epi_dcut1plus2, z_dcut1plus2; 
    Double_t Epi_acc0, z_acc0, Epi_acc1, z_acc1, Epi_acc2, z_acc2, Epi_acc3, z_acc3, Epi_acc1plus2, z_acc1plus2;

    Bool_t  accR_cut, accL_cut,shms_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, mod4_pioncut, mod4_notpioncut, pcal_cut, ctime_cut, hms_cut, pcal_cut_tight, cuttype1, cuttype1acc, cuttype2, cuttype2acc, cuttype1plus2, cuttype1plus2acc , hgcer_cut_loose,  paero_cut_loose,  cuttype0, cuttype0acc, common_cut, cuttype3, cuttype3acc, accsub_cut, acc_cut, shms_tr_did_cut, shms_tr_should_cut, hms_tr_did_cut, hms_tr_should_cut,basic_cut,basic_cal_aero, hms_cal_should_cut, hms_cal_did_cut, shms_cal_should_cut, shms_cal_did_cut, cal_eff_hms_shms_base_cut  ;

    Double_t Epi_cut_acc, zhad_cut_acc, Mx2_cut_acc;
    Double_t ctmin = 2.0;//1.5
    Double_t ctmax = 2.0;//1.5
    Double_t rfmin = 0.5;//0.5;
    Double_t rfmax = 1.5;//1.5;
    Double_t eprmin = 0.0;
    Double_t eprmax = 0.2;//0.15;
    Double_t pcaletotmin = 0.0;
    Double_t pcaletotmax = 0.75;
    Double_t offsetrf;

    TH2D *h2_XYAtCer1                    = new TH2D("h2_XYAtCer1","HGC, P_hgcer_npeSum 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer;", 300, -40, 40, 300, -40, 40 );
    TH3D *h3_XYAtCer_npeSum1             = new TH3D("h3_XYAtCer_npeSum1","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_2p0             = new TH3D("h3_XYAtCer_npeSum1_2p0","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_5p0             = new TH3D("h3_XYAtCer_npeSum1_5p0","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_7p0             = new TH3D("h3_XYAtCer_npeSum1_7p0","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
    TH3D *h3_XYAtCer_npeSum1_gt7             = new TH3D("h3_XYAtCer_npeSum1_gt7","HGC, P_hgcer_npeSum ; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);

    TH1F *hTotal2 = new TH1F ("hTotal2","",20,-10,20);                                                                                                                                     
    TH1F *hPass2 = new TH1F("hpass2","",20,-10,20);                                                                                                                                            
    TH2F *h2 = new TH2F("h2","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal5 = new TH1F ("hTotal5","",20,-10,20);                                                                                                                                     
    TH1F *hPass5 = new TH1F("hpass5","",20,-10,20);                                                                                                                                            
    TH2F *h5 = new TH2F("h5","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal7 = new TH1F ("hTotal7","",20,-10,20);                                                                                                                                     
    TH1F *hPass7 = new TH1F("hpass7","",20,-10,20);                                                                                                                                            
    TH2F *h7 = new TH2F("h7","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal7plus = new TH1F ("hTotal7plus","",20,-10,20);                                                                                                                                     
    TH1F *hPass7plus = new TH1F("hpass7plus","",20,-10,20);                                                                                                                                            
    TH2F *h7plus = new TH2F("h7plus","Efficiency vs Delta",20,-10,20,100,0,1);

    TH1F *hTotal = new TH1F ("hTotal","",20,-10,20);                                                                                                                                     
    TH1F *hPass = new TH1F("hpass","",20,-10,20);                                                                                                                                            
    TH2F *h = new TH2F("h","Efficiency vs Delta",20,-10,20,100,0,1);

    
#include "offsetrf.h"
    TTree * tt = (TTree *)f->Get("T");
    TTree * ss = (TTree *)f->Get("TSP");
#include "define_histogram.h"

   

    //----------------------------------------Fill Hist
#include "branch.h"

    Long64_t nentriesD = tt->GetEntries();
   
   
#include "scaler_branch.h"
    Long64_t scal_entries = ss->GetEntries();
#include "scaler_analysis.h"

    Int_t nscaler_reads_acc=0;
    for (int kk=0; kk<nentriesD;  kk++){//---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(kk);

      if (event_flag[nscaler_reads_acc]==1) {
	paero_cut = paero>3.0;
	hgcer_cut = hgcer>1.0;
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut = rf_pion > rfmin && rf_pion < rfmax;
	mod4_notpioncut =!mod4_pioncut;
	pcal_cut =  pcaletottrack < pcaletotmax ;// && pcalepr< eprmax ;

	Epi_cut_acc = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut_acc = Epi_cut_acc/dnu;//variable name is same between acc abd real, but histogram name is different
	Mx2_cut_acc=(protonmass + dnu - zhad_cut_acc*dnu) *  (protonmass + dnu - zhad_cut_acc*dnu) - abs(dpmiss)*abs(dpmiss);
	 


	
	hms_cut  =  hdelta> -8 && hdelta < 8  && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hcernpe>1.0 &&dW2>4 && Mx2_cut_acc > 1.6    && hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04;
	shms_cut =  pdelta >-10 && pdelta < 20   && phodstarttime == 1 /* && eventtype > 3*/ &&  pcal_cut && mod4_pioncut && paero_cut && pdipole ==1  && pxptar>-0.05&&pxptar<0.05&&pyptar>-0.04&&pyptar<0.04;
	pid_cut  = hms_cut && shms_cut;
       
      
	if (pid_cut){//Note this is not the accidental, cut see below for the accidental cut section.
	  hpbeta->Fill(pbeta);
	  hctime->Fill(ctime);
	}  
	 
      }
      
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;
    }

    
    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
   
    Bool_t hgcer_cut1 ,paero_cut1 , mod4_pioncut1,  mod4_notpioncut1,   pcal_cut1,   hms_cut1,   shms_cut1, shms_cut2, pid_cut1, ctime_cut1, acc_cut1, acc_cut1hardcut,acc_cut_norf;

    Int_t nscaler_reads=0;

    
    for (int kk=0; kk<nentriesD;  kk++){//-----------------------------------------------------Main Evt Loop
      tt->GetEntry(kk);
      if (event_flag[nscaler_reads]==1) {

	 
	Epi_cut = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut = Epi_cut/dnu;//variable name is same between acc abd real, but histogram name is different
	Mx2_cut=(protonmass + dnu - zhad_cut*dnu) *  (protonmass + dnu - zhad_cut*dnu) - abs(dpmiss)*abs(dpmiss);

	accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
	accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
	acc_cut1hardcut = (accR_cut || accL_cut);
	ctime_cut1 = ctime > max_value - ctmin && ctime < max_value + ctmax;


	paero_cut1 = paero>3.0;
	hgcer_cut =  hgcer>2.0;
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut1 = rf_pion > rfmin && rf_pion < rfmax;
	mod4_notpioncut1 =!mod4_pioncut;
	pcal_cut1 =  pcaletottrack < pcaletotmax;

	
	hms_cut1  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hcernpe>1.0 &&dW2>4&&Mx2_cut>1.6 ;
	shms_cut1 =  pdelta >-10 && pdelta < 20   && phodstarttime == 1 && pdipole ==1 ;
	shms_cut2 =  pcal_cut1 && mod4_pioncut1 && paero_cut1;
	basic_cut = hms_cut1 && shms_cut1;
	basic_cal_aero = hms_cut1 && shms_cut1 &&  pcal_cut1 && paero_cut1;//No RF
	pid_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && ctime_cut1;//-------------------all cut vs1
	acc_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && acc_cut1hardcut;//final accidental cut----------------------------------------->
	//acc cut when you doot have RF time
	acc_cut_norf = hms_cut1 && shms_cut1 && pcal_cut1 &&  paero_cut1  && acc_cut1hardcut;
 
      	/////////////////hgcer eff//////////////////////////////////==============================================================================================


	
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4    && mod4_pioncut1){
	  h2_XYAtCer1->Fill(hgc_yAtCer,hgc_xAtCer);
	  hTotal->Fill(pdelta);

	  if(hgcer>0 ){
	    h3_XYAtCer_npeSum1->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	  }
	  
	  if(hgcer>0 && hgcer<=2){
	    h3_XYAtCer_npeSum1_2p0->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    // hPass2->Fill(pdelta);

	  }
	  
	  if(hgcer>2 && hgcer<=5){
	    h3_XYAtCer_npeSum1_5p0->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    // hPass5->Fill(pdelta);

	  }

	  if(hgcer>5 && hgcer<=7){
	    h3_XYAtCer_npeSum1_7p0->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    // hPass7->Fill(pdelta);

	  }
	  
	  if(hgcer>7){
	    h3_XYAtCer_npeSum1_gt7->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	    //hPass7plus->Fill(pdelta);

	  }
	  if(hgcer>0){hPass->Fill(pdelta);}
	  if(hgcer>2){hPass2->Fill(pdelta);}
	  if(hgcer>5){hPass5->Fill(pdelta);}
	  if(hgcer>7){hPass7->Fill(pdelta);}




	  
	  
	}//coincut
      }	//entries data scal
      if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;

    }//entries
    TEfficiency *pEff = new TEfficiency();                                                                                                                                                                    pEff = new TEfficiency(*hPass, *hTotal); 

    TEfficiency *pEff2 = new TEfficiency();                                                                                                                                                                    pEff2 = new TEfficiency(*hPass2, *hTotal);
 
    TEfficiency *pEff5 = new TEfficiency();                                                                                                                                                                    pEff5 = new TEfficiency(*hPass5, *hTotal);

    TEfficiency *pEff7 = new TEfficiency();                                                                                                                                                                    pEff7 = new TEfficiency(*hPass7, *hTotal);

    TCanvas *c1 = new TCanvas("c1", "", 500,500);                                                                                                                                                             c1->Divide(2,2);
    c1->cd(1);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");
    
    h->Draw("");                                                                                                                                                                            
    pEff->Draw("same");

    c1->cd(2);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");                                                                                                                                                  
    h->Draw("");                                                                                                                                                                            
    pEff2->Draw("same");

    c1->cd(3);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");                                                                                                                                                  
    h->Draw("");                                                                                                                                                                            
    pEff5->Draw("same");


    c1->cd(4);
    h->GetXaxis()->CenterTitle();                                                                                                                                                          
    h->GetYaxis()->CenterTitle();                                                                                                                                                              
    h->GetXaxis()->SetTitle("P.gtr.dp ");                                                                                                                                                   
    h->GetYaxis()->SetTitle(" Efficiency");                                                                                                                                                  
    h->Draw("");                                                                                                                                                                            
    pEff7->Draw("same");
    
    c1->SaveAs(Form("pdf_hgc/eff_%d.pdf",runs[r]));

    

      
    TProfile2D *h3_XYAtCer_npeSum1_pyx = new TProfile2D("h3_XYAtCer_npeSum1_pyx","YAtCer vs XAtCer vs NPE > 0 ; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_2p0_pyx = new TProfile2D("h3_XYAtCer_npeSum1_2p0_pyx","YAtCer vs XAtCer vs NPE 0 to 2 ; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_2p0->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_5p0_pyx = new TProfile2D("h3_XYAtCer_npeSum1_5p0_pyx","YAtCer vs XAtCer vs NPE 2 to 5; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_5p0->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_7p0_pyx = new TProfile2D("h3_XYAtCer_npeSum1_7p0_pyx","YAtCer vs XAtCer vs NPE 5 to 7; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_7p0->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_gt7_pyx = new TProfile2D("h3_XYAtCer_npeSum1_gt7_pyx","YAtCer vs XAtCer vs NPE > 7; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_gt7->Project3DProfile("yx");


    TCanvas *hg = new TCanvas("hg","hgc plots",1600, 1200);
    hg->Divide(3,2);
    hg->cd(1);gPad->SetLogz();gPad->SetGrid();
    h2_XYAtCer1->Draw("colz");

    hg->cd(2);gPad->SetGrid();
    h3_XYAtCer_npeSum1_pyx->Draw("colz");

    hg->cd(3);gPad->SetGrid();
    h3_XYAtCer_npeSum1_2p0_pyx->Draw("colz");

    hg->cd(4);gPad->SetGrid();
    h3_XYAtCer_npeSum1_5p0_pyx->Draw("colz");

    hg->cd(5);gPad->SetGrid();
    h3_XYAtCer_npeSum1_7p0_pyx->Draw("colz");

    hg->cd(6);gPad->SetGrid();
    h3_XYAtCer_npeSum1_gt7_pyx->Draw("colz");

    hg->SaveAs(Form("pdf_hgc/hgcer_y_vs_x_logz_%d.pdf",runs[r]));
 
   

    
  
  }//runs
 
}//all



    
    c1->SaveAs(Form("pdf_hgc/eff_%d.pdf",runs[r]));

    

      
    TProfile2D *h3_XYAtCer_npeSum1_pyx = new TProfile2D("h3_XYAtCer_npeSum1_pyx","YAtCer vs XAtCer vs NPE > 0 ; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_2p0_pyx = new TProfile2D("h3_XYAtCer_npeSum1_2p0_pyx","YAtCer vs XAtCer vs NPE 0 to 2 ; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_2p0->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_5p0_pyx = new TProfile2D("h3_XYAtCer_npeSum1_5p0_pyx","YAtCer vs XAtCer vs NPE 2 to 5; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_5p0->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_7p0_pyx = new TProfile2D("h3_XYAtCer_npeSum1_7p0_pyx","YAtCer vs XAtCer vs NPE 5 to 7; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_7p0->Project3DProfile("yx");

    TProfile2D *h3_XYAtCer_npeSum1_gt7_pyx = new TProfile2D("h3_XYAtCer_npeSum1_gt7_pyx","YAtCer vs XAtCer vs NPE > 7; P_hgcer_yAtCer; P_hgcer_xAtCer;NPE ",300,-40,40, 300,-40,40, 0, 30);
    h3_XYAtCer_npeSum1_gt7->Project3DProfile("yx");


    TCanvas *hg = new TCanvas("hg","hgc plots",1600, 1200);
    hg->Divide(3,2);
    hg->cd(1);gPad->SetLogz();gPad->SetGrid();
    h2_XYAtCer1->Draw("colz");

    hg->cd(2);gPad->SetGrid();
    h3_XYAtCer_npeSum1_pyx->Draw("colz");

    hg->cd(3);gPad->SetGrid();
    h3_XYAtCer_npeSum1_2p0_pyx->Draw("colz");

    hg->cd(4);gPad->SetGrid();
    h3_XYAtCer_npeSum1_5p0_pyx->Draw("colz");

    hg->cd(5);gPad->SetGrid();
    h3_XYAtCer_npeSum1_7p0_pyx->Draw("colz");

    hg->cd(6);gPad->SetGrid();
    h3_XYAtCer_npeSum1_gt7_pyx->Draw("colz");

    hg->SaveAs(Form("pdf_hgc/hgcer_y_vs_x_logz_%d.pdf",runs[r]));
 
   

    
  
  }//runs
 
}//all


