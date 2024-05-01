#define m 4
#define n 2
{
  TFile *f = new TFile ("ROOTfiles/shms_replay_production_1583_100000.root");

  TCanvas* c1 = new TCanvas("c1","Pedestal", 1000,1000);
  TCanvas* c2 = new TCanvas("c2","PedestalY", 100, 0, 1000,1000);
  c1->Divide(4,4);
  c2->Divide(4,4);
 
  double mean[16][n];
  double rms[4][16][n];
  TH2D *h[4][n];
  TH1D *hp[16][n];
 const char * plane[m] = {"1x","1y","2x","2y"};
 const char *side[n] = {"pmt_pos","pmt_neg"};
 Int_t counter = 0;
 ofstream output("RMS_MEAN11.txt");
  for(Int_t p=0;p<4;p++){
    for(Int_t q=0;q<n;q++){
      h[p][q] = (TH2D*)f->Get(Form("phodo_%s_pped_vs_%s",plane[p],side[q]));
      h[p][q]->Draw();
    for(Int_t pad=0;pad<16;pad++){
      
      c1->cd(counter+1);
     
      hp[pad][q] = h[p][q]->ProjectionY(Form("Projection %d %d", p,pad), pad, pad+1);
      c2->cd(counter+1);
      hp[pad][q]->Draw();
      
      //output<<"p="<<p+1<<"   q="<<q+1<<"   mean="<<hp[pad][q]->GetMean()<<"    rms="<<hp[pad][q]->GetRMS()<<endl;
      output<<"p="<<plane[p]<<"   q="<<side[q]<<"   mean="<<hp[pad][q]->GetMean()<<"    rms="<<hp[pad][q]->GetRMS()<<endl;
     
       counter++;
       cout<<counter<<endl;
    }
    }
  }
  output.close();
}
