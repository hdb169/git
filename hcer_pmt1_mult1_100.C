void hcer_pmt1_mult1_100(){
  gStyle->SetOptStat(111);
  gStyle->SetPaintTextFormat("5.4g");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(0.06);
  gStyle->SetTitleFont(40);
  gStyle->SetTitleYOffset(1.1);
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleXSize(0.05);
  gStyle->SetLabelFont(40,"X");
  gStyle->SetLabelFont(40,"Y");
  gStyle->SetTitleFont(40,"X");
  gStyle->SetTitleFont(40,"Y");
  gStyle->SetLabelSize(0.034,"X");
  gStyle->SetLabelSize(0.034,"Y");
  gStyle->SetPaperSize(18,22);
  gStyle->SetAxisColor(17);

  // auto f1 = new TFile("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/old_100.root");
  // auto f2 = new TFile("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/new_100.root");

  auto f1 = new TFile("/home/hdbhatt/Desktop/analysis/ROOTfiles/old_100.root");
  auto f2 = new TFile("/home/hdbhatt/Desktop/analysis/ROOTfiles/new_100.root");


  TTree *t1 = (TTree *)f1->Get("T");
  TTree *t2 = (TTree *)f2->Get("T");


  TH1F *h1 = new TH1F("h1","Time Pmt1 Old Mult1 100ns", 250, 60, 160);
  TH1F *h2 = new TH1F("h2","Time Pmt1 cal del Old Mult1 100ns", 250, 60, 160);
  TH2F *h3 = new TH2F("h3","Amp vs Time Pmt1 Old Mult1 100ns", 250, 60, 160, 620, -25, 1000); 
  TH2F *h4 = new TH2F("h4","Amp vs Time Pmt1 cal del Old Mult1 100ns", 250, 60, 160, 620, -25, 1000);
  TH1F *h5 = new TH1F("h5","Time Pmt1 New Mult1 100ns", 250, 60, 160);
  TH1F *h6 = new TH1F("h6","Time Pmt1 cal del New Mult1 100ns", 250, 60, 160);
  TH2F *h7 = new TH2F("h7","Amp vs Time Pmt1 New Mult1 100ns", 250, 60, 160, 620, -25, 1000);
  TH2F *h8 = new TH2F("h8","Amp vs Time Pmt1 cal del New Mult1 100ns", 250, 60, 160, 620, -25, 1000);


  t1->Draw("H.cer.goodAdcTdcDiffTime[0]>>h1","H.cer.goodAdcMult[0]==1");
  t1->Draw("H.cer.goodAdcTdcDiffTime[0]>>h2","H.cer.goodAdcMult[0]==1 && H.cal.etottracknorm> 0.8 && H.cal.etottracknorm < 1.2 && H.gtr.dp >-10 && H.gtr.dp <10");
  t1->Draw("H.cer.goodAdcPulseAmp[0]:H.cer.goodAdcTdcDiffTime[0]>>h3","H.cer.goodAdcMult[0]==1");
  t1->Draw("H.cer.goodAdcPulseAmp[0]:H.cer.goodAdcTdcDiffTime[0]>>h4","H.cer.goodAdcMult[0]==1 && H.cal.etottracknorm> 0.8 && H.cal.etottracknorm < 1.2 && H.gtr.dp >-10 && H.gtr.dp <10 ");
  t2->Draw("H.cer.goodAdcTdcDiffTime[0]>>h5","H.cer.goodAdcMult[0]==1");
  t2->Draw("H.cer.goodAdcTdcDiffTime[0]>>h6","H.cer.goodAdcMult[0]==1  && H.cal.etottracknorm> 0.8 && H.cal.etottracknorm < 1.2 && H.gtr.dp >-10 && H.gtr.dp <10 ");
  t2->Draw("H.cer.goodAdcPulseAmp[0]:H.cer.goodAdcTdcDiffTime[0]>>h7","H.cer.goodAdcMult[0]==1");
  t2->Draw("H.cer.goodAdcPulseAmp[0]:H.cer.goodAdcTdcDiffTime[0]>>h8","H.cer.goodAdcMult[0]==1 && H.cal.etottracknorm> 0.8 && H.cal.etottracknorm < 1.2 && H.gtr.dp >-10 && H.gtr.dp <10 ");
  

  TCanvas *c1 = new TCanvas ("c1", "c1", 1000, 1000);
  c1->Divide(1,3);

  c1->cd(1);gPad->SetLogy();gPad->SetGrid();
  h1->Draw();
  h1->GetXaxis()->SetTitle("H.cer.goodAdcPulseTime PMT1");
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->SetTitle("Counts");
  h1->GetYaxis()->CenterTitle();
  h2->Draw("same");
  h2->SetLineColor(kRed);


  c1->cd(2);gPad->SetLogz();gPad->SetGrid();gPad->SetLogy();
  h3->Draw("colz");
  h3->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime  PMT1");
  h3->GetXaxis()->CenterTitle();
  h3->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h3->GetYaxis()->CenterTitle();


  c1->cd(3);gPad->SetLogz();gPad->SetGrid();gPad->SetLogy();

  h4->Draw("colz");
  h4->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime  PMT1");
  h4->GetXaxis()->CenterTitle();
  h4->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h4->GetYaxis()->CenterTitle();

  c1->SaveAs("pdf/logy_hcer_pmt1_mult1_100_old.pdf");
  delete c1;
  
  TCanvas *c2 = new TCanvas ("c2", "c2", 1000, 1000);

  c2->Divide(1,3);
  c2->cd(1);gPad->SetLogy();gPad->SetGrid();
  h5->Draw();
  h5->GetXaxis()->SetTitle("H.cer.goodAdcPulseTime PMT1");
  h5->GetXaxis()->CenterTitle();
  h5->GetYaxis()->SetTitle("Counts");
  h5->GetYaxis()->CenterTitle();
  h6->Draw("same");
  h6->SetLineColor(kRed);


  c2->cd(2);gPad->SetLogz();gPad->SetGrid();gPad->SetLogy();
  gPad->cd(1);
  h7->Draw("colz");
  h7->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime PMT1");
  h7->GetXaxis()->CenterTitle();
  h7->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h7->GetYaxis()->CenterTitle();


  c2->cd(3);gPad->SetLogz();gPad->SetGrid();gPad->SetLogy();
  h8->Draw("colz");
  h8->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime PMT1");
  h8->GetXaxis()->CenterTitle();
  h8->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h8->GetYaxis()->CenterTitle();

  
  c2->SaveAs("pdf/logy_hcer_pmt1_mult1_100_new.pdf");
  delete c2;

  //No logy plots
  
  TCanvas *c3 = new TCanvas ("c3", "c3", 1000, 1000);
  c3->Divide(1,3);

  c3->cd(1);gPad->SetGrid();
  h1->Draw();
  h1->GetXaxis()->SetTitle("H.cer.goodAdcPulseTime PMT1");
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->SetTitle("Counts");
  h1->GetYaxis()->CenterTitle();
  h2->Draw("same");
  h2->SetLineColor(kRed);

  
  c3->cd(2);gPad->SetLogz();gPad->SetGrid();
  gPad->cd(1);
  h3->Draw("colz");
  h3->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime  PMT1");
  h3->GetXaxis()->CenterTitle();
  h3->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h3->GetYaxis()->CenterTitle();

  c3->cd(3);gPad->SetLogz();gPad->SetGrid();
  h4->Draw("colz");
  h4->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime  PMT1");
  h4->GetXaxis()->CenterTitle();
  h4->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h4->GetYaxis()->CenterTitle();

 
  c3->SaveAs("pdf/nology_hcer_pmt1_mult1_100_old.pdf");
  delete c3;


  TCanvas *c4 = new TCanvas ("c4", "c4", 1000, 1000);
  c4->Divide(1,3);

  
  c4->cd(1);gPad->SetGrid();
  h5->Draw();
  h5->GetXaxis()->SetTitle("H.cer.goodAdcPulseTime PMT1");
  h5->GetXaxis()->CenterTitle();
  h5->GetYaxis()->SetTitle("Counts");
  h5->GetYaxis()->CenterTitle();
  h6->Draw("same");
  h6->SetLineColor(kRed);

  c4->cd(2);gPad->SetLogz();gPad->SetGrid();
  h7->Draw("colz");
  h7->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime PMT1");
  h7->GetXaxis()->CenterTitle();
  h7->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h7->GetYaxis()->CenterTitle();

  c4->cd(3);gPad->SetLogz();gPad->SetGrid();
  h8->Draw("colz");
  h8->GetXaxis()->SetTitle(" H.cer.goodAdcPulseTime PMT1");
  h8->GetXaxis()->CenterTitle();
  h8->GetYaxis()->SetTitle("H.cer.goodAdcPulseAmp");
  h8->GetYaxis()->CenterTitle();
  
  c4->SaveAs("pdf/nology_hcer_pmt1_mult1_100_new.pdf");

  delete c4;

  

}
