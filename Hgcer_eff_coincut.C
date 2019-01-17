void eff_coincut(){
  gStyle->SetOptStat(0);
  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("coin_replay_production_3435_good_-1.root");
  if (!f) {
    f = new TFile("coin_replay_production_3435_good_-1.root");
  }
        
  TTree *tt = (TTree*) f->Get("T");
  // TEfficiency* pEff = 0;
  TEfficiency* pEff = new TEfficiency("eff","Efficiency vs Delta,SHMS DELTA,Efficiency",20,-10,20);
  //*********************************************************************
  Double_t pionMass = 0.1395701835;
  Double_t mtarget = 1.87561298212;//D2 target mass
  TH1D *h1_epi_PcointimeROC2    = new TH1D("SHMS ROC2 Corrected epi Coin Time","SHMS ROC2 Corrected epi Coin Time; cointime [ns]",       480, -24, 24); 
  TH1D *h1_epi_PcointimeROC2_C  = new TH1D("SHMS ROC2 Corrected epi Coin Time_C","SHMS ROC2 Corrected epi Coin Time_C; cointime [ns]",   480, -24, 24); 
  TH1D *h1_epi_PcointimeROC2_B  = new TH1D("SHMS ROC2 Corrected epi Coin Time_B","SHMS ROC2 Corrected epi Coin Time_B; cointime [ns]",   480, -24, 24);

  int nentriesD = tt->GetEntries();
  cout<<"Entries:\t"<<nentriesD<<endl;

  Double_t HgtrX, HgtrTh, HgtrY, HgtrPh, hdelta, PgtrX, PgtrTh, PgtrY, PgtrPh, pdelta;
  Double_t HgtrBetaCalc, PgtrBetaCalc, evtType, PgtrP, HgtrP, PhodStatus, PhodStartTime, PhodfpHitsTime;
  Double_t cointime, HhodStatus, HhodStartTime, HhodfpHitsTime, SHMSpartMass, HMSpartMass;
  Double_t TcoinpTRIG1_ROC1_tdcTimeRaw, TcoinpTRIG4_ROC1_tdcTimeRaw, TcoinpTRIG1_ROC2_tdcTimeRaw;
  Double_t TcoinhTRIG1_ROC1_tdcTimeRaw, TcoinhTRIG1_ROC2_tdcTimeRaw, TcoinhTRIG4_ROC1_tdcTimeRaw;
  Double_t TcoinhTRIG4_ROC2_tdcTimeRaw, TcoinpTRIG4_ROC2_tdcTimeRaw;
  Double_t pbeta,hbeta,pcalepr,pcaletot,pcernpe,paeronpe,hcernpe,hcalepr,hcaletot,pngcernpe,pcaletotnorm;

  Double_t PdcXfp;
  Double_t PdcXpfp;
  Double_t PdcYfp;
  Double_t PdcYpfp;
  Double_t HdcXfp;
  Double_t HdcXpfp;
  Double_t HdcYfp;
  Double_t HdcYpfp;
  
  Int_t cntsepi=0;
  tt->SetBranchAddress("P.ngcer.npeSum",&pngcernpe);
  tt->SetBranchAddress("P.gtr.p", &PgtrP); 
  tt->SetBranchAddress("H.gtr.p", &HgtrP); 
  tt->SetBranchAddress("P.gtr.beta", &pbeta);
  tt->SetBranchAddress("H.gtr.beta", &hbeta); 
  tt->SetBranchAddress("H.gtr.dp", &hdelta);
  tt->SetBranchAddress("P.gtr.dp", &pdelta);
  tt->SetBranchAddress("P.cal.eprtracknorm", &pcalepr);                                                                    
  tt->SetBranchAddress("P.cal.etottracknorm", &pcaletot);                                                                  
  tt->SetBranchAddress("P.hgcer.npeSum", &pcernpe);
  tt->SetBranchAddress("P.aero.npeSum", &paeronpe);                                                                                                       
  tt->SetBranchAddress("P.cal.etotnorm", &pcaletotnorm);                                  
  tt->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);                                  
  tt->SetBranchAddress("H.cal.etottracknorm", &hcaletot);                                          
  tt->SetBranchAddress("H.cer.npeSum", &hcernpe); 
  tt->SetBranchAddress("P.hod.starttime", &PhodStartTime);
  tt->SetBranchAddress("P.hod.fpHitsTime", &PhodfpHitsTime);
  tt->SetBranchAddress("H.hod.starttime", &HhodStartTime);
  tt->SetBranchAddress("H.hod.fpHitsTime", &HhodfpHitsTime); 
  tt->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTimeRaw", &TcoinpTRIG1_ROC1_tdcTimeRaw);
  tt->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &TcoinpTRIG4_ROC1_tdcTimeRaw);
  tt->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw", &TcoinpTRIG1_ROC2_tdcTimeRaw);
  tt->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &TcoinpTRIG4_ROC2_tdcTimeRaw);
  tt->SetBranchAddress("H.gtr.x", &HgtrX);                                                               
  tt->SetBranchAddress("H.gtr.th", &HgtrTh);                                                             
  tt->SetBranchAddress("H.gtr.y", &HgtrY);                                                               
  tt->SetBranchAddress("H.gtr.ph", &HgtrPh);                                                             
  tt->SetBranchAddress("P.gtr.x", &PgtrX);                                                               
  tt->SetBranchAddress("P.gtr.th", &PgtrTh);                                                             
  tt->SetBranchAddress("P.gtr.y", &PgtrY);                                                               
  tt->SetBranchAddress("P.gtr.ph", &PgtrPh);                                                             


  Double_t pOffset = 1.5; //9.5 + 10;  // in ns                                  
  Double_t hOffset = 335;                                                        
  Double_t speedOfLight = 29.9792; // in cm/ns                                   
  Double_t SHMScentralPathLen = 18.1*100;  // SHMS Target to focal plane path length converted to cm  
  Double_t SHMSpathLength = 18.1*100;      // For now assume that it's same as SHMScentralPathLen  
  Double_t HMScentralPathLen = 22*100;     // HMS Target to focal plane path length converted to cm
  Double_t DeltaHMSpathLength;             // For now assume that it's same as HMScentralPathLen 
  Double_t SHMScoinCorr = 0.0;                                                   
  Double_t HMScoinCorr = 0.0;                                                    
  Double_t SHMSrawCoinTimeROC1;                                                  
  Double_t SHMSrawCoinTimeROC2;                                                  
  Double_t HMSrawCoinTimeROC1;                                                   
  Double_t HMSrawCoinTimeROC2;                                                   
  Double_t SHMScorrCoinTimeROC1;                                                 
  Double_t SHMScorrCoinTimeROC2;                                                 
  Double_t HMScorrCoinTimeROC1;                                                  
  Double_t HMScorrCoinTimeROC2;   

  SHMSpartMass = 0.1395701835; // pion mass in GeV/c^2                 
  HMSpartMass = 0.000510998; // electron mass in GeV/c^2  

  Bool_t epievent_cut, event_cut, hpdelta_cut,ctime_cut,  acc_cut, accL_cut, accR_cut; 

  TCut hpdelta;
  TCut epiCut;
  // TCut shouldCut;
  // TCut didCut;
  
  hpdelta = "P.gtr.dp > -10 && P.gtr.dp < 20 && H.gtr.dp > -10 && H.gtr.dp < 10";
  epiCut = "P.aero.npeSum > 1.0 && P.cal.eprtracknorm < 0.2 && H.cer.npeSum > 1.0 && H.cal.etottracknorm > 0.6 && H.cal.etottracknorm < 2.0 && H.cal.eprtracknorm  > 0.2"; 
  // shouldCut = " P.gtr.beta>0.8&&P.gtr.beta<1.3&&P.gtr.dp<20&&P.gtr.dp>-10&&P.aero.npeSum>2&&P.cal.eprtracknorm<0.4&&(P.cal.etottracknorm-P.cal.eprtracknorm)<0.4 )";
  // didCut = shouldCut &&" P.hgcer.npeSum>0.5";


  TCanvas *canvas1 = new TCanvas("canvas1","canvas1");                           
  tt->Draw("P.hod.starttime >> SHMShodoStartTime", epiCut && hpdelta );  
  TH1D *h1PhodoStartTime = (TH1D*)gDirectory->Get("SHMShodoStartTime");
  h1PhodoStartTime->GetXaxis()->SetTitle("SHMS hodo start time [ns]");           
  Double_t PhodoStartTimeMean = h1PhodoStartTime->GetMean();
  
  TCanvas *canvas2 = new TCanvas("canvas2","canvas2");                           
  tt->Draw("H.hod.starttime >> HMShodoStartTime", epiCut && hpdelta );  
  TH1D *h1HhodoStartTime = (TH1D*)gDirectory->Get("HMShodoStartTime");           
  h1HhodoStartTime->GetXaxis()->SetTitle("HMS hodo start time [ns]");            
  Double_t HhodoStartTimeMean = h1HhodoStartTime->GetMean();



  TH1F *hTotal = new TH1F("hTotal", "", 20, -10, 20);
  TH1F *hPass = new TH1F("hPass", " ", 20, -10, 20);

  for (int kk=0; kk<nentriesD;  kk++){
    tt->GetEntry(kk);
    if (kk % 50000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;
    evtType = tt->GetLeaf("fEvtHdr.fEvtType")->GetValue(); 
    hpdelta_cut = hdelta > -10 && hdelta < 10 && pdelta > -10 && pdelta < 20 ;
    epievent_cut = paeronpe > 0. && pcalepr < 0.2 && pcaletot < 0.5 && hcaletot > 0.6 && hcaletot < 2.0 && hpdelta_cut  && hcernpe > 0.;
    event_cut = epievent_cut;


    if (epievent_cut) {
      SHMSpartMass = 0.1395704; // pion mass in GeV/c^2 

      //  ---------------cointime calculation ------------------
      DeltaHMSpathLength = 12.462*HgtrTh + 0.1138*HgtrTh*HgtrX - 0.0154*HgtrX - 72.292*HgtrTh*HgtrTh - 0.0000544*HgtrX*HgtrX - 116.52*HgtrPh*HgtrPh;               
      PgtrBetaCalc = PgtrP/sqrt(PgtrP*PgtrP + SHMSpartMass*SHMSpartMass);        
      HgtrBetaCalc = HgtrP/sqrt(HgtrP*HgtrP + HMSpartMass*HMSpartMass);          

      SHMScoinCorr = SHMScentralPathLen / (speedOfLight*PgtrBetaCalc) + (SHMSpathLength - SHMScentralPathLen) / (speedOfLight*PgtrBetaCalc) + (PhodoStartTimeMean - PhodfpHitsTime);                                                                   
      HMScoinCorr = HMScentralPathLen / (speedOfLight*HgtrBetaCalc) + DeltaHMSpathLength / (speedOfLight*HgtrBetaCalc) + (HhodoStartTimeMean - HhodfpHitsTime);      

      SHMScoinCorr = SHMScentralPathLen / (speedOfLight*PgtrBetaCalc) + (SHMSpathLength - SHMScentralPathLen) / (speedOfLight*PgtrBetaCalc) + (PhodoStartTimeMean - PhodfpHitsTime);                                                                   
      HMScoinCorr = HMScentralPathLen / (speedOfLight*HgtrBetaCalc) + DeltaHMSpathLength / (speedOfLight*HgtrBetaCalc) + (HhodoStartTimeMean - HhodfpHitsTime);      

      SHMScorrCoinTimeROC1 = (TcoinpTRIG1_ROC1_tdcTimeRaw*0.1 - SHMScoinCorr) - (TcoinpTRIG4_ROC1_tdcTimeRaw*0.1 - HMScoinCorr) - pOffset; // 0.1 to convert to ns 

      SHMScorrCoinTimeROC2 = (TcoinpTRIG1_ROC2_tdcTimeRaw*0.1 - SHMScoinCorr) - (TcoinpTRIG4_ROC2_tdcTimeRaw*0.1 - HMScoinCorr) - pOffset; 
      h1_epi_PcointimeROC2->Fill(SHMScorrCoinTimeROC2);    
            
    }
  }

  Int_t bin_max = h1_epi_PcointimeROC2->GetMaximumBin();
  Double_t max_value = h1_epi_PcointimeROC2->GetBinCenter(bin_max);

  Int_t sh1=max_value + 3*4 -1.5;
  Int_t sh2=max_value + 4*4 +2.;
  Int_t sh3=max_value - 1*4 +1.5;
  Int_t sh4=max_value - 3*4 -1.5;
  Double_t acc_scale_fac = -3.0/((sh2-sh1)+(sh3-sh4));

  for (int kk=0; kk<nentriesD;  kk++){
    tt->GetEntry(kk);
    if (kk % 50000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;
    evtType = tt->GetLeaf("fEvtHdr.fEvtType")->GetValue(); 
    hpdelta_cut = hdelta > -10 && hdelta < 10 && pdelta > -10 && pdelta < 20 ;
    //  epievent_cut = paeronpe > 0. && pcalepr < 0.2 && pcaletot < 0.5 && hcaletot > 0.6 && hcaletot < 2.0 && hpdelta_cut  && hcernpe > 0.;
    epievent_cut =hdelta>-10&&hdelta<10;// && pcalepr < 0.2 && pcaletot < 0.5 && hcaletot > 0.6 && hcaletot < 2.0 && hpdelta_cut  && hcernpe > 0.;

    event_cut = epievent_cut;


    if (epievent_cut) {
      SHMSpartMass = 0.1395704; // pion mass in GeV/c^2 
      cntsepi++;
      //  ---------------cointime calculation ------------------
      DeltaHMSpathLength = 12.462*HgtrTh + 0.1138*HgtrTh*HgtrX - 0.0154*HgtrX - 72.292*HgtrTh*HgtrTh - 0.0000544*HgtrX*HgtrX - 116.52*HgtrPh*HgtrPh;               
      PgtrBetaCalc = PgtrP/sqrt(PgtrP*PgtrP + SHMSpartMass*SHMSpartMass);        
      HgtrBetaCalc = HgtrP/sqrt(HgtrP*HgtrP + HMSpartMass*HMSpartMass);          

      SHMScoinCorr = SHMScentralPathLen / (speedOfLight*PgtrBetaCalc) + (SHMSpathLength - SHMScentralPathLen) / (speedOfLight*PgtrBetaCalc) + (PhodoStartTimeMean - PhodfpHitsTime);                                                                   
      HMScoinCorr = HMScentralPathLen / (speedOfLight*HgtrBetaCalc) + DeltaHMSpathLength / (speedOfLight*HgtrBetaCalc) + (HhodoStartTimeMean - HhodfpHitsTime);      

      SHMScoinCorr = SHMScentralPathLen / (speedOfLight*PgtrBetaCalc) + (SHMSpathLength - SHMScentralPathLen) / (speedOfLight*PgtrBetaCalc) + (PhodoStartTimeMean - PhodfpHitsTime);                                                                   
      HMScoinCorr = HMScentralPathLen / (speedOfLight*HgtrBetaCalc) + DeltaHMSpathLength / (speedOfLight*HgtrBetaCalc) + (HhodoStartTimeMean - HhodfpHitsTime);      

      SHMScorrCoinTimeROC1 = (TcoinpTRIG1_ROC1_tdcTimeRaw*0.1 - SHMScoinCorr) - (TcoinpTRIG4_ROC1_tdcTimeRaw*0.1 - HMScoinCorr) - pOffset; // 0.1 to convert to ns 

      SHMScorrCoinTimeROC2 = (TcoinpTRIG1_ROC2_tdcTimeRaw*0.1 - SHMScoinCorr) - (TcoinpTRIG4_ROC2_tdcTimeRaw*0.1 - HMScoinCorr) - pOffset; 

      ctime_cut = SHMScorrCoinTimeROC2 > (max_value -0.6 ) && SHMScorrCoinTimeROC2 < (max_value + 0.6);
      accR_cut = SHMScorrCoinTimeROC2 > sh1 && SHMScorrCoinTimeROC2 < sh2 ;
      accL_cut = SHMScorrCoinTimeROC2 > sh4 && SHMScorrCoinTimeROC2 < sh3 ;
      acc_cut = accR_cut || accL_cut ; 



     
      if  (    pbeta>0.8&&pbeta<1.3&&pdelta<20&&pdelta>-10&&paeronpe>2)//&&pcaletot>0.15&&pcaletot<0.45) 

	{
	  hTotal->Fill(pdelta);
	}
	      
      if (      pbeta>0.8&&pbeta<1.3&&pdelta<20&&pdelta>-10&&paeronpe>2&&pcernpe>0.2)// &&pcaletot>0.15&&pcaletot<0.45 &&pcernpe > 0.2)
	{
	  hPass->Fill(pdelta);
	}
      if  (ctime_cut){
	h1_epi_PcointimeROC2_C->Fill(SHMScorrCoinTimeROC2); 
      }
	  
      else if (acc_cut){
	h1_epi_PcointimeROC2_B->Fill(SHMScorrCoinTimeROC2);    
      }
    }
  }  
  //***********************************************************************
 
  TCanvas *c5 =new TCanvas("c5","",1000,1000);
  TCanvas *c6 =new TCanvas("c6","",1000,1000);
  c5->Divide(2,2);
  c5->cd(1);
  h1_epi_PcointimeROC2_C->Draw();
  // h1_epi_PcointimeROC2_B->Draw("same");
 
  cout<<"Roc2_C Events ="<<h1_epi_PcointimeROC2_C->GetEntries()<<endl;
  cout<<"ROC2_B Events ="<<h1_epi_PcointimeROC2_B->GetEntries()<<endl;
  c5->cd(2); 
  h1_epi_PcointimeROC2_B->Draw();
  c5->cd(3);
  h1_epi_PcointimeROC2_C->Draw();
  h1_epi_PcointimeROC2_B->Draw("same");
  h1_epi_PcointimeROC2_B->SetLineColor(2);
  TH2F *h = new TH2F("h","EFFICIENCY vs SHMS DELTA pi+ 3435 3.37",20,-10,20,100,0,1);
  c6->cd();
  c6->SetGrid();
  // h->GetYaxis()->SetRangeUser(0,1.2);
  h->Draw("");
 
  cout<<"hTotal nEntries ="<<hTotal->GetEntries()<<endl;
  
  cout<<"hPass nEntries ="<<hPass->GetEntries()<<endl;
  pEff = new TEfficiency(*hPass, *hTotal);
  cout << "===================================================================" <<endl;
  Double_t Should = hTotal->GetEntries();
  Double_t Did = hPass->GetEntries();
  if(Did == 0)
    cout << "SHMS hgcer efficiency: "<< 0 <<" %"<<endl;
  else
    cout << "SHMS hgcer efficiency: "<< Did*100/Should <<" %"<<endl; 
  cout<<"======================================================================" <<endl;
  
  pEff->Draw("same");

  //pEff->Print("/w/hallc-scifs17exp/c-sidis18/SIDISAnalyzer/scripts/CER/PDF/3560_Eff_vs_Delta.pdf");
}

