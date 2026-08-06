#ifndef CREATEHISTOFUNCTIONS_HH
#define CREATEHISTOFUNCTIONS_HH 1

#include "CalibrationManager.hh"

//================================================================================================
void CreateTH1DHistoPulseIntesity(TH1D** h1, int N_PULSETYPE, int N_DETECTOR,
                                  TFile* fout);

void CreateTH2DHisto(HistoInfo* theHistoInfo, int N_PULSETYPE, TH2D**** h2,
                     TFile* fout);
//================================================================================================

void CreateTH1DHistoPulseIntesity(TH1D** h1, int N_PULSETYPE, TFile* fout) {
  char hname[100];
  char htitle[300];

  for (int ptype = 0; ptype < N_PULSETYPE; ptype++) {
    sprintf(hname, "hPulIntens_%d", ptype);
    sprintf(htitle,
            "Pulse intensities for  PulseType %d "
            "[NProtons,NPulses,PKUPamp,PKUParea,SILICounts]",
            ptype);
    h1[ptype] = new TH1D(hname, htitle, 5, 0.5, 5.5);
    h1[ptype]->SetDirectory(fout);
  }
  for (int ptype = 0; ptype < N_PULSETYPE; ptype++) {
    sprintf(hname, "hProtonsIntensity_%d", ptype);
    sprintf(htitle, "Histogram of Proton intensity pulses %d ", ptype);
    h1[N_PULSETYPE + ptype] = new TH1D(hname, htitle, 1e4, 0, 1e13);
    h1[N_PULSETYPE + ptype]->SetDirectory(fout);
  }
}

void CreateTH2DHisto(std::vector<string> ThereIsNameDetector,
                     HistoInfo* theHistoInfo, int N_PULSETYPE, TH2D**** h2,
                     TFile* fout) {
  if (std::find(ThereIsNameDetector.begin(), ThereIsNameDetector.end(),
                theHistoInfo->DetectorName) != ThereIsNameDetector.end()) {
    cout << endl << "Create histos for " << theHistoInfo->DetectorName << endl;

    string hName, hTitle;

    double* xaxis;

    for (int HistoType = 0; HistoType < (int)theHistoInfo->HistoType.size();
         HistoType++) {
      cout << "CreateTH2DHisto " << HistoType << " "
           << theHistoInfo->HistoName[HistoType] << " "
           << theHistoInfo->HistoType[HistoType] << endl;
    }
    for (int ptype = 0; ptype < N_PULSETYPE; ptype++) {
      h2[ptype] = new TH2D**[theHistoInfo->HistoType.size() + 1];

      for (int HistoType = 0; HistoType < (int)theHistoInfo->HistoType.size();
           HistoType++) {
        h2[ptype][HistoType] = new TH2D*[theHistoInfo->DetectorNumber.size()];
        xaxis = new double[(int)theHistoInfo->Xaxis[HistoType][0] + 1];
        if (theHistoInfo->HistoType[HistoType] == 1 ||
            theHistoInfo->HistoType[HistoType] == 5 ||
            theHistoInfo->HistoType[HistoType] == 7 ||
            theHistoInfo->HistoType[HistoType] == 9 ||
            theHistoInfo->HistoType[HistoType] == 10 ||
            theHistoInfo->HistoType[HistoType] == 11 ||
            theHistoInfo->HistoType[HistoType] == 12 ||
            theHistoInfo->HistoType[HistoType] == 13) {
          for (int i = 0; i <= theHistoInfo->Xaxis[HistoType][0]; i++) {
            // if()
            xaxis[i] = theHistoInfo->Xaxis[HistoType][1] *
                       pow(theHistoInfo->Xaxis[HistoType][2] /
                               theHistoInfo->Xaxis[HistoType][1],
                           i / (double)theHistoInfo->Xaxis[HistoType][0]);
          }
        } else if (theHistoInfo->HistoType[HistoType] == 2 ||
                   theHistoInfo->HistoType[HistoType] == 3 ||
                   theHistoInfo->HistoType[HistoType] == 4 ||
                   theHistoInfo->HistoType[HistoType] == 6 ||
                   theHistoInfo->HistoType[HistoType] == 8) {
          for (int i = 0; i <= theHistoInfo->Xaxis[HistoType][0]; i++) {
            // if()
            xaxis[i] = theHistoInfo->Xaxis[HistoType][1] +
                       (i *
                        (theHistoInfo->Xaxis[HistoType][2] -
                         theHistoInfo->Xaxis[HistoType][1]) /
                        (double)theHistoInfo->Xaxis[HistoType][0]);
            // cout << i << " " << xaxis[i] << endl;
          }
        }

        else {
          cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
               << " ###########" << endl;
          exit(1);
        }
        for (int det = 0; det < ((int)theHistoInfo->DetectorNumber.size());
             det++) {
          hName = theHistoInfo->HistoName[HistoType] + "_" +
                  theHistoInfo->DetectorName + "_" +
                  to_string(theHistoInfo->DetectorNumber[det]) + "_PType_" +
                  to_string(ptype);
          hTitle = theHistoInfo->HistoTitle[HistoType] + "_" +
                   theHistoInfo->DetectorName + "_" +
                   to_string(theHistoInfo->DetectorNumber[det]) + "_PType_" +
                   to_string(ptype);
          //

          if (theHistoInfo->Yaxis[HistoType].size() == 3) {
            h2[ptype][HistoType][det] =
                new TH2D(hName.c_str(), hTitle.c_str(),
                         theHistoInfo->Xaxis[HistoType][0], xaxis,
                         theHistoInfo->Yaxis[HistoType][0],
                         theHistoInfo->Yaxis[HistoType][1],
                         theHistoInfo->Yaxis[HistoType][2]);
          } else {
            double* yaxis;
            yaxis = new double[(int)theHistoInfo->Yaxis[HistoType].size()];
            for (int j = 0; j < ((int)theHistoInfo->Yaxis[HistoType].size());
                 j++) {
              yaxis[j] = theHistoInfo->Yaxis[HistoType][j];
              // cout << "yaxis[" << j << "]" << yaxis[j] << endl;
            }

            h2[ptype][HistoType][det] =
                new TH2D(hName.c_str(), hTitle.c_str(),
                         theHistoInfo->Xaxis[HistoType][0], xaxis,
                         theHistoInfo->Yaxis[HistoType].size() - 1, yaxis);
          }

          h2[ptype][HistoType][det]->GetYaxis()->SetTitle("E_{dep}(MeV)");
          if (theHistoInfo->HistoType[HistoType] == 1 ||
              theHistoInfo->HistoType[HistoType] == 5 ||
              theHistoInfo->HistoType[HistoType] == 13) {
            h2[ptype][HistoType][det]->GetXaxis()->SetTitle(
                "Neutron energy (eV)");
          } else if (theHistoInfo->HistoType[HistoType] == 2 ||
                     theHistoInfo->HistoType[HistoType] == 3 ||
                     theHistoInfo->HistoType[HistoType] == 4 ||
                     theHistoInfo->HistoType[HistoType] == 8) {
            h2[ptype][HistoType][det]->GetXaxis()->SetTitle("TOF (ns)");
          } else if (theHistoInfo->HistoType[HistoType] == 9) {
            h2[ptype][HistoType][det]->GetXaxis()->SetTitle("TOF (ns)");
            h2[ptype][HistoType][det]->GetYaxis()->SetTitle(
                "Neutron energy (eV)");
          }
          h2[ptype][HistoType][det]->SetDirectory(fout);
        }
      }
    }
  }
}
#endif
