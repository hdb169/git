#just draw a line between any two (x1,y1) and (x2,y2) pairs.
{
  TCanvas *c1 = new TCanvas("c1");
  TH1F *h= new TH1F("h","test",100,0,4);
  h->FillRandom("gaus",10000);
  h->Draw();
  Float_t ymax = h->GetMaximum();
  //TLine *line = new TLine(x1,y1,x2,y2);
    TLine *line = new TLine(0,200,1,0);

  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->Draw();
}
