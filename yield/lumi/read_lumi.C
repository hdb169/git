#include <sstream>
#include <string>
#include <fstream>

void read_lumi()
{
  //std::ifstream infile("singles.txt"); //reads first txtfile
  std::ifstream infile("txtfile/lumi_plot_piplus.txt"); //reads first txtfile

  std::string line;// read line by line
  vector <int> run; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> current;
  vector <double> rate;
  vector <double> lt;
  vector <double> shms_tr;
  vector <double> hms_tr;
  vector <double> yield;
  vector <double> yield_err;

  while (std::getline(infile, line))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line);// to read the whole strings in a line
      double a, b, c, d, e, f, g, h;// define eun by a, did by b, should by c, eff by d and eff_err by e
	if (!(iss >> a >> b >> c >> d >> e >>f >>g >>h)) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
	  {
            
	    break; 
            
	  } // error
        
      run.push_back(a);//now run is stored in a
      current.push_back(b);//did is stored in b
      rate.push_back(c);//should is stored as c
      lt.push_back(d);//eff = d
      shms_tr.push_back(e);//eff err = e
      hms_tr.push_back(f);//eff err = e
      yield.push_back(g);//eff err = e
      yield_err.push_back(h);//eff err = e


    }

  
  for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
    {
      cout <<  run[i]<<endl;//you have to cout each elements , so need i
      cout<<  yield_err[i]<<endl;
    }
  
   auto gr = new TGraphErrors(run.size(), &rate[0], &yield[0],  0, &yield_err[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  gr->Draw("ap");
  gr->SetMarkerColor(kRed);
  gr->SetLineColor(kRed);

  gr->SetMarkerStyle(21);
  gr->GetXaxis()->SetTitle("3/4 Rate (kHz)");
  gr->GetYaxis()->SetTitle("Corrected Yield (counts/mC)");
  gr->SaveAs("lumi.pdf");
  gr->GetYaxis()->SetRangeUser(170, 210);
  gr->GetXaxis()->SetLimits(250, 550);

  gr->SetTitle("Charge Normalized Yield vs SHMS 3/4 Rate, Pi+");
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  gr->SetLineWidth(3);
  //gr->GetYaxis()->SetRangeUser(0.85,1.0);
  
  auto gr1 = new TGraphErrors(run.size(), &current[0], &yield[0],  0, &yield_err[0]);// you are including Gr1aph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
  gr1->Draw("ap");
  gr1->SetMarkerColor(kRed);
  gr1->SetLineColor(kRed);

  gr1->SetMarkerStyle(21);
  gr1->GetXaxis()->SetTitle("BCM1 Current (uA)");
  gr1->GetYaxis()->SetTitle("Corrected Yield (counts/mC)");
  gr1->SaveAs("lumi_cur_pos.pdf");
  gr1->GetYaxis()->SetRangeUser(170, 210);
  // gr1->GetXaxis()->SetLimits(250, 550);

  gr1->SetTitle("Charge Normalized Yield vs Current, Pi+");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  gr1->SetLineWidth(3);
  //gr1->GetYaxis()->SetRangeUser(0.85,1.0);
  
  
}
