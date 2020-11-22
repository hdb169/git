void multigraphleg()
{
   TCanvas *c = new TCanvas("c","c",600, 400);

   TMultiGraph * mg = new TMultiGraph("mg","mg");

   const Int_t size = 10;
	        
   double x[size];
   double y1[size];
   double y2[size];
   double y3[size];

   for ( int i = 0; i <  size ; ++i ) {
      x[i] = i;
      y1[i] = size - i;
      y2[i] = size - 0.5 * i;
      y3[i] = size - 0.6 * i;
   }

   TGraph * gr1 = new TGraph( size, x, y1 );
   gr1->SetName("gr1");
   gr1->SetTitle("graph 1");
   gr1->SetMarkerStyle(21);
   gr1->SetDrawOption("AP");
   gr1->SetLineColor(2);
   gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);

   TGraph * gr2 = new TGraph( size, x, y2 );
   gr2->SetName("gr2");
   gr2->SetTitle("graph 2");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(2);
   gr2->SetDrawOption("P");
   gr2->SetLineColor(3);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);

   TGraph * gr3 = new TGraph( size, x, y3 );
   gr3->SetName("gr3");
   gr3->SetTitle("graph 3");
   gr3->SetMarkerStyle(23);
   gr3->SetLineColor(4);
   gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);

   mg->Add( gr1 );
   mg->Add( gr2 );

   gr3->Draw("ALP");
   mg->Draw("LP");
   c->BuildLegend();

   c->Print("multigraphleg.gif");
}
