pos
Run    p       rf eff     err         kaon cont    Err
 7635   3.15   0.966192   0.00978249   0.0338079   0.00978249
 7642   2.699   0.98645   0.00496349   0.0135502   0.00496349
 7646   2.248   0.996345   0.00183631   0.00365532   0.00183631
 7661   1.797   0.998162   0.00181419   0.00183781   0.00181419
 7699   3.514   0.971283   0.00821252   0.0287167   0.00821252
 7706   2.928   0.976579   0.00988179   0.0234212   0.00988179
 7716   2.341   0.981727   0.00460333   0.0182725   0.00460333
 7768   3.214   0.966557   0.00800962   0.0334428   0.00800962
 7775   2.718   0.983882   0.00472844   0.0161177   0.00472844
 7783   2.223   0.991461   0.00338437   0.00853872   0.00338437
 7808   3.461   0.977425   0.0059781   0.0225747   0.0059781
 7813   2.928   0.989306   0.00410863   0.0106937   0.00410863
 7815   2.394   0.996306   0.00245411	    0	     0	
=======================================================================
neg
 7593   3.15   0.996182   0.0076274   0.00381794   0.0076274
 7608   2.699   0.996738   0.00241214   0.00326209   0.00241214
 7611   2.248   0.999903   0.000308561   9.71058e-05   0.000308561
 7625   1.797   1          4.1226e-10   -0   -0
 7671   3.514   0.988475   0.0040404   0.011525   0.0040404
 7679   2.928   0.985281   0.00408419   0.014719   0.00408419
 7684   2.341   0.990768   0.00336859   0.00923236   0.00336859
 7735   3.214   0.99069   0.00425135   0.00930968   0.00425135
 7737   2.718   0.994628   0.00247877   0.00537169   0.00247877
 7757   2.223   0.997642   0.00307429   0.00235757   0.00307429
 7796   3.461   0.991752   0.00374661   0.00824837   0.00374661
 7798   2.928   0.994994   0.00275482   0.00500595   0.00275482
 7805   2.394   0.997461    0.00198933	    0	     0
=======================================================================
Plot



#include <sstream>
#include <string>
#include <fstream>

void read_rfeff_pos_neg()
{
  std::ifstream infile("rf_eff_pos.txt"); //reads first txtfile

  std::string line;// read line by line
  vector <int> run; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> mom;
  vector <double> eff;
  vector <double> eff_err;//f = nocut/cut
  vector <double> kaon_cont;
  vector <double> kaon_cont_err;
  
 
  while (std::getline(infile, line))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line);// to read the whole strings in a line
      double a, b, c, d, e, f;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a >> b >> c >> d >> e >> f )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run.push_back(a);
      mom.push_back(b);
      eff.push_back(c);
      eff_err.push_back(d);//eff = d
      kaon_cont.push_back(e);//eff err = e
      kaon_cont_err.push_back(f);
      

    }
  cout<< "I am good"<<endl;
  
  for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
    {
       cout<< run[i] <<endl;
       
    }
   cout<< "I am good"<<endl;
   //====================================

 std::ifstream infile1("rf_eff_neg.txt"); //reads first txtfile

 std::string line1;// read line by line
  vector <int> run1; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> mom1;
  vector <double> eff1;
  vector <double> eff_err1;//f = nocut/cut
  vector <double> kaon_cont1;
  vector <double> kaon_cont_err1;
  
 
  while (std::getline(infile1, line1))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line1);// to read the whole strings in a line
      double a1, b1, c1, d1, e1, f1;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a1 >> b1 >> c1 >> d1 >> e1 >> f1 )) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run1.push_back(a1);
      mom1.push_back(b1);
      eff1.push_back(c1);
      eff_err1.push_back(d1);//eff = d
      kaon_cont1.push_back(e1);//eff err = e
      kaon_cont_err1.push_back(f1);
      

    }
  cout<< "I am good"<<endl;
  
  for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
    {
       cout<< run1[i] <<endl;
       
    }
   cout<< "I am good"<<endl;



   
   
   TCanvas *c1 = new TCanvas("c1","c1", 1200, 8000);
   c1->Divide(1,1);
   c1->cd(1);gPad->SetGrid();
  auto gr = new TGraphErrors(run.size(), &mom[0], &eff[0],  0, &eff_err[0]);// you are including Graph with Error, first one is to set points equal to size of first column, u can keep any columns, the x axis quantities, beginning from first number[0], y axis quantities[0], error along xaxis quantity = 0, if no error is defined, error in y axis quantities[0]
   gr->Draw("ap");
  gr->SetMarkerColor(kBlack);
  gr->SetLineColor(kBlack);
  gr->SetLineWidth(2);
  gr->SetMarkerSize(2);

  gr->SetMarkerStyle(20);
  gr->GetXaxis()->SetTitle("SHMS Momentum (GeV)");
  gr->GetYaxis()->SetTitle("Pion Purity");
  // gr->SaveAs("lt.pdf");
  gr->GetYaxis()->SetRangeUser(0.94,1.01);
  gr->SetTitle("Pion Purity Using RF Time");
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  //gr->GetYaxis()->SetRangeUser(0.85,1.0);
  //gr->Draw("ap");

  auto gr1 = new TGraphErrors(run1.size(), &mom1[0], &eff1[0],  0, &eff_err1[0]);
  gr1->Draw("P same");
  gr1->SetMarkerColor(kRed);
  gr1->SetLineColor(kRed);
  gr1->SetLineWidth(2);
  gr1->SetMarkerSize(2);
  gr1->SetMarkerStyle(22);
  gr1->SetMarkerStyle(20);
  c1->SaveAs("lt.pdf");

  
}

