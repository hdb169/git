void lowrate(Int_t runNo, Int_t eventNo) {//6111,7770
  //TFile *f = new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/lowrate_jan9/coin_replay_production_%d_%d.root", runNo, eventNo));//may 8 2019
      TFile *f = new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/very_low_hirate/coin_replay_production_%d_%d.root", runNo, eventNo));//may 8 2019


  gStyle->SetOptStat(11111);
 

  TTree *t = (TTree*)f->Get("T");
  cout<<"======================================="<<endl;
  cout<<"Found The Rootfile"<<endl;
  cout<<"Please wait I will be Right Back"<<endl;
  cout<<"======================================="<<endl;
  TH1F * hraw_time[12];
  TH1F * praw_time[12];

  string h_plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  string p_plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};


  for (int ip = 0; ip<12; ip++){

    
    praw_time[ip] = new TH1F(Form("p_dc_%s_nhit", p_plane[ip].c_str()),"",25, 0,25);

    //for pion selection:
    //  t->Draw(Form("P.dc.%s.nhit>>p_dc_%s_nhit", p_plane[ip].c_str(), p_plane[ip].c_str()),"(P.dc.Ch1.nhit>=15 || P.dc.Ch2.nhit>=15)&&P.hod.goodscinhit==1&&P.hod.betanotrack>0.7&&P.hod.betanotrack<1.4&&P.cal.etotnorm>0.05&&P.cal.etotnorm<0.5");//good
    // for singles: 
    t->Draw(Form("P.dc.%s.nhit>>p_dc_%s_nhit", p_plane[ip].c_str(), p_plane[ip].c_str()),"( (P.dc.Ch1.nhit>=15 || P.dc.Ch2.nhit>=15) && (P.dc.Ch1.nhit<=5 || P.dc.Ch2.nhit<=5))   &&P.hod.goodscinhit==1&&P.hod.betanotrack>0.7&&P.hod.betanotrack<1.4&&P.cal.etotnorm>0.005&&P.cal.etotnorm<0.5");//good
    //t->Draw(Form("P.dc.%s.nhit>>p_dc_%s_nhit", p_plane[ip].c_str(), p_plane[ip].c_str()),"((P.dc.Ch1.nhit<=25 && P.dc.Ch1.nhit>=5)  && (P.dc.Ch2.nhit<=25 && P.dc.Ch2.nhit>=5)) &&P.hod.goodscinhit==1&&P.hod.betanotrack>0.7&&P.hod.betanotrack<1.4&&P.cal.etotnorm>0.8&&P.cal.etotnorm<1.2");


    }
  
  TCanvas *c2 = new TCanvas("c2", "SHMS DC Nhit", 1600,900);
  c2->Divide(4,3);gPad->SetLogy();

  for(int j=0; j<12; j++){

    c2->cd(j+1);gPad->SetLogy();//gPad->SetGrid();
    praw_time[j]->Draw();
    praw_time[j]->GetXaxis()->SetTitle(Form("P.dc.%s.nhit", p_plane[j].c_str()));
    praw_time[j]->GetXaxis()->CenterTitle("");
    praw_time[j]->GetYaxis()->SetTitle("Entries");
    praw_time[j]->GetYaxis()->SetTitleOffset(1.15);
    praw_time[j]->GetYaxis()->CenterTitle("");
    // praw_time[j]->SetLineWidth(2);
    praw_time[j]->SetLineColor(kRed);

    // praw_time[j]->SetTitle(Form("h_rawtdc_time_%s", h_plane[ip].c_str()));

  }
  c2->SaveAs(Form("pdf/P.dc.planes.nhit_Chamber12_hitsgreaterthan25_%d.pdf",runNo));
}


