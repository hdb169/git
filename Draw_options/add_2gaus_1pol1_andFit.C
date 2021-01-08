//void add_3hists_z4039(Int_t run11pos, Int_t run01pos, Int_t run012pos, Int_t run11neg, Int_t run01neg, Int_t run013neg){

void plot_aerofit_eff(){

  // gStyle->SetOptStat(1000011);//int
   gStyle->SetOptFit(111);
   gStyle->SetOptStat(0);

    //#include "bin7808.h"
 										  
  TFile *f1 = new TFile("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/kin33_34/kin7808/root_tree_new/charge_norm_data_hist_7808.root");//pip
  TFile *f2 = new TFile("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/kin33_34/kin7808/root_tree_new/charge_norm_data_hist_7808.root");//pip

  TFile *f3 = new TFile("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/kin33_34/kin7808/root_tree_new/charge_norm_data_hist_7796.root");//pim
  TFile *f4 = new TFile("/home/hdbhatt/Desktop/data_simc/rad_dat_simc/kin33_34/kin7808/root_tree_new/charge_norm_data_hist_7796.root");//pim

											  
  TH1D * haero_pos_num = (TH1D*)f1->Get("aero_1dc");//data
  TH1D * haero_pos_den = (TH1D*)f2->Get("aero_1dc");//data

  TH1D * haero_neg_num = (TH1D*)f3->Get("aero_1dc");//data
  TH1D * haero_neg_den = (TH1D*)f4->Get("aero_1dc");//data

 

  TCanvas *c1 = new TCanvas("c1","c1",1000, 500);
  c1->Divide(2,1);
  //num pos
  c1->cd(1);//gPad->SetGridx();gPad->SetGridy();
  haero_pos_num->Draw("hist");
  haero_pos_num->SetLineWidth(2);
  haero_pos_num->GetXaxis()->SetTitle("P.aero.npeSum");
  haero_pos_num->GetYaxis()->SetTitle("Counts");
  haero_pos_num->SetTitle("P.Aero.npe: Pos Numerator: 7808 : +3.46 GeV");
  
  TF1 * g1 = new TF1("g1", "gaus(0)+gaus(3)+pol1(6)", 0,50);
  Double_t parpos[] = {638, 11, 4.2, 38, 23, 7.35, 28.71, -0.589};
  g1->SetParameters(parpos);  
  haero_pos_num->Fit(g1,"R","",0,50);
  g1->Draw("same");
  double efffitpos  =   g1->Integral(4,50)/g1->Integral(0,50);
  double effdatapos =  haero_pos_num->Integral(haero_pos_num->FindBin(4),haero_pos_num->FindBin(50))/haero_pos_num->Integral(haero_pos_num->FindBin(0),haero_pos_num->FindBin(50));
 
  cout<< "Eff pos ="<< efffitpos<<"  "<<effdatapos<<endl;
  cout<<"  "<<endl;

 //num neg
  c1->cd(2);//gPad->SetGridx();gPad->SetGridy();
  haero_neg_num->Draw("hist");
  haero_neg_num->SetLineWidth(2);
  haero_neg_num->GetXaxis()->SetTitle("P.aero.npeSum");
  haero_neg_num->GetYaxis()->SetTitle("Counts");
  haero_neg_num->SetTitle("P.Aero.npe: Neg Numerator: 7796 : -3.46 GeV");

  TF1 * g2 = new TF1("g2", "gaus(0)+gaus(3)+pol1(6)", 0,50);
  Double_t parneg[] = {638, 11, 4.2, 38, 23, 7.35, 28.71, -0.589};
  g2->SetParameters(parneg);  
  haero_neg_num->Fit(g2,"R","",0,50);
  g2->Draw("same");
  double efffitneg  =   g2->Integral(4,50)/g2->Integral(0,50);
  double effdataneg =  haero_neg_num->Integral(haero_neg_num->FindBin(4),haero_neg_num->FindBin(50))/haero_neg_num->Integral(haero_neg_num->FindBin(0),haero_neg_num->FindBin(50));
 
  cout<< "Eff neg ="<< efffitneg<<"  "<<effdataneg<<endl;
  
  


  c1->SaveAs("pdf/plots_7808_7796.pdf");

  

}
 








