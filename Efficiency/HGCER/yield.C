//This applies the hgcer efficiency correction in Yield.


//made pcal 0.6, hcal 0.8, rf 0.4 , ctime 2, hcer 8, delta dropped centaral, graphical cut on
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
#define NRUNS 1//2//5


Double_t fun(double *x, double * par){// x = mom
  if (x[0] > 3.7 && x[0] < 4.15) {
    TF1::RejectPoint();
    return 0;
  }
  return par[0]*(1-par[1] * (x[0]*x[0]+0.1395701835*0.1395701835)/(1.00137*1.00137*x[0]*x[0]));
}

Double_t fun2(double *x, double * par){
  return par[0]*(1-par[1] * (x[0]*x[0]+0.1395701835*0.1395701835)/(1.00137*1.00137*x[0]*x[0]));
}


double RI = 1.00137;

void yield(){
  gStyle->SetPalette(1,0);//color in 2D 3D
  gStyle->SetOptStat(1000011);
  gStyle->SetOptFit(11);
  gStyle->SetTitleOffset(1.,"Y");
  gStyle->SetTitleOffset(.7,"X");
  gStyle->SetLabelSize(0.04,"XY");
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetPadLeftMargin(0.12);  
  //#include "gStyle.h"
  // gStyle->SetOptStat(0);
  //gStyle->SetOptStat(1000011);//integral
  // gStyle->SetOptStat(1111111);//integral
  gStyle->SetOptFit(1);//integral
   gStyle->SetErrorX(0.);    

  ofstream txtfile("txtfile/hgcer_eff.txt",ios::app);
  
  Int_t runs[NRUNS]={7735};//{7808};//,7635, 7593};//, 6194, 6245, 7796, 7768, 7735};
   
  Double_t mom[NRUNS] ={3.214};//{3.46};//,3.15, 3.15};//, 3.936, 3.936, 3.461, 3.214, 3.214};
  Double_t chargeq[NRUNS]={155};
  // gROOT->SetBatch("kTRUE");
  for(Int_t r=0; r<NRUNS; r++){

    // TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/hgcer/added_%d.root", runs[r]);
    TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/hgcer/coin_replay_production_%d_-1.root", runs[r]);    
    TFile *f = new TFile(filename, "READ");
    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }
    
    TString filename1  = Form("/home/hdbhatt/efficiency/hgcer/root/efficiency_map_%d.root", runs[r]);    
    // TString filename1  = Form("/home/hdbhatt/efficiency/hgcer/root/efficiency_map_nogrcut_%d.root", runs[r]);    
 TFile *f1 = new TFile(filename1, "READ");
    if(f1->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }


    TCutG *cutg = new TCutG("cutg",19);
    cutg->SetVarX("");
    cutg->SetVarY("");
    cutg->SetPoint(0, 7.87, 0 );
    cutg->SetPoint(1, 7.87, 2.5 );
    cutg->SetPoint(2, 5.25, 2.5 ) ;
    cutg->SetPoint(3, 5.25, 5.0);
    cutg->SetPoint(4, -2.7, 5.0);
    cutg->SetPoint(5, -2.5, 2.5);
    cutg->SetPoint(6, 8.08, 2.5);
    cutg->SetPoint(7, -8.08, 5.0);
    cutg->SetPoint(8, -10.65, 5.0 );
    cutg->SetPoint(9, -10.65, 2.5);
    cutg->SetPoint(10, -13.3, 2.5 );
    cutg->SetPoint(11, -13.3, 0 );
    cutg->SetPoint(12,  -2.72, 0) ;
    cutg->SetPoint(13, -2.5, -2.5);
    cutg->SetPoint(14, 0, -2.5 );
    cutg->SetPoint(15, 2.5, -2.5 );
    cutg->SetPoint(16, 5, -2.5 );
    cutg->SetPoint(17, 5, 0 );
    cutg->SetPoint(18, 7.87, 0 );
     
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
    Double_t ctmin = 1.8;//2.0;//1.5
    Double_t ctmax = 1.8;//2.0;//1.5
    Double_t rfmin = 0.5;//0.5;//0.5;
    Double_t rfmax = 1.5;//1.5;//1.5;
    Double_t eprmin = 0.0;
    Double_t eprmax = 0.2;//0.15;
    Double_t pcaletotmin = 0.0;
    Double_t pcaletotmax = 0.75;//0.75;
    Double_t offsetrf;
    double nbin  = 30;
    double loxy = -40;
    double hixy  = 40;
    double lodelta = -10;
    double hidelta = 20;
    double npelo = 0;
    double npehi = 30;

    double binxcer,binycer,eff_value;
    TH2D *h2_XYAtCer1                      = new TH2D("h2_XYAtCer1","HGC, P_hgcer_npeSum 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer;", nbin, loxy, hixy, nbin, loxy, hixy );
    TH2D *h2_XYAtCer0p5                    = new TH2D("h2_XYAtCer0p5","HGC, P_hgcer_npeSum 0.5; P_hgcer_yAtCer; P_hgcer_xAtCer;", nbin, loxy, hixy, nbin, loxy, hixy );
    TH3D *h3_XYAtCer_eff                   = new TH3D("h3_XYAtCer_eff","HGC Eff; P_hgcer_yAtCer; P_hgcer_xAtCer; Eff;", nbin, loxy, hixy, nbin, loxy, hixy, nbin, 0, 1);//eff
    //2D==3D, no bins in 3rd Axis, 0-1 = Weight //Devi BEst
    TProfile2D * twoD_eff = new TProfile2D("twoD_eff","Hgcer Eff as a function of x and y At Cer;P.hgcer.yAtCer;P.hgcer.xAtCer;Eff", nbin, loxy, hixy, nbin,loxy, hixy, 0, 1);
    //2D==3D, no bins in 3rd Axis, 0-1 = Weight //Devi BEst
    TH3D *h3_XYAtCer_npeSum1     = new TH3D("h3_XYAtCer_npeSum1","HGC Eff; P_hgcer_yAtCer; P_hgcer_xAtCer; NPE;", nbin, loxy, hixy, nbin, loxy, hixy, nbin, npelo, npehi);
    TProfile2D * hgcer_eff_npe0p5 = new TProfile2D("hgcer_eff_npe0p5","Hgcer Eff for Npe > 0.5; P_hgcer_yAtCer; P_hgcer_xAtCer; eff", nbin, loxy, hixy, nbin,loxy, hixy, 0, 1);
    TH2D *hRF_pion_vs_hgcer = new TH2D("hRF_pion_vs_hgcer","hRF_pion_vs_hgcer;  RF Time (ns); Hgcer NpeSum", nbin, 0, 4, nbin, npelo, npehi);

    //nocut
    TH1F *hTotal1dx_nocut = new TH1F ("hTotal1dx_nocut","",nbin, loxy, hixy);               
    TH1F *hPass1dx_nocut = new TH1F("hpass1dx_nocut","",nbin, loxy, hixy);
    TH1F *hTotal1dy_nocut = new TH1F ("hTotal1dy_nocut","",nbin, loxy, hixy);          
    TH1F *hPass1dy_nocut = new TH1F("hpass1dy_nocut","",nbin, loxy, hixy);
    TH1F *hTotal1ddp_nocut = new TH1F ("hTotal1ddp_nocut","",nbin, lodelta, hidelta); 
    TH1F *hPass1ddp_nocut = new TH1F("hpass1ddp_nocut","",nbin, lodelta, hidelta);
    TH2F *hTotal_2d_nocut = new TH2F ("hTotal_2d_nocut","",nbin, loxy, hixy, nbin, loxy, hixy);
    TH2F *hPass_2d_nocut = new TH2F("hpass_2d_nocut","",nbin, loxy, hixy, nbin, loxy, hixy);
    TProfile2D * xy_vs_npe_nocut = new TProfile2D("xy_vs_npe_nocut","Hgcer NPE as a function of x and y At Cer;P.hgcer.yAtCer;P.hgcer.xAtCer;NPESUM", nbin, loxy, hixy, nbin,loxy, hixy, npelo, npehi);
    TH1D *hRF_pion_nocut = new TH1D("hRF_pion","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    TH1D *hRF_pion_nocut_hgc = new TH1D("hRF_pion_nocut_hgc","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    //xcut
    TH1F *hTotal1dx_xcut = new TH1F ("hTotal1dx_xcut","",nbin, loxy, hixy);               
    TH1F *hPass1dx_xcut = new TH1F("hpass1dx_xcut","",nbin, loxy, hixy);
    TH1F *hTotal1dy_xcut = new TH1F ("hTotal1dy_xcut","",nbin, loxy, hixy);          
    TH1F *hPass1dy_xcut = new TH1F("hpass1dy_xcut","",nbin, loxy, hixy);
    TH1F *hTotal1ddp_xcut = new TH1F ("hTotal1ddp_xcut","",nbin, lodelta, hidelta); 
    TH1F *hPass1ddp_xcut = new TH1F("hpass1ddp_xcut","",nbin, lodelta, hidelta);
    TH2F *hTotal_2d_xcut = new TH2F ("hTotal_2d_xcut","",nbin, loxy, hixy, nbin, loxy, hixy);
    TH2F *hPass_2d_xcut = new TH2F("hpass_2d_xcut","",nbin, loxy, hixy, nbin, loxy, hixy);
    TProfile2D * xy_vs_npe_xcut = new TProfile2D("xy_vs_npe_xcut","Hgcer NPE as a function of x and y At Cer;P.hgcer.yAtCer;P.hgcer.xAtCer;NPESUM", nbin, loxy, hixy, nbin,loxy, hixy, npelo, npehi);
    TH1D *hRF_pion_xcut  = new TH1D("hRF_pion_xcut","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    TH1D *hRF_pion_xcut_hgc = new TH1D("hRF_pion_xcut_hgc","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    //grcut
    TH1F *hTotal1dx_grcut = new TH1F ("hTotal1dx_grcut","",nbin, loxy, hixy);               
    TH1F *hPass1dx_grcut = new TH1F("hpass1dx_grcut","",nbin, loxy, hixy);
    TH1F *hTotal1dy_grcut = new TH1F ("hTotal1dy_grcut","",nbin, loxy, hixy);          
    TH1F *hPass1dy_grcut = new TH1F("hpass1dy_grcut","",nbin, loxy, hixy);
    TH1F *hTotal1ddp_grcut = new TH1F ("hTotal1ddp_grcut","",nbin, lodelta, hidelta); 
    TH1F *hPass1ddp_grcut = new TH1F("hpass1ddp_grcut","",nbin, lodelta, hidelta);
    TH2F *hTotal_2d_grcut = new TH2F ("hTotal_2d_grcut","",nbin, loxy, hixy, nbin, loxy, hixy);
    TH2F *hPass_2d_grcut = new TH2F("hpass_2d_grcut","",nbin, loxy, hixy, nbin, loxy, hixy); 
    TProfile2D * xy_vs_npe_grcut = new TProfile2D("xy_vs_npe_grcut","Hgcer NPE as a function of x and y At Cer;P.hgcer.yAtCer;P.hgcer.xAtCer;NPESUM", nbin, loxy, hixy, nbin,loxy, hixy, npelo, npehi);
    TH1D *hRF_pion_grcut   = new TH1D("hRF_pion_grcut","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    TH1D *hRF_pion_grcut_hgc  = new TH1D("hRF_pion_grcut_hgc","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    //dip
    TH1F *hTotal1dx_dip = new TH1F ("hTotal1dx_dip","",nbin, loxy, hixy);               
    TH1F *hPass1dx_dip = new TH1F("hpass1dx_dip","",nbin, loxy, hixy);
    TH1F *hTotal1dy_dip = new TH1F ("hTotal1dy_dip","",nbin, loxy, hixy);          
    TH1F *hPass1dy_dip = new TH1F("hpass1dy_dip","",nbin, loxy, hixy);
    TH1F *hTotal1ddp_dip = new TH1F ("hTotal1ddp_dip","",nbin, lodelta, hidelta); 
    TH1F *hPass1ddp_dip = new TH1F("hpass1ddp_dip","",nbin, lodelta, hidelta);
    TH2F *hTotal_2d_dip = new TH2F ("hTotal_2d_dip","",nbin, loxy, hixy, nbin, loxy, hixy);
    TH2F *hPass_2d_dip = new TH2F("hpass_2d_dip","",nbin, loxy, hixy, nbin, loxy, hixy); 
    TProfile2D * xy_vs_npe_dip = new TProfile2D("xy_vs_npe_dip","Hgcer NPE as a function of x and y At Cer;P.hgcer.yAtCer;P.hgcer.xAtCer;NPESUM", nbin, loxy, hixy, nbin,loxy, hixy, npelo, npehi);
    TH1D *hRF_pion_dip   = new TH1D("hRF_pion_dip","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    TH1D *hRF_pion_dip_hgc  = new TH1D("hRF_pion_dip_hgc","hRF_pion;  RF Time (ns); Counts", nbin, 0, 4);
    
    TH1F *hmom = new TH1F("hmom","hmom", nbin, 2.5, 5.5);
    TH2F *eff_vs_delta = new TH2F("eff_vs_delta","eff_vs_delta", nbin, lodelta, hidelta, nbin, 0, 1.05);
    TH2F *eff_vs_x = new TH2F("eff_vs_x","eff_vs_x", nbin, loxy, hixy, nbin, 0, 1.05);
    TH2F *eff_vs_y = new TH2F("eff_vs_y","eff_vs_y", nbin, loxy, hixy, nbin, 0, 1.05);

    TH2F *tight_cuts_delta = new TH2F("tight_cuts_delta","tight_cuts_delta", nbin, lodelta, hidelta, nbin, 0, 1.05);
    //try by hpass/hTotal actual division
    TH1F *hgc_eff_delta = new TH1F("hgc_eff_delta","hgc_eff_delta", nbin, lodelta, hidelta);

    TH1F *hzhad = new TH1F ("hzhad","hzhad",20, 0, 1);               
    TH1F *hzhad_corr = new TH1F ("hzhad_corr","",20, 0, 1);               
    TH1F *hzhad_yield_corr = new TH1F ("hzhad_yield_corr","",20, 0, 1);               
    TH1F *hzhad_yield = new TH1F ("hzhad_yield","hzhad_yield",20, 0, 1);               
    TH1F *hzhad_grcut = new TH1F ("hzhad_grcut","",20, 0, 1);               
    TH1F *hzhad_grcut_corr = new TH1F ("hzhad_grcut_corr","",20, 0, 1);               

    TH1F *hTotal1ddp_nocut_corr = new TH1F ("hTotal1ddp_nocut_corr","",nbin, lodelta, hidelta); 
    TH1F *hTotal1ddp_nocut_yield = new TH1F ("hTotal1ddp_nocut_yield","",nbin, lodelta, hidelta); 
    TH1F *hTotal1ddp_nocut_yield_corr = new TH1F ("hTotal1ddp_nocut_yield_corr","",nbin, lodelta, hidelta); 
    TH1F *hTotal1ddp_grcut_corr = new TH1F ("hTotal1ddp_grcut_corr","",nbin, lodelta, hidelta); 

    // :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
    // this is read from efficiency map
    TH2F * eff_xy = (TH2F*)f1->Get("eff_xy");
    TCanvas * c1 = new TCanvas("c1", "c1", 1200, 800);
    c1->Divide(1,1);
    c1->cd(1);gPad->SetGrid();gPad->SetLogz();
    eff_xy->Draw("colz");
    c1->SaveAs(Form("pdf_eff/efficiency_map_xy_%d.pdf",runs[r]));


    
    FILE *ofile= fopen("txtfile/eff.txt","w");
    fprintf(ofile,"%s\t","(x,y->)");
    for(int k =1; k<=eff_xy->GetNbinsX(); k++){
      double xcer = eff_xy->GetYaxis()->GetBinCenter(k);
      fprintf(ofile,"%.1f\t",xcer);//yaxis values
    }
    fprintf(ofile,"\n");

    for (int i=1; i <= eff_xy->GetNbinsY(); i++){
      double ycer = eff_xy->GetXaxis()->GetBinCenter(i);
      fprintf(ofile,"%.1f\t",ycer);//xaxis values

      for (int j=1; j <= eff_xy->GetNbinsX(); j++){
        double eff2d = eff_xy->GetBinContent(i,j); //(x-axis,y-axis)

	fprintf(ofile,"%.3f\t", eff2d);
      }
      fprintf(ofile,"\n");
    }
    
    fclose(ofile);


    
 // cout<<
 // cout<< i<<"   "<<eff_xy->GetBinContent(i)<<"   "<<eff_xy->GetBinContent(j)<< endl
 // txtfile<<"\t"<<i;txtfile<<j<<"\t"<<eff2d;
 // cout<<i<<"\t"<<j<<"\t"<< eff2d <<endl;
    
// double	binxcer1      = eff_xy->GetYaxis()->FindBin(hgc_xAtCer);
// double	binycer1      = eff_xy->GetXaxis()->FindBin(hgc_yAtCer);
// double	eff_value1    = eff_xy->GetBinContent(binycer1, binxcer1);

    // :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=

    
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
   	
       	hms_cut  =  hdelta> -8 && hdelta < 8  && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hcernpe>1.0    && hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04;
	shms_cut =  pdelta >-10 && pdelta < 20   && phodstarttime == 1  && eventtype > 3 &&  pcal_cut && mod4_pioncut && paero_cut && pdipole ==1  && pxptar>-0.05&&pxptar<0.05&&pyptar>-0.04&&pyptar<0.04;//&&dW2>4 && Mx2_cut_acc > 1.6

	pid_cut  = hms_cut && shms_cut;
       
      
	if (pid_cut){//Note this is not the accidental, cut see below for the accidental cut section.
	  hpbeta->Fill(pbeta);
	  hctime->Fill(ctime);
	  hmom->Fill(PgtrP);
	}  
	 
      }
      
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;
    }

    
    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
    double centralP = hmom->GetMean();
    cout<<" "<<endl;
    cout<< runs[r]<<"  "<< "Central P = "<< centralP << endl;
    cout<<"  "<<endl;

    double binloP = centralP*0.9;
    double binhiP = centralP*1.2;
		

    TProfile * hgc_npe_vs_mom_nocut = new TProfile(" hgc_npe_vs_mom_nocut"," hgc_npe_vs_mom_nocut", nbin, binloP, binhiP,  npelo, npehi);
    TProfile * hgc_npe_vs_mom_xcut  = new TProfile(" hgc_npe_vs_mom_xcut"," hgc_npe_vs_mom_xcut", nbin, binloP, binhiP,  npelo, npehi);
    TProfile * hgc_npe_vs_mom_grcut = new TProfile(" hgc_npe_vs_mom_grcut"," hgc_npe_vs_mom_grcut", nbin, binloP, binhiP,  npelo, npehi);
    TProfile * hgc_npe_vs_mom_dip = new TProfile(" hgc_npe_vs_mom_dip"," hgc_npe_vs_mom_dip", nbin, binloP, binhiP,  npelo, npehi);


		
    Bool_t hgcer_cut1 ,paero_cut1 , mod4_pioncut1,  mod4_notpioncut1,   pcal_cut1,   hms_cut1,   shms_cut1, shms_cut2, pid_cut1, ctime_cut1, acc_cut1, acc_cut1hardcut,acc_cut_norf;


    Int_t nscaler_reads=0;

      
    for (int kk=0; kk<nentriesD;  kk++){//-----------------------------------------------------Main Evt Loop
      tt->GetEntry(kk);
      if (event_flag[nscaler_reads]==1) {
	// :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
	//  efficiency map begin
	// :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
	binxcer      = eff_xy->GetYaxis()->FindBin(hgc_xAtCer);
	binycer      = eff_xy->GetXaxis()->FindBin(hgc_yAtCer);
	eff_value    = eff_xy->GetBinContent(binycer, binxcer);

	if (eff_value == 0){eff_value = 1;}
	//cout<<eff_value<<endl;
	// :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
	//  efficiency map done
	// :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
	 
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

	hms_cut1  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 &&hxptar>-0.08 && hxptar<0.08&& hyptar>-0.04 && hyptar<0.04 && pxptar>-0.05&&pxptar<0.05&&pyptar>-0.04&&pyptar<0.04;
	shms_cut1 =  pdelta >-10 &&  pdelta < 20   && phodstarttime == 1 && pdipole ==1 ;


	shms_cut2 =  pcal_cut1 && mod4_pioncut1 && paero_cut1;
	basic_cut = hms_cut1 && shms_cut1;
	basic_cal_aero = hms_cut1 && shms_cut1 &&  pcal_cut1 && paero_cut1;//No RF
	pid_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && ctime_cut1;//-------------------all cut vs1
	acc_cut1 = hms_cut1 && shms_cut1 && shms_cut2 && acc_cut1hardcut;//final accidental cut----------------------------------------->
	acc_cut_norf = hms_cut1 && shms_cut1 && pcal_cut1 &&  paero_cut1  && acc_cut1hardcut;
 
	//nocut
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4  && mod4_pioncut1){

	  hRF_pion_nocut->Fill(rf_pion);
	  xy_vs_npe_nocut->Fill(hgc_yAtCer,hgc_xAtCer,hgcer);
	  hgc_npe_vs_mom_nocut->Fill(PgtrP,hgcer);

	  //no eff corr
	  hTotal1ddp_nocut->Fill(pdelta);
	  hzhad->Fill(zhad_cut);
	  //eff_corr
	  hTotal1ddp_nocut_corr->Fill(pdelta,1./eff_value);
	  hzhad_corr->Fill(zhad_cut,1./eff_value);
	  //eff_corr done

	  hTotal1dx_nocut->Fill(hgc_xAtCer);
	  hTotal1dy_nocut->Fill(hgc_yAtCer);
	  hTotal_2d_nocut->Fill(hgc_yAtCer,hgc_xAtCer);

	  if(hgcer>0.5){
	    hRF_pion_nocut_hgc->Fill(rf_pion);
	    hPass1ddp_nocut->Fill(pdelta);
	    hPass1dx_nocut->Fill(hgc_xAtCer);
	    hPass1dy_nocut->Fill(hgc_yAtCer);
	    hPass_2d_nocut->Fill(hgc_yAtCer,hgc_xAtCer);
	  }  
	}//no cut done
	// :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
	// graphical cut only
	// :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
	if(hms_cut1 && shms_cut1 && pcal_cut1 && ctime_cut1 && paero > 4  && mod4_pioncut1   /*&& (!cutg->IsInside(hgc_yAtCer,hgc_xAtCer))*/){
	  hTotal1ddp_grcut->Fill(pdelta);
	  hzhad_grcut->Fill(zhad_cut);
	  hTotal1ddp_grcut_corr->Fill(pdelta,1./eff_value);
	  hzhad_grcut_corr->Fill(zhad_cut,1./eff_value);
	  
	}
      }//scaler entries
      if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;
    }	//entries data scal

   
    TFile* pFile = new TFile(Form("root/yield_plots_%d.root",runs[r]),"RECREATE");    
   
    ///Yield

    hzhad_yield = (TH1F*)hzhad->Clone("hzhad_yield");
    hTotal1ddp_nocut_yield = (TH1F*)hTotal1ddp_nocut->Clone("hTotal1ddp_nocut_yield");
    hzhad_yield_corr = (TH1F*)hzhad_corr->Clone("hzhad_yield_corr");
    hTotal1ddp_nocut_yield_corr = (TH1F*)hTotal1ddp_nocut_corr->Clone("hTotal1ddp_nocut_yield_corr");

    
    double scalefac =chargeq[r]/1000.0;//mC
    hzhad_yield->Scale(1./scalefac);
    hTotal1ddp_nocut_yield->Scale(1/scalefac);
    hzhad_yield_corr->Scale(1./scalefac);
    hTotal1ddp_nocut_yield_corr->Scale(1/scalefac);

    
    TCanvas *c2 = new TCanvas("c2","c2", 1200, 800);
    c2->Divide(2,2);
    // c2->cd(1);gPad->SetGrid();
    // hTotal1ddp_nocut->Draw("e, p1");
    // hTotal1ddp_nocut->SetMarkerStyle(20);
    // hTotal1ddp_nocut->SetLineWidth(2);
    // hTotal1ddp_nocut->SetTitle(Form("Run: %d counts vs Delta: P = %f",runs[r], mom[r]));
    // hTotal1ddp_nocut->Write();
    
    
    // c2->cd(2);gPad->SetGrid();
    // hzhad->Draw("e, p1");
    // hzhad->SetTitle(Form("Run: %d counts vs z: P = %f",runs[r], mom[r]));
    // hzhad->SetMarkerStyle(20);
    // hzhad->SetLineWidth(2);
    // hzhad->Write();


    c2->cd(1);gPad->SetGrid();
    hTotal1ddp_nocut_yield->Draw("e, p1");
    hTotal1ddp_nocut_yield->SetMarkerStyle(20);
    hTotal1ddp_nocut_yield->SetLineWidth(2);
    hTotal1ddp_nocut_yield->SetTitle(Form("Run: %d Yield vs Delta: P = %f",runs[r], mom[r]));
    hTotal1ddp_nocut_yield->Write();
    hTotal1ddp_nocut_yield->GetYaxis()->SetTitle("counts/mC");
    hTotal1ddp_nocut_yield->GetXaxis()->SetTitle(" Pdelta");
    hTotal1ddp_nocut_yield->GetYaxis()->CenterTitle();
    hTotal1ddp_nocut_yield->GetXaxis()->CenterTitle();

    
    c2->cd(2);gPad->SetGrid();
    hzhad_yield->Draw("e, p1");
    hzhad_yield->SetTitle(Form("Run: %d Yield vs z: P = %f",runs[r], mom[r]));
    hzhad_yield->SetMarkerStyle(20);
    hzhad_yield->SetLineWidth(2);
    hzhad_yield->Write();
    hzhad_yield->GetXaxis()->SetRangeUser(0.45, 0.9);
    hzhad_yield->GetYaxis()->SetTitle("counts/mC");
    hzhad_yield->GetXaxis()->SetTitle(" Z");
    hzhad_yield->GetYaxis()->CenterTitle();
    hzhad_yield->GetXaxis()->CenterTitle();

   

    
    c2->cd(3);gPad->SetGrid();
    hTotal1ddp_nocut_yield_corr->Draw("e, p1");
    hTotal1ddp_nocut_yield_corr->SetMarkerStyle(20);
    hTotal1ddp_nocut_yield_corr->SetLineWidth(2);
    hTotal1ddp_nocut_yield_corr->SetTitle(Form("Run: %d Yield_Eff_Corr vs Delta: P = %f",runs[r], mom[r]));
    hTotal1ddp_nocut_yield_corr->Write();
    hTotal1ddp_nocut_yield_corr->GetYaxis()->SetTitle("counts/mC");
    hTotal1ddp_nocut_yield_corr->GetXaxis()->SetTitle(" Pdelta");
    hTotal1ddp_nocut_yield_corr->GetYaxis()->CenterTitle();
    hTotal1ddp_nocut_yield_corr->GetXaxis()->CenterTitle();

   
    
    c2->cd(4);gPad->SetGrid();
    hzhad_yield_corr->Draw("e, p1");
    hzhad_yield_corr->SetTitle(Form("Run: %d Yield_Eff_Corr vs z: P = %f",runs[r], mom[r]));
    hzhad_yield_corr->SetMarkerStyle(20);
    hzhad_yield_corr->SetLineWidth(2);
    hzhad_yield_corr->Write();
    hzhad_yield_corr->GetXaxis()->SetRangeUser(0.45, 0.9);
    hzhad_yield_corr->GetYaxis()->SetTitle("counts/mC");
    hzhad_yield_corr->GetXaxis()->SetTitle(" Z");
    hzhad_yield_corr->GetYaxis()->CenterTitle();
    hzhad_yield_corr->GetXaxis()->CenterTitle();

    c2->SaveAs(Form("pdf_eff/plots_yield_%d.pdf",runs[r]));

    
  }
}












// TCanvas *c5 = new TCanvas("c5","c5", 1200, 800);
//    c5->Divide(1,1);
//    c5->cd(1);gPad->SetGrid();
//    pEff_nocut->Draw("colz");
//    pEff_nocut->SetTitle(Form("Run: %d Efficiency Map XY pEff: P = %f",runs[r], mom[r]));

//    c5->SaveAs(Form("pdf_eff/plot_eff_pEff_%d.pdf",runs[r]));






///////eff 2d
/*
  TH2F *eff_xy = new TH2F("eff_xy","eff_xy",nbin, loxy, hixy, nbin, loxy, hixy);
  eff_xy->Divide(hPass_2d_nocut,hTotal_2d_nocut);
   

   

  TCanvas *c1 = new TCanvas("c1","c1", 1200, 800);
  c1->Divide(1,1);
  c1->cd(1);gPad->SetGrid();
  eff_xy->Draw("colz");
  eff_xy->SetTitle(Form("Run: %d Efficiency Map XY: P = %f",runs[r], mom[r]));
  eff_xy->Write();
    
  c1->SaveAs(Form("pdf_eff/plot_eff_%d.pdf",runs[r]));



*/

