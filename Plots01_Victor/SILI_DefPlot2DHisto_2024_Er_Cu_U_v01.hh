#ifndef DEFPLOT2DHISTO_2024_TEST_L6D6_HH
#define DEFPLOT2DHISTO_2024_TEST_L6D6_HH 1

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

double TimeMeasurement_ns = 1e8;
string NameDetector = "SILI";
bool CorrectDeadTime = false;

// string Direction2DHisto =
//     " /media/victor93/Elements/Valcayne/ExperimentData_Outputs/2024_Er_Cu_U/"
//     "2DHistos/"
//     "v05/Histos01_";

string Direction2DHisto =
    " /home/victor93/CmExperimentFolder/2024_Er_U/ProgramsC6D6/Analysis_v01/DatosEnDiscoDuro/"
    "2DHistos/"
    "v08GainCorrected/Histos01_";

string DirectionSave2DHisto =
    "/media/victor93/Elements/Valcayne/ExperimentData_Outputs/2024_Er_Cu_U/"
    "ResultsPlot2DHisto/v05GainCorrected/";
string SaveYieldFolder = "/home/victor93/CmExperimentFolder/2024_Er_U/ProgramsC6D6/Analysis_v01/DatosEnDiscoDuro/Yield/v08/";

string WFFile =
    "/home/victor93/CmExperimentFolder/2024_Er_U/ProgramsC6D6/Analysis_v01/WF/"
    "Result_Er_2_25_CS10_v03/Final/WF_23Er_2_25.in";

double TOFD = 184;
// For subtract backgroudnS
vector<string> MeasPredefined = {"Predefined", "Au_2_Si"};
vector<string> BackgroundMeasPredefined = {"Background", "Background_Si"};
vector<string> DummyPredefined = {"Empty_Er", "Empty_Si"};
vector<string> BackgroundDummyPredefined = {
    "Background",
    "Background_Si",
};

/// For GetSimul
vector<string> NameSimulArray = {"Au_13_100", "Au_40_200", "Er167_13"};
vector<string> NameSimulRootfile = {"DataPlot/Yield_Au_2_100", "DataPlot/Yield_Au_2_200", "DataPlot/Yield_SAMMY_Er167_13mm"};

vector<string> NameSimulRootfile2 = {"DataPlot/Yield_Au_2_100", "DataPlot/Yield_Au_2_200", "DataPlot/Yield_TC_Er167_13mm_ENDF8_BKG"};
vector<string> NameSimulArrayEdep = {"Cs_1"};
vector<string> NameSimulRootfileEdep = {
    "/media/victor93/Elements/Valcayne/ExperimentData_Outputs/2024_Er_Cu_U/"
    "Simulations/v01/2024_Er_Cu_U_v01_Cs_1e7.root"};
vector<double> Activity_kBq = {274, 274};

vector<int> ResolNumberDetector = {1, 2, 3};
// vector<double> ResolParameter1 = {0.00152035, 0.00134748, 0.00018827};
// vector<double> ResolParameter2 = {0.0100738, 0.0034685, 0.00467216};

vector<double> ResolParameter1 = {0.00193404, 0.00187058, 0.00256307};
vector<double> ResolParameter2 = {0.00838911, 0.00181082, 0.00139247};

// En for integrals normalize
// double NormalizeMinEn = 100;
// double NormalizeMaxEn = 500;

double NormalizeMinEn = 1.001e1;
double NormalizeMaxEn = 0.999e2;

// En or the xaxis plot
double ForPlotEminEn = 0.02;
double ForPlotEmaxEn = 1.0e4;

// Edep for integrals normalize
double NormalizeMinEdep = 2.2e4;
double NormalizeMaxEdep = 4e4;

// Edep for the xaxis plot
double ForPlotEminEdep = 10;
double ForPlotEmaxEdep = 4e4;

// For the Y axis of compare
double MinYForCompare = 2.2e4;
double MaxYForCompare = 4e4;

// For calculating gain shifts

int NumberIterations = 400;
double MinShift = 0.8;
double MaxShift = 1.2;

#endif
