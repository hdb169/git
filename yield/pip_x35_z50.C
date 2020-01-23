//this macro reads a few variables from the rootfile and just takes the counts by doing the accidental subtraction which is calculated by using the cointime plot. we will have cut 1 i.e all the cuts execept the accidental subtraction cut and the other is cut 2 with all the cuts plus the accidental cut.
#include "header.h"
//void data_acc(Int_t runNum){//6263 data, 6261 dummy for trial
void pip_x35_z50(){
  //Int_t runNum = 6068;//first run num here
  gStyle->SetOptStat(1111111);
#include "gStyle.h" 
#include "bin.h"
  TChain *tt = new TChain("T");
     tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/yield/coin_replay_production_6043_-1.root");
     tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/yield/coin_replay_production_6044_-1.root");
     tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/yield/coin_replay_production_6045_-1.root");

  TFile *ff = new TFile("root/pip_x35_z50.root","RECREATE");   

  //TTree *tt = (TTree*)f->Get("T");

  Long64_t nentriesD = tt->GetEntries();

  cout<<"data entries = "<<nentriesD<<"  "<<endl;

  Double_t pionMass = 0.1395701835;   
  Double_t pbeta,hbeta,pdelta,hdelta,hcaletot,pcaletottrack,pcalepr,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,Epi,Epi_d,Epi_acc,z,z_d,z_acc,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pcaletotnorm,goodscinhit,betanotrack,pdcntrack,pdcch1nhit,pdcch2nhit;
 
  TH1D *h_datactime = new TH1D("h_datactime", "h_datactime (ns)", binct, loct, hict);
  TH1D *h_datactime_d = new TH1D("h_datactime_d", "h_datactime_d (ns)", binct, loct, hict);
  TH1D *h_datactime_acc = new TH1D("h_datactime_acc", "h_datactime_acc", binct, loct, hict);


  TH1D *h_dataz = new TH1D("h_dataz","h_dataz", binz, loz, hiz);        
  TH1D *h_dataz_d = new TH1D("h_dataz_d","h_dataz_d", binz, loz, hiz);                                      
  TH1D *h_dataz_acc = new TH1D("h_dataz_acc","h_dataz_acc", binz, loz, hiz);                                      

                              
  TH1D *h_datax = new TH1D("h_datax","h_datax", binx, lox, hix);   
  TH1D *h_datax_d = new TH1D("h_datax_d","h_datax_d", binx, lox, hix);   
  TH1D *h_datax_acc = new TH1D("h_datax_acc","h_datax_acc", binx, lox, hix);                                      

                                 
  TH1D *h_dataQ2d = new TH1D("h_dataQ2d","h_dataQ2d",binq, loq, hiq);  



  Int_t cntsepi=0;
  Int_t evts=0;
  Int_t counts=0;
 
#include "setbranch.h"

  Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut,pid_cut,tracking_cut,did_cut,should_cut,acc_cut_should,acc_cut_did,pid_cut_acc;
 

  /////////////////////////////////////////////////////////PART 1 find Coincidence time peak/////////////////////////////////
  for (int kk=0; kk<nentriesD;  kk++)//original
    //for (int kk=0; kk<50000;  kk++)
   
    {

      tt->GetEntry(kk);

      if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;

      data_cut = paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.7 && pbeta < 1.3 &&hbeta > 0.7 &&hbeta < 1.3  && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1;//no hgcer cut 
  
      if(data_cut)
	{    cntsepi++;

	  h_datactime->Fill(ctime);
	 
	 
	}
    }

  cout <<"events that passed all cuts except ctime = " << cntsepi << endl;

  /////////////////////////////////////////////////////////DATA HISTOGRAM WITH CTIME && PID_CUT/////////////////////////////////

  cout<<"calulating the max peak value of the ctime dist"<<endl;

  Int_t bin_max = h_datactime->GetMaximumBin();
  Double_t max_value = h_datactime->GetBinCenter(bin_max);
  cout<<"ctime peak is at = "<< max_value <<endl;

  for (int ll=0; ll<nentriesD;  ll++){
    tt->GetEntry(ll);
    if (ll % 700000 == 0) cout << ll*100/nentriesD << "   % of data done" << endl;

    pid_cut =  paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.7 && pbeta < 1.3 &&hbeta > 0.7 &&hbeta < 1.3  && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1 && ctime > (max_value-2) && ctime < (max_value+2);
  
    if(pid_cut){
      evts++;
      h_datactime_d->Fill(ctime);
      Epi_d = sqrt(pow(pionMass,2) + pow(PgtrP,2));
      z_d = Epi_d/pkinomega;
      h_dataz_d->Fill(z_d);
      h_datax_d->Fill(xbj);


    }
  }


  /////////////////////////////////////////////////////////DATA HISTOGRAM WITH ONLY ACCIDENTALS/////////////////////////////////

  cout<<"calculating accidental backgrounds"<<endl;

  for (int mm=0; mm<nentriesD;  mm++)  
    //for (int mm=0; mm<50000;  mm++)

    {
      tt->GetEntry(mm);
      if (mm % 700000 == 0) cout << mm*100/nentriesD << "   % of data done" << endl;


      pid_cut_acc =   paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.7 && pbeta < 1.3 &&hbeta > 0.7 &&hbeta < 1.3  && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1;

      accR_cut        =   ctime > (max_value-22) && ctime < (max_value-6);
      accL_cut        =   ctime > (max_value+6) && ctime < (max_value+22);
     
      acc_cut    = (accL_cut || accR_cut) && pid_cut_acc;
      if(acc_cut){
	counts++;
	h_datactime_acc->Fill(ctime);
	Epi_acc = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_acc = Epi_acc/pkinomega;
	h_dataz_acc->Fill(z_acc);
	h_datax_acc->Fill(xbj);


      }
    }    

 
  gROOT->SetBatch(kFALSE);
  cout<<"plotting the histograms"<<endl;

  #include "plot.h"
  h_dataz_final->Write();
  c1->SaveAs("pdf/pip_x35_z50.pdf");

}
///////////////////////////////////////////////done///////////////////////////////////////////







































