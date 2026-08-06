#ifndef GETSIGNALSFUNCTIONS_HH
#define GETSIGNALSFUNCTIONS_HH 1

#include "CreateHistoFunctions.hh"
//================================================================================================
int GetSignals(string DetectorName, std::vector<double> DetectorDeadTime_ns,
               TTree* tr, Signal* theS, Long64_t EntryMin, Long64_t EntryMax,
               Signal* theSignals, CalibrationManager* theCalibM, int CondType,
               double TFlashs);
double GetAvgTFlash(Signal* theSignals, int NSignals);
double GetTflash(Signal* theSignals, int NSignals, int DetN);
int FindDetectorPosition(const std::vector<double>& vector, double numero);
int MakeCoincidences(int NSignals, Signal* theSignals, Event* theEvents,
                     double& PulseTFlash_ms, double Coinc_Window,
                     FullEvent* theFullEvents);
//================================================================================================

// CondType=0 --> se cogen todas las señales
// CondType==1 --> se cogen solo las señales que cumplen las condiciones del
// threshold If TFlash<0, se coge el TFlash de las señales
int GetSignals(string DetectorName, std::vector<double> DetectorDeadTime_ns,
               TTree* tr, Signal* theS, Long64_t EntryMin, Long64_t EntryMax,
               Signal* theSignals, CalibrationManager* theCalibM, int CondType,
               double TFlash) {
  double SignalEne, SignalTOF, SignalTFlash, TimeOfFlightDistance;
  double EdepPreviousSignal[NDetectorMAX], TOFPreviousSignal[NDetectorMAX];
  for (Long64_t i = 0; i < NDetectorMAX; i++) {
    EdepPreviousSignal[i] = -1;
    TOFPreviousSignal[i] = -1;
  }

  int NSignals = 0;

  for (Long64_t i = EntryMin; i <= EntryMax; i++) {
    // cout << "DetectorName: " << DetectorName << ", Entry: " << i << endl;
    tr->GetEntry(i);
    theS->DetName = DetectorName;
    SignalEne = theCalibM->TakeEnergy(theS);
    SignalTOF = theCalibM->TakeTOF(theS);
    // cout << TFlash << " antes " << endl;
    SignalTFlash = TFlash;
    if (TFlash < 0) {
      SignalTFlash = theCalibM->TakeTFlash(theS);
    } else {
    }
    if (std::isnan(SignalTFlash)) {
      std::cout << "TFlash es NaN" << std::endl;
      cout << "DetectorName: " << DetectorName << ", Entry: " << i << endl;
      cout << TFlash << " " << theCalibM->TakeTFlash(theS) << endl;
      exit(1);
    }
    if (CondType == 0 ||
        (CondType == 1 && theCalibM->IsInsideThresholdLimits(theS))) {
      if ((1.0e6 * (SignalTOF - TOFPreviousSignal[theS->detn])) >
          DetectorDeadTime_ns[theS->detn]) {  // added to remove deadtime
                                              // signals

        theSignals[NSignals].edep = SignalEne;
        theSignals[NSignals].tof = SignalTOF;
        theSignals[NSignals].tflash = SignalTFlash;
        TimeOfFlightDistance = theCalibM->TakeTOFD(theS);
        theSignals[NSignals].tofdistance = TimeOfFlightDistance;

        theSignals[NSignals].eNeutron =
            TOFtoE((SignalTOF - SignalTFlash) * 1.e6, TimeOfFlightDistance);
        theSignals[NSignals].detn = theS->detn;
        theSignals[NSignals].edepPreviousSignal =
            EdepPreviousSignal[theS->detn];
        theSignals[NSignals].tofPreviousSignal = TOFPreviousSignal[theS->detn];
        theSignals[NSignals].weight = theCalibM->TakeWeight(theS);

        EdepPreviousSignal[theS->detn] = theSignals[NSignals].edep;
        TOFPreviousSignal[theS->detn] = theSignals[NSignals].tof;
        NSignals++;
      }
    }
  }

  return NSignals;
}

// VERSION DE GetAvgTFlash DE ADRIAN
double GetAvgTFlash(Signal* theSignals, int NSignals) {
  double TFlash[NDetectorMAX + 1];
  for (int ndet = 1; ndet <= NDetectorMAX; ndet++) {
    TFlash[ndet] = GetTflash(theSignals, NSignals, ndet);
  }

  double Sum = 0;
  int count = 0;
  for (int i = 1; i <= NDetectorMAX; i++) {
    if (TFlash[i] * 1.e6 < TFLASH_BAF2_MAX_NS &&
        TFlash[i] * 1.e6 > TFLASH_BAF2_MIN_NS) {
      Sum += TFlash[i];
      count++;
    }
  }

  // return TFlash/(double)NSig;
  return Sum / (double)count;  // in ms
}

double GetTflash(Signal* theSignals, int NSignals, int DetN) {
  for (int i = 0; i < NSignals; i++) {
    if (theSignals[i].detn == DetN) {
      return theSignals[i].tflash;
    }
  }
  return 0;
}

int MakeCoincidences(int NSignals, Signal* theSignals, Event* theEvents,
                     double& PulseTFlash_ms, double Coinc_Window,
                     FullEvent* theFullEvents) {
  // Step 1: Sort all signals in time (they all belong to the same pulse)
  qsort(theSignals, NSignals, sizeof(Signal), TOFComparison);

  // If PulseTFlash_ms is negative, compute its average from the signals
  if (PulseTFlash_ms < 0) {
    PulseTFlash_ms = GetAvgTFlash(theSignals, NSignals);
  }

  // Safety check: make sure PulseTFlash_ms is not NaN
  if (std::isnan(PulseTFlash_ms)) {
    std::cout << "TFlash is NaN in MakeCoincidences" << std::endl;
    exit(1);
  }

  // Step 2: Initialize event-related variables
  double EventTOF = -1, EventESum = 0, EventEn = 0, EventWeight = 0;
  int EventMult = 0;
  int nEvents = 0;

  // Step 3: Loop over all signals and group them into coincidences
  for (int ns = 0; ns < NSignals; ns++) {
    // Check if the current signal is outside the coincidence time window
    if ((theSignals[ns].tof * 1.e6 - EventTOF * 1.e6) > Coinc_Window) {
      // If true, we have a new event (new coincidence)
      if (ns != 0) {  // Save the previous event before starting a new one
        if (theEvents) {
          theEvents[nEvents].esum = EventESum;
          theEvents[nEvents].mult = EventMult;
          theEvents[nEvents].tof = EventTOF;
          theEvents[nEvents].eNeutron = EventEn;
          theEvents[nEvents].CoincFlag = 0;
          theEvents[nEvents].weight = EventWeight;  //
        }
        if (theFullEvents) {
          theFullEvents[nEvents].esum = EventESum;
          theFullEvents[nEvents].mult = EventMult;
          theFullEvents[nEvents].tof = EventTOF;
          theFullEvents[nEvents].eNeutron = EventEn;
          theFullEvents[nEvents].weight = EventWeight;
        }
        nEvents++;

        // Avoid exceeding the event array limit
        if (nEvents >= MAXNEVENTSINPULSE) {
          cout << " ####### Error in " << __FILE__ << ", line " << __LINE__
               << " #######" << endl;
          exit(1);
        }
      }

      // Initialize parameters for the new event
      EventMult = 1;
      EventESum = theSignals[ns].edep;
      EventTOF = theSignals[ns].tof;
      EventWeight = theSignals[ns].weight;
      //                  TOFtoE((SignalTOF - SignalTFlash) * 1.e6,
      //                  TimeOfFlightDistance);

      EventEn = TOFtoE((EventTOF - PulseTFlash_ms) * 1.e6,
                       theSignals[ns].tofdistance);
      // cout << "theSignals[ns].tofdistance" << theSignals[ns].tofdistance
      //      << endl;

      // cout << "PulseTFlash_ms: " << PulseTFlash_ms
      //      << " theSignals[ns].tflash: " << theSignals[ns].tflash << endl;
      // cout << "EventTOF: " << EventTOF
      //      << " theSignals[ns].tof: " << theSignals[ns].tof << endl;
      // cout << "EventEn: " << EventEn
      //      << " theSignals[ns].eNeutron: " << theSignals[ns].eNeutron <<
      //      endl;

      // Initialize detailed event info if FullEvent structure is used
      if (theFullEvents) {
        for (int i = 0; i < 41; i++) {
          theFullEvents[nEvents].EdepDet[i] = 0;
          theFullEvents[nEvents].TofDet[i] = 0;
          theFullEvents[nEvents].WeightDet[i] = 0;
        }
        // Store detector-specific energy and TOF for the current signal
        theFullEvents[nEvents].EdepDet[theSignals[ns].detn] =
            theSignals[ns].edep;
        theFullEvents[nEvents].TofDet[theSignals[ns].detn] = theSignals[ns].tof;
        theFullEvents[nEvents].WeightDet[theSignals[ns].detn] =
            theSignals[ns].weight;
      }

    } else {
      // Signal falls inside the coincidence window → same event
      EventESum += theSignals[ns].edep;
      EventWeight += theSignals[ns].weight;
      EventMult++;

      // Store per-detector info if using FullEvent
      if (theFullEvents) {
        theFullEvents[nEvents].EdepDet[theSignals[ns].detn] =
            theSignals[ns].edep;
        theFullEvents[nEvents].TofDet[theSignals[ns].detn] = theSignals[ns].tof;
        theFullEvents[nEvents].WeightDet[theSignals[ns].detn] =
            theSignals[ns].weight;
        // (Optional) debugging lines below show timing differences
        // cout << setprecision(10) << ns << " " << theSignals[ns].detn << " "
        //      << theSignals[ns].edep << " " << theSignals[ns].tof * 1e6 << " "
        //      << theSignals[ns - 1].tof * 1e6 << " "
        //      << (theSignals[ns].tof - theSignals[ns - 1].tof) * 1e6 << "  "
        //      << (theSignals[ns].tof * 1e6 - theSignals[ns - 1].tof * 1e6)
        //      << endl;
      }
    }
  }

  // Step 4: Add the last event if there was one still open
  if (EventMult > 0) {
    if (theEvents) {
      theEvents[nEvents].esum = EventESum;
      theEvents[nEvents].mult = EventMult;
      theEvents[nEvents].tof = EventTOF;
      theEvents[nEvents].eNeutron = EventEn;
      theEvents[nEvents].CoincFlag = 0;
      theEvents[nEvents].weight = EventWeight;
    }
    if (theFullEvents) {
      theFullEvents[nEvents].esum = EventESum;
      theFullEvents[nEvents].mult = EventMult;
      theFullEvents[nEvents].tof = EventTOF;
      theFullEvents[nEvents].eNeutron = EventEn;
      theFullEvents[nEvents].weight = EventWeight;
    }
    nEvents++;

    // Check array size again
    if (nEvents >= MAXNEVENTSINPULSE) {
      cout << " ####### Error in " << __FILE__ << ", line " << __LINE__
           << " #######" << endl;
      exit(1);
    }
  }

  // Step 5: Return total number of events found in this pulse
  return nEvents;
}

#endif
