#ifndef DEFPLOT2DHISTO_2026_LABR_V01_HH
#define DEFPLOT2DHISTO_2026_LABR_V01_HH 1

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
string NameDetector = "FC-U";

bool CorrectDeadTime = false;
bool UseSiliCountsInsteadOfProtons = false;
double FactorToMultyplySiliCountsToProtons =
    402789675373.926581347;  // value calculated for 23Er_2_1000, so I do not
                             // have to calculate the normalization again with
                             // CountsGainCorrected

double TOFD = 183.88;
// For subtract backgroudnSasd
vector<string> MeasPredefined = {
    "Predefined",
};
vector<string> BackgroundMeasPredefined = {"Background_Det1_8"};
vector<string> DummyPredefined = {"Empty"};
vector<string> BackgroundDummyPredefined = {"Background_Det1_8"};

// For GetSimul
vector<string> NameSimulArray = {"Au25"};
vector<string> NameSimulRootfile = {
    "DataPlot/Yield_Sn_Au_645mg_radius1",
};

vector<vector<string>> NameSimulRootfile2 = {
    // Vector 0
    {
        "-1",
    },
    // Vector 1
    {"-1"},
    // Vector 2
    {
        "-1",
    },
    // Vector 3
    {
        "-1",
    },
    // Vector 4
    {
        "-1",
    },
    // Vector 5
    {
        "-1",
    },
    // Vector 6
    {
        "-1",
    }};

vector<string> NameSimulArrayEdep = {
    "Cs_2",
    "Co",
    "Mn",
};

vector<string> NameSimulRootfileEdep = {
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Cs_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"};

vector<double> Activity_kBq = {
    282, 17.4, 4.02, 9.27, 31.5, 16.4, 1, 1, 10.05, 237.38, 1, 1, 1, 1,
    1,   1,    1,    1,    1,    1,    1, 1, 1,     1,      1, 1, 1, 1};

vector<int> ResolNumberDetector = {1, 2, 3, 4};

// Values V02 2026_Sm
vector<double> ResolParameter1 = {0.00270311, 0.00259213, 0.00264867,
                                  0.00184269};
vector<double> ResolParameter2 = {0.00298827, 0.00940934, 0.00209685,
                                  0.00304363};

double NormalizeMinEn = 100;
double NormalizeMaxEn = 1000;

double ForPlotEminEn = 2e-2;
double ForPlotEmaxEn = 1e8;

double NormalizeMinEdep = 0.6;
double NormalizeMaxEdep = 0.7;

double ForPlotEminEdep = 0.1;
double ForPlotEmaxEdep = 1e5;

// For the Y axis of compare
double MinYForCompare = 0.1;
double MaxYForCompare = 2;

// For calculating gain shifts

int NumberIterations = 50;
double MinShift = 0.9;
double MaxShift = 1.1;

#endif
