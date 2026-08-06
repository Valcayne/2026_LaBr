

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TPaletteAxis.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TKey.h>
#include <TRandom.h>
#include <TF1.h>
#include <TMath.h>

using namespace std;

double ResFun(double *x,double *par){
  //return sqrt(par[0]*x[0]*x[0]+par[1]*x[0]);
  return sqrt(par[0]*x[0]*x[0]+par[1]*x[0]);

  //return sqrt(par[0]+par[1]/x[0])/2.35482;
  //return sqrt(par[0]+par[1]*x[0]);
//  return par[0]+sqrt(par[1]*x[0]);
  // return sqrt(par[0]*x[0]+par[1]*x[0]*x[0])/x[0];

 }

void plot01(char *file,char *RunCs,char *RunY,char *RunAm,char *RunCm,int det);void plot02(char *file,char *RunCs,char *RunY,char *RunAm,char *RunCm,int det);

void DoAllDetectorsResolution(char *file,char *RunCs,char *RunY,char *RunAm,char *RunCm){

  for(int j=1;j<41;j++){
    plot02(file,RunCs,RunY,RunAm,RunCm,j);
  }
} 

void DoAllDetectors(char *file,char *RunCs,char *RunY,char *RunAm,char *RunCm){

  for(int j=1;j<41;j++){
    plot01(file,RunCs,RunY,RunAm,RunCm,j);
  }
} 

void plot01(char *file,char *RunCs,char *RunY,char *RunAm,char *RunCm,int det){
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  
  ifstream inCs(RunCs);
  ifstream inY(RunY);
  ifstream inAm(RunAm);
  ifstream inCm(RunCm);

  char word[10];
double Amp[5];
double E[5];
double Error[5];
 double PercenError=0.1;

  for(int j=1;j<det;j++){
    inCs>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;

    inY>>word>>word>>word>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;
    inAm>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;
    inCm>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;
  }


  inCs>>word>>word>>word>>Amp[0];
    inY>>word>>word>>word>>Amp[1]>>word>>word>>Amp[2];
    inAm>>word>>word>>word>>Amp[3];
    inCm>>word>>word>>word>>Amp[4];
 
  E[0]=0.661657;
 E[1]=0.898042;
 E[2]=1.836063;
 E[3]=4.438;
 E[4]=6.130;
 for(int j=0;j<5;j++){ 
  cout<<"Energy"<<E[j]<<" Amp "<<Amp[j]<<endl;
  Error[j]=E[j]*PercenError;

  }
 
 TGraph* gr=new TGraphErrors(5,Amp,E,0,Error);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kBlue);
  

TH2D* h2=new TH2D("","",1000,-10,Amp[5-1]*1.1,1000,-0.1,E[5-1]*1.1);
   h2->GetXaxis()->SetTitle("Amp(channels)");
   h2->GetYaxis()->SetTitle("Energy (MeV)");
   char title[1000];
   sprintf(title," Blue Experimental Points -- BlackPol1 -- RedPol2 -- Det%d",det);
   h2->SetTitle(title);
  TCanvas* c1=new TCanvas("c1","c1",800,600);
   h2->Draw();
   gr->Draw("P same");
  cout<<"Fitting pol1 "<<endl;
  TF1 *myfitpol1 = new TF1("myfitpol1","pol1",0,20000);//pol1
  //myfitpol1->FixParameter(0,0);

  gr->Fit("myfitpol1","E0");
   myfitpol1->SetLineColor(kBlack);
   myfitpol1->Draw("same ");
   myfitpol1-> SetLineStyle(2);
  Double_t par1[2];
  myfitpol1->GetParameters(&par1[0]);
  //c1->Update();
  double p0pol1=par1[0];
  double p1pol1=par1[1];

  cout<<"  p0pol1 "<< p0pol1<<"  p1pol1 "<< p1pol1<<endl;

  cout<<"Fitting pol2 "<<endl;

  TF1 *myfitpol2 = new TF1("myfitpol2","pol2",0,20000);//pol2

  gr->Fit("myfitpol2","R0");
    myfitpol2->Draw("same");
   myfitpol2->SetLineColor(kRed);
   myfitpol2-> SetLineStyle(2);


  Double_t par2[3];
   myfitpol2->GetParameters(&par2[0]);
   c1->Update();
  double p0pol2=par2[0];
  double p1pol2=par2[1];
  double p2pol2=par2[2];
  cout<<"  p0pol2 "<< p0pol2<<"  p1pol2 "<< p1pol2<<"  p2pol2 "<< p2pol2<<endl;




  
  ///Checking Results
  for(int j=0;j<5;j++)
    {cout<<"Pol1 energy Real E "<<E[j]<<" using "<<p0pol1+ Amp[j]*p1pol1<<" Diferance % "<<100*(p0pol1+ Amp[j]*p1pol1-E[j])/E[j]<<endl;
      cout<<"Pol2 energy Real E "<<E[j]<<" using "<<p0pol2+ Amp[j]*p1pol2+ Amp[j]*Amp[j]*p2pol2<<" Diferance % "<<100*(p0pol2+ Amp[j]*p1pol2+ Amp[j]*Amp[j]*p2pol2-E[j])/E[j]<<endl<<endl;;

    
     
    }

  ofstream out(file,ios::out | ios::app | ios::binary);
  out<<det<<" "<<p0pol2<<" "<<p1pol2<<" "<<p2pol2<<endl;
  out.close();
  char Saveplot[1000];
  sprintf(Saveplot,"ResultsPlots03/CalibrationDet%d.png",det);
  c1->SaveAs(Saveplot);
  sprintf(Saveplot,"ResultsPlots03/CalibrationDet%d.root",det);
  c1->SaveAs(Saveplot);
 sprintf(Saveplot,"ResultsPlots03/CalibrationDet%d.eps",det);
  c1->SaveAs(Saveplot);


 //  delete gr;
//   delete h2;
//   delete myfitpol2;
//     delete myfitpol1;
  c1->SaveAs(Saveplot);

  return;
}



void plot02(char *file,char *RunCs,char *RunY,char *RunAm,char *RunCm,int det){
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  
  ifstream inCs(RunCs);
  ifstream inY(RunY);
  ifstream inAm(RunAm);
  ifstream inCm(RunCm);

  char word[10];
double ResPercen[5];
double E[5];
double afastPeak[5];

double Error[5];
 double PercenError=0.1;

  for(int j=1;j<det;j++){
    inCs>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;

    inY>>word>>word>>word>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;
    inAm>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;
    inCm>>word>>word>>word>>word>>word;  cout<<" "<<word<<endl;
  }


  inCs>>word>>word>>word>>afastPeak[0]>>ResPercen[0];
    inY>>word>>word>>word>>afastPeak[1]>>ResPercen[1]>>word>>afastPeak[2]>>ResPercen[2];
    inAm>>word>>word>>word>>afastPeak[3]>>ResPercen[3];
    inCm>>word>>word>>word>>afastPeak[4]>>ResPercen[4];
 


  E[0]=0.661657;
 E[1]=0.898042;
 E[2]=1.836063;
 E[3]=4.438;
 E[4]=6.130;
//  ResPercen[0]=100*ResPercen[0]*2.35482/E[0]/1000.0;
//  ResPercen[1]=100*ResPercen[1]*2.35482/E[1]/1000.0;
//  ResPercen[2]=100*ResPercen[2]*2.35482/E[2]/1000.0;
//  ResPercen[3]=100*ResPercen[3]*2.35482/E[3]/1000.0;
//  ResPercen[4]=100*ResPercen[4]*2.35482/E[4]/1000.0;


 ResPercen[0]=ResPercen[0]*2.35482*E[0]/afastPeak[0];
 ResPercen[1]=ResPercen[1]*2.35482*E[1]/afastPeak[1];
 ResPercen[2]=ResPercen[2]*2.35482*E[2]/afastPeak[2];
 ResPercen[3]=ResPercen[3]*2.35482*E[3]/afastPeak[3];
 ResPercen[4]=ResPercen[4]*2.35482*E[4]/afastPeak[4];


 // ResPercen[0]=ResPercen[0]/**2.35482*//(1000.0*E[0]);
//  ResPercen[1]=ResPercen[1]/**2.35482*//(1000.0*E[1]);
//  ResPercen[2]=ResPercen[2]/**2.35482*//(1000.0*E[2]);
//  ResPercen[3]=ResPercen[3]/**2.35482*//(1000.0*E[3]);
//  ResPercen[4]=ResPercen[4]/**2.35482*//(1000.0*E[4]);

 for(int j=0;j<5;j++){ 
   cout<<"Energy"<<E[j]<<" ResPercen "<<ResPercen[j]<<" afastPeak[0] "<<afastPeak[j]<<endl;
  //Error[j]=E[j]*PercenError;
  Error[j]=0.0;

  }
 
 TGraph* gr=new TGraphErrors(5,E,ResPercen,Error,0);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kBlue);
  
TH2D* h2=new TH2D("","",1000,-0.1,E[5-1]*1.1,1000,0.0,4);

//TH2D* h2=new TH2D("","",1000,-0.1,E[5-1]*1.1,1000,0.0,0.6);
   h2->GetXaxis()->SetTitle("Energy (MeV)");
   h2->GetYaxis()->SetTitle("FWHM (MeV)");

   char title[100];
   sprintf(title,"Det %d",det);
   h2->SetTitle(title);
  TCanvas* c1=new TCanvas("c1","c1",800,600);
   h2->Draw();
   gr->Draw("P same");
  cout<<"Fitting pol1 "<<endl;

//   TF1 *myfitpol1 = new TF1("myfitpol1",ResFun,0.1,10,2);
//   //TF1 *myfitpol1 = new TF1("myfitpol1","pol1",0.1,10);

//   //myfitpol1->FixParameter(0,-0.005);
//   //myfitpol1->FixParameter(1,0.02);

//   gr->Fit("myfitpol1");
//    myfitpol1->SetLineColor(kBlack);
//    myfitpol1->Draw("same E");
//    myfitpol1-> SetLineStyle(2);
//   Double_t par1[2];
//   myfitpol1->GetParameters(&par1[0]);
//   //c1->Update();
//   double p0pol1=par1[0];
//   double p1pol1=par1[1];

//   cout<<"  p0pol1 "<< p0pol1<<"  p1pol1 "<< p1pol1<<endl;

  
  TF1 *f1 = new TF1("ResFun",ResFun,0.1,10,2);
  f1->SetParameter(0,0.003);
  f1->SetParameter(1,0.001);
  gr->Fit(f1);
  f1->Draw("L same");


  Double_t par[2],par1[2];
  f1->GetParameters(&par[0]);
  c1->Update();
  double p0pol1=par[0];
  double p1pol1=par[1];


  
  ///Checking ResPercenults
  for(int j=0;j<5;j++)
    {cout<<"Pol1 energy Real E "<<E[j]<<" using "<<p0pol1+ ResPercen[j]*p1pol1<<" Diferance % "<<100*(p0pol1+ ResPercen[j]*p1pol1-E[j])/E[j]<<endl;
      

    
     
    }

  ofstream out(file,ios::out | ios::app | ios::binary);
  out<<"BAF2 "<<det<<" "<<p0pol1<<" "<<p1pol1<<endl;
  out.close();
  char Saveplot[1000];
  sprintf(Saveplot,"ResolutionResultsPlots03/ResDet%d.png",det);
  c1->SaveAs(Saveplot);
  sprintf(Saveplot,"ResolutionResultsPlots03/ResDet%d.root",det);
  c1->SaveAs(Saveplot);
 sprintf(Saveplot,"ResolutionResultsPlots03/ResDet%d.eps",det);
  c1->SaveAs(Saveplot);

  return;
}


