
void effvscuts(){
  TCanvas * c1 = new TCanvas("c1","Efficiency vs hgcer npeSum cut value",200,10,700,500);
 

  c1->SetGrid();
  c1->SetGridy();
 
  c1->Divide(1,1);
   // create the coordinate arrays for 3561 pi-; P=3.37 HGCER CUT
 
  Float_t x1[]  = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};//,1.1,1.2,1.3,1.4,1.5};
  Float_t y1[]  = {41.88,41.74,40.99,40.97,40.49,40.14,39.95,39.86,39.78,39.89,39.89,39.88,39.95 };
		
  c1->cd(1);
  TGraph * gr1 = new TGraph(15,x1,y1);
  gr1->SetTitle("Efficiency vs Shwrcut [ < ]");
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(21);
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  gr1->GetYaxis()->SetTitleOffset(1.5);
  gr1->GetXaxis()->SetTitleOffset(1.5);
  gr1->GetXaxis()->SetTitle("Shwr cut less than");
  gr1->GetYaxis()->SetTitle("Efficiency % ");
  gr1->GetYaxis()->SetRangeUser(0,100);
  gr1->Draw("AP*");
  c1->Update();
}
