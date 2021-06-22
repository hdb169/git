void plot_ptsin_ptcos(){
  gStyle->SetOptStat(1000111);
  TH1F *hist_ptsinphi = new TH1F("hist_ptsinphi","pt sin(phi) (GeV);pt sinc(phi) (GeV);Entries",100,-1.5,1.5);
  TH1F *hist_ptcosphi = new TH1F("hist_ptcosphi","pt cos(phi) (GeV);pt cos(phi) (GeV);Entries",100,-1.5,1.5);
  TH1F *hist_pt = new TH1F("hist_pt","pt (GeV);pt(GeV);Entries",100,-1,3);
  TH2F *hist_ptsin_ptcos = new TH2F("hist_ptsin_ptcos","pt sinphi vs pt cosphi (GeV);ptcosphi (GeV);ptsinphi (GeV)",100,-1,1,100,-1,1);

   TFile *f1 = new TFile("/home/hdbhatt/ROOTfiles/hgc/coin_replay_production_7672_100000.root");
   TFile *f2 = new TFile("/home/hdbhatt/efficiency/hgcer/ptsincos/pt_sincos.root","RECREATE");

  //TFile *f1 = new TFile("/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/pt/coin_replay_production_7777_-1.root");
  TTree * tt = (TTree*)f1->Get("T");
  Long64_t nentriesD = tt->GetEntries();
  double paero,pbeta,pdelta,hdelta,ctime,hcernpeSum,hdipole,pdipole,hbeta,pcal,hcal,hcernpe,phi,theta,mom,pt,ptsinphi,ptcosphi;
  
  std::vector<double> pt_vec,pt_vec_err,phi_vec,err_vec;

    
  tt->SetBranchAddress("P.aero.npeSum", &paero);
  tt->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
  tt->SetBranchAddress("P.gtr.dp", &pdelta);         
  tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
  tt->SetBranchAddress("H.cer.npeSum", &hcernpeSum); 
  tt->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);
  tt->SetBranchAddress("P.dc.InsideDipoleExit",&pdipole);
  tt->SetBranchAddress("H.gtr.beta", &hbeta); 
  tt->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
  tt->SetBranchAddress("P.aero.npeSum", &paero);
  tt->SetBranchAddress("P.cal.etottracknorm", &pcal);
  tt->SetBranchAddress("H.cal.etottracknorm", &hcal);
  tt->SetBranchAddress("H.cer.npe", &hcernpe);
  tt->SetBranchAddress("P.kin.secondary.ph_xq", &phi);
  tt->SetBranchAddress("P.kin.secondary.th_xq", &theta);
  tt->SetBranchAddress("P.gtr.p", &mom);                                                                            
  tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);                                                                            

  

  for (int kk=0; kk<nentriesD;  kk++){
    tt->GetEntry(kk);


    if(pdelta>-10&&pdelta<20&&hdelta>-8&&hdelta<8&&pcal<0.7&&hcal>0.75&&hbeta>0.5&&pbeta>0.5&&paero>4&&ctime>42&&ctime<45){
      pt=mom*sin(theta);
      pt_vec.push_back(pt);
      phi_vec.push_back(phi);
      err_vec.push_back(0);
      ptsinphi=pt*sin(phi);
      ptcosphi=pt*cos(phi);
      hist_pt->Fill(pt);
      hist_ptsinphi->Fill(ptsinphi);
      hist_ptcosphi->Fill(ptcosphi);
      hist_ptsin_ptcos->Fill(ptcosphi,ptsinphi);
    }
  }

  int n_counts = (int) pt_vec.size();
  double pt_arr[n_counts],phi_arr[n_counts], err_arr[n_counts];
  cout<<n_counts<<endl;
  std::copy(pt_vec.begin(),pt_vec.end(),pt_arr);
  std::copy(phi_vec.begin(),phi_vec.end(),phi_arr);
  std::copy(err_vec.begin(),err_vec.end(),err_arr);


 
  
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(2,2);
  c1->cd(1);gPad->SetLogy();
  hist_pt->Draw();gPad->SetGrid();
  hist_pt->Draw("hist");
  hist_pt->SetLineWidth(2);
  hist_pt->GetXaxis()->CenterTitle();
  hist_pt->GetYaxis()->CenterTitle();
  hist_pt->Write();

  c1->cd(2);gPad->SetLogz();gPad->SetGrid();
  hist_ptsin_ptcos->Draw("colz");
  hist_ptsin_ptcos->Draw("hist");
  hist_ptsin_ptcos->GetXaxis()->CenterTitle();
  hist_ptsin_ptcos->GetYaxis()->CenterTitle();
  hist_ptsin_ptcos->Write();

  
  c1->cd(3);gPad->SetGrid();
  hist_ptsinphi->Draw();
  hist_ptsinphi->Draw("hist");
  hist_ptsinphi->SetLineWidth(2);
  hist_ptsinphi->GetXaxis()->CenterTitle();
  hist_ptsinphi->GetYaxis()->CenterTitle();
  hist_ptsinphi->Write();
  
  c1->cd(4);gPad->SetGrid();
  hist_ptcosphi->Draw();
  hist_ptcosphi->Draw("hist");
  hist_ptcosphi->SetLineWidth(2);
  hist_ptcosphi->GetXaxis()->CenterTitle();
  hist_ptcosphi->GetYaxis()->CenterTitle();
  hist_ptcosphi->Write();

  c1->SaveAs("hcer_0_1.pdf");

  
 TCanvas *c_ptpolar = new TCanvas("c_ptpolar","",800,800);
  TGraphPolar *g_ptpolar = new TGraphPolar(n_counts,phi_arr,pt_arr,err_arr,err_arr);
  g_ptpolar->Draw("p");
  g_ptpolar->SetMarkerColor(kRed);
  g_ptpolar->SetMarkerStyle(4);
  c_ptpolar->SaveAs("plorplot.pdf");
  g_ptpolar->Write();
  
 
}
