//1) This macro will calculate the tracking efficiency of one or more shms coincidence runs as well as singles. But the cuts for electron selection has to be changed.
// For pion selcetion  pcaletotnorm>0.05 && pcaletotnorm<0.5 where as for electron selection (singles), pcaletotnorm>0.7 && pcaletotnorm<1.4
//2) For, Coin Runs, yield Y = Counts/ (Q* corrected_efficiency), where
//corrected efficiency = good counts/ [Q(mc)* tr eff * 3/4 shms eff * cpu LT * elec_LT (all< = 1)].
//3) But for singles, Y =  Counts *ps1_factor / [Q(mc)* tr eff * 3/4 shms eff * cpu LT * elec_LT (all< = 1)].
//4) The tracking efficiency is printed in the txtfile.
//Dec 04, 2019
#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>

#define NRUNS 4
void singles_eff(){
  // gErrorIgnoreLevel= kError;
   gROOT->SetBatch(kTRUE);//kFALSE =0, kTRUE =1, kTRUE not  will display the plot, kFALSE will .

  //#include "header.h"
  Int_t runs[NRUNS]= {6482,6483,6484,6485};
  TFile *f;
  TTree *tt;
  for(Int_t i=0; i<NRUNS; i++){

    // f[i]=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/check_ngconly_7671_tofall/7671_checked_to_%d_-1.root", runs[i]),"read");
    f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/singles_jan2/coin_replay_production_%d_-1.root", runs[i]),"read");
    cout<< "Opening Run Num = "<< runs[i] <<endl; 

    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }

    tt=(TTree *)f->Get("T");
   

    Double_t pionMass = 0.1395701835;   

    Double_t pcaletot,pcaletotnorm,pcaletracknorm,pbeta,hbeta,pdelta,hdelta,pcaletottracknorm,hcaletot,pcaleprtracknorm,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,E_pi,z_had,z_had_all,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,goodscinhit,betanotrack,pdcntrack;
 
    
    TH1D *h_caletotnorm_did     = new TH1D("h_caletotnorm_did","h_caletotnorm_did", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_should  = new TH1D("h_caletotnorm_should","h_caletotnorm_should", 100, 0.001, 2);                                      
  
    

    tt->SetBranchAddress("P.gtr.p", &PgtrP); 
    tt->SetBranchAddress("H.gtr.p", &HgtrP); 
    tt->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
    tt->SetBranchAddress("H.gtr.beta", &hbeta); 
    tt->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
    tt->SetBranchAddress("P.gtr.dp", &pdelta);                                                                                
    tt->SetBranchAddress("P.cal.eprtracknorm", &pcaleprtracknorm);                                                                    
    tt->SetBranchAddress("P.cal.etottracknorm", &pcaletottracknorm);                                                                  
    tt->SetBranchAddress("P.hgcer.npeSum", &phg);
    tt->SetBranchAddress("P.aero.npeSum", &paeronpe);                                          
    tt->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);  
    tt->SetBranchAddress("P.cal.etracknorm", &pcaletracknorm); 
    tt->SetBranchAddress("H.cal.etottracknorm", &hcaletot);                                          
    tt->SetBranchAddress("H.cer.npeSum", &hcernpe);    
    tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
    tt->SetBranchAddress("H.hod.goodstarttime", &hhodstarttime);
    tt->SetBranchAddress("P.hod.goodstarttime",&phodstarttime);
    tt->SetBranchAddress("P.dc.InsideDipoleExit",&pdipole);
    tt->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);
    tt->SetBranchAddress("P.cal.etot",&pcaletot);
    tt->SetBranchAddress("P.cal.etotnorm",&pcaletotnorm);
    tt->SetBranchAddress("P.hod.goodscinhit",&goodscinhit);
    tt->SetBranchAddress("P.dc.ntrack",&pdcntrack);
    tt->SetBranchAddress("P.hod.betanotrack",&betanotrack);


    Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut,pid_cut, pion_cut,should_cut,did_cut;
 
    Long64_t nentriesD = tt->GetEntries();

    cout<<"Total Entries = "<<nentriesD<<endl;

    // for (int kk=0; kk<nentriesD/100;  kk++)//============================================>evts
    for (int kk=0; kk<nentriesD;  kk++)//============================================>evts
      {

	tt->GetEntry(kk);

	//cout<<"total entries = "<<tt->GetEntries()<<endl;
	//	if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;
//to select electrons,
	did_cut    = goodscinhit==1 && betanotrack > 0.7 && betanotrack < 1.4   && pcaletotnorm>0.7 && pcaletotnorm<1.4 &&pdcntrack>0.0;
	should_cut = goodscinhit==1 && betanotrack > 0.7 && betanotrack < 1.4   && pcaletotnorm>0.7 && pcaletotnorm<1.4;
//to select pions,

//       did_cut    = goodscinhit==1 && betanotrack > 0.7 && betanotrack < 1.4   && pcaletotnorm>0.5 && pcaletotnorm<0.5 &&pdcntrack>0.0;
 //       should_cut = goodscinhit==1 && betanotrack > 0.7 && betanotrack < 1.4   && pcaletotnorm>0.5 && pcaletotnorm<0.5;


  
	if(did_cut)
	  {    
	    h_caletotnorm_did->Fill(pcaletotnorm);
	  }
      

	if(should_cut)
	  {    
	    h_caletotnorm_should->Fill(pcaletotnorm);
	  }
      }
    
    TCanvas *c1 = new TCanvas("c1", "no_ctime_cut",1200,800); 
  
    c1->Divide(2,1);

    c1->cd(1);gPad->SetGridx();
    h_caletotnorm_did->Draw();
    h_caletotnorm_did->SetLineWidth(2);
    h_caletotnorm_did->SetLineColor(kRed);
    h_caletotnorm_did->SetTitle(Form("P.cal.etotnorm_did: Run : %d", runs[i]));
    h_caletotnorm_did->GetXaxis()->SetTitle("P.cal.etotnorm");//============================================>try
    h_caletotnorm_did->GetXaxis()->CenterTitle();
    h_caletotnorm_did->GetXaxis()->SetTitleOffset(1.2);
    

    c1->cd(2);gPad->SetGridx();
    h_caletotnorm_should->Draw();
    h_caletotnorm_should->SetLineWidth(2);
    h_caletotnorm_should->SetLineColor(kBlue);
    h_caletotnorm_should->SetTitle(Form("P.cal.etotnorm_should: Run : %d", runs[i]));
    h_caletotnorm_should->GetXaxis()->SetTitle("P.cal.etotnorm");//============================================>try
    h_caletotnorm_should->GetXaxis()->CenterTitle();
    h_caletotnorm_should->GetXaxis()->SetTitleOffset(1.2);
      
    c1->SaveAs(Form("integral_pdf/%d.pdf",runs[i]));
    //  c1->~TCanvas();	
    // delete c1;
 
    Double_t did_integral = h_caletotnorm_did->Integral();
    Double_t should_integral = h_caletotnorm_should->Integral();

    auto did_entries= h_caletotnorm_did->GetEntries();
    auto should_entries= h_caletotnorm_should->GetEntries();

    Double_t did_integral_findbin = h_caletotnorm_did->Integral( h_caletotnorm_did->FindBin(0.700001),h_caletotnorm_did->FindBin(1.3999) );//these are the x-axis lower points and upper points
    Double_t should_integral_findbin = h_caletotnorm_should->Integral(  h_caletotnorm_should->FindBin(0.700001),h_caletotnorm_should->FindBin(1.3999  ) );//these are the x-axis lower points and upper points




    Double_t efficiency_single = (did_integral / should_integral);
    //The following 3 lins are actually the same, but trying to see whether h->Integral() or h->GetEntries() or h->Integral(FindBin(x_min,x_max)) are the same or different, but they all are the same. So the best way is to use h->Integral() 

    cout<< setprecision(2)<<fixed<< "Run Num = " <<runs[i] <<" did_integral    =  "<<did_integral         <<" should_integral    =   "  <<should_integral         <<  "           eff = " <<(did_integral / should_integral)*100.0<<  "%"<<endl; 
    // cout<< setprecision(2)<<fixed<< "Run Num = " <<runs[i] <<" did_entries     =  "<<did_entries          <<" should_entries     =   "  <<should_entries          <<  "           eff = " <<(did_entries / should_entries)*100.0 <<  "%"<<endl;
    //cout<< setprecision(2)<<fixed<< "Run Num = " <<runs[i] <<" did_int_findbin =  "<<did_integral_findbin <<" should_int_findbin =   "  <<should_integral_findbin<<  "            eff = " <<(did_integral_findbin / should_integral_findbin)*100.0<<  "%"<<endl;


    auto error= (1/should_integral) * sqrt(did_integral*(1-did_integral/should_integral));
    ofstream txtfile ("txtfile/shms_singles_eff.txt",ios::app);

    txtfile<<runs[i]<<"  "<<did_integral<<"  "<<should_integral<<"  "<<efficiency_single<<"  "<<error<<""<<endl;
    								

  }
    
}



