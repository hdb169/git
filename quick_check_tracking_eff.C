#include "CTRun.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCut.h"

using namespace std;

void CTtrkingEffi(Int_t runNumber)
{
    TCut shmsScinGood    =  "P.hod.goodscinhit == 1";
    TCut shmsScinShould  =  shmsScinGood;
    TCut shmsScinShoulde =  shmsScinGood &&  "P.cal.etotnorm > 0.6 && P.cal.etotnorm < 1.6 && P.hgcer.npeSum > 0.5";
    TCut shmsScinShouldh =  shmsScinGood && "P.hod.betanotrack > 0.6 && P.hod.betanotrack < 1.5 && P.cal.etotnorm > 0. && P.hgcer.npeSum < 0.5";
    TCut shmsScinDid     =  shmsScinShould && "P.dc.ntrack > 0";
    TCut shmsScinDide    =  shmsScinShoulde && "P.dc.ntrack > 0";
    TCut shmsScinDidh    =  shmsScinShouldh && "P.dc.ntrack > 0";

    CTRun *ct = new CTRun(runNumber);
    if(!ct->fRunExist)
	return;
    TTree *tree = ct->GetTree();
    TH1D *pShouldHadron;
    TH1D *pDidHadron;  
    TH1D *pShouldElectron;
    TH1D *pDidElectron;  
    
    tree->Draw("P.hod.goodscinhit>>pShouldHadron", shmsScinShouldh,"goff");
    //tree->Draw("P.hod.betanotrack>>pShouldHadron", shmsScinShouldh);
    pShouldHadron = (TH1D*)gDirectory->Get("pShouldHadron");

    tree->Draw("P.hod.goodscinhit>>pDidHadron", shmsScinDidh,"goff");
    pDidHadron = (TH1D*)gDirectory->Get("pDidHadron");

    tree->Draw("P.hod.goodscinhit>>pShouldElectron", shmsScinShoulde,"goff");
    pShouldElectron = (TH1D*)gDirectory->Get("pShouldElectron");

    tree->Draw("P.hod.goodscinhit>>pDidElectron", shmsScinDide,"goff");
    pDidElectron = (TH1D*)gDirectory->Get("pDidElectron");

    Int_t pNumShouldHadron = pShouldHadron->GetEntries();
    Int_t pNumDidHadron = pDidHadron->GetEntries();
    Int_t pNumShouldElectron = pShouldElectron->GetEntries();
    Int_t pNumDidElectron = pDidElectron->GetEntries();

    cout << "===============================================================" <<endl;
    if(pNumShouldHadron == 0)
        cout << "SHMS hadron tracking efficiency: "<< 0 <<" %"<<endl;
    else
        cout << "SHMS hadron tracking efficiency: "<< (Double_t)pNumDidHadron*100/pNumShouldHadron <<" %"<<endl;
    
    if(pNumShouldElectron == 0)
        cout << "SHMS electron tracking efficiency: "<< 0 <<" %"<<endl;
    else
       cout << "SHMS electron tracking efficiency: "<< (Double_t)pNumDidElectron*100/pNumShouldElectron <<" %"<<endl;
//*************************************HMS**************************************88
    TCut HMSScinGood    =   "H.hod.goodscinhit == 1";
    TCut HMSScinShould  =   HMSScinGood; 
    TCut HMSScinShoulde =   HMSScinGood && "H.hod.betanotrack > 0.8 && H.hod.betanotrack < 1.2 && H.cal.etotnorm > 0.6&& H.cal.etotnorm < 2.0&& H.cer.npeSum > 0.5";
    TCut HMSScinShouldh =   HMSScinGood && "H.cal.etotnorm <0.6&& H.cal.etotnorm>0.0&& H.cer.npeSum < 0.5";
    TCut HMSScinDid     =   HMSScinShould && "H.dc.ntrack > 0";
    TCut HMSScinDide    =   HMSScinShoulde && "H.dc.ntrack > 0";
    TCut HMSScinDidh    =   HMSScinShouldh && "H.dc.ntrack > 0";

    TH1D *hShouldElectron;
    TH1D *hDidElectron;
    TH1D *hShouldHadron;
    TH1D *hDidHadron;  
    
    tree->Draw("H.hod.goodscinhit>>hShouldElectron", HMSScinShoulde,"goff");
    //    tree->Draw("H.hod.betanotrack>>hShouldElectron", HMSScinShoulde);
    hShouldElectron = (TH1D*)gDirectory->Get("hShouldElectron");

    tree->Draw("H.hod.goodscinhit>>hDidElectron", HMSScinDide,"goff");
    hDidElectron = (TH1D*)gDirectory->Get("hDidElectron");

    tree->Draw("H.hod.goodscinhit>>hShouldHadron", HMSScinShouldh,"goff");
    hShouldHadron = (TH1D*)gDirectory->Get("hShouldHadron");

    tree->Draw("H.hod.goodscinhit>>hDidHadron", HMSScinDidh,"goff");
    hDidHadron = (TH1D*)gDirectory->Get("hDidHadron");


    Int_t hNumShouldElectron = hShouldElectron->GetEntries();
    Int_t hNumDidElectron = hDidElectron->GetEntries();
    Int_t hNumShouldHadron = hShouldHadron->GetEntries();
    Int_t hNumDidHadron = hDidHadron->GetEntries();

    cout << "-------------------------------------------------------------" <<endl;
    if(hNumShouldElectron == 0)
       cout << "HMS electron tracking efficiency: "<< 0 <<" %"<<endl;
    else
       cout << "HMS electron tracking efficiency: "<< (Double_t)hNumDidElectron*100/hNumShouldElectron <<" %"<<endl;
    if(hNumShouldHadron == 0)
       cout << "HMS hadron tracking efficiency: "<< 0 <<" %"<<endl;
    else
       cout << "HMS hadron tracking efficiency: "<< (Double_t)hNumDidHadron*100/hNumShouldHadron <<" %"<<endl;
    cout << "===============================================================" <<endl;
}
