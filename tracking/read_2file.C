

#include <sstream>
#include <string>
#include <fstream>

void read_2file()
{
  //std::ifstream infile("singles.txt"); //reads first txtfile
  std::ifstream infile("txtfile/springpim_D2_eff.txt"); //reads first txtfile

  std::string line;// read line by line
  vector <int> run; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  //vector <double> rate;
  vector <double> did;
  vector <double> should;  
  vector <double> did_div_should;
  vector <double> did_div_should_err;

  while (std::getline(infile, line))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line);// to read the whole strings in a line
      double a, c, d, e, f;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a  >> c >> d >> e >> f )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run.push_back(a);//now run is stored in a
      did.push_back(c);//should is stored as c
      should.push_back(d);//eff = d
      did_div_should.push_back(e);//eff err = e
      did_div_should_err.push_back(f);//rate = f
      

    }

  
  //The following portion of code is for reading the second txt file, for now I have only one txt file.

    std::ifstream infile1("txtfile/shms_rate.txt");//reads the second txt file
    
    std::string line1;//read all lines, there are just two columns
    vector <int> run1;//first column
    vector <double> rate;//second column
    
     while (std::getline(infile1, line1))
    {
    std::istringstream iss(line1);//pass each column of line1 tp a1, b1
    double a1, b1;   ;
        
    if (!(iss >> a1>> b1)) 
    {
            
    break; 
            
    } // error
      run1.push_back(a1);//first column
    rate.push_back(b1);//second column
    }
  
  //=========================================================//
    
  
  // for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
  //   {
  //     cout <<  run[i]<<endl;//you have to cout each elements , so need i
  //     cout<<  did_div_should[i]<<endl;
  //   }
  TCanvas *c1= new TCanvas("c1", "changing nhit from 25 to 15",1200,800);
  auto gr = new TGraphErrors(run.size(), &rate[0], &did_div_should[0],  0, &did_div_should_err[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  gr->Draw("ap");
  gr->SetMarkerStyle(kFullTriangleUp);
  gr->GetXaxis()->SetTitle("SHMS 3/4 Rate (kHz)");
  gr->GetYaxis()->SetTitle("Traking Efficiency  ");
  gr->SaveAs("pdf/tracking_eff_mixruns.pdf");
  //r->GetYaxis()->SetRangeUser(0.98,1);
  gr->SetTitle("Traking Efficiency vs Shms 3/4 Rate : Pi- spring : D2 target ");
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  gr->GetYaxis()->SetRangeUser(0.8, 1);
  c1->SaveAs("pdf/nhit_25_to_15_spring_pim.pdf");
 // auto gr1 = new TGraphErrors(run.size(), &rate[0], &elclean_div_q[0],  0, &elclean_div_q_err[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
 //  gr1->Draw("ap");
 //  gr1->SetMarkerStyle(kFullTriangleUp);
 //  gr1->GetXaxis()->SetTitle("SHMS 3/4 Rate (kHz)");
 //  gr1->GetYaxis()->SetTitle("Elclean_divide_Q (per mC)");
 //  gr1->SaveAs("pdf/singles_elclean.pdf");
 //  //r->GetYaxis()->SetRangeUser(0.98,1);
 //  gr1->SetTitle("Elclean divide Q vs Rate Singles Runs");
 //  gr1->GetXaxis()->CenterTitle();
 //  gr1->GetYaxis()->CenterTitle();
 //  //gr1->GetYaxis()->SetRangeUser(0.85,1.0);
  
 
    
}
