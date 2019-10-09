//this macro reads a few variables from the rootfile and just takes the counts by doing the accidental subtraction which is calculated by using the cointime plot. we will have cut 1 i.e all the cuts execept the accidental subtraction cut and the other is cut 2 with all the cuts plus the accidental cut.
  #include "header.h"
void pim_x35_z70(){
 
  gStyle->SetOptStat();
  gROOT->SetBatch(kTRUE);
  gROOT->ForceStyle(); 
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetNdivisions(505);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadLeftMargin(0.08);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadBottomMargin(.14);
  gStyle->SetTitleYOffset(1.09);
  gStyle->SetTitleXOffset(0.855);
  gStyle->SetTitleYSize(0.03);
  gStyle->SetTitleXSize(0.03);
  gStyle->SetLabelFont(62,"X");
  gStyle->SetLabelFont(62,"Y");
  gStyle->SetTitleFont(62,"X");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetLabelSize(0.025,"X");
  gStyle->SetLabelSize(0.025,"Y");
  gStyle->SetPaperSize(23,24);
  TChain *tt = new TChain("T");
  
  
  
  tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/hcal_oct5/coin_replay_production_6068_-1.root");
  tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/hcal_oct5/coin_replay_production_6070_-1.root");
  tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/hcal_oct5/coin_replay_production_6071_-1.root");

  TFile *ff = new TFile("ROOT/pim_x35_z70.root", "RECREATE");      

  Double_t pionMass = 0.1395701835;    //Gev/c^2     

  Double_t pbeta,hbeta,pdelta,hdelta,pcaletot,hcaletot,pcalepr,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,E_pi,z_had,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole;
  TH1D *h_Q2d = new TH1D("h_Q2d","Q2 (GeV2)",binq, loq, hiq);  
  TH1D *h_Q2a = new TH1D("h_Q2a","Q2 (GeV2)",binq, loq, hiq); 
  TH1D *h_Wd = new TH1D("h_Wd","W (GeV)", 20, 1.0, 4.0 );
  TH1D *h_Wa = new TH1D("h_Wa","W (GeV)", 20, 1.0, 4.0 );
  TH1D *h_xd = new TH1D("h_xd","X_bj", binx, lox, hix);   
  TH1D *h_xa = new TH1D("h_xa","X_Bj",binx, lox, hix);    
  TH1D *h_ctime = new TH1D("h_ctime", "ctime", 400,25,75);
  TH1D *h_ctimed = new TH1D("h_ctime_C", "ctime_with_ctimecut", 400,25,75);
  TH1D *h_ctimea = new TH1D("h_ctime_B", "ctime_with_accidentals", 400,25,75);
  TH2D *h_beta_ctimed = new TH2D("h_beta_ctime_d","pbeta vs ctime data ",400,25,75,100,0.5,1.5);
  TH2D *h_beta_ctimea = new TH2D("h_beta_ctime_a","pbeta vs ctime acc ",400,25,75,100,0.5,1.5);

  TH2D *h_ct = new TH2D("h_ct","pbeta vs ctime",400,25,75,100,0.5,1.5);
  TH1D *h_betad = new TH1D("h_betad","beta for data",100,0.5,1.5);
  TH1D *h_betaa = new TH1D("h_betaa","beta for acc",100,0.5,1.5);

  TH1D *h_pdeltad = new TH1D("h_pdeltad","SHMS DELTA DATA", bin2, -10,20);
  TH1D *h_pdeltaa = new TH1D("h_pdeltaa","SHMS DELTA ACC", bin2, -10,20);
  TH1D *h_hgcd = new TH1D("h_hgc","HGCER DATA",100,0.001,30);
  TH1D *h_hgca = new TH1D("h_hgca","HGCER ACC",100,0.001,30);

  TH2D *h_hgc_deltad = new TH2D("h_hgc_deltad", "HGC vs Delta Data", bin2,-10,20,20,0.001,30.001);
  TH2D *h_hgc_deltaa = new TH2D("h_hgc_deltaa", "HGC vs Delta Acc ", bin2,-10,20,20,0.001,30.001);

  TH1D *h_zd = new TH1D("h_zd","z_had", binz, loz, hiz);                                      
  TH1D *h_za = new TH1D("h_za","z_had", binz, loz, hiz);  

  
  Int_t cntsepi=0;
  tt->SetBranchAddress("P.gtr.p", &PgtrP); 
  tt->SetBranchAddress("H.gtr.p", &HgtrP); 
  tt->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
  tt->SetBranchAddress("H.gtr.beta", &hbeta); 
  tt->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
  tt->SetBranchAddress("P.gtr.dp", &pdelta);                                                                                
  tt->SetBranchAddress("P.cal.eprtracknorm", &pcalepr);                                                                    
  tt->SetBranchAddress("P.cal.etottracknorm", &pcaletot);                                                                  
  tt->SetBranchAddress("P.hgcer.npeSum", &phg);
  tt->SetBranchAddress("P.aero.npeSum", &paeronpe);                                          
  tt->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);                                  
  tt->SetBranchAddress("H.cal.etottracknorm", &hcaletot);                                          
  tt->SetBranchAddress("H.cer.npeSum", &hcernpe); 
  tt->SetBranchAddress("H.kin.primary.W", &W);
  tt->SetBranchAddress("H.kin.primary.Q2", &Q2);
  tt->SetBranchAddress("H.kin.primary.x_bj", &xbj); 
  tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
  tt->SetBranchAddress("H.kin.primary.omega", &pkinomega);
  tt->SetBranchAddress("H.hod.goodstarttime", &hhodstarttime);
  tt->SetBranchAddress("P.hod.goodstarttime",&phodstarttime);
  tt->SetBranchAddress("P.dc.InsideDipoleExit",&pdipole);
  tt->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);


  Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut;
  Long64_t nentriesD = tt->GetEntries();
  cout<<"Total Entries ="<<nentriesD<<endl;
  for (int kk=0; kk<nentriesD;  kk++){
    tt->GetEntry(kk);
    if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;


    //for pi-runs
    data_cut = paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletot < 0.4 && pcaletot> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.0 &&  pbeta > 0.8 && pbeta < 1.2 &&hbeta > 0.8 &&hbeta < 1.2 &&phg>2 && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole;
    //old data cut is following 
    //data_cut =  paeronpe>0.5 && pcalepr< 0.1 && pcalepr > 0.0 && pcaletot < 0.5 && pcaletot> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.0 &&  pbeta > 0.8 && pbeta < 1.2 &&hbeta > 0.8 &&hbeta < 1.2 &&phg>0.5 && hhodstarttime ==1 &&phodstarttime == 1;

    // data_cut = paeronpe>1.0 && pcalepr< 0.2 && pcaletot < 0.5 && hcaletot > 0.6 && hcaletot < 1.4 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.0 &&  pbeta > 0.8 && pbeta < 1.3 &&hbeta > 0.8 &&hbeta < 1.3 &&phg>1;// && hhodstarttime ==1 &&phodstarttime == 1;

    if(data_cut){
      cntsepi++;

      h_ctime->Fill(ctime);
    }
  }

  cout << cntsepi <<" events passed all cuts but ctime" << endl;

  Int_t bin_max = h_ctime->GetMaximumBin();
  Double_t max_value = h_ctime->GetBinCenter(bin_max);
  cout<<"MAX VALUE ="<< max_value <<endl;


  
  Int_t sh1=max_value + 3*4 -1.5;
  Int_t sh2=max_value + 4*4 +2.;
  Int_t sh3=max_value - 1*4 +1.5;
  Int_t sh4=max_value - 3*4 -1.5;
  Double_t acc_scale_fac = -3.0/((sh2-sh1)+(sh3-sh4));

  Long64_t nentries1 = tt->GetEntries();
  for(int i=0; i<nentries1; i++){
    tt->GetEntry(i);

    if (i % 700000 == 0) cout << i*100/nentries1 << "   % of data done" << endl;

    data_cut = paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletot < 0.4 && pcaletot> 0.1 && hcaletot > 0.8 && hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.0 &&  pbeta > 0.8 && pbeta < 1.2 &&hbeta > 0.8 &&hbeta < 1.2 &&phg>2 && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole==1;
    

    // data_cut = paeronpe>1.0 && pcalepr< 0.1&& pcaletot <0.5 && hcaletot >0.6 && hcaletot <1.8 && hdelta> -10 && hdelta<10 && pdelta>-10 && pdelta<20  &&hcernpe>1&&hcalepr>0.15 && pbeta>0.8 && pbeta<1.3 &&hbeta>0.8 &&hbeta<1.3&&phg>1 ;
    
    if(data_cut){

      ctime_cut = ctime  > max_value - 1.5 && ctime < max_value + 1.5;// beacuse peak is at 43.4375 and ctime peak  lies between 40 to 45.
      accR_cut = ctime > sh1 && ctime < sh2 ;
      accL_cut = ctime > sh4 && ctime < sh3 ;
      acc_cut = accR_cut || accL_cut ; 

      if(ctime_cut){
	h_Wd->Fill(W);
	h_Q2d->Fill(Q2);
	h_xd->Fill(xbj);
	h_ctimed->Fill(ctime);
	h_betad->Fill(pbeta);
	h_beta_ctimed->Fill(ctime,pbeta);
	h_pdeltad->Fill(pdelta);
	h_hgcd->Fill(phg);
	h_hgc_deltad->Fill(pdelta,phg);
	E_pi = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_had = E_pi/pkinomega;
	h_zd->Fill(z_had);
      }
      else if (acc_cut){

	h_Wa->Fill(W);
	h_Q2a->Fill(Q2);
	h_xa->Fill(xbj);
	h_ctimea->Fill(ctime);
	h_betaa->Fill(pbeta);
	h_beta_ctimea->Fill(ctime,pbeta);
	h_pdeltaa->Fill(pdelta);
	h_hgca->Fill(phg);
	h_hgc_deltaa->Fill(pdelta,phg);
	E_pi = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	z_had = E_pi/pkinomega;
	h_za->Fill(z_had);

      }
    }
  }
 
  TH1D *h_Wc = new TH1D(*h_Wd);
  if (!(h_Wc->GetSumw2N() > 0)) h_Wc->Sumw2(kTRUE);
  h_Wc->Add(h_Wa,acc_scale_fac);

  TH1D *h_Q2c = new TH1D(*h_Q2d); 
  if (!(h_Q2c->GetSumw2N() > 0)) h_Q2c->Sumw2(kTRUE);
  h_Q2c->Add(h_Q2a,acc_scale_fac);


  TH1D *h_xc = new TH1D(*h_xd);                                       
  if (!(h_xc->GetSumw2N() > 0)) h_xc->Sumw2(kTRUE);
  h_xc->Add(h_xa,acc_scale_fac);

  TH1D *h_ctimec = new TH1D(*h_ctimed);                                       
  if (!(h_ctimec->GetSumw2N() > 0)) h_ctimec->Sumw2(kTRUE);
  h_ctimec->Add(h_ctimea,acc_scale_fac);


  TH1D *h_betac = new TH1D(*h_betad);
  if(!h_betac->GetSumw2N()) h_betac->Sumw2(kTRUE);
  h_betac->Add(h_betaa,acc_scale_fac);



  TH2D *h_beta_ctimec = new TH2D(*h_beta_ctimed);                                       
  if (!(h_beta_ctimec->GetSumw2N() > 0)) h_beta_ctimec->Sumw2(kTRUE);
  h_beta_ctimec->Add(h_beta_ctimea,acc_scale_fac);
 

  TH1D *h_pdeltac = new TH1D(*h_pdeltad);                                       
  if (!(h_pdeltac->GetSumw2N() > 0)) h_pdeltac->Sumw2(kTRUE);
  h_pdeltac->Add(h_pdeltaa,acc_scale_fac);



  TH1D *h_hgcc = new TH1D(*h_hgcd);                                       
  if (!(h_hgcc->GetSumw2N() > 0)) h_hgcc->Sumw2(kTRUE);
  h_hgcc->Add(h_hgca,acc_scale_fac);


  TH2D *h_hgc_deltac = new TH2D(*h_hgc_deltad);                                       
  if (!(h_hgc_deltac->GetSumw2N() > 0)) h_hgc_deltac->Sumw2(kTRUE);
  h_hgc_deltac->Add(h_hgc_deltaa,acc_scale_fac);


		
  TH1D *h_zc = new TH1D(*h_zd);    
  if (!(h_zc->GetSumw2N() > 0)) h_zc->Sumw2(kTRUE);
  h_zc->Add(h_za,acc_scale_fac);
	

  gROOT->SetBatch(kFALSE);

  TCanvas *c1 = new TCanvas("c1","ctime",800,500);
  c1->SetGrid();
 
  c1->Divide(2,2);
  c1->cd(1);
  h_ctime->SetLineColor(kBlack);
  h_ctime->Draw();
  h_ctimed->SetFillColor(29);
  h_ctimed->SetMarkerColor(kBlue);
  h_ctimed->SetLineColor(kBlue);
  h_ctimed->Draw("SAME");
  h_ctimea->SetMarkerColor(kRed);
  h_ctimea->SetFillColor(46);
  h_ctimea->SetLineColor(kRed);
  h_ctimea->Draw("SAME");


  c1->cd(3);
  h_Q2c->SetLineWidth(2);
  h_Q2c->SetMarkerColor(kBlue);
  h_Q2c->SetLineColor(kBlue);
  h_Q2c->Draw("p e1");

			
  c1->cd(2);
  h_xc->SetLineWidth(2);
  h_xc->SetFillColor(kBlue);
  h_xc->SetMarkerColor(kBlue);
  h_xc->SetLineColor(kBlue);
  h_xc->Draw("p e1");

		      

  c1->cd(4);
  h_zc->SetLineWidth(2);
  h_zc->SetFillColor(kBlue);
  h_zc->SetMarkerColor(kBlue);
  h_zc->SetLineColor(kBlue);
  h_zc->Draw("p e1");

	        
			
  cout<<"acc_scale_fac ="<<acc_scale_fac<<endl;
		
  ff->cd();
  ff->Write();
		

c1->SaveAs("PDF/pim_x35_z70.pdf");

			

}



