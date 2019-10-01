#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>
#define NRUNS 3
using namespace std;

void cal_check(){
  Int_t runs[NRUNS] = {6359,6545,6524};//

  //Int_t runs[NRUNS] = { 6290, 6291, 6292, 6293, 6306};//, 6307, 6308, 6348, 6349, 6350, 6351, 6259, 6360, 6367, 6370, 6375, 6376, 6377, 6378, 6379, 6380, 6381, 6524, 6525, 6526, 6527, 6528, 6529  };//7593, 7594, 7595, 7596, 7597, 7599, 7600, 7601, 7602, 7603, 7604, 7605, 7606, 7607, 7608, 7609, 7610, 7611, 7612, 7613, 7614, 7615, 7616, 7617, 7618, 7619, 7620, 7621, 7622, 7623, 7625, 7626, 7627, 7628, 7629, 7630, 7631, 7632, 7633, 7634, 7635, 7636, 7637, 7638, 7639, 7640, 7641, 7642, 7643, 7644, 7645, 7646, 7647, 7648, 7649, 7650, 7651, 7652, 7654, 7655, 7657, 7658, 7659, 7660, 7661, 7662, 7663, 7666, 7667, 7668, 7669 ,7670 ,7671, 7672, 7673, 7674, 7675, 7676, 7677, 7678, 7679, 7680, 7681, 7682, 7684, 7685, 7686, 7687, 7688, 7689, 7690, 7692, 7694, 7695, 7697, 7698, 7699, 7702, 7703, 7706, 7707, 7708, 7709, 7710, 7711, 7712, 7713, 7714, 7715, 7716, 7717, 7718, 7719, 7720, 7721, 7722, 7723, 7724, 7725, 7727, 7728, 7730, 7733, 7735, 7736, 7737, 7738, 7739, 7740, 7741, 7742, 7743, 7747, 7748, 7749, 7750, 7751, 7752, 7753, 7754, 7755, 7757, 7758, 7759, 7760, 7762, 7763, 7765, 7766, 7768, 7769, 7770, 7771, 7772, 7773, 7774, 7775, 7776, 7777, 7778, 7779, 7781, 7782, 7783, 7784, 7785, 7786, 7787, 7790, 7791, 7792, 7793, 7794, 7796, 7797, 7798, 7799, 7800, 7801, 7802, 7803, 7804, 7805, 7806, 7807, 7808, 7809, 7811, 7812, 7813, 7814, 7815, 7816, 7817, 7820, 7822, 7823, 7824, 7826, 7827, 7828, 7829, 7830};//{7593,7594,7777};//, 6095, 6099, 6103, 6111, 6118, 6122, 6127, 6141, 6241, 6245, 6253, 6257, 6264, 6271, 6277, 6287, 6290, 6293, 6297,6351, 6358, 6360, 6368, 6376, 6381, 6453, 6459, 6465, 6475, 6485, 6489, 6493, 6498};


  TFile *f[NRUNS];
  TTree *t[NRUNS];
  TH1F *h1[NRUNS];
  TH2F *h2[NRUNS];
  TH2F *h3[NRUNS];
  TH2F *h4[NRUNS];
  TH1F *h5[NRUNS];
  TH1F *h6[NRUNS];
  TH1F *h10[NRUNS];
  TH2F *h11[NRUNS];

  TCanvas *c1[NRUNS];
  TCanvas *c2[NRUNS];

  for(Int_t i=0; i<NRUNS; i++){
    // f[i]=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/check_cal_calib_sep30/cal_run_pim_11deg_4p2_%d.root", runs[i]),"read");

    f[i]=new TFile(Form("coin_replay_production_%d_-1.root", runs[i]),"read");
    t[i]=(TTree *)f[i]->Get("T");

    h1[i] = new TH1F(Form("h1[%d]", i), Form(""),100, 0.001, 1.8);
    h1[i]->SetLineWidth(2);
    h1[i]->SetLineColor(kBlue);
    h1[i]->SetTitle(Form("shms_P.cal.etottracknorm_Run_%d",runs[i]));
    h1[i]->GetYaxis()->SetTitle("Entries");
    h1[i]->GetYaxis()->CenterTitle();
    h1[i]->GetXaxis()->SetTitle("pcal with -10<dp<20, 0.5<beta<1.5");
    h1[i]->GetXaxis()->CenterTitle();
    h1[i]->GetXaxis()->SetTitleOffset(1.2);


    h5[i] = new TH1F(Form("h5[%d]", i), Form(""),100, 0.001, 1.8);
    h5[i]->SetLineWidth(2);
    h5[i]->SetLineColor(kBlue);
    h5[i]->SetTitle(Form("shms_P.cal.etottracknorm_Run_%d",runs[i]));
    h5[i]->GetYaxis()->SetTitle("Entries");
    h5[i]->GetYaxis()->CenterTitle();
    h5[i]->GetXaxis()->SetTitle("pcal with -10<dp<20, 0.5<beta<1.5, aero>2 && hgc>2");
    h5[i]->GetXaxis()->CenterTitle();
    h5[i]->GetXaxis()->SetTitleOffset(1.2);

    
    h6[i] = new TH1F(Form("h6[%d]", i), Form(""),100, 0.001, 1.8);
    h6[i]->SetLineWidth(2);
    h6[i]->SetLineColor(kBlue);
    h6[i]->SetTitle(Form("shms_P.cal.etottracknorm_Run_%d",runs[i]));
    h6[i]->GetYaxis()->SetTitle("Entries");
    h6[i]->GetYaxis()->CenterTitle();
    h6[i]->GetXaxis()->SetTitle("pcal with -10<dp<20, 0.5<beta<1.5, hgc >10");
    h6[i]->GetXaxis()->CenterTitle();
    h6[i]->GetXaxis()->SetTitleOffset(1.2);
    


    
    h10[i] = new TH1F(Form("h10[%d]", i), Form(""),100, 0.001, 1.8);
    h10[i]->SetLineWidth(2);
    h10[i]->SetLineColor(kBlue);
    h10[i]->SetTitle(Form("shms_P.cal.etottracknorm_Run_%d",runs[i]));
    h10[i]->GetYaxis()->SetTitle("Entries");
    h10[i]->GetYaxis()->CenterTitle();
    h10[i]->GetXaxis()->SetTitle("pcal with -10<dp<20, 0.5<beta<1.5, aero>2, hgc>25");
    h10[i]->GetXaxis()->CenterTitle();
    h10[i]->GetXaxis()->SetTitleOffset(1.2);
    //*********

    h2[i] = new TH2F(Form("h2[%d]", i), Form(""),100, 0.001, 1.8, 100, -15, 25);
    h2[i]->SetLineWidth(2);
    h2[i]->SetLineColor(kBlue);
    h2[i]->SetTitle(Form("shms_#delta_vs_pcal_etottracknorm_Run_%d",runs[i]));
    h2[i]->GetYaxis()->SetTitle("shms_delta");
    h2[i]->GetYaxis()->CenterTitle();
    h2[i]->GetXaxis()->SetTitle("  pcal with -10<dp<20, 0.5<beta<1.5, aero>2, hgc>2");
    h2[i]->GetXaxis()->CenterTitle();
    h2[i]->GetXaxis()->SetTitleOffset(1.2);
    
  
    h3[i] = new TH2F(Form("h3[%d]", i), Form(""),100, 0.001, 1.8, 100, -15, 25);
    h3[i]->SetLineWidth(2);
    h3[i]->SetLineColor(kBlue);
    h3[i]->SetTitle(Form("shms_#delta_vs_pcal_etottracknorm_Run_%d",runs[i]));
    h3[i]->GetYaxis()->SetTitle("shms_delta vs pcal");
    h3[i]->GetYaxis()->CenterTitle();
    h3[i]->GetXaxis()->SetTitle("pcal with -10<dp<20, 0.5<beta<1.5, aero>2, hgc>10");
    h3[i]->GetXaxis()->CenterTitle();
    h3[i]->GetXaxis()->SetTitleOffset(1.2);

    
    h4[i] = new TH2F(Form("h4[%d]", i), Form(""),100, 0, 30, 100, -15, 25);
    h4[i]->SetLineWidth(2);
    h4[i]->SetLineColor(kBlue);
    h4[i]->SetTitle(Form("shms_#delta_vs_hgc_Run_%d",runs[i]));
    h4[i]->GetYaxis()->SetTitle("shms_delta vs hgc");
    h4[i]->GetYaxis()->CenterTitle();
    h4[i]->GetXaxis()->SetTitle("hgcer with -10<dp<20, 0.5<beta<1.5, aero>2");
    h4[i]->GetXaxis()->CenterTitle();
    h4[i]->GetXaxis()->SetTitleOffset(1.2);

     
    h11[i] = new TH2F(Form("h11[%d]", i), Form(""),100, 0.001,1.5, 100, 0.001, 1.5);
    h11[i]->SetLineWidth(2);
    h11[i]->SetLineColor(kBlue);
    h11[i]->SetTitle(Form("shower_vs_pre-shower_Run_%d",runs[i]));
    h11[i]->GetYaxis()->SetTitle("shms_shower");
    h11[i]->GetYaxis()->CenterTitle();
    h11[i]->GetXaxis()->SetTitle("preshower with -10<dp<20, 0.5<beta<1.5 &&aero>2, hgc>2");
    h11[i]->GetXaxis()->CenterTitle();
    h11[i]->GetXaxis()->SetTitleOffset(1.2);


    gStyle->SetOptFit(1);
    c1[i] = new TCanvas(Form("c%d]", i),"",1500,1200); 
    c1[i]->Divide(2,2); 

    c1[i]->cd(1);gPad->SetGridx();
    t[i]->Draw(Form("P.cal.etottracknorm>>h1[%d]", i ),"P.gtr.dp>-15&&P.gtr.dp<25 && P.gtr.beta>0.5 && P.gtr.beta< 1.5");
    h1[i]->Fit("gaus","","",0.9, 1.1);


    c1[i]->cd(2);gPad->SetGridx();
    t[i]->Draw(Form("P.cal.etottracknorm>>h5[%d]", i ),"P.gtr.dp>-15&&P.gtr.dp<25 && P.gtr.beta>0.5 && P.gtr.beta< 1.5 &&P.aero.npeSum>2&&P.hgcer.npeSum>2");
    h5[i]->Fit("gaus","","",0.9, 1.1);


    c1[i]->cd(3);gPad->SetGridx();
    t[i]->Draw(Form("P.cal.etottracknorm>>h6[%d]", i ),"P.gtr.dp>-15&&P.gtr.dp<25 && P.gtr.beta>0.5 && P.gtr.beta< 1.5 &&P.hgcer.npeSum>10 && P.aero.npeSum>2");
    h6[i]->Fit("gaus","","",0.9, 1.1);


    c1[i]->cd(4);gPad->SetGridx();
    t[i]->Draw(Form("P.cal.etottracknorm>>h10[%d]", i ),"P.gtr.dp>-15&&P.gtr.dp<25 && P.gtr.beta>0.5 && P.gtr.beta< 1.5 &&P.hgcer.npeSum>25 &&P.aero.npeSum>2 ");
    h10[i]->Fit("gaus","","",0.9, 1.1);
    Double_t av[i] =  h10[i]->GetMean();
    cout<< "Mean = "<<av[i]<<endl;
    c1[i]->SaveAs(Form("sept30/1d_%d.pdf",runs[i]));


    //the following is the alternative way of gaus fit instead of the above last line
    // TString hist_name = Form("h1[%d]", i);
    // TH1F *hist = (TH1F*)gDirectory->Get(hist_name);
    // hist->Fit("gaus", "","",0.9, 1.1);
    c2[i] = new TCanvas(Form("c%d]", i),"",1500,1250); 
    c2[i]->Divide(2,2); 


    c2[i]->cd(1);/*gPad->SetGridx();*/gPad->SetLogz();
    t[i]->Draw(Form("P.gtr.dp:P.cal.etottracknorm>>h2[%d]", i ), " P.gtr.dp>-15 &&P.gtr.dp <25  && P.aero.npeSum >2 && P.hgcer.npeSum>2&& P.gtr.beta>0.5 && P.gtr.beta <1.5","colz");

    c2[i]->cd(2);gPad->SetLogz();
    t[i]->Draw(Form("P.gtr.dp:P.cal.etottracknorm>>h3[%d]", i ), " P.gtr.dp>-15 &&P.gtr.dp <25 && P.aero.npeSum>2 && P.hgcer.npeSum>10 && P.gtr.beta>0.5 && P.gtr.beta<1.5","colz ");
    // h3[i]->Fit("gaus","","",0.8,1.2);

    c2[i]->cd(3);gPad->SetGridx();gPad->SetLogz();
    t[i]->Draw(Form("P.gtr.dp:P.hgcer.npeSum>>h4[%d]", i ), "P.gtr.dp>-15 &&P.gtr.dp <25 && P.aero.npeSum>2 && P.gtr.beta>0.5&& P.gtr.beta<1.5","colz");

    c2[i]->cd(4);gPad->SetGridx();gPad->SetLogz();
    t[i]->Draw(Form("P.cal.etottracknorm-P.cal.eprtracknorm:P.cal.eprtracknorm>>h11[%d]", i ), "P.gtr.dp>-15 &&P.gtr.dp <25 && P.aero.npeSum>2&&P.hgcer.npeSum>2 && P.gtr.beta>0.5&& P.gtr.beta<1.5","colz");


    c2[i]->SaveAs(Form("sept30/2d_%d.pdf",runs[i]));

    // c1[i]->~TCanvas();//not to display the histogram in terminal;

  }
}
