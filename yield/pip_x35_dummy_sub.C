#include "header.h"
#include "bin.h"
void pip_x35_dummy_sub() {
  gStyle->SetOptStat(1111111);
  TFile *f1 = new TFile("root/pip_x35_z70.root");//, "READ");
  TFile *f2 = new TFile("root/pip_x35_z60.root");//, "READ");
  TFile *f3 = new TFile("root/pip_x35_z50.root");//, "READ");
  TFile *f4 = new TFile("root/pip_x35_z40.root");//, "READ");
  TFile *f11 = new TFile("root/pip_x35_z70_al.root");//, "READ");
  TFile *f22 = new TFile("root/pip_x35_z60_al.root");//, "READ");
  TFile *f33 = new TFile("root/pip_x35_z50_al.root");//, "READ");
  TFile *f44 = new TFile("root/pip_x35_z40_al.root");//, "READ");

  Double_t data_factor = 0.244;// dummy factor  fixed for D2-Al 

  Double_t tot_q1 = 101.235;//D2 charge in 4 z settings
  Double_t tot_q2 = 93.062;
  Double_t tot_q3 = 61.152;
  Double_t tot_q4 = 122.288;

  //for dummy we need additional scaling by 0.244 due to the window thickness
  Double_t tot_q11 = 143.441 /data_factor;//Al charge in 4 settings
  Double_t tot_q22 = 138.017 /data_factor;
  Double_t tot_q33 = 94.143 /data_factor;
  Double_t tot_q44 = 193.051 /data_factor;


  TFile *f = new TFile("root/pip_x35_z_70_60_50_40.root", "RECREATE");
  /////////////////////////////////////////////////D2 Target///////////////////////////////////////////////////////
  TCanvas *c10 = new TCanvas("c10", "data_pip_x35",1600,1200);  
  c10->Divide(4,2);

  c10->cd(1);gPad->SetGrid();
  TH1D *h1 = (TH1D*)f1->Get("h_dataz_final");
  TH1D *new_h1 = new TH1D ("new_h1", "new_h1", binz, loz, hiz);
  h1->Scale(1/tot_q1);
  new_h1 = (TH1D*)h1->Clone();
  new_h1->Draw("");
  new_h1->SetLineColor(kBlue);
  new_h1->SetTitle("D2_z70_counts/charge");

  c10->cd(2);gPad->SetGrid();
  TH1D *h2 = (TH1D*)f2->Get("h_dataz_final");
  TH1D *new_h2 = new TH1D ("new_h2", "new_h2", binz, loz, hiz);
  h2->Scale(1/tot_q2);
  new_h2 = (TH1D*)h2->Clone();
  new_h2->Draw("");
  new_h2->SetLineColor(kBlue);
  new_h2->SetTitle("D2_z60_counts/charge");

  c10->cd(3);gPad->SetGrid();
  TH1D *h3 = (TH1D*)f3->Get("h_dataz_final");
  TH1D *new_h3 = new TH1D ("new_h3", "new_h3", binz, loz, hiz); 
  h3->Scale(1/tot_q3);
  new_h3 = (TH1D*)h3->Clone();
  new_h3->Draw("e,p1");
  new_h3->SetLineColor(kBlue);
  new_h3->SetTitle("D2_z50_counts/charge");


  c10->cd(4);gPad->SetGrid();
  TH1D *h4 = (TH1D*)f4->Get("h_dataz_final");
  TH1D *new_h4 = new TH1D ("new_h4", "new_h4", binz, loz, hiz);
  h4->Scale(1/tot_q4);
  new_h4=(TH1D*)h4->Clone();
  new_h4->Draw("e,p1");
  new_h4->SetLineColor(kBlue);
  new_h4->SetTitle("D2_z40_counts/charge");

  /////////////////////////////////////////////////////AL DUMMY TARGET//////////////////////
  c10->cd(5);gPad->SetGrid();

  TH1D *h11 = (TH1D*)f11->Get("h_dataz_final");
  TH1D *new_h11 = new TH1D ("new_h11", "new_h11", binz, loz, hiz);
  h11->Scale(1/tot_q11);
  new_h11= (TH1D*)h11->Clone();
  new_h11->Draw("e,p1");
  new_h11->SetLineColor(kBlue);
  new_h11->SetTitle("Al_z70_counts/charge");
 

  c10->cd(6);gPad->SetGrid();
  TH1D *h22 = (TH1D*)f22->Get("h_dataz_final");
  TH1D *new_h22 = new TH1D ("new_h22", "new_h22", binz, loz, hiz);
  h22->Scale(1/tot_q22);
  new_h22= (TH1D*)h22->Clone();
  new_h22->Draw("e,p1");
  new_h22->SetLineColor(kBlue);
  new_h22->SetTitle("Al_z60_counts/charge");
  
  c10->cd(7);gPad->SetGrid();

  TH1D *h33 = (TH1D*)f33->Get("h_dataz_final");
  TH1D *new_h33 = new TH1D ("new_h33", "new_h33", binz, loz, hiz);
  h33->Scale(1/tot_q33);
  new_h33= (TH1D*)h33->Clone();
  new_h33->Draw("e,p1");
  new_h33->SetLineColor(kBlue);
  new_h33->SetTitle("Al_z50_counts/charge");
  

  c10->cd(8);gPad->SetGrid();
  TH1D *h44 = (TH1D*)f44->Get("h_dataz_final");
  TH1D *new_h44 = new TH1D ("new_h44", "new_h44", binz, loz, hiz);
  h44->Scale(1/tot_q44);
  new_h44= (TH1D*)h44->Clone();
  new_h44->Draw("e,p1");
  new_h44->SetLineColor(kBlue);
  new_h44->SetTitle("Al_z40_counts/charge");
  c10->SaveAs("pdf/pip_x35_d2_plots.pdf");

  /////////////////////////////////////////////////////AL DUMMY TARGET DONE//////////////////////
  
  cout <<"total bins in z = "<< binz<< endl;
  cout <<"charge (q1) = "<<tot_q1<< endl;
  cout <<"charge (q2) = "<<tot_q2<<endl;
  cout <<"charge (q3) = "<<tot_q3<< endl;
  cout <<"charge (q4) = "<<tot_q4<< endl;
  cout <<"==========================="<< endl;
  cout <<"Eff. charge (q11)/data_dfactor = "<<tot_q11<< "  "<< "charge(q11) = " <<tot_q11*data_factor<<endl;
  cout <<"Eff. charge (q22)/data_dfactor = "<<tot_q22<< "  "<< "charge(q22) = " <<tot_q22*data_factor<<endl;
  cout <<"Eff. charge (q33)/data_dfactor = "<<tot_q33<< "  "<< "charge(q33) = " <<tot_q33*data_factor<<endl;
  cout <<"Eff. charge (q44)/data_dfactor = "<<tot_q44<< "  "<< "charge(q44) = " <<tot_q44*data_factor<<endl;
  
//////////////////////////////////////////////////YIELD  D2- YIELD DUMMY TARGET PLOT /////////////////////////////////////////

  TH1D *pip_x35_z70 = new TH1D ("pip_x35_z70", "x35_z70_D2-Al", binz, loz, hiz);
  TH1D *pip_x35_z60 = new TH1D ("pip_x35_z60", "x35_z60_D2-Al", binz, loz, hiz);
  TH1D *pip_x35_z50 = new TH1D ("pip_x35_z50", "x35_z50_D2-Al", binz, loz, hiz);
  TH1D *pip_x35_z40 = new TH1D ("pip_x35_z40", "x35_z40_D2-Al", binz, loz, hiz);

  TCanvas *c11 = new TCanvas("c11", "c11", 1600,1200);
  c11->Divide(2,2);

  c11->cd(1);
  pip_x35_z70->Add(new_h1,new_h11,1.0,-1.0);
  if(!(pip_x35_z70->GetSumw2N()>0)) pip_x35_z70->Sumw2(kTRUE);
  pip_x35_z70->Draw("e,p1");
  pip_x35_z70->SetLineColor(kBlue);
  pip_x35_z70->SetLineWidth(2);
  pip_x35_z70->SetTitle("Clean Yield for pip_x35_z70");

  c11->cd(2);
  pip_x35_z60->Add(new_h2,new_h22,1.0,-1.0);
  if(!(pip_x35_z60->GetSumw2N()>0)) pip_x35_z60->Sumw2(kTRUE);
  pip_x35_z60->Draw("e,p1");
  pip_x35_z60->SetLineWidth(2);
  pip_x35_z60->SetLineColor(kBlue);
  pip_x35_z60->SetTitle("Clean Yield for pip_x35_z60");

  c11->cd(3);
  pip_x35_z50->Add(new_h3,new_h33,1.0,-1.0);
  if(!(pip_x35_z50->GetSumw2N()>0)) pip_x35_z50->Sumw2(kTRUE);
  pip_x35_z50->Draw("e,p1");
  pip_x35_z50->SetLineWidth(2);
  pip_x35_z50->SetLineColor(kBlue);
  pip_x35_z50->SetTitle("Clean Yield  for pip_x35_z50");


  c11->cd(4);
  pip_x35_z40->Add(new_h4,new_h44,1.0,-1.0);
  if(!(pip_x35_z40->GetSumw2N()>0)) pip_x35_z40->Sumw2(kTRUE);
  pip_x35_z40->Draw("e,p1");
  pip_x35_z40->SetLineWidth(2);
  pip_x35_z40->SetLineColor(kBlue);
  pip_x35_z40->SetTitle("Clean Yield for pip_x35_z40");

  pip_x35_z70->Write();
  pip_x35_z60->Write();
  pip_x35_z50->Write();
  pip_x35_z40->Write();
  c11->SaveAs("pdf/pip_x35_al_plots.pdf");


  //////////////Done for "pip_x35"/////////////

}

