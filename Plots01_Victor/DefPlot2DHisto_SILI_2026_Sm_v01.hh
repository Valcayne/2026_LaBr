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
bool UseSiliCountsInsteadOfProtons = false;
double FactorToMultyplySiliCountsToProtons =
    402789675373.926581347;  // value calculated for 23Er_2_1000, so I do not
                             // have to calculate the normalization again with
                             // CountsGainCorrected

double TOFD = 183.88;
// For subtract backgroudnSasd
vector<string> MeasPredefined = {"AllRuns_NoFilters"};
vector<string> BackgroundMeasPredefined = {"Background"};
vector<string> DummyPredefined = {"AllRuns_NoFilters"};
vector<string> BackgroundDummyPredefined = {"Background"};

// For GetSimul
vector<string> NameSimulArray = {"1"};
vector<string> NameSimulRootfile = {"1"};

vector<vector<string>> NameSimulRootfile2 = {{"1"}};

vector<string> NameSimulArrayEdep = {"1"};

vector<string> NameSimulRootfileEdep = {"1"};

vector<double> Activity_kBq = {1};

vector<int> ResolNumberDetector = {1, 2, 3, 4};

// Values V02 2026_Sm
vector<double> ResolParameter1 = {0.00220787, 0.00192447, 0.00325949,
                                  0.00331343};
vector<double> ResolParameter2 = {0.00195622, 0.00287341, 0.00200706,
                                  0.00913615};

// double NormalizeMinEn = 11.0e3;
// double NormalizeMaxEn = 11.2e3;
//

double NormalizeMinEn = 10;
double NormalizeMaxEn = 100;

// En or the xaxis plot
// double ForPlotEminEn = 0.02;
// double ForPlotEmaxEn = 1e6;
double ForPlotEminEn = 1e-3;
double ForPlotEmaxEn = 1e4;
// Edep for integrals normalize
double NormalizeMinEdep = 14000;
double NormalizeMaxEdep = 30000;

// Edep for the xaxis plot
double ForPlotEminEdep = 0.1;
double ForPlotEmaxEdep = 35000;

// For the Y axis of compare
double MinYForCompare = 0.1;
double MaxYForCompare = 2;

// For calculating gain shifts

int NumberIterations = 200;
double MinShift = 0.9;
double MaxShift = 1.1;

#endif
