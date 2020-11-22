#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include <math.h>
#include <iostream>

double costh(double m, double p) {
   return std::sqrt(p*p+m*m)/(p*1.0006349);
  }
double npe(double m, double p) {
   return 1-(p*p+m*m)/(p*p*1.0006349*1.0006349);
  }

void Cerenkov_N(){
  TF1 *f1 = new TF1("pi;theta;momentum","std::acos(std::sqrt(x*x+0.139*0.139)/(x*1.0006349))*180/3.14159",3.9,10);
  f1->GetXaxis()->SetTitle("momentum");
  f1->GetYaxis()->SetTitle("theta");
  TCanvas *c_pion_p = new TCanvas();
  f1->Draw();
  f1->SetTitle("pi");
  c_pion_p->SaveAs("results/cer_angle_pi_p.pdf");

  TF1 *f11 = new TF1("pi;cos(th);momentum","std::sqrt(x*x+0.139*0.139)/(x*1.0006349)",3.9,10);
  f11->GetXaxis()->SetTitle("momentum");
  f11->GetYaxis()->SetTitle("cos(th)");
  TCanvas *c_pion_p_cos = new TCanvas();
  f11->Draw();
  f11->SetTitle("pi");
  c_pion_p_cos->SaveAs("results/cer_costh_pi_p.pdf");

  TF1 *fe = new TF1("e;cos(th);momentum","std::sqrt(x*x+0.00051*0.00051)/(x*1.0006349)",0,10);
  fe->GetXaxis()->SetTitle("momentum");
  fe->GetYaxis()->SetTitle("cos(th)");
  TCanvas *c_electron_p = new TCanvas();
  fe->Draw();
  fe->SetTitle("e");
  c_electron_p->SaveAs("results/cer_costh_e_p.pdf");
  
  TF1 *f1m = new TF1("pi;cos(th);mass","std::sqrt(6.358*6.358+x*x)/(6.358*1.0006349)",0,0.4);
  f1m->SetTitle("6.358");
  TF1 *f1m2 = new TF1("pi;cos(th);mass","std::sqrt(4.357*4.357+x*x)/(4.357*1.0006349)",0,0.4);
  f1m2->SetTitle("4.357");
  TF1 *f1m3 = new TF1("pi;cos(th);mass","std::sqrt(5.27*5.27+x*x)/(5.27*1.0006349)",0,0.4);
  f1m3->SetTitle("5.27");
  TGraph *g1m = new TGraph();
  double M_pi = 0.139;
  double M_e = 0.00051;
  double M_k = 0.494;
  double cos_pi = costh(M_pi,6.358);
  double cos_e = costh(M_e,6.358);
  double cos_k = costh(M_k,6.358);
  double cos_pi_2 = costh(M_pi,4.357);
  double cos_e_2 = costh(M_e,4.357);
  double cos_pi_3 = costh(M_pi,5.27);
  double cos_e_3 = costh(M_e,5.27);
  std::cout<<"for pi 6.358 "<<cos_pi<<std::endl;
  std::cout<<"for e 6.358 "<<cos_e<<std::endl;
  std::cout<<"for k 6.358 "<<cos_k<<std::endl;
  std::cout<<"for pi 4.357 "<<cos_pi_2<<std::endl;
  std::cout<<"for e 4.357 "<<cos_e_2<<std::endl;
  std::cout<<"for pi 5.27 "<<cos_pi_3<<std::endl;
  std::cout<<"for e 5.27 "<<cos_e_3<<std::endl;
  g1m->SetPoint(0,M_pi,cos_pi);
  g1m->SetPoint(1,M_e,cos_e);
  g1m->SetPoint(2,M_k,cos_k);
  g1m->SetPoint(3,M_pi,cos_pi_2);
  g1m->SetPoint(4,M_e,cos_e_2);
  g1m->SetPoint(5,M_pi,cos_pi_3);
  g1m->SetPoint(6,M_e,cos_e_3);

  TCanvas *c_momentum_mass = new TCanvas();
  g1m->SetMarkerStyle(8);
  g1m->GetXaxis()->SetTitle("mass");
  g1m->GetYaxis()->SetTitle("cos(th)");
  g1m->GetXaxis()->SetRangeUser(0,0.3);
  g1m->Draw("ap");
  g1m->SetTitle("cos(th) for different momentum");
  f1m->Draw("same");
  f1m2->SetLineColor(4);
  f1m2->Draw("same");
  f1m3->SetLineColor(6);
  f1m3->Draw("same");
  c_momentum_mass->BuildLegend();
  c_momentum_mass->SaveAs("results/cer_npe_mass.pdf");

  TF1 *f2m = new TF1("","1-(6.358*6.358+x*x)/(6.358*6.358*1.0006349*1.0006349)",0,0.4);
  f2m->SetTitle("6.358");
  TF1 *f2m2 = new TF1("","1-(4.357*4.357+x*x)/(4.357*4.357*1.0006349*1.0006349)",0,0.4);
  f2m2->SetTitle("4.357");
  TF1 *f2m3 = new TF1("pi;cos(th);mass","1-(5.27*5.27+x*x)/(5.27*5.27*1.0006349*1.0006349)",0,0.4);
  f2m3->SetTitle("5.27");
  TGraph *g2m = new TGraph();
  double npe_pi = npe(M_pi,6.358);
  double npe_e = npe(M_e,6.358);
  double npe_k = npe(M_k,6.358);
  double npe_pi_2 = npe(M_pi,4.357);
  double npe_e_2 = npe(M_e,4.357);
  double npe_pi_3 = npe(M_pi,5.27);
  double npe_e_3 = npe(M_e,5.27);
  std::cout<<"for pi 6.358  "<<npe_pi<<std::endl;
  std::cout<<"for e 6.358 "<<npe_e<<std::endl;
  std::cout<<"for k 6.358 "<<npe_k<<std::endl;
  std::cout<<"for pi 4.357 "<<npe_pi_2<<std::endl;
  std::cout<<"for e 4.357 "<<npe_e_2<<std::endl;
  std::cout<<"for pi 5.27 "<<npe_pi_3<<std::endl;
  std::cout<<"for e 5.27 "<<npe_e_3<<std::endl;
  g2m->SetPoint(0,M_pi,npe_pi);
  g2m->SetPoint(1,M_e,npe_e);
  g2m->SetPoint(2,M_k,npe_k);
  g2m->SetPoint(3,M_pi,npe_pi_2);
  g2m->SetPoint(4,M_e,npe_e_2);
  g2m->SetPoint(5,M_pi,npe_pi_3);
  g2m->SetPoint(6,M_e,npe_e_3);

  TCanvas *c_momentum_mass_npe = new TCanvas();
  g2m->SetMarkerStyle(8);
  g2m->GetXaxis()->SetTitle("mass");
  g2m->GetYaxis()->SetTitle("Npe/N0");
  g2m->GetXaxis()->SetRangeUser(0,0.3);
  g2m->Draw("ap");

  g2m->SetTitle("Npe/N0 for different momentum");
  f2m->Draw("same");
  f2m2->SetLineColor(4);
  f2m2->Draw("same");
  f2m3->SetLineColor(6);
  f2m3->Draw("same");
  c_momentum_mass_npe->BuildLegend();
  c_momentum_mass_npe->SaveAs("results/cer_npe_mass.pdf");
 
  
  TGraph *g_pi_p = new TGraph();
  double npe_0 = npe(M_pi,6.358);
  double npe_1 = npe(M_pi,4.357);
  double npe_2 = npe(M_pi,5.27);
  std::cout<<"6.538 "<<npe_0<<std::endl;
  std::cout<<"4.357 "<<npe_1<<std::endl;
  std::cout<<"5.27 "<<npe_2<<std::endl;
  g_pi_p->SetPoint(0,6.358,npe_0);
  g_pi_p->SetPoint(1,4.357,npe_1);
  g_pi_p->SetPoint(2,5.27,npe_2);
  TF1 *f2 = new TF1("sin^2th","1-(x*x+0.139*0.139)/(x*x*1.0006349*1.0006349)",3.9,10);
  TF1 *f_e = new TF1("sin^2th","1-(x*x+0.000511*0.000511)/(x*x*1.0006349*1.0006349)",3.9,10);
  g_pi_p->GetXaxis()->SetTitle("momentum");
  g_pi_p->GetYaxis()->SetTitle("Npe/N0");
  TCanvas *c_pion_thisp = new TCanvas();
  g_pi_p->SetMarkerStyle(8);
  g_pi_p->GetYaxis()->SetRangeUser(0,0.002);
  g_pi_p->GetXaxis()->SetRangeUser(0,10);
  g_pi_p->Draw("ap");
  f2->Draw("same");
  f_e->SetLineColor(kBlack);
  f_e->Draw("same");
  g_pi_p->SetTitle("pi Npe/N0");
  c_pion_thisp->SaveAs("results/cer_npe_pi_p.pdf");
}
