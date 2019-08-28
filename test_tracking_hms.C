#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>
#include <TGraph.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <TSystem.h>
#include <TString.h>
#include <TCut.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TChain.h>
#include <TTree.h>
#include <TF1.h>

using namespace std;

const Int_t NRUNS1 =203;

void test(){

  TFile *f1[NRUNS1];
  TTree *t1[NRUNS1];
  TTree *s1[NRUNS1];


  TH1D *h1[NRUNS1];
  TH1D *h2[NRUNS1];

  Double_t did1[NRUNS1];
  Double_t should1[NRUNS1];
  Double_t efficiency1[NRUNS1];
  Double_t error1[NRUNS1];
TGraphErrors * gr = new TGraphErrors();
  


//Int_t rruns1[NRUNS1] = {7593, 7594, 7595, 7596, 7597, 7599, 7600, 7601, 7602, 7603, 7604, 7635, 7636, 7637, 7638, 7639,7727,7728, 7730, 7733, 7735, 7736, 7765, 7766, 7767, 7768, 7769, 7770, 7771, 7772};

 Int_t rruns1[NRUNS1] = 
{7593, 7594, 7595,7596, 7597, 7599, 7600, 7601, 7602, 7603, 7604, 7605, 7606, 7607, 7608, 7609, 7610, 7611, 7612, 7613, 7614, 7615, 7616, 7617, 7618, 7619, 7620, 7621, 7622, 7623, 7625, 7626, 7627, 7628, 7629, 7630, 7631, 7632, 7633, 7634, 7635, 7636, 7637, 7638, 7639, 7640, 7641, 7642, 7643, 7644, 7645, 7646, 7647, 7648, 7649, 7650, 7651, 7652, 7654, 7655, 7657, 7658, 7659, 7660, 7661, 7662, 7663, 7666, 7667, 7668, 7669 ,7670 ,7671, 7672, 7673, 7674, 7675, 7676, 7677, 7678, 7679, 7680, 7681, 7682, 7684, 7685, 7686, 7687, 7688, 7689, 7690, 7692, 7694, 7695, 7697, 7698, 7699, 7702, 7703, 7706, 7707, 7708, 7709, 7710, 7711, 7712, 7713, 7714, 7715, 7716, 7717, 7718, 7719, 7720, 7721, 7722, 7723, 7724, 7725, 7727, 7728, 7730, 7733, 7735, 7736, 7737, 7738, 7739, 7740, 7741, 7742, 7743, 7747, 7748, 7749, 7750, 7751, 7752, 7753, 7754, 7755, 7757, 7758, 7759, 7760, 7762, 7763, 7765, 7766, 7768, 7769, 7770, 7771, 7772, 7773, 7774, 7775, 7776, 7777, 7778, 7779, 7781, 7782, 7783, 7784, 7785, 7786, 7787, 7790, 7791, 7792, 7793, 7794, 7796, 7797, 7798, 7799, 7800, 7801, 7802, 7803, 7804, 7805, 7806, 7807, 7808, 7809, 7811, 7812, 7813, 7814, 7815, 7816, 7817, 7820, 7822, 7823, 7824, 7826, 7827, 7828, 7829, 7830  };//, 7596, 7597, 7635, 7636, 7637, 7671, 7672, 7699, 7702, 7703, 7735, 7736, 7768, 7769, 7770, 7771};


  for (int i=0; i<NRUNS1;i++){
    f1[i]= new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/tracking/coin_replay_production_%d_-1.root",rruns1[i]),"read");
    t1[i]= (TTree *)f1[i]->Get("TSP");
    s1[i]= (TTree *)f1[i]->Get("T");

    auto nEntries1 = t1[i]->GetEntries();
    t1[i]->GetEntry(nEntries1 -1);

    h1[i] =new TH1D("h1[i]", "h2_Beta",200, 0.6, 1.4);
    h2[i] =new TH1D("h2[i]", "h2_Beta",200, 0.6, 1.4);

 //    s1[i]->Draw("H.gtr.beta>>h1[i]","P.gtr.dp>5&&P.gtr.dp<20 && P.cal.etottracknorm> 0.15 && P.cal.etottracknorm<0.4 && P.aero.npeSum> 0.5 && P.cal.eprtracknorm>0&&P.cal.eprtracknorm<0.15&& P.gtr.beta>0.7&&P.gtr.beta<1.3 && H.cal.etottracknorm>0.8&&H.cal.etottracknorm<1.2&& H.gtr.dp>-10&&H.gtr.dp<10 && H.gtr.beta>0.7&&H.gtr.beta<1.3 && H.cer.npeSum>0.0 && P.hgcer.npeSum>0.5","");//did_cut

// s1[i]->Draw("H.gtr.beta>>h2[i]","P.gtr.dp>5&&P.gtr.dp<20 && P.cal.etottracknorm> 0.15 && P.cal.etottracknorm<0.4 && P.aero.npeSum> 0.5 && P.cal.eprtracknorm>0&&P.cal.eprtracknorm<0.15&& P.gtr.beta>0.7&&P.gtr.beta<1.3 && H.cal.etottracknorm>0.8&&H.cal.etottracknorm<1.2&& H.gtr.dp>-10&&H.gtr.dp<10 && H.gtr.beta>0.7&&H.gtr.beta<1.3  ","");//did_cut

 s1[i]->Draw("H.gtr.beta>>h1[i]", "H.hod.goodscinhit==1 && H.hod.betanotrack > 0.5 && H.hod.betanotrack < 1.4 && (H.dc.1x1.nhit + H.dc.1u2.nhit + H.dc.1u1.nhit + H.dc.1v1.nhit + H.dc.1x2.nhit + H.dc.1v2.nhit) < 21 && (H.dc.2x1.nhit + H.dc.2u2.nhit + H.dc.2u1.nhit + H.dc.2v1.nhit + H.dc.2x2.nhit + H.dc.2v2.nhit) < 21 && H.cer.npeSum > 0.0  &&H.dc.ntrack>0.","goff");  //did_cut

s1[i]->Draw("H.gtr.beta>>h2[i]", "H.hod.goodscinhit==1 && H.hod.betanotrack > 0.5 && H.hod.betanotrack < 1.4 && (H.dc.1x1.nhit + H.dc.1u2.nhit + H.dc.1u1.nhit + H.dc.1v1.nhit + H.dc.1x2.nhit + H.dc.1v2.nhit) < 21 && (H.dc.2x1.nhit + H.dc.2u2.nhit + H.dc.2u1.nhit + H.dc.2v1.nhit + H.dc.2x2.nhit + H.dc.2v2.nhit) < 21 && H.cer.npeSum > 0.0","goff"); //should_cut


 did1[i] = h1[i]->GetEntries();
 should1[i] = h2[i]->GetEntries();
 efficiency1[i]= did1[i]/should1[i];
 error1[i]= (1/should1[i]) * sqrt(did1[i]*(1-did1[i]/should1[i]));
 cout<<rruns1[i]<< "   "<</*" Entries = "<<nEntries1<<  "   "<<*/ "did  = "<<did1[i]<<"  "<<"should  = " <<should1[i]<<"  "<<"eff  = "<<  efficiency1[i]<< " " <<"error = " <<error1[i]<<""<<endl;

 gr->SetPoint(i, rruns1[i], efficiency1[i]);
 gr->SetPointError(i, 0, error1[i]);

  }
  TCanvas *c1 =new TCanvas("c1", "", 500, 500);
  gr->Draw("AP*"); 
  c1->SaveAs("pdf/hms_tracking_eff.pdf");

}
