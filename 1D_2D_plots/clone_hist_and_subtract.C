
  htest->Add(h1test,h4test,1,-1);//same as htest=h1-h2;
  c11->Divide(3,2);
  c11->cd(1);
  h1->Draw();
  c11->cd(2);
  h4->Draw();
  c11->cd(3);
  htest->Draw();

  c11->cd(4);
  h4test->Draw();
  c11->cd(5);
  h1test->Add(h4test,-1);//same as h1-h2
  h1test->Draw();

  cout<<h1test->Integral()<<  "     "<<h4test->Integral()<<" "<<htest->Integral()<<endl;
  cout<<h1test->GetEntries()<< "    "<<h4test->GetEntries()<<"  "<<h1test->GetEntries()-h4test->GetEntries()<<endl;
  f->Write();
