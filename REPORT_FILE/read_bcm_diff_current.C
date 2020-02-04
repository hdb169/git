#include <sstream>
#include <string>
#include <fstream>
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TPaveLabel.h"
void read_current_diff()
{
  std::ifstream infile("txtfile/fall_diff_final.txt"); //reads first txtfile
    
  std::string line;// read line by line
  vector <double> run; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> bcm121;//(bcm1-bcm2)/bcm1
  vector <double> bcmaba;//(a-b)/a
  vector <double> bcm1a1;

   // vector <double>runNum;
    
  while (std::getline(infile, line))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line);// to read the whole strings in a line
      double a, b, c, d;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a >> b >> c >> d)) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run.push_back(a);//now run is stored in a
      bcm121.push_back(b);//did is stored in b
      bcmaba.push_back(c);//should is stored as c
      bcm1a1.push_back(d);//eff = d
     
    }


  

  for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
    {


      // cout<<"hello"<<endl;
      // cout <<" run : "<<run[i]<<"\t"<<" bcm121 : " <<bcm121[i]<< "  bcmaba : "<<bcmaba[i]<< "    bcm1a1 : " <<bcm1a1  <<  endl;//you have to cout each elements , so need i
      cout <<" run : "<<run[i]<<"\t"<<" bcm121 : " << bcm121[i]<< "  bcmaba : " <<bcmaba[i]<< "    bcm1a1 : " << bcm1a1[i]  <<  endl;//you have to cout each elements , so need i


    }
  
  
   auto c3 = new TCanvas("c3","c3",1600, 1200);
   c3->cd();gPad->SetGridy();
   TMultiGraph *mg1 = new TMultiGraph("mg1", " fractional change in BCM current vs Run Num Nov 7-28, 2018");
   //TMultiGraph *mg1 = new TMultiGraph("mg1", " fractional change in BCM current vs Run Num March 7-17, 2019");

  auto gr1 = new TGraph(run.size(), &run[0], &bcm121[0]);

  gr1->SetName("gr1");
  gr1->SetMarkerStyle(21);
  gr1->SetTitle("(BCM1-BCM2)/BCM1");
  gr1->SetMarkerColor(kRed);
  auto gr2 = new TGraph(run.size(), &run[0],&bcmaba[0]);
  gr2->SetName("gr2");
  gr2->SetMarkerStyle(22);
  gr2->SetTitle("(BCM4A-BCM4B)/BCM4A");
  gr2->SetMarkerColor(kBlue);
  auto gr3 = new TGraph(run.size(), &run[0],&bcm1a1[0]);
  gr3->SetName("gr3");
  gr3->SetTitle("(BCM1-BCM4A)/BCM1");
  gr3->SetMarkerStyle(23);
  gr3->SetMarkerColor(1);



  mg1->Add(gr1);
  mg1->Add(gr2);
  mg1->Add(gr3);
  mg1->Draw("AP");

  //auto legend = new TLegend(0.1,0.7,0.48,0.9);


 c3->BuildLegend();

 mg1->GetXaxis()->SetTitle("Run Num Fall");
 mg1->GetYaxis()->SetTitle("fraction change in Current ");
 mg1->SetTitle("Comparision of fractional change ofcurrent between BCMs");
 mg1->GetXaxis()->CenterTitle();
 mg1->GetYaxis()->CenterTitle();
  
 c3->SaveAs("pdf/shms_bcm_fall.pdf");
}
