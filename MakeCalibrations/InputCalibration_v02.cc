
#include "../GeneralFun/MakeCalibrationFunctions.hh"
// int main(int argc, char** argv);
// void MakeEnergyCalibration_2024_Test_L6D6() {
int main(int argc, char** argv) {
  //  int Plot(){

  cout << "starting    " << endl;

  // Sources and detectors calibrated
  std::vector<string> SourcesCalibrated = {"Cs", "Y1", "Y2", "AmBe", "CmC"};

  std::vector<int> DetectorsCalibrated = {1, 2, 3, 4};

  // Information MC

  string MCEndFile = "_1e7.root";
  string MCfname;

  // Information experimental data

  string FolderRootFiles = EOSPATH;
  int PositionArraySourceThatMatch = -1;
  string Expfname;
  string ExpfnameBackground;
  int NumberBinsExpfname = 2e4;
  double EMaxExpfname = 1e5;

  // Information outputfolder
  string ArgumentsCondor = "Condor/Inputs/ArgumentsForCondor.txt";

  // Information calibration sources
  string BackgroundType = "Background_2";
  std::vector<string> Source = {"Cs", "Bi1", "Bi2", "AmBe", "Y1",
                                "Y2", "Co",  "Ba",  "CmC",  "Mn"};
  std::vector<string> SourceType = {"Cs_2", "Bi_2", "Bi_2", "AmBe_2", "Y_2",
                                    "Y_2",  "Co_2", "Ba_2", "CmC_2",  "Mn_2"};
  std::vector<string> SourceTypeSimulation = {"Cs", "Bi", "Bi", "AmBe", "Y",
                                              "Y",  "Co", "Ba", "CmC",  "Mn"};
  //  std::vector<double> Percen = {30, 25, 20, 13, 20, 30, 30, 30, 20, 20};

  std::vector<double> Percen = {30, 30, 20, 13, 20, 30, 30, 40, 20, 20};

  std::vector<double> GammaEnergy = {0.661657, 0.569698, 1.063656, 4.438,
                                     0.89804,  1.836063, 1.173,    0.356012,
                                     6.130,    0.834848};
  std::vector<int> Rebin = {2, 2, 2, 8, 2, 4, 4, 1, 16, 4};

  bool LaunchFitPoints = true;
  // Parameters for fitting
  int GeneralRebin = 1;
  string NameoutputFile;
  int npRes = 100;  // Number points resolution
  npRes = 50;
  double Res = 0.2;    // Resolution val ue
  double PERRes = 80;  // Percentage variation resolution. The range tested is
                       //   [Res-Res*PERRes, Res+Res*PERRes]
  int npCalib = 200;   // Number of points calibration adf
  npCalib = 50;
  double Calib[(int)DetectorsCalibrated.size()] = {
      0.00032,
      0.00032,
      0.00032,
      0.00032,
  };  // Calibration value
  double PERCalib = 20;  // Percentage variation calibratio. The range tested is
                         // [Calib-Calib*PERCalib, Calib+Calib*PERCalib]

  if (((int)Source.size() == (int)SourceType.size() ==
       (int)SourceTypeSimulation.size() == (int)Percen.size() ==
       (int)GammaEnergy.size())) {
    cout << (int)Source.size() << " " << (int)SourceType.size() << " "
         << (int)Percen.size() << " " << (int)GammaEnergy.size() << endl;
    cout << " ######## Error in " << __FILE__ << ", line " << __LINE__
         << " ########" << endl;
    exit(1);
  }

  cout << "start for" << endl;
  ofstream outdata(ArgumentsCondor);
  for (int j = 0; j < (int)DetectorsCalibrated.size(); j++) {
    for (int i = 0; i < (int)SourcesCalibrated.size(); i++) {
      for (size_t k = 0; k < Source.size(); ++k) {
        // cout << Source[k] << " " << SourcesCalibrated[i] << endl;
        if (Source[k] == SourcesCalibrated[i]) {
          PositionArraySourceThatMatch = k;
          break;
        }
      }
      if (PositionArraySourceThatMatch == -1) {
        cout << " ######## Error in " << __FILE__ << ", line " << __LINE__
             << " ########" << endl;
        exit(1);
      }
      NameoutputFile = outFolder + "/Calibration_Det" +
                       to_string(DetectorsCalibrated[j]) + "_" +
                       SourcesCalibrated[i] + ".root";
      if (!FileExists(NameoutputFile)) {
        // cout << NameoutputFile << " exists" << endl;
        LaunchFitPoints = false;
        MCfname = MCFolder +
                  SourceTypeSimulation[PositionArraySourceThatMatch] +
                  MCEndFile;
        Expfname = DataFolder + "/Amp_Det" + to_string(DetectorsCalibrated[j]) +
                   "_" + SourceType[PositionArraySourceThatMatch] + ".root";
        ExpfnameBackground = DataFolder + "/Amp_Det" +
                             to_string(DetectorsCalibrated[j]) + "_" +
                             BackgroundType + ".root";
        outdata << SourcesCalibrated[i] << " " << DetectorsCalibrated[j] << "  "
                << SourceType[PositionArraySourceThatMatch] << "  "
                << DataFolder << "  " << RunListFname << "  " << FolderRootFiles
                << "  " << Expfname << "  " << ExpfnameBackground << "  "
                << BackgroundType << "  " << NumberBinsExpfname << "  "
                << EMaxExpfname << "  " << MCfname << "  " << outFolder << "  "
                << GammaEnergy[PositionArraySourceThatMatch] << "  "
                << Rebin[PositionArraySourceThatMatch] << "  "
                << Percen[PositionArraySourceThatMatch] << "  " << npRes << "  "
                << Res << "  " << PERRes << "  " << npCalib << "  " << Calib[j]
                << "  " << PERCalib << endl;
        cout << endl
             << "Launch " << SourcesCalibrated[i] << " "
             << DetectorsCalibrated[j] << "  " << endl;

        cout << "MakeEnergyCalibration " << SourcesCalibrated[i] << " "
             << DetectorsCalibrated[j] << "  "
             << SourceType[PositionArraySourceThatMatch] << "  " << DataFolder
             << "  " << RunListFname << "  " << FolderRootFiles << "  "
             << Expfname << "  " << ExpfnameBackground << "  " << BackgroundType
             << "  " << NumberBinsExpfname << "  " << EMaxExpfname << "  "
             << MCfname << "  " << outFolder << "  "
             << GammaEnergy[PositionArraySourceThatMatch] << "  "
             << Rebin[PositionArraySourceThatMatch] << "  "
             << Percen[PositionArraySourceThatMatch] << "  " << npRes << "  "
             << Res << "  " << PERRes << "  " << npCalib << "  " << Calib[j]
             << "  " << PERCalib << endl;

        // cout << SourceType[PositionArraySourceThatMatch] << "  " <<
        // DataFolder
        //    << "  " << RunListFname << "  " << FolderRootFiles << "  " <<
        //    Expfname
        //  << "  " << ExpfnameBackground << "  " << BackgroundType << "  "
        // << NumberBinsExpfname << "  " << EMaxExpfname << "  " << MCfname
        //<< "  " << outFolder << "  "
        //<< GammaEnergy[PositionArraySourceThatMatch] << "  "
        //<< Rebin[PositionArraySourceThatMatch] << "  "
        //<< Percen[PositionArraySourceThatMatch] << "  " << npRes << "  "
        //<< Res << "  " << PERRes << "  " << npCalib << "  " << Calib
        //<< "  " << PERCalib << endl;
      }
    }

    if (LaunchFitPoints) {
      NameoutputFile =
          outFolder + "/DataDet" + to_string(DetectorsCalibrated[j]) + ".out";
      if (!FileExists(NameoutputFile)) {
        cout << "FitPoints for " << DetectorsCalibrated[j] << endl;

        outdata << DetectorsCalibrated[j] << " " << outFolder << "  " << endl;
        string LaunchFits = "MakeEnergyCalibration " +
                            to_string(DetectorsCalibrated[j]) + " " + outFolder;
        cout << LaunchFits << endl;
        // system(LaunchFits.c_str());
      } else {
        cout << "File " << NameoutputFile
             << " exits so the calibration is finished" << endl;
      }
    }
  }
  outdata.close();

  system(
      "condor_submit "
      "Condor/ProgramsLaunch/LaunchCondorMakeEnergyCalibration.sh");
}
