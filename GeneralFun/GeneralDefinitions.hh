#ifndef GENERALDEFINITIONS_HH
#define GENERALDEFINITIONS_HH 1

#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TKey.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPad.h>
#include <TPaletteAxis.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TTree.h>

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
TH1D hello;
// =====================================================================
//   ------------------------------ PKUP -------------------------------
/*
Las siguientes variables sirven para decidir qué pulsos son dedicados y qué
pulsos son parásitos. Sólo los pulsos que cumplen determinadas condiciones se
tienen en cuenta. Lo de DEDICATED_PULSES_ID y PARASITIC_PULSES_ID es qué flag se
usa para cada pulso, dedicado o parásito. Ha cambiado con el tiempo, así que las
variables que llevan *_ROOTFILE hacen referencia al valor de la flag del
treefile: PSpulse. Las otras "DEDICATED_PULSES_ID" son para que lleven aquí
siempre el mismo valor. Puede faltar alguna condición más en los silicios, que
no se ha tenido en cuenta.
*/

#define ALLOW_MORE_THAN_ONE_PKUP_SIGNAL 1

#define DEDICATED_PULSES_ID_ROOTFILE 2  // 1
#define PARASITIC_PULSES_ID_ROOTFILE 3  // 2
#define DEDICATED_PULSES_ID 2
#define PARASITIC_PULSES_ID 3

#define DEDICATED_PULSES_PKUPAMPMIN 1
#define DEDICATED_PULSES_PKUPAMPMAX 1.e10
#define PARASITIC_PULSES_PKUPAMPMIN 1
#define PARASITIC_PULSES_PKUPAMPMAX 1.e10

#define DEDICATED_PULSES_INTMIN 6.e12   // 5.e12
#define DEDICATED_PULSES_INTMAX 1.e20   // 8.e12
#define PARASITIC_PULSES_INTMIN 1.e12   // 2.2e12
#define PARASITIC_PULSES_INTMAX 4.5e12  // 3.8e12
// =====================================================================

// =====================================================================
//   ---------------------------- PATHS --------------------------------
// =====================================================================

//   ---------------------------- Plots01 --------------------------------

string Direction2DHisto =
    "../DatosEnDiscoDuro/2DHistos/v02GainCorrectedMerge/Histos01_";

// string Direction2DHisto = "../DatosEnDiscoDuro/2DHistos/v02Merge/Histos01_";
//
string DirectionSave2DHisto = "../DatosEnDiscoDuro/ResultsPlot2DHisto/v02";
string DirectionSave2DHistoCONDOR =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/ResultsPlot2DHisto/v02";

string SaveYieldFolder =
    "../DatosEnDiscoDuro/Yield/"
    "v02";
string WFFile =
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "ProgramsC6D6/Analysis_v01/WF/Result_Er167_13_CS10_v03/Final/"
    "WF_Er167_13.in";
//   ---------------------------- Make2DHisto --------------------------------
char outdir[200] =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/2DHistos/"
    "v02/";
char CalibDirName[200] =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Calibration/"
    "CalibrationRunByRunv02";

char outdirGainCorrected[200] =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/2DHistos/"
    "v02GainCorrected/";
char CalibDirNameGainCorrected[200] =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Calibration/"
    "CalibrationRunByRunGainCorrectedv02";

char EOSPATH[200] = "/eos/experiment/ntof/processing/official/done/";
// char EOSPATH[200] =
//     "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/RootFiles/v01/done";

char WFFolder[1000] =
    "/eos/home-v/valcayne/nTOFDataProcessing/2024_Er_Cu_U/Calibration/WF/"
    "v01/";
// char RunListFname[1000] =
//     "/afs/cern.ch/work/v/valcayne/2026_Sm/RunLists/"
//     "RunList_2026_v01.txt";

// I put the Runlist directly from EOS so no everone can play with it
char RunListFname[1000] =
    "/eos/home-v/valcayne/CopiaOrdenadorCIEMAT/CmExperimentFolder/2026_Sm/"
    "2026_Sm/RunLists/RunList_2026_v01.txt";
// I put the Runlist directly from EOS so no everone can play with it
// This is mainly used to correct for the gainshift
char RunListFnameLABR[1000] =
    "/eos/home-v/valcayne/CopiaOrdenadorCIEMAT/CmExperimentFolder/2026_Sm/"
    "2026_Sm/RunLists/RunList_2026_LABR_v02.txt";

char DirNameoutMerged[200] =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/2DHistos/"
    "v02GainCorrectedMerge";

//   ----------------------------
//   MakeCalibration--------------------------------

string MCFolder =
    "/eos/home-v/valcayne/nTOFDataProcessing/2024_Er_Cu_U/Simulations/v02/"
    "2024_Er_Cu_U_";

// Information experimental data
string DataFolder =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Calibration/"
    "HistoAmp_v03";

string outFolder =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Calibration/"
    "OutputMakeEnergyCalibration_v03_NoBa";

//   ---------------------------- Monitoring --------------------------------

char dirnameMonitoring[1000] =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/GainMonitoring/v02";

string dirnameMonitor =
    "/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Monitoring";

//   ---------------------------- Colors --------------------------------

TColor* color0 = new TColor(10000, 0.0, 0.0, 0.0);     // black
TColor* color1 = new TColor(10001, 1.0, 0.0, 0.0);     // red
TColor* color2 = new TColor(10003, 0.0, 0.0, 1.0);     // blue
TColor* color3 = new TColor(10002, 0.35, 0.83, 0.33);  // Green hard
TColor* color4 = new TColor(10004, 1, 0.0, 1.0);       // magenta
TColor* color5 = new TColor(10005, 0.0, 1.0, 1.0);     // Cyan
TColor* color6 = new TColor(10006, 0.9, 0.6, 0);       // orange
TColor* color7 = new TColor(10007, 0.81, 0.37, 0.38);  // Granate
TColor* color8 = new TColor(10008, 0.35, 0.33, 0.85);  // other blue
TColor* color9 = new TColor(10009, 0.87, 0.73, 0.53);  // sand color

TColor* color10 = new TColor(10010, 0.8, 0.78, 0.67);
TColor* color11 = new TColor(10011, 0.54, 0.66, 0.63);
TColor* color12 = new TColor(10012, 0.83, 0.81, 0.53);
TColor* color13 = new TColor(10013, 0.52, 0.76, 0.64);
TColor* color14 = new TColor(10014, 0.51, 0.62, 0.55);
TColor* color15 = new TColor(10015, 0.70, 0.65, 0.59);
TColor* color16 = new TColor(10016, 0.8, 0.78, 0.67);
TColor* color17 = new TColor(10017, 0.67, 0.56, 0.58);
TColor* color18 = new TColor(10018, 0.46, 0.54, 0.57);
TColor* color19 = new TColor(10019, 0.68, 0.74, 0.78);
TColor* color20 = new TColor(10020, 0.5, 0.5, 0.61);
// =====================================================================

#define NDetectorMAX 15  // this is the maximum number of detectors of one typw

// =====================================================================
//   ------------------------------ TAC --------------------------------

#define TFLASH_BAF2_MIN_NS 11000
#define TFLASH_BAF2_MAX_NS 11500

// =====================================================================
//   ---------------------------- Other --------------------------------
#define MAXNBUNCHESINFILE 100000
#define MAXNSIGNALSINPULSE 1000000
// #define MAXNEVENTSINPULSE 1000000
//  =====================================================================

struct HistoInfo {
  string DetectorName;
  std::vector<int> DetectorNumber;
  std::vector<string> HistoName;
  std::vector<string> HistoTitle;
  std::vector<double> DetectorDeadTime_ns;
  std::vector<int> HistoType;
  std::vector<vector<double>> Xaxis;
  std::vector<vector<double>> Yaxis;
};

struct Signal {
  int RunNumber, BunchNumber, date, detn, time, PSpulse, isAlpha, movie;
  double edep, tof, tflash, eNeutron, tofPreviousSignal, edepPreviousSignal,
      weight;
  float amp, area, fwhm, fwtm, area_0, amp_0, area2, PulseIntensity, afast,
      aslow, Tau;
  string DetName;
};

struct PKUPInfo {
  int npulses;
  int np1, np2, np3;                    // dedicated,parasitic,other
  double PulsInt1, PulsInt2, PulsInt3;  // dedicated,parasitic,other
  double PKUPamp1, PKUPamp2, PKUPamp3, PKUParea1, PKUParea2,
      PKUParea3;  // dedicated,parasitic,other
  int pulseType[MAXNBUNCHESINFILE];
  int BunchNumber[MAXNBUNCHESINFILE];
  double PulseIntensity[MAXNBUNCHESINFILE];
  double PKUPAmp[MAXNBUNCHESINFILE];
  double PKUPArea[MAXNBUNCHESINFILE];
  double PKUPTflash[MAXNBUNCHESINFILE];
};

#endif
