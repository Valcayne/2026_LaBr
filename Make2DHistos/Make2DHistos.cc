
#include "../GeneralFun/FillHistoFunctions.hh"

int main(int argc, char** argv) {
  bool IfGainCorrected = false;
  if (argc == 3) {
    cout << " ******* We create the 2DHistos with GainCorrected "
            "***************"
         << endl;
    IfGainCorrected = true;

  }

  else if (argc != 2) {
    cout << " ******* Input has to be like: Make2DHisto [RunNumber] "
            "***************"
         << endl;
    return 1;
  }

  int RunNumber = atoi(argv[1]);

  //==================================================================================
  /* HistoType
     1 Normal 2D (En/Edep)
     2 Similar to 1 but with TOF (TOF/Edep)
     3 Save the TFlash values
     4 Save the DeltaTime; The difference in time with the preovious count in
     the detector.  (Delta/TOF )
     5 Normal 2D (En/Edep) with WF d
     6 Save the  DetectorDeadTime_ns so I can recover it to plot the 2DHistos
     7 Normal 2D   (En/Edep) with Events
     8  Save the DeltaTime; The difference in time with the reference detector
     with Edep
     9  Save the DeltaTime; The difference in time with the reference
     detector with En
     10 11 12 are to perform coincidendes between detectors.
     13 Normal 2D   (En/Edep) with Events and WF

     */
  // Test
  char outdir2DHistos[1000];
  char CalibDirName2DHistos[1000];
  sprintf(outdir2DHistos, outdir);
  sprintf(CalibDirName2DHistos, CalibDirName);

  if (IfGainCorrected) {
    sprintf(outdir2DHistos, outdirGainCorrected);
    sprintf(CalibDirName2DHistos, CalibDirNameGainCorrected);
  }

  bool WFDefine = false;

  WFDefine = true;

  //==================================================================================

  std::vector<HistoInfo>* HistoInfos = new std::vector<HistoInfo>();

  // Define C6D6
  HistoInfos->emplace_back();
  HistoInfos->back().DetectorName = "LABR";
  HistoInfos->back().UseAreaInsteadOfAmplitude = {true};  // in ns

  HistoInfos->back().DetectorNumber = {0,  1,  2,  3,  4,  5,  6,  7,  8, 9,
                                       10, 11, 12, 13, 14, 15, 16, 17, 18};
  HistoInfos->back().DetectorDeadTime_ns = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  HistoInfos->back().HistoName.push_back("Edep");
  HistoInfos->back().HistoTitle.push_back("Edep");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1.1e2, 1.e-3, 1.e8});
  HistoInfos->back().Yaxis.push_back({1e4, 0, 10});  /// dive b y 5
  // HistoInfos->back().Yaxis.push_back({2e4, 0, 2e4});

  HistoInfos->back().HistoName.push_back("En");
  HistoInfos->back().HistoTitle.push_back("En");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1.9e5, 1.e-2, 1.e8});
  HistoInfos->back().Yaxis.push_back(
      {0.1, 0.12, 0.15, 0.3, 0.4, 0.45, 0.5, 0.55, 1, 1.5, 2.0, 5, 10, 20});

  // Define FC-U
  HistoInfos->emplace_back();
  HistoInfos->back().DetectorName = "FC-U";
  HistoInfos->back().DetectorNumber = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  HistoInfos->back().DetectorDeadTime_ns = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  HistoInfos->back().UseAreaInsteadOfAmplitude = {false};  //

  HistoInfos->back().HistoName.push_back("Edep");
  HistoInfos->back().HistoTitle.push_back("Edep");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1e1, 1.e-3, 1.e7});
  HistoInfos->back().Yaxis.push_back({2e4, 0, 1e5});

  HistoInfos->back().HistoName.push_back("En");
  HistoInfos->back().HistoTitle.push_back("En");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1e3, 1.e-3, 1.e7});
  HistoInfos->back().Yaxis.push_back({2e2, 0, 1e5});

  // Define FC-U
  HistoInfos->emplace_back();
  HistoInfos->back().DetectorName = "FC-B";
  HistoInfos->back().DetectorNumber = {
      0,
      1,
      2,
  };
  HistoInfos->back().DetectorDeadTime_ns = {0, 0, 0};
  HistoInfos->back().UseAreaInsteadOfAmplitude = {false};  //

  HistoInfos->back().HistoName.push_back("Edep");
  HistoInfos->back().HistoTitle.push_back("Edep");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1e1, 1.e-3, 1.e7});
  HistoInfos->back().Yaxis.push_back({2e4, 0, 1e5});

  HistoInfos->back().HistoName.push_back("En");
  HistoInfos->back().HistoTitle.push_back("En");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1e3, 1.e-3, 1.e7});
  HistoInfos->back().Yaxis.push_back({2e2, 0, 1e5});

  // Define SILI
  HistoInfos->emplace_back();
  HistoInfos->back().DetectorName = "SILI";
  HistoInfos->back().DetectorNumber = {0, 1, 2, 3, 4};
  HistoInfos->back().DetectorDeadTime_ns = {0, 0, 0, 0, 0};

  HistoInfos->back().HistoName.push_back("Edep");
  HistoInfos->back().HistoTitle.push_back("Edep");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1e1, 1.e-3, 1.e7});
  HistoInfos->back().Yaxis.push_back({2e4, 0, 1e5});

  HistoInfos->back().HistoName.push_back("En");
  HistoInfos->back().HistoTitle.push_back("En");
  HistoInfos->back().HistoType.push_back(1);
  HistoInfos->back().Xaxis.push_back({1e3, 1.e-3, 1.e7});
  HistoInfos->back().Yaxis.push_back({2e2, 0, 1e5});

  int const N_PULSETYPE =
      4;  // All, Dedicated, Parasitic, Other
          //==============================================================================
  //==============================================================================

  //==============================================================================
  //==============================================================================

  // Get data file:
  char infname[1000];
  sprintf(infname, "%s/run%d.root", EOSPATH, RunNumber);
  TFile* f1 = new TFile(infname, "READ");
  if (f1->IsZombie()) {
    cout << " ################# ERROR: FILE " << infname
         << " does not exist  #################" << endl;
    return 1;
  }
  cout << "RootFile= " << infname << endl;
  //==============================================================================
  //==============================================================================

  // Output files:
  cout << " Creating output files ..." << endl;
  char outrootfname[1000];
  // char outtxtfname[1000];
  sprintf(outrootfname, "%s/Histos01_%d.root", outdir2DHistos, RunNumber);
  // sprintf(outtxtfname, "%s/Histo01_%d.txt", outdir, RunNumber);
  TFile* fout = new TFile(outrootfname, "RECREATE");
  // ofstream out(outtxtfname);
  // out << " RUN " << RunNumber << endl;

  //==============================================================================
  //==============================================================================

  // Init PKUP objects:
  cout << "Start PKUP" << endl;
  //-----------------------------------------------
  PKUPInfo* thePKUPInfo = new PKUPInfo();
  TakePKUPInfo(infname, thePKUPInfo);
  int nbunches = thePKUPInfo->npulses;  ///
  //-----------------------------------------------

  // Calibrate all detectors:
  CalibrationManager* theCalibM =
      new CalibrationManager(CalibDirName2DHistos, RunListFname, RunNumber);
  // theCalibM->PrintData(outtxtfname);
  //==============================================================================
  //==============================================================================
  if (WFDefine) {
    theCalibM->CalibrationManagerWF(WFFolder, RunListFname, RunNumber, 0);
  }

  // Suponiendo que ya tienes:
  // std::vector<HistoInfo> *HistoInfos = new std::vector<HistoInfo>();

  // Vectores para manejar los datos de cada detector
  std::vector<TTree*> trees(HistoInfos->size(), nullptr);
  std::vector<bool> ThereIsDetector(HistoInfos->size(), false);
  std::vector<string> ThereIsNameDetector(HistoInfos->size(), "0");

  std::vector<int> nbunchesDet(HistoInfos->size(), 0);
  std::vector<Long64_t*> bunchesIndex(HistoInfos->size(), nullptr);
  std::vector<int*> BunchNumber(HistoInfos->size(), nullptr);
  std::vector<Signal> theSignals(HistoInfos->size());
  std::vector<Signal*> theSignalsArray(HistoInfos->size(), nullptr);
  std::vector<Event*> theEvents(HistoInfos->size(), nullptr);

  std::vector<FullEvent*> theFullEvents(HistoInfos->size(), nullptr);
  std::vector<int> NSignals(HistoInfos->size(), 0);
  std::vector<int> NEvents(HistoInfos->size(), 0);

  // Loop sobre todos los detectores
  for (int i = 0; i < HistoInfos->size(); ++i) {
    HistoInfo& info = HistoInfos->at(i);

    // Obtener el TTree del detector
    trees[i] = (TTree*)f1->Get(info.DetectorName.c_str());
    if (trees[i] != nullptr) {
      cout << "There is " << info.DetectorName << endl;
      ThereIsDetector[i] = true;
      ThereIsNameDetector[i] = info.DetectorName;

      // Reservar memoria para bunches
      bunchesIndex[i] = new Long64_t[MAXNBUNCHESINFILE];
      BunchNumber[i] = new int[MAXNBUNCHESINFILE];
      nbunchesDet[0] = 0;
      nbunchesDet[i] =
          CreateBunchesIndex(trees[i], bunchesIndex[i], BunchNumber[i]);

      // Asociar la estructura Signal
      AttachStruct(&theSignals[i], trees[i], info.UseAreaInsteadOfAmplitude);

      // Crear array dinámico de señales
      theSignalsArray[i] = new Signal[MAXNSIGNALSINPULSE];

      // Si el detector necesita eventos y full events
      theEvents[i] = new Event[MAXNSIGNALSINPULSE];
      theFullEvents[i] = new FullEvent[MAXNSIGNALSINPULSE];
    } else {
      cout << "There is not " << info.DetectorName << endl;
    }
  }
  // for (size_t i = 0; i < HistoInfos->size(); ++i) {
  //   if (!(std::find(ThereIsNameDetector.begin(), ThereIsNameDetector.end(),
  //                   HistoInfos->at(i).DetectorName) !=
  //         ThereIsNameDetector.end())) {
  //     cout << endl
  //          << "Delete " << HistoInfos->at(i).DetectorName << " At histo
  //          infos"
  //          << endl;

  //     HistoInfos->erase(HistoInfos->begin() + i);
  //   }
  // }
  //==============================================================================
  //==============================================================================

  cout << " Creating histograms ..." << endl;

  // Pulse intensity histograms:
  TH1D* hPulIntens[N_PULSETYPE * 2];
  CreateTH1DHistoPulseIntesity(hPulIntens, N_PULSETYPE, fout);

  // C6D6 histos

  std::vector<TH2D****> h2D_detectors(
      HistoInfos->size());  // vector para guardar los histogramas

  for (size_t i = 0; i < HistoInfos->size(); ++i) {
    // bool thereIsDetector = HistoInfos->at(i).Exists;  // o la bandera que
    // tengas
    h2D_detectors[i] =
        new TH2D***[N_PULSETYPE];  // inicializa el array de punteros

    CreateTH2DHisto(ThereIsNameDetector, &HistoInfos->at(i), N_PULSETYPE,
                    h2D_detectors[i], fout);
  }
  /************************************************************************
   *************************************************************************
   ************************************************************************/
  std::vector<int> milestones = {1, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  size_t nextMilestone = 0;
  // Main loop:
  cout << "Starting main loop ..." << endl;
  for (int npul = 0; npul < nbunches; ++npul) {
    int PulseType = thePKUPInfo->pulseType[npul];
    int thisPulseType = 3;  // Other
    if (PulseType == DEDICATED_PULSES_ID) thisPulseType = 1;
    if (PulseType == PARASITIC_PULSES_ID) thisPulseType = 2;
    int progress = (npul + 1) * 100 / nbunches;
    // cout << npul << " " << progress << endl;
    // si hemos pasado el siguiente hito, lo mostramos
    if (nextMilestone < milestones.size() &&
        progress >= milestones[nextMilestone]) {
      std::cout << "Progress: " << milestones[nextMilestone] << " % "
                << "Pulsenumber " << npul << std::endl;
      ++nextMilestone;  // pasamos al siguiente
    }
    double TFlash = -1;
    if (thePKUPInfo->PulseIntensity[npul] < 1.e12) {
      TFlash = 0;
    }

    FillPulseIntensity(
        N_PULSETYPE, thisPulseType, thePKUPInfo->PulseIntensity[npul],
        thePKUPInfo->PKUPAmp[npul], thePKUPInfo->PKUPArea[npul], hPulIntens);

    for (size_t i = 0; i < HistoInfos->size(); ++i) {
      if (!ThereIsDetector[i]) continue;

      // cout << "Detector " << HistoInfos->at(i).DetectorName << endl;
      NSignals[i] = GetSignals(HistoInfos->at(i).DetectorName,
                               HistoInfos->at(i).DetectorDeadTime_ns, trees[i],
                               &theSignals[i], bunchesIndex[i][npul],
                               bunchesIndex[i][npul + 1] - 1,
                               theSignalsArray[i], theCalibM, 1, TFlash);

      if (theEvents[i] != nullptr) {
        NEvents[i] = MakeCoincidences(
            NSignals[i], theSignalsArray[i], theEvents[i], TFlash,
            HistoInfos->at(i).CoincidenceWindow, theFullEvents[i]);
      }
      // Llamadas a FillType1..FillType8 según el detector
      // Puedes hacer un switch según DetectorType o algún flag dentro de
      // HistoInfo

      FillType1(thisPulseType, NSignals[i], theSignalsArray[i],
                h2D_detectors[i], -1.e20, 1.e20, &HistoInfos->at(i));

      FillType2(thisPulseType, NSignals[i], theSignalsArray[i],
                h2D_detectors[i], -1.e20, 1.e20, &HistoInfos->at(i));

      FillType3(thisPulseType, NSignals[i], theSignalsArray[i],
                h2D_detectors[i], -1.e20, 1.e20, &HistoInfos->at(i));

      FillType4(thisPulseType, NSignals[i], theSignalsArray[i],
                h2D_detectors[i], -1.e20, 1.e20, &HistoInfos->at(i));
      FillType5(thisPulseType, NSignals[i], theSignalsArray[i],
                h2D_detectors[i], -1.e20, 1.e20, &HistoInfos->at(i));

      FillType6(thisPulseType, NSignals[i], theSignalsArray[i],
                h2D_detectors[i], -1.e20, 1.e20, &HistoInfos->at(i));

      FillType7(thisPulseType, NEvents[i], theEvents[i], h2D_detectors[i],
                -1.e20, 1.e20, &HistoInfos->at(i));
      FillType8(thisPulseType, NEvents[i], theFullEvents[i], h2D_detectors[i],
                -1.e20, 1.e20, &HistoInfos->at(i));
      FillType9(thisPulseType, NEvents[i], theFullEvents[i], h2D_detectors[i],
                -1.e20, 1.e20, &HistoInfos->at(i));

      FillType10(thisPulseType, NEvents[i], NEvents, theFullEvents, i,
                 h2D_detectors[i], -1.e20, 1.e20, *HistoInfos,
                 ThereIsNameDetector);
      FillType11(thisPulseType, NEvents[i], NEvents, theFullEvents, i,
                 h2D_detectors[i], -1.e20, 1.e20, *HistoInfos,
                 ThereIsNameDetector);
      FillType12(thisPulseType, NEvents[i], NEvents, theFullEvents, i,
                 h2D_detectors[i], -1.e20, 1.e20, *HistoInfos,
                 ThereIsNameDetector);
      FillType13(thisPulseType, NEvents[i], theEvents[i], h2D_detectors[i],
                 -1.e20, 1.e20, &HistoInfos->at(i));
    }
  }

  cout << " ... end main loop" << endl;

  //==============================================================================
  //==============================================================================

  // Write results:
  cout << " Writting results ..." << endl;
  fout->Write();
  fout->Close();
  delete fout;
  cout << " ... done" << endl;

  //==============================================================================
  //==============================================================================

  cout << " File " << outrootfname << " has been created " << endl;

  return 0;
}
