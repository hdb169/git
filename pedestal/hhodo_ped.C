#define m 4
#define n 2
{
  TFile *f = new TFile ("ROOTfiles/shms_replay_production_1583_100000.root");

  TCanvas* c1 = new TCanvas("c1","Pedestal", 1000,1000);
  TCanvas* c2 = new TCanvas("c2","PedestalY", 100, 0, 1000,1000);
  c1->Divide(2,4);
  c2->Divide(2,4);
 
  double mean[m][n];
  double rms[m][n];
  TH2D *h[m][n];
  TH1D *hp[m][n];
 const char * plane[m] = {"1x","1y","2x","2y"};
 const char *side[n] = {"pmt_pos","pmt_neg"};
 Int_t counter = 0;
 ofstream output("RMS_MEAN.txt");
  for(Int_t p=0;p<m;p++){
    for(Int_t q=0;q<n;q++){
      
      c1->cd(counter+1);
      h[p][q] = (TH2D*)f->Get(Form("phodo_%s_pped_vs_%s",plane[p],side[q]));
      h[p][q]->Draw();
     
      hp[p][q] = h[p][q]->ProjectionY(Form("Projection %d", counter), 0, 500);
      c2->cd(counter+1);
      hp[p][q]->Draw();
      
      //output<<"p="<<p+1<<"   q="<<q+1<<"   mean="<<hp[p][q]->GetMean()<<"    rms="<<hp[p][q]->GetRMS()<<endl;
      output<<"p="<<plane[p]<<"   q="<<side[q]<<"   mean="<<hp[p][q]->GetMean()<<"    rms="<<hp[p][q]->GetRMS()<<endl;
     
       counter++;
       cout<<counter<<endl;
    }
  }
  output.close();
}
