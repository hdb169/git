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
#define NRUNS 122

Int_t runs[NRUNS]=        {6020,6021,6022,6023,6026,6024,6025,6026,6029,6030,6031,6032,6027,6028,6033,6034,6035,6036,6043,6044,6045,6046,6039,6038,6040,6041,6042,6537,6538,6040,6041,6042,6537,
			   6538,6541,6539,6145,6146,6154,6155,6168,6142,6144,6163,6164,6500,6501,6502,6194,6195,6196,6192,6193,6198,6199,6197,6200,6201,6419,6420,6421,6422,6423,6525,6426,6429,
			   6430,6431,6432,6433,6427,6428,6309,6310,6311,6312,6313,6314,6387,6388,6397,6398,6386,6389,6518,6519,6520,6521,6535,6536,6533,6534,7635,7636,7637,7638,7639,7699,7702,
			   7703,7706,7707,7708,7709,7710,7711,7712,1163,7760,7762,7765,7766,7768,7769,7770,7771,7772,7808,7809,7811,7812};

#define nums  21
Int_t hgcerhist[nums]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};


double RI = 1.00137;

void plot_RF_posruns(){
  gStyle->SetPalette(1,0);//color in 2D 3D
  gStyle->SetOptStat(1000011);
  gStyle->SetOptFit(1);
  gStyle->SetTitleOffset(1.,"Y");
  gStyle->SetTitleOffset(.7,"X");
  gStyle->SetLabelSize(0.04,"XY");
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetPadLeftMargin(0.12);  
  //#include "gStyle.h"
   gStyle->SetOptStat(0);
  //gStyle->SetOptStat(1000011);//integral
  // gStyle->SetOptStat(1111111);//integral
  gStyle->SetOptFit(1);//integral
  // gStyle->SetErrorX(0); 

  ofstream txtfile_central("txtfile/hgcer_eff_central.txt",ios::app);
  ofstream txtfile_middle("txtfile/hgcer_eff_middle.txt",ios::app);
  ofstream txtfile_exterior("txtfile/hgcer_eff_exterior.txt",ios::app);

  
  gStyle->SetErrorX(0);

  for(Int_t r=0; r<NRUNS; r++){
  
    TString filename  = Form("/home/hdbhatt/ROOTfiles/short_hgc/coin_replay_production_%d_-1.root", runs[r]);//------7796
    //TString filename  = Form("/home/hdbhatt/ROOTfiles/short_hgc/pippip_all_2p9plus_%d.root", runs[r]);//------7796

    TFile *f = new TFile(filename, "READ");
    TFile * f11 = new TFile(Form("root_rfhist/rftime_hist_%d.root",runs[r]),"RECREATE");

    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

   
    TCutG *cutg = new TCutG("cutg",22);
    cutg->SetVarX("");
    cutg->SetVarY("");
    cutg->SetPoint(0, 4.8,2.4 );
    cutg->SetPoint(1, 2.4,2.4 );
    cutg->SetPoint(2, 2.4,3.1 ) ;
    cutg->SetPoint(3, 0,3.1);
    cutg->SetPoint(4, 0, 2.4);
    cutg->SetPoint(5, -0.8,2.4);
    cutg->SetPoint(6, -0.8,1.6);
    cutg->SetPoint(7, -3.2,1.6);
    cutg->SetPoint(8, -3.2,0.8 );
    cutg->SetPoint(9, -1.64,0.8);
    cutg->SetPoint(10, -1.64,0 );
    cutg->SetPoint(11, -0.8,0);
    cutg->SetPoint(12,  -0.8,-0.8) ;
    cutg->SetPoint(13, 0.8,-0.8);
    cutg->SetPoint(14, 0.8,-1.6 );
    cutg->SetPoint(15, 3.2,-1.6 );
    cutg->SetPoint(16, 3.2,0);
    cutg->SetPoint(17, 2.4,0);
    cutg->SetPoint(18, 2.4, 0.8 ); 
    cutg->SetPoint(19, 5.6,0.6 );
    cutg->SetPoint(20, 5.6,1.6 );
    cutg->SetPoint(21, 4.8,1.6);
    cutg->SetPoint(22, 4.8,2.4);
    
    TCutG *cutg1 = new TCutG("cutg1",8);
    cutg1->SetVarX("");
    cutg1->SetVarY("");
    cutg1->SetPoint(0,-10,-10 );
    cutg1->SetPoint(1, 0,-10 );
    cutg1->SetPoint(2, 10,-10 ) ;
    cutg1->SetPoint(3, 10,0);
    cutg1->SetPoint(4, 10,10);
    cutg1->SetPoint(5, 0,10);
    cutg1->SetPoint(6, -10,10);
    cutg1->SetPoint(7, -10,0);
    cutg1->SetPoint(8, -10,-10);

    TCutG *cutg2 = new TCutG("cutg2",8);
    cutg2->SetVarX("");
    cutg2->SetVarY("");
    cutg2->SetPoint(0,-20,-20 );
    cutg2->SetPoint(1, 0,-20 );
    cutg2->SetPoint(2, 20,-20 ) ;
    cutg2->SetPoint(3, 20,0);
    cutg2->SetPoint(4, 20,20);
    cutg2->SetPoint(5, 0,20);
    cutg2->SetPoint(6, -20,20);
    cutg2->SetPoint(7, -20,0);
    cutg2->SetPoint(8, -20,-20);
    
    //#include "binkin391_401.h"

#include "grcutfile0.h"
#include "bin7808.h"

    
    Double_t pionmass   = 0.1395701835;    //Gev/c^2 
    Double_t protonmass = 0.93827231;//GeV/c2
    Double_t dxbj, dQ2, dnu,domega,  dW2, dpmiss, demiss,  zhad, Mx2,Mx2a_acccut,Epi_acccut,zhad_acccut,Epi_pidcut,zhad_pidcut,Mx2_pidcut,Epi_cut,zhad_cut,Mx2_cut ;//d = data
    Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,mom,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,phodgoodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit, phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,rf_pion,hhodgoodscinhit,hhodbetanotrack,hdcntrack,hgtry,pgtry,phodbetanotrack,hcaletotnorm,gevnum,hxptar,hyptar,pxptar,pyptar ;

    double scaler_eventnum,bcm1charge,bcm1current,scaler1MHztime,scaler1MHztimecut,bcm1chargecut,s1xscaler,s1yscaler,s2xscaler,s2yscaler,ptrig1scaler,ptrig2scaler,ptrig3scaler,ptrig4scaler,ptrig6scaler,pedtmscaler,pelcleanscaler,pl1acceptscaler,edtmtdctime,edtmtdctimeraw,mult,ptrig1rate,rate,charge,hgc_xAtCer,hgc_yAtCer   ;
    
    Double_t Epi_dcut0, z_dcut0, Epi_dcut1, z_dcut1, Epi_dcut2, z_dcut2, Epi_dcut3, z_dcut3, Epi_dcut1plus2, z_dcut1plus2; 
    Double_t Epi_acc0, z_acc0, Epi_acc1, z_acc1, Epi_acc2, z_acc2, Epi_acc3, z_acc3, Epi_acc1plus2, z_acc1plus2 ,rf_pion1 ;

    Bool_t  accR_cut, accL_cut,shms_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, mod4_pioncut, mod4_notpioncut, pcal_cut, hcal_cut, ctime_cut, hms_cut, pcal_cut_tight, cuttype1, cuttype1acc, cuttype2, cuttype2acc, cuttype1plus2, cuttype1plus2acc , hgcer_cut_loose,  paero_cut_loose,  cuttype0, cuttype0acc, common_cut, cuttype3, cuttype3acc, accsub_cut, acc_cut, shms_tr_did_cut, shms_tr_should_cut, hms_tr_did_cut, hms_tr_should_cut,basic_cut,basic_cal_aero, hms_cal_should_cut, hms_cal_did_cut, shms_cal_should_cut, shms_cal_did_cut, cal_eff_hms_shms_base_cut,cointime_cut ;

    Double_t Epi_cut_acc, zhad_cut_acc, Mx2_cut_acc;
    Double_t ctmin = 2;//2.0;//1.5
    Double_t ctmax = 2;//2.0;//1.5
    Double_t rfmin = 0.5;//0.5;//0.5;
    Double_t rfmax = 1.5;//1.5;//1.5;
    Double_t eprmin = 0.0;
    Double_t eprmax = 0.2;//0.15;
    Double_t pcaletotmin = 0.0;
    Double_t pcaletotmax = 0.7;//0.75;
    Double_t hcaletotmin = 0.75;//0.75;
    Double_t offsetrf;
    double nbin  = 70;//5;
    double loxy = -70;//-30;
    double hixy  = 40;//30;
    double lodelta = -10;
    double hidelta = 20;
    double npelo = 0;
    double npehi = 30;
    double binP   = 20;
    double binloP = 2.9;
    double binhiP = 5.5;
    double maxct = 47.5;
    double minct = 42.5;
    TH1F *hmom = new TH1F("hmom","", 17, 2.8, 7.0);
    TH1F *hmom_all_regions = new TH1F("hmom_all_regions (hole removed)","Mom Distn (all regions); Mom (GeV); Counts", 17, 2.8, 7.0);
    TH1F *hmom_circle1 = new TH1F("hmom_circle1","Mom Distn (inner circle); Mom (GeV); Counts", 17, 2.8, 7.0);
    TH1F *hmom_circle2 = new TH1F("hmom_circle2","Mom Distn (middle circle); Mom (GeV); Counts", 17, 2.8, 7.0);
    TH1F *hmom_circle3 = new TH1F("hmom_circle3","Mom Distn (exterior); Mom (GeV); Counts", 17, 2.8, 7.0);

    TH1F *hctimecut = new TH1F("hctimecut","", 100, 30, 55);
    TProfile2D * xy_vs_npe_grcut = new TProfile2D("xy_vs_npe_grcut","X vs Y  vs NPE (hole present, No Cer Cut);P.hgcer.yAtCer;P.hgcer.xAtCer;NPESUM", 300, -50, 50, 300, -50, 50, 0, 35);
    TProfile2D * xy_vs_npe_grcut_hole_removed = new TProfile2D("xy_vs_npe_grcut_hole_removed","X vs Y  vs NPE (hole removed,  Cer Cut);P.hgcer.yAtCer;P.hgcer.xAtCer;NPESUM", 300, -50, 50, 300, -50, 50, 0, 35);

    TH2D * XvsY_hgc0p5 = new TH2D("XvsY_hgc0p5","X vs Y At Hgcer;P.hgcer.yAtCer;P.hgcer.xAtCer", 300, -50, 50, 300, -50, 50);
    TH2D * XvsY_hgc0p5_hole = new TH2D("XvsY_hgc0p5_hole","X vs Y At Hgcer (Remove Hole + stripe);P.hgcer.yAtCer;P.hgcer.xAtCer", 300, -50, 50, 300, -50, 50);
    TH2D * XvsY_hgc0p5_all_regions = new TH2D("XvsY_hgc0p5_all_regions","X vs Y At Hgcer (All But Remove Hole + stripe);P.hgcer.yAtCer;P.hgcer.xAtCer", 300, -50, 50, 300, -50, 50);
    TH2D * XvsY_hgc0p5_cir1 = new TH2D("XvsY_hgc0p5_cir1","X vs Y At Hgcer (circle 1) ;P.hgcer.yAtCer;P.hgcer.xAtCer", 300, -50, 50, 300, -50, 50);
    TH2D * XvsY_hgc0p5_cir2 = new TH2D("XvsY_hgc0p5_cir2","X vs Y At Hgcer (circle 2) ;P.hgcer.yAtCer;P.hgcer.xAtCer", 300, -50, 50, 300, -50, 50);
    TH2D * XvsY_hgc0p5_exterior = new TH2D("XvsY_hgc0p5_cir3","X vs Y At Hgcer (exterior) ;P.hgcer.yAtCer;P.hgcer.xAtCer", 300, -50, 50, 300, -50, 50);



   
#include "offsetrf.h"
    TTree * tt = (TTree *)f->Get("T");
    TTree * ss = (TTree *)f->Get("TSP");
#include "define_histogram.h"

    //----------------------------------------Fill Hist
    //#include "branch_original.h"
#include "branch_rf.h"

    Long64_t nentriesD = tt->GetEntries();
   
   
#include "scaler_branch.h"
    Long64_t scal_entries = ss->GetEntries();
#include "scaler_analysis.h"

    Int_t nscaler_reads_acc=0;
   
   
		
    Bool_t hgcer_cut1 ,paero_cut1 , mod4_pioncut1,  mod4_notpioncut1,   pcal_cut1, hcal_cut1,  hms_cut1,   shms_cut1, shms_cut2, pid_cut1, ctime_cut1, acc_cut1, acc_cut1hardcut,acc_cut_norf,central_hole,right_or_left_of_hole,remove_region,circle1, circle22, circle2, circle3, pid_cutacc, hms_cutacc ;

    Bool_t  pid_cutacc_acc,  central_hole_acc,  right_or_left_of_hole_acc,remove_region_acc;
    Int_t nscaler_reads=0;

    for (int kk=0; kk<nentriesD;  kk++){//-----------------------------------------------------Main Evt Loop
      tt->GetEntry(kk);
      pid_cutacc_acc  =  hdelta> -8 && hdelta < 8  && hhodstarttime ==1 && hdipole==1  &&hcernpe>1.0 && hcaletottrack>0.75 && hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04   && pdelta >-10 && pdelta < 20   && phodstarttime == 1  && eventtype > 3 && pcaletottrack<0.7 && paero>4 && pdipole ==1 && pxptar>-0.05&&pxptar<0.05&&pyptar>-0.05&&pyptar<0.05;//hms_cutacc && shms_cut1

      central_hole_acc = (pow(hgc_yAtCer-1.33, 2) +  pow(hgc_xAtCer-0.83, 2) >= pow(6.0, 2));//radius = 2.54->3.54
      right_or_left_of_hole_acc = ((hgc_yAtCer > 1.33 && (hgc_xAtCer < 0. ||  hgc_xAtCer > 3.0) ) ||  (hgc_yAtCer < 1.33 && (hgc_xAtCer < 0.||  hgc_xAtCer > 3)));

      remove_region_acc = central_hole_acc && right_or_left_of_hole_acc;//ok
      if(pid_cutacc_acc &&remove_region_acc){
	hctime->Fill(ctime);
      }
    
    }


    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
   
      
    for (int kk=0; kk<nentriesD;  kk++){//-----------------------------------------------------Main Evt Loop
      tt->GetEntry(kk);
    
      rf_pion1 = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
      // rf_pion1 = (fmod(-prftdctime+phodfphitstime+ 400.10 ,4.008));
      //mod4_pioncut1 = ((rf_pion1 > 2.5 && rf_pion1 < 3.5));

      mod4_pioncut1 = ((rf_pion1 > 0.5 && rf_pion1 < 1.5)||(rf_pion1 > 2.5 && rf_pion1 < 3.5));
      mod4_notpioncut1 =!mod4_pioncut;
      pcal_cut1 =  pcaletottrack < pcaletotmax;
      hcal_cut1 =  hcaletottrack > hcaletotmin;

      hms_cut1  =  hdelta> -8 && hdelta < 8  && hhodstarttime ==1 && hdipole==1  &&hcernpe>1.0 && hcaletottrack>0.75 && hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04 && ctime>(max_value-ctmin)&&ctime<(max_value+ctmax);
      //for pim
      hms_cutacc  =  hdelta> -8 && hdelta < 8  && hhodstarttime ==1 && hdipole==1  &&hcernpe>1.0 && hcaletottrack>0.75 && hxptar>-0.08&&hxptar<0.08&&hyptar>-0.04&&hyptar<0.04;
      shms_cut1 =  pdelta >-10 && pdelta < 20   && phodstarttime == 1  && eventtype > 3 && pcaletottrack<0.7 && paero>4 && pdipole ==1 && pxptar>-0.05&&pxptar<0.05&&pyptar>-0.05&&pyptar<0.05;
      pid_cutacc  = hms_cutacc && shms_cut1 ;//&& mod4_pioncut1;//no HGC but RFtime
      pid_cut1  = hms_cut1 && shms_cut1;// && mod4_pioncut1;//no HGC but RFtime

      central_hole = (pow(hgc_yAtCer-1.33, 2) +  pow(hgc_xAtCer-0.83, 2) >= pow(6.0, 2));//radius = 2.54->3.54
      // right_or_left_of_hole = ((hgc_yAtCer > 1.33 && (hgc_xAtCer < 0.47 ||  hgc_xAtCer > 2.34) ) ||  (hgc_yAtCer < 1.33 && (hgc_xAtCer < 0.26 ||  hgc_xAtCer > 1.76)));
      right_or_left_of_hole = ((hgc_yAtCer > 1.33 && (hgc_xAtCer < 0. ||  hgc_xAtCer > 3.0) ) ||  (hgc_yAtCer < 1.33 && (hgc_xAtCer < 0.||  hgc_xAtCer > 3)));
      remove_region = central_hole && right_or_left_of_hole;//ok

      circle1 = (pow(hgc_yAtCer, 2) +  pow(hgc_xAtCer, 2) <= pow(14.5, 2)) && remove_region ;//ok//2.54 to 10
      circle2 = (pow(hgc_yAtCer, 2) +  pow(hgc_xAtCer, 2) <= pow(24, 2)) && (pow(hgc_yAtCer, 2) +  pow(hgc_xAtCer, 2) > pow(14.5, 2)) && remove_region ;//ok 10 to 20
      circle3 = (!circle1 && !circle2) && remove_region;//20+
      //acc cut here
      accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
      accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
      acc_cut         =   (accR_cut || accL_cut);
 
      //for acc sub///////////////////////////////////////////////////////////////////////
     
      if(pid_cutacc && remove_region && acc_cut && hgcer > 0.5){

	  hRF_acc->Fill(rf_pion1);

	      }
      
      //acc sub done/////////////////////////////////////////////////////////////////////
      if(pid_cut1&&hgcer>0.5){
	  hRF_coin->Fill(rf_pion1);
      }
    
    }//entries  
  
   
      TH1F *   hRF_acc_1peak = (TH1F*) hRF_acc->Clone();
      hRF_acc_1peak->Scale((ctmin+ctmax)/16.0);

      
      hRF_clean_pos->Add(hRF_coin,hRF_acc_1peak,1,-1);

      
      hRF_clean_pos->Sumw2();
      hRF_clean_pos->Write();

      TCanvas *RF = new TCanvas("RF","RF", 1200, 800);
      RF->Divide(1,1);
      RF->cd(1);gPad->SetGrid();
      hRF_coin->Draw("hist");
      hRF_clean_pos->Draw("hist sames");
      hRF_acc->Draw("hist sames");
      hRF_coin->SetLineWidth(2);
      hRF_acc->SetLineWidth(2);
      hRF_clean_pos->SetLineWidth(2);
      hRF_coin->SetLineColor(kBlack);
      hRF_acc->SetLineColor(kRed);
      hRF_clean_pos->SetLineColor(kBlue);
      hRF_coin->GetXaxis()->SetAxisColor(17);
      hRF_coin->GetYaxis()->SetAxisColor(17);
      hRF_coin->SetTitle(Form("RF Time %d",runs[r]));
      RF->SaveAs(Form("pdf_rf/rf_hists_%d.pdf",runs[r]));
    
  }
}
