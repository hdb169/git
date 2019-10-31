import ROOT
from ROOT import TCanvas, TFile, TProfile, TNtuple, TH1F, TH2F
from ROOT import gROOT, gBenchmark, gRandom, gSystem, Double,gPad

print (" This is my script ")
f = ROOT.TFile.Open("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/cal_calib_oct22/coin_replay_production_7671_100000.root", "read")


t= f.Get("T")

c1 = TCanvas( 'c1', 'The FillRandom example', 1000,800 )
c1.Divide(2,2)

c1.cd(1)
gPad.SetGridx()
gPad.SetGridy()
t.Draw("P.cal.etottracknorm>>h(100,0.001,2)","P.gtr.dp>-10&&P.gtr.dp<20&&P.gtr.beta>0.5&&P.gtr.beta<1.5")
#h.Show() #not work
#h.Write() #not work
#gBenchmark.Show( 'five' )

#t.Print()
#t.scan()
#for event in f.T :
     # print event.branchName.<do something with it>

c1.cd(2)
t.Draw("H.cal.etottracknorm>>h2(100,0.001,2)","H.gtr.dp>-10&&P.gtr.dp<10&&H.gtr.beta>0.5&&H.gtr.beta<1.5")
gPad.SetGridx()
gPad.SetGridy()

c1.cd(3)
t.Draw("P.hod.beta>>h3(100,0.001,2)","P.gtr.dp>-10&&P.gtr.dp<20&&P.gtr.beta>0.5&&P.gtr.beta<1.5&&P.hgcer.npeSum>2.0")
gPad.SetGridx()
gPad.SetGridy()


c1.cd(4)
t.Draw("H.hod.beta>>h4(100,0.001,2)","H.gtr.dp>-10&&H.gtr.dp<10&&H.gtr.beta>0.5&&H.gtr.beta<1.5&&H.cer.npeSum>2.0")
gPad.SetGridx()
gPad.SetGridy()



c1.Print("pdf/newhist.pdf")
