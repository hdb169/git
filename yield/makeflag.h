//make an universal flag for the cut
//This code does not work

for (int kk=0; kk<nentriesD;  kk++)//original
    //for (int kk=0; kk<50000;  kk++)
   
    {

      tt->GetEntry(kk);

      if (kk % 700000 == 0) cout << kk*100/nentriesD << "   % of data done" << endl;

      bool universal_flag = false;
      if(paeronpe>2.0 && pcalepr< 0.1 && pcalepr > 0.00001 && pcaletottrack < 0.4 && pcaletottrack> 0.1 && hcaletot > 0.8 &&
	 hcaletot < 1.2 && hdelta> -10 && hdelta < 10 && pdelta >-10 && pdelta < 20  && hcernpe > 1.5 &&  pbeta > 0.7 && 
	 pbeta < 1.3 &&hbeta > 0.7 &&hbeta < 1.3  && hhodstarttime ==1 &&phodstarttime == 1 && hdipole==1 && pdipole ==1){

	universal_flag = true;
      }
      else universal_flag = false;


      //  Epi = sqrt(pow(pionMass,2) + pow(PgtrP,2));
      //  z = Epi/pkinomega;


      if(universal_flag == true){


	h_datactime->Fill(ctime);

      }
      Int_t bin_max = h_datactime->GetMaximumBin();
      Double_t max_value = h_datactime->GetBinCenter(bin_max);
      cout<<"ctime peak is at = "<< max_value <<endl;

      bool cointime_flag = false;
      if(ctime > (max_value-2) && ctime < (max_value+2)){
	cointime_flag = true;
      }
      else cointime_flag = false;
  

      if(universal_flag == true && cointime_flag == true){

	h_dataz_acc->Fill(z);
      }
    }
