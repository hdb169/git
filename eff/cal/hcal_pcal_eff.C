#define NRUNS 12
void aero_vs_shmsP(){//has hgcer cut
  ofstream txtfile1("txtfile/cur_rate_charge.txt",ios::app);
  ofstream txtfile2("txtfile/hcal_neg_pcal_sh_presh.txt",ios::app);

  for(Int_t r = 0; r<NRUNS;r++){
    gROOT->SetBatch("kTRUE");
    //gStyle->SetOptStat(0);
    //gStyle->SetOptStat(1000011);
    gStyle->SetPalette(1,0);
    gStyle->SetOptStat(1000011);
    gStyle->SetOptFit(11);
    gStyle->SetTitleOffset(1.,"Y");
    gStyle->SetTitleOffset(.7,"X");
    gStyle->SetLabelSize(0.04,"XY");
    gStyle->SetTitleSize(0.06,"XY");
    gStyle->SetPadLeftMargin(0.12);
   
    // Int_t runs[NRUNS] = {6500, 6145,7635,7768,7808,7699};//pos
    //Int_t runs[NRUNS] = {6486,6111,7593,7735,7796,7671};//neg
    //===good Int_t runs[NRUNS] ={7808,7796,7699,7671};//{6500, 6145,7635,7768,7808,7699,6486,6111,7593,7735,7796,7671};
    //Int_t runs[NRUNS] = { 7805,7806,7807,7803,7804,   7815,7816,7817,7819,7820};
    //TString filename  = Form("/home/hdbhatt/Desktop/eff/ROOTfiles/coin_replay_production_%d_-1.root", runs[r]);
    // Int_t runs[NRUNS] ={/*6021,6194,6537,7699,7808,6309,7635,*/   6043,6544,6049,6185,6514  };//+
    //Int_t runs[NRUNS] ={6500, 6145,7635,7768,7808,7699,6486,6111,7593,7735,7796,7671};//,
        Int_t runs[NRUNS] ={6500, 6145,7635,   7768,   7808,   7699,6486,6111,7593,7735,  7796,  7671};//,

	//TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/coin_replay_production_%d_-1.root", runs[r]);
     TString filename  = Form("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/ROOTfiles/added_%d.root", runs[r]);

    TFile *f = new TFile(filename, "READ");
    TFile * f11 = new TFile(Form("root/hcal_eff_%d.root",runs[r]),"RECREATE");
    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

#include "bin.h"
#include "double_good.h"

    
    
    Double_t ctmin = 1.8;
    Double_t ctmax = 1.8;
    Double_t rfmin = 0.5;
    Double_t rfmax = 1.5;
    
    Double_t pcaletotmax = 0.8;
    Double_t hcaletotmin = 0.7;

    Double_t aeromin = 10;//5
    Double_t hgcermin = 5;  
    Double_t hcermin = 13;//8
    
    Double_t rfmin_loose = 0.3;
    Double_t rfmax_loose = 1.8;

    Double_t hmsxptarmin  = -0.06;
    Double_t hmsxptarmax  =  0.06;
    Double_t hmsyptarmin  = -0.025;
    Double_t hmsyptarmax  =  0.025;
    Double_t shmsxptarmin = -0.045;
    Double_t shmsxptarmax =  0.045;
    Double_t shmsyptarmin = -0.028;
    Double_t shmsyptarmax =  0.028;

    
   
    Bool_t all_but_nohcer, all_cut, xptaryptar_cut,  xptaryptar_pre, all_but_noaero, all_but_nohgcer,all_but_noxyptar, all_but_noW2Mx2   ;

#include "offsetrf.h"
    TTree * tt = (TTree *)f->Get("T");    TTree * ss = (TTree *)f->Get("TSP");
#include "define_histogram.h"
#include "branch.h"
    Long64_t nentriesD = tt->GetEntries();
#include "scaler_branch.h"
    Long64_t scal_entries = ss->GetEntries();
    cout<< runs[r] <<" : "<<  "Entries = "<<nentriesD<<endl;
#include "scaler_analysis.h"
    Int_t nscaler_reads_acc=0;
    for (int kk=0; kk<nentriesD;  kk++){//---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(kk);

      if (event_flag[nscaler_reads_acc]==1) {
	rf_pion_pre = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut_pre = rf_pion_pre > rfmin && rf_pion_pre < rfmax;
	mod4_notpioncut_pre =!mod4_pioncut_pre;
	Epi_cut_pre  = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut_pre = Epi_cut_pre/dnu;
	Mx2_cut_pre  = (protonmass + dnu - zhad_cut_pre*dnu) *  (protonmass + dnu - zhad_cut_pre*dnu) - abs(dpmiss)*abs(dpmiss);
	xptaryptar_pre = hmsxptar > hmsxptarmin && hmsxptar < hmsxptarmax &&   hmsyptar > hmsyptarmin && hmsyptar < hmsyptarmax &&  shmsxptar > shmsxptarmin && shmsxptar < shmsxptarmax  &&  shmsyptar > shmsyptarmin && shmsyptar < shmsyptarmax; 

	pid_cut_pre  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut_pre && paero > aeromin   && pcaletottrack < pcaletotmax &&  hcaletottrack  > hcaletotmin && xptaryptar_pre && dW2 > 4 && Mx2_cut_pre > 1.6;// /* hgcer > hgcermin*/

	if (pid_cut_pre){
	  hpbeta->Fill(pbeta);
	  hctime->Fill(ctime);
	}  
	 
      }
   
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;

    }
  
    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
    Int_t nscaler_reads=0;
    for (int s=0; s<nentriesD;  s++){
      tt->GetEntry(s);
      if (event_flag[nscaler_reads]==1) {

	Epi = sqrt(pow(pionmass,2) + pow(PgtrP,2));
	zhad = Epi/dnu;
	Mx2 = (protonmass + dnu - zhad*dnu) *  (protonmass + dnu - zhad*dnu) - abs(dpmiss)*abs(dpmiss);
	accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
	accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
	acc_cut = (accR_cut || accL_cut);
	ctime_cut = ctime > (max_value - ctmin) && ctime < (max_value + ctmax);
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut = rf_pion > rfmin && rf_pion < rfmax;
	mod4_pioncut_loose = rf_pion > rfmin_loose && rf_pion < rfmax_loose;
	mod4_notpioncut =!mod4_pioncut;
	xptaryptar_cut = hmsxptar > hmsxptarmin && hmsxptar < hmsxptarmax &&   hmsyptar > hmsyptarmin && hmsyptar < hmsyptarmax &&  shmsxptar > shmsxptarmin && shmsxptar < shmsxptarmax  &&  shmsyptar > shmsyptarmin && shmsyptar < shmsyptarmax; 

	
	base_cut          =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin &&  xptaryptar_cut    && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin *///==========>HGC, Mx2, dW2=====
	base_cut_looserf  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut_loose && paero > aeromin &&  xptaryptar_cut  && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */

	shms_etottrack_cut = pcaletottrack < pcaletotmax;
	hms_etottrack_cut  = hcaletottrack >  hcaletotmin;

	acc_cut   =  base_cut && acc_cut;    
	coin_cut  =  base_cut && ctime_cut;
	all_cut =  coin_cut && shms_etottrack_cut && hms_etottrack_cut; //all coin cuts but no acc subtraction done here.
	all_but_noxyptar =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 1.6 && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */

	all_but_nohcer =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 1.6 && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */
	all_but_noaero =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut &&/* paero > aeromin &&*/ ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */
	all_but_nohgcer =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 1.6;//NOHGCER
	all_but_noW2Mx2 =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin;
	
	//hdelta> -8 && hdelta < 8 && hcer
	hmsshower = hcaletottrack-hcalepr;
	shmsshower = pcaletottrack-pcalepr;
	
	hcal_should_cut_acc   =  acc_cut && shms_etottrack_cut;
	hcal_did_cut_acc      =  hcal_should_cut_acc           && hms_etottrack_cut;
	pcal_should_cut_acc   =  acc_cut && hms_etottrack_cut;
	pcal_did_cut_acc      =  pcal_should_cut_acc           && shms_etottrack_cut;
	all_acc_cut           =  acc_cut && shms_etottrack_cut && hms_etottrack_cut;
	
	if(all_acc_cut){hctimeacc->Fill(ctime);}
	//fill assuming acc hist
	//also plotting should quantity for hms and shms cal, as it should be the best one

	if(hcal_did_cut_acc){
	  hist_hcal_did_acc->Fill(hcaletottrack);
	}
       	if(hcal_should_cut_acc){

	  hist_hcal_should_acc->Fill(hcaletottrack);
	  hms_sh_vs_psh_should_acc->Fill(hcalepr,hmsshower);
	}
	
	if(pcal_did_cut_acc){
	  hist_pcal_did_acc->Fill(pcaletottrack);
	  
	}
       	if(pcal_should_cut_acc){
	  hist_pcal_should_acc->Fill(pcaletottrack);
	  shms_sh_vs_psh_should_acc->Fill(pcalepr,shmsshower);
	}

	//acc cut done

	//Earlier above we defined for accidental and now we are defining for the coincidence events. The only difference is taking ctime peak events///
	hcal_should_cut_coin   =  coin_cut && shms_etottrack_cut;
	hcal_did_cut_coin      =  hcal_should_cut_coin           && hms_etottrack_cut;
	pcal_should_cut_coin   =  coin_cut && hms_etottrack_cut;
	pcal_did_cut_coin      =  pcal_should_cut_coin           && shms_etottrack_cut;
	all_coin_cut           =  coin_cut && shms_etottrack_cut && hms_etottrack_cut;
	
	//Fill coin hist
	if(hcal_did_cut_coin){hist_hcal_did_coin->Fill(hcaletottrack);}
       	if(hcal_should_cut_coin){
	  hist_hcal_should_coin->Fill(hcaletottrack);
	  hms_sh_vs_psh_should_coin->Fill(hcalepr,hmsshower);

	}
	
	if(pcal_did_cut_coin){hist_pcal_did_coin->Fill(pcaletottrack);}
       	if(pcal_should_cut_coin){
	  hist_pcal_should_coin->Fill(pcaletottrack);
	  shms_sh_vs_psh_should_coin->Fill(pcalepr,shmsshower);

	}

       	//+++++++++++++++++++++++++++++++sh vs etot, presh vs etot************************
       	//	if(all_coin_cut) //with hcal, pcal cuts too 

	if(coin_cut) //with hcal, pcal cuts too 
	  {
	    hms_sh_vs_psh->Fill(hcalepr,hmsshower);
	    shms_sh_vs_psh->Fill(pcalepr,shmsshower);
	    ctime_vs_rf->Fill(rf_pion, ctime);
	    etot_vs_rf->Fill(rf_pion,pcaletottrack);
	    hms_etot_vs_rf->Fill(rf_pion,hcaletottrack);
	    epr_vs_rf->Fill(rf_pion, pcalepr);
	    ctime_vs_etot->Fill(pcaletottrack, ctime);
	    ctime_vs_epr->Fill(pcalepr,ctime);
	    hctimect->Fill(ctime);
	    sh_vs_rf->Fill(rf_pion,shmsshower);
	    hmsepr_vs_rf->Fill(rf_pion,hcalepr);
	    hmssh_vs_rf->Fill(rf_pion,hmsshower);
	    
	  }

	if(all_but_nohcer){//to plot npe vs hms p
	  hcernpe_vs_hmsp->Fill(HgtrP,hcernpe);
	}
	if(all_but_noaero){//to plot npe vs shms p
	  aeronpe_vs_shmsp->Fill(PgtrP,paero);
	}
	if(all_but_nohgcer){//to plot npe vs shms p
	  hgcernpe_vs_shmsp->Fill(PgtrP,hgcer);
	}

	if(all_but_noxyptar){//this is all but non xptar, yptar 
	  hms_xptar_noxyptar->Fill(hmsxptar);
	  hms_yptar_noxyptar->Fill(hmsyptar);
	  shms_xptar_noxyptar->Fill(shmsxptar);
	  shms_yptar_noxyptar->Fill(shmsyptar);
	  hms_xptar_vs_yptar_noxyptar->Fill(hmsyptar,hmsxptar);//xptar along yaxis and yptar along x axis
	  shms_xptar_vs_yptar_noxyptar->Fill(shmsyptar,shmsxptar);
	}

  	//all_cut: all pid+coin+RF aero etc
	if(all_cut){//this is for xptar, yptar peter's values (xptar,yptar)=>HMS(+/-0.06,+/-0.022) and SHMS(+/-0.045,+/-0.028)
	  hms_xptar->Fill(hmsxptar);
	  hms_yptar->Fill(hmsyptar);
	  shms_xptar->Fill(shmsxptar);
	  shms_yptar->Fill(shmsyptar);
	  hms_xptar_vs_yptar->Fill(hmsyptar,hmsxptar);//xptar along yaxis and yptar along x axis
	  shms_xptar_vs_yptar->Fill(shmsyptar,shmsxptar);
	}

	
	if(base_cut_looserf) //no any cal cut at all

	  {
	    hms_sh_vs_psh_base->Fill(hcalepr,hmsshower);
	    shms_sh_vs_psh_base->Fill(pcalepr,shmsshower);
	    ctime_vs_rf_base->Fill(rf_pion, ctime);
	    etot_vs_rf_base->Fill(rf_pion,pcaletottrack);
	    hms_etot_vs_rf_base->Fill(rf_pion,hcaletottrack);
	    epr_vs_rf_base->Fill(rf_pion, pcalepr);
	    ctime_vs_etot_base->Fill(pcaletottrack, ctime);
	    ctime_vs_epr_base->Fill(pcalepr,ctime);
	    sh_vs_rf_base->Fill(rf_pion,shmsshower);
	    hmsepr_vs_rf_base->Fill(rf_pion,hcalepr);
	    hmssh_vs_rf_base->Fill(rf_pion,hmsshower);
	  }	

	if(all_but_noW2Mx2){
	  d_W2->Fill(dW2);
	  d_Wprime2->Fill(Mx2);

	}
	
      }//eventflag
      if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;

    }//nentries

    TCanvas * cc4 = new TCanvas ("cc4", "W2  MX2", 1200, 800);
    cc4->Divide(2,2);

    cc4->cd(1);
    d_W2->Draw();gPad->SetGridx();gPad->SetGridy();
    d_W2->SetTitle(Form("W2 : Run %d",runs[r]));

    cc4->cd(2);gPad->SetGridx();gPad->SetGridy();
    d_Wprime2->Draw();
    d_Wprime2->SetTitle(Form("Mx2 : Run %d",runs[r]));
    cc4->SaveAs(Form("pdf/W2_Mx2_%d.pdf", runs[r]));

    
    TCanvas * cc3 = new TCanvas ("cc3", "hcer vs npe", 1200, 800);

    cc3->Divide(4,3);
    //before xptar yptar cut
   cc3->cd(1);gPad->SetGridx();gPad->SetGridy();
    hms_xptar_noxyptar->Draw();
    hms_xptar_noxyptar->GetXaxis()->SetTitle("HMS XPTAR");
    hms_xptar_noxyptar->GetXaxis()->CenterTitle();
    hms_xptar_noxyptar->SetTitle(Form("hms_xptar : Run %d",runs[r]));

    cc3->cd(2);gPad->SetGridx();gPad->SetGridy();
    hms_yptar_noxyptar->Draw();
    hms_yptar_noxyptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_yptar_noxyptar->GetXaxis()->CenterTitle();

    
    cc3->cd(3);gPad->SetGridx();gPad->SetGridy();
    shms_xptar_noxyptar->Draw();
    shms_xptar_noxyptar->GetXaxis()->SetTitle("SHMS XPTAR");
    shms_xptar_noxyptar->GetXaxis()->CenterTitle();


    cc3->cd(4);gPad->SetGridx();gPad->SetGridy();
    shms_yptar_noxyptar->Draw();
    shms_yptar_noxyptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_yptar_noxyptar->GetXaxis()->CenterTitle();

    
    cc3->cd(5);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    hms_xptar_vs_yptar_noxyptar->Draw("colz");
    hms_xptar_vs_yptar_noxyptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_xptar_vs_yptar_noxyptar->GetYaxis()->SetTitle("HMS XPTAR");
    hms_xptar_vs_yptar_noxyptar->GetXaxis()->CenterTitle();
    hms_xptar_vs_yptar_noxyptar->GetYaxis()->CenterTitle();

    cc3->cd(6);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    shms_xptar_vs_yptar_noxyptar->Draw("colz");
    shms_xptar_vs_yptar_noxyptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_xptar_vs_yptar_noxyptar->GetYaxis()->SetTitle("SHMS XPTAR");
    shms_xptar_vs_yptar_noxyptar->GetXaxis()->CenterTitle();
    shms_xptar_vs_yptar_noxyptar->GetYaxis()->CenterTitle();

    
    //after xptar yptar cut
    cc3->cd(7);gPad->SetGridx();gPad->SetGridy();
    hms_xptar->Draw();
    hms_xptar->GetXaxis()->SetTitle("HMS XPTAR");
    hms_xptar->GetXaxis()->CenterTitle();
    hms_xptar->SetTitle(Form("hms_xptar : Run %d",runs[r]));

    cc3->cd(8);gPad->SetGridx();gPad->SetGridy();
    hms_yptar->Draw();
    hms_yptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_yptar->GetXaxis()->CenterTitle();

    
    cc3->cd(9);gPad->SetGridx();gPad->SetGridy();
    shms_xptar->Draw();
    shms_xptar->GetXaxis()->SetTitle("SHMS XPTAR");
    shms_xptar->GetXaxis()->CenterTitle();


    cc3->cd(10);gPad->SetGridx();gPad->SetGridy();
    shms_yptar->Draw();
    shms_yptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_yptar->GetXaxis()->CenterTitle();

    
    cc3->cd(11);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    hms_xptar_vs_yptar->Draw("colz");
    hms_xptar_vs_yptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_xptar_vs_yptar->GetYaxis()->SetTitle("HMS XPTAR");
    hms_xptar_vs_yptar->GetXaxis()->CenterTitle();
    hms_xptar_vs_yptar->GetYaxis()->CenterTitle();

    cc3->cd(12);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    shms_xptar_vs_yptar->Draw("colz");
    shms_xptar_vs_yptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_xptar_vs_yptar->GetYaxis()->SetTitle("SHMS XPTAR");
    shms_xptar_vs_yptar->GetXaxis()->CenterTitle();
    shms_xptar_vs_yptar->GetYaxis()->CenterTitle();

    
    
    cc3->SaveAs(Form("pdf/xptar_yptar_%d.pdf", runs[r]));

    TCanvas * cc2 = new TCanvas ("cc2", "hcer vs npe", 1000, 800);
    cc2->Divide(2,2);
    cc2->cd(1);gPad->SetLogz();
    hcernpe_vs_hmsp->Draw("colz");
    hcernpe_vs_hmsp->SetTitle(Form("HCER NPE vs HMS MOM : Run: %d",runs[r]));
      
    cc2->cd(2);gPad->SetLogz();
    aeronpe_vs_shmsp->Draw("colz");

    cc2->cd(3);gPad->SetLogz();
    hgcernpe_vs_shmsp->Draw("colz");
  

    cc2->SaveAs(Form("pdf/hcer_aero_hgcer_npe_vs_p_%d.pdf", runs[r]));
    
    // find acc only under the main ctime peak only (in 16ns..., in 1ns ..., and under main peak ~3 ns ....)
    TH1D *  hist_hcal_did_acc_1peak = (TH1D*)hist_hcal_did_acc->Clone();
    TH1D *  hist_hcal_should_acc_1peak = (TH1D*)hist_hcal_should_acc->Clone();
    TH1D *  hist_pcal_did_acc_1peak = (TH1D*)hist_pcal_did_acc->Clone();
    TH1D *  hist_pcal_should_acc_1peak = (TH1D*)hist_pcal_should_acc->Clone();
    TH1D *  hist_ctime_acc_1peak = (TH1D*)hctimeacc->Clone();//copy of acc hist

    TH2D * hms_sh_vs_psh_should_acc_1peak = (TH2D*)hms_sh_vs_psh_should_acc->Clone();
    TH2D * shms_sh_vs_psh_should_acc_1peak = (TH2D*)shms_sh_vs_psh_should_acc->Clone();


    hist_hcal_did_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_hcal_should_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_pcal_did_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_pcal_should_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_ctime_acc_1peak->Scale((ctmin+ctmax)/16);
    hms_sh_vs_psh_should_acc_1peak->Scale((ctmin+ctmax)/16);
    shms_sh_vs_psh_should_acc_1peak->Scale((ctmin+ctmax)/16);


    
    double onepeakacc_counts = hist_ctime_acc_1peak->Integral();
    cout<<runs[r]<<"  "<<"acc one peak counts = "<<onepeakacc_counts<<endl;

    if (hist_hcal_did_acc_1peak->GetSumw2N() == 0) hist_hcal_did_acc_1peak->Sumw2(kTRUE);
    if (hist_hcal_should_acc_1peak->GetSumw2N() == 0) hist_hcal_should_acc_1peak->Sumw2(kTRUE);
    if (hist_pcal_did_acc_1peak->GetSumw2N() == 0) hist_pcal_did_acc_1peak->Sumw2(kTRUE);
    if (hist_pcal_should_acc_1peak->GetSumw2N() == 0) hist_pcal_should_acc_1peak->Sumw2(kTRUE);
    if (hist_ctime_acc_1peak->GetSumw2N() == 0) hist_ctime_acc_1peak->Sumw2(kTRUE);

    if (hms_sh_vs_psh_should_acc_1peak->GetSumw2N() == 0) hms_sh_vs_psh_should_acc_1peak->Sumw2(kTRUE);
    if (shms_sh_vs_psh_should_acc_1peak->GetSumw2N() == 0) shms_sh_vs_psh_should_acc_1peak->Sumw2(kTRUE);


    hist_hcal_did_clean->Add(hist_hcal_did_coin,hist_hcal_did_acc_1peak,1.0,-1.0);
    hist_hcal_should_clean->Add(hist_hcal_should_coin,hist_hcal_should_acc_1peak,1.0,-1.0);
    hist_pcal_did_clean->Add(hist_pcal_did_coin,hist_pcal_did_acc_1peak,1.0,-1.0);
    hist_pcal_should_clean->Add(hist_pcal_should_coin,hist_pcal_should_acc_1peak,1.0,-1.0);
    hist_ctime_clean->Add(hctimect,hist_ctime_acc_1peak,1.0,-1.0);

    hms_sh_vs_psh_should_clean->Add(hms_sh_vs_psh_should_coin,hms_sh_vs_psh_should_acc_1peak,1.0,-1.0);
    shms_sh_vs_psh_should_clean->Add(shms_sh_vs_psh_should_coin,shms_sh_vs_psh_should_acc_1peak,1.0,-1.0);

    

    if (hist_hcal_did_clean->GetSumw2N() == 0) hist_hcal_did_clean->Sumw2(kTRUE);
    if (hist_hcal_should_clean->GetSumw2N() == 0) hist_hcal_should_clean->Sumw2(kTRUE);
    if (hist_pcal_did_clean->GetSumw2N() == 0) hist_pcal_did_clean->Sumw2(kTRUE);
    if (hist_pcal_should_clean->GetSumw2N() == 0) hist_pcal_should_clean->Sumw2(kTRUE);
    if (hist_ctime_clean->GetSumw2N() == 0) hist_ctime_clean->Sumw2(kTRUE);
    if (hms_sh_vs_psh_should_clean->GetSumw2N() == 0) hms_sh_vs_psh_should_clean->Sumw2(kTRUE);
    if (hms_sh_vs_psh_should_clean->GetSumw2N() == 0) shms_sh_vs_psh_should_clean->Sumw2(kTRUE);



    

    TCanvas * cc1 = new TCanvas ("cc1", "cc1", 1000, 800);
    cc1->Divide(1,1);
    cc1->cd(1);

    
    hctimect->Draw("hist ");//all coincuts, main peak only
    hctimect->SetLineColor(kMagenta);
    hctimect->SetLineWidth(1);
    //hist_ctime_clean->Draw();
    hist_ctime_clean->SetLineColor(kGreen);
    hist_ctime_clean->SetLineWidth(2);

    hctime->Draw("hist sames");//finding peak all but no ct
    hctime->SetLineWidth(1);
    hctime->SetLineColor(kBlack);

 
    hctimeacc->Draw("hist sames");//acc 4 peaks only
    hctimeacc->SetLineColor(kRed);
    hctimeacc->SetLineWidth(1);

    
    hist_ctime_acc_1peak->Draw("hist sames");
    hist_ctime_acc_1peak->SetLineColor(kPink);
    hist_ctime_acc_1peak->SetLineWidth(3);

    // hist_ctime_clean->Draw("hist, sames");

   
    


    double ctime_acc_ent        = hctimeacc->Integral();
    double ctime_acc_1peak_ent  = hist_ctime_acc_1peak->Integral();
    double ctime_coin_ent       = hctimect->Integral();
    double ctime_clean_ent      = hist_ctime_clean->Integral();
    cout<<"============================================================================"<<endl;
    cout<<runs[r]<<"  "<<"Coin Peak, Acc,  Clean enries = "<<ctime_coin_ent<<"    "<<ctime_acc_1peak_ent<<"     "<<ctime_clean_ent<<endl;
    cout<<"============================================================================"<<endl;

   
    cc1->SaveAs(Form("pdf/ctime_bef_acc_%d.pdf", runs[r]));
    delete cc1;
   
    TCanvas * c1 = new TCanvas ("c1", "c1", 1000, 800);
    c1->Divide(3,2);
    c1->cd(1);gPad->SetLogy();
    hist_hcal_did_coin->Draw();
    //hist_hcal_did_acc->Draw("sames");
    hist_hcal_did_acc->SetLineColor(kPink);
    hist_hcal_did_acc_1peak->Draw("hist sames");
    hist_hcal_did_acc_1peak->SetLineColor(kRed);
    hist_hcal_did_clean->Draw("hist sames");
    hist_hcal_did_clean->SetLineColor(kGreen);
    hist_hcal_did_clean->SetLineWidth(3);    
    hist_hcal_did_coin->SetTitle(Form("HCAL DID %d",runs[r]));

    c1->cd(2);gPad->SetLogy();
    hist_hcal_should_coin->Draw();
    //hist_hcal_should_acc->Draw("sames");
    hist_hcal_should_acc->SetLineColor(kPink);
    hist_hcal_should_acc_1peak->Draw("hist sames");
    hist_hcal_should_acc_1peak->SetLineColor(kRed);
    hist_hcal_should_clean->Draw("hist sames");
    hist_hcal_should_clean->SetLineColor(kGreen);
    hist_hcal_should_clean->SetLineWidth(3);    

    c1->cd(3);gPad->SetLogy();
    hist_pcal_did_coin->Draw();
    //hist_pcal_did_acc->Draw("sames");
    hist_pcal_did_acc->SetLineColor(kPink);
    hist_pcal_did_acc_1peak->Draw("hist sames");
    hist_pcal_did_acc_1peak->SetLineColor(kRed);
    hist_pcal_did_clean->Draw("hist sames");
    hist_pcal_did_clean->SetLineColor(kGreen);
    hist_pcal_did_clean->SetLineWidth(3); 

    c1->cd(4);gPad->SetLogy();
    hist_pcal_should_coin->Draw();
    //hist_pcal_should_acc->Draw("sames");
    hist_pcal_should_acc->SetLineColor(kPink);
    hist_pcal_should_acc_1peak->Draw("hist sames");
    hist_pcal_should_acc_1peak->SetLineColor(kRed);
    hist_pcal_should_clean->Draw("hist sames");
    hist_pcal_should_clean->SetLineColor(kGreen);
    hist_pcal_should_clean->SetLineWidth(3);   

    c1->cd(5);gPad->SetLogz();
    hms_sh_vs_psh_should_clean->Draw("colz");

    c1->cd(6);gPad->SetLogz();
    shms_sh_vs_psh_should_clean->Draw("colz");


    // delete c1;
    
    double ent_hcaldid_coin =  hist_hcal_did_coin->Integral();
    double ent_hcaldid_acc =  hist_hcal_did_acc->Integral();
    double ent_hcaldid_acc_1peak =  hist_hcal_did_acc_1peak->Integral();
    double ent_hcaldid_clean =  hist_hcal_did_clean->Integral();


    double ent_hcalshould_coin =  hist_hcal_should_coin->Integral();
    double ent_hcalshould_acc =  hist_hcal_should_acc->Integral();
    double ent_hcalshould_acc_1peak =  hist_hcal_should_acc_1peak->Integral();
    double ent_hcalshould_clean =  hist_hcal_should_clean->Integral();

    //Find Bin
    // cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    double int_hcaldid_clean =  hist_hcal_did_clean->Integral(hist_hcal_did_clean->FindBin(hcaletotmin),hist_hcal_did_clean->FindBin(2));
    double int_hcalshould_clean =  hist_hcal_should_clean->Integral(hist_hcal_should_clean->FindBin(0.),hist_hcal_should_clean->FindBin(2));
    //cout<<runs[r]<<"  "<< " hcal : did FindBin / should Find Bin    =  "<<  int_hcaldid_clean<<" / "   << int_hcalshould_clean   << "  =  "<< int_hcaldid_clean/int_hcalshould_clean<<endl;
    double int_pcaldid_clean =  hist_pcal_did_clean->Integral(hist_pcal_did_clean->FindBin(0),hist_pcal_did_clean->FindBin(pcaletotmax));
    double int_pcalshould_clean =  hist_pcal_should_clean->Integral(hist_pcal_should_clean->FindBin(0),hist_pcal_should_clean->FindBin(2));
    //cout<<runs[r]<<"  "<< " pcal : did FindBin / should Find Bin    =  "<<  int_pcaldid_clean<<" / "   << int_pcalshould_clean   << "  =  "<<  int_pcaldid_clean/int_pcalshould_clean<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"   "<<endl;
    
    
    double ent_pcaldid_coin =  hist_pcal_did_coin->Integral();
    double ent_pcaldid_acc =  hist_pcal_did_acc->Integral();
    double ent_pcaldid_acc_1peak =  hist_pcal_did_acc_1peak->Integral();
    double ent_pcaldid_clean =  hist_pcal_did_clean->Integral();

    double ent_pcalshould_coin =  hist_pcal_should_coin->Integral();
    double ent_pcalshould_acc =  hist_pcal_should_acc->Integral();
    double ent_pcalshould_acc_1peak =  hist_pcal_should_acc_1peak->Integral();
    double ent_pcalshould_clean =  hist_pcal_should_clean->Integral();

    double hcal_eff = ent_hcaldid_clean/ent_hcalshould_clean;
    double pcal_eff = ent_pcaldid_clean/ent_pcalshould_clean;

    // cout<<runs[r]<<" "<<"hcal did = "<< int_hcaldid_clean<< "   "<< "pcal_did = "<<int_pcaldid_clean<<endl;
    // cout<<runs[r]<<" "<<"hcal did1 = "<< ent_hcaldid_clean<< "   "<< "pcal_did1 = "<<ent_pcaldid_clean<<endl;

   

    cout<<runs[r]<<"  "<< "hcal did ent    =  "<<  ent_hcaldid_coin     <<"     "<<  ent_hcaldid_acc<<    "     "<<  ent_hcaldid_acc_1peak<<    "     "<< ent_hcaldid_clean<<endl;  
    cout<<runs[r]<<"  "<< "hcal should ent =  "<<  ent_hcalshould_coin  <<"     "<<  ent_hcalshould_acc<< "     "<<  ent_hcalshould_acc_1peak<< "     "<< ent_hcalshould_clean<<endl;  
    cout<<runs[r]<<"  "<< "pcal did ent    =  "<<  ent_pcaldid_coin     <<"     "<<  ent_pcaldid_acc<<    "     "<<  ent_pcaldid_acc_1peak<<    "     "<< ent_pcaldid_clean<<endl;  
    cout<<runs[r]<<"  "<< "pcal should ent =  "<<  ent_pcalshould_coin  <<"     "<<  ent_pcalshould_acc<< "     "<<  ent_pcalshould_acc_1peak<< "     "<< ent_pcalshould_clean<<endl;  
    cout<<"  "<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<runs[r]<<"      "<<"hcal eff =  "<<ent_hcaldid_clean<<" / "<<ent_hcalshould_clean<< "     "<< hcal_eff<<endl;
    cout<<runs[r]<<"      "<<"pcal eff =  "<<ent_pcaldid_clean<<" / "<<ent_pcalshould_clean<< "     "<< pcal_eff<<endl;

    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

   

    TCanvas * c2 = new TCanvas ("c2", "c2", 1000, 800);
    c2->Divide(4,3);
    c2->cd(1);gPad->SetLogz();
    hms_sh_vs_psh->Draw("colz");
    hms_sh_vs_psh->SetTitle(Form("HMS SH VS PSH %d",runs[r]));

    c2->cd(2);gPad->SetLogz();
    hms_etot_vs_rf->Draw("colz");

    c2->cd(3);gPad->SetLogz();
    shms_sh_vs_psh->Draw("colz");

    c2->cd(4);gPad->SetLogz();
    ctime_vs_rf->Draw("colz");

    c2->cd(5);gPad->SetLogz();
    etot_vs_rf->Draw("colz");

    c2->cd(6);gPad->SetLogz();
    epr_vs_rf->Draw("colz");

    c2->cd(7);gPad->SetLogz();
    ctime_vs_etot->Draw("colz");

    c2->cd(8);gPad->SetLogz();
    ctime_vs_epr->Draw("colz");

    c2->cd(9);gPad->SetLogz();
    sh_vs_rf->Draw("colz");

    c2->cd(10);gPad->SetLogz();
    hmsepr_vs_rf->Draw("colz");

    c2->cd(11);gPad->SetLogz();
    hmssh_vs_rf->Draw("colz");

    
    

    //delete c2;
    //////////////////these are base plots with no cal cut//////////////
    TCanvas * c3 = new TCanvas ("c3", "c3", 1000, 800);
    c3->Divide(4,3);
    c3->cd(1);gPad->SetLogz();
    hms_sh_vs_psh_base->Draw("colz");
    hms_sh_vs_psh_base->SetTitle(Form("HMS SH VS PSH BASE %d",runs[r]));

    c3->cd(2);gPad->SetLogz();
    hms_etot_vs_rf_base->Draw("colz");

      
    c3->cd(3);gPad->SetLogz();
    shms_sh_vs_psh_base->Draw("colz");

    c3->cd(4);gPad->SetLogz();
    ctime_vs_rf_base->Draw("colz");

    c3->cd(5);gPad->SetLogz();
    etot_vs_rf_base->Draw("colz");

    c3->cd(6);gPad->SetLogz();
    epr_vs_rf_base->Draw("colz");

    c3->cd(7);gPad->SetLogz();
    ctime_vs_etot_base->Draw("colz");

    c3->cd(8);gPad->SetLogz();
    ctime_vs_epr_base->Draw("colz");

    c3->cd(9);gPad->SetLogz();
    sh_vs_rf_base->Draw("colz");

    c3->cd(10);gPad->SetLogz();
    hmsepr_vs_rf_base->Draw("colz");

    c3->cd(11);gPad->SetLogz();
    hmssh_vs_rf_base->Draw("colz");


    c1->SaveAs(Form("pdf/cal_coin_before_accsub_%d.pdf", runs[r]));
    c2->SaveAs(Form("pdf/plots_2d_%d.pdf", runs[r]));
    c3->SaveAs(Form("pdf/base_plots_2d_nocal_%d.pdf", runs[r]));
    //c4->SaveAs(Form("pdf/pcal_sh_presh_separate_%d.pdf", runs[r]));
    //c5->SaveAs(Form("pdf/SH_VS_ETOT_%d.pdf", runs[r]));

    delete c1;
    delete c2;
    delete c3;
    // delete c4;
   
    double current_bcmcut  = charge_sum_cut/tot_scal_cut_time;  
    txtfile1<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut/1000<<endl;
    txtfile2<< runs[r]<<"   "<<ent_hcaldid_clean<<"    "<<ent_hcalshould_clean<< "     "<<" = "<<hcal_eff<<"    "<<ent_pcaldid_clean<<"   "<<ent_pcalshould_clean<< "     " <<" = "<< pcal_eff<<endl;//"   "<<pcal_shower_eff<<"   "<<pcal_pre_shower_eff<< endl;
    //txtfile2<< runs[r]<<"   "<<current_bcmcut<<"   "<<PTRIG1_Rate<<"   "<<charge_sum_cut/1000.<<endl;

    hcernpe_vs_hmsp->Write();
    aeronpe_vs_shmsp->Write();
    hgcernpe_vs_shmsp->Write();

 
    
    //=======final
    cout<<" "<<endl;
    
  }//runs
  cout<<" "<<endl;

}//void
