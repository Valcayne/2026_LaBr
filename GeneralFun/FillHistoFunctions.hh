
#ifndef FILLHISTOFUNCTIONS_HH
#define FILLHISTOFUNCTIONS_HH 1

#include "GetSignalsFunctions.hh"

//=====================================================================================
int FillPulseIntensity(int N_PULSETYPE, int thisPulseType,
                       double PulseIntensity, double PKUPAmp, double PKUPArea,
                       TH1D** hPulIntens);
int FillType12(int thisPulseType, int NEvents, std::vector<int> NEventsArray,
               std::vector<FullEvent*>& theFullEvents, int NumberHistoType,
               TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
               std::vector<HistoInfo>& TheHistoInfoVector,
               std::vector<string> ThereIsNameDetector);
int FillType11(int thisPulseType, int NEvents, std::vector<int> NEventsArray,
               std::vector<FullEvent*>& theFullEvents, int NumberHistoType,
               TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
               std::vector<HistoInfo>& TheHistoInfoVector,
               std::vector<string> ThereIsNameDetector);
int FillType10(int thisPulseType, int NEvents, std::vector<int> NEventsArray,
               std::vector<FullEvent*>& theFullEvents, int NumberHistoType,
               TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
               std::vector<HistoInfo>& TheHistoInfoVector,
               std::vector<string> ThereIsNameDetector);
int FillType9(int thisPulseType, int NEvents, FullEvent* theFullEvents,
              TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);
int FillType8(int thisPulseType, int NEvents, FullEvent* theFullEvents,
              TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);
int FillType7(int thisPulseType, int NEvents, Event* theEvents, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);

int FillType6(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);

int FillType5(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);
int FillType4(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);
int FillType3(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);
int FillType2(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);
int FillType1(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo);
int FillTypeSILICounts(int thisPulseType, int NSignals, Signal* theSignals,
                       TH1D** hPulIntens, double EdepThresholdMin,
                       double EdepThresholdMax, HistoInfo* TheHistoInfo);
//=====================================================================================

/************************************************************************
*************************************************************************
************************************************************************/
int FillTypeSILICounts(int thisPulseType, int NSignals, Signal* theSignals,
                       TH1D** hPulIntens, double EdepThresholdMin,
                       double EdepThresholdMax, HistoInfo* TheHistoInfo) {
  for (int i = 0; i < NSignals; i++) {
    double NeutEne = theSignals[i].eNeutron;
    double Edep = theSignals[i].edep;
    int DetN = theSignals[i].detn;
    double EdepEminForSiliCount = 2.2e4;
    double EdepEmaxForSiliCount = 4.0e4;
    double EnEminForSiliCount = 0.02;
    double EnEmaxForSiliCount = 1e5;
    if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
      if (Edep > EdepEminForSiliCount && Edep < EdepEmaxForSiliCount) {
        if (NeutEne > EnEminForSiliCount && NeutEne < EnEmaxForSiliCount) {
          if (-1 != FindDetectorPosition(TheHistoInfo->DetectorNumber,
                                         DetN)) {  // Check if the detector
                                                   // number is in TheHistoInfo
            //  cout << "Fill " << DetN << " " <<
            //  hPulIntens[0]->GetBinContent(5) << " " << i << " " << Edep << "
            //  " << NeutEne << endl;

            hPulIntens[thisPulseType]->AddBinContent(5, 1);
            hPulIntens[0]->AddBinContent(5, 1);
          }
        }
      }
    }
  }
  return 0;
}
int FillPulseIntensity(int N_PULSETYPE, int thisPulseType,
                       double PulseIntensity, double PKUPAmp, double PKUPArea,
                       TH1D** hPulIntens) {
  hPulIntens[thisPulseType]->AddBinContent(1, PulseIntensity);
  hPulIntens[thisPulseType]->AddBinContent(2, 1);
  hPulIntens[thisPulseType]->AddBinContent(3, PKUPAmp);
  hPulIntens[thisPulseType]->AddBinContent(4, PKUPArea);

  hPulIntens[0]->AddBinContent(1, PulseIntensity);
  hPulIntens[0]->AddBinContent(2, 1);
  hPulIntens[0]->AddBinContent(3, PKUPAmp);
  hPulIntens[0]->AddBinContent(4, PKUPArea);

  hPulIntens[N_PULSETYPE + thisPulseType]->Fill(PulseIntensity);
  hPulIntens[N_PULSETYPE]->Fill(PulseIntensity);

  return 0;
}
int FillType7(int thisPulseType, int NEvents, Event* theEvents, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 7;
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test 7" << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //      << NEvents << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NEvents; i++) {
        double NeutEne = theEvents[i].eNeutron;
        double Edep = theEvents[i].esum;
        int Mul = theEvents[i].mult;
        //   cout << i << " " << theEvents[i].tof << endl;
        // cout << "Event " << i << " Ene " << NeutEne << " Edep " << Edep
        //      << " Mul " << Mul << endl;
        if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
          if (-1 != FindDetectorPosition(TheHistoInfo->DetectorNumber,
                                         Mul)) {  // Check if the detector
                                                  // number is in TheHistoInfo
            // cout << "Fill " << i << "  " << thisPulseType << " "
            //      << TheHistoInfo->HistoType[j] << " "
            //      << FindDetectorPosition(TheHistoInfo->DetectorNumber, Mul)
            //      << " " << Mul << " " << Edep << "        " << NeutEne <<
            //      endl;
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, Mul)]
                   ->Fill(NeutEne, Edep);
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                   ->Fill(NeutEne, Edep);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, Mul)]
                ->Fill(NeutEne, Edep);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                ->Fill(NeutEne, Edep);

            // h2[ptype][HistoType][det]
          }
        }
      }
    }
  }
  return 0;
}

int FillType8(int thisPulseType, int NEvents, FullEvent* theFullEvents,
              TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 8;
  int referencedetector = 1;
  int MaxDet = *std::max_element(TheHistoInfo->DetectorNumber.begin(),
                                 TheHistoInfo->DetectorNumber.end());
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NEvents; i++) {
        if (theFullEvents[i].mult > 1 &&
            (theFullEvents[i].EdepDet[referencedetector]) > 0.0) {
          // cout << "Event " << i << " Mult " << theFullEvents[i].mult << "
          // esum "
          //      << theFullEvents[i].esum << endl;
          for (int k = 0; k <= (MaxDet); k++) {
            double Edep = theFullEvents[i].EdepDet[k];
            double DeltaTime =
                (theFullEvents[i].TofDet[k] * 1e6) -
                (theFullEvents[i].TofDet[referencedetector] * 1e6);
            if (Edep > 0.0) {
              // cout << k << " "
              //      << FindDetectorPosition(TheHistoInfo->DetectorNumber, k)
              //      << " Edep " << Edep << " DeltaTime " << DeltaTime << " "
              //      << theFullEvents[i].TofDet[k] * 1e6 << " "
              //      << theFullEvents[i].TofDet[referencedetector] * 1e6 <<
              //      endl;
              hEn[thisPulseType][j]
                 [FindDetectorPosition(TheHistoInfo->DetectorNumber, k)]
                     ->Fill(DeltaTime, Edep);
              hEn[thisPulseType][j]
                 [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                     ->Fill(DeltaTime, Edep);
              hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, k)]
                  ->Fill(DeltaTime, Edep);
              hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                  ->Fill(DeltaTime, Edep);

              // h2[ptype][HistoType][det]
            }
          }
        }
      }
    }
  }

  return 0;
}
int FillType9(int thisPulseType, int NEvents, FullEvent* theFullEvents,
              TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 9;
  int referencedetector = 1;
  int MaxDet = *std::max_element(TheHistoInfo->DetectorNumber.begin(),
                                 TheHistoInfo->DetectorNumber.end());
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NEvents; i++) {
        if (theFullEvents[i].mult > 1 &&
            (theFullEvents[i].EdepDet[referencedetector]) > 0.0) {
          // cout << "Event " << i << " Mult " << theFullEvents[i].mult << "
          // esum "
          //      << theFullEvents[i].esum << endl;
          for (int k = 0; k <= (MaxDet); k++) {
            double Edep = theFullEvents[i].EdepDet[k];
            double ENeutron = theFullEvents[i].eNeutron;

            double DeltaTime =
                (theFullEvents[i].TofDet[k] * 1e6) -
                (theFullEvents[i].TofDet[referencedetector] * 1e6);
            if (Edep > 0.0) {
              // cout << k << " "
              //      << FindDetectorPosition(TheHistoInfo->DetectorNumber, k)
              //      << " Edep " << Edep << " DeltaTime " << DeltaTime << " "
              //      << theFullEvents[i].TofDet[k] * 1e6 << " "
              //      << theFullEvents[i].TofDet[referencedetector] * 1e6 <<
              //      endl;
              hEn[thisPulseType][j]
                 [FindDetectorPosition(TheHistoInfo->DetectorNumber, k)]
                     ->Fill(ENeutron, DeltaTime);
              hEn[thisPulseType][j]
                 [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                     ->Fill(ENeutron, DeltaTime);
              hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, k)]
                  ->Fill(ENeutron, DeltaTime);
              hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                  ->Fill(ENeutron, DeltaTime);

              // h2[ptype][HistoType][det]
            }
          }
        }
      }
    }
  }

  return 0;
}

int FillType10(int thisPulseType, int NEvents, std::vector<int> NEventsArray,
               std::vector<FullEvent*>& theFullEvents, int NumberHistoType,
               TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
               std::vector<HistoInfo>& TheHistoInfoVector,
               std::vector<string> ThereIsNameDetector) {
  // cout << "Starting FillType10" << endl;
  int FillType = 10;
  FullEvent* theEvents = theFullEvents[NumberHistoType];
  HistoInfo& TheHistoInfo = TheHistoInfoVector[NumberHistoType];

  int CoincidenceHistoNumber = -1;
  double CoincidenceWindow = 0.0;
  for (int j = 0; j < (int)TheHistoInfo.HistoName.size(); j++) {
    if (FillType == TheHistoInfo.HistoType[j]) {
      CoincidenceWindow = TheHistoInfo.CoincidenceWindow;
      if (TheHistoInfo.HistoCoincidenceName.size() < j) {
        cout << "Check that all the HistoInfo previous to type 10 have "
                "HistoCoincidenceName "
             << " ########### Error in " << __FILE__ << ", line " << __LINE__
             << " ###########" << endl;
        exit(1);
      }

      for (int k = 0; k < (int)TheHistoInfoVector.size(); k++) {
        HistoInfo& info =
            TheHistoInfoVector[k];  // referencia al i-ésimo HistoInfo
        // cout << "TheHistoInfo.HistoCoincidenceName[j] "
        //      << TheHistoInfo.HistoCoincidenceName[j] << " info.DetectorName "
        //      << info.DetectorName << endl;
        if (std::find(ThereIsNameDetector.begin(), ThereIsNameDetector.end(),
                      TheHistoInfo.HistoCoincidenceName[j]) !=
            ThereIsNameDetector.end()) {
          if (TheHistoInfo.HistoCoincidenceName[j] == info.DetectorName) {
            CoincidenceHistoNumber = k;
          }
        }
      }
    }
  }

  if (CoincidenceHistoNumber != -1) {
    FullEvent* theEventsCoincidences = theFullEvents[CoincidenceHistoNumber];
    HistoInfo& theInfoCoincidences = TheHistoInfoVector[CoincidenceHistoNumber];
    // cout << "theEventsCoincidences " << theEventsCoincidences
    //      << " theInfoCoincidences " << theInfoCoincidences.DetectorName <<
    //      endl;
    if (!theEventsCoincidences) {
      std::cerr << "ERROR: theEvents es nullptr en NumberHistoType="
                << NumberHistoType << std::endl;
    }

    //

    for (int j = 0; j < (int)TheHistoInfo.HistoType.size(); j++) {
      if (FillType == TheHistoInfo.HistoType[j]) {
        int k = 0;

        for (int i = 0; i < NEvents; i++) {
          double NeutEne = theEvents[i].eNeutron;
          double Edep = theEvents[i].esum;
          int Mul = theEvents[i].mult;
          double Tof_ns = theEvents[i].tof * 1e6;
          std::cout << std::fixed << std::setprecision(10);
          if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
            if (-1 != FindDetectorPosition(TheHistoInfo.DetectorNumber,
                                           Mul)) {  // Check if the detector
                                                    // number is in TheHistoInfo

              //
              while (theEventsCoincidences[k].tof * 1e6 < Tof_ns &&
                     k < NEventsArray[CoincidenceHistoNumber]) {
                k++;
              }
              // cout << "k " << k << " " << theEventsCoincidences[k].tof
              //      << "                         "
              //      << theEventsCoincidences[k].esum << " "
              //      << NEventsArray[CoincidenceHistoNumber] << endl;
              // cout << "theEventsCoincidences[k].tof * 1e6 "
              //      << theEventsCoincidences[k].tof * 1e6 << " Tof_ns " <<
              //      Tof_ns
              //      << endl;
              // std::cin.get();
              k = k - 1;
              if (k == -1) {
                k = 0;
              }
              //  cout << "k " << k << endl;
              if ((theEventsCoincidences[k + 1].tof > 0) &&
                      (theEventsCoincidences[k + 1].tof * 1e6 <
                       (Tof_ns + CoincidenceWindow)) ||
                  (theEventsCoincidences[k].tof * 1e6 >
                   (Tof_ns - CoincidenceWindow))) {
                // cout << " In coincidendence theEventsCoincidences[k].tof *
                // 1e6 "
                //      << theEventsCoincidences[k].tof * 1e6 << " Tof_ns "
                //      << Tof_ns << endl;
                hEn[thisPulseType][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, Mul)]
                       ->Fill(NeutEne, Edep);
                hEn[thisPulseType][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, 0)]
                       ->Fill(NeutEne, Edep);
                hEn[0][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, Mul)]
                       ->Fill(NeutEne, Edep);
                hEn[0][j][FindDetectorPosition(TheHistoInfo.DetectorNumber, 0)]
                    ->Fill(NeutEne, Edep);
              }
            }
          }
        }
      }
    }
  }

  return 0;
}

int FillType6(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 6;

  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    for (int i = 0; i < (int)TheHistoInfo->DetectorDeadTime_ns.size(); i++) {
      if (FillType == TheHistoInfo->HistoType[j]) {
        if (hEn[thisPulseType][j][i]->GetBinContent(1, 1) == 0) {
          hEn[thisPulseType][j][i]->SetBinContent(
              1, 1, TheHistoInfo->DetectorDeadTime_ns[i]);

          // cout << "Fill " << thisPulseType << " " << j << " " << i << " "
          //      << TheHistoInfo->DetectorDeadTime_ns[i] << endl;
          // cout << " Getbin cont"
          //      << hEn[thisPulseType][j][i]->GetBinContent(1, 1) << endl;
        }
      }
    }
  }

  return 0;
}

int FillType5(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 5;
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NSignals; i++) {
        double NeutEne = theSignals[i].eNeutron;
        double Edep = theSignals[i].edep;
        int DetN = theSignals[i].detn;
        double Weight = theSignals[i].weight;
        // cout << "Det " << DetN << " Edep " << Edep << "weight " << Weight
        // << endl;
        if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
          if (-1 != FindDetectorPosition(TheHistoInfo->DetectorNumber,
                                         DetN)) {  // Check if the detector
                                                   // number is in TheHistoInfo
            // cout << "Fill " << thisPulseType << " "
            //      << TheHistoInfo->HistoType[j] << " " << DetN << Edep << "
            //      "
            //      << NeutEne << endl;
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                   ->Fill(NeutEne, Edep, Weight);
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                   ->Fill(NeutEne, Edep, Weight);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                ->Fill(NeutEne, Edep, Weight);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                ->Fill(NeutEne, Edep, Weight);

            // h2[ptype][HistoType][det]
          }
        }
      }
    }
  }
  return 0;
}

int FillType4(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 4;
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NSignals; i++) {
        double TOF = theSignals[i].tof * 1.e6;  // For ns
        double TOFPreviousSignal =
            theSignals[i].tofPreviousSignal * 1.e6;  // For ns

        double Edep = theSignals[i].edep;
        double EdepPreviousSignal = theSignals[i].edepPreviousSignal;

        int DetN = theSignals[i].detn;
        double DeltaTime = TOF - TOFPreviousSignal;
        double NeutEne = theSignals[i].eNeutron;

        if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
          if (DeltaTime < 0) {
            // cout << "For Det" << DetN << " TOF (" << TOF
            //      << ") < TOFPreviousSignal (" << TOFPreviousSignal << ")"
            //      << endl;
            DeltaTime = -1;
          }

          if (NeutEne < 2e6) {  // I add this in order to remove effects
                                // observed due to the g-flash
            if (-1 !=
                FindDetectorPosition(TheHistoInfo->DetectorNumber,
                                     DetN)) {  // Check if the detector
                                               // number is in TheHistoInfo
              // cout << "Fill " << thisPulseType << " "
              //      << TheHistoInfo->HistoType[j] << " " << DetN << Edep <<
              //      "
              //      "
              //      << NeutEne << endl;

              hEn[thisPulseType][j]
                 [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                     ->Fill(DeltaTime, Edep);
              hEn[thisPulseType][j]
                 [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                     ->Fill(DeltaTime, Edep);
              hEn[0][j]
                 [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                     ->Fill(DeltaTime, Edep);
              hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                  ->Fill(DeltaTime, Edep);

              // h2[ptype][HistoType][det]
            }
          }
        }
      }
    }
  }
  return 0;
}

int FillType3(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 3;
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NSignals; i++) {
        double Tflash = theSignals[i].tflash * 1.e6;  // For ns
        int DetN = theSignals[i].detn;

        if ((!(thisPulseType == 3)) &&
            (Tflash >
             hEn[thisPulseType][j]
                [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                    ->GetXaxis()
                    ->GetBinUpEdge(hEn[thisPulseType][j]
                                      [FindDetectorPosition(
                                           TheHistoInfo->DetectorNumber, DetN)]
                                          ->GetNbinsX()))) {
          cout << "Tflash= " << Tflash << "> up limit= "
               << hEn[thisPulseType][j]
                     [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                         ->GetXaxis()
                         ->GetBinUpEdge(
                             hEn[thisPulseType][j]
                                [FindDetectorPosition(
                                     TheHistoInfo->DetectorNumber, DetN)]
                                    ->GetNbinsX())
               << endl
               << " ########### Error in " << __FILE__ << ", line " << __LINE__
               << " ###########" << endl;
          // exit(1);
        }

        if (-1 != FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)) {
          hEn[thisPulseType][j]
             [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                 ->Fill(Tflash, 1);
          hEn[thisPulseType][j]
             [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                 ->Fill(Tflash, 1);
          hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
              ->Fill(Tflash, 1);
          hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
              ->Fill(Tflash, 1);

          // h2[ptype][HistoType][det]
        }
      }
    }
  }
  return 0;
}
int FillType2(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 2;
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NSignals; i++) {
        double TOF = theSignals[i].tof * 1.e6;        // For ns
        double Tflash = theSignals[i].tflash * 1.e6;  // For ns
        //  cout << "thisPulseType " << thisPulseType << " TOF " << TOF << "
        //  Tflash"        << Tflash << endl;
        double Edep = theSignals[i].edep;
        int DetN = theSignals[i].detn;

        if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
          if (-1 != FindDetectorPosition(TheHistoInfo->DetectorNumber,
                                         DetN)) {  // Check if the detector
                                                   // number is in TheHistoInfo
            // cout << "Fill " << thisPulseType << " "
            //      << TheHistoInfo->HistoType[j] << " " << DetN << Edep << "
            //      "
            //      << NeutEne << endl;

            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                   ->Fill(TOF - Tflash, Edep);
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                   ->Fill(TOF - Tflash, Edep);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                ->Fill(TOF - Tflash, Edep);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                ->Fill(TOF - Tflash, Edep);

            // h2[ptype][HistoType][det]
          }
        }
      }
    }
  }
  return 0;
}
int FillType1(int thisPulseType, int NSignals, Signal* theSignals, TH2D**** hEn,
              double EdepThresholdMin, double EdepThresholdMax,
              HistoInfo* TheHistoInfo) {
  int FillType = 1;
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NSignals; i++) {
        double NeutEne = theSignals[i].eNeutron;
        double Edep = theSignals[i].edep;
        int DetN = theSignals[i].detn;

        if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
          if (-1 != FindDetectorPosition(TheHistoInfo->DetectorNumber,
                                         DetN)) {  // Check if the detector
                                                   // number is in TheHistoInfo
            // cout << "Fill " << thisPulseType << " "
            //      << TheHistoInfo->HistoType[j] << " " << DetN << Edep << "
            //      "
            //      << NeutEne << endl;
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                   ->Fill(NeutEne, Edep);
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                   ->Fill(NeutEne, Edep);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, DetN)]
                ->Fill(NeutEne, Edep);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                ->Fill(NeutEne, Edep);

            // h2[ptype][HistoType][det]
          }
        }
      }
    }
  }
  return 0;
}
int FillType11(int thisPulseType, int NEvents, std::vector<int> NEventsArray,
               std::vector<FullEvent*>& theFullEvents, int NumberHistoType,
               TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
               std::vector<HistoInfo>& TheHistoInfoVector,
               std::vector<string> ThereIsNameDetector) {
  //  cout << "Starting FillType10" << endl;
  int FillType = 11;
  FullEvent* theEvents = theFullEvents[NumberHistoType];
  HistoInfo& TheHistoInfo = TheHistoInfoVector[NumberHistoType];

  int CoincidenceHistoNumber = -1;
  double CoincidenceWindow = 0.0;
  for (int j = 0; j < (int)TheHistoInfo.HistoName.size(); j++) {
    if (FillType == TheHistoInfo.HistoType[j]) {
      CoincidenceWindow = TheHistoInfo.CoincidenceWindow;
      if (TheHistoInfo.HistoCoincidenceName.size() < j) {
        cout << "Check that all the HistoInfo previous to type 10 have "
                "HistoCoincidenceName "
             << " ########### Error in " << __FILE__ << ", line " << __LINE__
             << " ###########" << endl;
        exit(1);
      }
      // cout << TheHistoInfo.HistoType[j] << " TheHistoInfo->HistoType[j] "
      //      << TheHistoInfo.HistoType[j] << endl;
      // cout << TheHistoInfo.HistoType[j] << " TheHistoInfo->HistoName[j] "
      //      << TheHistoInfo.HistoName[j] << endl;
      // cout << TheHistoInfo.HistoType[j]
      //      << " TheHistoInfo->HistoCoincidenceName[j] "
      //      << TheHistoInfo.HistoCoincidenceName[j] << endl;
      for (int k = 0; k < (int)TheHistoInfoVector.size(); k++) {
        HistoInfo& info =
            TheHistoInfoVector[k];  // referencia al i-ésimo HistoInfo
        if (std::find(ThereIsNameDetector.begin(), ThereIsNameDetector.end(),
                      TheHistoInfo.HistoCoincidenceName[j]) !=
            ThereIsNameDetector.end()) {
          if (TheHistoInfo.HistoCoincidenceName[j] == info.DetectorName) {
            // cout << "TheHistoInfo.HistoCoincidenceName[j] "
            //      << TheHistoInfo.HistoCoincidenceName[j]
            //      << " TheHistoInfo.HistoName[j] " <<
            //      TheHistoInfo.DetectorName
            //      << " info.DetectorName " << info.DetectorName << endl;
            // ;
            CoincidenceHistoNumber = k;
            // cout << "NumberHistoType " << NumberHistoType
            //      << " CoincidenceHistoNumber " << CoincidenceHistoNumber <<
            //      endl;
          }
        }
      }
    }
  }

  if (CoincidenceHistoNumber != -1) {
    FullEvent* theEventsCoincidences = theFullEvents[CoincidenceHistoNumber];
    HistoInfo& theInfoCoincidences = TheHistoInfoVector[CoincidenceHistoNumber];
    //
    for (int j = 0; j < (int)TheHistoInfo.HistoType.size(); j++) {
      if (FillType == TheHistoInfo.HistoType[j]) {
        int k = 0;

        for (int i = 0; i < NEvents; i++) {
          double NeutEne = theEvents[i].eNeutron;
          double Edep = theEvents[i].esum;
          int Mul = theEvents[i].mult;
          double Tof_ns = theEvents[i].tof * 1e6;
          std::cout << std::fixed << std::setprecision(10);
          if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
            if (-1 != FindDetectorPosition(TheHistoInfo.DetectorNumber,
                                           Mul)) {  // Check if the detector
                                                    // number is in TheHistoInfo
              // cout << endl << "Tof " << Tof_ns << endl;
              //
              while (
                  theEventsCoincidences[k].tof * 1e6 < Tof_ns &&
                  k < NEventsArray
                          [CoincidenceHistoNumber]) {  // cout << k
                                                       // << " " <<
                                                       // theEventsCoincidences[k].tof
                                                       // * 1e6 <<
                // endl; std::cin.get();

                k++;
              }
              k = k - 1;
              if (k == -1) {
                k = 0;
              }
              // cout << endl << "Tof " << Tof_ns << endl;
              // cout << "k " << k << " i " << i
              //      << " tof theEventsCoincidences antes "
              //      << theEventsCoincidences[k].tof * 1e6
              //      << " tof theEventsCoincidences despues "
              //      << theEventsCoincidences[k + 1].tof * 1e6 << endl;

              // cout << "eseum" << theEvents[i].esum << " "
              //      << theEventsCoincidences[k].esum << endl;

              // if (theEventsCoincidences[k].tof * 1e6 >
              //     (Tof_ns - CoincidenceWindow)) {
              //   // cout << "If true" << theEventsCoincidences[k].tof * 1e6
              //   <<
              //   ">
              //   // "
              //   //      << Tof_ns - CoincidenceWindow << endl;
              //   // cout << "Entra por abajo" << endl;
              //   // std::cin.get();
              // }
              // if (theEventsCoincidences[k + 1].tof * 1e6 <
              //     (Tof_ns + CoincidenceWindow)) {
              //   // cout << "If true" << theEventsCoincidences[k + 1].tof *
              //   1e6
              //   //      << " <" << Tof_ns + CoincidenceWindow << endl;
              //   // cout << "Entra por arriba" << endl;
              //   // std::cin.get();
              // }
              if ((theEventsCoincidences[k + 1].tof > 0) &&
                      (theEventsCoincidences[k + 1].tof * 1e6 <
                       (Tof_ns + CoincidenceWindow)) ||
                  (theEventsCoincidences[k].tof * 1e6 >
                   (Tof_ns - CoincidenceWindow))) {
                double TimeDifference;
                if (theEventsCoincidences[k + 1].tof * 1e6 <
                    (Tof_ns + CoincidenceWindow)) {
                  TimeDifference =
                      Tof_ns - theEventsCoincidences[k + 1].tof * 1e6;
                  // cout << "TimeDifference Arriba" << TimeDifference <<
                  // endl;
                } else {
                  TimeDifference = Tof_ns - theEventsCoincidences[k].tof * 1e6;
                  // cout << "TimeDifference debajo" << TimeDifference <<
                  // endl;
                }
                hEn[thisPulseType][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, Mul)]
                       ->Fill(NeutEne, TimeDifference);
                hEn[thisPulseType][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, 0)]
                       ->Fill(NeutEne, TimeDifference);
                hEn[0][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, Mul)]
                       ->Fill(NeutEne, TimeDifference);
                hEn[0][j][FindDetectorPosition(TheHistoInfo.DetectorNumber, 0)]
                    ->Fill(NeutEne, TimeDifference);
              }
            }
          }
        }
      }
    }
  }

  return 0;
}

int FillType12(int thisPulseType, int NEvents, std::vector<int> NEventsArray,
               std::vector<FullEvent*>& theFullEvents, int NumberHistoType,
               TH2D**** hEn, double EdepThresholdMin, double EdepThresholdMax,
               std::vector<HistoInfo>& TheHistoInfoVector,
               std::vector<string> ThereIsNameDetector) {
  //  cout << "Starting FillType10" << endl;
  int FillType = 12;
  FullEvent* theEvents = theFullEvents[NumberHistoType];
  HistoInfo& TheHistoInfo = TheHistoInfoVector[NumberHistoType];

  int CoincidenceHistoNumber = -1;
  double CoincidenceWindow = 0.0;
  for (int j = 0; j < (int)TheHistoInfo.HistoName.size(); j++) {
    if (FillType == TheHistoInfo.HistoType[j]) {
      CoincidenceWindow = TheHistoInfo.CoincidenceWindow;
      if (TheHistoInfo.HistoCoincidenceName.size() < j) {
        cout << "Check that all the HistoInfo previous to type 10 have "
                "HistoCoincidenceName "
             << " ########### Error in " << __FILE__ << ", line " << __LINE__
             << " ###########" << endl;
        exit(1);
      }

      for (int k = 0; k < (int)TheHistoInfoVector.size(); k++) {
        HistoInfo& info =
            TheHistoInfoVector[k];  // referencia al i-ésimo HistoInfo
        if (std::find(ThereIsNameDetector.begin(), ThereIsNameDetector.end(),
                      TheHistoInfo.HistoCoincidenceName[j]) !=
            ThereIsNameDetector.end()) {
          if (TheHistoInfo.HistoCoincidenceName[j] == info.DetectorName) {
            // cout << "TheHistoInfo.HistoCoincidenceName[j] "
            //      << TheHistoInfo.HistoCoincidenceName[j]
            //      << " TheHistoInfo.HistoName[j] " <<
            //      TheHistoInfo.DetectorName
            //      << " info.DetectorName " << info.DetectorName << endl;
            // ;
            CoincidenceHistoNumber = k;
            // cout << "NumberHistoType " << NumberHistoType
            //      << " CoincidenceHistoNumber " << CoincidenceHistoNumber <<
            //      endl;
          }
        }
      }
    }
  }

  if (CoincidenceHistoNumber != -1) {
    FullEvent* theEventsCoincidences = theFullEvents[CoincidenceHistoNumber];
    HistoInfo& theInfoCoincidences = TheHistoInfoVector[CoincidenceHistoNumber];
    //
    for (int j = 0; j < (int)TheHistoInfo.HistoType.size(); j++) {
      if (FillType == TheHistoInfo.HistoType[j]) {
        int k = 0;

        for (int i = 0; i < NEvents; i++) {
          double NeutEne = theEvents[i].eNeutron;
          double Edep = theEvents[i].esum;
          int Mul = theEvents[i].mult;
          double Tof_ns = theEvents[i].tof * 1e6;
          std::cout << std::fixed << std::setprecision(10);
          if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
            if (-1 != FindDetectorPosition(TheHistoInfo.DetectorNumber,
                                           Mul)) {  // Check if the detector
                                                    // number is in TheHistoInfo
              // cout << endl << "Tof " << Tof_ns << endl;
              //
              while (
                  theEventsCoincidences[k].tof * 1e6 < Tof_ns &&
                  k < NEventsArray
                          [CoincidenceHistoNumber]) {  // cout << k
                                                       // << " " <<
                                                       // theEventsCoincidences[k].tof
                                                       // * 1e6 <<
                // endl; std::cin.get();

                k++;
              }
              k = k - 1;
              if (k == -1) {
                k = 0;
              }
              // cout << "k " << k << " i " << i
              //      << " tof theEventsCoincidences antes "
              //      << theEventsCoincidences[k].tof * 1e6
              //      << " tof theEventsCoincidences despues "
              //      << theEventsCoincidences[k + 1].tof * 1e6 << endl;

              // cout << "eseum" << theEvents[i].esum << " "
              //      << theEventsCoincidences[k].esum << endl;

              // if (theEventsCoincidences[k].tof * 1e6 >
              //     (Tof_ns - CoincidenceWindow)) {
              //   cout << "If true" << theEventsCoincidences[k].tof * 1e6 <<
              //   "
              //   >"
              //        << Tof_ns - CoincidenceWindow << endl;
              //   cout << "Entra por abajo" << endl;
              //   std::cin.get();
              // }
              // if (theEventsCoincidences[k + 1].tof * 1e6 <
              //     (Tof_ns + CoincidenceWindow)) {
              //   cout << "If true" << theEventsCoincidences[k + 1].tof * 1e6
              //        << " <" << Tof_ns + CoincidenceWindow << endl;
              //   cout << "Entra por arriba" << endl;
              //   std::cin.get();
              //   k++;
              // }
              if (!((theEventsCoincidences[k + 1].tof > 0) &&
                    ((theEventsCoincidences[k + 1].tof * 1e6 <
                      (Tof_ns + CoincidenceWindow)) ||
                     (theEventsCoincidences[k].tof * 1e6 >
                      (Tof_ns - CoincidenceWindow))))) {
                hEn[thisPulseType][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, Mul)]
                       ->Fill(NeutEne, Edep);
                hEn[thisPulseType][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, 0)]
                       ->Fill(NeutEne, Edep);
                hEn[0][j]
                   [FindDetectorPosition(TheHistoInfo.DetectorNumber, Mul)]
                       ->Fill(NeutEne, Edep);
                hEn[0][j][FindDetectorPosition(TheHistoInfo.DetectorNumber, 0)]
                    ->Fill(NeutEne, Edep);
              }
            }
          }
        }
      }
    }
  }

  return 0;
}
int FillType13(int thisPulseType, int NEvents, Event* theEvents, TH2D**** hEn,
               double EdepThresholdMin, double EdepThresholdMax,
               HistoInfo* TheHistoInfo) {
  int FillType = 13;
  for (int j = 0; j < (int)TheHistoInfo->HistoType.size(); j++) {
    // cout << " Test " << FillType << " " << TheHistoInfo->HistoType[j] << ""
    //  << NSignals << endl;
    if (FillType == TheHistoInfo->HistoType[j]) {
      for (int i = 0; i < NEvents; i++) {
        double NeutEne = theEvents[i].eNeutron;
        double Edep = theEvents[i].esum;
        int Mul = theEvents[i].mult;
        int Weight = theEvents[i].weight;

        //   cout << i << " " << theEvents[i].tof << endl;
        // cout << "Event " << i << " Ene " << NeutEne << " Edep " << Edep
        //      << " Mul " << Mul << endl;
        if (Edep > EdepThresholdMin && Edep < EdepThresholdMax) {
          if (-1 != FindDetectorPosition(TheHistoInfo->DetectorNumber,
                                         Mul)) {  // Check if the detector
                                                  // number is in TheHistoInfo
            // cout << "Fill " << thisPulseType << " "
            //      << TheHistoInfo->HistoType[j] << " " << DetN << Edep << "
            //      "
            //      << NeutEne << endl;
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, Mul)]
                   ->Fill(NeutEne, Edep, Weight);
            hEn[thisPulseType][j]
               [FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                   ->Fill(NeutEne, Edep, Weight);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, Mul)]
                ->Fill(NeutEne, Edep, Weight);
            hEn[0][j][FindDetectorPosition(TheHistoInfo->DetectorNumber, 0)]
                ->Fill(NeutEne, Edep, Weight);

            // h2[ptype][HistoType][det]
          }
        }
      }
    }
  }
  return 0;
}
/****************************************************************
*************************************************************************
************************************************************************/

#endif
