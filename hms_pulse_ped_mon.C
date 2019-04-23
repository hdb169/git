/This macro reads the HMS histograms from Rootfile and reads the values of pedestals in each PMTs for, trigger, Hodoscopes, calorimeter, and Cerenkov.

const Int_t goldRunNum1   = 1536;           // For Trig only
const Int_t goldRunNum    = 1782;  //for detectors
ofstream myfile;
//myfile.open("outHMS.txt");//To store ped diff


void trigger(Int_t, Int_t);
void hodo(Int_t , Int_t); 
void cal(Int_t, Int_t);
void calo(Int_t, Int_t);
void cer(Int_t, Int_t);



void hms_ped(Int_t runNumber, Int_t eventNumber)

{

  const Int_t run           = runNumber;
  const Int_t nevents       = eventNumber;
   
  trigger(runNumber, eventNumber);
  hodo(runNumber, eventNumber);
  cal(runNumber, eventNumber);
  calo(runNumber, eventNumber);
  cer(runNumber, eventNumber);
}

void trigger(Int_t runNumber, Int_t eventNumber)

{ 
  const Int_t run           = runNumber;
  const Int_t nevents       = eventNumber; 
  const Int_t numHistos     = 3;   
 
  //ofstream myfile;
   myfile.open("outHMS.txt");//To store ped diff
   
 
  TFile *f1 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_50000.root",goldRunNum1));//Golden_Rootfile for trigger only
    
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
  // Int_t plane=1;
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
 
  TFile *f2 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_%d.root",run,nevents));      // no golden


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
      cout << setprecision(2) << fixed <<histos[i]<<""<<"\t"<< bar[i]<<"\t"<<variables[i]<<"\t"<<"\t"<<meanG[i]<<"\t\t"<<mean[i]<<"\t\t"<<meanDiff[i]<<endl;

      myfile<<histos[i]<<"\t"<<"\t"<<meanG[i]<<"\t\t"<<mean[i]<<"\t\t"<<meanDiff[i]<<endl;//to stores values in .txt file


    }
  
  for (int i = 0; i<numHistos ; i++)
    {
      if(fabs(meanDiff[i])>2.5) // //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
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
          cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
          cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
          cout<<"___________________________________________________________________________________"<<endl;
          cout << setprecision(2) << fixed <<"chan"<<" "<< channel[i] << " " <<"bar"<<" "<< bar[i] 
               << "\t" <<  variables[i] << "\t" <<"MG"<<"  "<<meanG[i] <<"  " 
               <<"M"<<"  "<< mean[i] <<" " <<"MD"<<" "<< meanDiff[i] << endl;//MG=mean golden,M = mean current, MD = mean diff
          cout<<"_____________________________________________________________________"<<endl;
       
        }        

    }
 
  myfile <<"___________________________________________________________________________"<<endl;
   
}//end trigger
  
//----------------------------HMS DETECTORS PPED STARTS HERE--------------------------


void hodo(Int_t runNumber, Int_t eventNumber)
{
  const Int_t run           = runNumber;
  const Int_t nevents       = eventNumber;
  TFile *f3 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_50000.root",goldRunNum));//Golden_Rootfile for detectors only
  TFile *f4 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_%d.root",run,nevents));//Current Rootfile

  myfile <<"________________________________________________________________________________________"<<endl;
  myfile <<"HMS PEDESTAL GOLDEN  RUN NUMBER    =" "    "<<goldRunNum<<endl;
  myfile <<"HMS PEDESTAL CURRENT  RUN NUMBER   =" "    "<<run<<endl;
  myfile <<"________________________________________________________________________________________"<<endl;
  myfile <<"hms_good_pped"<< "\t\t\t"<<"PMT_Num"<<"\t\t"<<"Mean_Gold"<<"    "<<"Mean_Curr"<<" \t   "<<"Mean_Diff"<<endl;
  myfile <<"________________________________________________________________________________________"<<endl;
 


  //-------------------------------------FOR HMS HODOSCOPE PMTS IN 1X = 16, 1Y =10, 2X = 16, 2Y = 10------------------

  Double_t mean1[104];
  Double_t mean11[104];
  Double_t meanDiff1[104];
  
  TString plane1[4]= {"1x","1y","2x","2y"};//4 planes
  TString polarity1[2] = {"pos","neg"};//Two sides
  Int_t numPMT1[4] = {16, 10, 16, 10};//PMTs in each side

  for(int i = 0; i < 4; ++i)//plane
    {
      for(int j = 0; j<2; ++j)//polarity
        {
          TString hist1Name = "hhodo_";
          hist1Name += plane1[i];
          hist1Name += "_good_pped_vs_pmt_";
          hist1Name += polarity1[j];  //Reading the Histogram from Golden Run
          TH2D* hist1_2D = (TH2D*)f3->Get(hist1Name);
              
          TString hist1Name1 = "hhodo_";
          hist1Name1 += plane1[i];
          hist1Name1 += "_good_pped_vs_pmt_";
          hist1Name1 += polarity1[j];//Reading the histogram from current Run
          TH2D *hist11_2D  = (TH2D*)f4->Get(hist1Name1);
          TH1D *projHist1;//For Golden Run
          TH1D *projHist11;//For Current Run

          bool first_error = true;
              
          for(int k = 0; k< numPMT1[i]; ++k)//PMT
            {
                  
              projHist1     =  hist1_2D->ProjectionY("hodo_proj", k+1, k+1);
              projHist11    =  hist11_2D->ProjectionY("hodo_proj1", k+1, k+1);

              mean1[k] = projHist1->GetMean();//Mean Golden
              mean11[k] = projHist11->GetMean();//Mean Current
              meanDiff1[k] = fabs(mean1[k]-mean11[k]);//Mean Diff

              // cout <<hist1Name<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean1[k]<<  " & " << "Mean_Current ="<<mean11[k]<<" Mean1_Diff = "<<fabs(mean1[k]-mean11[k])<<endl;
               cout << setprecision(2) << fixed <<hist1Name<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean1[k]<<  " & " << "Mean_Current ="<<mean11[k]<<" Mean1_Diff = "<< meanDiff1[k]<<endl;

              myfile << setprecision(2) << fixed << hist1Name << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean1[k]<<"\t\t"<< mean11[k]<<"\t\t"<< meanDiff1[k]<<endl;//to store values in .txt file
              if (mean11[k]!=0.0) {


                if(fabs(meanDiff1[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
                  {
                    if(first_error){
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
                      cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
                      cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
                      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      first_error=false;
                    }
                    cout << setprecision(2) << fixed<<hist1Name<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean1[k] <<"  " 
                         <<"M ="<<"  "<< mean11[k] <<" " <<"MD"<<" "<< meanDiff1[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
                    cout<<"___________________________________________________________________________________"<<endl;
                  }
              }
            }
        }
    }
       
  myfile<<"******************************************************************************************"<<endl;
 
}//end hodo     

   //************************HMS CALORIMETER hA and hB***************SHWR*****************************************// 
void cal(Int_t runNumber, Int_t eventNumber)

{
  const Int_t run           = runNumber;
  const Int_t nevents       = eventNumber;
  TFile *f3 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_50000.root",goldRunNum));//Golden_Rootfile for detectors only
  TFile *f4 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_%d.root",run,nevents));//Current Rootfile
  Double_t mean2[52];
  Double_t mean22[52];
  Double_t meanDiff2[52];//Randomly taken 1000
 
  TString hcal[2]= {"hA","hB"};
  TString polarity2[2] = {"pos","neg"};
  Int_t numberofPMTs[2] = {13, 13};
 
  for(int i = 0; i < 2; ++i)//plane
    {
      for(int j = 0; j<2; ++j)//polarity
        {
          TString hist2Name = "hcal_";
          hist2Name += hcal[i];
          hist2Name += "_good_pped_vs_pmt_";
          hist2Name += polarity2[j];                     //Get Histogram From Golden
          TH2D* hist2_2D = (TH2D*)f3->Get(hist2Name);
         
          TString hist2Name1 = "hcal_";
          hist2Name1 += hcal[i];
          hist2Name1 += "_good_pped_vs_pmt_";
          hist2Name1 += polarity2[j];                 //Get Histogram from Current
          TH2D *hist22_2D  = (TH2D*)f4->Get(hist2Name1);

          TH1D *projHist2;
          TH1D *projHist22;
          bool first_error = true;
         
          for(int k = 0; k< numberofPMTs[i]; ++k)//PMT
            {
              projHist2     =  hist2_2D->ProjectionY("hcal_proj", k+1, k+1); //Y-Projection
              projHist22    =  hist22_2D->ProjectionY("hcal_proj1", k+1, k+1);//Y-Projection
             
              mean2[k] = projHist2->GetMean();//Getting Mean from Golden Run
              mean22[k] = projHist22->GetMean();//Getting Mean from Current Run
              meanDiff2[k] = fabs(mean2[k]-mean22[k]);//Mean Diff
             
               cout << setprecision(2) << fixed  <<hist2Name<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean2[k]<<  " & " << "Mean_Current ="<<mean22[k]<<" Mean_Diff = "<<meanDiff2[k]<<endl;
             
              myfile<<hist2Name << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean2[k]<<"\t\t"<< mean22[k]<<"\t\t"<< meanDiff2[k]<<endl;//to store values in .txt file
              if (mean22[k]!=0.0) {
               
                if(fabs(meanDiff2[k])>2.5) 
                  {
                    if(first_error){
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
                      cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
                      cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
                      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      first_error=false;
                    }
                    cout << setprecision(2) << fixed<<hist2Name<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean2[k] <<"  " 
                         <<"M ="<<"  "<< mean22[k] <<" " <<"MD"<<" "<< meanDiff2[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
                    cout<<"___________________________________________________________________________________"<<endl;
                  }
              }
            }
        }
    }
 
  myfile<<"******************************************************************************************"<<endl;  

}//end calhA
      
//***************HMS CAL hC and hD ************PRESHWR PLANES**************************************
void calo(Int_t runNumber, Int_t eventNumber)

{
  const Int_t run           = runNumber;
  const Int_t nevents       = eventNumber;
  TFile *f3 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_50000.root",goldRunNum));//Golden_Rootfile for detectors only
  TFile *f4 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_%d.root",run,nevents));//Current Rootfile
     
  Double_t mean3[26];
  Double_t mean33[26];
  Double_t meanDiff3[26];//Randomly 
  //  Double_t numbPMT3[1000];
 

  // TH1D *hist3[2];//ONLY TWO HISTOGRAMS
  // TH1D *hist33[2];
  TString hcal1[2]= {"hC","hD"};
  TString polarity3[1] = {"pos"};
  Int_t numPMT3[2] = {13, 13};
  for(int i = 0; i < 2; ++i)//plane
    {
      for(int j = 0; j<1; ++j)//polarity
        {
          TString hist3Name = "hcal_";
          hist3Name += hcal1[i];
          hist3Name += "_good_pped_vs_pmt_";
          hist3Name += polarity3[j];          //GETTING HOSTOGRAM FROM GOLDEN RUN
          TH2D* hist3_2D = (TH2D*)f3->Get(hist3Name);
         
          TString hist3Name1 = "hcal_";
          hist3Name1 += hcal1[i];
          hist3Name1 += "_good_pped_vs_pmt_";
          hist3Name1 += polarity3[j];          //Getting Histogram from Current Run
          TH2D *hist33_2D  = (TH2D*)f4->Get(hist3Name1);
          TH1D *projHist3;
          TH1D *projHist33;

          bool first_error = true;
   
          for(int k = 0; k< numPMT3[i]; ++k)//PMT
            {
              projHist3     =  hist3_2D->ProjectionY("hcal1_proj", k+1, k+1);  //Y projection of golden Run
              projHist33    =  hist33_2D->ProjectionY("hcal1_proj1", k+1, k+1);  //Y- Projection of current Run

              mean3[k] = projHist3->GetMean();//Mean Golden
              mean33[k] = projHist33->GetMean();//Mean Current
              meanDiff3[k] = fabs(mean3[k]-mean33[k]);//Mean Diff

   cout << setprecision(2) << fixed << hist3Name<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean3[k]<<  " & " << "Mean_Current ="<<mean33[k]<<" Mean_Diff = "<<meanDiff3[k]<<endl;
                
              myfile<<hist3Name << "\t"<< "PMT ="<<"\t"<<k+1<<"\t"<<mean3[k]<<"\t\t"<< mean33[k]<<"\t\t"<< meanDiff3[k]<<endl;//to store values in .txt file
              if (mean33[k]!=0.0) {

                if(fabs(meanDiff3[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
                  {
                    if(first_error){
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
                      cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
                      cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
                      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                      cout<<"___________________________________________________________________________________"<<endl;
                      first_error=false;
                    }
                    cout << setprecision(2) << fixed<<hist3Name<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean3[k] <<"  " 
                         <<"M ="<<"  "<< mean33[k] <<" " <<"MD"<<" "<< meanDiff3[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
                    cout<<"___________________________________________________________________________________"<<endl;

       
                  }
    
              }
            }
            
        }
    }
    
  
  myfile<<"******************************************************************************************"<<endl;
 
} //hc, hd  cal
//************************HMS CERENKOV**************************************************************//

void cer(Int_t runNumber, Int_t eventNumber)

{
const Int_t run           = runNumber;
const Int_t nevents       = eventNumber;
TFile *f3 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_50000.root",goldRunNum));//Golden_Rootfile for detectors only
TFile *f4 = new TFile(Form("../../ROOTfiles/hms_replay_production_%d_%d.root",run,nevents));//Current Rootfile
     

Double_t mean4[2];
Double_t mean44[2];
Double_t meanDiff4[2];
  
TString hcer[1]= {"hcer"};
Int_t numPMT4[1] = {2}; //One histogram, two pmts, no positive and negative sides
 
  
for(int i = 0; i < 1; ++i)//plane
  {

    TString hist4Name = "hcer";
    hist4Name += "_good_pped_vs_pmt";// reads Hisogram from Golden Run
    TH2D* hist4_2D = (TH2D*)f3->Get(hist4Name);
        
    TString hist4Name1 = "hcer";
    hist4Name1 += "_good_pped_vs_pmt";//Reads Histogram from Current Run
    TH2D *hist44_2D  = (TH2D*)f4->Get(hist4Name1);

    TH1D *projHist4;
    TH1D *projHist44;
    bool first_error = true;
          
    for(int k = 0; k< numPMT4[i]; ++k)//PMT
      {
        projHist4     =  hist4_2D->ProjectionY("hcal_proj", k+1, k+1);//Y-Projection
        projHist44    =  hist44_2D->ProjectionY("hcal_proj1", k+1, k+1);//Y-projection

        mean4[k] = projHist4->GetMean();//Mean Golden
        mean44[k] = projHist44->GetMean();//Mean current
        meanDiff4[k] = fabs(mean4[k]-mean44[k]);//Mean Diff

    cout << setprecision(2) << fixed  <<hist4Name<< " PMT = "<< k+1 <<"  Mean_Golden = "<<mean4[k]<<  " & " << "Mean_Current ="<<mean44[k]<<" Mean_Diff = "<<meanDiff4[k]<<endl;

        myfile<<"------"<< hist4Name  << "\t"<< "PMT  ="<<"\t"<<k+1<<"\t"<<mean4[k]<<"\t\t"<< mean44[k]<<"\t\t"<< meanDiff4[k]<<endl;//to store values in .txt file
        if (mean44[k]!=0.0) {

          if(fabs(meanDiff4[k])>2.5) //The following message will appear in terminal if Pedestal mean differnce is greater than 2.5
            {
              if(first_error){
                cout<<"___________________________________________________________________________________"<<endl;
                cout<<"Golden Run = "<<goldRunNum<<"     "<<"AND""     "<<"This Run = "<<run<<endl;
                cout<<"___________________________________________________________________________________"<<endl;
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                cout<<"___________________________________________________________________________________"<<endl;
                cout<<" HERE THE MEAN DIFFERNCE OF PULSE PEDUSTAL BETWEEN GOLDEN RUN (MG) AND"<<endl;
                cout<<"CURRENT RUN (M) IS GREATER THAN 2.5 mV FOR THE FOLLOWING HISTOGRAM(S)"<<endl;
                cout<<"PLEASE CONSULT WITH BRAD SAWATZKY (brads@jlab.org) or ERIC POOSER(pooser@jlab.org)"<<endl;
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Attention Needed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                cout<<"___________________________________________________________________________________"<<endl;
                first_error=false;
              }
              cout << setprecision(2) << fixed<<hist4Name<<"   "<<"PMT :"<<k+1<<"   "<<"MG ="<<"  "<<mean4[k] <<"  " 
                   <<"M ="<<"  "<< mean44[k] <<" " <<"MD"<<" "<< meanDiff4[k] << endl;//MG=mean golden,M = mean current, MD = mean diff
              cout<<"___________________________________________________________________________________"<<endl;
            }
             
        }
      }
  }
    
myfile <<"******************************************************************************************"<<endl;

 myfile.close();  
}//cer
