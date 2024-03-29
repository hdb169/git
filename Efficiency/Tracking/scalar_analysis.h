//this file has to be included in the traacking eff file to calculate rate or current and to apply the current cut > 5 in data analysis too
TTree * ss = (TTree *)f->Get("TSP");
Long64_t scal_entries = ss->GetEntries();

Double_t  Scal_evNumber;
ss->SetBranchAddress("evNumber",&Scal_evNumber);
Double_t  Scal_BCM4B_charge;
ss->SetBranchAddress("P.BCM4B.scalerCharge",&Scal_BCM4B_charge);
Double_t  Scal_BCM4B_current;
ss->SetBranchAddress("P.BCM4B.scalerCurrent",&Scal_BCM4B_current);
Double_t  Scal_BCM1_charge;
ss->SetBranchAddress("P.BCM1.scalerCharge",&Scal_BCM1_charge);
Double_t  Scal_BCM1_current;
ss->SetBranchAddress("P.BCM1.scalerCurrent",&Scal_BCM1_current);
Double_t  Scal_time;
ss->SetBranchAddress("P.1MHz.scalerTime",&Scal_time);
Double_t  Scal_EDTM;
ss->SetBranchAddress("P.EDTM.scaler",&Scal_EDTM);
Double_t  Scal_hEL_CLEAN;
ss->SetBranchAddress("P.pEL_CLEAN.scaler",&Scal_hEL_CLEAN);
Double_t  Scal_hEL_REAL;
ss->SetBranchAddress("P.pEL_REAL.scaler",&Scal_hEL_REAL);
Double_t  Scal_TRIG2;
ss->SetBranchAddress("P.pTRIG2.scaler",&Scal_TRIG2);
Double_t  Scal_TRIG3;
ss->SetBranchAddress("P.pTRIG3.scaler",&Scal_TRIG3);
Double_t  Scal_TRIG1;
ss->SetBranchAddress("P.pTRIG1.scaler",&Scal_TRIG1);
Double_t  Scal_TRIG4;
ss->SetBranchAddress("P.pTRIG4.scaler",&Scal_TRIG4);
Double_t  Scal_TRIG5;
ss->SetBranchAddress("P.pTRIG5.scaler",&Scal_TRIG5);
Double_t  Scal_TRIG6;
ss->SetBranchAddress("P.pTRIG6.scaler",&Scal_TRIG6);
Double_t  Scal_pHGCER;
ss->SetBranchAddress("P.HCER.scaler",&Scal_pHGCER);
Double_t  Scal_Splane[4];
ss->SetBranchAddress("P.S1X.scaler",&Scal_Splane[0]);
ss->SetBranchAddress("P.S1Y.scaler",&Scal_Splane[1]);
ss->SetBranchAddress("P.S2X.scaler",&Scal_Splane[2]);
ss->SetBranchAddress("P.S2Y.scaler",&Scal_Splane[3]);
//loop through scalers
Int_t nscal_reads=0;
Int_t nscal_reads_cut=0;
Double_t prev_read=-1;
Double_t charge_sum=0;
Double_t charge_sum_cut=0;
Double_t prev_charge=0;
Double_t charge_sum_corr=0;
Double_t charge_sum_cut_corr=0;
Double_t prev_charge_corr=0;
Double_t event_flag[20000];
Double_t scal_event_number[20000];
Double_t tot_scal_EDTM=0;
Double_t tot_scal_cut_EDTM=0;
Double_t prev_EDTM=0;
Double_t tot_scal_hEL_CLEAN=0;
Double_t tot_scal_cut_hEL_CLEAN=0;
Double_t prev_hEL_CLEAN=0;
Double_t tot_scal_hEL_REAL=0;
Double_t tot_scal_cut_hEL_REAL=0;
Double_t prev_hEL_REAL=0;
Double_t tot_scal_TRIG2=0;
Double_t tot_scal_TRIG3=0;
Double_t prev_TRIG2=0;
Double_t prev_TRIG3=0;
Double_t tot_scal_cut_TRIG2=0;
Double_t tot_scal_cut_TRIG3=0;
Double_t tot_scal_TRIG1=0;
Double_t tot_scal_TRIG4=0;
Double_t prev_TRIG1=0;
Double_t prev_TRIG4=0;
Double_t tot_scal_cut_TRIG1=0;
Double_t tot_scal_cut_TRIG4=0;
Double_t tot_scal_cut_time=0;
Double_t tot_scal_TRIG5=0;
Double_t prev_TRIG5=0;
Double_t tot_scal_cut_TRIG5=0;
Double_t tot_scal_TRIG6=0;
Double_t prev_TRIG6=0;
Double_t tot_scal_pHGCER=0;
Double_t tot_scal_cut_pHGCER=0;
Double_t prev_pHGCER=0;
Double_t tot_scal_cut_TRIG6=0;
Double_t threshold_cut=5.0;
Double_t minimumcur_cut=5.0;//5

//
Double_t tot_scal_Splane[4]={0,0,0,0};
Double_t prev_Splane[4]={0,0,0,0};
Double_t tot_scal_cut_Splane[4]={0,0,0,0};
//
Double_t tot_scal_time=0;
Double_t prev_time=0;
// cout << " scal ent = " << scal_entries << endl;
Double_t nlast=float(scal_entries);
TH1F *h_cur_entry = new TH1F("h_cur_entry","; ENtry;current",nlast,0,nlast);
TH1F *h_cur = new TH1F("h_cur","; Current ;",200,0,100);
//  Long64_t data_entries = tt->GetEntries();
for (int i = 0; i < scal_entries; i++) {
  ss->GetEntry(i);
  h_cur_entry->Fill(float(i),Scal_BCM1_current);
  if (Scal_BCM1_current > 3) h_cur->Fill(Scal_BCM1_current);//>3
 }
  
Double_t peak_current = h_cur->GetBinCenter(h_cur->GetMaximumBin());
//cout << " Peak current = " << peak_current  <<" " <<  h_cur->GetMaximumBin() << endl;
Double_t Scal_BCM1_charge_corr=0;
for (int i = 0; i < scal_entries; i++) {
  ss->GetEntry(i);
  event_flag[nscal_reads] = 0;
  scal_event_number[nscal_reads] = Scal_evNumber;
  Double_t BCM1_correction=1.;
  if (Scal_BCM1_current >2.) {
    if (Scal_BCM1_current <= 60) {
      BCM1_correction =1.0 + 0.045* ( log(60.)-log(Scal_BCM1_current))/( log(60.)-log(2.) );
    } else {
      BCM1_correction =1.0 + 0.010*(Scal_BCM1_current-60)/25.;
    } 
  }
  Scal_BCM1_charge_corr+=Scal_BCM1_current*(Scal_time-prev_time)*BCM1_correction;
  //cout << Scal_BCM1_charge << " "  << Scal_BCM1_charge_corr << " " << BCM1_correction << endl;
   if (TMath::Abs(Scal_BCM1_current) > minimumcur_cut) {
  // if (TMath::Abs(Scal_BCM1_current-peak_current) < threshold_cut) {


    
    event_flag[nscal_reads] = 1;


    tot_scal_cut_time+=(Scal_time-prev_time);
    tot_scal_cut_EDTM+=(Scal_EDTM-prev_EDTM);
    tot_scal_cut_hEL_CLEAN+=(Scal_hEL_CLEAN-prev_hEL_CLEAN);
    tot_scal_cut_hEL_REAL+=(Scal_hEL_REAL-prev_hEL_REAL);
    tot_scal_cut_TRIG2+=(Scal_TRIG2-prev_TRIG2);
    tot_scal_cut_TRIG3+=(Scal_TRIG3-prev_TRIG3);
    tot_scal_cut_TRIG1+=(Scal_TRIG1-prev_TRIG1);
    tot_scal_cut_TRIG4+=(Scal_TRIG4-prev_TRIG4);
    tot_scal_cut_TRIG5+=(Scal_TRIG5-prev_TRIG5);
    tot_scal_cut_TRIG6+=(Scal_TRIG6-prev_TRIG6);
    tot_scal_cut_pHGCER+=(Scal_pHGCER-prev_pHGCER);
    for (Int_t s=0;s<4;s++) tot_scal_cut_Splane[s]+=(Scal_Splane[s]-prev_Splane[s]);
    //	     cout << i << " " << tot_scal_cut_Splane[0] << " " << Scal_Splane[0] << " " << prev_Splane[0] << endl;

    charge_sum_cut+=(Scal_BCM1_charge-prev_charge);
    charge_sum_cut_corr+=(Scal_BCM1_charge_corr-prev_charge_corr);
    nscal_reads_cut++;
  }
  prev_charge = Scal_BCM1_charge;
  prev_charge_corr = Scal_BCM1_charge_corr;
  prev_time = Scal_time;
  prev_EDTM = Scal_EDTM;
  prev_hEL_CLEAN = Scal_hEL_CLEAN;
  prev_hEL_REAL = Scal_hEL_REAL;
  prev_TRIG2 = Scal_TRIG2;
  prev_TRIG3 = Scal_TRIG3;
  prev_TRIG1 = Scal_TRIG1;
  prev_TRIG4 = Scal_TRIG4;
  prev_TRIG5 = Scal_TRIG5;
  prev_TRIG6 = Scal_TRIG6;
  prev_pHGCER = Scal_pHGCER;
  for (Int_t s=0;s<4;s++) prev_Splane[s]=Scal_Splane[s];
  // cout <<  nscal_reads <<  " " << Scal_BCM4B_current << " " << event_flag[nscal_reads] << " " << Scal_TRIG1 << endl;
  nscal_reads++;
  charge_sum=Scal_BCM1_charge;
  charge_sum_corr=Scal_BCM1_charge_corr;
  tot_scal_EDTM=Scal_EDTM;
  tot_scal_hEL_CLEAN=Scal_hEL_CLEAN;
  tot_scal_hEL_REAL=Scal_hEL_REAL;
  tot_scal_TRIG2=Scal_TRIG2;
  tot_scal_TRIG3=Scal_TRIG3;
  tot_scal_TRIG1=Scal_TRIG1;
  tot_scal_TRIG4=Scal_TRIG4;
  tot_scal_TRIG5=Scal_TRIG5;
  tot_scal_TRIG6=Scal_TRIG6;
  tot_scal_time=Scal_time;
  tot_scal_pHGCER=Scal_pHGCER;
  for (Int_t s=0;s<4;s++) tot_scal_Splane[s]=Scal_Splane[s];
 }

    
Double_t Elclean_Rate = tot_scal_cut_hEL_CLEAN/(tot_scal_cut_time*1000);
Double_t Elreal_Rate = tot_scal_cut_hEL_REAL/(tot_scal_cut_time*1000);
Double_t PTRIG2_Rate = tot_scal_cut_TRIG2/(tot_scal_cut_time*1000);
Double_t PTRIG3_Rate = tot_scal_cut_TRIG3/(tot_scal_cut_time*1000);//----------------------------------------------------HMS
Double_t hgcer_trig_rate =  tot_scal_cut_pHGCER/(tot_scal_cut_time*1000);//kHz
Double_t PTRIG1_Rate = tot_scal_cut_TRIG1/(tot_scal_cut_time*1000);
Double_t Edtm_Rate = tot_scal_cut_EDTM/(tot_scal_cut_time*1000);
