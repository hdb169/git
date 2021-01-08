//this adds 2 gaus and 1 pol 1 functions and fits the shape, prints parameters.
void plot_aerofit_eff(){

  // gStyle->SetOptStat(1000011);//int
   gStyle->SetOptFit(111);
   gStyle->SetOptStat(0);

    //#include "bin7808.h"
 										  
  TFile *f1 = new TFile("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/kin33_34/kin7808/root_tree_new/charge_norm_data_hist_7808.root");//pip
  TFile *f2 = new TFile("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/kin33_34/kin7808/root_tree_new/charge_norm_data_hist_7796.root");//pim

											  
  TH1D * haero_pos = (TH1D*)f1->Get("aero_1dc");//data
  TH1D * haero_neg = (TH1D*)f2->Get("aero_1dc");//data

 

  TCanvas *c1 = new TCanvas("c1","c1",1000, 500);
  c1->Divide(2,1);
  //num pos
  c1->cd(1);//gPad->SetGridx();gPad->SetGridy();
  haero_pos->Draw("hist");
  haero_pos->SetLineWidth(2);
  haero_pos->GetXaxis()->SetTitle("P.aero.npeSum");
  haero_pos->GetYaxis()->SetTitle("Counts");
  haero_pos->SetTitle("P.Aero.npeSum: Pos: 7808 : +3.46 GeV");
  
  TF1 * g1 = new TF1("g1", "gaus(0)+gaus(3)+pol1(6)", 0,50);
  Double_t parpos[] = {638, 11, 4.2, 38, 23, 7.35, 28.71, -0.589};
  g1->SetParameters(parpos);  
  haero_pos->Fit(g1,"R","",0,50);
  g1->Draw("same");
  double efffitpos  =   g1->Integral(4,50)/g1->Integral(0,50);
  double effdatapos =  haero_pos->Integral(haero_pos->FindBin(4),haero_pos->FindBin(50))/haero_pos->Integral(haero_pos->FindBin(0),haero_pos->FindBin(50));
 
  cout<< "Eff pos ="<< efffitpos<<"  "<<effdatapos<<endl;
  cout<<"  "<<endl;

 //num neg
  c1->cd(2);//gPad->SetGridx();gPad->SetGridy();
  haero_neg->Draw("hist");
  haero_neg->SetLineWidth(2);
  haero_neg->GetXaxis()->SetTitle("P.aero.npeSum");
  haero_neg->GetYaxis()->SetTitle("Counts");
  haero_neg->SetTitle("P.Aero.npeSum: Neg: 7796 : -3.46 GeV");

  TF1 * g2 = new TF1("g2", "gaus(0)+gaus(3)+pol1(6)", 0,50);
  Double_t parneg[] = {638, 11, 4.2, 38, 23, 7.35, 28.71, -0.589};
  g2->SetParameters(parneg);  
  haero_neg->Fit(g2,"R","",0,50);
  g2->Draw("same");
  double efffitneg  =   g2->Integral(4,50)/g2->Integral(0,50);
  double effdataneg =  haero_neg->Integral(haero_neg->FindBin(4),haero_neg->FindBin(50))/haero_neg->Integral(haero_neg->FindBin(0),haero_neg->FindBin(50));
 
  cout<< "Eff neg ="<< efffitneg<<"  "<<effdataneg<<endl;
  
  


  c1->SaveAs("pdf/plots_7808_7796.pdf");

  

}
 








