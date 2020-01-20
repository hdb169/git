#include "header.h"
void try_dd(Int_t d2run, Int_t d2evts, Int_t alrun, Int_t alevts){

#include "gStyle.h" 
  TFile *fdata= new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/very_low_hirate/coin_replay_production_%d_%d.root",d2run, d2evts));
  TFile *fal = new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/very_low_hirate/coin_replay_production_%d_%d.root",alrun, alevts));
   
  TFile *ff = new TFile(Form("root/%d_%d.root", d2run, alrun),"RECREATE");   
  TH1D *h1=new TH1D("h1","h1",100,0,2);   
  TTree *tdata= (TTree*)fdata->Get("T");
  TTree *tal= (TTree*)fal->Get("T");
  Long64_t nentriesData = tdata->GetEntries();
  Long64_t nentriesAl = tal->GetEntries();
  cout<<"data entries = "<<nentriesData<<" dummy entries = "<<nentriesAl<<endl;


//Define histograms for data and dummy

  //------1----->/////////////////////////////only data histograms for tracking efficiency////////////////////////
  TH1D *cal_did = new TH1D("cal_did ","cal_did", bin, lo, hi);                                      
  TH1D *cal_should = new TH1D("cal_should","cal_should", bin, lo, hi); //fill P.cal.etotnorm not the tracknorm
                                     
 //------2----->/////////////////////////////only data histograms for yield calculation ////////////////////////
  TH1D *pbeta = new TH1D("pbeta ","pbeta", bin, lo, hi);  
  TH1D *ctime = new TH1D("ctime", "ctime (ns)", binct, loct, hict);
                                 
  // set branch address
    #include "setbranch.h"
//define cuts
Bool_t ctime_cut, acc_cut, did_cut. should_cut..;
for (int kk=0; kk<nentriesData;  kk++)
    {
      tt->GetEntry(kk);
            if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;

      did_cut = pcaletot>0.7 &&.....;
      should_cut = pcaletot>0.7&&....;
        if(did_cut)

	{   
h1->Fill(x);
	 

	}

      if(should_cut)
	{    
h2->Fill(x)

	}
}
for (int kk=0; kk<nEntriesAl;  kk++)
    {

      tt->GetEntry(kk);

      if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;

did_cut_al= .....;
should_cut_al
      if(did_cut_al)

	{   

	  h11->Fill(xx)

	}

      if(should_cut_al)
	{    

	
  h22->Fill(yy)

	}

    
    }
