#include "header.h"
void pos_3p2dummy_7772(){
#include "gStyle.h"
  TChain *tt = new TChain("T");
  
  tt->Add("ROOTfiles/pos_3p2dummy_7772.root");

  TFile *ff = new TFile("root_yield/yield_pos_3p2dummy_7772.root","RECREATE");   
  Long64_t nentriesD = tt->GetEntries();
  cout<<"data entries = "<<nentriesD<<"  "<<endl;

#include "binz.h"


  Double_t pbeta,hbeta,pdelta,hdelta,hcaletottrack,pcaletottrack,pcalepr,hcalepr,paero,hcernpe,hgcer,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,goodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit;
  Double_t phodrftdcmult,phodrftdctime,prftdcmult,prftdctime , hhodrftdcmult,hhodrftdctime,hrftdcmult,hrftdctime,phodfphitstime,hhodfphitstime,rfminusfp,eventtype,rf_pion ;

  TH1D *cointime = new TH1D("cointime", "cointime (ns)", binct, loct, hict);
  TH1D *cointime_pi = new TH1D("cointime_pi", "cointime_pi (ns)", binct, loct, hict);
  TH1D *cointime_notpi = new TH1D("cointime_nopi", "cointime_nopi (ns)", binct, loct, hict);
  TH1D *ctime_hist = new TH1D("ctime_hist", "ctime_hist (ns)", binaccct, loaccct, hiaccct);
  TH1D *ctime_hist_acc = new TH1D("ctime_hist_acc", "ctime_hist_acc (ns)", binaccct, loaccct, hiaccct);
  TH1D *h_dataz_acc= new TH1D("h_dataz_acc", "h_dataz_acc", binz, loz, hiz);//acc
  TH1D *cointime_narrow = new TH1D("cointime_narrow", "cointime_narrow (ns)", binct, loct, hict);

  
  //added1.2
  TH1D * cointime_notpi_in = new TH1D("cointime_nopi_in", "cointime_nopi_in (ns)", binct, loct, hict);
  TH2D * mod4_red_inbeta = new TH2D(" mod4_red_in"," mod4_red_in",binrf, binrflo, binrfhi, 100, 0.8, 1.2);
  TH2D * mod4_red_inaero = new TH2D(" mod4_red_inaero"," mod4_red_inaero",binrf, binrflo, binrfhi, 100, 0.00001, 30);

  //added in

  TH1D *beta_did_hms_shms_cuts = new TH1D("beta_did_hms_shms_cuts", "beta_did_hms_shms_cuts", 50, 0.7, 1.3);
  TH1D *beta_should_hms_shms_cuts = new TH1D("beta_should_hms_shms_cuts", "beta_should_hms_shms_cuts", 50, 0.7, 1.3);


  TH1D *prf_tdctime = new TH1D("prf_tdctime", "prf_tdctime", bintdctime, lotdctime, hitdctime);//T.coin.pRF_tdcTime 
  TH1D *phodfp_hitstime = new TH1D("phodfp_hitstime", "phodfp_hitstime", binhitstime, lohitstime, hihitstime);//P.hod.fpHitsTime

  TH1D *rf_minus_fp = new TH1D("rf_minus_fp ", "rf_minus_fp ",bindiff, lodiff, hidiff);

  TH1D *rf_minus_phodfp_mod4 = new TH1D("rf_minus_phodfp_mod4 ", "rf_minus_phodfp_mod4 ", binrf, binrflo, binrfhi);//T.coin.pRF_tdcTime-P.hod.fpHitsTime
  TH2D *beta_vs_rf = new TH2D("beta_vs_rf","beta_vs_rf",binrf, binrflo, binrfhi, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_notpion = new TH2D("beta_vs_rf_notpion","beta_vs_rf_notpion",binrf, binrflo, binrfhi, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_calctaero = new TH2D("beta_vs_rf_calctaero","beta_vs_rf_calctaero",binrf, binrflo, binrfhi, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_allpid_rfcut_did = new TH2D("beta_vs_rf_allpid_rfcut_did","beta_vs_rf_allpid_rfcut_did",binrf, binrflo, binrfhi, 100, 0.8, 1.2);
  TH2D *beta_vs_rf_allpid_should = new TH2D("beta_vs_rf_allpid_should","beta_vs_rf_allpid_should",binrf, binrflo, binrfhi, 100, 0.8, 1.2);
  TH2D *shower_vs_preshower = new TH2D("shower_vs_preshower","shower_vs_preshower",100, 0.0001,0.8, 100, 0.0001, 1.8);
  TH2D *shower_vs_preshower_rf = new TH2D("shower_vs_preshower_rf","shower_vs_preshower_rf",100, 0.0001,0.8, 100, 0.0001, 1.8);

  TH2D *aero_vs_rf = new TH2D("aero_vs_rf","aero_vs_rf",binrf, binrflo, binrfhi, 100, 0.00001, 30);
  TH2D *aero_vs_rf_ctcut = new TH2D("aero_vs_rf_ctcut","aero_vs_rf_ctcut",binrf, binrflo, binrfhi, 100, 0.00001, 30);

  TH1D *pcal = new TH1D("pcal", "pcal", bincal, local, hical);

  TH1D *pcal_epr = new TH1D("pcal_epr", "pcal_epr", bincal, local, hical);
  TH1D *pcal_epr_rf = new TH1D("pcal_epr_rf", "pcal_epr_rf", bincalepr, localepr, hicalepr);


  TH1D *pcal_etot = new TH1D("pcal_etot", "pcal_etot", bincal, local, hical);
  TH1D *pcal_etot_rf = new TH1D("pcal_etot_rf", "pcal_etot_rf", bincal, local, hical);
  TH1D *pcal_etot_notpion = new TH1D("pcal_etot_notpion", "pcal_etot_notpion", bincal, local, hical);
  TH1F *hTotal = new TH1F("hTotal", " ", 30, -10, 20); //delta                        
  TH1F *hPass = new TH1F("hpass", " ", 30, -10, 20); //delta                       
  TH2F *h = new TH2F("h","RF Efficiency (pion) vs SHMS Delta",100,-10, 20 ,100, 0, 1); 
  //hgcer
  TH1F *hgchist = new TH1F("hgchist", "hgchist",binhgc, binlohgc, binhihgc);
  TH2F *hgc_vs_rf = new TH2F("hgc_vs_rf","hgc_vs_rf", binrf, binrflo, binrfhi, binhgc, binlohgc, binhihgc );

  TH1F *hgchistcalct = new TH1F("hgchistcalct", "hgchistcalct",binhgc, binlohgc, binhihgc);
  TH2F *hgc_vs_rfcalct = new TH2F("hgc_vs_rfcalct","hgc_vs_rfcalct", binrf, binrflo, binrfhi, binhgc, binlohgc, binhihgc);


  TH1F *hgchistpion = new TH1F("hgchistpion", "hgchistpion",binhgc, binlohgc, binhihgc);
  TH2F *hgc_vs_rfpion = new TH2F("hgc_vs_rfpion","hgc_vs_rfpion", binrf, binrflo, binrfhi, binhgc, binlohgc, binhihgc);
  //accidental hists cut0
  TH1D * h_dataz_cut0copy0 = new TH1D ("h_dataz_cut0copy0", "h_dataz_cut0_copy0", binz, loz, hiz);
  TH1D * h_dataz_acc_only0 = new TH1D ("h_dataz_acc_copy0", "h_dataz_acc_copy0", binz, loz, hiz);
  TH1D * h_dataz_cut0 = new TH1D ("h_dataz_cut0", "h_dataz_cut0", binz, loz, hiz);
  TH1D * h_dataz_acc0= new TH1D("h_dataz_acc0", "h_dataz_acc0", binz, loz, hiz);//acc
  //////// cut1
  TH1D * h_dataz_acc1= new TH1D("h_dataz_acc1", "h_dataz_acc1", binz, loz, hiz);//acc
  TH1D * h_dataz_cut1copy1 = new TH1D ("h_dataz_cut1copy1", "h_dataz_cut1_copy1", binz, loz, hiz);
  TH1D * h_dataz_acc_only1 = new TH1D ("h_dataz_acc_copy1", "h_dataz_acc_copy1", binz, loz, hiz);
  TH1D * h_dataz_cut1 = new TH1D ("h_dataz_cut1", "h_dataz_cut1", binz, loz, hiz);
  //cut2
  TH1D * h_dataz_acc2= new TH1D("h_dataz_acc2", "h_dataz_acc2", binz, loz, hiz);//acc
  TH1D * h_dataz_cut2copy2 = new TH1D ("h_dataz_cut2copy2", "h_dataz_cut2_copy2", binz, loz, hiz);
  TH1D * h_dataz_acc_only2 = new TH1D ("h_dataz_acc_copy2", "h_dataz_acc_copy2", binz, loz, hiz);
  TH1D * h_dataz_cut2 = new TH1D ("h_dataz_cut2", "h_dataz_cut2", binz, loz, hiz);
  //cut3
  TH1D * h_dataz_acc3= new TH1D("h_dataz_acc3", "h_dataz_acc3", binz, loz, hiz);//acc
  TH1D * h_dataz_cut3copy3 = new TH1D ("h_dataz_cut3copy3", "h_dataz_cut3_copy3", binz, loz, hiz);
  TH1D * h_dataz_acc_only3 = new TH1D ("h_dataz_acc_copy3", "h_dataz_acc_copy3", binz, loz, hiz);
  TH1D * h_dataz_cut3 = new TH1D ("h_dataz_cut3", "h_dataz_cut3", binz, loz, hiz);
  
  //cut1plus2
  TH1D * h_dataz_acc1plus2= new TH1D("h_dataz_acc1plus2", "h_dataz_acc1plus2", binz, loz, hiz);//acc
  TH1D * h_dataz_cut1plus2copy1plus2 = new TH1D ("h_dataz_cut1plus2copy1plus2", "h_dataz_cut1plus2_copy1plus2", binz, loz, hiz);
  TH1D * h_dataz_acc_only1plus2 = new TH1D ("h_dataz_acc_copy1plus2", "h_dataz_acc_copy1plus2", binz, loz, hiz);
  TH1D * h_dataz_cut1plus2 = new TH1D ("h_dataz_cut1plus2", "h_dataz_cut1plus2", binz, loz, hiz);
  

  
  //yield
  TH1D *h_dataz_0 = new TH1D("h_dataz_0","h_dataz_0", binz, loz, hiz);        
  TH1D *h_dataz_1 = new TH1D("h_dataz_1","h_dataz_1", binz, loz, hiz);        
  TH1D *h_dataz_2 = new TH1D("h_dataz_2","h_dataz_2", binz, loz, hiz);
  TH1D *h_dataz_3 = new TH1D("h_dataz_3","h_dataz_3", binz, loz, hiz);        
  TH1D *h_dataz_1plus2 = new TH1D("h_dataz_1plus2","h_dataz_1plus2", binz, loz, hiz);        

  Double_t Epi_dcut0, z_dcut0, Epi_dcut1, z_dcut1, Epi_dcut2, z_dcut2, Epi_dcut3, z_dcut3, Epi_dcut1plus2, z_dcut1plus2; 
  Double_t Epi_acc0, z_acc0, Epi_acc1, z_acc1, Epi_acc2, z_acc2, Epi_acc3, z_acc3, Epi_acc1plus2, z_acc1plus2;

#include "branch.h" 

  Bool_t  accidental_cut, acc_cut_trial, accR_cut, accL_cut,shms_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc,hgcer_cut, paero_cut, mod4_pioncut, mod4_notpioncut, pcal_cut, ctime_cut, hms_cut, pcal_cut_tight, cuttype1, cuttype1acc, cuttype2, cuttype2acc, cuttype1plus2, cuttype1plus2acc , hgcer_cut_loose,  paero_cut_loose,  mod4_pioncut_tight, mod4_notpioncut_tight, cuttype0, cuttype0acc, common_cut, cuttype3, cuttype3acc, accsub_cut, acc_cut;


  ////////////////To find ctime peak////////////////

  for (int ac=0; ac<nentriesD;  ac++)//original
    //for (int ac=0; ac<50000;  ac++)
   
    {

      tt->GetEntry(ac);



      accsub_cut = paero>4.0 && pcalepr< 0.2 && pcalepr > 0.0 && pcaletottrack < 0.8 && pcaletottrack> 0.0 && hcaletottrack > 0.8 && hcaletottrack < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.8 && pbeta < 1.2 &&hbeta > 0.8 &&hbeta < 1.2  && hhodstarttime ==1 && phodstarttime == 1 && hdipole==1 && pdipole ==1; 
  
      if(accsub_cut)
	{  

	  ctime_hist->Fill(ctime);
	 
	 
	}
    }
  cout<<"Step 1: calulating the max peak value of the ctime dist"<<endl;

  Int_t bin_max = ctime_hist->GetMaximumBin();
  Double_t max_value = ctime_hist->GetBinCenter(bin_max);
  cout<<"ctime peak is at = "<< max_value <<endl;

  cout<<"Step 2: Now calculating accidental backgrounds"<<endl;

 
  
  /////////////////////////////////////////////////////////PART 1 find Coincidence time peak done/////////////////////////////////
  for (int kk=0; kk<nentriesD;  kk++)//original
    //  for (int kk=0; kk<10000;  kk++)
   
    {

      tt->GetEntry(kk);


      accR_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
      accL_cut        =   ctime > (max_value + 10 ) && ctime < (max_value + 18);
      accidental_cut = (accR_cut || accL_cut);
								   
      hms_cut =  hdelta> -10 && hdelta < 10 && hbeta >0.8 && hbeta <1.2 && hhodstarttime ==1 && hdipole==1  && hcaletottrack > 0.8 && hcaletottrack <1.2 && hcernpe>1.5 ;
      shms_cut =  pdelta >-10 && pdelta < 20   && pbeta >0.8 && pbeta<1.2 && phodstarttime == 1 && pdipole ==1 && eventtype==4;
      common_cut = hms_cut && shms_cut;
      hgcer_cut = hgcer>1.5;
      paero_cut = paero>5.0;      
      rf_pion = (fmod(-prftdctime+phodfphitstime+1000+1.0,4.008));
      mod4_pioncut = rf_pion >0.3 && rf_pion < 1.1;
      mod4_pioncut_tight = rf_pion > 0.4 && rf_pion < 1.05;
      mod4_notpioncut =!mod4_pioncut;
      mod4_notpioncut_tight =!mod4_pioncut_tight;
      pcal_cut = pcaletottrack> 0.0 && pcaletottrack < 0.8 && pcalepr > 0.00001 && pcalepr<0.2 ;
      pcal_cut_tight = pcaletottrack> 0.0 && pcaletottrack < 0.6 && pcalepr > 0.00001 && pcalepr<0.2 ;
      //////////// ctime_cut = ctime>42.2 && ctime<43.8;
      // ctime_cut = ctime > max_value - 0.8 && ctime < max_value + 0.8;




      ctime_cut = ctime > max_value - 0.8 && ctime < max_value + 0.8;

      hgcer_cut_loose = hgcer >0.5;
      paero_cut_loose = paero >4.0;
      
      cuttype0 = common_cut && ctime_cut;
      cuttype0acc = common_cut;
      
      cuttype1 = cuttype0 && hgcer_cut && paero_cut  &&  pcal_cut_tight;
      cuttype1acc = common_cut &&hgcer_cut && paero_cut && pcal_cut_tight;
      
      cuttype2 = cuttype0 && mod4_pioncut && pcal_cut_tight;
      cuttype2acc = common_cut && mod4_pioncut && pcal_cut_tight;
      
      cuttype3 = cuttype0 && mod4_pioncut && paero_cut && pcal_cut_tight;
      cuttype3acc = common_cut && mod4_pioncut && paero_cut && pcal_cut_tight;
      
      cuttype1plus2 = cuttype1 && cuttype2;
      cuttype1plus2acc = cuttype1acc && cuttype2acc;

      acc_cut = accidental_cut;
      //////////////////////////////////////////////////////////									       
      //for yield only begin
      //cut0
      
      if (cuttype0){
	Epi_dcut0 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_dcut0= Epi_dcut0/pkinomega ;
	h_dataz_0->Fill(z_dcut0);
      }

      if(acc_cut && cuttype0acc){
	Epi_acc0 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc0 = Epi_acc0/pkinomega;
	h_dataz_acc0->Fill(z_acc0);
      }
    
      //cut1
      if (cuttype1){
	Epi_dcut1 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_dcut1 = Epi_dcut1/pkinomega ;
	h_dataz_1->Fill(z_dcut1);
      }
      if(acc_cut && cuttype1acc){
	Epi_acc1 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc1 = Epi_acc1/pkinomega;
	h_dataz_acc1->Fill(z_acc1);

      }

      //cut2
      if (cuttype2){
	
	Epi_dcut2 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_dcut2 = Epi_dcut2/pkinomega;
	h_dataz_2->Fill(z_dcut2);
      }
      if(acc_cut && cuttype2acc){
	Epi_acc2 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc2 = Epi_acc2/pkinomega;
	h_dataz_acc2->Fill(z_acc2);
      }

      //cut3
      if (cuttype3){
	Epi_dcut3 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_dcut3 = Epi_dcut3/pkinomega;
	h_dataz_3->Fill(z_dcut3);
      }
      if(acc_cut & cuttype3acc){
	Epi_acc3 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc3 = Epi_acc3/pkinomega;
	h_dataz_acc3->Fill(z_acc3);
      }
	
      //cut1plus2
      if (cuttype1plus2){
	
	Epi_dcut1plus2 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_dcut1plus2 = Epi_dcut1plus2/pkinomega;
	h_dataz_1plus2->Fill(z_dcut1plus2);
      }

      if(acc_cut & cuttype1plus2acc){
	Epi_acc1plus2 = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc1plus2 = Epi_acc1plus2/pkinomega;
	h_dataz_acc1plus2->Fill(z_acc1plus2);
      }
      //for cointime
      if(common_cut && ctime_cut){
	cointime_narrow->Fill(ctime);
      }
      
      ///////////////////////////////////////////////////////////////////////////////
      
      //for yield only done
      
      
      if(shms_cut)
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
	  hgchist->Fill(hgcer);//beta and delta
	  hgc_vs_rf->Fill(rf_pion,hgcer);//beta and delta

	  
	  if(mod4_pioncut && pcal_cut && paero_cut){
	    // if( pcal_cut && paero_cut){

	    cointime_pi->Fill(ctime);//green

	  }
	  if(mod4_notpioncut && pcal_cut){
	    cointime_notpi->Fill(ctime);//red
	    if(ctime_cut){ //added to see small red peak in ctime
	      cointime_notpi_in->Fill(ctime);
	      mod4_red_inbeta->Fill(rf_pion,pbeta);
	      mod4_red_inaero->Fill(rf_pion,paero);

	    }
	  }


	  if(pcal_cut && ctime_cut && paero_cut){
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
	      hgchistpion->Fill(hgcer);//beta and delta
	      hgc_vs_rfpion->Fill(rf_pion,hgcer);//beta and delta

	    }
	  }
	  if(pcal_cut && ctime_cut && paero_cut && mod4_notpioncut){//not pion
	    pcal_etot_notpion->Fill(pcaletottrack);
	    beta_vs_rf_notpion->Fill(rf_pion,pbeta);
	    
	  }

	  if(ctime_cut && pcal_cut){
	    aero_vs_rf_ctcut->Fill(rf_pion,paero);
	    hgchistcalct->Fill(hgcer);//beta and delta
	    hgc_vs_rfcalct->Fill(rf_pion,hgcer);//beta and delta
	    
	    if(paero_cut){
	      beta_vs_rf_calctaero->Fill(rf_pion,pbeta);
	    }
	  }
	}
    }
  //Actual Coin Time Plot
  
  TCanvas *coin = new TCanvas("coin", "coin", 1600,1200);
  coin->Divide(1,1);
  coin->cd(1);
  cointime->Draw("");
  cointime->SetLineWidth(2);
  cointime->GetXaxis()->SetTitle("Cointime [ns]");
  cointime->GetYaxis()->SetTitle("Counts");
  cointime->GetXaxis()->CenterTitle();
  cointime->GetYaxis()->CenterTitle();
  cointime_pi->Draw("same");
  cointime_pi->SetLineWidth(2);
  cointime_pi->SetLineColor(kBlack);
  cointime_notpi->Draw("Same");
  cointime_notpi->SetLineWidth(2);
  cointime_notpi->SetLineColor(kRed);
  cointime_narrow->Draw("same");
  cointime_narrow->SetLineWidth(4);
  cointime_narrow->SetLineColor(kGreen);

  
  TLegend* leg0 = new TLegend(0.6,0.6,0.9,0.9);
  leg0->AddEntry(cointime,"#beta, #delta cuts only","L");
  leg0->AddEntry(cointime_pi," #beta, #delta, CAL, AERO, RF cuts for pion (All Cuts)","L");
  leg0->AddEntry(cointime_notpi,"#beta, #delta, CAL, NOT RF only ( NOT PION) ","L");
  leg0->AddEntry(cointime_narrow," cointime_narrow For Accidental Sub","L");

  leg0->Draw("Same");
  gPad->Update();

  
  //////////////////ACTUAL  ACCIDENTAL SUB PLOTS HERE????????????
  //cut0
  h_dataz_cut0copy0 = (TH1D *) h_dataz_0->Clone();//before acc sub
  h_dataz_acc_only0 = (TH1D *) h_dataz_acc0->Clone();
  h_dataz_acc_only0->Scale(1.6/16.0);//only acc in 1 peak
  h_dataz_cut0->Add(h_dataz_cut0copy0, h_dataz_acc_only0, 1.0, -1.0);	
  //cut1
  h_dataz_cut1copy1 = (TH1D *) h_dataz_1->Clone();//before acc sub
  h_dataz_acc_only1 = (TH1D *) h_dataz_acc1->Clone();
  h_dataz_acc_only1->Scale(1.6/16.0);//only acc in 1 peak
  h_dataz_cut1->Add(h_dataz_cut1copy1, h_dataz_acc_only1, 1.0, -1.0);	

  //cut2
  h_dataz_cut2copy2 = (TH1D *) h_dataz_2->Clone();//before acc sub
  h_dataz_acc_only2 = (TH1D *) h_dataz_acc2->Clone();
  h_dataz_acc_only2->Scale(1.6/16.0);//only acc in 1 peak
  h_dataz_cut2->Add(h_dataz_cut2copy2, h_dataz_acc_only2, 1.0, -1.0);	

  //cut3
  h_dataz_cut3copy3 = (TH1D *) h_dataz_3->Clone();//before acc sub
  h_dataz_acc_only3 = (TH1D *) h_dataz_acc3->Clone();
  h_dataz_acc_only3 ->Scale(1.6/16.0);//only acc in 1 peak
  h_dataz_cut3 ->Add(h_dataz_cut3copy3, h_dataz_acc_only3, 1.0, -1.0);	

  //cut1plus2

  h_dataz_cut1plus2copy1plus2 = (TH1D *) h_dataz_1plus2->Clone();//before acc sub
  h_dataz_acc_only1plus2 = (TH1D *) h_dataz_acc1plus2->Clone();
  h_dataz_acc_only1plus2->Scale(1.6/16.0);//only acc in 1 peak
 h_dataz_cut1plus2 ->Add(h_dataz_cut1plus2copy1plus2, h_dataz_acc_only1plus2, 1.0, -1.0);	

  //plot 

  TCanvas * c0 = new TCanvas("c0", "c0", 1600, 1200);

  c0->Divide(2,2);
  c0->cd(1);
  h_dataz_cut0->GetYaxis()->SetRangeUser(-1000,4500);
  h_dataz_cut0->Draw("e,p1");
  h_dataz_cut0->SetLineColor(kGreen);
  h_dataz_cut0->SetMarkerStyle(21);
  h_dataz_cut0->SetMarkerColor(kGreen);
  h_dataz_cut0->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_cut0->GetYaxis()->SetTitle("Counts");
  h_dataz_cut0->SetTitle("Z_hadron for Cut0");
  h_dataz_cut0->GetYaxis()->SetTitle("Counts");

  c0->cd(2);
  h_dataz_0->Draw("e,p1");
  h_dataz_0->SetLineColor(kBlue);
  h_dataz_0->SetMarkerColor(kBlue);
  h_dataz_0->SetMarkerStyle(22);
  h_dataz_0->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_0->GetYaxis()->SetTitle("Counts");

  
  c0->cd(3);
  h_dataz_acc_only0->Draw("e,p1");
  h_dataz_acc_only0->SetLineColor(kRed);
  h_dataz_acc_only0->SetMarkerColor(kRed);
  h_dataz_acc_only0->SetMarkerStyle(23);
  h_dataz_acc_only0->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_acc_only0->GetYaxis()->SetTitle("Counts");

  
  c0->cd(4);
  h_dataz_cut0->Draw("e,p1");
  h_dataz_0->Draw("e,same");
  h_dataz_acc_only0->Draw("e,same");
  gPad->Update();

  
 


  TCanvas * c1 = new TCanvas("c1", "c1", 1600, 1200);

  c1->Divide(2,2);
  c1->cd(1);
  h_dataz_cut1->GetYaxis()->SetRangeUser(-1000,4500);
  h_dataz_cut1->Draw("e,p1");
  h_dataz_cut1->SetLineColor(kGreen);
  h_dataz_cut1->SetMarkerStyle(21);
  h_dataz_cut1->SetMarkerColor(kGreen);
  h_dataz_cut1->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_cut1->GetYaxis()->SetTitle("Counts");
  h_dataz_cut1->GetXaxis()->CenterTitle();
  h_dataz_cut1->GetYaxis()->CenterTitle();
  h_dataz_cut1->SetTitle("Z_hadron for Cut1");
  h_dataz_cut1->GetYaxis()->SetTitle("Counts");

  c1->cd(2);
  h_dataz_1->Draw("e,p1");
  h_dataz_1->SetLineColor(kBlue);
  h_dataz_1->SetMarkerColor(kBlue);
  h_dataz_1->SetMarkerStyle(22);
  h_dataz_1->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_1->GetYaxis()->SetTitle("Counts");
  h_dataz_1->GetXaxis()->CenterTitle();
  h_dataz_1->GetYaxis()->CenterTitle();
  
  c1->cd(3);
  h_dataz_acc_only1->Draw("e,p1");
  h_dataz_acc_only1->SetLineColor(kRed);
  h_dataz_acc_only1->SetMarkerColor(kRed);
  h_dataz_acc_only1->SetMarkerStyle(23);
  h_dataz_acc_only1->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_acc_only1->GetYaxis()->SetTitle("Counts");
  h_dataz_acc_only1->GetXaxis()->CenterTitle();
  h_dataz_acc_only1->GetYaxis()->CenterTitle();
  
  c1->cd(4);
  h_dataz_cut1->Draw("e,p1");
  h_dataz_1->Draw("e,same");
  h_dataz_acc_only1->Draw("e,same");
  gPad->Update();



  TCanvas * c2 = new TCanvas("c2", "c2", 1600, 1200);

  c2->Divide(2,2);
  
  c2->cd(1);
  h_dataz_cut2->GetYaxis()->SetRangeUser(-1000,4500);
  h_dataz_cut2->Draw("e,p1");
  h_dataz_cut2->SetLineColor(kGreen);
  h_dataz_cut2->SetMarkerStyle(21);
  h_dataz_cut2->SetMarkerColor(kGreen);
  h_dataz_cut2->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_cut2->GetYaxis()->SetTitle("Counts");
  h_dataz_cut2->SetTitle("Z_hadron for Cut2");
  h_dataz_cut2->GetYaxis()->SetTitle("Counts");
  h_dataz_cut2->GetXaxis()->CenterTitle();
  h_dataz_cut2->GetYaxis()->CenterTitle();
  
  c2->cd(2);
  h_dataz_2->Draw("e,p1");
  h_dataz_2->SetLineColor(kBlue);
  h_dataz_2->SetMarkerColor(kBlue);
  h_dataz_2->SetMarkerStyle(22);
  h_dataz_2->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_2->GetYaxis()->SetTitle("Counts");
  h_dataz_2->GetXaxis()->CenterTitle();
  h_dataz_2->GetYaxis()->CenterTitle();
  
  c2->cd(3);
  h_dataz_acc_only2->Draw("e,p1");
  h_dataz_acc_only2->SetLineColor(kRed);
  h_dataz_acc_only2->SetMarkerColor(kRed);
  h_dataz_acc_only2->SetMarkerStyle(23);
  h_dataz_acc_only2->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_acc_only2->GetYaxis()->SetTitle("Counts");
  h_dataz_acc_only2->GetXaxis()->CenterTitle();
  h_dataz_acc_only2->GetYaxis()->CenterTitle();
  
  
  c2->cd(4);
  h_dataz_cut2->Draw("e,p1");
  h_dataz_2->Draw("e,same");
  h_dataz_acc_only2->Draw("e,same");
  gPad->Update();



  TCanvas * c3 = new TCanvas("c3", "c3", 1600, 1200);

  c3->Divide(2,2);
  c3->cd(1);
  h_dataz_cut3->GetYaxis()->SetRangeUser(-1000,4500);
  h_dataz_cut3->Draw("e,p1");
  h_dataz_cut3->SetLineColor(kGreen);
  h_dataz_cut3->SetMarkerStyle(21);
  h_dataz_cut3->SetMarkerColor(kGreen);
  h_dataz_cut3->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_cut3->GetYaxis()->SetTitle("Counts");
  h_dataz_cut3->SetTitle("Z_hadron for Cut3");
  h_dataz_cut3->GetYaxis()->SetTitle("Counts");
  h_dataz_cut3->GetXaxis()->CenterTitle();
  h_dataz_cut3->GetYaxis()->CenterTitle();

  
  c3->cd(2);
  h_dataz_3->Draw("e,p1");
  h_dataz_3->SetLineColor(kBlue);
  h_dataz_3->SetMarkerColor(kBlue);
  h_dataz_3->SetMarkerStyle(22);
  h_dataz_3->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_3->GetYaxis()->SetTitle("Counts");
  h_dataz_3->GetXaxis()->CenterTitle();
  h_dataz_3->GetYaxis()->CenterTitle();
  
  c3->cd(3);
  h_dataz_acc_only3->Draw("e,p1");
  h_dataz_acc_only3->SetLineColor(kRed);
  h_dataz_acc_only3->SetMarkerColor(kRed);
  h_dataz_acc_only3->SetMarkerStyle(23);
  h_dataz_acc_only3->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_acc_only3->GetYaxis()->SetTitle("Counts");
  h_dataz_acc_only3->GetXaxis()->CenterTitle();
  h_dataz_acc_only3->GetYaxis()->CenterTitle();
  
  c3->cd(4);
  h_dataz_cut3->Draw("e,p1");
  h_dataz_3->Draw("e,same");
  h_dataz_acc_only3->Draw("e,same");
  gPad->Update();


  TCanvas * c1plus2 = new TCanvas("c1plus2", "c1plus2", 1600, 1200);

  c1plus2->Divide(2,2);
  c1plus2->cd(1);
 h_dataz_cut1plus2->GetYaxis()->SetRangeUser(-1000,4500);
 h_dataz_cut1plus2->Draw("e,p1");
 h_dataz_cut1plus2->SetLineColor(kGreen);
 h_dataz_cut1plus2->SetMarkerStyle(21);
 h_dataz_cut1plus2->SetMarkerColor(kGreen);
 h_dataz_cut1plus2->GetXaxis()->SetTitle("Z_HADRON");
 h_dataz_cut1plus2->GetYaxis()->SetTitle("Counts");
 h_dataz_cut1plus2->SetTitle("Z_hadron for Cut1 plus2");
 h_dataz_cut1plus2->GetYaxis()->SetTitle("Counts");
 h_dataz_cut1plus2->GetXaxis()->CenterTitle();
 h_dataz_cut1plus2->GetYaxis()->CenterTitle();

  
  c1plus2->cd(2);
  h_dataz_1plus2->Draw("e,p1");
  h_dataz_1plus2->SetLineColor(kBlue);
  h_dataz_1plus2->SetMarkerColor(kBlue);
  h_dataz_1plus2->SetMarkerStyle(22);
  h_dataz_1plus2->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_1plus2->GetYaxis()->SetTitle("Counts");
  h_dataz_1plus2->GetXaxis()->CenterTitle();
  h_dataz_1plus2->GetYaxis()->CenterTitle();

  
  c1plus2->cd(3);
  h_dataz_acc_only1plus2->Draw("e,p1");
  h_dataz_acc_only1plus2->SetLineColor(kRed);
  h_dataz_acc_only1plus2->SetMarkerColor(kRed);
  h_dataz_acc_only1plus2->SetMarkerStyle(23);
  h_dataz_acc_only1plus2->GetXaxis()->SetTitle("Z_HADRON");
  h_dataz_acc_only1plus2->GetYaxis()->SetTitle("Counts");
  h_dataz_acc_only1plus2->GetXaxis()->CenterTitle();
  h_dataz_acc_only1plus2->GetYaxis()->CenterTitle();
  
  c1plus2->cd(4);
 h_dataz_cut1plus2->Draw("e,p1");
  h_dataz_1plus2->Draw("e,same");
  h_dataz_acc_only1plus2->Draw("e,same");
  gPad->Update();




  h_dataz_cut0->Write();
  // h_dataz_0->Write();
  // h_dataz_acc_only0->Write();


  h_dataz_cut1->Write();
  // h_dataz_1->Write();
  // h_dataz_acc_only1->Write();

  h_dataz_cut2->Write();
  // h_dataz_2->Write();
  // h_dataz_acc_only2->Write();

  h_dataz_cut3->Write();
  // h_dataz_3->Write();
  // h_dataz_acc_only3->Write();


  h_dataz_cut1plus2->Write();
  // h_dataz_1plus2->Write();
  //h_dataz_acc_only1plus2->Write();

  coin->Write();
  cointime->Write();
  cointime_pi->Write();
  cointime_notpi->Write();
  cointime_narrow->Write();
  

    
  c0->SaveAs("pdf_7772/cut0_accsub_pos_3p2dummy_7772.pdf");
  c1->SaveAs("pdf_7772/cut1_accsub_pos_3p2dummy_7772.pdf");
  c2->SaveAs("pdf_7772/cut2_accsub_pos_3p2dummy_7772.pdf");
  c3->SaveAs("pdf_7772/cut3_accsub_pos_3p2dummy_7772.pdf");
  c1plus2->SaveAs("pdf_7772/cut1plus2_accsub_pos_3p2dummy_7772.pdf");
  coin->SaveAs("pdf_7772/ctime_pos_3p2dummy_7772.pdf");
 }
