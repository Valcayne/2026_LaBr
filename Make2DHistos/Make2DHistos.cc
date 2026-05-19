
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

  // HistoType
  //  1 Normal 2D (En/Edep)
  //  2 Similar to 1 but with TOF (TOF/Edep)
  //  3 Save the TFlash values
  //  4 Save the DeltaTime; The difference in time with the preovious detector.
  //  (Delta/TOF )
  //  5 Normal 2D (En/Edep) with WF d
  //  6 Save the DetectorDeadTime_ns so I can recover it to plot the 2DHistos

  // Test
  //==================================================================================

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

  HistoInfo* HistoInfoC6D6 = new HistoInfo();

  HistoInfoC6D6->DetectorName = "C6D6";
  HistoInfoC6D6->DetectorNumber = {0, 1, 2, 3, 4};
  HistoInfoC6D6->DetectorDeadTime_ns = {0, 0, 0, 0, 0};

  HistoInfoC6D6->HistoName.push_back("Edep");
  HistoInfoC6D6->HistoTitle.push_back("Edep");
  HistoInfoC6D6->HistoType.push_back(1);
  HistoInfoC6D6->Xaxis.push_back({1e3, 1.e-3, 1.e7});
  // HistoInfoC6D6->Yaxis.push_back({2e4, 0, 20});
  HistoInfoC6D6->Yaxis.push_back({2e3, 0, 20});

  HistoInfoC6D6->HistoName.push_back("En");
  HistoInfoC6D6->HistoTitle.push_back("En");
  HistoInfoC6D6->HistoType.push_back(1);

  HistoInfoC6D6->Xaxis.push_back({1.8e5, 1.e-2, 1.e7});
  HistoInfoC6D6->Yaxis.push_back({0.12, 0.15, 0.3, 0.5, 1, 10, 20});
  if (IfGainCorrected) {
    HistoInfoC6D6->HistoName.push_back("Edep_WF");
    HistoInfoC6D6->HistoTitle.push_back("Edep_WF");
    HistoInfoC6D6->HistoType.push_back(5);
    HistoInfoC6D6->Xaxis.push_back({1e3, 1.e-3, 1.e7});
    // HistoInfoC6D6->Yaxis.push_back({2e4, 0, 20});
    HistoInfoC6D6->Yaxis.push_back({2e3, 0, 20});

    HistoInfoC6D6->HistoName.push_back("En_WF");
    HistoInfoC6D6->HistoTitle.push_back("En_WF");
    HistoInfoC6D6->HistoType.push_back(5);

    HistoInfoC6D6->Xaxis.push_back({1.8e5, 1.e-2, 1.e7});
    HistoInfoC6D6->Yaxis.push_back({0.12, 0.15, 10, 20});
  }
  HistoInfoC6D6->HistoName.push_back("TFlash");
  HistoInfoC6D6->HistoTitle.push_back("TFlash");
  HistoInfoC6D6->HistoType.push_back(3);
  HistoInfoC6D6->Xaxis.push_back({1e6, 0, 1.e6});
  HistoInfoC6D6->Yaxis.push_back({1, 0, 2});
  HistoInfoC6D6->HistoName.push_back("DeltaTOF");
  HistoInfoC6D6->HistoTitle.push_back("DeltaTOF");
  HistoInfoC6D6->HistoType.push_back(4);
  HistoInfoC6D6->Xaxis.push_back({1e4, 0, 1.e4});
  HistoInfoC6D6->Yaxis.push_back({400, 0, 20});

  HistoInfoC6D6->HistoName.push_back("DetectorDeadTime_ns");
  HistoInfoC6D6->HistoTitle.push_back("DetectorDeadTime_ns");
  HistoInfoC6D6->HistoType.push_back(6);
  HistoInfoC6D6->Xaxis.push_back({1, 0, 2});
  HistoInfoC6D6->Yaxis.push_back({1, 0, 2});

  HistoInfo* HistoInfoSILI = new HistoInfo();

  HistoInfoSILI->DetectorName = "SILI";
  HistoInfoSILI->DetectorNumber = {0, 1, 2, 3, 4};
  HistoInfoSILI->DetectorDeadTime_ns = {0, 0, 0, 0, 0};

  HistoInfoSILI->HistoName.push_back("Edep");
  HistoInfoSILI->HistoTitle.push_back("Edep");
  HistoInfoSILI->HistoType.push_back(1);
  HistoInfoSILI->Xaxis.push_back({1e1, 1.e-3, 1.e7});
  HistoInfoSILI->Yaxis.push_back({2e4, 0, 1e5});

  HistoInfoSILI->HistoName.push_back("En");
  HistoInfoSILI->HistoTitle.push_back("En");
  HistoInfoSILI->HistoType.push_back(1);
  HistoInfoSILI->Xaxis.push_back({1e3, 1.e-3, 1.e7});
  HistoInfoSILI->Yaxis.push_back({2e2, 0, 1e5});

  // HistoInfoSILI->HistoName.push_back("En_1000");
  // HistoInfoSILI->HistoTitle.push_back("En");
  // HistoInfoSILI->HistoType.push_back(1);
  // HistoInfoSILI->Xaxis.push_back({1000, 1.e-3, 1.e7});
  // HistoInfoSILI->Yaxis.push_back({200, 0, 1e5});

  // HistoInfoSILI->HistoName.push_back("En_100");
  // HistoInfoSILI->HistoTitle.push_back("En");
  // HistoInfoSILI->HistoType.push_back(1);
  // HistoInfoSILI->Xaxis.push_back({100, 1.e-3, 1.e7});
  // HistoInfoSILI->Yaxis.push_back({200, 0, 1e5});

  // HistoInfoSILI->HistoName.push_back("En_10");
  // HistoInfoSILI->HistoTitle.push_back("En");
  // HistoInfoSILI->HistoType.push_back(1);
  // HistoInfoSILI->Xaxis.push_back({10, 1.e-3, 1.e7});
  // HistoInfoSILI->Yaxis.push_back({200, 0, 1e5});

  HistoInfo* HistoInfoFIMG = new HistoInfo();

  // HistoInfoFIMG->DetectorName = "FIMG";
  // HistoInfoFIMG->DetectorNumber = {0, 1, 2};
  // HistoInfoFIMG->DetectorDeadTime_ns = {0, 0, 0};

  // HistoInfoFIMG->HistoName.push_back("Edep");
  // HistoInfoFIMG->HistoTitle.push_back("Edep");
  // HistoInfoFIMG->HistoType.push_back(1);
  // HistoInfoFIMG->Xaxis.push_back({100, 1.e-3, 1.e7});
  // HistoInfoFIMG->Yaxis.push_back({1000, 0, 1e4});

  // HistoInfoFIMG->HistoName.push_back("En");
  // HistoInfoFIMG->HistoTitle.push_back("En");
  // HistoInfoFIMG->HistoType.push_back(1);
  // HistoInfoFIMG->Xaxis.push_back({1e4, 1.e-3, 1.e7});
  // HistoInfoFIMG->Yaxis.push_back({2e1, 0, 1e4});

  HistoInfo* HistoInfoLABR = new HistoInfo();

  HistoInfoLABR->DetectorName = "LABR";
  HistoInfoLABR->DetectorNumber = {0, 1, 2};
  HistoInfoLABR->DetectorDeadTime_ns = {0, 0, 0};

  HistoInfoLABR->HistoName.push_back("Edep");
  HistoInfoLABR->HistoTitle.push_back("Edep");
  HistoInfoLABR->HistoType.push_back(1);
  HistoInfoLABR->Xaxis.push_back({100, 1.e-3, 1.e7});
  HistoInfoLABR->Yaxis.push_back({2e4, 0, 20});

  HistoInfoLABR->HistoName.push_back("En");
  HistoInfoLABR->HistoTitle.push_back("En");
  HistoInfoLABR->HistoType.push_back(1);
  HistoInfoLABR->Xaxis.push_back({1.8e5, 1.e-2, 1.e7});
  HistoInfoLABR->Yaxis.push_back({0.1, 0.12, 0.15, 0.3, 0.5, 1, 10, 20});

  int const N_PULSETYPE = 4;  // All, Dedicated, Parasitic, Other
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
  // sprintf(outtxtfname, "%s/Histo01_%d.txt", outdir2DHistos, RunNumber);
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

  // Create tree and signal for each detector
  TTree* trC6D6 = (TTree*)f1->Get(HistoInfoC6D6->DetectorName.c_str());
  bool ThereIsC6D6Detector = false;
  int nbunchesC6D6 = 0;
  Long64_t bunchesIndexC6D6[MAXNBUNCHESINFILE];
  int BunchNumberC6D6[MAXNBUNCHESINFILE];
  Signal theC6D6S;
  int NC6D6Signals = 0;
  Signal* theC6D6Signals;
  theC6D6Signals = new Signal[MAXNSIGNALSINPULSE];
  bool UseAreaInsteadOfAmplitudeC6D6 = false;
  if (!(trC6D6 == 0)) {
    cout << "There is C6D6" << endl;

    ThereIsC6D6Detector = true;
    nbunchesC6D6 =
        CreateBunchesIndex(trC6D6, bunchesIndexC6D6, BunchNumberC6D6);
    AttachStruct(&theC6D6S, trC6D6, UseAreaInsteadOfAmplitudeC6D6);
  }
  //==============================================================================
  //===============
  //===============================================================

  TTree* trSILI = (TTree*)f1->Get(HistoInfoSILI->DetectorName.c_str());
  bool ThereIsSILIDetector = false;
  Signal theSILIS;
  int nbunchesSILI = 0;
  Long64_t bunchesIndexSILI[MAXNBUNCHESINFILE];
  int BunchNumberSILI[MAXNBUNCHESINFILE];
  int NSILISignals = 0;
  Signal* theSILISignals;
  bool UseAreaInsteadOfAmplitudeSILI = false;

  if (!trSILI == 0) {
    cout << "There is SILI" << endl;
    ThereIsSILIDetector = true;
    nbunchesSILI =
        CreateBunchesIndex(trSILI, bunchesIndexSILI, BunchNumberSILI);
    AttachStruct(&theSILIS, trSILI);
    theSILISignals = new Signal[MAXNSIGNALSINPULSE];
  }
  //==============================================================================
  //==============================================================================
  bool ThereIsFIMGDetector = false;

  TTree* trFIMG = (TTree*)f1->Get(HistoInfoFIMG->DetectorName.c_str());
  Signal theFIMGS;
  int nbunchesFIMG = 0;
  Long64_t bunchesIndexFIMG[MAXNBUNCHESINFILE];
  int BunchNumberFIMG[MAXNBUNCHESINFILE];
  int NFIMGSignals = 0;
  Signal* theFIMGSignals;
  bool UseAreaInsteadOfAmplitudeFIMG = false;

  if (!trFIMG == 0) {
    cout << "There is FIMG" << endl;
    ThereIsFIMGDetector = true;
    nbunchesFIMG =
        CreateBunchesIndex(trFIMG, bunchesIndexFIMG, BunchNumberFIMG);
    AttachStruct(&theFIMGS, trFIMG, UseAreaInsteadOfAmplitudeFIMG);
    theFIMGSignals = new Signal[MAXNSIGNALSINPULSE];
  }
  // //==============================================================================
  //==============================================================================
  bool ThereIsLABRDetector = true;

  TTree* trLABR = (TTree*)f1->Get(HistoInfoLABR->DetectorName.c_str());
  Signal theLABRS;
  int nbunchesLABR = 0;
  Long64_t bunchesIndexLABR[MAXNBUNCHESINFILE];
  int BunchNumberLABR[MAXNBUNCHESINFILE];
  int NLABRSignals = 0;
  Signal* theLABRSignals;
  bool UseAreaInsteadOfAmplitudeLABR = true;
  if (!trLABR == 0) {
    cout << "There is LABR" << endl;
    ThereIsLABRDetector = true;
    nbunchesLABR =
        CreateBunchesIndex(trLABR, bunchesIndexLABR, BunchNumberLABR);
    AttachStruct(&theLABRS, trLABR, UseAreaInsteadOfAmplitudeLABR);
    theLABRSignals = new Signal[MAXNSIGNALSINPULSE];
  }

  //==============================================================================
  //==============================================================================

  cout << " Creating histograms ..." << endl;

  // Pulse intensity histograms:
  TH1D* hPulIntens[N_PULSETYPE * 2];
  CreateTH1DHistoPulseIntesity(hPulIntens, N_PULSETYPE, fout);

  // C6D6 histos

  TH2D*** h2D_C6D6[N_PULSETYPE];
  CreateTH2DHisto(ThereIsC6D6Detector, HistoInfoC6D6, N_PULSETYPE, h2D_C6D6,
                  fout);

  // SILI histos

  TH2D*** h2D_SILI[N_PULSETYPE];
  CreateTH2DHisto(ThereIsSILIDetector, HistoInfoSILI, N_PULSETYPE, h2D_SILI,
                  fout);
  // FIMG histos

  TH2D*** h2D_FIMG[N_PULSETYPE];
  CreateTH2DHisto(ThereIsFIMGDetector, HistoInfoFIMG, N_PULSETYPE, h2D_FIMG,
                  fout);

  // LABR histos

  TH2D*** h2D_LABR[N_PULSETYPE];
  CreateTH2DHisto(ThereIsLABRDetector, HistoInfoLABR, N_PULSETYPE, h2D_LABR,
                  fout);

  /************************************************************************
   *************************************************************************
   ************************************************************************/

  // Main loop:
  cout << " Starting main loop ..." << endl;
  for (int npul = 0; npul < nbunches; npul++) {
    // cout << "Pulse " << npul << "Type pulse" <<
    // thePKUPInfo->pulseType[npul]<< endl;
    int PulseType = thePKUPInfo->pulseType[npul];
    int thisPulseType = 3;  // Other
    if (thePKUPInfo->pulseType[npul] == DEDICATED_PULSES_ID) {
      thisPulseType = 1;
    }
    if (thePKUPInfo->pulseType[npul] == PARASITIC_PULSES_ID) {
      thisPulseType = 2;
    }
    double C6D6TFlash = -1;
    double SILITFlash = -1;
    double FIMGTFlash = -1;
    double LABRTFlash = -1;

    // cout << "Inte " << thePKUPInfo->PulseIntensity[npul] << endl;
    if (thePKUPInfo->PulseIntensity[npul] < 1.e12) {
      // There is not beam in this run so I force the Tflash to Zero for
      // security
      C6D6TFlash = 0;
      SILITFlash = 0;
      FIMGTFlash = 0;
      LABRTFlash = 0;
    }

    FillPulseIntensity(
        N_PULSETYPE, thisPulseType, thePKUPInfo->PulseIntensity[npul],
        thePKUPInfo->PKUPAmp[npul], thePKUPInfo->PKUPArea[npul], hPulIntens);

    if (ThereIsC6D6Detector) {
      NC6D6Signals =
          GetSignals(HistoInfoC6D6->DetectorName,
                     HistoInfoC6D6->DetectorDeadTime_ns, trC6D6, &theC6D6S,
                     bunchesIndexC6D6[npul], bunchesIndexC6D6[npul + 1] - 1,
                     theC6D6Signals, theCalibM, 1, C6D6TFlash);  //

      FillType1(thisPulseType, NC6D6Signals, theC6D6Signals, h2D_C6D6, -1.e20,
                1.e20, HistoInfoC6D6);

      FillType2(thisPulseType, NC6D6Signals, theC6D6Signals, h2D_C6D6, -1.e20,
                1.e20, HistoInfoC6D6);

      FillType3(thisPulseType, NC6D6Signals, theC6D6Signals, h2D_C6D6, -1.e20,
                1.e20, HistoInfoC6D6);

      FillType4(thisPulseType, NC6D6Signals, theC6D6Signals, h2D_C6D6, -1.e20,
                1.e20, HistoInfoC6D6);
      FillType5(thisPulseType, NC6D6Signals, theC6D6Signals, h2D_C6D6, -1.e20,
                1.e20, HistoInfoC6D6);
      FillType6(thisPulseType, NC6D6Signals, theC6D6Signals, h2D_C6D6, -1.e20,
                1.e20, HistoInfoC6D6);
    }
    if (ThereIsSILIDetector) {
      NSILISignals =
          GetSignals(HistoInfoSILI->DetectorName,
                     HistoInfoSILI->DetectorDeadTime_ns, trSILI, &theSILIS,
                     bunchesIndexSILI[npul], bunchesIndexSILI[npul + 1] - 1,
                     theSILISignals, theCalibM, 1, SILITFlash);  //

      FillType1(thisPulseType, NSILISignals, theSILISignals, h2D_SILI, -1.e20,
                1.e20, HistoInfoSILI);

      FillTypeSILICounts(thisPulseType, NSILISignals, theSILISignals,
                         hPulIntens, -1.e20, 1.e20, HistoInfoSILI);
    }
    if (ThereIsFIMGDetector) {
      NFIMGSignals =
          GetSignals(HistoInfoFIMG->DetectorName,
                     HistoInfoFIMG->DetectorDeadTime_ns, trFIMG, &theFIMGS,
                     bunchesIndexFIMG[npul], bunchesIndexFIMG[npul + 1] - 1,
                     theFIMGSignals, theCalibM, 1, FIMGTFlash);  //

      FillType1(thisPulseType, NFIMGSignals, theFIMGSignals, h2D_FIMG, -1.e20,
                1.e20, HistoInfoFIMG);
    }

    if (ThereIsLABRDetector) {
      NLABRSignals =
          GetSignals(HistoInfoLABR->DetectorName,
                     HistoInfoLABR->DetectorDeadTime_ns, trLABR, &theLABRS,
                     bunchesIndexLABR[npul], bunchesIndexLABR[npul + 1] - 1,
                     theLABRSignals, theCalibM, 1, LABRTFlash);  //

      FillType1(thisPulseType, NLABRSignals, theLABRSignals, h2D_LABR, -1.e20,
                1.e20, HistoInfoLABR);
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
