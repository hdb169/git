void data_mc_k36()  {
  using namespace TMath;
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetNdivisions(505);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(0.11);

  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadBottomMargin(.14);
  gStyle->SetTitleYOffset(0.91);
  gStyle->SetTitleXOffset(2.2);
  gStyle->SetTitleYSize(0.08);
  gStyle->SetTitleXSize(0.08);
  gStyle->SetLabelFont(62,"X");
  gStyle->SetLabelFont(62,"Y");
  gStyle->SetTitleFont(62,"X");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetLabelSize(0.07,"X");
  gStyle->SetLabelSize(0.07,"Y");
  gStyle->SetPaperSize(18,22);
const int nBins = 100; 
  TFile *fh = new TFile("k36_3dp.root");
  fh->ls();
  TH1F *h10 = (TH1F*) fh->Get("h10");
  Double_t Y_d =h10->Integral();
  TH1F *h20 = (TH1F*) fh->Get("h20");
  TH1F *h30 = (TH1F*) fh->Get("h30");
  TH1F *h40 = (TH1F*) fh->Get("h40");
  TH1F *h50 = (TH1F*) fh->Get("h50");
// for(Int_t i=0;i<nBins;i++){
//  Double_t E1, E2, E3, E4, E5;
//   if (h10->GetBinContent(i))  {E1 = 1./sqrt((h10->GetBinContent(i)));} else {E1=0;}
//   if (h20->GetBinContent(i))  {E2 = 1./sqrt((h20->GetBinContent(i)));} else {E2=0;}
//   if (h30->GetBinContent(i))  {E3 = 1./sqrt((h30->GetBinContent(i)));} else {E3=0;}
//   if (h40->GetBinContent(i))  {E4 = 1./sqrt((h40->GetBinContent(i)));} else {E4=0;}
//   if (h50->GetBinContent(i))  {E5 = 1./sqrt((h50->GetBinContent(i)));} else {E5=0;}
//   h10->SetBinError(i,E1);
//   h20->SetBinError(i,E2);
//   h30->SetBinError(i,E3);
//   h40->SetBinError(i,E4);
//   h50->SetBinError(i,E5);  
//  }


 h10->SetLineColor(kBlack); 
 ifstream inputfile1, inputfile2;
 Double_t Q,LT,Trk_eff,I;
 inputfile1.open(Form("normFactors/k36.dat"));
  inputfile1>>fixed>>Q>>I>>LT>>Trk_eff;
  inputfile1.close();
  cout<<"charge_hy: "<<Q<<"   current_hy:  "<<I<<"   LT_hy:   "<<LT<<"   TE_Hy:   "<<Trk_eff<<endl;
 
  h10->Scale(1/(Q*LT*Trk_eff));
  h20->Scale(1/(Q*LT*Trk_eff));
  h30->Scale(1/(Q*LT*Trk_eff));
  h40->Scale(1/(Q*LT*Trk_eff));
  h50->Scale(1/(Q*LT*Trk_eff));

  TFile *fd = new TFile("dummy_k36_3dp.root");
  fd->ls();
  TH1F *h10d = (TH1F*) fd->Get("h10");
  TH1F *h20d = (TH1F*) fd->Get("h20");
  TH1F *h30d = (TH1F*) fd->Get("h30");
  TH1F *h40d = (TH1F*) fd->Get("h40");
  TH1F *h50d = (TH1F*) fd->Get("h50");
  TH1F *h10dd = (TH1F*) fd->Get("h10");
  TH1F *h20dd = (TH1F*) fd->Get("h20");
  TH1F *h30dd= (TH1F*) fd->Get("h30");
  TH1F *h40dd = (TH1F*) fd->Get("h40");
  TH1F *h50dd = (TH1F*) fd->Get("h50");


  // for(Int_t i=0;i<nBins;i++){
  //   Double_t E1d, E2d, E3d, E4d, E5d;
  //   if (h10d->GetBinContent(i))  {E1d = 1./sqrt((h10d->GetBinContent(i)));} else {E1d=0;}
  //   if (h20d->GetBinContent(i))  {E2d = 1./sqrt((h20d->GetBinContent(i)));} else {E2d=0;}
  //   if (h30d->GetBinContent(i))  {E3d = 1./sqrt((h30d->GetBinContent(i)));} else {E3d=0;}
  //   if (h40d->GetBinContent(i))  {E4d = 1./sqrt((h40d->GetBinContent(i)));} else {E4d=0;}
  //   if (h50d->GetBinContent(i))  {E5d = 1./sqrt((h50d->GetBinContent(i)));} else {E5d=0;}
  //   h10d->SetBinError(i,E1d);
  //   h20d->SetBinError(i,E2d);
  //   h30d->SetBinError(i,E3d);
  //   h40d->SetBinError(i,E4d);
  //   h50d->SetBinError(i,E5d);
  // }

  Double_t Qd,LTd,Trk_effd,Id;
  inputfile2.open(Form("normFactors/dummy_k36.dat"));
  inputfile2>>fixed>>Qd>>Id>>LTd>>Trk_effd;
  inputfile2.close();
  cout<<"charge_dummy: "<<Qd<<"   current_dummy:  "<<Id<<"   LT_dummy:   "<<LTd<<"   TE_Dummy:   "<<Trk_effd<<endl;
  Double_t tr = 6.;
  h10d->Scale(1/(tr*Qd*LTd*Trk_effd));
  h20d->Scale(1/(tr*Qd*LTd*Trk_effd));
  h30d->Scale(1/(tr*Qd*LTd*Trk_effd));
  h40d->Scale(1/(tr*Qd*LTd*Trk_effd));
  h50d->Scale(1/(tr*Qd*LTd*Trk_effd));
  h10d->SetLineColor(kBlue);
h20d->SetLineColor(kBlue);h30d->SetLineColor(kBlue);
h40d->SetLineColor(kBlue);h50d->SetLineColor(kBlue);
  h10->Add(h10d,-1);
  h20->Add(h20d,-1);
  h30->Add(h30d,-1);
  h40->Add(h40d,-1);
  h50->Add(h50d,-1);


  
  Double_t sig_cent =0.112155E-04; 
Int_t nmc =500000;  
  // Int_t normf =0.204185E+08; //2*fiq1
//  Int_t normf =0.204495E+08;//defq1q2
//Int_t normf =0.204031E+08;//250
//Int_t normf =0.204312E+08;//275
//Int_t normf =0.204317E+08;//325
//Int_t normf = 0.204440E+08;//375
//Int_t normf = 0.204223E+08;//425
Int_t normf = 0.204238E+08;//475
Double_t mcnorm = (normf)/(1000.*nmc);


  
  const double pmin = -0.06;
  const double pmax = 0.06;
  const double th_min = -0.09;
  const double th_max = 0.09;
  const double ph_min = -0.04;
  const double ph_max = 0.045;
  const double ymin = -0.08;
  const double ymax = 0.08;  
  const double wmin = 0.85;
  const double wmax = 1.11;

  const double dp_cut = 0.035;
  const double th_cut = 0.09;
  const double ph_cut = 0.04;
  const double y_cut = 0.08;
  const double w_min = 0.85;
  const double w_max = 1.07;

  Float_t sigcc;
  Float_t  ssdelta;
  Float_t  ssxptar;
  Float_t  ssyptar;
  Float_t  Weight;
  Float_t  W;
  Float_t  ssytar;
  
  TFile *f1=new TFile("/lustre/expphy/work/halla/gmp12/gautam/SIMC/simc_fall16/worksim/h2_k36_475.root");
  t= (TTree*)f1->Get("h666");
  t->SetBranchAddress("Weight",&Weight);
  t->SetBranchAddress("W",&W);
  t->SetBranchAddress("ssdelta",&ssdelta);
  t->SetBranchAddress("ssxptar",&ssxptar);
  t->SetBranchAddress("ssyptar",&ssyptar);
  t->SetBranchAddress("ssytar",&ssytar);
   

  Int_t snentries = t->GetEntries();
  TH1F *h11 = new TH1F("","",nBins,wmin,wmax);
  TH1F *h11c = new TH1F("","",nBins,wmin,wmax); 
  TH1F *h12 = new TH1F("","",nBins,pmin,pmax);
  TH1F *h13 = new TH1F("","",nBins,ph_min,ph_max);
  TH1F *h14 = new TH1F("","",nBins,th_min,th_max);
  TH1F *h15 = new TH1F("","",nBins,ymin,ymax);
  h11->SetLineColor(kRed);
  h12->SetLineColor(kRed);
  h13->SetLineColor(kRed);
  h14->SetLineColor(kRed);
  h15->SetLineColor(kRed);


  for(Int_t j=0;j<snentries;j++){     	
    t->GetEntry(j);
    if ((W)<w_max &&(W)>w_min && TMath::Abs(ssdelta)<dp_cut*100. && TMath::Abs(ssyptar)<ph_cut &&TMath::Abs(ssxptar)<th_cut && TMath::Abs(ssytar)<y_cut*100.) {	 
      h11->Fill(W,Weight*mcnorm);  
      h11c->Fill(W); 
      h12->Fill(ssdelta/100.,Weight*mcnorm);  
      h13->Fill(ssyptar,Weight*mcnorm);  
      h14->Fill(ssxptar+0.0024,Weight*mcnorm);  
      h15->Fill(ssytar/100.,Weight*mcnorm);  

    }
  }  


 
  Double_t Y_m = h11c->GetEntries();
  TCanvas *c2 = new TCanvas("c2","",1400,900);
  c2->Divide(2,3);
  c2->cd(1);
  h10->Draw();h10->SetTitle("K3-6"):
  h10->GetYaxis()->SetRangeUser(0,0.01);
  // h10-> SetMarkerStyle(kPlus);
 h10dd->Draw("same");
  h11->Draw("same");     
  leg = new TLegend(0.5,0.65,0.75,0.85);  
  leg->AddEntry(h11,"MC","lp");
  leg->AddEntry(h10,"Data - EndCap","lp");
leg->AddEntry(h10d,"EndCap","lp");
  leg->SetTextSize(0.07);
  leg->Draw();
  h10->SetMaximum(1.05*TMath::Max(h10->GetMaximum(),h11->GetMaximum()));
TPaveText *t0 = new TPaveText(0.55,0.3,0.75,0.5,"NDC");
  t0->AddText("#DeltaW= -5.1 MeV");
  t0->SetShadowColor(0);
  t0->SetTextSize(0.06);
  t0->SetFillColor(0);
  t0->Draw("same");
  Double_t W_ISIMC = h11->Integral();
  Double_t W_IData = h10->Integral();
  cout<<"W_ISIMC:   "<<W_ISIMC<<"    "<<"W_IData:   "<<W_IData<<endl;
  
  c2->cd(2);
  h20->Draw(); h20->GetYaxis()->SetRangeUser(0,0.003);
  // h20-> SetMarkerStyle(kPlus);
  h12->Draw("same");h20d->Draw("hsame");
 
  c2->cd(3);
  h30->Draw(); h30->GetYaxis()->SetRangeUser(0,0.0041);
  h13->Draw("same");h30d->Draw("hsame");
 
  c2->cd(4);
  h40->Draw(); h40->GetYaxis()->SetRangeUser(0,0.0025);
  h14->Draw("same");h40d->Draw("hsame");
  TPaveText *t011z = new TPaveText(0.5,0.3,0.7,0.5,"NDC");
  t011z->AddText("#DeltaX'_{tar} = 2.4 mrad");
  t011z->SetShadowColor(0);
  t011z->SetTextSize(0.06);
  t011z->SetFillColor(0);
  t011z->Draw("same");
  c2->cd(5);
  h50->Draw();
  // h50->SetMarkerStyle(kFullTriangleUp);
  // h50-> SetMarkerStyle(kPlus);
  h15->Draw("same");h50d->Draw("hsame");
  h50->SetMaximum(1.05*TMath::Max(h50->GetMaximum(),h15->GetMaximum()));
   h50->GetYaxis()->SetRangeUser(0,0.0034);
  c2->cd(6);  
  Double_t W_ISIMC = h11->Integral();
  Double_t W_IData = h10->Integral();
  cout<<"W_ISIMC:   "<<W_ISIMC<<"    "<<"W_IData:   "<<W_IData<<endl;
  Double_t eRatio =W_IData/W_ISIMC*sqrt(1/Y_d +1/Y_m );
 
  TPaveText *t011 = new TPaveText(0.1,0.01,0.9,0.99,"NDC");
  t011->AddText("E = 6.427 GeV, #theta = 30.9, P_{0} = 3.224 GeV/c");
  t011->AddText(" Q^{2} =  5.93GeV^{2}");
  t011->AddText(Form(" W_{Data}/W_{SIMC} = %f #pm %f",W_IData/W_ISIMC,eRatio));
  t011->AddText(Form("Cross section = %e #pm %e #mubarn/sr",W_IData/W_ISIMC*sig_cent,eRatio*sig_cent));
  t011->SetShadowColor(0);
  t011->SetTextSize(0.07);
  t011->SetFillColor(0);
  t011->Draw(""); 
   
}
