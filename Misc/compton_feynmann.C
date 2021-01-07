//A macro to draw compton scattering Feynmann Diagram
void compton_feynman()
{
   
   TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 300);
   c1->Range(0, 0, 180, 60);
   Int_t linsav = gStyle->GetLineWidth();
   gStyle->SetLineWidth(3);
   TLatex t;
   t.SetTextAlign(22);
   t.SetTextSize(0.1);
   TArrow * ar;
   TLine * l;
   TEllipse * el;
   TCurlyLine * gamma;

   // regular compton   
   ar = new TArrow(10, 50, 20, 40, 0.02,"|>"); ar->Draw();
   l = new TLine(20, 40, 30, 30); l->Draw();
   el = new TEllipse(30,30,0.8,0.8);
   el->SetFillColor(1);
   el->SetFillStyle(1001);
   el->Draw();
   ar = new TArrow(30, 30, 45, 30, 0.02,"|>"); ar->Draw();
   l = new TLine(45, 30, 60, 30); l->Draw();
   el = new TEllipse(60,30,0.8,0.8);
   el->SetFillColor(1);
   el->SetFillStyle(1001);
   el->Draw();   
   ar = new TArrow(60, 30, 70, 40, 0.02,"|>"); ar->Draw();
   l = new TLine(70, 40, 80, 50); l->Draw();
   t.DrawLatex(17,36,"e");
   t.DrawLatex(47,27,"e");
   t.DrawLatex(75,40,"e");

   gamma = new TCurlyLine(30, 30, 10, 10);
   gamma->SetWavy();
   gamma->Draw();
   t.DrawLatex(14.5,20.7,"#gamma");
   gamma = new TCurlyLine(60, 30, 80, 10);
   gamma->SetWavy();
   gamma->Draw();
   t.DrawLatex(77.5,20.7,"#gamma");

   // cross diagram compton   
   ar = new TArrow(100, 50, 120, 45, 0.02,"|>"); ar->Draw();
   l = new TLine(120, 45, 140, 40); l->Draw();
   el = new TEllipse(140,40,0.8,0.8);
   el->SetFillColor(1);
   el->SetFillStyle(1001);
   el->Draw();
   ar = new TArrow(140, 40, 140, 30, 0.02,"|>"); ar->Draw();
   l = new TLine(140, 30, 140, 20); l->Draw();
   el = new TEllipse(140,20,0.8,0.8);
   el->SetFillColor(1);
   el->SetFillStyle(1001);
   el->Draw();   
   ar = new TArrow(140, 20, 155, 35, 0.02,"|>"); ar->Draw();
   l = new TLine(155, 35, 170, 50); l->Draw();
   t.DrawLatex(123,41,"e");
   t.DrawLatex(137,27,"e");
   t.DrawLatex(162,38,"e");

   gamma = new TCurlyLine(140, 20, 100, 10);
   gamma->SetWavy();
   gamma->Draw();
   t.DrawLatex(114.5,18.5,"#gamma");
   gamma = new TCurlyLine(140, 40, 170, 10);
   gamma->SetWavy();
   gamma->Draw();
   t.DrawLatex(167,20.7,"#gamma");

   
   //TArc *a = new TArc(70, 30, 15);
   //a->Draw();
   //t.DrawLatex(55, 45,"#bar{q}");
   //t.DrawLatex(85, 15,"q");
   //TCurlyLine *gluon = new TCurlyLine(70, 45, 70, 15);
   //gluon->Draw();
   //t.DrawLatex(77.5,30,"g");

   //TCurlyLine *z0 = new TCurlyLine(85, 30, 110, 30);
   //z0->SetWavy();
   //z0->Draw();
   //t.DrawLatex(100, 37.5,"Z^{0}");

   //l = new TLine(110, 30, 130, 10); l->Draw();
   //l = new TLine(110, 30, 130, 50); l->Draw();

   //TCurlyArc *gluon1 = new TCurlyArc(110, 30, 12.5*sqrt(2), 315, 45);
   //gluon1->Draw();

   //t.DrawLatex(135,6,"#bar{q}");
   //t.DrawLatex(135,55,"q");
   //t.DrawLatex(135,30,"g");
   c1->Update();
   gStyle->SetLineWidth(linsav);
}
