//This macro reads the HMS histograms from Rootfile and reads the values of pedestals in each PMTs for, trigger, Hodoscopes, calorimeter, and Cerenkov.

void hms_ped(Int_t runNumber, Int_t eventNumber)

{
  const Int_t run           = runNumber;
  const Int_t nevents       = eventNumber;
  const Int_t goldRunNum1   = 1536;            //For Trig only
  const Int_t goldRunNum    = 1782;            //For Detectors only
  const Int_t numHistos     = 3;               //Number of histos for trigger only

  Double_t mean[1000];
  Double_t mean1[1000];
  Double_t meanDiff[1000];//Randomly taken 1000
  Double_t numPMT[1000];
  ofstream myfile;
  myfile.open("outHMS.txt");//To store ped diff

  {  //goes to end of trig

    TFile *f1 = new TFile(Form("ROOTfiles/hms_replay_production_%d_50000.root",goldRunNum1));//Golden_Rootfile for trigger only
    
    myfile <<"______________________________________________________________________________________"<<endl;
    myfile <<"HMS TRIGGER GOLDEN  RUN NUMBER    =" "    "<<goldRunNum1<<endl;
    myfile <<"HMS TRIGGER CURRENT RUN NUMBER    =" "    "<<run<<endl;
    myfile <<"______________________________________________________________________________________"<<endl;
    myfile <<"hms_pped"<< "\t\t\t"<<"Mean_Gold"<<"\t"<<"Mean_Curr"<<"\t"<<"Mean_Diff"<<endl;
    myfile <<"______________________________________________________________________________________"<<endl;
  
    TH1D *histG[numHistos];
    TH1D *hist[numHistos];
    Int_t channel [3]={13,12,15};//(see hallc_replay/MAPS/HMS/DETEC/TRIG/htrig.map)
    TString variables[numHistos]={"hSHWR","hPSHWR","hCER"};
    TString histos[numHistos]={"htrig_hshwr_adc_pped",  "htrig_hpreShwr_adc_pped", "htrig_hcersum_adc_pped" }; 
    Int_t plane=1;
    Int_t bar [3]={6,5,8}; //variables are corresponding to these bars

    //For Golden

    double meanG[numHistos],rmsG[numHistos];
    double mean[numHistos],rms[numHistos];
    double meanDiff[numHistos],rmsDiff[numHistos];
    double eff_rms[numHistos];

    for (int i = 0; i<numHistos ; i++)
      {
	histG[i] = (TH1D*)gDirectory->Get(histos[i]);
	//histG[i] = (TH1D*)gDirectory->GetList()->FindObject(branches[i]);
	if (histG[i]) {

	  meanG[i]=histG[i]->GetMean();
	  rmsG[i]=histG[i]->GetRMS();
	}
	else
	  {

	    cout << "***************ATTENTION REQUIRED *****************************" << endl;
	    cout << "***********HMS_TRIGGER_PULSE_PEDESTALS_HAVE PROBLEMS *********" << endl;
	    cout << "***********PLEASE LOOK AT HMS_TRIGGER_SUM_PPED_HISTOGRAMS*****" << endl;
     
	  }
      }
 
    TFile *f2 = new TFile(Form("ROOTfiles/hms_replay_production_%d_%d.root",run,nevents));      // no golden


    for (int i = 0; i<numHistos ; i++)
      {
	hist[i] = (TH1D*)gDirectory->Get(histos[i]);
	mean[i]=hist[i]->GetMean();
	rms[i]=hist[i]->GetRMS();
      }

    for (int i = 0; i<numHistos ; i++)
      {
	meanDiff[i]=meanG[i]-mean[i];
	eff_rms[i] = sqrt(pow(rmsG[i], 2)+pow(rms[i], 2));
      }



    for (int i = 0; i<numHistos ; i++)
      {
	//open this cout if we want to print values in terminal
	// cout <<channel[i]<<""<<"\t"<< bar[i]<<"\t"<<variables[i]<<"\t"<<"\t"<<meanG[i]<<"\t\t"<<mean[i]<<"\t\t"<<meanDiff[i]<<endl;
	myfile<<histos[i]<<"\t"<<"\t"<<meanG[i]<<"\t\t"<<mean[i]<<"\t\t"<<meanDiff[i]<<endl;//to stores values in .txt file


      }
  
    for (int i = 0; i<numHistos ; i++)
      {
	if(abs(meanDiff[i])>2.5) // //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
	  {
	    cout<<"_____________________________________________________________________"<<endl;
	    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!" << endl;
	    cout<<"_____________________________________________________________________"<<endl;
	 
	    cout << "--------------------See ROC1 --- SLOT 17---------------------------" << endl;//hallc_replay/MAPS/HMS/DETEC/TRIG/htrig.map
	    cout<<"___________________________________________________________________________________"<<endl;
	    cout<<"Golden Run = "<<goldRunNum1<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
	    cout<<"___________________________________________________________________________________"<<endl;
	    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	    cout<<"___________________________________________________________________________________"<<endl;
	    cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
	    cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
	    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	    cout<<"___________________________________________________________________________________"<<endl;
	    cout << setprecision(2) << fixed <<"chan"<<" "<< channel[i] << " " <<"bar"<<" "<< bar[i] 
		 << "\t" <<  variables[i] << "\t" <<"MG"<<"  "<<meanG[i] <<"  " 
		 <<"M"<<"  "<< mean[i] <<" " <<"MD"<<" "<< meanDiff[i] << endl;//MG=mean golden,M = mean current, MD = mean diff
	    cout<<"_____________________________________________________________________"<<endl;
       
	  }	

      }
 
    myfile <<"___________________________________________________________________________"<<endl;

  }

  //----------------------------HMS DETECTORS PPED STARTS HERE--------------------------


  TFile *f3 = new TFile(Form("ROOTfiles/hms_replay_production_%d_50000.root",goldRunNum));//Golden_Rootfile for detectors only

  TFile *f4 = new TFile(Form("ROOTfiles/hms_replay_production_%d_%d.root",run,nevents));//Current Rootfile

  myfile <<"________________________________________________________________________________________"<<endl;
  myfile <<"HMS PEDESTAL GOLDEN  RUN NUMBER    =" "    "<<goldRunNum<<endl;
  myfile <<"HMS PEDESTAL CURRENT  RUN NUMBER   =" "    "<<run<<endl;
  myfile <<"________________________________________________________________________________________"<<endl;
  myfile <<"hms_good_pped"<< "\t\t\t"<<"PMT_Num"<<"\t\t"<<"Mean_Gold"<<"    "<<"Mean_Curr"<<" \t   "<<"Mean_Diff"<<endl;
  myfile <<"________________________________________________________________________________________"<<endl;


  {   //goes to end of detectors 

    //-------------------------------------FOR HMS HODOSCOPE PMTS IN 1X = 16, 1Y =10, 2X = 16, 2Y = 10------------------

  
    {  //goes to end of hodo

      TH1D *hist[8];//Total Histograms =8
      TH1D *hist1[8];
      TString plane[4]= {"1x","1y","2x","2y"};//4 planes
      TString polarity[2] = {"pos","neg"};//Two sides
      Int_t numPMT[4] = {16, 10, 16, 10};//PMTs in each side

      for(int i = 0; i < 4; ++i)//plane
  	{
  	  for(int j = 0; j<2; ++j)//polarity
  	    {
  	      TString histName = "hhodo_";
  	      histName += plane[i];
  	      histName += "_good_pped_vs_pmt_";
  	      histName += polarity[j];  //Reading the Histogram from Golden Run
  	      TH2D* hist = (TH2D*)f3->Get(histName);
	      
  	      TString histName1 = "hhodo_";
  	      histName1 += plane[i];
  	      histName1 += "_good_pped_vs_pmt_";
  	      histName1 += polarity[j];//Reading the histogram from current Run
  	      TH2D *hist1  = (TH2D*)f4->Get(histName1);
  	      TH1D *projHist;//For Golden Run
  	      TH1D *projHist1;//For Current Run

  	      bool first_error = true;
	      
  	      for(int k = 0; k< numPMT[i]; ++k)//PMT
  		{
		  
  		  projHist     =  hist->ProjectionY("hodo_proj", k+1, k+1);
  		  projHist1    =  hist1->ProjectionY("hodo_proj1", k+1, k+1);

  		  mean[k] = projHist->GetMean();//Mean Golden
  		  mean1[k] = projHist1->GetMean();//Mean Current
  		  meanDiff[k] = abs(mean[k]-mean1[k]);//Mean Diff

  		  //	cout <<histName<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current ="<<mean1[k]<<" Mean_Diff = "<<abs(mean[k]-mean1[k])<<endl;
  		  myfile << setprecision(2) << fixed << histName << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file
  		  if (mean1[k]!=0.0) {

  		    if(abs(meanDiff[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
  		      {
  			if(first_error){
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
  			  cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
  			  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  first_error=false;
  			}
  			cout << setprecision(2) << fixed<<histName<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean[k] <<"  " 
  			     <<"M ="<<"  "<< mean1[k] <<" " <<"MD"<<" "<< meanDiff[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
  			cout<<"___________________________________________________________________________________"<<endl;
  		      }
  		  }
  		}
  	    }
  	}
       
      myfile<<"******************************************************************************************"<<endl;

    }

    //************************HMS CALORIMETER hA and hB***************SHWR*****************************************// 
    {   //goes to end of hA, hB

      TH1D *hist[4];
      TH1D *hist1[4];
      TString hcal[2]= {"hA","hB"};
      TString polarity[2] = {"pos","neg"};
      Int_t numPMT[2] = {13, 13};
 
      for(int i = 0; i < 2; ++i)//plane
  	{
  	  for(int j = 0; j<2; ++j)//polarity
  	    {
  	      TString histName = "hcal_";
  	      histName += hcal[i];
  	      histName += "_good_pped_vs_pmt_";
  	      histName += polarity[j];                     //Get Histogram From Golden
  	      TH2D* hist = (TH2D*)f3->Get(histName);
	 
  	      TString histName1 = "hcal_";
  	      histName1 += hcal[i];
  	      histName1 += "_good_pped_vs_pmt_";
  	      histName1 += polarity[j];                 //Get Histogram from Current
  	      TH2D *hist1  = (TH2D*)f4->Get(histName1);
  	      TH1D *projHist;
  	      TH1D *projHist1;
  	      bool first_error = true;
	      
  	      for(int k = 0; k< numPMT[i]; ++k)//PMT
  		{
  		  projHist     =  hist->ProjectionY("hcal_proj", k+1, k+1); //Y-Projection
  		  projHist1    =  hist1->ProjectionY("hcal_proj1", k+1, k+1);//Y-Projection

  		  mean[k] = projHist->GetMean();//Getting Mean from Golden Run
  		  mean1[k] = projHist1->GetMean();//Getting Mean from Current Run
		
  		  //	cout <<histName<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current ="<<mean1[k]<<" Mean_Diff = "<<abs(mean[k]-mean1[k])<<endl;

  		  myfile<<histName << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file
  		  if (mean1[k]!=0.0) {

  		    if(abs(meanDiff[k])>2.5) 
  		      {
  			if(first_error){
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
  			  cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
  			  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  first_error=false;
  			}
  			cout << setprecision(2) << fixed<<histName<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean[k] <<"  " 
  			     <<"M ="<<"  "<< mean1[k] <<" " <<"MD"<<" "<< meanDiff[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
  			cout<<"___________________________________________________________________________________"<<endl;
  		      }
  		  }
  		}
  	    }
  	}
    
      myfile<<"******************************************************************************************"<<endl;

    }
    //***************HMS CAL hC and hD ************PRESHWR PLANES**************************************

    {  //goes upto end of hC, hD

      TH1D *hist[2];//ONLY TWO HISTOGRAMS
      TH1D *hist1[2];
      TString hcal[2]= {"hC","hD"};
      TString polarity[1] = {"pos"};
      Int_t numPMT[2] = {13, 13};
      for(int i = 0; i < 2; ++i)//plane
  	{
  	  for(int j = 0; j<1; ++j)//polarity
  	    {
  	      TString histName = "hcal_";
  	      histName += hcal[i];
  	      histName += "_good_pped_vs_pmt_";
  	      histName += polarity[j];          //GETTING HOSTOGRAM FROM GOLDEN RUN
  	      TH2D* hist = (TH2D*)f3->Get(histName);
	 
  	      TString histName1 = "hcal_";
  	      histName1 += hcal[i];
  	      histName1 += "_good_pped_vs_pmt_";
  	      histName1 += polarity[j];          //Getting Histogram from Current Run
  	      TH2D *hist1  = (TH2D*)f4->Get(histName1);
  	      TH1D *projHist;
  	      TH1D *projHist1;

  	      bool first_error = true;
   
  	      for(int k = 0; k< numPMT[i]; ++k)//PMT
  		{
  		  projHist     =  hist->ProjectionY("hcal_proj", k+1, k+1);  //Y projection of golden Run
  		  projHist1    =  hist1->ProjectionY("hcal_proj1", k+1, k+1);  //Y- Projection of current Run

  		  mean[k] = projHist->GetMean();//Mean Golden
  		  mean1[k] = projHist1->GetMean();//Mean Current
		
  		  // cout << histName <<" PMT = " << k+1 <<" Mean = " <<mean[k] <<endl;
  		  // cout <<histName1 <<" PMT = " << k+1 <<" Mean = " <<mean1[k] <<endl;
  		  //cout <<histName<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current ="<<mean1[k]<<" Mean_Diff = "<<abs(mean[k]-mean1[k])<<endl;
		
  		  myfile<<histName << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file
  		  if (mean1[k]!=0.0) {

  		    if(abs(meanDiff[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
  		      {
  			if(first_error){
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
  			  cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
  			  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  			  cout<<"___________________________________________________________________________________"<<endl;
  			  first_error=false;
  			}
  			cout << setprecision(2) << fixed<<histName<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean[k] <<"  " 
  			     <<"M ="<<"  "<< mean1[k] <<" " <<"MD"<<" "<< meanDiff[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
  			cout<<"___________________________________________________________________________________"<<endl;

       
  		      }
    
  		  }
  		}
	    
  	    }
  	}
    
  
      myfile<<"******************************************************************************************"<<endl;

    }

    //************************HMS CERENKOV**************************************************************//
    {  //goes to end of cer


      TH1D *hist[1];//only 1 histogram
      TH1D *hist1[1];

      TString hcer[1]= {"hcer"};
      Int_t numPMT[1] = {2}; //One histogram, two pmts, no positive and negative sides
 
  
      for(int i = 0; i < 1; ++i)//plane
  	{

  	  TString histName = "hcer";
  	  histName += "_good_pped_vs_pmt";// reads Hisogram from Golden Run
  	  TH2D* hist = (TH2D*)f3->Get(histName);
	
  	  TString histName1 = "hcer";
  	  histName1 += "_good_pped_vs_pmt";//Reads Histogram from Current Run
	  
  	  TH2D *hist1  = (TH2D*)f4->Get(histName1);
  	  TH1D *projHist;
  	  TH1D *projHist1;
  	  bool first_error = true;
	  
  	  for(int k = 0; k< numPMT[i]; ++k)//PMT
  	    {
  	      projHist     =  hist->ProjectionY("hcal_proj", k+1, k+1);//Y-Projection
  	      projHist1    =  hist1->ProjectionY("hcal_proj1", k+1, k+1);//Y-projection

  	      mean[k] = projHist->GetMean();//Mean Golden
  	      mean1[k] = projHist1->GetMean();//Mean current
	    
  	      // cout << histName <<" PMT = " << k+1 <<" Mean = " <<mean[k] <<endl;
  	      // cout <<histName1 <<" PMT = " << k+1 <<" Mean = " <<mean1[k] <<endl;
  	      // cout <<histName<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current ="<<mean1[k]<<" Mean_Diff = "<<abs(mean[k]-mean1[k])<<endl;

  	      myfile<<"------"<< histName  << "\t"<< "PMT  ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file
  	      if (mean1[k]!=0.0) {

  		if(abs(meanDiff[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
  		  {
  		    if(first_error){
  		      cout<<"___________________________________________________________________________________"<<endl;
  		      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
  		      cout<<"___________________________________________________________________________________"<<endl;
  		      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  		      cout<<"___________________________________________________________________________________"<<endl;
  		      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
  		      cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
  		      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  		      cout<<"___________________________________________________________________________________"<<endl;
  		      first_error=false;
  		    }
  		    cout << setprecision(2) << fixed<<histName<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean[k] <<"  " 
  			 <<"M ="<<"  "<< mean1[k] <<" " <<"MD"<<" "<< meanDiff[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
  		    cout<<"___________________________________________________________________________________"<<endl;
  		  }
	     
  	      }
  	    }
  	}
    
      myfile <<"******************************************************************************************"<<endl;
    }

    myfile.close();
    
  }  
}
