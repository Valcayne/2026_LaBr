// #include "DefPlot2DHisto_SILI_2025_Ar_v01.hh"
#include "Plot2DHisto.cc"

void plot2DCompareWithRunType(int RunNumber);

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << " ########## Input has to be like:  RunNumber ########## " << endl;
    return 1;
  }
  plot2DCompareWithRunType(atoi(argv[1]));
}

void plot2DCompareWithRunType(int RunNumber) {
  int rebin = 10;
  string NameSaveEDEP, NameSaveEN, NameRunNumber, outdirGainCorrectedSTRING,
      OperationToCopy, OperationToDelete;
  Direction2DHisto = DirNameoutMerged;
  Direction2DHisto = Direction2DHisto + "/Histos01_";
  vector<string> RunString;
  string RunType = TakeRunType(RunListFname, RunNumber);

  RunString.push_back(to_string(RunNumber));
  RunString.push_back(RunType);
  if ((RunType != "AllRuns") && (RunNumber != 115785)) {
    vector<int> Detector;
    Detector.push_back(0);

    for (int detN = 0; detN <= 4; detN++) {
      Detector[0] = detN;
      outdirGainCorrectedSTRING = outdirGainCorrected;
      NameSaveEDEP = DirectionSave2DHistoCONDOR + "/CompareWithRunType/Det" +
                     to_string(detN) + "_" + to_string(RunNumber) + "_" +
                     RunType + "_Edep";
      NameSaveEN = DirectionSave2DHistoCONDOR + "/CompareWithRunType/Det" +
                   to_string(detN) + "_" + to_string(RunNumber) + "_" +
                   RunType + "_En";
      NameRunNumber = outdirGainCorrectedSTRING + "/Histos01_" +
                      to_string(RunNumber) + ".root";
      OperationToCopy = "cp " + NameRunNumber + " " + DirNameoutMerged;
      OperationToDelete = "rm ";
      OperationToDelete = OperationToDelete + DirNameoutMerged;

      OperationToDelete =
          OperationToDelete + "/Histos01_" + to_string(RunNumber) + ".root";

      cout << endl << endl << "RunType " << RunType << endl << endl;
      cout << " doing.. " << OperationToCopy << endl;
      system(OperationToCopy.c_str());
      ForPlotEmaxEdep = 10;
      ForPlotEminEdep = 0.1;

      plot2D({"Edep"}, RunString, Detector, {0.01}, {1e4}, {0}, "CPulse", rebin,
             false, false, false, true, NameSaveEDEP);
      plot2D({"En"}, RunString, Detector, {0.15}, {9.99}, {1}, "CP", rebin * 10,
             false, false, false, true, NameSaveEN);
      cout << " doing.. " << OperationToDelete << endl;
      system(OperationToDelete.c_str());
    }
  }
}
