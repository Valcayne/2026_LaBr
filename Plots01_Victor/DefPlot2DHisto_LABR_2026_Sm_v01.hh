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
string NameDetector = "LABR";

bool CorrectDeadTime = false;
bool UseSiliCountsInsteadOfProtons = false;
double FactorToMultyplySiliCountsToProtons =
    402789675373.926581347;  // value calculated for 23Er_2_1000, so I do not
                             // have to calculate the normalization again with
                             // CountsGainCorrected

double TOFD = 183.88;
// For subtract backgroudnSasd
vector<string> MeasPredefined = {
    "Predefined",     "Empty_Er",       "PbNat_2mm",      "Pb208_1mm",
    "Sm147_Thick_Al", "Sm149_Thick_Al", "Sm152_Thick_Al", "Er164_Thick_Al",
    "Sm147_Thick_Bi", "Sm149_Thick_Bi", "Sm152_Thick_Bi",
};
vector<string> BackgroundMeasPredefined = {
    "Background_2", "Background",   "Background_2", "Background_2",
    "Background_2", "Background_2", "Background_2", "Background_2",
    "Background_2", "Background_2", "Background_2"};
vector<string> DummyPredefined = {
    "Empty",    "Empty_Er", "Empty",    "Empty",    "Empty_Al", "Empty_Al",
    "Empty_Al", "Empty_Al", "Empty_Bi", "Empty_Bi", "Empty_Bi"};
vector<string> BackgroundDummyPredefined = {
    "Background_2", "Background",   "Background_2", "Background_2",
    "Background_2", "Background_2", "Background_2", "Background_2",
    "Background_2", "Background_2", "Background_2"};

// For GetSimul
vector<string> NameSimulArray = {
    "Au25",        "Au_40_200",  "Ar",          "EmptyCapsule", "Pb-20-21",
    "Au-40-100",   "SbNat",      "Sb121",       "Sb123",        "Er164_Thick",
    "Er164_Thin",  "SmNat_5um",  "SmNat_Thick", "Sm147_Thick",  "Sm149_Thick",
    "Sm152_Thick", "SmNat_Thick"};
vector<string> NameSimulRootfile = {
    "DataPlot/Yield_Sn_Au_645mg_radius1",
    "DataPlot/Yield_Au_2_200",
    " DataPlot/Yield_Ar40_ENDF80_v01",
    "DataPlot/Yield_Ar40_ENDF80_v01",
    "DataPlot/Yield_Pb_2cm_7g",
    "DataPlot/Yield_Au_2_100",
    "DataPlot/Yield_SbNat_574mg",
    "DataPlot/Yield_Sb121_839mg",
    "DataPlot/Yield_Sb123_1091mg",
    "DataPlot/Yield_Er164_217mg_v01",
    "DataPlot/Yield_Er164_44.53mg_v01",
    "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm_All",
    "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm_All",
    "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm_All",
    "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm_All",
    "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm_All",
    "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm_All"};

vector<vector<string>> NameSimulRootfile2 = {
    // Vector 0
    {"-1", "DataPlot/Yield_Au_2_200", "DataPlot/Yield_Ar40_ENDF80_v01",
     "DataPlot/Ar-40Pre", "DataPlot/Yield_Pb_2cm_7g", "DataPlot/Yield_Au_2_100",
     "DataPlot/Yield_SbNat_574mg", "DataPlot/Yield_Sb121_839mg",
     "DataPlot/Yield_Sb123_1091mg", "DataPlot/Yield_Er164_217mg_v01_Er162",
     "DataPlot/Yield_Er164_44.53mg_Er164",
     "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm144",
     "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm144",
     "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm144",
     "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm144",
     "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm144",
     "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm144"},
    // Vector 1
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
     "DataPlot/Yield_Er164_217mg_v01_Er164",
     "DataPlot/Yield_Er164_44.53mg_Er166",
     "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm147",
     "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm147",
     "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm147",
     "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm147",
     "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm147",
     "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm147"},
    // Vector 2
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
     "DataPlot/Yield_Er164_217mg_v01_Er166",
     "DataPlot/Yield_Er164_44.53mg_Er167",
     "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm148",
     "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm148",
     "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm148",
     "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm148",
     "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm148",
     "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm148"},
    // Vector 3
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
     "DataPlot/Yield_Er164_217mg_v01_Er167",
     "DataPlot/Yield_Er164_44.53mg_Er168",
     "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm149",
     "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm149",
     "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm149",
     "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm149",
     "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm149",
     "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm149"},
    // Vector 4
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
     "DataPlot/Yield_Er164_217mg_v01_Er168",
     "DataPlot/Yield_Er164_44.53mg_Er170",
     "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm150",
     "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm150",
     "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm150",
     "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm150",
     "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm150",
     "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm150"},
    // Vector 5
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
     "DataPlot/Yield_Er164_217mg_v01_Er170",
     "DataPlot/Yield_Er164_44.53mg_v01_BKG",
     "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm152",
     "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm152",
     "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm152",
     "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm152",
     "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm152",
     "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm152"},
    // Vector 6
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
     "DataPlot/Yield_Er164_217mg_v01_Er170",
     "DataPlot/Yield_Er164_44.53mg_v01_BKG",
     "DataPlot/Yield_Sn_SmNat_14.68mg_radius1.25cm_v01_Sm154",
     "DataPlot/Yield_Sn_SmNat_315mg_13mm_v01_Sm154",
     "DataPlot/Yield_Sn_Sm147_339mg_13mm_v01_Sm154",
     "DataPlot/Yield_Sn_Sm149_339mg_13mm_v01_Sm154",
     "DataPlot/Yield_Sn_Sm152_898mg_13mm_v01_Sm154",
     "DataPlot/Yield_Sn_SmNat_884mg_13mm_v01_Sm154"}};

vector<string> NameSimulArrayEdep = {
    "Cs_2",        "Co",          "Mn",         "Co57_Det2_2", "Bi",
    "Ba_4",        "AmBe_2",      "CmC_2",      "Eu",          "Y_2",
    "Au",          "Au_40_200",   "Er167_13",   "Er166_13",    "U238",
    "Sm147_Thick", "Sm149_Thick", "Sm152_Thick"};

vector<string> NameSimulRootfileEdep = {
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Cs_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Co_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Mn_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Co57_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Bi_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Ba_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_AmBe_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_CmC_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Eu_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v02/2024_Er_Cu_U_Y_1e7.root",
    " /home/victor93/ExperimentsData//2024_Er_Cu_U/Simulations/v03/Au_13/"
    "2024_Er_Cu_U_Au_13_CS10_TW30ns_Cas_Au197-01_25_1e6_1e8.root ",
    " /home/victor93/ExperimentsData//2024_Er_Cu_U/Simulations/v03/Au_13/"
    "2024_Er_Cu_U_Au_13_CS10_TW30ns_Cas_Au197-01_25_1e6_1e8.root ",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v01/2024_Er_Cu_U_v01_Er167_v02_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v01/2024_Er_Cu_U_v01_Er166_v02_1e8.root",
    "/home/victor93/ExperimentsData//2024_Er_Cu_U/"
    "Simulations/v01/2024_Er_Cu_U_U238_LowCs_1e6.root ",
    "/home/victor93/ExperimentsData//2026_Sm/Simulations/v01/Sm_25/"
    "2026_Sm_Sm_25_CS10_TW30ns_Cas_Sm147_1e6_1e7.root",
    "/home/victor93/ExperimentsData//2026_Sm/Simulations/v01/Sm_25/"
    "2026_Sm_Sm_25_CS10_TW30ns_Cas_Sm149_NoPrimary_1e6_1e7.root",
    "/home/victor93/ExperimentsData//2026_Sm/Simulations/v01/Sm_25/"
    "2026_Sm_Sm_25_CS10_TW30ns_Cas_Sm152_NoPrimary_1e6_1e8.root",
};

vector<double> Activity_kBq = {
    282, 17.4, 4.02, 9.27, 31.5, 16.4, 1, 1, 10.05, 237.38, 1, 1, 1, 1,
    1,   1,    1,    1,    1,    1,    1, 1, 1,     1,      1, 1, 1, 1};

vector<int> ResolNumberDetector = {1, 2, 3, 4};
// vector<double> ResolParameter1 = {0.00152035, 0.00134748, 0.00018827};
// vector<double> ResolParameter2 = {0.0100738, 0.0034685, 0.00467216};

// vector<double> ResolParameter1 = {0.00193404, 0.00187058, 0.00256307};
// vector<double> ResolParameter2 = {0.00838911, 0.00181082, 0.00139247};

// vector<double> ResolParameter1 = {0.00329717, 0.00285433,
// 0.00136088,0.00211402}; vector<double> ResolParameter2 = {0.00215909,
// 0.0030931, 0.00293019, 0.0105527};

// vector<double> ResolParameter1 = {0.00258232, 0.00227249, 0.00167079,
//                                   0.00371062};
// vector<double> ResolParameter2 = {0.00233583, 0.00225643, 0.00221157,
// 0.008693};

// // Resolution for v05
// vector<double> ResolParameter1 = {0.00230012, 0.00273878, 0.00195789,
// 0.0018448}; vector<double> ResolParameter2 = {0.00237909, 0.00202048,
// 0.00211079, 0.0107645};

// vector<double> ResolParameter1 = {0.00230012, 0.00273878, 0.00195789,
// 0.00333743}; vector<double> ResolParameter2 = {0.00237909, 0.00202048,
// 0.00211079, 0.00877844};

// // Resolution for v08
// vector<double> ResolParameter1 = {0.00272027, 0.00273878, 0.00195789,
// 0.00194601}; vector<double> ResolParameter2 = {0.00195347, 0.00202048,
// 0.00211079, 0.00781076};
// // Resolution for v08

// vector<double> ResolParameter1 = {0.00272027, 0.00273878, 0.00195789,
//                                   0.00194601};
// vector<double> ResolParameter2 = {0.00195347, 0.00202048, 0.00211079,
//                                   0.00781076};
// Values V02 2026_Sm
vector<double> ResolParameter1 = {0.00270311, 0.00259213, 0.00264867,
                                  0.00184269};
vector<double> ResolParameter2 = {0.00298827, 0.00940934, 0.00209685,
                                  0.00304363};
// 1 0.00230012  0.00237909
// 4 0.0018448  0.0107645
// 3 0.00195789  0.00211079
// 2 0.00273878  0.00202048

// En for integrals normalize
// double NormalizeMinEn = 100;
// double NormalizeMaxEn = 500;

// double NormalizeMinEn = 7.0;
// double NormalizeMaxEn = 8.5;

double NormalizeMinEn = 100;
double NormalizeMaxEn = 1000;
//   En or the xaxis plot
//   double ForPlotEminEn = 0.02;
//   double ForPlotEmaxEn = 1e6;
double ForPlotEminEn = 2e-2;
double ForPlotEmaxEn = 1e6;
//    double ForPlotEminEn = 3;
// double ForPlotEmaxEn = 7;
// Edep for integrals normalize
double NormalizeMinEdep = 0.2;
double NormalizeMaxEdep = 0.8;

// Edep for the xaxis plot
double ForPlotEminEdep = 0.1;
double ForPlotEmaxEdep = 8;

// For the Y axis of compare
double MinYForCompare = 0.1;
double MaxYForCompare = 2;

// For calculating gain shifts

int NumberIterations = 200;
double MinShift = 0.98;
double MaxShift = 1.02;

#endif
/*


 ForPlotEminEn = 11e3;
 ForPlotEmaxEn = 11.25e3;
 plot2D({"En_WF","En"}, {"Ar"}, {0}, {0.150}, {9.999}, {1}, "Yield",
{2},true,true,true);
SaveRootEpsPngTxt(c1,"ResultsPlot/Ar/2025_EAR1_WF_NoWF_11_v02")


 ForPlotEminEn = 17.7e3;
 ForPlotEmaxEn = 18.1e3;
 plot2D({"En_WF","En"}, {"Ar"}, {0}, {0.150}, {9.999}, {1}, "Yield",
{2},true,true,true);
SaveRootEpsPngTxt(c1,"ResultsPlot/Ar/2025_EAR1_WF_NoWF_17_v02")

 ForPlotEminEn = 58.7e3;
 ForPlotEmaxEn = 61.1e3;
 plot2D({"En_WF","En"}, {"Ar"}, {0}, {0.150}, {9.999}, {1}, "Yield",
{2},true,true,true);
SaveRootEpsPngTxt(c1,"ResultsPlot/Ar/2025_EAR1_WF_NoWF_59_60_v02")

ForPlotEminEn =70e3;
 ForPlotEmaxEn = 88.1e3;
 plot2D({"En_WF","En"}, {"Ar"}, {0}, {0.150}, {9.999}, {1}, "Yield",
{20},true,true,true);
SaveRootEpsPngTxt(c1,"ResultsPlot/Ar/2025_EAR1_WF_NoWF_70_v02")


 ForPlotEminEn = 85.7e3;
 ForPlotEmaxEn = 105.1e3;
 plot2D({"En_WF","En"}, {"Ar"}, {0}, {0.150}, {9.999}, {1}, "Yield",
{8},true,true,true);
SaveRootEpsPngTxt(c1,"ResultsPlot/Ar/2025_EAR1_WF_NoWF_90_105_v02")

 ForPlotEminEn = 140.7e3;
 ForPlotEmaxEn = 200.1e3;
 plot2D({"En_WF","En"}, {"Ar"}, {0}, {0.150}, {9.999}, {1}, "Yield",
{8},true,true,true);
SaveRootEpsPngTxt(c1,"ResultsPlot/Ar/2025_EAR1_WF_NoWF_140_200_v02")

 ForPlotEminEn = 200.7e3;
 ForPlotEmaxEn = 400.1e3;
 plot2D({"En_WF","En"}, {"Ar"}, {0}, {0.150}, {9.999}, {1}, "Yield",
{20},true,true,true);
SaveRootEpsPngTxt(c1,"ResultsPlot/Ar/2025_EAR1_WF_NoWF_200_400_v02")


*/
