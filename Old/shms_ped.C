//This macro reads the SHMS histograms from Rootfile and reads the values of pedestals in each PMTs for, trigger, Hodoscopes, calorimeter, HGCER,  NGCERand Aerogel.

#include <TH1F.h>
#include <TH2F.h>
#include <cmath>
void shms_ped(Int_t runNumber, Int_t eventNumber)
{
  const Int_t run          = runNumber;
  const Int_t nevents      = eventNumber;
  const Int_t goldRunNum1  = 2467;// for trig only
  const Int_t goldRunNum   = 2687;// for detectors only
  const Int_t numHistos  = 5;     //Number of histos for Trig only
  Double_t mean[1000];
  Double_t mean1[1000];
  Double_t meanDiff[1000];
  Double_t numPMT[1000];

  ofstream myfile;
  myfile.open("outSHMS.txt"); //To store pedestals differences


  { // goes to the end of trigger


    TFile *f1 = new TFile(Form("ROOTfiles/shms_replay_production_%d_50000.root", goldRunNum1));//Golden Run for Trigger only

    myfile <<"____________________________________________________________________________"<<endl;
    myfile <<"SHMS TRIGGER GOLDEN  RUN NUMBER    =" "  "<<goldRunNum1<<endl;
    myfile <<"SHMS TRIGGER CURRENT RUN NUMBER    =" "  "<<run<<endl;
    myfile <<"____________________________________________________________________________"<<endl;
    myfile <<"shms_sum_pped"<< "\t\t\t"<<"Mean_Gold"<<"\t"<<"Mean_Curr"<<"\t"<<"Mean_Diff"<<endl;
    myfile <<"____________________________________________________________________________"<<endl;


    TH1D *histG[numHistos];
    TH1D *hist[numHistos];
    Int_t   channel[5] = {1,2,3,4,5}; //(see hallc_replay/MAPS/SHMS/DETEC/TRIG/ptrig.map)
    TString variables[numHistos] = {"pHGCER", "pNGCER", "pPSHWR", "pHG_MOD", "pNG_MOD"};
    TString histos[numHistos]    = {"ptrig_phgc_sum_pped", "ptrig_pngc_sum_pped", "ptrig_prshwr_sum_pped", "ptrig_phgc_sum_MOD_pped", "ptrig_pngc_sum_MOD_pped"};
 
    Int_t plane=1;
    Int_t bar [5]={2,3,4,6,7}; //variables are corresponding to these bars
 
    // For Goldern

    double meanG[numHistos],    rmsG[numHistos];
    double mean[numHistos],     rms[numHistos];
    double meanDiff[numHistos], rmsDiff[numHistos];
    double eff_rms[numHistos];


    for (int i = 0; i < numHistos-2 ; i++)
      {
	histG[i] = (TH1D*)gDirectory->Get(histos[i]);
	if (histG[i]) {
	  meanG[i]=histG[i]->GetMean();
	  rmsG[i]=histG[i]->GetRMS();
	}
	else 
	  {	
	    cout << "****************ATTENTION REQUIRED ********************************" << endl;
	    cout << "************SHMS_TRIGGER_PULSE_PEDESTALS_HAVE PROBLEMS ************" << endl;
	    cout << "************PLEASE LOOK AT SHMS_TRIGGER_SUM_PPED_HISTOGRAMS********" << endl;    
	  }
      }
 
    TFile *f2= new TFile(Form("ROOTfiles/shms_replay_production_%d_%d.root",run,nevents));  // no golden

    for (int i = 0; i < numHistos-2 ; i++)
      {
	hist[i] = (TH1D*)gDirectory->Get(histos[i]);
	// cout << "mean = " << hist[i]->GetMean() << endl;
	mean[i]=hist[i]->GetMean();
	rms[i]=hist[i]->GetRMS();
      }

    for (int i = 0; i < numHistos-2 ; i++)
      {
	meanDiff[i]=meanG[i]-mean[i];
	eff_rms[i] = sqrt(pow(rmsG[i], 2)+pow(rms[i], 2));
      }


    for (int i = 0; i < numHistos-2 ; i++)
      {
	//open this cout if we want to print values in terminal
	//	cout <<channel[i]<<""<<"\t"<< bar[i]<<"\t"<<histos[i]<<"\t"<<"\t"<<meanG[i]<<"\t\t"<<mean[i]<<"\t\t"<<meanDiff[i]<<endl;
	myfile<<histos[i]<<"\t"<<"\t"<<meanG[i]<<"\t\t"<<mean[i]<<"\t\t"<<meanDiff[i]<<endl;//to store values in .txt file

      }
 
    for (int i = 0; i < numHistos-2 ; i++)
      {
	if(abs(meanDiff[i])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
	  {
	  
	    cout<<"_____________________________________________________________________"<<endl;
	    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!" << endl;
	    cout<<"_____________________________________________________________________"<<endl;
	 
	    cout << "--------------------See ROC2 --- SLOT 14---------------------------" << endl;//hallc_replay/MAPS/SHMS/DETEC/TRIG/ptrig.map
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

  //--------------------------------FOR SHMSC  DETECTORS ------------STARTS FROM HERE-------------------

 
  TFile *f3 = new TFile(Form("ROOTfiles/shms_replay_production_%d_50000.root",goldRunNum));//Golden ROOTfile Detectors only

  TFile *f4 = new TFile(Form("ROOTfiles/shms_replay_production_%d_%d.root",run,nevents));//Takes Current ROOTfile

  myfile <<"SHMS PEDESTAL GOLDEN  RUN NUMBER  =" "    "<<goldRunNum<<endl;
  myfile <<"SHMS PEDESTAL CURRENT  RUN NUMBER =" "    "<<run<<endl;
  myfile <<"____________________________________________________________________________________________"<<endl;
  myfile <<"shms_good_pped"<< "\t\t\t\t"<<"PMT_Num"<<"\t\t"<<"Mean_Gold"<<"    "<<"Mean_Curr"<<"    "<<"Mean_Diff"<<endl;
  myfile <<"____________________________________________________________________________________________"<<endl;

  {   //goes to end of all detectors

    //******************FOR SHMS HODOSCOPE, PMTS in 1x = 13, 1y =13, 2x=14, 2y =21*************************
  
    {  //goes to end of hodo

      TH1D *hist[8];//8 Histograms for SHMS HODO
      TH1D *hist1[8];

      TString plane[4]= {"1x","1y","2x","2y"};//4-planes
      TString polarity[2] = {"pos","neg"};//2-sides in each plane
      Int_t numPMT[4] = {13, 13, 14, 21};//Pmts in 4 planes
  
      for(int i = 0; i < 4; ++i)//plane
	{
	  for(int j = 0; j<2; ++j)//polarity
	    {
	      TString histName = "phodo_";
	      histName += plane[i];
	      histName += "_good_pped_vs_pmt_";
	      histName += polarity[j]; //READS THE HISTOGRAM for GOLDEN RUN
	    
	      TH2D* hist = (TH2D*)f3->Get(histName);
	      
	      TString histName1 = "phodo_";  //Get The Histogram
	      histName1 += plane[i];
	      histName1 += "_good_pped_vs_pmt_";
	      histName1 += polarity[j]; //READS THE HISTOGRAMFOR CURRENT RUN
	  
	      TH2D *hist1  = (TH2D*)f4->Get(histName1);//Read 
	      TH1D *projHist;
	      TH1D *projHist1;

	      bool first_error = true;
	      
	      for(int k = 0; k< numPMT[i]; ++k)//PMT
	      
		{
		  projHist     =  hist->ProjectionY("phodo_proj", k+1, k+1);
		  projHist1    =  hist1->ProjectionY("phodo_proj1", k+1, k+1);//CALCULATES Y-PROJECTION

		  mean[k] = projHist->GetMean();//Mean Golden
		  mean1[k] = projHist1->GetMean();//Mean Current 
		  meanDiff[k] = fabs(mean[k]-mean1[k]);//Mean Diff

		  //	cout <<histName<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current ="<<mean1[k]<<" Mean_Diff = "<<fabs(mean[k]-mean1[k])<<endl;
		  myfile << setprecision(2) << fixed <<"-----"<< histName << "\t"<<"PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file
  		
		  if (mean1[k]!=0.0) {

		    if(fabs(meanDiff[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5 mV
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
  
      myfile<<"**********************************************************************************************"<<endl;
    
    }

    //******************************SHMS CAL PRSHWR*********************************************************

    {    //goes to end of cal prshwr


      TH1D *hist[2];//2 Histograms
      TH1D *hist1[2];

      TString polarity[2] = {"pos","neg"};//Two sides 
      Int_t numPMT[2] = {14, 14};//14 Pmts in each side
  
      for(int j = 0; j<2; ++j)//polarity
	{
	  TString histName = "pcal_prshwr_good_pped_vs_pmt_";
	  histName += polarity[j];//Reads Histogram from Golden Run

	  TH2D* hist = (TH2D*)f3->Get(histName);
	  TString histName1 = "pcal_prshwr_good_pped_vs_pmt_";
	  histName1 += polarity[j];//Reads Histogram from Current Run
     
	  TH2D *hist1  = (TH2D*)f4->Get(histName1);
	  TH1D *projHist;
	  TH1D *projHist1;
       
	  bool first_error = true;
	      
	  for(int k = 0; k< numPMT[j]; ++k)//PMT
	    {
	      projHist     =  hist->ProjectionY("pcal_proj", k+1, k+1);//Does Y-Projectin
	      projHist1    =  hist1->ProjectionY("pcal_proj1", k+1, k+1);

	      mean[k] = projHist->GetMean();//Mean Golden
	      mean1[k] = projHist1->GetMean();//Mean Current
	      meanDiff[k] = fabs(mean[k]-mean1[k]);//Mean Diff
  	   	
	      // cout <<histName<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current ="<<mean1[k]<<" Mean_Diff = "<<fabs(mean[k]-mean1[k])<<endl;
	      myfile << setprecision(2) << fixed << histName << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file


	      if (mean1[k]!=0.0) {

		if(fabs(meanDiff[k])>2.5)//setting 2.5 mV as a cutoff point
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
    
      myfile<<"**********************************************************************************************"<<endl;

    }
    //****************************SHMS CAL SHWR 1 HISTOGRAM ONLY*****************************************
 
    {  //goes to end of Cal shwr


      TH1D *hist[1];//1 histogram
      TH1D *hist1[1];
      TString pcal[1]= {"pcal_shwr"};
      Int_t numPMT[1] = {224};//224 pmts

      for(int i = 0; i < 1; ++i)//plane
	{

	  TString histName = "pcal_shwr";
	  histName += "_good_pped_vs_pmt";
	  TH2D* hist = (TH2D*)f3->Get(histName);//Read Histogram from Golden Run
	
	  TString histName1 = "pcal_shwr";
	  histName1 += "_good_pped_vs_pmt";
	  TH2D *hist1  = (TH2D*)f4->Get(histName1);//Reads Histogram from Current Run
		
	  TH1D *projHist;
	  TH1D *projHist1;
	  bool first_error = true;

	  for(int k = 0; k< numPMT[i]; ++k)//PMT
	    {
	      projHist     =  hist->ProjectionY("hcal_proj", k+1, k+1);
	      projHist1    =  hist1->ProjectionY("hcal_proj1", k+1, k+1);//Y-projection 

	      mean[k] = projHist->GetMean();
	      mean1[k] = projHist1->GetMean();
	      meanDiff[k] = fabs(mean[k]-mean1[k]);//Taking Absolute mean differnce
	      //cout << setprecision(2) << fixed<<mean[k]<<"  "<<mean1[k]<<" "<<fabs(meanDiff[k])<<endl;
	      // cout <<histName<< " " " PMT = "<< k+1 <<"""Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current = "<<mean1[k]<<" Mean_Diff = "<<fabs(mean[k]-mean1[k])<<endl;

	      myfile << setprecision(2) << fixed <<"----"<< histName << "\t\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file

	      if (mean1[k]!=0.0){

		if (fabs(meanDiff[k])>2.5 )//The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
		  {
		    if(first_error){
		      cout<<"__________________________________________________________________ ______________"<<endl;
		      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
		      cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
		      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		      cout<<"____________________________________________________________________________________"<<endl;
		      first_error=false;
		    }
	      
		    cout << setprecision(2) << fixed<<histName<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean[k] <<"  " 
			 <<"M ="<<"  "<< mean1[k] <<" " <<"MD"<<" "<< meanDiff[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
		    cout<<"___________________________________________________________________________________"<<endl;
		  }
	      } 
	    }
	}
   

      myfile <<"************************************************************************************************"<<endl;

    }
    //********************SHMS HGCER************************1 Histogram 4 PMTs**********************************
    {   //goes to end of Hgcer

      TH1D *hist[1];//one histogram
      TH1D *hist1[1];
      Int_t numPMT[1] = {4};//4 Pmts 

      for(int j = 0; j<1; ++j)//polarity
	{
	  TString histName = {"phgcer_good_pped_vs_pmt"};//Read the histogram from Golden Run
	  TH2D* hist = (TH2D*)f3->Get(histName);
	  
	  TString histName1 = ("phgcer_good_pped_vs_pmt");  //Get The Histogram from Current Run
	  TH2D *hist1  = (TH2D*)f4->Get(histName1);//
	  TH1D *projHist;
	  TH1D *projHist1;

	  bool first_error = true;
	      
	  for(int k = 0; k< numPMT[j]; ++k)//PMT
	    {
	      projHist     =  hist->ProjectionY("phgcer_proj", k+1, k+1);//Does Y-projection
	      projHist1    =  hist1->ProjectionY("phgcer_proj1", k+1, k+1);

	      mean[k] = projHist->GetMean();//Mean Golden
	      mean1[k] = projHist1->GetMean();//Mean Current
	      meanDiff[k] =fabs(mean[k]-mean1[k]);//Takes mean diff
	      //cout << setprecision(2) << fixed<<mean[k]<<"  "<<mean1[k]<<" "<<fabs(meanDiff[k])<<endl;
	      // cout <<histName<< " " " PMT = "<< k+1 <<"""Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current = "<<mean1[k]<<" Mean_Diff = "<<fabs(mean[k]-mean1[k])<<endl;


	      myfile << setprecision(2) << fixed <<"-------"<< histName << "\t\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file
	      if (mean1[k]!=0.0){
		if(fabs(meanDiff[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
	 
		  {
		    if(first_error){
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
		      cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
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
      myfile <<"************************************************************************************************"<<endl;
	
    }
    //*************************SHMS NGCER 1 Histogram, 4 PMTs******************************************************


    {  // goes to end of ngcer  

      TH1D *hist[1];//1 Histogram
      TH1D *hist1[1];
      Int_t numPMT[1] = {4};//4 Pmts

      for(int j = 0; j<1; ++j)//polarity
	{
	  TString histName = {"pngcer_good_pped_vs_pmt"};
	  TH2D* hist = (TH2D*)f3->Get(histName);//GET Hiistogram from Golden Run

	  
	  TString histName1 = ("pngcer_good_pped_vs_pmt");  //Get The Histogram from current Run
	  TH2D *hist1  = (TH2D*)f4->Get(histName1);
	  TH1D *projHist;
	  TH1D *projHist1;

	  bool first_error = true;
	      
	  for(int k = 0; k< numPMT[j]; ++k)//PMT
	    {
		  
	      projHist     =  hist->ProjectionY("phgcer_proj", k+1, k+1);
	      projHist1    =  hist1->ProjectionY("phgcer_proj1", k+1, k+1);

	      mean[k] = projHist->GetMean();//Mean Golden
	      mean1[k] = projHist1->GetMean();//Mean Current
	      meanDiff[k] = fabs(mean[k]-mean1[k]);//Mean Diff
	      //cout << setprecision(2) << fixed<<mean[k]<<"  "<<mean1[k]<<" "<<fabs(meanDiff[k])<<endl;
	      // cout <<histName<< " " " PMT = "<< k+1 <<"""Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current = "<<mean1[k]<<" Mean_Diff = "<<fabs(mean[k]-mean1[k])<<endl;

	      myfile << setprecision(2) << fixed <<"--------"<< histName << "\t\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file

	      if (mean1[k]!=0.0){

		if(fabs(meanDiff[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
	 
		  {
		    if(first_error){
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
		      cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
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
    
      myfile <<"************************************************************************************************"<<endl;
    }

    //******************************SHMS AEROGEL 7 PMTS EACH*******************************************************
    { //goes to end of ngcer

      TH1D *hist[2];//2 Histograms
      TH1D *hist1[2];

      TString polarity[2] = {"pos","neg"};//Two sides 
      Int_t numPMT[2] = {7, 7};//14 Pmts in each side
  
      for(int j = 0; j<2; ++j)//polarity
	{
	  TString histName = "paero_good_pped_vs_pmt_";
	  histName += polarity[j];//Reads Histogram from Golden Run

	  TH2D* hist = (TH2D*)f3->Get(histName);
	  TString histName1 = "paero_good_pped_vs_pmt_";
	  histName1 += polarity[j];//Reads Histogram from Current Run
     
	  TH2D *hist1  = (TH2D*)f4->Get(histName1);
	  TH1D *projHist;
	  TH1D *projHist1;
       
	  bool first_error = true;
	      
	  for(int k = 0; k< numPMT[j]; ++k)//PMT
	    {
	      projHist     =  hist->ProjectionY("paero_proj", k+1, k+1);//Does Y-Projectin
	      projHist1    =  hist1->ProjectionY("paero_proj1", k+1, k+1);

	      mean[k] = projHist->GetMean();//Mean Golden
	      mean1[k] = projHist1->GetMean();//Mean Current
	      meanDiff[k] = fabs(mean[k]-mean1[k]);//Mean Diff
  	   	
	      //  cout <<histName<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean[k]<<  " & " << "Mean_Current ="<<mean1[k]<<" Mean_Diff = "<<fabs(mean[k]-mean1[k])<<endl;
	      myfile << setprecision(2) << fixed <<"------"<< histName << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean[k]<<"\t\t"<< mean1[k]<<"\t\t"<< meanDiff[k]<<endl;//to store values in .txt file



	      if (mean1[k]!=0.0) {

		if(fabs(meanDiff[k])>2.5)//setting 2.5 mV as a cutoff point
		  {
		    if(first_error){
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		      cout<<"___________________________________________________________________________________"<<endl;
		      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
		      cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
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
    

      myfile <<"************************************************************************************************"<<endl;
    
    }
    myfile.close(); 
  }
}
  
