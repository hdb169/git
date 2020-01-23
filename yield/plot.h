#define ROOT_header


TCanvas *c1 = new TCanvas("c1","c1",1600,1200);
 
c1->Divide(3,3);
c1->cd(1);
 
h_datactime->SetLineColor(kBlue);
//if(!(h_datactime->GetSumw2N()>0)) h_datactime->Sumw2(kTRUE);
h_datactime->Draw("");
h_datactime->SetTitle(" ctime with pid cut");
h_datactime->SetLineWidth(2);
  
c1->cd(2);
h_dataz_d->SetLineColor(kBlue);
if(!(h_dataz_d->GetSumw2N()>0)) h_dataz_d->Sumw2(kTRUE);
h_dataz_d->Draw("e,p1");
h_dataz_d->SetTitle("zhadron with pid & ctime cut");
h_dataz_d->SetLineWidth(2); 
  
c1->cd(3);
h_dataz_acc->SetLineColor(kRed);
if (!( h_dataz_acc->GetSumw2N() > 0))  h_dataz_acc->Sumw2(kTRUE);
h_dataz_acc->Draw("e,p1");
h_dataz_acc->SetTitle("zhadron with accidental in 8. peaks");
h_dataz_acc->SetLineWidth(2);   

c1->cd(4);
h_datactime->Draw();
h_datactime_acc->SetLineColor(kRed);
h_datactime_d->Draw("same");
h_datactime_d->SetFillColor(kPink);
h_datactime_acc->Draw("same");
h_datactime_acc->SetFillColor(kYellow);
h_datactime_acc->SetTitle("ctime with acc within 8. peaks");
h_datactime_acc->SetLineWidth(2);	
  


c1->cd(5);
TH1D *h_dataz_d_copy = new TH1D("h_dataz_d_copy","h_dataz_d_copy",binz,loz,hiz);
TH1D *h_dataz_acc_copy = new TH1D("h_dataz_acc_copy","h_dataz_acc_copy",binz,loz,hiz);
h_dataz_d_copy= (TH1D*)h_dataz_d->Clone();//copy of h_dataz_d
h_dataz_acc_copy= (TH1D*)h_dataz_acc->Clone();//copy of h_dataz_acc
h_dataz_acc_copy->Scale(1.0/8.0);// scale the accidental plot by 1/8.
TH1D *h_dataz_acc_scaled= (TH1D*)h_dataz_acc_copy->Clone();
if (!( h_dataz_acc_scaled->GetSumw2N() > 0))  h_dataz_acc_scaled->Sumw2(kTRUE);
h_dataz_acc_scaled->Draw();
h_dataz_acc_scaled->SetLineColor(kRed);
h_dataz_acc_scaled->SetLineWidth(2);
h_dataz_acc_scaled->SetTitle("zhadron in scaled hist");


c1->cd(6);
if (!( h_dataz_d_copy->GetSumw2N() > 0))  h_dataz_d_copy->Sumw2(kTRUE);
h_dataz_d_copy->Draw("e,p1");
if (!(  h_dataz_acc_copy->GetSumw2N() > 0))  h_dataz_acc_copy->Sumw2(kTRUE);
h_dataz_acc_copy->Draw("same");
h_dataz_d_copy->SetLineColor(kBlue);
h_dataz_acc_copy->SetLineColor(kRed);



c1->cd(7);
  
////======================do the accidental subtraction: corrected hist-accidental hist=========================================

TH1D *h_dataz_final = new TH1D("h_dataz_final","h_dataz_final",binz,loz,hiz);// data-accidental
h_dataz_final->Add( h_dataz_d_copy,  h_dataz_acc_copy, 1.0, -1.0);
if (!( h_dataz_final->GetSumw2N() > 0))  h_dataz_final->Sumw2(kTRUE);
h_dataz_final->Draw("e,p1");
h_dataz_final->SetLineColor(kBlack);
h_dataz_final->SetLineWidth(3);


cout<<"all entries = "<< nentriesD <<endl;
cout<<"all without ctime cut = "<< h_datactime->Integral()<<endl;	
cout<<"all with ctime cut = "<<h_dataz_d->Integral()<<endl; 	
cout<<"accidental cuts in 8. peaks = "<<h_dataz_acc->Integral()<<endl;
cout<<"scaled accidental ="<<h_dataz_acc_scaled->Integral()<<endl;
cout<<"final good = "<<h_dataz_final->Integral()<<endl;
