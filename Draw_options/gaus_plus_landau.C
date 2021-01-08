//The following are two function addition 
gaus_plus_landau(){
TF1 *fg = new TF1("fg","gaus",0.1,0.6);//needed to add gaussian to Landau
  fg->SetParameter(0,1200);
  fg->SetParameter(1,0.45);
  // fg->SetParameter(2,0.07);
 
  TF1 *fl = new TF1("fl","landau",0.72,4.5);//needed to add gaussian to Landau
  fl->SetParameter(0,3000);
  fl->SetParameter(1,1.02);
 
  double par[6];   // both of function has total 6 pars
  TF1 *ft = new TF1("ft", "gaus(0)+landau(3)",0.1,5.0);
 
  TCanvas* c3y = new TCanvas("c3y","c3y",600,600);
  c3y->cd();
  py->Draw();
  py->Fit("fl","0"," ",0.72,4.5);//"0" --> means fit function will not appear
  py->Fit("fg","0","", 0.1,0.6);
  fg->GetParameters(&par[0]);//needed to add gaussian to Landau
  fl->GetParameters(&par[3]);//needed to add gaussian to Landau
  ft->SetParameters(par);
  py->Fit("ft","R+","ep");
  }
