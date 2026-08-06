
#ifndef FILLHISTOFUNCTIONS_HH
#define FILLHISTOFUNCTIONS_HH 1

#include "GetSignalsFunctions.hh"

//=====================================================================================
int FillPulseIntensity(int N_PULSETYPE, int thisPulseType,
                       double PulseIntensity, double PKUPAmp, double PKUPArea,
                       TH1D** hPulIntens);

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

/****************************************************************
*************************************************************************
************************************************************************/

#endif
