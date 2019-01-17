#include <iostream>
#include <cmath>
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"

#include "TCanvas.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TStyle.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/VectorUtil.h"
R__LOAD_LIBRARY(libMathMore.so)
R__LOAD_LIBRARY(libGenVector.so)

#include "THStack.h"
#include "TBufferJSON.h"

#include "nlohmann/json.hpp"

#include "THcParmList.h"
R__LOAD_LIBRARY(libPodd.so)
R__LOAD_LIBRARY(libHallA.so)
R__LOAD_LIBRARY(libdc.so)
R__LOAD_LIBRARY(libHallC.so)

// fmt - string formatting library
#include "fmt/core.h"
#include "fmt/ostream.h"
R__LOAD_LIBRARY(libfmt.so)

using Pvec3D   = ROOT::Math::XYZVector;
using Pvec4D   = ROOT::Math::PxPyPzMVector;

// VecOps::RVec is like std::vector with some extra bells and whistles 
using inters   = ROOT::VecOps::RVec<int>;
using doublers = ROOT::VecOps::RVec<double>;
using floaters = ROOT::VecOps::RVec<float>;
using shorters = ROOT::VecOps::RVec<short>;

void bean_test(int RunNumber = 6018, int nevents = -1, const char* codatype = "COIN") {

  std::string coda_type = codatype;
  //std::string coda_type = "SHMS";
  //std::string coda_type = "COIN";

  std::string rootfile  = "ROOTfiles_online/";
  //kstd::string rootfile  = "/net/cdaq/cdaql3data/cdaq/sidis-fall-18/ROOTfiles_online/";
  //std::string rootfile    = std::string("ROOTfiles/coin_replay_production_");
  rootfile    += std::string("coin_replay_production_");

  if (coda_type == "SHMS") {
    rootfile = std::string(
      "ROOTfiles/shms_replay_production_all_");
    // + std::to_string(RunNumber) + "_50000.root";
  }
  rootfile += std::to_string(RunNumber) + "_" + std::to_string(nevents) + ".root";

  std::string run_list_json  = "DBASE/run_list.json";

  auto file = new TFile(rootfile.c_str());
  //new TBrowser;

  ROOT::EnableImplicitMT(4);

  Pvec4D  Pbeam(0,0,10.598,0.000511);

  ROOT::RDataFrame d("T",rootfile);
  ROOT::RDataFrame d_sh("TSH",rootfile);

  std::string hpdelta = "P.gtr.dp > -10 && P.gtr.dp < 20 && H.gtr.dp > -10 && H.gtr.dp < 10";
  std::string epiCut  = "P.aero.npeSum > 1.0 && P.cal.eprtracknorm < 0.2 "
                        "&& H.cer.npeSum > 1.0 && H.cal.etottracknorm > 0.6 "
                        "&& H.cal.etottracknorm < 2.0 && H.cal.eprtracknorm  > 0.2"; 

  auto d0 = d
  .Define("hms_e_EoverP",
          [](doublers& EOverP) {
            return EOverP[EOverP > 0.5 && EOverP < 1.8];
          }, {"H.cal.etottracknorm"})
  .Define("hms_e_EoverP_nGood",
          [](doublers& EOverP) {
            return (int)EOverP.size();
          }, {"hms_e_EoverP"})
  .Define("shms_pi_preshower",
          [](doublers& EOverP) {
            return EOverP[EOverP < 0.2];
          }, {"P.cal.eprtracknorm"})
  .Define("shms_pi_preshower_nGood",
          [](doublers& EOverP) {
            return (int)EOverP.size();
          }, {"shms_pi_preshower"})
  ;


  auto d2 = d0
    .Filter([](double npe){return npe>1.0;},{"H.cer.npeSum"})
    .Filter(
      [](int n_good) {
        if( n_good >0 ) {
          return true;
        }
        return  false;
      },{"hms_e_EoverP_nGood"});

  auto d3 = d2
  .Filter(
    [](int n_good) {
        if( n_good >0 ) {
          return true;
        }
      return  false;
    },{"shms_pi_preshower_nGood"});


  auto d_spec_cuts  = d2
  .Filter(hpdelta)
  .Filter(epiCut);

  // Find the coin peak 
  auto   h_coin_time      = d_spec_cuts.Histo1D({"coin_time","coin_time",800,0,100},"CTime.ePiCoinTime_ROC2");
  int    coin_peak_bin    = h_coin_time->GetMaximumBin();
  double coin_peak_center = h_coin_time->GetBinCenter(coin_peak_bin);
  //std::cout << " coin peak at " << coin_peak_center << " ns\n";
    
  // Cut on the coin time 
  auto d_coin_time_cut = d_spec_cuts .Filter([=](double coin_time) {return std::abs(coin_time - coin_peak_center)< 2.0;},{"CTime.ePiCoinTime_ROC2"});
  auto h_coin_time2    = d_coin_time_cut.Histo1D({"coin_time2","coin_time2",800,0,100},"CTime.ePiCoinTime_ROC2");

  auto d_random     = d_spec_cuts.Filter([=](double coin_time) {return std::abs(coin_time - coin_peak_center-28)< 10.0;},{"CTime.ePiCoinTime_ROC2"});
  auto h_coin_time3 = d_random.Histo1D({"coin_time2","coin_time2",800,0,100},"CTime.ePiCoinTime_ROC2");

  auto d2_2    = d_coin_time_cut.Filter("fEvtHdr.fEvtType == 2");
  auto d2_coin = d_coin_time_cut.Filter("(fEvtHdr.fEvtType == 6) || (fEvtHdr.fEvtType == 4)");

  // Histograms lazy evaluated -> Nothing happens until they are used below (eg Draw() is called) 
  auto h_EOverP_0       = d0.Histo1D<doublers>({"hms_e_EoverP_0","SHMS total shower; SHMS E/P",    100,0.05,1.8},"P.cal.etottracknorm");
  auto h_EOverP_2       = d2.Histo1D<doublers>({"hms_e_EoverP_2","SHMS total shower; SHMS E/P",    100,0.05,1.8},"P.cal.etottracknorm");
  auto h_EOverP_3       = d3.Histo1D<doublers>({"hms_e_EoverP_3","SHMS total shower; SHMS E/P",    100,0.05,1.8},"P.cal.etottracknorm");

  auto h_EprOverP_0       = d0.Histo1D<doublers>({"hms_e_EoverP_0","SHMS pre-shower; SHMS E/P",    100,0.05,1.8},"P.cal.eprtracknorm");
  auto h_EprOverP_2       = d2.Histo1D<doublers>({"hms_e_EoverP_2","SHMS pre-shower; SHMS E/P",    100,0.05,1.8},"P.cal.eprtracknorm");
  auto h_EprOverP_3       = d3.Histo1D<doublers>({"hms_e_EoverP_3","SHMS pre-shower; SHMS E/P",    100,0.05,1.8},"P.cal.eprtracknorm");

  //auto h_EOverP_1       = d0.Histo1D<doublers>({"hms_e_EoverP_1","E/P cut; HMS E/P",100,0.05,1.8},"hms_e_EoverP");
  //auto h_EOverP_nGood_0 = d0.Histo1D({"h_EOverP_nGood_0","h_EOverP_nGood_0",10,0,10},"P.cal.ntracks");
  //auto h_EOverP_nGood_1 = d0.Histo1D({"h_EOverP_nGood_1","h_EOverP_nGood_0",10,0,10},"hms_e_EoverP_nGood");

  auto h_event_type = d0.Histo1D({"event_type","event_type",10,0,10},"fEvtHdr.fEvtType");

  auto total_charge = d_sh.Sum("H.BCM4A.scalerCurrent");

  auto d_beans = d2_coin .Filter("P.hgcer.npeSum>1.0");

  auto hms_electron_counts  =  d2.Count();
  auto hms_electron_counts2 = d2_2.Count();
  auto coin_counts          = d2_coin.Count();

  auto rand_bg_count = d_random.Count();

  auto bean_count = d_beans.Count();
  auto pion_count = d_beans.Count();
  //auto disp = d2.Display("fEvtHdr.fEvtType");

  //disp->Print();
  double random_bg    = double(*rand_bg_count)/5.0;
  double hms_e_yield  = (*hms_electron_counts) /(*total_charge);
  double hms_e_yield2 = (*hms_electron_counts2)/(*total_charge);
  double coin_yield   = (*coin_counts)/(*total_charge);

  double pi_K_ratio = double(*pion_count)/(double(*coin_counts)- double(*pion_count));
  double kaon_counts = (double(*coin_counts)- double(*pion_count));

  {
    std::ofstream outfile("coin_yields.txt",std::ofstream::app);
  outfile 
  <<  RunNumber << "    xxxxxx    "  
  <<  double(*coin_counts) << "   " 
  << random_bg <<  "   " 
  << *pion_count <<  "   " 
  << double(*pion_count) - random_bg*double(*pion_count)/(double(*coin_counts))  << "    " 
  << pi_K_ratio <<  "   " 
  <<  "   \n" ;
  }

  std::cout << " ----------------------------------------------    \n" ;
  std::cout << " # of good coin  = " << int(double(*pion_count) - random_bg*double(*pion_count)/(double(*coin_counts)) ) << "    \n" ;
  std::cout << " ----------------------------------------------    \n" ;
  //std::cout << " pions+kaons   : " << *coin_counts << "\n";
  //std::cout << " pions         : " << *pion_count << "\n";
  //std::cout << " random        : " << random_bg << "\n";
  //std::cout << " ratio         : "  << pi_K_ratio << " \n";


  //std::cout << " counts  : " << *hms_electron_counts << "\n";
  //std::cout << " charge  : " << *total_charge << " uC\n";
  //std::cout << " yield   : " << (*hms_electron_counts)  << " cnts, " << hms_e_yield  << " cnts/uC\n";
  //std::cout << " singles : " << (*hms_electron_counts2) << " cnts, " << hms_e_yield2 << " cnts/uC\n";
  //std::cout << " coin    : " << (*coin_counts) << " cnts, " << coin_yield << " cnts/uC\n";

  //auto s_dc_x_fp           = d2.Histo1D({"s_dc_x_fp ","xy fp; x",100,-50,50}, "P.dc.x_fp");
  //auto s_dc_y_fp           = d2.Histo1D({"s_dc_y_fp ","xy fp; y",100,-50,50}, "P.dc.y_fp");
  //auto s_dc_xp_fp          = d2.Histo1D({"s_dc_xp_fp","xy fp; xp",100,-50,50},"P.dc.xp_fp");
  //auto s_dc_yp_fp          = d2.Histo1D({"s_dc_yp_fp","xy fp; xp",100,-50,50},"P.dc.yp_fp");
  
  // -----------------------------------------------------------
  //
  TCanvas* c = nullptr;
  int b1 = 0;
  int b2 = 0;
  double hmax = 0.0;
  THStack*  hs = nullptr;
  //TLatex latex;

  // ---------------------------------------------------------
  //
  c = new TCanvas();
  c->Divide(2,2);
  c->cd(1);

  // This call starts the loop over the data.
  // A DrawCopy is used so that the histogram is not deleted at the end of 
  // scope, and thus stays visible on the canvas.
  h_EOverP_0->DrawCopy();

  c->cd(2);
  h_EOverP_2->DrawCopy();

  c->cd(3);
  h_event_type->DrawCopy();

  c->cd(4);
  h_coin_time->DrawCopy();
  h_coin_time2->SetLineColor(4);
  h_coin_time2->DrawCopy("same");
  h_coin_time3->SetLineColor(2);
  h_coin_time3->DrawCopy("same");

  gPad->BuildLegend();

  gSystem->mkdir("results/df_example", true);
  c->SaveAs((std::string("results/df_example/c1_")+std::to_string(RunNumber)+".pdf").c_str());
  c->SaveAs((std::string("results/df_example/c1_")+std::to_string(RunNumber)+".png").c_str());
  
  // ---------------------------------------------------------
  //
  c = new TCanvas();
  hs = new THStack("SHMS_cal","SHMS calorimeter; E/P");

  h_EOverP_0->SetLineColor(1);
  h_EOverP_2->SetLineColor(4);
  h_EOverP_3->SetLineColor(2);
  h_EprOverP_0->SetLineColor(8);
  h_EprOverP_2->SetLineColor(6);
  h_EprOverP_3->SetLineColor(9);

  hs->Add((TH1*)h_EOverP_0->Clone());
  hs->Add((TH1*)h_EOverP_2->Clone());
  hs->Add((TH1*)h_EOverP_3->Clone());

  hs->Add((TH1*)h_EprOverP_0->Clone());
  hs->Add((TH1*)h_EprOverP_2->Clone());
  hs->Add((TH1*)h_EprOverP_3->Clone());

  hs->Draw("nostack");
  gPad->SetLogy(true);
  gPad->BuildLegend();

  c->SaveAs((std::string("results/df_example/c2_")+std::to_string(RunNumber)+".pdf").c_str());
  c->SaveAs((std::string("results/df_example/c2_")+std::to_string(RunNumber)+".png").c_str());

}
