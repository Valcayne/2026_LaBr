#ifndef TACCALIBRATOR_HH
#define TACCALIBRATOR_HH 1

#include <TF1.h>
#include <TFile.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TMath.h>
#include <TSpectrum.h>
#include <TTree.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define TREENAME \
  "LABR"  // "LABR" de-activates reading CutList. Other options: "BAF2"
#define NDETECTORS 16  // 40
const string ROOTFILEFOLDER = "../DatosEnDiscoDuro/RootFiles/MichiData";

// //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// // Cs137,Y88,Bi207,Ba133

// #define CSYSOURCE 1
// #define NHISTOBINS  1000
// #define HISTOLOWLIM 80e3//50e3//180e3
// #define HISTOHILIM 220e3//500e3
// #define TRIGGERLEVEL 0.9//0.5 //(% of the max value of the no-bkg histo)
// #define FWHM_EST 10e3       // estimation of the FWHM
// #define CUTFILENAME 11 //

// //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// // Cs137,Y88,Bi207,Ba133

#define CSYSOURCE 1
#define NHISTOBINS 400
#define HISTOLOWLIM 100e3
#define HISTOHILIM 400e3
#define TRIGGERLEVEL 0.3  //(% of the max value of the no-bkg histo)
#define FWHM_EST 3e3      // estimation of the FWHM
#define CUTFILENAME 11    //

// //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// ////////AmBe:

//  #define AMBESOURCE 1
//  #define NHISTOBINS 200
//  #define HISTOLOWLIM 400e3
//  #define HISTOHILIM 1000e3
//  #define TRIGGERLEVEL 0.6  //(% of the max value of the no-bkg histo)
//  #define FWHM_EST 20e3      // estimation of the FWHM
//  #define CUTFILENAME 11 // It MEANS
//  sprintf(cutlistname,"/home/u6979/CmMeasurement/Functions/AnalysisTAC/PulseDiscrimination/CutList0%d.txt",CutFileNumber);
//

// ////////Pu/C,CmC
// #define CMCSOURCE 1
// #define NHISTOBINS 200
// #define HISTOLOWLIM 1100e3 //2500
// #define HISTOHILIM 2000e3//5000
// #define TRIGGERLEVEL 0.2  //(% of the max value of the no-bkg histo)
// #define FWHM_EST 5e3      // estimation of the FWHM
// #define CUTFILENAME 11 //

// #define HISTOLOWLIM 80
// #define HISTOHILIM 250
// #define TRIGGERLEVEL 0.5 //(% of the max value of the no-bkg histo)
// #define FWHM_EST 5       // estimation of the FWHM

#define MAXNLOCALMAX 10
class TACCalibrator {
 public:
  TACCalibrator();
  ~TACCalibrator();
  int FillAndCreateHistograms(string filename);

  int FillHistograms(string filename);
  void FillRatioVal(string CutFilename);

  int TakeBackground(int CrNumber);
  int TakeAllBackgrounds();

  int FindPeaks(int CrNumber);
  int FindAllPeaks();

  int SaveValues(string filename);
  double RatioVal[NDETECTORS + 1], TimeRatioVal[NDETECTORS + 1];
  TH1F* GetHhisto(int cr) { return h[cr]; }
  TH1F* GetBhisto(int cr) { return b[cr]; }
  TH1F* GetDhisto(int cr) { return d[cr]; }

  int GetNFitFun(int cr) { return NFitFun[cr]; }
  TF1* GetFitFun(int cr, int i) { return FitFun[cr][i]; }
  TF1* GetFitFun2(int cr, int i) { return FitFun2[cr][i]; }

 private:
  TH1F* h[NDETECTORS + 1];  // real hstograms
  TH1F* b[NDETECTORS + 1];  //"background"
  TH1F* d[NDETECTORS + 1];  // real - background

  TF1* FitFun[NDETECTORS + 1][MAXNLOCALMAX];
  TF1* FitFun2[NDETECTORS + 1][MAXNLOCALMAX];
  int NFitFun[NDETECTORS + 1];

  double FWHM;
};

#endif
