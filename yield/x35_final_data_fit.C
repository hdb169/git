//This will take the ratio of pi+ yield over pi- yield for 4 different z settings individually.
//I will add these 4 histograms to get the final one.


#include "header.h"
#include "bin.h"
void x35_final_data_fit() {
  double z[100];
  double Rd;
  double R_D[100];
  double ratio[100];
  double rd_ratio[100];
  ///for fit function for pi+/Pi- yield ratio abd Rd_measured////////////////////////


  for (int i = 0; i < 100; i++)//taking all int numbers from 0 t0 1
    {
      z[i] = i/100.0;//made each number 0.1, 0.2, 0.3, ..
    
      R_D[i] = pow((1.0-z[i]),0.083583)/pow((1.0+z[i]),1.9838);//Rd

      ratio[i]= (R_D[i]+4)/ (4*R_D[i]+1);//pi+/pi-
      // cout << z[i]<< endl;

      rd_ratio[i] = (4 - ratio [i]) / (ratio[i] - 1);//Rd_measured (4-R)/(R-1)


    }

  TGraph *gr1 = new TGraph(100, z, ratio);//to plot Yield ratio
  TGraph *gr2 = new TGraph(100, z, rd_ratio);//to plot Rd_measured


  ////////////////////////this for data,above is for simc//////////
  //gStyle->SetOptStat(111111);
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(1);
  gStyle->SetOptStat(0);

  TFile * f2 = new TFile("root/pip_x35_z_70_60_50_40.root");//pip---------------->f2  -----pi+
  TFile * f1 = new TFile("root/pim_x35_z_70_60_50_40.root");//pim---------------> f1  -----pi -
  TFile * f3 = new TFile("root/final_ratio_x35.root","RECREATE");


  TH1D *h_pip_x35_z70 = (TH1D*)f2->Get("pip_x35_z70");
  TH1D *h_pip_x35_z60 = (TH1D*)f2->Get("pip_x35_z60");
  TH1D *h_pip_x35_z50 = (TH1D*)f2->Get("pip_x35_z50");
  TH1D *h_pip_x35_z40 = (TH1D*)f2->Get("pip_x35_z40");

  TH1D *h_pim_x35_z70 = (TH1D*)f1->Get("pim_x35_z70");
  TH1D *h_pim_x35_z60 = (TH1D*)f1->Get("pim_x35_z60");
  TH1D *h_pim_x35_z50 = (TH1D*)f1->Get("pim_x35_z50");
  TH1D *h_pim_x35_z40 = (TH1D*)f1->Get("pim_x35_z40");


  TH1D *ratio_x35_z70 = new TH1D("ratio_x35_z70","ratio_x35_z70",binz,loz,hiz);
  TH1D *ratio_x35_z60 = new TH1D("ratio_x35_z60","ratio_x35_z60",binz,loz,hiz);
  TH1D *ratio_x35_z50 = new TH1D("ratio_x35_z50","ratio_x35_z50",binz,loz,hiz);
  TH1D *ratio_x35_z40 = new TH1D("ratio_x35_z40","ratio_x35_z40",binz,loz,hiz);


  //////////////////////////////////Ratio of Pi+/Pi Yield for different z settings////////////
  

  //////////////new trial////////////////
  TH1D *h1= new TH1D("h1","h1",binz, loz,hiz);
  TH1D *h2= new TH1D("h2","h2",binz, loz,hiz);
  TH1D *final_x35= new TH1D("final_x35","final_yield_ratio_x35",binz, loz,hiz);

  h1->Add(h_pip_x35_z70);
  h1->Add(h_pip_x35_z60);
  h1->Add(h_pip_x35_z50);
  h1->Add(h_pip_x35_z40);

  h2->Add(h_pim_x35_z70);
  h2->Add(h_pim_x35_z60);
  h2->Add(h_pim_x35_z50);
  h2->Add(h_pim_x35_z40);
  TCanvas *cc = new TCanvas ("cc", "Yield of pi + / Yield  of pi - ",1600,1200);
  final_x35->Divide(h1,h2);

  cc->Divide(1,1);
  cc->cd(1);
  // cc->cd(1);
  // h1->Draw();
  // cc->cd(2);
  // h2->Draw();
  cc->cd(1);
  final_x35->Draw();
  final_x35->Add(ratio_x35_z70);
  final_x35->Add(ratio_x35_z60);
  final_x35->Add(ratio_x35_z50);
  final_x35->Add(ratio_x35_z40);
  final_x35->Draw();
  if (!( final_x35->GetSumw2N() > 0))  final_x35->Sumw2(kTRUE);
  final_x35->SetTitle("Yield Ratio Pi+/Pi-, Q2=4.00 GeV2, x = 0.34, z = 0.7, 0.6, 0.5, 0.4");
  final_x35->GetXaxis()->SetTitle("z_hadron");
  final_x35->GetYaxis()->SetTitle("Yield of pi+/Pi-");
  final_x35->GetXaxis()->CenterTitle();
  final_x35->GetYaxis()->SetTitleFont(62);
  final_x35->GetYaxis()->SetTitleOffset(0.5);
  final_x35->GetYaxis()->SetTitleSize(0.042);
  final_x35->GetYaxis()->SetTitleOffset(1.2);
  final_x35->GetYaxis()->SetLabelSize(0.03);
  final_x35->GetYaxis()->SetLabelFont(62);
  final_x35->GetYaxis()->SetTitleFont(62);
  final_x35->GetXaxis()->SetTitleSize(0.05);
  final_x35->GetXaxis()->SetTitleFont(62);
  final_x35->GetXaxis()->SetTitleOffset(1.0);
  final_x35->GetXaxis()->SetLabelFont(62);
  final_x35->GetYaxis()->CenterTitle();
  final_x35->SetMarkerStyle(21);
  final_x35->SetMarkerSize(0.75);
  final_x35->SetMarkerColor(4);
  final_x35->Draw("");
  gPad->Update();
  final_x35->GetXaxis()->SetRangeUser(0.34,0.8);
  final_x35->GetYaxis()->SetRangeUser(-2,4);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(kRed); 
  gr1->Draw("same");
 

  ///////////////////////FOR RD_Meauserd Data rd= (4-R)/(R-1)

  cout<<final_x35->GetNbinsX()<<endl;
  TH1D *h_Rd_meas = new TH1D("h_Rd_meas", "h_Rd_meas", binz, loz,hiz);
  for (int i=1; i <= final_x35->GetNbinsX(); i++)

    {//good piece
      Rd = 4.0 - (final_x35->GetBinContent(i)); //Rd = (4.0 - final_x35->GetBinContent(i)) /(final_x35->GetBinContent(i) - 1.0 );
      Rd /= (final_x35->GetBinContent(i)) - 1.0;
      h_Rd_meas->SetBinContent(i, Rd);
    }



  TCanvas *cc1 = new TCanvas ("cc1", "Rd_Measured ",1600,1200);

  cc1->cd();
  if (!( h_Rd_meas->GetSumw2N() > 0))  h_Rd_meas->Sumw2(kTRUE);
  h_Rd_meas->SetTitle("Rd_measured, Q2=4.00 GeV2, x = 0.34, z = 0.7, 0.6, 0.5, 0.4");
  h_Rd_meas->GetXaxis()->SetTitle("z_hadron");
  h_Rd_meas->GetYaxis()->SetTitle("Rd_Measured");
  h_Rd_meas->GetXaxis()->CenterTitle();
  h_Rd_meas->GetYaxis()->SetTitleFont(62);
  h_Rd_meas->GetYaxis()->SetTitleOffset(0.5);
  h_Rd_meas->GetYaxis()->SetTitleSize(0.042);
  h_Rd_meas->GetYaxis()->SetTitleOffset(1.2);
  h_Rd_meas->GetYaxis()->SetLabelSize(0.03);
  h_Rd_meas->GetYaxis()->SetLabelFont(62);
  h_Rd_meas->GetYaxis()->SetTitleFont(62);
  h_Rd_meas->GetXaxis()->SetTitleSize(0.05);
  h_Rd_meas->GetXaxis()->SetTitleFont(62);
  h_Rd_meas->GetXaxis()->SetTitleOffset(1.0);
  h_Rd_meas->GetXaxis()->SetLabelFont(62);
  h_Rd_meas->GetYaxis()->CenterTitle();
  h_Rd_meas->SetMarkerStyle(21);
  h_Rd_meas->SetMarkerSize(0.75);
  h_Rd_meas->SetMarkerColor(4);
  h_Rd_meas->Draw("");
  gPad->Update();
  h_Rd_meas->GetXaxis()->SetRangeUser(0.34,0.8);
  h_Rd_meas->GetYaxis()->SetRangeUser(-40,40);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(kRed); 
  gr2->Draw("same");
 
  //////////////////////////Extra work///////////////
  TCanvas *cc2 = new TCanvas ("cc2", "Rd_Measured ",1600,1200);
  cc2->Divide(1,2);
  cc2->cd(1);
  final_x35->Draw("");
  gr1->Draw("same");

  cc2->cd(2);
  h_Rd_meas->Draw("");
  gr2->Draw("same");

  //////////////////////////////////Write /////////////////

  gr2->Write();
  gr2->Write();
  h_Rd_meas->Write();
  h_Rd_meas->Write();


  cc->SaveAs("pdf/final_yield_ratio_x35_Q2_4p00.pdf");
  cc1->SaveAs("pdf/final_Rd_measuared_x35_Q2_4p00.pdf");
  cc2->SaveAs("pdf/final_plots_x34.pdf");

}
 


















