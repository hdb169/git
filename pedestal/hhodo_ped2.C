#define m 2
#define n 2
{
  TFile *f = new TFile ("ROOTfiles/shms_replay_production_1583_100000.root");

  TCanvas* c1 = new TCanvas("c1","Pedestal", 1000,1000);
  TCanvas* c2 = new TCanvas("c2","PedestalY", 100, 0, 1000,1000);
  c1->Divide(8,8);
  c2->Divide(8,8);
  TCanvas* c3 = new TCanvas("c3","Pedestal", 1000,1000);
  TCanvas* c4 = new TCanvas("c4","PedestalY", 100, 0, 1000,1000);
  c3->Divide(8,5);
  c4->Divide(8,5);
 
  double mean[16][n];
  double rms[16][n];
  TH2D *hx[4][n];
  TH1D *hpx[16][n];
   TH2D *hy[4][n];
  TH1D *hpy[16][n];
  // const char * plane[m] = {"1x","1y","2x","2y"};
   const char * planex[m] = {"1x","2x"};
    const char * planey[m] = {"1y","2y"};
 const char *side[n] = {"pmt_pos","pmt_neg"};
 Int_t counter = 0;
 ofstream outputx("RMS_MEANx.txt");
  ofstream outputy("RMS_MEANy.txt");
 
  for(Int_t p=0;p<2;p++){
    for(Int_t q=0;q<n;q++){
      
      hx[p][q] = (TH2D*)f->Get(Form("phodo_%s_pped_vs_%s",planex[p],side[q]));
    c1->cd(counter+1);  hx[p][q]->Draw();
       hy[p][q] = (TH2D*)f->Get(Form("phodo_%s_pped_vs_%s",planey[p],side[q]));
    c3->cd(counter+1);    hy[p][q]->Draw();
      
    for(Int_t pad=0;pad<16;pad++){
      
      
     
      hpx[pad][q] = hx[p][q]->ProjectionY(Form("Projection %d %d", p,pad), pad, pad+1);
      c2->cd(counter+1);
      hpx[pad][q]->Draw();
      
      //output<<"p="<<p+1<<"   q="<<q+1<<"   mean="<<hp[pad][q]->GetMean()<<"    rms="<<hp[pad][q]->GetRMS()<<endl;
      outputx<<"p="<<planex[p]<<"   q="<<side[q]<<"   mean="<<hpx[pad][q]->GetMean()<<"    rms="<<hpx[pad][q]->GetRMS()<<endl;
     
       counter++;
       cout<<counter<<endl;
    }

     for(Int_t pad=0;pad<10;pad++){
      
     
     
      hpy[pad][q] = hy[p][q]->ProjectionY(Form("Projection %d %d", p,pad), pad, pad+1);
      c4->cd(counter+1);
      hpy[pad][q]->Draw();
      
      //output<<"p="<<p+1<<"   q="<<q+1<<"   mean="<<hp[pad][q]->GetMean()<<"    rms="<<hp[pad][q]->GetRMS()<<endl;
      outputy<<"p="<<planey[p]<<"   q="<<side[q]<<"   mean="<<hpy[pad][q]->GetMean()<<"    rms="<<hpy[pad][q]->GetRMS()<<endl;
     
       counter++;
       cout<<counter<<endl;
    }
    }
  }
  outputx.close();
   outputy.close()
  
}
