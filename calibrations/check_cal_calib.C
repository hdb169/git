//plot two same variables from 6545 calibrated with 7671 vs from same run 7671.
#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>
using namespace std;

#define NRUNS 1
void check_calib1(){
#include "header.h"
  Int_t runs[NRUNS]={6545}; //7593, 7594, 7595, 7596, 7597, 7599, 7600, 7601, 7602, 7603, 7604, 7605, 7606, 7607, 7608, 7609, 7610, 7611, 7612, 7613, 7614, 7615, 7616, 7617, 7618, 7619, 7620, 7621, 7622, 7623, 7625, 7626, 7627, 7628, 7629, 7630, 7631, 7632, 7633, 7634, 7635, 7636, 7637, 7638, 7639, 7640, 7641, 7642, 7643, 7644, 7645, 7646, 7647, 7648, 7649, 7650, 7651, 7652, 7654, 7655, 7657, 7658, 7659, 7660, 7661, 7662, 7663, 7666, 7667, 7668, 7669 ,7670 ,7671, 7672, 7673, 7674, 7675, 7676, 7677, 7678, 7679, 7680, 7681, 7682, 7684, 7685, 7686, 7687, 7688, 7689, 7690, 7692, 7694, 7695, 7697, 7698, 7699, 7702, 7703, 7706, 7707, 7708, 7709, 7710, 7711, 7712, 7713, 7714, 7715, 7716, 7717, 7718, 7719, 7720, 7721, 7722, 7723, 7724, 7725, 7727, 7728, 7729, 7730, 7733, 7735, 7736, 7737, 7738, 7739, 7740, 7741, 7742, 7743, 7747, 7748, 7749, 7750, 7751, 7752, 7753, 7754, 7755, 7757, 7758, 7759, 7760, 7762, 7763, 7765, 7766, 7768, 7769, 7770, 7771, 7772, 7773, 7774, 7775, 7776, 7777, 7778, 7779, 7781, 7782, 7783, 7784, 7785, 7786, 7787, 7790, 7791, 7792, 7793, 7794, 7796, 7797, 7798, 7799, 7800, 7801, 7802, 7803, 7804, 7805, 7806, 7807, 7808, 7809, 7811, 7812, 7813, 7814, 7815, 7816, 7817, 7820, 7822, 7823, 7824, 7826, 7827, 7828, 7829, 7830           };

  TFile *f[NRUNS];
  TTree *tt[NRUNS];
  for(Int_t i=0; i<NRUNS; i++){

    // f[i]=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/check_ngconly_7671_tofall/7671_checked_to_%d_-1.root", runs[i]),"read");
    f[i]=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/cal_calib_oct22/coin_replay_production_%d_-1.root", runs[i]),"read");
    tt[i]=(TTree *)f[i]->Get("T");
    // TChain *tt = new TChain("T");
 
    // tt->Add("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/spring_final/7671_checked_to_7593_-1.root");

    //TFile *ff = new TFile("root/7672_with_7671.root", "RECREATE");      

    Double_t pionMass = 0.1395701835;   

    Double_t pcaletot,pcaletotnorm,pcaletracknorm,pbeta,hbeta,pdelta,hdelta,pcaletottracknorm,hcaletot,pcalepr,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,E_pi,z_had,z_had_all,pkinomega,PgtrP,HgtrP,hhodstarttime,phodstarttime,hdipole, pdipole;
 
    cout<<f[i]<<endl;
    TH1D *h_ctime = new TH1D("h_ctime", "ctime (ns)", 400,25,75);
    TH1D *h_z = new TH1D("h_z","z_had_all", binz, loz, hiz);                                      

    TH1D *h_Q2d = new TH1D("h_Q2d","Q2 (GeV2)",binq, loq, hiq);  
    TH1D *h_xd = new TH1D("h_xd","X_bj", binx, lox, hix);   
    TH1D *h_ctimed = new TH1D("h_ctimed", "ctimed (ns)", 400,25,75);
    TH1D *h_zd = new TH1D("h_zd","z_had", binz, loz, hiz);                                      
    TH1D *h_caletot = new TH1D("h_caletot","h_caletot", 100, 0.0001, 7);                                      
    TH1D *h_caletotnorm = new TH1D("h_caletotnorm","h_caletotnorm", 100, 0.0001, 2);                                      
    TH1D *h_EoverP = new TH1D("h_EoverP","h_EoverP", 100, 0.0001, 2);                                      
    TH2D *h_shwr_vs_preshwr = new TH2D("h_shwr_vs_preshwr","h_shwr_vs_preshwr",100, 0.001, 1.5, 100, 0.001,1.5);

    TH2D *h_dp_vs_EoverP = new TH2D("h_dp_vs_EoverP","h_dp_vs_EoverP", 100, 0.001, 2, 100, -12, 22);                                      
    TH2D *h_dp_vs_beta = new TH2D("h_dp_vs_beta","h_dp_vs_beta", 100,0.001, 2, 100, -12, 22);                                       

    //cout<<runs[i]<<endl;
  
    Int_t cntsepi=0;
    Int_t evts=0;
    tt[i]->SetBranchAddress("P.gtr.p", &PgtrP); 
    tt[i]->SetBranchAddress("H.gtr.p", &HgtrP); 
    tt[i]->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
    tt[i]->SetBranchAddress("H.gtr.beta", &hbeta); 
    tt[i]->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
    tt[i]->SetBranchAddress("P.gtr.dp", &pdelta);                                                                                
    tt[i]->SetBranchAddress("P.cal.eprtracknorm", &pcalepr);                                                                    
    tt[i]->SetBranchAddress("P.cal.etottracknorm", &pcaletottracknorm);                                                                  
    tt[i]->SetBranchAddress("P.hgcer.npeSum", &phg);
    tt[i]->SetBranchAddress("P.aero.npeSum", &paeronpe);                                          
    tt[i]->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);  
                                tt[i]->SetBranchAddress("P.cal.etracknorm", &pcaletracknorm); 
                                //tt[i]->SetBranchAddress("P.cal.eprtracknorm", &pcaletracknorm);  
 
    tt[i]->SetBranchAddress("H.cal.etottracknorm", &hcaletot);                                          
    tt[i]->SetBranchAddress("H.cer.npeSum", &hcernpe); 
    // tt[i]->SetBranchAddress("H.kin.primary.W", &W);
    // tt[i]->SetBranchAddress("H.kin.primary.Q2", &Q2);
    // tt[i]->SetBranchAddress("H.kin.primary.x_bj", &xbj); 
    tt[i]->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
    //tt[i]->SetBranchAddress("H.kin.primary.omega", &pkinomega);
    tt[i]->SetBranchAddress("H.hod.goodstarttime", &hhodstarttime);
    tt[i]->SetBranchAddress("P.hod.goodstarttime",&phodstarttime);
    tt[i]->SetBranchAddress("P.dc.InsideDipoleExit",&pdipole);
    tt[i]->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);
    tt[i]->SetBranchAddress("P.cal.etot",&pcaletot);
    tt[i]->SetBranchAddress("P.cal.etotnorm",&pcaletotnorm);
    

    Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut,pid_cut;
 
    Long64_t nentriesD = tt[i]->GetEntries();

    // cout<<"Total Entries = "<<nentriesD<<endl;

    for (int kk=0; kk<nentriesD;  kk++)//============================================>evts
      {

	tt[i]->GetEntry(kk);

	//	if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;

	data_cut = paeronpe>2.0 &&  pdelta >-10 && pdelta < 20  &&  pbeta > 0.5 && pbeta < 1.5 && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1;
  
      	if(data_cut)
	  {    cntsepi++;

	    h_ctime->Fill(ctime);
	    E_pi = sqrt(pow(pionMass,2) + pow(PgtrP,2));
	    z_had_all = E_pi/pkinomega;
	    h_z->Fill(z_had_all);
	    h_caletot->Fill(pcaletot);
	    h_caletotnorm->Fill(pcaletotnorm);
	    h_EoverP->Fill(pcaletottracknorm);
	    h_shwr_vs_preshwr->Fill(pcalepr,pcaletracknorm-pcalepr);
	    h_dp_vs_EoverP->Fill(pcaletottracknorm,pdelta);
	    h_dp_vs_beta->Fill(pbeta,pdelta);

	  }
      }

    
    //cout << "final good events = "<<  cntsepi << endl;

    gROOT->SetBatch(kFALSE);

    /*#include "plot.h"*/
     TCanvas *c1 = new TCanvas("c1", "c1",1500,1200); 

    
    c1->Divide(3,2);
    c1->cd(1);
    h_caletot->Draw();
    h_caletot->SetLineWidth(2);
    h_caletot->SetLineColor(kBlue);
    h_caletot->SetTitle(Form("P.cal.etot RUN NUM %d", runs[i]));
    h_caletot->GetXaxis()->SetTitle("P.cal.etot");//============================================>try
    h_caletot->GetXaxis()->CenterTitle();
    h_caletot->GetXaxis()->SetTitleOffset(1.2);

				    
    c1->cd(2);
    h_caletotnorm->Draw();
    h_caletotnorm->SetLineWidth(2);
    h_caletotnorm->SetLineColor(kBlue);
    h_caletotnorm->SetTitle(Form("P.cal.etotnorm RUN NUM %d", runs[i]));
    h_caletotnorm->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_caletotnorm->GetXaxis()->CenterTitle();
    h_caletotnorm->GetXaxis()->SetTitleOffset(1.2);


    c1->cd(3);gPad->SetGridx();
    h_EoverP->Draw();
    h_EoverP->SetLineWidth(2);
    h_EoverP->SetLineColor(kBlue);
    h_EoverP->SetTitle(Form("P.cal.etottracknorm RUN NUM %d", runs[i]));
    h_EoverP->GetXaxis()->SetTitle("P.cal.etottracknorm");
    h_EoverP->GetXaxis()->CenterTitle();
    h_EoverP->GetXaxis()->SetTitleOffset(1.2);

		
    c1->cd(4);gPad->SetLogz();
    h_shwr_vs_preshwr->Draw("colz");
    h_shwr_vs_preshwr->SetLineWidth(2);
    h_shwr_vs_preshwr->SetLineColor(kBlue);
    h_shwr_vs_preshwr->SetTitle(Form("shower vs preshower RUN NUM %d", runs[i]));
    h_shwr_vs_preshwr->GetYaxis()->SetTitle("shms_shower");
    h_shwr_vs_preshwr->GetYaxis()->CenterTitle();
    h_shwr_vs_preshwr->GetXaxis()->SetTitle("shms_preshower");
    h_shwr_vs_preshwr->GetXaxis()->CenterTitle();
    h_shwr_vs_preshwr->GetXaxis()->SetTitleOffset(1.2);


    c1->cd(5);gPad->SetLogz();
    h_dp_vs_EoverP->Draw("colz");
    h_dp_vs_EoverP->SetLineWidth(2);
    h_dp_vs_EoverP->SetLineColor(kBlue);
    h_dp_vs_EoverP->SetTitle(Form("dp vs E/P RUN NUM %d", runs[i]));
    h_dp_vs_EoverP->GetYaxis()->SetTitle("dp");
    h_dp_vs_EoverP->GetYaxis()->CenterTitle();
    h_dp_vs_EoverP->GetXaxis()->SetTitle("E/P");
    h_dp_vs_EoverP->GetXaxis()->CenterTitle();
    h_dp_vs_EoverP->GetXaxis()->SetTitleOffset(1.2);


    c1->cd(6);gPad->SetLogz();
    h_dp_vs_beta->Draw("colz");
    h_dp_vs_beta->SetLineWidth(2);
    h_dp_vs_beta->SetLineColor(kBlue);
    h_dp_vs_beta->SetTitle(Form("dp vs pbeta RUN NUM %d", runs[i]));
    h_dp_vs_beta->GetYaxis()->SetTitle("dp");
    h_dp_vs_beta->GetYaxis()->CenterTitle();
    h_dp_vs_beta->GetXaxis()->SetTitle("P.gtr.beta");
    h_dp_vs_beta->GetXaxis()->CenterTitle();
    h_dp_vs_beta->GetXaxis()->SetTitleOffset(1.2);


    // ff->cd();
    //ff->Write();
    

 
    c1->SaveAs(Form("pdf/cal_check_%d_self.pdf)",runs[i]));
    
    c1->~TCanvas();	

  }

}





