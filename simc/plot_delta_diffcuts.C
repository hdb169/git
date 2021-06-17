void make_it_work(){
gStyle->SetOptStat(1000011);

  gStyle->SetOptStat(1111111);

  using namespace std;

  TH1F *s1_Em;

  TCut h_pid_cut_simc_2;
 
  TFile *f1 = new TFile("/u/group/c-csv/hdbhatt/my_analysis/simc2021April/simc_gfortran/worksim/simc_60701.root");
  TTree *u1 = (TTree*)f1->Get("h10");

  //h_pid_cut_simc_2 = "Em < 3.2 && Em > 0.0";//Em < 0.032+0.0005*i(i=1 to 10)
  h_pid_cut_simc_2 = "Em < 3.2 && Em > 2.005";//Em < 0.032+0.0005*i(i=1 to 10)

  s1_Em = new TH1F("s1_Em","", 100,0,10);
  // u1->Draw("Em>>s1_Em",h_pid_cut_simc_2*"Weight*3453510000/400000","goff");
  u1->Draw("Em>>s1_Em",h_pid_cut_simc_2*"Weight*0.154889E+12/300000","goff");



  Double_t good_counts2_1 = s1_Em->GetEntries();
  Double_t integral2_1 = s1_Em->Integral();

  cout<<"0-0.032"<<"  "<<good_counts2_1<<"   "<<integral2_1<<endl;
}
*/
//////////////////BELOW//////////
 

#define NRUNS  2



void make_it_work(){
  Int_t runs[NRUNS]= {60701,60911};
  Double_t normfac[NRUNS]={0.154889E+12, 0.163448E+12};
  Int_t gevents[NRUNS] = {300000,300000};//if it is different for diff runs

  double Emiss,Weight,normwt, spdelta;
  TH1F *hist[20];
  for(int i=1;i<21;i++){
    hist[i]= new TH1F(Form("hist[%d]",i),"",100,0,10);
  }


  for(int r=0;r<NRUNS;r++){
    TString filename  = Form("/u/group/c-csv/hdbhatt/my_analysis/simc2021April/simc_gfortran/worksim/simc_%d.root",runs[r]);
    TFile *f = new TFile(filename, "READ");
    //TFile * f1 = new TFile(Form("detest/testDB_%d.root",runs[r]),"RECREATE");//not working
    gStyle->SetOptStat(1000111);
    cout<< "Opening Run Num = "<<filename<<"\t"<< runs[r] <<endl;
   
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }
    TTree * tt = (TTree *)f->Get("h10");//h666
    Long64_t nentriesD = tt->GetEntries();
 
    for (int kk=0; kk<nentriesD;  kk++){
      tt->GetEntry(kk);
      normwt = Weight*normfac[r]/gevents[r];

      Emiss = tt->GetLeaf("Em")->GetValue();
      Weight = tt->GetLeaf("W")->GetValue();
      spdelta = tt->GetLeaf("ssdelta")->GetValue();

      for(int i=1;i<21;i++){
if(Emiss > (1.005+0.05*i)  &&  (Emiss<=2.2+0.05*i)){//change these, say for i = 20; //but you are keeping >0
 hist[i]->Fill(spdelta,normwt);//I filled delta

}
      }


    }//entries
    TCanvas *c1 = new TCanvas("c1","c1", 1200, 800);
    c1->Divide(4,5);
    for(int i = 1;i<21;i++){
      c1->cd(i);//gPad->SetGrid();
      hist[i]->Draw("hist");
      hist[i]->SetTitle(Form("Delta: Emiss => (%.5f - %.5f)",1.005+0.05*i, 2.2+0.05*i ));//make same as cuts above
      hist[i]->SetLineWidth(2);
      //hist[i]->Write();
      cout<< runs[r]<<"   "<< " Ent = "<<hist[i]->GetEntries()<<"   "<<"Int = "<<hist[i]->Integral()<<endl;
    }

    c1->SaveAs(Form("dbtest/hists_%d.pdf",runs[r]));

  }//runs
 
}
