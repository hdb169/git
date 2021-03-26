//1) This macro will calculate the tracking efficiency of one or more shms coincidence runs as well as singles. But the cuts for electron selection has to be changed. For pion selcetion  pcaletotnorm>0.05 && pcaletotnorm<0.5 where as for electron selection (singles), pcaletotnorm>0.7 && pcaletotnorm<1.4
//2) For, Coin Runs, yield Y = Counts/ (Q* corrected_efficiency), where
//corrected efficiency = good counts/ [Q(mc)* tr eff * 3/4 shms eff * cpu LT * elec_LT (all< = 1)].
//3) But for singles, Y =  Counts *ps1_factor / [Q(mc)* tr eff * 3/4 shms eff * cpu LT * elec_LT (all< = 1)].
//4) The tracking efficiency is printed in the txtfile.

#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>




//no calcut





#define NRUNS 63//65
void fall_pimd2(){
  // gErrorIgnoreLevel= kError;
  // gROOT->SetBatch(kTRUE);//kFALSE =0, kTRUE =1, kTRUE not  will display the plot, kFALSE will .
  Int_t runs[NRUNS] = { /*6065, 6066*/ 6068, 6070, 6071, 6073, 6081, 6082, 6083, 6088, 6089, 6090, 6104, 6105, 6106, 6111, 6112, 6114, 6237, 6240, 6241, 6245, 6246,6247, 6248, 6249, 6250, 6253, 6254, 6255, 6285, 6286, 6287, 6290, 6291, 6451, 6452, 6453, 6459, 6460, 6461, 6524, 6525, 6526, 6527, 6528, 6529, 6545, 6548, 6549, 7593, 7594, 7595, 7596, 7597, 7671 , 7672, 7729, 7730, 7733, 7735, 7736, 7776, 7796, 7797  };
  //Int_t runs[NRUNS] = {6459,6461,6462,6464 };

      gStyle->SetOptStat(1000011);

  TFile *f;
  TTree *tt;
  for(Int_t i=0; i<NRUNS; i++){

    // f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/yield/coin_replay_production_%d_-1.root", runs[i]),"read");
    //f=new TFile(Form("/home/hdbhatt/efficiency/tracking/ROOTfiles/coin_replay_production_%d_-1.root", runs[i]),"read");
    f=new TFile(Form("/home/hdbhatt/efficiency/tracking/ROOTfiles/coin_replay_production_%d_-1.root", runs[i]),"read");

    //cout<< "Opening Run Num = "<< runs[i] <<endl; 

    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }

    tt=(TTree *)f->Get("T");
   

    Double_t pionMass = 0.1395701835;   

    Double_t pcaletot,pcaletotnorm,pcaletracknorm,pbeta,hbeta,pdelta,hdelta,pcaletottracknorm,hcaletot,pcaleprtracknorm,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,E_pi,z_had,z_had_all,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole,pgoodscinhit,hgoodscinhit,pbetanotrack,hbetanotrack,pdcntrack,hdcntrack,rawctime,hcaletotnorm,gevnum;
 
    
    TH1D *h_caletotnorm_didshms     = new TH1D("h_caletotnorm_didshms","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_shouldshms  = new TH1D("h_caletotnorm_shouldshms","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_didhms     = new TH1D("h_caletotnorm_didhms","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_shouldhms  = new TH1D("h_caletotnorm_shouldhms","", 100, 0.001, 2);                                      
   
    TH1D *h_caletotnorm_didshms_nodelta     = new TH1D("h_caletotnorm_didshms_nodelta","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_didhms_nodelta     = new TH1D("h_caletotnorm_didhms_nodelta","", 100, 0.001, 2);                                      


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
    tt->SetBranchAddress("H.cal.etotnorm",&hcaletotnorm);
    tt->SetBranchAddress("P.hod.goodscinhit",&pgoodscinhit);
    tt->SetBranchAddress("H.hod.goodscinhit",&hgoodscinhit);
    tt->SetBranchAddress("P.dc.ntrack",&pdcntrack);
    tt->SetBranchAddress("H.dc.ntrack",&hdcntrack);
    tt->SetBranchAddress("P.hod.betanotrack",&pbetanotrack);
    tt->SetBranchAddress("H.hod.betanotrack",&hbetanotrack);
    tt->SetBranchAddress("CTime.CoinTime_RAW_ROC2",&rawctime);
    tt->SetBranchAddress("g.evnum",&gevnum);

    // gStyle->SetOptStat(0);

    Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut,pid_cut, pion_cut,should_cutshms,did_cutshms,did_cut1,should_cut1,hms_cut,delta_cut, should_cuthms, did_cuthms, did_cuthms_nodelta, did_cutshms_nodelta;
 
    Long64_t nentriesD = tt->GetEntries();

    //cout<<"Total Entries = "<<nentriesD<<endl;
#include "scalar_analysis.h"
    Int_t nscaler_reads=0;

    
    for (int kk=0; kk<nentriesD;  kk++)//============================================>evts
      {

	tt->GetEntry(kk);
	if (event_flag[nscaler_reads]==1) {

	  //	did_cut    = goodscinhit==1 && betanotrack > 0.7 && betanotrack < 1.4   && pcaletotnorm>0.08 && pcaletotnorm<0.4 &&pdcntrack>0.0;
	  //should_cut = goodscinhit==1 && betanotrack > 0.7 && betanotrack < 1.4   && pcaletotnorm>0.08 && pcaletotnorm<0.4;
	  hms_cut = hgoodscinhit==1 &&hcaletotnorm>0.8 && hhodstarttime==1 && hcernpe>0 &&hbetanotrack>0.5&&hbetanotrack<1.5   ;
	
	  should_cutshms = pgoodscinhit==1 && pbetanotrack > 0.5 && pbetanotrack<1.5  &&    pcaletotnorm>0.05 && pcaletotnorm<0.5  && phodstarttime==1 && phg > 0.5 && paeronpe>4  && hms_cut ;
	  did_cutshms    = should_cutshms &&pdelta>-100&&pdelta<100 && pdcntrack>0.0;
	  did_cutshms_nodelta    = should_cutshms  && pdcntrack>0.0;

	  should_cuthms = pgoodscinhit==1 && pbetanotrack > 0.5 &&pbetanotrack < 1.5 &&    pcaletotnorm>0.05 && pcaletotnorm<0.5   && phodstarttime==1 && phg > 0.5 && paeronpe>4  && hms_cut ;
	  did_cuthms    = should_cuthms &&hdelta>-100&&hdelta<100 && hdcntrack>0.0;
	  did_cuthms_nodelta    = should_cuthms  && hdcntrack>0.0;


	  
	
	  if(did_cutshms)
	    {    h_caletotnorm_didshms->Fill(pcaletotnorm);}
	  if(should_cutshms)
	    {h_caletotnorm_shouldshms->Fill(pcaletotnorm);}
	  

	  if(did_cuthms)
	    {    h_caletotnorm_didhms->Fill(hcaletotnorm);}
	  if(should_cuthms)
	    {h_caletotnorm_shouldhms->Fill(hcaletotnorm);}

	  if(did_cutshms_nodelta)
	    {    h_caletotnorm_didshms_nodelta->Fill(pcaletotnorm);}

	  if(did_cuthms_nodelta)
	    {    h_caletotnorm_didhms_nodelta->Fill(hcaletotnorm);}
 
	  
	}//event flag
	if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;
      }//nentries
    TCanvas *c1 = new TCanvas("c1", "no_ctime_cut",1200,800); 

    // cout<<runs[i]<<"  "<<PTRIG1_Rate<<endl;
    c1->Divide(3,2);

    c1->cd(1);
    h_caletotnorm_didshms->Draw();
    h_caletotnorm_didshms->SetLineWidth(2);
    h_caletotnorm_didshms->SetLineColor(kRed);
    h_caletotnorm_didshms->GetXaxis()->CenterTitle();
    h_caletotnorm_didshms->GetXaxis()->SetTitleOffset(1.2);
    h_caletotnorm_didshms->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_caletotnorm_didshms->GetYaxis()->SetTitle("Entries");
    h_caletotnorm_didshms->SetTitle("DID SHMS");
    
    c1->cd(2);

    h_caletotnorm_shouldshms->Draw("");
    h_caletotnorm_shouldshms->SetLineWidth(2);
    h_caletotnorm_shouldshms->SetLineColor(kBlue);
    h_caletotnorm_shouldshms->GetXaxis()->CenterTitle();
    h_caletotnorm_shouldshms->GetXaxis()->SetTitleOffset(1.2);
    h_caletotnorm_shouldshms->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_caletotnorm_shouldshms->GetYaxis()->SetTitle("Entries");
    h_caletotnorm_shouldshms->SetTitle("SHOULD SHMS");


    c1->cd(3);
    h_caletotnorm_didshms_nodelta->Draw();
    h_caletotnorm_didshms_nodelta->SetLineWidth(2);
    h_caletotnorm_didshms_nodelta->SetLineColor(kRed);
    h_caletotnorm_didshms_nodelta->GetXaxis()->CenterTitle();
    h_caletotnorm_didshms_nodelta->GetXaxis()->SetTitleOffset(1.2);
    h_caletotnorm_didshms_nodelta->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_caletotnorm_didshms_nodelta->GetYaxis()->SetTitle("Entries");
    h_caletotnorm_didshms_nodelta->SetTitle("DID SHMS NODELTA ");
    
    
    c1->cd(4);
    h_caletotnorm_didhms->Draw();
    h_caletotnorm_didhms->SetLineWidth(2);
    h_caletotnorm_didhms->SetLineColor(kRed);
    h_caletotnorm_didhms->GetXaxis()->CenterTitle();
    h_caletotnorm_didhms->GetXaxis()->SetTitleOffset(1.2);
    h_caletotnorm_didhms->GetXaxis()->SetTitle("H.cal.etotnorm");
    h_caletotnorm_didhms->GetYaxis()->SetTitle("Entries");
    h_caletotnorm_didhms->SetTitle("DID HMS ");

    c1->cd(5);

    h_caletotnorm_shouldhms->Draw("");
    h_caletotnorm_shouldhms->SetLineWidth(2);
    h_caletotnorm_shouldhms->SetLineColor(kBlue);
    h_caletotnorm_shouldhms->GetXaxis()->CenterTitle();
    h_caletotnorm_shouldhms->GetXaxis()->SetTitleOffset(1.2);
    h_caletotnorm_shouldhms->GetXaxis()->SetTitle("H.cal.etotnorm");
    h_caletotnorm_shouldhms->GetYaxis()->SetTitle("Entries");
    h_caletotnorm_shouldhms->SetTitle("SHOULD HMS ");

   c1->cd(6);
    h_caletotnorm_didhms_nodelta->Draw();
    h_caletotnorm_didhms_nodelta->SetLineWidth(2);
    h_caletotnorm_didhms_nodelta->SetLineColor(kRed);
    h_caletotnorm_didhms_nodelta->GetXaxis()->CenterTitle();
    h_caletotnorm_didhms_nodelta->GetXaxis()->SetTitleOffset(1.2);
    h_caletotnorm_didhms_nodelta->GetXaxis()->SetTitle("H.cal.etotnorm");
    h_caletotnorm_didhms_nodelta->GetYaxis()->SetTitle("Entries");
    h_caletotnorm_didhms_nodelta->SetTitle("DID HMS NODELTA ");

    
    c1->SaveAs(Form("pdf_hit35/tracking_shms_%d.pdf",runs[i]));

    // c1->SaveAs(Form("integral_pdf/fallpim_D2_%d.pdf",runs[i]));
    //  c1->~TCanvas();	
    // delete c1;
 
    Double_t did_integralshms = h_caletotnorm_didshms->Integral();
    Double_t should_integralshms = h_caletotnorm_shouldshms->Integral();

    Double_t did_integralhms = h_caletotnorm_didhms->Integral();
    Double_t should_integralhms = h_caletotnorm_shouldhms->Integral();

    Double_t did_integralshms_nodelta = h_caletotnorm_didshms_nodelta->Integral();
    Double_t did_integralhms_nodelta = h_caletotnorm_didhms_nodelta->Integral();


    // auto did_entries= h_caletotnorm_did->GetEntries();
    // auto should_entries= h_caletotnorm_should->GetEntries();

    //Double_t did_integral_findbin = h_caletotnorm_did->Integral( h_caletotnorm_did->FindBin(0.700001),h_caletotnorm_did->FindBin(1.3999) );//these are the x-axis lower points and upper points
    //Double_t should_integral_findbin = h_caletotnorm_should->Integral(  h_caletotnorm_should->FindBin(0.700001),h_caletotnorm_should->FindBin(1.3999  ) );//these are the x-axis lower points and upper points


    double curr= charge_sum_cut/tot_scal_cut_time;

    Double_t efficiency_shms = (did_integralshms / should_integralshms);
    auto efficiency_err_shms= (1/should_integralshms) * sqrt(did_integralshms*(1-did_integralshms/should_integralshms));

    Double_t efficiency_hms = (did_integralhms / should_integralhms);
    auto efficiency_err_hms= (1/should_integralhms) * sqrt(did_integralhms*(1-did_integralhms/should_integralhms));

    Double_t efficiency_shms_nodelta = (did_integralshms_nodelta / should_integralshms);
    auto efficiency_err_shms_nodelta= (1/should_integralshms) * sqrt(did_integralshms_nodelta*(1-did_integralshms_nodelta/should_integralshms));

    Double_t efficiency_hms_nodelta = (did_integralhms_nodelta / should_integralhms);
    auto efficiency_err_hms_nodelta= (1/should_integralhms) * sqrt(did_integralhms_nodelta*(1-did_integralhms_nodelta/should_integralhms));

    

    ofstream txtfile_shms ("txtfile_shms/shms_tr_eff_rate_hit35.txt",ios::app);
    txtfile_shms<<runs[i]<<"   "<<PTRIG1_Rate<<"    "<<did_integralshms<<"   "<<should_integralshms<<"   "<<efficiency_shms<<"    "<<efficiency_err_shms<<endl;
    cout<<"shms   "<<runs[i]<<"   "<<PTRIG1_Rate<<"    "<<did_integralshms<<"   "<<should_integralshms<<"   "<<efficiency_shms<<"   "<<efficiency_err_shms<<endl;

    ofstream txtfile_shmscurr ("txtfile_shms/shms_tr_eff_curr_hit35.txt",ios::app);
    txtfile_shmscurr<<runs[i]<<"   "<<curr<<"     "<<did_integralshms<<"   "<<should_integralshms<<"   "<<efficiency_shms<<"   "<<efficiency_err_shms<<""<<endl;

    
    ofstream txtfile_shms_nodelta ("txtfile_shms/shms_tr_eff_curr_nodelta_hit35.txt",ios::app);							
    txtfile_shms_nodelta<<runs[i]<<"   "<<PTRIG1_Rate<< "    "<<did_integralshms_nodelta<<"   "<<should_integralshms<<"   "<<efficiency_shms_nodelta<<"   "<<efficiency_err_shms_nodelta<<""<<endl;
    cout<<"shms   "<<runs[i]<<"  "<<curr<<"    "<<did_integralshms_nodelta<<"   "<<should_integralshms<<"   "<<efficiency_shms_nodelta<<"   "<<efficiency_err_shms_nodelta<<""<<endl;

    ofstream txtfile_hms_curr ("txtfile_hms/hms_tr_eff_curr_hit35.txt",ios::app);							
    txtfile_hms_curr<<runs[i]<<"   "<<curr<< "    "<<did_integralhms<<"   "<<should_integralhms<<"   "<<efficiency_hms<<"   "<<efficiency_err_hms<<""<<endl;
    cout<<"hms   "<<runs[i]<<"  "<<curr<<"    "<<did_integralhms<<"   "<<should_integralhms<<"   "<<efficiency_hms<<"   "<<efficiency_err_hms<<""<<endl;

    ofstream txtfile_hms_nodelta ("txtfile_hms/hms_tr_eff_curr_nodelta_hit35.txt",ios::app);							
    txtfile_hms_nodelta<<runs[i]<<"   "<<curr<< "    "<<did_integralhms_nodelta<<"   "<<should_integralhms<<"   "<<efficiency_hms_nodelta<<"   "<<efficiency_err_hms_nodelta<<""<<endl;
    cout<<"hms  "<<runs[i]<<"  "<<curr<<"    "<<did_integralhms_nodelta<<"   "<<should_integralhms<<"   "<<efficiency_hms_nodelta<<"   "<<efficiency_err_hms_nodelta<<""<<endl;



    //txtfile<<runs[i]<<"  "<<did_integral<<"  "<<should_integral<<"  "<<efficiency_single<<"  "<<error<<""<<endl;
    //  txtfile<<runs[i]<<"  "<<efficiency<<"  "<<error<<""<<endl;

    // cout<<runs[i]<<" "<<charge_sum_cut/tot_scal_cut_time<<"  "<<PTRIG1_Rate<<endl;
  }
    
}



// c1->cd(2);
//    h_betanotrack_did->Draw();
//    h_betanotrack_did->SetLineWidth(2);
//    h_betanotrack_did->SetLineColor(kRed);
//    h_betanotrack_did->GetXaxis()->SetTitle("P.hod.betanotrack");//============================================>try
//    h_betanotrack_did->GetXaxis()->CenterTitle();
//    h_betanotrack_did->GetXaxis()->SetTitleOffset(1.2);
    

//    h_betanotrack_should->Draw("same");
//    h_betanotrack_should->SetLineWidth(2);
//    h_betanotrack_should->SetLineColor(kBlue);
//    h_betanotrack_should->GetXaxis()->CenterTitle();
//    h_betanotrack_should->GetXaxis()->SetTitleOffset(1.2);
