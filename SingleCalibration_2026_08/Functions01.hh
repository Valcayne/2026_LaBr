#ifndef FUNCTIONS01_HH
#define FUNCTIONS01_HH 1

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1D.h>
#include <TH2D.h>
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

#define ROUTINEOPT 3  // 1: Eric's, 2: CMT's, 3: ntof standard PSA
#define GETAREA_METHOD 2 	// 1: Re-definition with formula, 
							// 2: from tree->area, 
							// 3: tree->area/TauSlow; 
							// See function GetArea(...)

using namespace std;

struct Signal{
  int RunNumber,BunchNumber,date,detn,time,PSpulse,isAlpha;
  double tof,tflash;
  float amp,area,fwhm,fwtm,area_0,amp_0,area2,PulseIntensity,afast,aslow,Tau;
};

//===========================================================================================
int TakeFinalMultFactors(const char* fname,int* run,double* MF,int CRN); //All the MF for crystal CRN
int TakeFinalMultFactors(const char* fname,double* MF,int run); // The 40 MF for one run
double FindMultFactor(int RunN,int* runnumbers,double* MF,int nruns);
void TakePeaks(const char* fname,double* x,int column, int NDets=40);//column=1,2,3,...
void TakeEnergyCalibrationParameters(const char* fname,double* a0,double* a1,double* a2);
void TakeAlphaGammaCutValues(const char* fname,double* Ratioval,double* timeRatioval);
void TakeTimeCalibrationParameters(const char* fname,double* Toffset,double* Tslope);
float_t GetArea(float_t area);
int GetParType(Signal* P, double* TimeRatioVal, double* AmpRatioVal);
void AttachStruct(Signal* P,TTree* tr);
void SetStyle03();
void SetStyle04();
void SetStyle05();
double GetR2(TGraph* gr, TF1* f); // Coefficient of determination (R^2) for a TGraph and a TF1
//===========================================================================================

double GetR2(TGraph* gr, TF1* f)
{
    // Calculate the coefficient of determination (R²) for the fit
    // R² = 1 - (sum of squared residuals) / (total sum of squares)
    if (!gr || !f) return -1.0;

    const int n = gr->GetN();
    if (n <= 1) return -1.0;

    // Calculate the mean of y values
    double sumY = 0.0;
    double x, y;

    for (int i = 0; i < n; ++i) {
        gr->GetPoint(i, x, y);
        sumY += y;
    }

    const double yMean = sumY / n;

    // Calculate total sum of squares (SS_tot) and residual sum of squares (SS_res)
    double ssTot = 0.0;
    double ssRes = 0.0;

    for (int i = 0; i < n; ++i) {
        gr->GetPoint(i, x, y);
        const double yFit = f->Eval(x);
        ssTot += (y - yMean) * (y - yMean);
        ssRes += (y - yFit) * (y - yFit);
    }

    if (ssTot == 0.0) return -1.0;
    return 1.0 - ssRes / ssTot;
}

void SetStyle03(){

  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.58);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleSize(0.07,"t");
  gStyle->SetTitleAlign(23);

  gStyle->SetLabelSize(0.07,"xy");
  gStyle->SetLabelOffset(0.008,"xy");
  gStyle->SetTitleSize(0.07,"xy");
  gStyle->SetTitleOffset(1.04,"x");
  gStyle->SetTitleOffset(1.45,"y");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  gROOT->ForceStyle();
}

// Same as 03 but higher RightMargin for X axis with out-of-frame scientific notation (x10^)
void SetStyle04(){

  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.58);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleSize(0.07,"t");
  gStyle->SetTitleAlign(23);

  gStyle->SetLabelSize(0.07,"xy");
  gStyle->SetLabelOffset(0.008,"xy");
  gStyle->SetTitleSize(0.07,"xy");
  gStyle->SetTitleOffset(1.04,"x");
  gStyle->SetTitleOffset(1.45,"y");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  gROOT->ForceStyle();
}


// Similat to 04 but with a subpad for residuals
void SetStyle05(){

  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.58);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleSize(0.07,"t");
  gStyle->SetTitleAlign(23);

  gStyle->SetLabelSize(0.08,"y");
  gStyle->SetLabelSize(0.0, "x"); // No X axis labels in the upper pad, they will be in the lower pad
  gStyle->SetLabelOffset(0.008,"y");
  gStyle->SetTitleSize(0.08,"y");
  gStyle->SetTitleOffset(1.10,"y");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  gROOT->ForceStyle();
}


void AttachStruct(Signal* P,TTree* tr){

  tr->SetBranchAddress("RunNumber",&(P->RunNumber));
  tr->SetBranchAddress("BunchNumber",&(P->BunchNumber));
  tr->SetBranchAddress("date",&(P->date));
  tr->SetBranchAddress("detn",&(P->detn));
  tr->SetBranchAddress("time",&(P->time));
  tr->SetBranchAddress("amp",&(P->amp));
  tr->SetBranchAddress("tof",&(P->tof));
  tr->SetBranchAddress("tflash",&(P->tflash));
  tr->SetBranchAddress("area",&(P->area));
  tr->SetBranchAddress("fwhm",&(P->fwhm));
  tr->SetBranchAddress("fwtm",&(P->fwtm));
  tr->SetBranchAddress("area_0",&(P->area_0));
  tr->SetBranchAddress("amp_0",&(P->amp_0));
  tr->SetBranchAddress("area2",&(P->area2));
  tr->SetBranchAddress("PSpulse",&(P->PSpulse));
  tr->SetBranchAddress("PulseIntensity",&(P->PulseIntensity));
  tr->SetBranchAddress("afast",&(P->afast));
  tr->SetBranchAddress("aslow",&(P->aslow));
  tr->SetBranchAddress("isAlpha",&(P->isAlpha));
  tr->SetBranchAddress("risetime",&(P->Tau));
}


void TakeTimeCalibrationParameters(const char* fname,double* Toffset,double* Tslope){

  char word[100];
  int detn;
  ifstream in(fname);
  for(int i=1;i<=40;i++){
    in>>word>>detn>>word>>word>>Toffset[i]>>Tslope[i];
    if(detn!=i){cout<<" ############## Error in "<<__FILE__<<", line "<<__LINE__<<" ##############"<<endl; exit(1);}
  }
  in.close();
  if(!in.good()){
    cout<<" ############## Error reading TimeCalibrationParameters --> "<<fname<<"  ##############"<<endl;
    exit(1);
  }

}


void TakeAlphaGammaCutValues(const char* fname,double* Ratioval,double* timeRatioval){
  int detn;
  ifstream in(fname);
  for(int i=1;i<=40;i++){
    in>>detn;
    in>>Ratioval[detn]>>timeRatioval[detn];
    if(detn!=i){cout<<" ############## Error in "<<__FILE__<<", line "<<__LINE__<<" ##############"<<endl; exit(1);}
  }
  if(!in.good()){
    cout<<" ############## Error reading CutList --> "<<fname<<"  ##############"<<endl;
    exit(1);
  }
  in.close();
}


void TakeEnergyCalibrationParameters(const char* fname,double* a0,double* a1,double* a2){

  ifstream in(fname);
  if(!in.good()){
    cout<<" **** Error opening file <"<<fname<<"> ****"<<endl;
    exit(1);
  }
  string word;
  int NDet;
  
  for(int i=1;i<=40;i++){
    in>>word>>NDet;
    if(NDet!=i){cout<<" ########### Error reading "<<fname<<" ###########"<<endl;}
    in>>a0[i]>>a1[i]>>a2[i];
  }
  in.close();


}


int TakeFinalMultFactors(const char* fname,int* run,double* MF,int CRN){

  int NRuns;
  char word[100];
  ifstream in(fname);
  in>>NRuns>>word;
  for(int i=1;i<=40;i++){
    in>>word>>word;
    for(int j=0;j<NRuns;j++){
      in>>run[j]>>MF[j];
    }
    if(i==CRN){break;}
  }
  return NRuns;
}


int TakeSILIMultFactors(const char* fname, int* run, double* MF, int CRN){
	int NRuns;
	char word[100];
	ifstream in(fname);
	in>>NRuns>>word;
	for(int i=1; i<=4;i++){
		in>>word>>word;
		for(int j=0; j<NRuns; j++){
			in>>run[j]>>MF[j];
		}
		if(i==CRN){break;}
	}
	return NRuns;
}


int TakeFinalMultFactors(const char* fname,double* MF,int run){

  for(int i=0;i<=40;i++){MF[i]=0;}
  int NRuns,thisRun;
  double thisMF;
  char word[100];
  ifstream in(fname);
  in>>NRuns>>word;
  for(int i=1;i<=40;i++){
    in>>word>>word;
    for(int j=0;j<NRuns;j++){
      in>>thisRun>>thisMF;
      if(thisRun==run){
	MF[i]=thisMF;
      }
    }
  }
  for(int i=1;i<=40;i++){
    if(MF[i]==0){
      cout<<" ############# ERROR in "<<__FILE__<<", line "<<__LINE__<<" #############"<<endl; exit(1);
    }
  }
  
  return 0;
}


void TakePeaks(const char* fname,double* x,int column, int NDets){//column=1,2,3,...

  ifstream in(fname);
  char word[500];

  int np=0,np_old=0;
  for(int i=0;i<NDets;i++){
    in>>word>>np;
    if (np==0) {
      cout << " **** WARNING: Detector with zero calibration points in file <" << fname << ">, detector " << i + 1 << " ****" << endl;
      cout << " **** This detector will be ignored in the fit ****" << endl;
      continue; 
    }
    //cout<<word<<endl;
    if(column>np || (np_old!=np && i>0)){
      cout<<" **** Error in "<<__FILE__<<", line "<<__LINE__<<" ****"<<endl;
      cout<<fname<<"  "<<i+1<<"  "<<column<<endl;
      exit(1);
    }
    for(int j=0;j<column;j++){
      in>>word>>x[i+1]>>word;
    }
    in.ignore(256,'\n');
    //for(int j=column;j<np;j++){
    //  in>>word>>word>>word;
    //}
    np_old=np;
  }
  if(!in.good()){
    cout<<" **** Error reading "<<fname<<" ****"<<endl;
    exit(1);
  }
  in.close();

}


double FindMultFactor(int RunN,int* runnumbers,double* MF,int nruns){

  if(RunN<=runnumbers[0]){return MF[0];}
  if(RunN>=runnumbers[nruns-1]){return MF[nruns-1];}

  for(int i=0;i<nruns;i++){
    if(runnumbers[i]==RunN){
      return MF[i];
    }
    if(runnumbers[i]>RunN){ //then we need to interpolate
      double slope=(MF[i]-MF[i-1])/(runnumbers[i]-runnumbers[i-1]);
      double bfac=MF[i]-slope*runnumbers[i];
      return bfac+slope*RunN;
    }
  }

  //We should not be here
  cout<<" ########## ERROR in "<<__FILE__<<", line "<<__LINE__<<" ##########"<<endl; exit(1);

  return 0;
}


Float_t GetArea(Float_t fastamp,Float_t slowamp,Float_t area,Float_t Tau) {
	// Joins the different methods to determine the area from the "area"
	// taken from the tree
	//==================================================================
	int opt = GETAREA_METHOD; 
	double TauSlow=630;
	//==================================================================
	Float_t area_new; 
	
	if (opt==1) {
		area_new=(2.71828*fastamp*Tau+slowamp*(TauSlow-Tau))/TauSlow; //re-definition, since it could be wrong in the rootfile
	}
	else if(opt==2) {
		area_new = area; 
	}
	else if(opt==3) {
		area_new = area/TauSlow;
	}
	
	
	return area_new;
}

int GetParType(Signal* P, double* TimeRatioVal, double* AmpRatioVal) {
	// Twin of TACCalibrationManager::GetParType in TACCalibrationManager.hh

	int DetN=P->detn;
	double TauSlow=630;
	
	double timeratio;
	if (ROUTINEOPT==1) {timeratio=P->fwhm/(TauSlow*log(1.+P->aslow));}
	else if (ROUTINEOPT==2) {timeratio=P->fwtm;}
  else if (ROUTINEOPT==3) {
    // No pulse discrimination, only one particle type (gammas):
    return 1; // gammas
  }

	double area = GetArea(P->afast,P->aslow,P->area,P->Tau);
	double areasratio=P->afast/area;
	if((timeratio>TimeRatioVal[DetN] && ROUTINEOPT==1) ||
	   (areasratio<AmpRatioVal[DetN] && ROUTINEOPT==2) ){

		if((areasratio<AmpRatioVal[DetN] && ROUTINEOPT==1) ||
		   (timeratio>TimeRatioVal[DetN] && ROUTINEOPT==2) ){
			return 0; //alphas
		}
		else{
			return 1; //gammas
		}
	}

	return 2;     // others
}


#endif

