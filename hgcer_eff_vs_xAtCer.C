void hgcer_eff_vs_xAtCer(Int_t runNumber){

 gStyle->SetOptStat(1111);

   
  TChain *tree = new TChain("T");

//tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_7777_100000.root");
//tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_6088_100000.root");
//tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_7671_100000.root");
//tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_6499_100000.root");
//tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_6359_100000.root");
tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/hgc_aug20/coin_replay_production_7735_-1.root");
tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/hgc_aug20/coin_replay_production_7736_-1.root");
//tree->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_7679_15000.root");
  
  TFile *MyFile = new TFile(Form("output_root/new_hist%d.root",runNumber),"RECREATE");
  
  
  TH1F *hTotalx          = new TH1F("hTotalx", "Eff vs X ", 40, -20., 20.);
  TH1F *hPassx           = new TH1F("hPassx" , "         ", 40, -20., 20.);
  TH1F *hTotaly         = new TH1F("hTotaly","Eff vs Y ", 40, -20., 20.);
  TH1F *hPassy          = new TH1F("hPassy" ,"         ", 40, -20., 20.);

  
  TH2F *XvsYtotal       = new TH2F ("XvsYtotal"," ",  40, -20.0, 20.0, 40, -20.0, 20.0); 
  TH2F *XvsYpass        = new TH2F ("XvsYpass" ," ",  40, -20.0, 20.0, 40, -20.0, 20.0); 
  TH2F *XvsY            = new TH2F ("XvsY"," ",       40, -20.0, 20.0, 40, -20.0, 20.0);
  

  Double_t delta,beta,aero;
  Double_t npe,ctime;
  Double_t cal, w2, epr;
  Double_t track_x_fp,track_y_fp ;
  Double_t track_xp_fp,track_yp_fp ;
  Double_t my_x, my_y;
  Double_t el_hi;
  

  //TTree *tree = (TTree*) f->Get("T");
  
  tree->SetBranchAddress("P.gtr.dp",              &delta);
  tree->SetBranchAddress("P.dc.x_fp",             &track_x_fp);
  tree->SetBranchAddress("P.dc.xp_fp",            &track_xp_fp);
  tree->SetBranchAddress("P.dc.y_fp",             &track_y_fp);
  tree->SetBranchAddress("P.dc.yp_fp",            &track_yp_fp);
  tree->SetBranchAddress("P.hgcer.npeSum",        &npe);
  tree->SetBranchAddress("P.cal.etottracknorm",   &cal);
  //  tree->SetBranchAddress("P.kin.W2",              &w2);
  //  tree->SetBranchAddress("T.coin.pEL_HI_tdcTime", &el_hi);
  tree->SetBranchAddress("P.cal.eprtracknorm",     &epr);
  tree->SetBranchAddress("P.aero.npeSum",          &aero);
  tree->SetBranchAddress("P.gtr.beta",             &beta);
  tree->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);


  Long64_t nentries =tree->GetEntries();
  
  for (Long64_t i=0; i<nentries; i++) 
    {
     
      tree->GetEntry(i);
 
      my_x = track_x_fp - 156.27 * (track_xp_fp);
      my_y = track_y_fp - 156.27 * (track_yp_fp);
      
      bool should_cut = delta> -12 && delta <22 &&aero>1.3 &&cal>0.1 &&cal<0.4 &&epr>0.0 &&epr<0.2 &&beta>0.6 &&beta<1.5;// &&ctime>41&&ctime<45 ;// &&epr<0.4 (cal-epr):epr >0.1&& (cal-epr):epr <0.5;//&& el_hi>100 && cal>0.2 &&cal < 0.6 && (cal-epr):epr >0.1&& (cal-epr):epr <0.5;// &&aero>1.;
      bool did_cut = should_cut && npe>1;

      if (should_cut)
	{
	  hTotalx   ->Fill(my_x);
	  hTotaly   ->Fill(my_y);
	  XvsYtotal ->Fill(my_y, my_x);	
	  XvsY      ->Fill(my_y, my_x);	
	}

      if (did_cut)
	{
	  hPassx   ->Fill(my_x);
	  hPassy   ->Fill(my_y);
	  XvsYpass ->Fill(my_y, my_x);	  
	}
    }
 
  TEfficiency *pEff = new TEfficiency();
  pEff  = new TEfficiency(*hPassx, *hTotalx);
  pEff->SetTitle(" ; x_{cer};Efficiency"); 

  TEfficiency *pEff2 = new TEfficiency();
  pEff2 = new TEfficiency(*hPassy, *hTotaly);
  pEff2->SetTitle(" ;y_{cer};Efficiency");

  TEfficiency *pEff1 = new TEfficiency();
  pEff1  = new TEfficiency(*XvsYpass, *XvsYtotal);
  
  TCanvas *c1 =  new TCanvas("c1", " " ,1500, 800);
  c1  ->cd();
  pEff1->Draw("colz");

  TCanvas *c3 = new TCanvas( "c3","", 1500, 800);
  c3->cd();
  pEff2->Draw();

  TCanvas *c2 = new TCanvas("c2", "", 1500, 800);
  c2->cd();
  pEff->Draw();
  pEff  ->Write("X");
  pEff2->Write("Y");
  pEff1 ->Write("XYhist");
  XvsY  ->Write("xyhistCount");
 
  MyFile->Print();


}
