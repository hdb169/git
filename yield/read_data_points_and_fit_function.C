

#include <sstream>
#include <string>
#include <fstream>

void readfile()
{
  //std::ifstream infile("singles.txt"); //reads first txtfile
  std::ifstream infile("txtfile/x35_weight_70_60_50_40.txt"); //reads first txtfile

  std::string line;// read line by line
  vector <int> run; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> z_hadron;
  vector <double> weight;
  vector <double> error;
  

  while (std::getline(infile, line))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line);// to read the whole strings in a line
      double a, b, c, d;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a >> b >> c >> d )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run.push_back(a);//now run is stored in a
      z_hadron.push_back(b);//did is stored in b
      weight.push_back(c);//should is stored as c
      error.push_back(d);//eff = d
      
    }


 
  //=========================================================//
  TCanvas *c1 = new TCanvas("c1","c1",1600,1200);
  c1->cd();
  for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
    {
      cout <<  run[i]<<endl;//you have to cout each elements , so need i
      cout<<  weight[i]<<endl;
    }
  
  auto gr = new TGraphErrors(run.size(), &z_hadron[0], &weight[0],  0, &error[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  gr->SetMarkerStyle(21);
  gr->GetXaxis()->SetTitle("z_hadron");
  gr->GetYaxis()->SetTitle("Yield ratio Pi+/Pi-");
  gr->SaveAs("pdf/singles_elreal.pdf");
  // gr->GetXaxis()->SetRangeUser(0,1);
  gr->SetTitle("Yield Ratio pi+/Pi- for x = 0.35");
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  
  gr->GetXaxis()->SetLimits(0.2, 0.8);
  gr->GetYaxis()->SetRangeUser(0, 4);
  gr->Draw("ap");
  // gr->GetXaxis()->SetRangeUser(0,1);

  //////////////////////////////////////////////////////////////////PDF FIT///////////////////////////

  
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
  // TCanvas *c2=new TCanvas("c2","c2",1600,1200);
  //c2->cd();
 TGraph *gr1 = new TGraph(100, z, ratio);//to plot Yield ratio
  gr1->SetLineWidth(2);
  gr1->SetLineColor(kRed); 
  gr1->Draw("same");
  
  c1->SaveAs("pdf/fourpints.pdf");






  //////////////////////////////////////////////////////////////////PDF FIT///////////////////////////


}
