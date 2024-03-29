#define NRUNS 519
void hcal_pcal_eff_short(){//has hgcer cut
  
  for(Int_t r = 0; r<NRUNS;r++){
    gROOT->SetBatch("kTRUE");
    //gStyle->SetOptStat(0);
    //gStyle->SetOptStat(1000011);
    gStyle->SetPalette(1,0);
    gStyle->SetOptStat(1000011);
    gStyle->SetOptFit(11);
    gStyle->SetTitleOffset(1.,"Y");
    gStyle->SetTitleOffset(.7,"X");
    gStyle->SetLabelSize(0.04,"XY");
    gStyle->SetTitleSize(0.06,"XY");
    gStyle->SetPadLeftMargin(0.12);
    Int_t runs[NRUNS]     ={   6020, 6021, 6022, 6026, 6027, 6028, 6029, 6030, 6031, 6032, 6043, 6044, 6045, 6046, 6049, 6050, 6051, 6052, 6053, 6054, 6055, 6056, 6057, 6058, 6067, 6068, 6070, 6071, 6073, 6080, 6081, 6087, 6088, 6089, 6090, 6091, 6093, 6094, 6095, 6096, 6097, 6098, 6109, 6110, 6111, 6112, 6114, 6115, 6116, 6119, 6120, 6124, 6125, 6127, 6128, 6129, 6130, 6132, 6133, 6135, 6136, 6137, 6138, 6145, 6146, 6154, 6155, 6166, 6168, 6169, 6170, 6171, 6172, 6179, 6180, 6181, 6182, 6183, 6184, 6185, 6186, 6187, 6194, 6195, 6196, 6197, 6198, 6199, 6205, 6208, 6209, 6210, 6211, 6212, 6213, 6214, 6215, 6216, 6217, 6219, 6220, 6242, 6243, 6244, 6245, 6246, 6247, 6248, 6249, 6250, 6251, 6252, 6261, 6262, 6263, 6264, 6265, 6266, 6267, 6270, 6271, 6272, 6273, 6274, 6275, 6276, 6288, 6289, 6290, 6291, 6292, 6293, 6294, 6295, 6296, 6304, 6305, 6306, 6307, 6308, 6309, 6310, 6311, 6312, 6317, 6318, 6322, 6323, 6325, 6326, 6327, 6328, 6329, 6339, 6340, 6341, 6342, 6343, 6344, 6345, 6346, 6347, 6348, 6349, 6350, 6351, 6352, 6353, 6354, 6359, 6360, 6363, 6364, 6365, 6367, 6368, 6370, 6371, 6372, 6373, 6374, 6375, 6376, 6377, 6378, 6379, 6380, 6381, 6382, 6383, 6385, 6386, 6387, 6388, 6389, 6390, 6391, 6393, 6394, 6395, 6396, 6397, 6398, 6399, 6400, 6401, 6402, 6403, 6404, 6405, 6406, 6407, 6408, 6410, 6411, 6412, 6413, 6415, 6416, 6417, 6419, 6421, 6422, 6423, 6425, 6426, 6427, 6428, 6429, 6430, 6431, 6432, 6433, 6434, 6435, 6436, 6439, 6440, 6441, 6442, 6443, 6444, 6445, 6446, 6447, 6448, 6451, 6452, 6453, 6454, 6455, 6456, 6459, 6460, 6461, 6462, 6463, 6464, 6465, 6466, 6467, 6468, 6469, 6470, 6471, 6472, 6473, 6474, 6475, 6476, 6477, 6478, 6479,  6486, 6487, 6488, 6489, 6490, 6491, 6493, 6494, 6495, 6496, 6497, 6498, 6499, 6500, 6501, 6502, 6503, 6504, 6506, 6507, 6509, 6510, 6512, 6513, 6514, 6515, 6516, 6517, 6518, 6519, 6520, 6521, 6522, 6523, 6524, 6525, 6526, 6527, 6528, 6529, 6531, 6532, 6533, 6534, 6535, 6536, 6537, 6538, 6539, 6541, 6542, 6543, 6544, 6545, 6546, 6547, 6548, 6549, 6550, 6551, 6552, 7593, 7594, 7595, 7596, 7597, 7599, 7600, 7601, 7602, 7603, 7604, 7605, 7606, 7607, 7608, 7609, 7610, 7611, 7612, 7613, 7614, 7615, 7616, 7617, 7618, 7619, 7620, 7621, 7622, 7623, 7625, 7626, 7627, 7628, 7629, 7630, 7631, 7632, 7633, 7634, 7635, 7636, 7637, 7638, 7639, 7640, 7641, 7642, 7643, 7644, 7645, 7646, 7647, 7648, 7649, 7650, 7651, 7652, 7654, 7655, 7657, 7658, 7659, 7660, 7661, 7662, 7663, 7666, 7667, 7668, 7669, 7670, 7671, 7672, 7673, 7674, 7675, 7676, 7677, 7678, 7679, 7680, 7681, 7682, 7684, 7685, 7686, 7687, 7688, 7689, 7690, 7692, 7694, 7695, 7697, 7698, 7699, 7702, 7703, 7706, 7707, 7708, 7709, 7710, 7711, 7712, 7713, 7714, 7715, 7716, 7717, 7718, 7719, 7720, 7721, 7722, 7724, 7725, 7727, 7728, 7735, 7736, 7737, 7738, 7739, 7740, 7747, 7748, 7749, 7750, 7751, 7752, 7757, 7758, 7759, 7760, 7762, 7768, 7769, 7770, 7771, 7772, 7773, 7774, 7775, 7776, 7777, 7783, 7784, 7785, 7786, 7787, 7790, 7791, 7792, 7793, 7794, 7796, 7797, 7798, 7799, 7800, 7801, 7802, 7803, 7804, 7805, 7806, 7807, 7808, 7809, 7811, 7812, 7813, 7814, 7815, 7816, 7817, 7819, 7820    };

    TString filename  = Form("/home/hdbhatt/ROOTfiles/coin_replay_production_%d_-1.root", runs[r]);
    // TString filename  = Form("/lustre19/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/pT2_tdc/coin_replay_production_%d_-1.root", runs[r]);

    TFile *f = new TFile(filename, "READ");
    //TFile * f11 = new TFile(Form("root/hcal_eff_%d.root",runs[r]),"RECREATE");
    // cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

#include "bin.h"
#include "double_good.h"

    
    
    Double_t ctmin = 1.5;
    Double_t ctmax = 1.5;
    Double_t rfmin = 0.6;
    Double_t rfmax = 1.3;
    
    Double_t pcaletotmax = 0.8;
    Double_t hcaletotmin = 0.7;

    Double_t aeromin = 8;//5
    Double_t hgcermin = 5;  
    Double_t hcermin = 10;//8
    
    Double_t rfmin_loose = 0.3;
    Double_t rfmax_loose = 1.8;

    Double_t hmsxptarmin  = -0.06;
    Double_t hmsxptarmax  =  0.06;
    Double_t hmsyptarmin  = -0.025;
    Double_t hmsyptarmax  =  0.025;
    Double_t shmsxptarmin = -0.045;
    Double_t shmsxptarmax =  0.045;
    Double_t shmsyptarmin = -0.028;
    Double_t shmsyptarmax =  0.028;

    
   
    Bool_t all_but_nohcer, all_cut, xptaryptar_cut,  xptaryptar_pre, all_but_noaero, all_but_nohgcer,all_but_noxyptar, all_but_noW2Mx2,acc_cutdef   ;

#include "offsetrf.h"
    TTree * tt = (TTree *)f->Get("T");
    TTree * ss = (TTree *)f->Get("TSP");
    //#include "define_histogram.h"
#include "define_histogram_z07.h"
#include "branch.h"
    Long64_t nentriesD = tt->GetEntries();
#include "scaler_branch.h"
    Long64_t scal_entries = ss->GetEntries();
    //cout<< runs[r] <<" : "<<  "Entries = "<<nentriesD<<endl;
#include "scaler_analysis.h"
    Int_t nscaler_reads_acc=0;
    for (int kk=0; kk<nentriesD;  kk++){//---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(kk);

      if (event_flag[nscaler_reads_acc]==1) {
	rf_pion_pre = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut_pre = rf_pion_pre > rfmin && rf_pion_pre < rfmax;
	mod4_notpioncut_pre =!mod4_pioncut_pre;
	Epi_cut_pre  = sqrt(pow(pionmass,2) + pow(PgtrP,2));//variable same
	zhad_cut_pre = Epi_cut_pre/dnu;
	Mx2_cut_pre  = (protonmass + dnu - zhad_cut_pre*dnu) *  (protonmass + dnu - zhad_cut_pre*dnu) - abs(dpmiss)*abs(dpmiss);
	xptaryptar_pre = hmsxptar > hmsxptarmin && hmsxptar < hmsxptarmax &&   hmsyptar > hmsyptarmin && hmsyptar < hmsyptarmax &&  shmsxptar > shmsxptarmin && shmsxptar < shmsxptarmax  &&  shmsyptar > shmsyptarmin && shmsyptar < shmsyptarmax; 

	pid_cut_pre  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut_pre && paero > aeromin   && pcaletottrack < pcaletotmax &&  hcaletottrack  > hcaletotmin && xptaryptar_pre;// && dW2 > 4 && Mx2_cut_pre > 1.6;// /* hgcer > hgcermin*/

	if (pid_cut_pre){
	  hpbeta->Fill(pbeta);
	  hctime->Fill(ctime);
	}  
	 
      }
   
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;

    }
  
    Int_t bin_max = hctime->GetMaximumBin();
    Double_t max_value = hctime->GetBinCenter(bin_max);
    Int_t nscaler_reads=0;
    for (int s=0; s<nentriesD;  s++){
      tt->GetEntry(s);
      if (event_flag[nscaler_reads]==1) {

	Epi = sqrt(pow(pionmass,2) + pow(PgtrP,2));
	zhad = Epi/dnu;
	Mx2 = (protonmass + dnu - zhad*dnu) *  (protonmass + dnu - zhad*dnu) - abs(dpmiss)*abs(dpmiss);
	accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
	accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
	acc_cutdef = (accR_cut || accL_cut);
	ctime_cut = ctime > (max_value - ctmin) && ctime < (max_value + ctmax);
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut = rf_pion > rfmin && rf_pion < rfmax;
	mod4_pioncut_loose = rf_pion > rfmin_loose && rf_pion < rfmax_loose;
	mod4_notpioncut =!mod4_pioncut;
	xptaryptar_cut = hmsxptar > hmsxptarmin && hmsxptar < hmsxptarmax &&   hmsyptar > hmsyptarmin && hmsyptar < hmsyptarmax &&  shmsxptar > shmsxptarmin && shmsxptar < shmsxptarmax  &&  shmsyptar > shmsyptarmin && shmsyptar < shmsyptarmax; 

	
	base_cut          =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && xptaryptar_cut;   // && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin *///==========>HGC, Mx2, dW2=====
	base_cut_looserf  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut_loose && paero > aeromin && xptaryptar_cut; // && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */

	shms_etottrack_cut = pcaletottrack < pcaletotmax;
	hms_etottrack_cut  = hcaletottrack >  hcaletotmin;

	acc_cut   =  base_cut && acc_cutdef;    
	coin_cut  =  base_cut && ctime_cut;
	all_cut =  coin_cut && shms_etottrack_cut && hms_etottrack_cut; //all coin cuts but no acc subtraction done here.

	all_but_noxyptar =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */

	all_but_nohcer =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 1.6 && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */
	all_but_noaero =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut &&/* paero > aeromin &&*/ ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin && dW2 > 4 && Mx2 > 1.6;/* && hgcer > hgcermin */
	all_but_nohgcer =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 1.6;//NOHGCER
	all_but_noW2Mx2 =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin;
	
	//hdelta> -8 && hdelta < 8 && hcer
	hmsshower = hcaletottrack-hcalepr;
	shmsshower = pcaletottrack-pcalepr;
	
	hcal_should_cut_acc   =  acc_cut && shms_etottrack_cut;
	hcal_did_cut_acc      =  hcal_should_cut_acc           && hms_etottrack_cut;
	pcal_should_cut_acc   =  acc_cut && hms_etottrack_cut;
	pcal_did_cut_acc      =  pcal_should_cut_acc           && shms_etottrack_cut;
	all_acc_cut           =  acc_cut && shms_etottrack_cut && hms_etottrack_cut;
	
	if(all_acc_cut){hctimeacc->Fill(ctime);}
	//fill assuming acc hist
	//also plotting should quantity for hms and shms cal, as it should be the best one

	if(hcal_did_cut_acc){
	  hist_hcal_did_acc->Fill(hcaletottrack);
	}
       	if(hcal_should_cut_acc){

	  hist_hcal_should_acc->Fill(hcaletottrack);
	  hms_sh_vs_psh_should_acc->Fill(hcalepr,hmsshower);
	}
	
	if(pcal_did_cut_acc){// ..........................................cal acc in z
	  // hist_pcal_did_acc->Fill(pcaletottrack); jan19
	  hist_pcal_did_acc->Fill(zhad);

	}
       	if(pcal_should_cut_acc){//.........................................cal acc in z 
	  // hist_pcal_should_acc->Fill(pcaletottrack); jan19
	  hist_pcal_should_acc->Fill(zhad);
	  shms_sh_vs_psh_should_acc->Fill(pcalepr,shmsshower);
	}

	//acc cut done

	//Earlier above we defined for accidental and now we are defining for the coincidence events. The only difference is taking ctime peak events///
	hcal_should_cut_coin   =  coin_cut && shms_etottrack_cut;
	hcal_did_cut_coin      =  hcal_should_cut_coin           && hms_etottrack_cut;
	pcal_should_cut_coin   =  coin_cut && hms_etottrack_cut;
	pcal_did_cut_coin      =  pcal_should_cut_coin           && shms_etottrack_cut;
	all_coin_cut           =  coin_cut && shms_etottrack_cut && hms_etottrack_cut;
	
	//Fill coin hist
	if(hcal_did_cut_coin){hist_hcal_did_coin->Fill(hcaletottrack);}
       	if(hcal_should_cut_coin){
	  hist_hcal_should_coin->Fill(hcaletottrack);
	  hms_sh_vs_psh_should_coin->Fill(hcalepr,hmsshower);

	}
	
	if(pcal_did_cut_coin){//-----------------------------------cal coin  did in z
	  // hist_pcal_did_coin->Fill(pcaletottrack); jan 19
	  hist_pcal_did_coin->Fill(zhad);

	}
       	if(pcal_should_cut_coin){//-------------------------------------cal coin should in z
	  // hist_pcal_should_coin->Fill(pcaletottrack); jan 19
	  hist_pcal_should_coin->Fill(zhad);
	  shms_sh_vs_psh_should_coin->Fill(pcalepr,shmsshower);

	}

       	//+++++++++++++++++++++++++++++++sh vs etot, presh vs etot************************
       	//	if(all_coin_cut) //with hcal, pcal cuts too 

	if(coin_cut) //with hcal, pcal cuts too 
	  {
	    hms_sh_vs_psh->Fill(hcalepr,hmsshower);
	    shms_sh_vs_psh->Fill(pcalepr,shmsshower);
	    ctime_vs_rf->Fill(rf_pion, ctime);
	    etot_vs_rf->Fill(rf_pion,pcaletottrack);
	    hms_etot_vs_rf->Fill(rf_pion,hcaletottrack);
	    epr_vs_rf->Fill(rf_pion, pcalepr);
	    ctime_vs_etot->Fill(pcaletottrack, ctime);
	    ctime_vs_epr->Fill(pcalepr,ctime);
	    hctimect->Fill(ctime);
	    sh_vs_rf->Fill(rf_pion,shmsshower);
	    hmsepr_vs_rf->Fill(rf_pion,hcalepr);
	    hmssh_vs_rf->Fill(rf_pion,hmsshower);
	    
	  }

	if(all_but_nohcer){//to plot npe vs hms p
	  hcernpe_vs_hmsp->Fill(HgtrP,hcernpe);
	}
	if(all_but_noaero){//to plot npe vs shms p
	  aeronpe_vs_shmsp->Fill(PgtrP,paero);
	}
	if(all_but_nohgcer){//to plot npe vs shms p
	  hgcernpe_vs_shmsp->Fill(PgtrP,hgcer);
	}

	if(all_but_noxyptar){//this is all but non xptar, yptar 
	  hms_xptar_noxyptar->Fill(hmsxptar);
	  hms_yptar_noxyptar->Fill(hmsyptar);
	  shms_xptar_noxyptar->Fill(shmsxptar);
	  shms_yptar_noxyptar->Fill(shmsyptar);
	  hms_xptar_vs_yptar_noxyptar->Fill(hmsyptar,hmsxptar);//xptar along yaxis and yptar along x axis
	  shms_xptar_vs_yptar_noxyptar->Fill(shmsyptar,shmsxptar);
	}

  	//all_cut: all pid+coin+RF aero etc
	if(all_cut){//this is for xptar, yptar peter's values (xptar,yptar)=>HMS(+/-0.06,+/-0.022) and SHMS(+/-0.045,+/-0.028)
	  hms_xptar->Fill(hmsxptar);
	  hms_yptar->Fill(hmsyptar);
	  shms_xptar->Fill(shmsxptar);
	  shms_yptar->Fill(shmsyptar);
	  hms_xptar_vs_yptar->Fill(hmsyptar,hmsxptar);//xptar along yaxis and yptar along x axis
	  shms_xptar_vs_yptar->Fill(shmsyptar,shmsxptar);
	}

	
	if(base_cut_looserf) //no any cal cut at all

	  {
	    hms_sh_vs_psh_base->Fill(hcalepr,hmsshower);
	    shms_sh_vs_psh_base->Fill(pcalepr,shmsshower);
	    ctime_vs_rf_base->Fill(rf_pion, ctime);
	    etot_vs_rf_base->Fill(rf_pion,pcaletottrack);
	    hms_etot_vs_rf_base->Fill(rf_pion,hcaletottrack);
	    epr_vs_rf_base->Fill(rf_pion, pcalepr);
	    ctime_vs_etot_base->Fill(pcaletottrack, ctime);
	    ctime_vs_epr_base->Fill(pcalepr,ctime);
	    sh_vs_rf_base->Fill(rf_pion,shmsshower);
	    hmsepr_vs_rf_base->Fill(rf_pion,hcalepr);
	    hmssh_vs_rf_base->Fill(rf_pion,hmsshower);
	  }	

	if(all_but_noW2Mx2){
	  d_W2->Fill(dW2);
	  d_Wprime2->Fill(Mx2);

	}
	
      }//eventflag
      if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;

    }//nentries

   
    // find acc only under the main ctime peak only (in 16ns..., in 1ns ..., and under main peak ~3 ns ....)
    TH1D *  hist_hcal_did_acc_1peak = (TH1D*)hist_hcal_did_acc->Clone();
    TH1D *  hist_hcal_should_acc_1peak = (TH1D*)hist_hcal_should_acc->Clone();
    TH1D *  hist_pcal_did_acc_1peak = (TH1D*)hist_pcal_did_acc->Clone();
    TH1D *  hist_pcal_should_acc_1peak = (TH1D*)hist_pcal_should_acc->Clone();
    TH1D *  hist_ctime_acc_1peak = (TH1D*)hctimeacc->Clone();//copy of acc hist

    TH2D * hms_sh_vs_psh_should_acc_1peak = (TH2D*)hms_sh_vs_psh_should_acc->Clone();
    TH2D * shms_sh_vs_psh_should_acc_1peak = (TH2D*)shms_sh_vs_psh_should_acc->Clone();


    hist_hcal_did_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_hcal_should_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_pcal_did_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_pcal_should_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_ctime_acc_1peak->Scale((ctmin+ctmax)/16);
    hms_sh_vs_psh_should_acc_1peak->Scale((ctmin+ctmax)/16);
    shms_sh_vs_psh_should_acc_1peak->Scale((ctmin+ctmax)/16);


    
    double onepeakacc_counts = hist_ctime_acc_1peak->Integral();
    //cout<<runs[r]<<"  "<<"acc one peak counts = "<<onepeakacc_counts<<endl;

    if (hist_hcal_did_acc_1peak->GetSumw2N() == 0) hist_hcal_did_acc_1peak->Sumw2(kTRUE);
    if (hist_hcal_should_acc_1peak->GetSumw2N() == 0) hist_hcal_should_acc_1peak->Sumw2(kTRUE);
    if (hist_pcal_did_acc_1peak->GetSumw2N() == 0) hist_pcal_did_acc_1peak->Sumw2(kTRUE);
    if (hist_pcal_should_acc_1peak->GetSumw2N() == 0) hist_pcal_should_acc_1peak->Sumw2(kTRUE);
    if (hist_ctime_acc_1peak->GetSumw2N() == 0) hist_ctime_acc_1peak->Sumw2(kTRUE);

    if (hms_sh_vs_psh_should_acc_1peak->GetSumw2N() == 0) hms_sh_vs_psh_should_acc_1peak->Sumw2(kTRUE);
    if (shms_sh_vs_psh_should_acc_1peak->GetSumw2N() == 0) shms_sh_vs_psh_should_acc_1peak->Sumw2(kTRUE);


    hist_hcal_did_clean->Add(hist_hcal_did_coin,hist_hcal_did_acc_1peak,1.0,-1.0);
    hist_hcal_should_clean->Add(hist_hcal_should_coin,hist_hcal_should_acc_1peak,1.0,-1.0);
    hist_pcal_did_clean->Add(hist_pcal_did_coin,hist_pcal_did_acc_1peak,1.0,-1.0);
    hist_pcal_should_clean->Add(hist_pcal_should_coin,hist_pcal_should_acc_1peak,1.0,-1.0);
    hist_ctime_clean->Add(hctimect,hist_ctime_acc_1peak,1.0,-1.0);

    hms_sh_vs_psh_should_clean->Add(hms_sh_vs_psh_should_coin,hms_sh_vs_psh_should_acc_1peak,1.0,-1.0);
    shms_sh_vs_psh_should_clean->Add(shms_sh_vs_psh_should_coin,shms_sh_vs_psh_should_acc_1peak,1.0,-1.0);

    

    if (hist_hcal_did_clean->GetSumw2N() == 0) hist_hcal_did_clean->Sumw2(kTRUE);
    if (hist_hcal_should_clean->GetSumw2N() == 0) hist_hcal_should_clean->Sumw2(kTRUE);
    if (hist_pcal_did_clean->GetSumw2N() == 0) hist_pcal_did_clean->Sumw2(kTRUE);
    if (hist_pcal_should_clean->GetSumw2N() == 0) hist_pcal_should_clean->Sumw2(kTRUE);
    if (hist_ctime_clean->GetSumw2N() == 0) hist_ctime_clean->Sumw2(kTRUE);
    if (hms_sh_vs_psh_should_clean->GetSumw2N() == 0) hms_sh_vs_psh_should_clean->Sumw2(kTRUE);
    if (hms_sh_vs_psh_should_clean->GetSumw2N() == 0) shms_sh_vs_psh_should_clean->Sumw2(kTRUE);



    

   


    double ctime_acc_ent        = hctimeacc->Integral();
    double ctime_acc_1peak_ent  = hist_ctime_acc_1peak->Integral();
    double ctime_coin_ent       = hctimect->Integral();
    double ctime_clean_ent      = hist_ctime_clean->Integral();
    // cout<<"============================================================================"<<endl;
    // cout<<runs[r]<<"  "<<"Coin Peak, Acc,  Clean enries = "<<ctime_coin_ent<<"    "<<ctime_acc_1peak_ent<<"     "<<ctime_clean_ent<<endl;
    // cout<<"============================================================================"<<endl;

   
    
    double ent_hcaldid_coin =  hist_hcal_did_coin->Integral();
    double ent_hcaldid_acc =  hist_hcal_did_acc->Integral();
    double ent_hcaldid_acc_1peak =  hist_hcal_did_acc_1peak->Integral();
    double ent_hcaldid_clean =  hist_hcal_did_clean->Integral();


    double ent_hcalshould_coin =  hist_hcal_should_coin->Integral();
    double ent_hcalshould_acc =  hist_hcal_should_acc->Integral();
    double ent_hcalshould_acc_1peak =  hist_hcal_should_acc_1peak->Integral();
    double ent_hcalshould_clean =  hist_hcal_should_clean->Integral();

    //Find Bin
    // cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    double int_hcaldid_clean =  hist_hcal_did_clean->Integral(hist_hcal_did_clean->FindBin(hcaletotmin),hist_hcal_did_clean->FindBin(2));
    double int_hcalshould_clean =  hist_hcal_should_clean->Integral(hist_hcal_should_clean->FindBin(0.),hist_hcal_should_clean->FindBin(2));
    //cout<<runs[r]<<"  "<< " hcal : did FindBin / should Find Bin    =  "<<  int_hcaldid_clean<<" / "   << int_hcalshould_clean   << "  =  "<< int_hcaldid_clean/int_hcalshould_clean<<endl;
    double int_pcaldid_clean =  hist_pcal_did_clean->Integral(hist_pcal_did_clean->FindBin(0),hist_pcal_did_clean->FindBin(pcaletotmax));
    double int_pcalshould_clean =  hist_pcal_should_clean->Integral(hist_pcal_should_clean->FindBin(0),hist_pcal_should_clean->FindBin(2));
    //cout<<runs[r]<<"  "<< " pcal : did FindBin / should Find Bin    =  "<<  int_pcaldid_clean<<" / "   << int_pcalshould_clean   << "  =  "<<  int_pcaldid_clean/int_pcalshould_clean<<endl;
    //cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    //cout<<"   "<<endl;
    
    
    double ent_pcaldid_coin =  hist_pcal_did_coin->Integral();
    double ent_pcaldid_acc =  hist_pcal_did_acc->Integral();
    double ent_pcaldid_acc_1peak =  hist_pcal_did_acc_1peak->Integral();
    double ent_pcaldid_clean =  hist_pcal_did_clean->Integral();

    double ent_pcalshould_coin =  hist_pcal_should_coin->Integral();
    double ent_pcalshould_acc =  hist_pcal_should_acc->Integral();
    double ent_pcalshould_acc_1peak =  hist_pcal_should_acc_1peak->Integral();
    double ent_pcalshould_clean =  hist_pcal_should_clean->Integral();

    double hcal_eff = ent_hcaldid_clean/ent_hcalshould_clean;
    double pcal_eff = ent_pcaldid_clean/ent_pcalshould_clean;
    double hcal_eff_err = (1/ent_hcalshould_clean) * sqrt(ent_hcaldid_clean *( 1- hcal_eff ));
    double pcal_eff_err = (1/ent_pcalshould_clean) * sqrt(ent_pcaldid_clean *( 1- pcal_eff ));

    ofstream txtfile1("txtfile-cal-aps/hcal_pcal_eff.txt",ios::app);

    txtfile1<<setprecision(5)<<runs[r]<<"\t"<<hcal_eff<<"\t"<<hcal_eff_err<<"\t"<< pcal_eff<<"\t"<<pcal_eff_err<<endl;
      cout<<runs[r]<<" "<<endl;

  }//runs

}//void
