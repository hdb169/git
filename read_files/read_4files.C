#include "bin.h"
#include <sstream>
#include <string>
#include <fstream>

void read_4file()
{






  //std::ifstream infile("singles.txt"); //reads first txtfile
  // std::ifstream infile("txtfile/ch12_singles_D2_eff.txt"); //reads first txtfile
  std::ifstream infile5("x35_z40.txt"); //reads first txtfile
  std::string line5;// read line by line
  vector <double> z5; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
   vector <double> y5;
  vector <double> e5;  

  while (std::getline(infile5, line5))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line5);// to read the whole strings in a line
      double a5, b5, c5;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a5>> b5>> c5  )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      z5.push_back(a5);//now run is stored in a
      y5.push_back(b5);//now run is stored in a
      e5.push_back(c5);//eff = d
      

    }









  /////////////////////////////////first file done



  //std::ifstream infile("singles.txt"); //reads first txtfile
  // std::ifstream infile("txtfile/ch12_singles_D2_eff.txt"); //reads first txtfile
  std::ifstream infile1("x35_z50.txt"); //reads first txtfile
  std::string line1;// read line by line
  vector <double> z1; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
   vector <double> y1;
  vector <double> e1;  

  while (std::getline(infile1, line1))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line1);// to read the whole strings in a line
      double a1, b1, c1;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a1>> b1>> c1  )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      z1.push_back(a1);//now run is stored in a
      y1.push_back(b1);//now run is stored in a
      e1.push_back(c1);//eff = d
      

    }
  //////////////////////////2nd file////////////
    
  std::ifstream infile2("x35_z60.txt"); //reads first txtfile

  std::string line2;// read line by line
  vector <double> z2; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> y2;
  vector <double> e2;  

  while (std::getline(infile2, line2))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line2);// to read the whole strings in a line
      double a2, b2, c2;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a2>> b2>> c2  )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      z2.push_back(a2);//now run is stored in a
      y2.push_back(b2);//now run is stored in a
      e2.push_back(c2);//eff = d
      

    }


  //////////////////////////////////3rdfile/////////////////////

std::ifstream infile3("x35_z70.txt"); //reads first txtfile

  std::string line3;// read line by line
  vector <double> z3; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> y3;
  vector <double> e3;  

  while (std::getline(infile3, line3))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line3);// to read the whole strings in a line
      double a3, b3, c3;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a3>> b3>> c3  )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      z3.push_back(a3);//now run is stored in a
      y3.push_back(b3);//now run is stored in a
      e3.push_back(c3);//eff = d
      

    }


  ////////////////////////done 3rd file////////////////






















  ///////////////////////done 4th file/////////////////
  TCanvas *c1= new TCanvas("c1", "c1",1200,800);

  c1->cd();gPad->SetGridx();gPad->SetGridy();

auto mg = new TMultiGraph();

  auto gr1 = new TGraphErrors(z1.size(), &z1[0], &y1[0],  0, &e1[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  //gr1->Draw("ap");
  gr1->SetMarkerStyle(22);
  gr1->SetMarkerSize(1.4);
  gr1->GetXaxis()->SetTitle("SHMS 3/4 Rate (kHz)");
  gr1->GetYaxis()->SetTitle("Tracking Efficiency");
  gr1->SetName("gr1");
   gr1->SetTitle("x = 0.4, z = 0.5");

  // gr1->SetTitle("Tracking efficiency vs SHMS 3/4 Rate");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  //gr1->GetYaxis()->SetRangeUser(0.85,1.0);
  gr1->GetXaxis()->SetAxisColor(17);
  gr1->GetYaxis()->SetAxisColor(17);
  gr1->SetMarkerColor(kBlue);
  mg->Add(gr1);
  // c1->SaveAs("pdf/6459_64.pdf");

  /////////////////////////////////////draw second g=file//////////////////  


  auto gr2 = new TGraphErrors(z2.size(), &z2[0], &y2[0],  0, &e2[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  //gr1->Draw("ap");

  //gr2->Draw("AP same");
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerSize(1.3);
  gr2->SetMarkerColor(kRed);
  gr2->GetXaxis()->SetTitle("SHMS 3/4 Rate (kHz)");
  gr2->GetYaxis()->SetTitle("Tracking Efficiency");
  gr2->SaveAs("pdf/singles_elclean.pdf");
  // gr2->GetYaxis()->SetRangeUser(0.98,1);
  // gr2->SetName("gr2");
  gr2->SetTitle("Tracking efficiency vs SHMS 3/4 Rate");
  gr2->GetXaxis()->CenterTitle();
  gr2->GetYaxis()->CenterTitle();
  //gr2->GetYaxis()->SetRangeUser(0.85,1.0);
  gr2->GetXaxis()->SetAxisColor(17);
  gr2->GetYaxis()->SetAxisColor(17);
  gr2->SetName("gr2");
   gr2->SetTitle("x = 0.4, z = 0.6");

   gr2->SetTitle("");
   /////////////////////////////////draw 3rd file//////////////

  auto gr3 = new TGraphErrors(z3.size(), &z3[0], &y3[0],  0, &e3[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  //gr1->Draw("ap");

  //gr3->Draw("AP same");
  gr3->SetMarkerStyle(34);
  gr3->SetMarkerSize(1.3);
  gr3->SetMarkerColor(1);
  gr3->GetXaxis()->SetTitle("SHMS 3/4 Rate (kHz)");
  gr3->GetYaxis()->SetTitle("Tracking Efficiency");
  gr3->SaveAs("pdf/singles_elclean.pdf");
  // gr3->GetYaxis()->SetRangeUser(0.98,1);
  // gr3->SetName("gr3");
  gr3->SetTitle("Tracking efficiency vs SHMS 3/4 Rate");
  gr3->GetXaxis()->CenterTitle();
  gr3->GetYaxis()->CenterTitle();
  //gr3->GetYaxis()->SetRangeUser(0.85,1.0);
  gr3->GetXaxis()->SetAxisColor(17);
  gr3->GetYaxis()->SetAxisColor(17);
  gr3->SetName("gr3");
   gr3->SetTitle("x = 0.4, z = 0.7");

   gr3->SetTitle("");
 
   ////////////////////add gr5


  auto gr5 = new TGraphErrors(z3.size(), &z3[0], &y3[0],  0, &e3[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  //gr1->Draw("ap");

  //gr5->Draw("AP same");
  gr5->SetMarkerStyle(34);
  gr5->SetMarkerSize(1.3);
  gr5->SetMarkerColor(1);
  gr5->GetXaxis()->SetTitle("SHMS 3/4 Rate (kHz)");
  gr5->GetYaxis()->SetTitle("Tracking Efficiency");
  gr5->SaveAs("pdf/singles_elclean.pdf");
  // gr5->GetYaxis()->SetRangeUser(0.98,1);
  // gr5->SetName("gr5");
  gr5->SetTitle("Tracking efficiency vs SHMS 3/4 Rate");
  gr5->GetXaxis()->CenterTitle();
  gr5->GetYaxis()->CenterTitle();
  //gr5->GetYaxis()->SetRangeUser(0.85,1.0);
  gr5->GetXaxis()->SetAxisColor(17);
  gr5->GetYaxis()->SetAxisColor(17);
  gr5->SetName("gr5");
   gr5->SetTitle("x = 0.4, z = 0.7");

   gr5->SetTitle("");







   /////////////Draw fit function/////////////////

 ////////////////////////////plotted the separate yield ratio for pi+ and pi-/////////////////
  cout<<binz<< "  "<< loz<<" "<<hiz<<endl;

  //////////////////////////////////Ratio of Pi+/Pi Yield for different z settings////////////
  double z[100];
  double Rd;
  double R_D[100];
  double ratio[100];
  double rd_ratio[100];


 


  for (int i = 0; i < 100; i++)//taking all int numbers from 0 t0 1
    {
      z[i] = i/100.0;//made each number 0.1, 0.2, 0.3, ..
    
      R_D[i] = pow((1.0-z[i]),0.083583)/pow((1.0+z[i]),1.9838);//Rd

      ratio[i]= (R_D[i]+4)/ (4*R_D[i]+1);//pi+/pi-
      // cout << z[i]<< endl;

      rd_ratio[i] = (4 - ratio [i]) / (ratio[i] - 1);//Rd_measured (4-R)/(R-1)


    }

  TGraph *gr10 = new TGraph(100, z, ratio);//to plot Yield ratio
  gr10->SetLineWidth(2);
  gr10->SetLineColor(kMagenta); 
  gr10->SetName("gr10");
  gr10->SetTitle("Model Based on HERMES Data");

  gr10->Draw("same");

  ////////////////////////////////Multigraph//////////////////////
  mg->Add(gr2);
  mg->Add(gr3);
   mg->Add(gr5);
  mg->Draw("ap");
  mg->GetXaxis()->SetAxisColor(17);
  mg->GetYaxis()->SetAxisColor(17);
  mg->GetXaxis()->SetTitle("z_hadron");
  mg->GetYaxis()->SetTitle("Yield Ratio of Pi+/Pi)");
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->CenterTitle();
  mg->SetTitle("Yield Ratio: Pi+/Pi-, Q2 = 4GeV2, x = 0.4, z = 0.5, 0.6, 0.7");
  mg->GetYaxis()->SetRangeUser(0,3);
  gr10->Draw("same");
// c1->Update();
  // c1->BuildLegend();
  c1->Update();

  c1->SaveAs("pdf/6429_6459_64.pdf");


}
