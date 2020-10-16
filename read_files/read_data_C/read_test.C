//This macro reads 3 columns of test.dat and fill then in 3 hists h1, h2, h3 such that first column in h1 and so on. Also 
// creates ntuplus of x, y and z.


//http://www1.phys.vt.edu/~dayabay/Presentations/090916.dm.Root1.pdf

#include "Riostream.h"
void read_test() {
  ifstream in;
  //in.open(Form("test.dat"));
  in.open("test.dat");

  Float_t x,y,z;
  Int_t nlines = 0;
  TFile *f = new TFile("read_datfile.root","RECREATE");
  TH1F *h1 = new TH1F("h1","x distribution",1000,-5,5);
  TH1F *h2 = new TH1F("h2","y distribution",1000,-5,5);
  TH1F *h3 = new TH1F("h3","z distribution",1000,-5,5);

  TNtuple *ntuple = new TNtuple("ntuple","data fromascii file","x:y:z");
  while (1) {
    in >> x >> y >> z;
    if (!in.good()) break;
    //if (nlines < 26) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);    
    if (nlines < 26) printf("x=%2f, y=%2f, z=%2f\n",x,y,z);


    h1->Fill(x);
    h2->Fill(y);
    h3->Fill(z);

    
    ntuple->Fill(x,y,z);
    
    nlines++;
  }
  printf(" found %d points\n",nlines+1);
  in.close();
  f->Write();
}
