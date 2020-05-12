//this reads two files, one has run , livetime, error and the othere has 3/4 rate
//root -l read_livetime.C


#include <sstream>
#include <string>
#include <fstream>

void read_livetime()
{
  std::ifstream infile("live_time.txt"); //reads first txtfile

  std::string line;// read line by line
  vector <int> run; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> cur_nocut;
  vector <double> cur_cut;
  vector <double> factor;//f = nocut/cut
  vector <double> all_edtm;
  vector <double> acc_edtm;
  vector <double> uncorr_ratio;// rmeas = acc/all
  vector <double> livetime;// (rmeas - (1.-f))/f
  vector <double> err;
  vector <double> ptrig1rate;

 
  while (std::getline(infile, line))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line);// to read the whole strings in a line
      double a, b, c, d, e, f, g, h, i, j;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run.push_back(a);
      cur_nocut.push_back(b);
      cur_cut.push_back(c);
      factor.push_back(d);//eff = d
      all_edtm.push_back(e);//eff err = e
      acc_edtm.push_back(f);
      uncorr_ratio.push_back(g);
      livetime.push_back(h);
      err.push_back(i);
      ptrig1rate.push_back(j);

    }
  cout<< "I am good"<<endl;
  
  for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
    {
       cout<< run[i] <<endl;
        cout << livetime[i]<<endl;//you have to cout each elements , so need i
       cout<<  err[i]<<endl;
      cout<<  ptrig1rate[i]<<endl;
    }
   cout<< "I am good"<<endl;
   //====================================

 std::ifstream infile2("rate.txt"); //reads first txtfile

  std::string line2;// read line by line
  vector <double> run2; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> rate2;
 

  while (std::getline(infile2, line2))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line2);// to read the whole strings in a line
      double a2, b2;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a2>> b2 )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run2.push_back(a2);//now run is stored in a
      rate2.push_back(b2);//now run is stored in a
     

    }

 for (int i =0; i< run2.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
    {
       cout<< run2[i] <<endl;
        cout << rate2[i]<<endl;//you have to cout each elements , so need i
      
    }
   cout<< "I am good"<<endl;





   
   
  auto gr = new TGraphErrors(run.size(), &rate2[0], &livetime[0],  0, &err[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  gr->Draw("ap");
  gr->SetMarkerColor(kRed);
  gr->SetLineColor(kRed);

  gr->SetMarkerStyle(23);
  gr->GetXaxis()->SetTitle("pTRIG1 Rate (kHz)");
  gr->GetYaxis()->SetTitle("Computer Live Time");
  gr->SaveAs("lt.pdf");
  //r->GetYaxis()->SetRangeUser(0.98,1);
  gr->SetTitle("Computer Live Time for all Runs");
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  //gr->GetYaxis()->SetRangeUser(0.85,1.0);
  
 
  
}
