											`	A	`	1	`	//SHMS/HODO/1x/

#include <iostream>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TMatrixD.h>
#include <TROOT.h>
#include <TMatrixDBase.h>
#include <TMath.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>
#include <cstdlib>
#include <TH2F.h>
#include <TPad.h>
#include <TCutG.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TStyle.h>

using namespace std;

static const double degtorad = 3.141592653589793/180.;



bool inside_poly(Double_t amp, Double_t timediff, Double_t x1, Double_t x2, Double_t x3, Double_t x4, Double_t x5, Double_t x6, Double_t x7, Double_t y1, Double_t y2, Double_t y3, Double_t y4, Double_t y5, Double_t y6, Double_t y7)

{

  TCutG *mycut = new TCutG("mycut",7);
  mycut->SetVarX("");
  mycut->SetVarY("");
  /*  mycut->SetPoint(0,20,-202.);
  mycut->SetPoint(1,70,-205.);
  mycut->SetPoint(2,140,-206.);
  mycut->SetPoint(3,140,-209.);
  mycut->SetPoint(4,60,-208.);
  mycut->SetPoint(5,20,-205.);
  mycut->SetPoint(6,20,-202.); */

  mycut->SetPoint(0,x1,y1);
  mycut->SetPoint(1,x2,y2);
  mycut->SetPoint(2,x3,y3);
  mycut->SetPoint(3,x4,y4);
  mycut->SetPoint(4,x5,y5);
  mycut->SetPoint(5,x6,y6);
  mycut->SetPoint(6,x7,y7);



  if(mycut->IsInside(amp,timediff)){
    return true;
  } else {
    return false;
  }
}

TLegend * leg;

//void formatit(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag, Double_t low, Double_t high){
void formatit(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetLogy();
  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.21);
  gPad->SetRightMargin(0.11);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);

  gStyle->SetOptStat(0);

  histo->SetLabelSize(0.035, "x");
  histo->SetLabelSize(0.035, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kBlue);
  histo->SetLineWidth(1);
  histo->SetLineStyle(1);
  histo->Draw("");

 if (flag == 0){

  leg = new TLegend(0.2,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kAzure+7);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same");

 }

}
 // TLine *line = new TLine(low,0.5,low,30);
 // line->SetLineColor(kViolet+1);
 // line->SetLineStyle(1);
 // line->SetLineWidth(5);
 // line->Draw("same");
 // TLine *line1 = new TLine(high,0.5,high,30);
 // line1->SetLineColor(kViolet+1);
 // line1->SetLineStyle(1);
 // line1->SetLineWidth(5);
 // line1->Draw("same");

 // line1->Draw("same");

//}

//TLegend * leg1;

void legend(TH1F * histo0, TH1F * histo1,TH1F * histo2, TH1F * histo3)
{

  leg = new TLegend(0.6,0.85,0.9,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.025);
  leg->SetTextColor(kAzure+7);
  leg->SetBorderSize(0);
  leg->AddEntry(histo0,"no hit Sel","l");
  leg->AddEntry(histo1,"Mult Cut == 1","l");
  leg->AddEntry(histo2,"elec cut","l"); 
  leg->AddEntry(histo3,"Mult & elec cut","l");
  leg->Draw("same");
}

void legend_same(TH1F * histo0, TH1F * histo1,TH1F * histo2, TH1F * histo3)
{

  leg = new TLegend(0.6,0.8,0.9,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.025);
  leg->SetTextColor(kAzure+7);
  leg->SetBorderSize(0);
  leg->AddEntry(histo0,"hit Sel","l");
  leg->AddEntry(histo1,"Mult cut == 1","l");
  leg->AddEntry(histo2,"elec cut","l"); 
  leg->AddEntry(histo3,"Mult & elec cut","l");
  leg->Draw("same");


}

void formatitd(TH1D *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.21);
  gPad->SetRightMargin(0.11);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);


  histo->SetLabelSize(0.035, "x");
  histo->SetLabelSize(0.035, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kPink+10);
  histo->SetLineWidth(1);
  histo->SetLineStyle(2);
  histo->Draw("");

 if (flag == 0){

  leg = new TLegend(0.2,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kAzure+7);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same");

 }

}


void formatit_2d(TH2F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.21);
  gPad->SetRightMargin(0.11);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);


  histo->SetLabelSize(0.035, "x");
  histo->SetLabelSize(0.035, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  //  histo->SetLineColor(kPink+10);
  //  histo->SetLineWidth(3);
  //  histo->SetLineStyle(2);
  //  histo->Draw("colz");

  /*  TCutG *mycut = new TCutG("mycut",7);
  mycut->SetVarX("");
  mycut->SetVarY("");
  mycut->SetPoint(0,20,-202.);
  mycut->SetPoint(1,70,-205.);
  mycut->SetPoint(2,140,-206.);
  mycut->SetPoint(3,140,-209.);
  mycut->SetPoint(4,60,-208.);
  mycut->SetPoint(5,20,-205.);
  mycut->SetPoint(6,20,-202.); */

  histo->Draw("colz");


 if (flag == 0){

  leg = new TLegend(0.2,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kAzure+7);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same");

 }

}
void formatit_2dd(TH2F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.21);
  gPad->SetRightMargin(0.11);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);


  histo->SetLabelSize(0.035, "x");
  histo->SetLabelSize(0.035, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  //  histo->SetLineColor(kPink+10);
  //  histo->SetLineWidth(3);
  //  histo->SetLineStyle(2);
  histo->Draw("colz");

 if (flag == 0){

  leg = new TLegend(0.2,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kAzure+7);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same");

 }

}

void formatit_same(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.21);
  gPad->SetRightMargin(0.11);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);


  histo->SetLabelSize(0.035, "x");
  histo->SetLabelSize(0.035, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  // histo->SetLineColor(kAzure+7);
  histo->SetLineWidth(1);
  histo->SetLineStyle(4);
  histo->Draw("same");

 if (flag == 0){

  leg = new TLegend(0.2,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kRed-4);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same");

 }

}


int binmax  = 0;
double x    = 0;
double xmin = 0;
double xmax = 0;

//ofstream phodo_neg, phodo_pos;

ofstream phodo_neg_min("phodo_neg_min.txt", fstream::app);
ofstream phodo_neg_max("phodo_neg_max.txt", fstream::app);

ofstream phodo_pos_min("phodo_pos_min.txt", fstream::app);
ofstream phodo_pos_max("phodo_pos_max.txt", fstream::app);

//ofstream phodo_pos("phodo_pos.txt", fstream::app);

void window_neg(TH1F * histo){

  binmax = histo->GetMaximumBin(); 
  x = histo->GetXaxis()->GetBinCenter(binmax);
  
  xmin = x -40;
  xmax = x +40;
    
  phodo_neg_min << xmin << ",";
  phodo_neg_max << xmax << ",";

  auto * line =  new TLine (xmin, 0, xmin, 10000);
  line->Draw();
  line->SetLineColor(kMagenta);
  line->SetLineWidth(2);
  auto * line1 =  new TLine (xmax, 0, xmax, 10000);
  line1->Draw();
  line1->SetLineColor(kMagenta);
  line1->SetLineWidth(2);
  


}

void window_pos(TH1F * histo){

  binmax = histo->GetMaximumBin(); 
  x = histo->GetXaxis()->GetBinCenter(binmax);
  
  xmin = x -40;
  xmax = x +40;
    
  phodo_pos_max << xmax << ",";
  phodo_pos_min << xmin << ",";

  // phodo_neg << xmax << ",";

  auto * line =  new TLine (xmin, 0, xmin, 10000);
  line->Draw();
  line->SetLineColor(kMagenta);
  line->SetLineWidth(2);
  auto * line1 =  new TLine (xmax, 0, xmax, 10000);
  line1->Draw();
  line1->SetLineColor(kMagenta);
  line1->SetLineWidth(2);

}


int main(){
  
  TFile *myfile;
  
  TChain chain("T");
  // TString fname = "/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_hodo_mar22_6449_-1.root";
  //  TString fname = "/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_7593_300000_online.root";
  //TString fname = "/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_hodo_mar22_6518_-1.root";
  // TString fname = "/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/coin_replay_production_hodo_mar22_6359_10000.root";
  TString fname = "/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/new_100.root";


 
  chain.Add(fname);
  
  const UInt_t nplanes = 4;
  const UInt_t nsides = 2;
  const UInt_t maxbars  = 16;
  const UInt_t nsignals = 2;
  const UInt_t nadcsignals = 8;
  const UInt_t ntdcsignals = 2;
  const UInt_t maxhits = 128*16*4;

  const TString plane_names[nplanes] = {"1x", "1y", "2x", "2y"};
  const UInt_t  nbars[nplanes] = {13, 13, 14, 21};
  const TString sides[nsides] = {"Neg", "Pos"};
  const TString sides_counter[nsides] = {"neg", "pos"};
  const TString signals[nsides] = {"Adc", "Tdc"};
  const TString adc_signals[nadcsignals] = {"Ped", "PedRaw", "PulseInt", "PulseIntRaw", "PulseAmp", "PulseAmpRaw", "PulseTimeRaw", "PulseTime"};
  const TString tdc_signals[ntdcsignals] = {"Time", "TimeRaw"};
  
  Int_t nadchits[nplanes][nsides];
  Int_t ntdchits[nplanes][nsides];
  
  Double_t adc_paddles[nplanes][nsides][maxhits];
  Double_t tdc_paddles[nplanes][nsides][maxhits];
  
  Double_t adc_values[nplanes][nsides][nadcsignals][maxhits];
  Double_t tdc_values[nplanes][nsides][ntdcsignals][maxhits];

  Double_t goodAdcTdcDiff[nplanes][nsides][30];

  Double_t goodPulseAmp[nplanes][nsides][30];

  Double_t goodAdcMult[nplanes][nsides][30];

  Double_t errorFlag[nplanes][nsides][maxhits];

  for(UInt_t ip = 0; ip < nplanes; ip++) {

    for(UInt_t iside = 0; iside < nsides; iside++) { 
      
      for(UInt_t ibar = 0; ibar < nbars[ip]; ibar++) {

      }	
	
	for(UInt_t isignal = 0; isignal < nsignals; isignal++) {
	  
	  if(signals[isignal] == "Adc") {
	    
	    TString adc_base_name = "P.hod."+ plane_names[ip]+"."+sides_counter[iside]+signals[isignal];
	    
	    TString adc_base_name_good = "P.hod."+ plane_names[ip]+".Good"+sides[iside]+signals[isignal];
	    //cout <<adc_base_name_good << endl;
	    
	    TString adc_base_name_raw = "P.hod."+ plane_names[ip]+"."+sides_counter[iside]+signals[isignal]; // same as adc_base_name
	    
	    TString adc_base_name_raw_low = "P.hod."+ plane_names[ip]+"."+sides_counter[iside]+signals[isignal]; //same as adc_base_name
	    
	    TString adc_base_name_low = "P.hod."+ plane_names[ip]+".good"+sides[iside]+signals[isignal];
	    
	    TString adc_base_name_counter = "P.hod."+ plane_names[ip]+"."+sides_counter[iside]+signals[isignal]; // same as adc base name 

	    TString error_flag = adc_base_name + "ErrorFlag";
	    chain.SetBranchAddress( error_flag, &errorFlag[ip][iside][0]);

	    cout << error_flag <<endl;
	    //cout << "name is: " << intlist_name << endl;

	    TString good_adc_mult = adc_base_name_good + "Mult";
	    chain.SetBranchAddress(good_adc_mult, &goodAdcMult[ip][iside][0]);
	    // cout << adc_mult << endl;

	    TString good_AdcTdcDiff = adc_base_name_good + "TdcDiffTime";
	    chain.SetBranchAddress(good_AdcTdcDiff, &goodAdcTdcDiff[ip][iside][0]);

	    // cout << goodAdcTdcDiff << endl;
	    //  cout << adc_mult << endl;
	    
	    TString good_adc_neg_pulse_amp = adc_base_name_good + "PulseAmp";
	    chain.SetBranchAddress(good_adc_neg_pulse_amp, &goodPulseAmp[ip][iside][0]);

	    // cout << good_adc_neg_pulse_amp << endl;


	    TString adc_ndata_name = "Ndata."+adc_base_name_counter+"Counter";
	    chain.SetBranchAddress(adc_ndata_name, &nadchits[ip][iside]);
	    //cout <<  adc_ndata_name << endl;
	    
	    TString adc_paddle_name = adc_base_name_counter+"Counter";
	    chain.SetBranchAddress(adc_paddle_name, &adc_paddles[ip][iside][0]);
	    //cout <<  adc_paddle_name << endl;
	    
	    for (UInt_t iadcsignal = 0; iadcsignal < nadcsignals; iadcsignal++) {
	      
	      if (adc_signals[iadcsignal] == "Ped") {
		
		TString pedlist_name = adc_base_name_raw_low+"Ped";
		chain.SetBranchAddress(pedlist_name, &adc_values[ip][iside][iadcsignal][0]);
		// cout << pedlist_name <<endl;
	      }
	      
	      if (adc_signals[iadcsignal] == "PedRaw") {
		
		TString pedrawlist_name = adc_base_name_raw_low+"PedRaw";
		chain.SetBranchAddress(pedrawlist_name, &adc_values[ip][iside][iadcsignal][0]);
		//cout << pedrawlist_name << endl;
	      }
	      
	      if (adc_signals[iadcsignal] == "PulseInt") {
		TString intlist_name = adc_base_name+"PulseInt";
		chain.SetBranchAddress(intlist_name, &adc_values[ip][iside][iadcsignal][0]);
		// cout << intlist_name << endl;
	      }
	      if (adc_signals[iadcsignal] == "PulseTime") {
		TString intlist_name = adc_base_name+"PulseTime";
		chain.SetBranchAddress(intlist_name, &adc_values[ip][iside][iadcsignal][0]);
		// cout << "name is: " << intlist_name << endl;
	      }
	      if (adc_signals[iadcsignal] == "PulseIntRaw") {
		TString intrawlist_name = adc_base_name_raw+"PulseIntRaw";
		chain.SetBranchAddress(intrawlist_name, &adc_values[ip][iside][iadcsignal][0]);
	      }
	      if (adc_signals[iadcsignal] == "PulseAmp") {
		TString amplist_name = adc_base_name+"PulseAmp";
		chain.SetBranchAddress(amplist_name, &adc_values[ip][iside][iadcsignal][0]);

		//	TString good_amplist_name = adc_base_name_good+"PulseAmp";
		//	chain.SetBranchAddress(good_amplist_name, &goodAdc_amp_neg[ip][iside][iadcsignal][0]);
		//cout << good_amplist_name << endl;
	      }
	      if (adc_signals[iadcsignal] == "PulseAmpRaw") {
		TString amprawlist_name = adc_base_name_raw+"PulseAmpRaw";
		chain.SetBranchAddress(amprawlist_name,&adc_values[ip][iside][iadcsignal][0]);
	      }
	      if (adc_signals[iadcsignal] == "PulseTimeRaw") {
		TString ptrawlist_name = adc_base_name_raw+"PulseTimeRaw";
		chain.SetBranchAddress(ptrawlist_name, &adc_values[ip][iside][iadcsignal][0]);
	      }
	    }
	  }
		
	if(signals[isignal] == "Tdc") {
	  TString tdc_base_name = "P.hod."+ plane_names[ip]+"."+ sides_counter[iside]+signals[isignal];
	  //  cout <<  tdc_base_name << endl;
	  
	  TString tdc_base_name_good = "P.hod."+ plane_names[ip]+".Good"+ sides[iside]+signals[isignal];
	  // cout << tdc_base_name_good << endl;
	  
	  TString tdc_base_name_counter = "P.hod."+ plane_names[ip]+"."+ sides_counter[iside]+signals[isignal]; //same as tdc base name
	  //  cout << tdc_base_name_counter << endl;
	  
	  TString tdc_ndata_name = "Ndata."+ tdc_base_name_counter+"Counter"; 
	  // cout <<  tdc_ndata_name << endl;
	  chain.SetBranchAddress(tdc_ndata_name, &ntdchits[ip][iside]);
	  
	  TString tdc_paddle_name = tdc_base_name_counter+"Counter";
	  chain.SetBranchAddress(tdc_paddle_name, &tdc_paddles[ip][iside][0]);
	  //  cout << tdc_paddle_name << endl;
	  
	  for (UInt_t itdcsignal = 0; itdcsignal < ntdcsignals; itdcsignal++) {
	    if (tdc_signals[itdcsignal] == "Time") {
	      TString tdclist_name = tdc_base_name+"Time";
	      chain.SetBranchAddress(tdclist_name, &tdc_values[ip][iside][itdcsignal][0]);
	      // cout << "name is: " << tdclist_name << endl;
	    }
	    if (tdc_signals[itdcsignal] == "TimeRaw") {
	      TString tdcrawlist_name = tdc_base_name+"TimeRaw";
	      chain.SetBranchAddress(tdcrawlist_name, &tdc_values[ip][iside][itdcsignal][0]);
	    }
	  }
	}
	
      }
    }
  }
  
  Int_t ndata_neg_difft, ndata_pos_difft;
  Double_t pos_difft[100], neg_difft[100], tdc_ref_time, adc_ref_time, tdc_ref_time2yt;

  Double_t cal;
  Double_t aeroNpe;
  Double_t starttime;
  Double_t hgcer;
  chain.SetBranchAddress("P.cal.etottracknorm", &cal);
  chain.SetBranchAddress("P.aero.npeSum", &aeroNpe);
  chain.SetBranchAddress("P.hod.starttime",&starttime);
  chain.SetBranchAddress("P.hgcer.npeSum",&hgcer);

  // chain.SetBranchAddress("T.shms.pT1_tdcTimeRaw", &tdc_ref_time);
  // chain.SetBranchAddress("T.shms.pT2_tdcTimeRaw", &tdc_ref_time2yt);
  // chain.SetBranchAddress("T.shms.pFADC_TREF_ROC2_adcPulseTimeRaw", &adc_ref_time);


  TH1F* difft_pos_good[20][4];
  TH1F* difft_neg_good[20][4];
  

  TH2F* diff_neg_tdc[20];
  TH2F* diff_pos_tdc[20];

  TH1F* diff_neg_tdc_1d[20];
  TH1F* diff_pos_tdc_1d[20];
  TH1F* diff_pos_tdc_1d_cut[20];

  //  TH1F* tdc_ref_Time = new TH1F("","",100,3200.,4200.);
  //  TH1F* tdc_ref_Time2yt = new TH1F("","",100,3200.,4200.);
  //  TH1F* adc_ref_Time = new TH1F("","",80,4000.,4500.);

  TH1F* diff_pos[20];
  TH1F* diff_pos_eCut[20];
  TH1F* diff_pos_multCut[20];
  TH1F* diff_pos_mult_eCut[20];
  

  TH1F* diff_neg[20];
  TH1F* diff_neg_eCut[20];
  TH1F* diff_neg_multCut[20];
  TH1F* diff_neg_mult_eCut[20];

  TH1F* good_neg[20];
  TH1F* good_neg_eCut[20];
  TH1F* good_neg_multCut[20];
  TH1F* good_neg_mult_eCut[20];

  TH1F* good_pos[20];
  TH1F* good_pos_eCut[20];
  TH1F* good_pos_multCut[20];
  TH1F* good_pos_mult_eCut[20];

  TH2F* diff_neg_amp[20];
  TH2F* diff_neg_amp_eCut[20];
  TH2F* diff_neg_amp_multCut[20];
  TH2F* diff_neg_amp_mult_eCut[20];

  TH2F* good_neg_amp[20];
  TH2F* good_neg_amp_multCut[20];

  TH2F* good_pos_amp[20];
  TH2F* good_pos_amp_multCut[20];




  TH2F* diff_pos_amp[20];
  TH2F* diff_pos_amp_eCut[20];
  TH2F* diff_pos_amp_multCut[20];
  TH2F* diff_pos_amp_mult_eCut[20];

  TH2F* diff_pos_amp_cut[20];

  // Int_t bin = 320;
  // Int_t maxR = 180;
  // Int_t minR = -180;

   Int_t bin = 532;
   Int_t maxR = 300;
   Int_t minR = -300;

  


    for(Int_t mm = 0; mm < 20; mm++){


      diff_pos[mm]            = new TH1F("","", bin, minR, maxR);
      diff_pos_eCut[mm]       = new TH1F("","", bin, minR, maxR);
      diff_pos_multCut[mm]    = new TH1F("","", bin, minR, maxR);
      diff_pos_mult_eCut[mm]  = new TH1F("","", bin, minR, maxR);



      diff_neg[mm]            = new TH1F("","", bin, minR, maxR);
      diff_neg_eCut[mm]       = new TH1F("","", bin, minR, maxR);
      diff_neg_multCut[mm]    = new TH1F("","", bin, minR, maxR);
      diff_neg_mult_eCut[mm]  = new TH1F("","", bin, minR, maxR);


      good_neg[mm]            = new TH1F("","", bin, minR, maxR);
      good_neg_eCut[mm]       = new TH1F("","", bin, minR, maxR);
      good_neg_multCut[mm]    = new TH1F("","", bin, minR, maxR);
      good_neg_mult_eCut[mm]  = new TH1F("","", bin, minR, maxR);

      good_pos[mm]            = new TH1F("","", bin, minR, maxR);
      good_pos_eCut[mm]       = new TH1F("","", bin, minR, maxR);
      good_pos_multCut[mm]    = new TH1F("","", bin, minR, maxR);
      good_pos_mult_eCut[mm]  = new TH1F("","", bin, minR, maxR);


      // diff_neg_tdc[mm] = new TH2F("","",100,-220.,-190.,140,-190.,-120.);
      // diff_pos_tdc[mm] = new TH2F("","",100,-220.,-190.,140,-190.,-120.);

      // diff_neg_tdc_1d[mm] = new TH1F("","",140,-190.,-120.);
      // diff_pos_tdc_1d[mm] = new TH1F("","",140,-190.,-120.);
      // diff_pos_tdc_1d_cut[mm] = new TH1F("","",140,-190.,-120.);

     

      //diff_pos_amp_cut[mm] = new TH2F("","",200,0.,200.,410,-240.,-170.);



      diff_pos_amp[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      diff_pos_amp_eCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      diff_pos_amp_multCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      diff_pos_amp_mult_eCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);

      good_pos_amp[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      good_pos_amp_multCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);


      diff_neg_amp[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      diff_neg_amp_eCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      diff_neg_amp_multCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      diff_neg_amp_mult_eCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);

      good_neg_amp[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);
      good_neg_amp_multCut[mm] = new TH2F("","", bin, minR, maxR, 100, -20., 800.);

    }




    Int_t nentries = chain.GetEntries();
    
    cout << "Total Entries "<< nentries <<endl;
    
    for(Int_t i=0; i < nentries; i++){
      
      // cout << "entry : " << i << endl;
      //cout << "*******************************"<<endl;
      chain.GetEntry(i);
      
      //  tdc_ref_Time->Fill(tdc_ref_time);
      //  tdc_ref_Time2yt->Fill(tdc_ref_time2yt);
      //  adc_ref_Time->Fill(adc_ref_time);
      
      
      for(UInt_t ip = 0; ip < nplanes; ip++) {
	
	if (ip == 0){
	  
	  // cout << "plane :" << ip << endl;
	  
	  //  cout << " totals hits adc hits in plane" << ip << " " << nadchits[ip][0]<< endl;
	  
	  for(Int_t adc_neg_ihit = 0; adc_neg_ihit < nadchits[ip][0]; adc_neg_ihit++){
	    
	    //cout << " loop over adc hits " << " " << adc_neg_ihit + 1 << endl;

	    if (errorFlag[ip][0][adc_neg_ihit]==1)continue;
	      
	    UInt_t adc_neg_bar = TMath::Nint(adc_paddles[ip][0][adc_neg_ihit]) - 1; // hit associate with bar one side
	    
	    //  cout <<" adc_neg_bar number : " <<  adc_neg_bar << endl;
	    
	    // cout << " total tdc hits" << " " <<  ntdchits[ip][0] << endl;
	    
	    for(Int_t tdc_neg_ihit = 0; tdc_neg_ihit < ntdchits[ip][0]; tdc_neg_ihit++){
	      
	      // cout << " looping over tdc hits : "<<  tdc_neg_ihit + 1 << endl;
	      
	      UInt_t tdc_neg_bar = TMath::Nint(tdc_paddles[ip][0][tdc_neg_ihit]) - 1;
	      
	      //	cout <<" tdc_neg_bar number : "<< tdc_neg_bar << endl;

	      //	cout <<"\n";
	      
	      for (Int_t pmt_neg = 0; pmt_neg < 13; pmt_neg++){
		
		if ( adc_neg_bar == pmt_neg &&  tdc_neg_bar == pmt_neg ){
		  
		  //  cout << "pmt number " << pmt_neg << endl;

		  // 2000. is the fTdcOffset from the PARAM file like in the email; 
		  //0.1 is the conversion from TDC channels to ns
		  //  pleas change 0.1 to pscin_tdc_to_time = 0.09766 ; 0.1
		  //(See Log Entry 3574348)
		  
		  
		  Double_t adc_tdc_neg_tdiff = (tdc_values[ip][0][0][tdc_neg_ihit] + 1860.) * 0.09766 - adc_values[ip][0][7][adc_neg_ihit] ; // ?? pulsetime substraction 

		  Double_t adc_amp_neg = adc_values[ip][0][2][adc_neg_ihit];

		  //  Double_t tdc_time_neg = (tdc_values[ip][0][1][tdc_neg_ihit] + 2000.) * 0.1 - tdc_ref_time*0.1;
		  
		  //        cout << " time neg: " << tdc_time_neg << " " <<tdc_values[ip][0][1][tdc_neg_ihit]*0.1 << " " << tdc_ref_time*0.1<< endl;
     

		  //  cout << "value : "<<good_AdcTdcDiff[ip][0][pmt_neg]<< endl;

		  diff_neg[pmt_neg]->Fill(adc_tdc_neg_tdiff);// no hit selection  Adtdc time diff 

		  good_neg[pmt_neg]->Fill(goodAdcTdcDiff[ip][0][pmt_neg]); // good Adc TDC (hit selection)
		  
		  // diff_neg_tdc[pmt_neg]->Fill(adc_tdc_neg_tdiff,tdc_time_neg);
		  
		  // diff_neg_tdc_1d[pmt_neg]->Fill(tdc_time_neg);
		  
		  diff_neg_amp[pmt_neg]->Fill(adc_tdc_neg_tdiff, adc_amp_neg); // Pulse Amp

		  good_neg_amp[pmt_neg]->Fill(goodAdcTdcDiff[ip][0][pmt_neg], goodPulseAmp[ip][0][pmt_neg]); //Good Pulse Amp 

		  // cout <<"good  amp Value : "<<  goodAdc_amp_neg[ip][0][4][pmt_neg]<< endl;


		  //if (cal>0.8 && aeroNpe>2.0)
		  if (cal>1.1 && aeroNpe>5.0 )//&&hgcer>2.0 )

		    {
		      diff_neg_eCut[pmt_neg]->Fill(adc_tdc_neg_tdiff); // electron cut
		      diff_neg_amp_eCut[pmt_neg]->Fill(adc_tdc_neg_tdiff, adc_amp_neg);
		      good_neg_eCut[pmt_neg]->Fill(goodAdcTdcDiff[ip][0][pmt_neg]);
		      
		      if (goodAdcMult[ip][0][pmt_neg]==1)
		  	{
		  	  diff_neg_mult_eCut[pmt_neg]->Fill(adc_tdc_neg_tdiff); //elec and Mult Cut
		  	  diff_neg_amp_mult_eCut[pmt_neg]->Fill(adc_tdc_neg_tdiff, adc_amp_neg);
		  	  good_neg_mult_eCut[pmt_neg]->Fill(goodAdcTdcDiff[ip][0][pmt_neg]);
			  
		  	}
		    }

		  if (goodAdcMult[ip][0][pmt_neg]==1)
		    {
		      diff_neg_multCut[pmt_neg]->Fill(adc_tdc_neg_tdiff);
		      diff_neg_amp_multCut[pmt_neg]->Fill(adc_tdc_neg_tdiff, adc_amp_neg);
		      good_neg_multCut[pmt_neg]->Fill(goodAdcTdcDiff[ip][0][pmt_neg]);
		      good_neg_amp_multCut[pmt_neg]->Fill(goodAdcTdcDiff[ip][0][pmt_neg], goodPulseAmp[ip][0][pmt_neg]);
		    }
		  
		}
	      }
	    }
	    // cout << "\n";
	    // cout << "*********************************"<<endl;
	  }
	
	 for(Int_t adc_pos_ihit = 0; adc_pos_ihit < nadchits[ip][1];adc_pos_ihit++)  {
	   
	   if (errorFlag[ip][1][adc_pos_ihit]==1)continue;

	   UInt_t adc_pos_bar = TMath::Nint(adc_paddles[ip][1][adc_pos_ihit]) - 1;
	   
	   
	   
	   for(Int_t tdc_pos_ihit = 0; tdc_pos_ihit < ntdchits[ip][1];tdc_pos_ihit++)  {
	     
	     UInt_t tdc_pos_bar = TMath::Nint(tdc_paddles[ip][1][tdc_pos_ihit])- 1;
	     
	     for (Int_t pmt = 0; pmt < 13; pmt++){
	
	       if ( adc_pos_bar == pmt && tdc_pos_bar == pmt){
		 
		 Double_t adc_tdc_pos_tdiff = (tdc_values[ip][1][0][tdc_pos_ihit] + 1860.) * 0.09766- adc_values[ip][1][7][adc_pos_ihit];
		 Double_t adc_amp_pos = adc_values[ip][1][2][adc_pos_ihit];
		 //	 Double_t tdc_time_pos = (tdc_values[ip][1][1][tdc_pos_ihit] +2000.) * 0.1 - tdc_ref_time*0.1;
		  
		 // diff_pos_tdc[pmt]->Fill(adc_tdc_pos_tdiff,tdc_time_pos);
		 
		 // diff_pos_tdc_1d[pmt]->Fill(tdc_time_pos);

		 diff_pos[pmt]->Fill(adc_tdc_pos_tdiff);
		 good_pos[pmt]->Fill(goodAdcTdcDiff[ip][1][pmt]);
		  
		 diff_pos_amp[pmt]->Fill(adc_tdc_pos_tdiff,adc_amp_pos);
		 
	         good_pos_amp[pmt]->Fill(goodAdcTdcDiff[ip][1][pmt], goodPulseAmp[ip][1][pmt]);
		 
		 //	 if (cal>0.8 && aeroNpe>2.0)
		 if (cal>1.1 && aeroNpe>5.0 )//&& hgcer >2.0)


		   {
		     diff_pos_eCut[pmt]->Fill(adc_tdc_pos_tdiff); // electron cut
		     diff_pos_amp_eCut[pmt]->Fill(adc_tdc_pos_tdiff, adc_amp_pos);
		     good_pos_eCut[pmt]->Fill(goodAdcTdcDiff[ip][1][pmt]);

		     if (goodAdcMult[ip][1][pmt]==1)
		       {
		 	 diff_pos_mult_eCut[pmt]->Fill(adc_tdc_pos_tdiff); //elec and Mult Cut
		 	 diff_pos_amp_mult_eCut[pmt]->Fill(adc_tdc_pos_tdiff, adc_amp_pos); 
			 good_pos_mult_eCut[pmt]->Fill(goodAdcTdcDiff[ip][1][pmt]);
		       }
		   }
		 if (goodAdcMult[ip][1][pmt]==1)
		   {
		     //cout << nadcMult[ip][1][pmt]<< endl;
		     diff_pos_multCut[pmt]->Fill(adc_tdc_pos_tdiff);
		     diff_pos_amp_multCut[pmt]->Fill(adc_tdc_pos_tdiff, adc_amp_pos);
		     good_pos_multCut[pmt]->Fill(goodAdcTdcDiff[ip][1][pmt]);
		     good_pos_amp_multCut[pmt]->Fill(goodAdcTdcDiff[ip][1][pmt], goodPulseAmp[ip][1][pmt]);
		   }
		 
		 
	       }
	       
	     }
	   }
	 }
	}
	
      }
    }
    // good_pos_amp[0]->Draw();

    //good_neg_amp_multCut[0]->Draw();
    

    //****************** canvas for negative side *************************//
    for (int pmt = 0; pmt<13 ; pmt++)
    {
      auto *c1 = new TCanvas ("c1", "", 500, 500);
      c1->Divide(2,2);

      c1->cd(1);
      
      formatit(diff_neg[pmt],"no hit sel",Form("TdcAdcTimeDiff_Neg_%d(ns)",pmt+1),"Events", 1);

      formatit_same(diff_neg_multCut[pmt]," "," "," ", 1);

      formatit_same(diff_neg_eCut[pmt]," "," "," ", 1);

      formatit_same(diff_neg_mult_eCut[pmt]," "," ","", 1);
      
      
      diff_neg_eCut[pmt]->SetLineColor(kRed);
      diff_neg_eCut[pmt]->SetLineStyle(1);
      diff_neg_multCut[pmt]->SetLineColor(kBlue-7);
      diff_neg_mult_eCut[pmt]->SetLineColor(kRed-10);

      legend(diff_neg[pmt],  diff_neg_multCut[pmt], diff_neg_eCut[pmt], diff_neg_mult_eCut[pmt]);

      //*************************************************************************************//

      c1->cd(2);
      gPad->Divide(2,2);

      gPad->cd(1);
      formatit_2d(diff_neg_amp[pmt], " no hit Sel","TdcAdcTimeDiff_Neg(ns)", "PulseAmp",0); 
      
      c1->cd(2);
      gPad->cd(2);
      formatit_2d(diff_neg_amp_multCut[pmt], "mult Cut","TdcAdcTimeDiff_Neg(ns)", "PulseAmp",0);
 

      c1->cd(2);
      gPad->cd(3);
      formatit_2d(diff_neg_amp_eCut[pmt], "elec Cut","TdcAdcTimeDiff_Neg(ns)", "PulseAmp",0);
      
      
      
      c1->cd(2);
      gPad->cd(4);
      formatit_2d(diff_neg_amp_mult_eCut[pmt], "Mult & eCut","TdcAdcTimeDiff_Neg(ns)", "PulseAmp",0);

      //***********************************************************************************//
      c1->cd(3);
      formatit(good_neg[pmt],"wide cut",Form("P.hod.1x.GoodNegAdcTdcDiffTime_%d(ns)",pmt+1),"Events", 0);

      formatit_same(good_neg_multCut[pmt]," "," "," ", 1);

      formatit_same(good_neg_eCut[pmt]," "," "," ", 1);
      
      formatit_same(good_neg_mult_eCut[pmt]," "," ","", 1);

      good_neg_eCut[pmt]->SetLineColor(kRed);
      good_neg_eCut[pmt]->SetLineStyle(1);
      good_neg_multCut[pmt]->SetLineColor(kBlue-7);
      good_neg_mult_eCut[pmt]->SetLineColor(kRed-10);

      legend_same(good_neg[pmt], good_neg_multCut[pmt], good_neg_eCut[pmt], good_neg_mult_eCut[pmt]);
      window_neg(good_neg[pmt]);
     
      
      //*********************************************************************************************//
      c1->cd(4); 
      gPad->Divide(2,1);
      gPad->cd(1);
      formatit_2d(good_neg_amp[pmt],"hit sel hcana ", "GoodTdcAdcTimeDiff_Neg(ns)", "PulseAmp", 0);

      c1->cd(4);
      gPad->cd(2);
      formatit_2d(good_neg_amp_multCut[pmt],"mult Cut ", "GoodTdcAdcTimeDiff_Neg(ns)", "PulseAmp", 0);

      c1->SaveAs(Form("plots/Neg_S1X_plane_Pmt%d_test.pdf", pmt+1));
      
      //********************Canvas for positive side**************************//

      auto *c2 = new TCanvas("c2", "", 500, 500);
      c2->Divide(2,2);
      c2->cd(1);

      formatit(diff_pos[pmt],"no hit sel",Form("TdcAdcTimeDiff_Pos_%d(ns)",pmt+1),"Events", 1);      

      formatit_same(diff_pos_multCut[pmt]," "," "," ", 1);

      formatit_same(diff_pos_eCut[pmt]," "," "," ", 1);

      formatit_same(diff_pos_mult_eCut[pmt]," "," ","", 1);

      diff_pos_eCut[pmt]->SetLineColor(kRed);
      diff_pos_eCut[pmt]->SetLineStyle(1);
      diff_pos_multCut[pmt]->SetLineColor(kBlue-7);
      diff_pos_mult_eCut[pmt]->SetLineColor(kRed-10);

      legend(diff_pos[pmt], diff_pos_multCut[pmt], diff_pos_eCut[pmt],  diff_pos_mult_eCut[pmt]);
    
      c2->cd(2);
      gPad->Divide(2,2);
      gPad->cd(1);
      formatit_2d(diff_pos_amp[pmt], "no hit sel","TdcAdcTimeDiff_Pos(ns)", "PulseAmp",0);

      c2->cd(2);
      gPad->cd(2);
      formatit_2d(diff_pos_amp_multCut[pmt], "mult Cut","TdcAdcTimeDiff_Pos(ns)", "PulseAmp",0);
      
      
      c2->cd(2);
      gPad->cd(3);
      formatit_2d(diff_pos_amp_eCut[pmt], "elec Cut","TdcAdcTimeDiff_Pos(ns)", "PulseAmp",0);
 
      c2->cd(2);
      gPad->cd(4);
      formatit_2d(diff_pos_amp_mult_eCut[pmt], "Mult & eCut","TdcAdcTimeDiff_Pos(ns)", "PulseAmp",0);

      //***************************************************************************************************//
      c2->cd(3);
      formatit(good_pos[pmt],"wide cut",Form("P.hod.1x.GoodPosAdcTdcDiffTime_%d(ns)",pmt+1),"Events", 0);

      formatit_same(good_pos_multCut[pmt]," "," "," ", 1);

      formatit_same(good_pos_eCut[pmt]," "," "," ", 1);
      
      formatit_same(good_pos_mult_eCut[pmt]," "," ","", 1);

      good_pos_eCut[pmt]->SetLineColor(kRed);
      good_pos_eCut[pmt]->SetLineStyle(1);
      good_pos_multCut[pmt]->SetLineColor(kBlue-7);
      good_pos_mult_eCut[pmt]->SetLineColor(kRed-10);

      legend_same(good_pos[pmt], good_pos_multCut[pmt], good_pos_eCut[pmt], good_pos_mult_eCut[pmt]);
      window_pos(good_pos[pmt]);
     
      
      //*********************************************************************************************//
      c2->cd(4); 
      gPad->Divide(2,1);
      gPad->cd(1);
      formatit_2d(good_pos_amp[pmt],"hit sel hcana ", "GoodTdcAdcTimeDiff_Pos(ns)", "PulseAmp", 0);
      
      c2->cd(4);
      gPad->cd(2);
      formatit_2d(good_pos_amp_multCut[pmt],"mult Cut ", "GoodTdcAdcTimeDiff_Pos(ns)", "PulseAmp", 0);
      
      
      c2->SaveAs(Form("plots/Pos_S1X_plane_Pmt%d_test.pdf", pmt+1));
      // diff_pos[0]->Draw();
       }
    
    // ofstream outfilemore("s1x_debug.txt");
    // ofstream outfileneed("s1x_need.txt");
    // ofstream outfilepos("s1x_pos.txt");
    // ofstream outfileneg("s1x_neg.txt");
    
    // Int_t nbinspos, nbinsneg, maxposbin, maxnegbin, maxposbinglobal, maxnegbinglobal;
    // Double_t maxposentries, maxnegentries, maxposxvalue, maxnegxvalue;
    
    // not nice that this is hardcoded
    // Double_t lowlimit = -80;
    // Double_t highlimit = 80.;
    // Double_t bins = 320.;
    // Double_t lines_pos_low[13];
    // Double_t lines_neg_low[13];
    // Double_t lines_pos_high[13];
    // Double_t lines_neg_high[13];
    
    // // cout << "index" << setw(20) << "maxposentries" << setw(20) << "maxposbin" << setw(20) << "maxposxvalue" << setw(20) << "maxnegentries" << setw(20) << "maxnegbin" << setw(20) << "maxnegxvalue" << endl;
    
    // for(Int_t mo = 0; mo < 13; mo++)
    //   {
    
    //     maxposentries = diff_pos[mo]->GetMaximum();
    //     maxnegentries = diff_neg[mo]->GetMaximum();
    //     maxposbin = diff_pos[mo]->GetMaximumBin();
    //     maxposxvalue = lowlimit + (highlimit-lowlimit)*maxposbin/bins;
    //     maxnegbin = diff_neg[mo]->GetMaximumBin();
    //     maxnegxvalue = lowlimit + (highlimit-lowlimit)*maxnegbin/bins;
    
    //     lines_neg_low[mo] = maxnegxvalue-30.;
    //     lines_pos_low[mo] = maxposxvalue-30.;
    //     lines_neg_high[mo] = maxnegxvalue+30.;
    //     lines_pos_high[mo] = maxposxvalue+30.;
    
    //     outfilemore << mo << setw(20) << maxposentries << setw(20) <<maxposbin << setw(20) << maxposxvalue << setw(20) << maxnegentries << setw(20) << maxnegbin << setw(20) << maxnegxvalue << endl;
    //     outfileneed << mo << setw(20) << maxposxvalue << setw(20) << (maxposxvalue-30.) << setw(20) << (maxposxvalue+30.) << setw(20) << maxnegxvalue << setw(20) << (maxnegxvalue-30.) << setw(20) << (maxnegxvalue+30.) << endl;
    //     outfilepos << mo << setw(20) << (maxposxvalue-30.) << setw(20) << (maxposxvalue+30.) << endl;
    //     outfileneg << mo << setw(20) << (maxnegxvalue-30.) << setw(20) << (maxnegxvalue+30.) << endl;
    
    //   }
    
    //  gStyle->SetOptStat(kTrue);
    // gStyle->SetCanvasColor(10);
    // gStyle->SetFrameFillColor(10);
    // gStyle->SetCanvasBorderMode(0);
    // gStyle->SetPadBorderMode(0);
    // gStyle->SetPalette(1,0);
    
    // gStyle->SetOptStat(0);
    
    // TCanvas *c7000 = new TCanvas("c7000","",900,900);
    // gPad->SetLogy();
    // tdc_ref_Time->SetLabelSize(0.024, "x");
    // tdc_ref_Time->SetLabelSize(0.024, "y");
    // tdc_ref_Time->GetXaxis()->SetTitle("SHMS Hodo ref time: T.shms.pT1_tdcTimeRaw");
    // tdc_ref_Time->Draw();
    // c7000->Print("tdc_hodo_ref_time.png");
    
    // TCanvas *c70001 = new TCanvas("c70001","",900,900);
    // gPad->SetLogy();
    // tdc_ref_Time2yt->SetLabelSize(0.024, "x");
    // tdc_ref_Time2yt->SetLabelSize(0.024, "y");
    // tdc_ref_Time2yt->GetXaxis()->SetTitle("SHMS Hodo ref time: T.shms.pT2_tdcTimeRaw");
    // tdc_ref_Time2yt->Draw();
    // // c70001->Print("tdc_hodo_ref_time_2yt.png");
    
    // TCanvas *c8000 = new TCanvas("c8000","",900,900);
    // gPad->SetLogy();
    // adc_ref_Time->SetLabelSize(0.024, "x");
    // adc_ref_Time->SetLabelSize(0.024, "y");
    // adc_ref_Time->GetXaxis()->SetTitle("SHMS Hodo ref time: T.shms.pFADC_TREF_ROC2_adcPulseTimeRaw");
    // adc_ref_Time->Draw();
    // // c8000->Print("adc_hodo_ref_time.png");
    
    // TCanvas *c100 = new TCanvas("c100","",900,900);
    // c100->Divide(2,2);
    // c100->cd(1);
    // formatit(diff_pos[0],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_0(ns)","Events",0,lines_pos_low[0],lines_pos_high[0]);
    // //  formatit_same(difft_pos_good[0],"","TdcAdcTimeDiff_Pos_0(ns)","Events",0);
    // c100->cd(2);
    // formatit(diff_neg[0],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_0(ns)","Events",0,lines_neg_low[0],lines_neg_high[0]);
    // //  formatit_same(difft_neg_good[0],"","TdcAdcTimeDiff_Neg_0(ns)","Events",0);
    // c100->cd(3);
    // formatit(diff_pos[1],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_1(ns)","Events",0,lines_pos_low[1],lines_pos_high[1]);
    // //  formatit_same(difft_pos_good[1],"","TdcAdcTimeDiff_Pos_1(ns)","Events",0);
    // c100->cd(4);
  // formatit(diff_neg[1],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_1(ns)","Events",0,lines_neg_low[1],lines_neg_high[1]);
  //  formatit_same(difft_neg_good[1],"","TdcAdcTimeDiff_Neg_1(ns)","Events",0);
  //c100->Print("s1x_1.png");

  // TCanvas *c200 = new TCanvas("c200","",900,900);
  // c200->Divide(2,2);
  // c200->cd(1);
  // formatit(diff_pos[2],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_2(ns)","Events",0,lines_pos_low[2],lines_pos_high[2]);
  // //  formatit_same(difft_pos_good[2],"","TdcAdcTimeDiff_Pos_2(ns)","Events",0);
  // c200->cd(2);
  // formatit(diff_neg[2],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_2(ns)","Events",0,lines_neg_low[2],lines_neg_high[2]);
  // //  formatit_same(difft_neg_good[2],"","TdcAdcTimeDiff_Neg_2(ns)","Events",0);
  // c200->cd(3);
  // formatit(diff_pos[3],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_3(ns)","Events",0,lines_pos_low[3],lines_pos_high[3]);
  // //  formatit_same(difft_pos_good[3],"","TdcAdcTimeDiff_Pos_3(ns)","Events",0);
  // c200->cd(4);
  // formatit(diff_neg[3],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_3(ns)","Events",0,lines_neg_low[3],lines_neg_high[3]);
  // //  formatit_same(difft_neg_good[3],"","TdcAdcTimeDiff_Neg_3(ns)","Events",0);
  // // c200->Print("s1x_2.png");

  // TCanvas *c300 = new TCanvas("c300","",900,900);
  // c300->Divide(2,2);
  // c300->cd(1);
  // formatit(diff_pos[4],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_4(ns)","Events",0,lines_pos_low[4],lines_pos_high[4]);
  // //  formatit_same(difft_pos_good[4],"","TdcAdcTimeDiff_Pos_4(ns)","Events",0);
  // c300->cd(2);
  // formatit(diff_neg[4],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_4(ns)","Events",0,lines_neg_low[4],lines_neg_high[4]);
  // //  formatit_same(difft_neg_good[4],"","TdcAdcTimeDiff_Neg_4(ns)","Events",0);
  // c300->cd(3);
  // formatit(diff_pos[5],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_5(ns)","Events",0,lines_pos_low[5],lines_pos_high[5]);
  // //  formatit_same(difft_pos_good[5],"","TdcAdcTimeDiff_Pos_5(ns)","Events",0);
  // c300->cd(4);
  // formatit(diff_neg[5],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_5(ns)","Events",0,lines_neg_low[5],lines_neg_high[5]);
  // //  formatit_same(difft_neg_good[5],"","TdcAdcTimeDiff_Neg_5(ns)","Events",0);
  // // c300->Print("s1x_3.png");

  // TCanvas *c400 = new TCanvas("c400","",900,900);
  // c400->Divide(2,2);
  // c400->cd(1);
  // formatit(diff_pos[6],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_6(ns)","Events",0,lines_pos_low[6],lines_pos_high[6]);
  // //  formatit_same(difft_pos_good[6],"","TdcAdcTimeDiff_Pos_6(ns)","Events",0);
  // c400->cd(2);
  // formatit(diff_neg[6],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_6(ns)","Events",0,lines_neg_low[6],lines_neg_high[6]);
  // //  formatit_same(difft_neg_good[6],"","TdcAdcTimeDiff_Neg_6(ns)","Events",0);
  // c400->cd(3);
  // formatit(diff_pos[7],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_7(ns)","Events",0,lines_pos_low[7],lines_pos_high[7]);
  // //  formatit_same(difft_pos_good[7],"","TdcAdcTimeDiff_Pos_7(ns)","Events",0);
  // c400->cd(4);
  // formatit(diff_neg[7],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_7(ns)","Events",0,lines_neg_low[7],lines_neg_high[7]);
  // //  formatit_same(difft_neg_good[7],"","TdcAdcTimeDiff_Neg_7(ns)","Events",0);
  // // c400->Print("s1x_4.png");

  // TCanvas *c500 = new TCanvas("c500","",900,900);
  // c500->Divide(2,2);
  // c500->cd(1);
  // formatit(diff_pos[8],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_8(ns)","Events",0,lines_pos_low[8],lines_pos_high[8]);
  // //  formatit_same(difft_pos_good[8],"","TdcAdcTimeDiff_Pos_8(ns)","Events",0);
  // c500->cd(2);
  // formatit(diff_neg[8],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_8(ns)","Events",0,lines_neg_low[8],lines_neg_high[8]);
  // //  formatit_same(difft_neg_good[8],"","TdcAdcTimeDiff_Neg_8(ns)","Events",0);
  // c500->cd(3);
  // formatit(diff_pos[9],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_9(ns)","Events",0,lines_pos_low[9],lines_pos_high[9]);
  // //  formatit_same(difft_pos_good[9],"","TdcAdcTimeDiff_Pos_9(ns)","Events",0);
  // c500->cd(4);
  // formatit(diff_neg[9],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_9(ns)","Events",0,lines_neg_low[9],lines_neg_high[9]);
  // //  formatit_same(difft_neg_good[9],"","TdcAdcTimeDiff_Neg_9(ns)","Events",0);
  // //c500->Print("s1x_5.png");

  // TCanvas *c700 = new TCanvas("c700","",900,900);
  // c700->Divide(2,2);
  // c700->cd(1);
  // formatit(diff_pos[10],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_10(ns)","Events",0,lines_pos_low[10],lines_pos_high[10]);
  // //  formatit_same(difft_pos_good[10],"","TdcAdcTimeDiff_Pos_10(ns)","Events",0);
  // c700->cd(2);
  // formatit(diff_neg[10],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_10(ns)","Events",0,lines_neg_low[10],lines_neg_high[10]);
  // //  formatit_same(difft_neg_good[10],"","TdcAdcTimeDiff_Neg_10(ns)","Events",0);
  // c700->cd(3);
  // formatit(diff_pos[11],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_11(ns)","Events",0,lines_pos_low[11],lines_pos_high[11]);
  // //  formatit_same(difft_pos_good[11],"","TdcAdcTimeDiff_Pos_11(ns)","Events",0);
  // c700->cd(4);
  // formatit(diff_neg[11],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_11(ns)","Events",0,lines_neg_low[11],lines_neg_high[11]);
  // //  formatit_same(difft_neg_good[11],"","TdcAdcTimeDiff_Neg_11(ns)","Events",0);
  // c700->Print("s1x_6.png");


  // TCanvas *c800 = new TCanvas("c800","",900,900);
  // c800->Divide(2,2);
  // c800->cd(1);
  // formatit(diff_pos[12],"SHMS S1X, no cuts","TdcAdcTimeDiff_Pos_12(ns)","Events",0,lines_pos_low[12],lines_pos_high[12]);
  // //  formatit_same(difft_pos_good[12],"","TdcAdcTimeDiff_Pos_12(ns)","Events",0);
  // c800->cd(2);
  // formatit(diff_neg[12],"SHMS S1X, no cuts","TdcAdcTimeDiff_Neg_12(ns)","Events",0,lines_neg_low[12],lines_neg_high[12]);
  //  formatit_same(difft_neg_good[12],"","TdcAdcTimeDiff_Neg_12(ns)","Events",0);

  // c800->Print("s1x_7.png");



  return 0;

}
