#include "DefPlot2DHisto_2026_LaBr_v01.hh"
// #include "DefPlot2DHisto_2026_FC-U_v01.hh"

///
///

#include "../GeneralFun/PlotFunctions_Victor.hh"

void plot2D(std::vector<string> NameHisto, std::vector<string> MeasurementType,
            std::vector<int> detN, std::vector<double> EnOrEdepMin,
            std::vector<double> EnOrEdepMax, std::vector<int> PType,
            string TypeOfPlot, std::vector<int> rebin,
            bool UseBackgroundSubtracted = false, bool IfNormalize = false,
            bool CompareWithSimul = false, bool CalculateRatio = false,
            string IfSaveName = "-1");

void plot2D(std::vector<string> NameHisto, std::vector<string> MeasurementType,
            std::vector<int> detN, std::vector<double> EnOrEdepMin,
            std::vector<double> EnOrEdepMax, std::vector<int> PType,
            string TypeOfPlot, int rebin, bool UseBackgroundSubtracted = false,
            bool IfNormalize = false, bool CompareWithSimul = false,
            bool CalculateRatio = false, string IfSaveName = "-1");

void Plot2DHisto() {
  /*
 plot2D({"En"}, {"Sb123"}, {0}, {0.15}, {9.999}, {1}, "Yield", {100}, 1,1,1);
 plot2D({"En"}, {"Au","Au_3","Au_4","Au_5","Au_6"}, {0}, {0.15}, {9.999},
{1},"Yield", {10000}, 1,0,0,1); plot2D({"Edep"},
{"Cs_1","Cs_2","Cs_3","Cs_4","Cs_5","Cs_6","Cs_7","Cs_8","Cs_9","Cs_12","Cs_13","Cs_14","Cs_14"},
{1},{0.15}, {9.999}, {3}, "CR", {1}, 0,0,0);

plot2D({"Edep"},
{"Ba_4","Ba_5","Ba_6","Ba_7","Ba_8","Ba_10","Ba_11","Ba_12","Ba_13","Ba_14"},
{2},{0.15}, {9.999}, {3}, "CR", {1}, 1);

plot2D({"Edep"},
{"AmBe_2","AmBe_3","AmBe_4","AmBe_6","AmBe_7","AmBe_8"}, {2},{0.15},
{9.999}, {3}, "CR", {10}, 1);


 plot2D({"Edep"},
{"Y_4","Y_5","Y_6","Y_7","Y_8"}, {4}, {0.15},{9.999}, {3}, "CR", {1}, 1);
plot2D({"Edep"}, {"Ba_4","Ba_5","Ba_6"}, {4}, {0.15},{9.999}, {3}, "CR", {1},
1); plot2D({"Edep"},
{"Background","Background_1","Background_2","Background_3","Background_4","Background_5","Background_6","Background_7","Background_8"},
{1}, {0.15}, {9.999}, {3}, "CR", {4});
 */
}
void plot2D(std::vector<string> NameHisto, std::vector<string> MeasurementType,
            std::vector<int> detN, std::vector<double> EnOrEdepMin,
            std::vector<double> EnOrEdepMax, std::vector<int> PType,
            string TypeOfPlot, int rebin, bool UseBackgroundSubtracted,
            bool IfNormalize, bool CompareWithSimul, bool CalculateRatio,
            string IfSaveName) {
  vector<int> REBIN;
  REBIN.push_back(rebin);
  plot2D(NameHisto, MeasurementType, detN, EnOrEdepMin, EnOrEdepMax, PType,
         TypeOfPlot, REBIN, UseBackgroundSubtracted, IfNormalize,
         CompareWithSimul, CalculateRatio, IfSaveName);
}
void plot2D(std::vector<string> NameHisto, std::vector<string> MeasurementType,
            std::vector<int> detN, std::vector<double> EnOrEdepMin,
            std::vector<double> EnOrEdepMax, std::vector<int> PType,
            string TypeOfPlot, std::vector<int> rebin,
            bool UseBackgroundSubtracted, bool IfNormalize,
            bool CompareWithSimul, bool CalculateRatio, string IfSaveName) {
  // performs the integrals
  bool Integrate = true;
  // -------------------------------------------------
  int NameHistoSize = NameHisto.size();
  int MeasurementTypeSize = MeasurementType.size();
  int detNSize = detN.size();
  int EnOrEdepMinSize = EnOrEdepMin.size();
  int EnOrEdepMaxSize = EnOrEdepMax.size();
  int PTypeSize = PType.size();
  int rebinSize = rebin.size();

  int NumberOfHisto = NameHistoSize * MeasurementTypeSize * detNSize *
                      EnOrEdepMinSize * EnOrEdepMaxSize * PTypeSize * rebinSize;
  cout << "NumberOfHisto " << NumberOfHisto << endl;
  double npulses[NumberOfHisto];
  double nprotons[NumberOfHisto];
  TH1D* h1[NumberOfHisto];
  TH1D* h1GainShift[NumberOfHisto];

  TCanvas* c2[NumberOfHisto];
  string TitleLegend[NumberOfHisto];
  string TitleHisto;
  string SaveName = DirectionSave2DHisto + NameDetector + "_" + NameHisto[0];
  double Returnpulses, Returnprotons;
  int n = 0;
  string fname;
  TH1D* hSimul;
  TH1D* hSimul2[10];
  int const hSimul2Size = 1;

  bool SubtractBackground = false;
  double Used_PType[NumberOfHisto];
  double Used_rebin[NumberOfHisto];
  double Used_EnOrEdepMin[NumberOfHisto];
  double Used_EnOrEdepMax[NumberOfHisto];
  double ifEnOrEdepMaxAndEnOrEdepMinCouple = false;
  bool IfEnOrEdep = true;
  if (NameHisto[0] == "Edep") {
    IfEnOrEdep = false;
  }
  if (NameHisto[0] == "Edep_WF") {
    IfEnOrEdep = false;
  }

  if (EnOrEdepMinSize > 1 && (EnOrEdepMinSize == EnOrEdepMaxSize)) {
    EnOrEdepMaxSize = 1;
    ifEnOrEdepMaxAndEnOrEdepMinCouple = true;
    NumberOfHisto =
        MeasurementTypeSize * detNSize * EnOrEdepMinSize * PTypeSize;
  }
  for (auto p = 0; p < NameHistoSize; p++) {
    for (auto i = 0; i < MeasurementTypeSize; i++) {
      fname = Direction2DHisto + MeasurementType[i] + ".root";
      SaveName = SaveName + "_" + MeasurementType[i];
      for (auto j = 0; j < detNSize; j++) {
        if (i == 0) {
          SaveName = SaveName + "_Det" + to_string(detN[j]);
        }
        for (auto k = 0; k < EnOrEdepMinSize; k++) {
          if (ifEnOrEdepMaxAndEnOrEdepMinCouple) {
            EnOrEdepMaxSize = 1;
          }

          for (auto l = 0; l < EnOrEdepMaxSize; l++) {
            if (ifEnOrEdepMaxAndEnOrEdepMinCouple) {
              l = k;
            }
            for (auto m = 0; m < PTypeSize; m++) {
              for (auto q = 0; q < rebinSize; q++) {
                if (i == 0 && j == 0) {
                  SaveName = SaveName + "_PType" + to_string(PType[m]);
                }
                if (NameHistoSize != 1) {
                  TitleLegend[n] = TitleLegend[n] + NameHisto[p];
                }
                if (MeasurementTypeSize != 1) {
                  TitleLegend[n] = TitleLegend[n] + MeasurementType[i];
                }
                if (detNSize != 1) {
                  TitleLegend[n] =
                      TitleLegend[n] + " Det " + to_string(detN[j]);
                }
                if (EnOrEdepMinSize != 1 || EnOrEdepMaxSize != 1) {
                  if (IfEnOrEdep) {
                    TitleLegend[n] =
                        TitleLegend[n] + " (" +
                        doubleToDecimalString(EnOrEdepMin[k], 2) + "," +
                        doubleToDecimalString(EnOrEdepMax[l], 1) + ") MeV";
                  } else {
                    if (EnOrEdepMin[k] > 99) {
                      TitleLegend[n] =
                          TitleLegend[n] + " (" +
                          doubleToDecimalString(EnOrEdepMin[k] / 1000, 2) +
                          "," +
                          doubleToDecimalString(EnOrEdepMax[l] / 1000, 1) +
                          ") keV";
                    } else {
                      TitleLegend[n] =
                          TitleLegend[n] + " (" +
                          doubleToDecimalString(EnOrEdepMin[k], 2) + "," +
                          doubleToDecimalString(EnOrEdepMax[l], 1) + ") eV";
                    }
                  }
                }

                if (PTypeSize != 1) {
                  TitleLegend[n] =
                      TitleLegend[n] + " PType " + to_string(PType[m]);
                }
                if (rebinSize != 1) {
                  TitleLegend[n] =
                      TitleLegend[n] + " rebin " + to_string(rebin[q]);
                }
                cout << "fname " << fname << endl;

                if (UseBackgroundSubtracted) {
                  c2[n] = new TCanvas(TitleLegend[n].c_str(),
                                      TitleLegend[n].c_str(), 800, 600);

                  h1[n] = Project2DHistoSubtractBackground(
                      Direction2DHisto, NameDetector, NameHisto[p],
                      MeasurementType[i], PType[m], detN[j], IfEnOrEdep,
                      Returnpulses, Returnprotons, TOFD, EnOrEdepMin[k],
                      EnOrEdepMax[l], TimeMeasurement_ns, MeasPredefined,
                      BackgroundMeasPredefined, DummyPredefined,
                      BackgroundDummyPredefined, c2[n], CorrectDeadTime);

                } else {
                  h1[n] = Project2DHisto(
                      fname, NameDetector, NameHisto[p], MeasurementType[i],
                      PType[m], detN[j], IfEnOrEdep, Returnpulses,
                      Returnprotons, TOFD, EnOrEdepMin[k], EnOrEdepMax[l],
                      TimeMeasurement_ns, CorrectDeadTime);
                }
                /// int NotUSed = ChangeTOFD(h1[n], TOFD, 183.96);
                // Change TOF     in case of needed
                npulses[n] = Returnpulses;
                nprotons[n] = Returnprotons;
                Used_PType[n] = PType[m];
                Used_rebin[n] = rebin[q];

                Used_EnOrEdepMin[n] = EnOrEdepMin[k];
                Used_EnOrEdepMax[n] = EnOrEdepMax[l];
                // cout << i << " " << TitleLegend[i] << " pulses " <<
                // npulses[n]
                //    << " nprotons " << nprotons[n] << endl;
                h1[n]->SetLineColor(n + 10001);
                n++;
              }
            }
          }
        }
      }
    }
  }
  hSimul = (TH1D*)h1[0]->Clone();
  for (int i = 0; i < hSimul2Size; i++) {
    hSimul2[i] = (TH1D*)h1[0]->Clone();
  }
  if (CompareWithSimul) {
    if (NameHisto[0] == "Edep") {
      cout << "Start with GetSimulMC" << endl;
      hSimul =
          GetSimulMC(h1[0], detN[0], MeasurementType[0], NameSimulArrayEdep,
                     NameSimulRootfileEdep, Activity_kBq, ResolNumberDetector,
                     ResolParameter1, ResolParameter2, TypeOfPlot, "0");
    } else if (NameHisto[0] == "Edep_WF") {
      cout << "Start with GetSimulMC" << endl;
      hSimul =
          GetSimulMC(h1[0], detN[0], MeasurementType[0], NameSimulArrayEdep,
                     NameSimulRootfileEdep, Activity_kBq, ResolNumberDetector,
                     ResolParameter1, ResolParameter2, TypeOfPlot, WFFile);
    } else {
      cout << "···············3" << MeasurementType[0] << " " << PType[0]
           << endl;
      hSimul = GetSimul(h1[0], MeasurementType[0], NameSimulArray,
                        NameSimulRootfile, TypeOfPlot);
      for (int i = 0; i < hSimul2Size; i++) {
        cout << "hsimul2 " << i << " "
             << NameSimulRootfile2[i][FindPositionString(NameSimulArray,
                                                         MeasurementType[0])]
             << endl;
        if (NameSimulRootfile2[i][FindPositionString(
                NameSimulArray, MeasurementType[0])] != "-1") {
          hSimul2[i] = GetSimul(h1[0], MeasurementType[0], NameSimulArray,
                                NameSimulRootfile2[i], TypeOfPlot);
          hSimul2[i]->SetLineColor(10002 + i);
          hSimul2[i]->Rebin(rebin[0]);
          hSimul2[i]->Scale(1.0 / (double)rebin[0]);
        }
      }
    }
    hSimul->SetLineColor(kBlack);
  }
  hSimul->Rebin(rebin[0]);
  hSimul->Scale(1.0 / (double)rebin[0]);

  // hSimul2->Rebin(rebin[0]);
  //  hSimul2->Scale(1.0 / (double)rebin[0]);
  /// We define  the title of the histo
  TitleHisto = TitleHisto + NameDetector;
  if (MeasurementTypeSize == 1) {
    TitleHisto = TitleHisto + " " + MeasurementType[0];
    if (UseBackgroundSubtracted) {
      TitleHisto = TitleHisto + "-Bkgs";
    }
    if (IfNormalize && IfEnOrEdep) {
      TitleHisto = TitleHisto + " Nor (" +
                   doubleToDecimalString(NormalizeMinEn, 0) + "," +
                   doubleToDecimalString(NormalizeMaxEn, 0) + ") eV";
    }
    if (IfNormalize && (!IfEnOrEdep)) {
      TitleHisto = TitleHisto + " Nor (" +
                   doubleToDecimalString(NormalizeMinEdep, 0) + "," +
                   doubleToDecimalString(NormalizeMaxEdep, 0) + ") eV";
    }
  }

  if (detNSize == 1) {
    TitleHisto = TitleHisto + " Det" + to_string(detN[0]);
  }
  if (PTypeSize == 1) {
    TitleHisto = TitleHisto + " PType " + to_string(PType[0]);
  }
  if (EnOrEdepMinSize == 1 && EnOrEdepMaxSize == 1) {
    if (IfEnOrEdep) {
      TitleHisto = TitleHisto + " (" +
                   doubleToDecimalString(EnOrEdepMin[0], 2) + "," +
                   doubleToDecimalString(EnOrEdepMax[0], 1) + ") MeV";
    } else {
      TitleHisto = TitleHisto + " (" +
                   doubleToDecimalString(EnOrEdepMin[0], 1) + "," +
                   doubleToDecimalString(EnOrEdepMax[0], 1) + ") eV";
    }
  }
  if (CorrectDeadTime) {
    TitleHisto = TitleHisto + " DeadTimeCorrected";
  }
  cout << "TitleHisto " << TitleHisto << endl;

  /// We define Y axis for TypeOfPlot
  for (auto i = 0; i < NumberOfHisto; i++) {
    h1[i]->Rebin(Used_rebin[i]);
    // cout << "rebin " << rebin << " i " << i << endl;
    if (TypeOfPlot == "Counts") {
      cout << "Counts" << endl;
      h1[i]->GetYaxis()->SetTitle("counts");
    } else if (TypeOfPlot == "CPulse") {
      h1[i]->Scale(8.e12 / npulses[i]);
      h1[i]->GetYaxis()->SetTitle("counts/Pulses ");
    } else if (TypeOfPlot == "CP") {
      h1[i]->Scale(8.e12 / nprotons[i]);
      h1[i]->GetYaxis()->SetTitle("counts/8#upoint10^{12} protons  ");
    } else if (TypeOfPlot == "CP1e17") {
      h1[i]->Scale(1.e17 / nprotons[i]);
      h1[i]->GetYaxis()->SetTitle("counts/1#upoint10^{17} protons  ");
    } else if (TypeOfPlot == "Uncer") {
      h1[i]->Scale(1.e17 / nprotons[i]);
      h1[i]->GetYaxis()->SetTitle("Uncer (\%) for 1#upoint10^{17} protons  ");
      double CountsBinDel;
      for (int j = 1; j <= h1[i]->GetNbinsX(); j++) {
        CountsBinDel = 100 * (1.0 / (double)sqrt(h1[i]->GetBinContent(j)));
        h1[i]->SetBinContent(j, CountsBinDel);
        h1[i]->SetBinError(j, 0);
      }

    } else if (TypeOfPlot == "CR") {
      if (!IfEnOrEdep) {
        double BinWidth = h1[i]->GetBinWidth(1);
        // The idea is to have the number of counts per second.
        double scalefactor =
            DeltaEnergyToTime(Used_EnOrEdepMin[i], Used_EnOrEdepMax[i], TOFD) /
            TimeMeasurement_ns * (double)npulses[i];
        h1[i]->Scale(10.0 / BinWidth / scalefactor);
        h1[i]->GetYaxis()->SetTitle("counts/s/BinWidth");
        double CRDet =
            BinWidth / 1e6 *
            h1[i]->Integral(h1[i]->FindBin(0.15), h1[i]->FindBin(20));
        cout << "CR" << TitleLegend[i] << " threshold 0.15 MeV Det" << detN[i]
             << " " << CRDet << endl;
        if (IfNormalize) {
          TitleLegend[i] = TitleLegend[i] +
                           " CR=" + doubleToDecimalString(CRDet, 3) + " c/#mus";
        }
      } else {
        h1[i]->Scale(1.0 / npulses[i]);
        DivideByBinTime(h1[i], TOFD);
        h1[i]->GetYaxis()->SetTitle("counts/#mus");
      }
    } else if (TypeOfPlot == "Yield_Sn_25mm") {
      h1[i]->Scale(7.e12 / nprotons[i]);
      // DivideByNeutronFluence_iso_AllYears(
      //     h1[i], "Flux_26_AllRuns_NoFilters_Until124680");
      DivideByNeutronFluence_iso_AllYears(h1[i], "h1");

      h1[i]->Scale(1.0 / 4.0);  // Because I use the 4 detectors
      h1[i]->Scale(
          1.0 /
          1.0);  // Scaling factor obtained wiht the Au saturated resonance

      h1[i]->GetYaxis()->SetTitle("Yield*Sn");
    } else if (TypeOfPlot == "Yield_Sn_20mm") {
      h1[i]->Scale(7.e12 / nprotons[i]);
      DivideByNeutronFluence_iso_AllYears(
          h1[i], "Flux_26_AllRuns_NoFilters_Until124680_20mm");
      h1[i]->Scale(1.0 / 4.0);  // Because I use the 4 detectors
      h1[i]->Scale(
          1.0 /
          1.18);  // Scaling factor obtained wiht the Au saturated resonance

      h1[i]->GetYaxis()->SetTitle("Yield*Sn");
    } else if (TypeOfPlot == "Yield_Sn_13mm") {
      h1[i]->Scale(7.e12 / nprotons[i]);
      DivideByNeutronFluence_iso_AllYears(
          h1[i], "Flux_26_AllRuns_NoFilters_Until124680_13mm");
      h1[i]->Scale(1.0 / 4.0);  // Because I use the 4 detectors
      h1[i]->Scale(
          1.0 /
          1.14);  // Scaling factor obtained wiht the Au saturated resonance

      h1[i]->GetYaxis()->SetTitle("Yield*Sn");
    } else if (TypeOfPlot == "Yield") {
      if (NameDetector == "SILI") {
        // DivideByNeutronFluence_NOiso_2023(h1[i]);
        // DivideByLi6CS(h1[i]);
        // DivideByEfficiencySiMon1(h1[i]);
        DivideByLi6CS_Eff_Flux_2023(h1[i]);

        h1[i]->GetYaxis()->SetTitle(" Flux_{SILI}/Flux_{Eval}");
      } else {
        h1[i]->Scale(7.e12 / nprotons[i]);
        DivideByNeutronFluence_iso_AllYears(h1[i], "h1");
        // DivideByNeutronFluence_iso_2024(h1[i]);

        h1[i]->GetYaxis()->SetTitle("Yield* ");
      }
    } else if (TypeOfPlot == "YieldTXT") {
      h1[i]->Scale(7.e12 / nprotons[i]);
      DivideByNeutronFluence_iso_2023(h1[i]);
      // DivideByNeutronFluence_iso_2024(h1[i]);

      h1[i]->GetYaxis()->SetTitle("Yield* ");

      if (MeasurementTypeSize == 1 && NameHistoSize == 1 &&
          EnOrEdepMinSize == 1 && EnOrEdepMaxSize == 1 && PTypeSize == 1 &&
          rebinSize == 1) {
        int EnOrEdepMinSave = 1000 * EnOrEdepMin[0];
        int EnOrEdepMaxSave = 1000 * EnOrEdepMax[0];
        if (EnOrEdepMaxSave == 9999)
          EnOrEdepMaxSave =
              10000;  // Lo hago para poder poner 9.999 y que coja el bin de 10
        string SaveTxtYield =
            SaveYieldFolder + "Y_" + MeasurementType[0] + "_" + NameHisto[0] +
            "_D" + to_string(detN[i]) + "_E" + to_string(EnOrEdepMinSave) +
            "_" + to_string(EnOrEdepMaxSave) + "_PT" + to_string(PType[0]) +
            "_R" + to_string(rebin[0]) + ".txt";
        ofstream ofs(SaveTxtYield);
        for (int j = 1; j <= h1[i]->GetNbinsX(); j++) {
          if (h1[i]->GetBinContent(j) < 0) {
            // cout << "The Yield is negative, so I put it to zero " <<
            // h1[i]->GetBinContent(j) << " " << std::scientific << "       "
            //  << h1[i]->GetBinCenter(j) << "        " <<
            //  h1[i]->GetBinContent(j) << "        " << h1[i]->GetBinError(j)
            //  << endl;
            ofs << std::scientific << "       " << h1[i]->GetBinCenter(j)
                << "        " << 0.00000000000000000 << "        "
                << h1[i]->GetBinError(j) << endl;
          } else {
            ofs << std::scientific << "       " << h1[i]->GetBinCenter(j)
                << "        " << h1[i]->GetBinContent(j) << "        "
                << h1[i]->GetBinError(j) << endl;
          }
        }
        ofs.close();
        cout << "SaveTxtYield " << SaveTxtYield << endl;
      }

    }

    else if (TypeOfPlot ==
             "CountsTXT") {  /// counts per 7e12 protons per bin width
      cout << " Do CountsTXT" << endl;
      h1[i]->Scale(7.e12 / nprotons[i]);
      DivideByBinWidth(h1[i]);

      int nbins = h1[i]->GetNbinsX();
      double val, err, ene1;
      for (int j = 1; j <= nbins; j++) {
        val = h1[i]->GetBinContent(j);
        err = h1[i]->GetBinError(j);
        ene1 = h1[i]->GetBinCenter(j);
        cout << ene1 << " " << val << endl;
      }

      h1[i]->GetYaxis()->SetTitle("counts/7#upoint10^{12} protons/BinWidth");
    } else {
      cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
           << " ###########" << endl;
      exit(1);
    }
  }

  cout << "after counts" << endl;

  if (!CompareWithSimul) {
    hSimul = (TH1D*)h1[0]->Clone();
  }
  /// We Normalize

  if (IfNormalize && IfEnOrEdep) {
    Normalize(h1, NumberOfHisto, hSimul, NormalizeMinEn, NormalizeMaxEn);
    if ((NameDetector == "SILI") && (TypeOfPlot == "Yield")) {
      double binValue;
      double LowLimit = 10.001;
      double HighLimit = 99.99;
      // calculate the integral in the range dividing by th enumber of bins;
      binValue =
          h1[0]->Integral(h1[0]->FindBin(LowLimit), h1[0]->FindBin(HighLimit)) /
          (1 + (h1[0]->FindBin(HighLimit) - h1[0]->FindBin(LowLimit)));
      cout << "Integral "
           << h1[0]->Integral(h1[0]->FindBin(LowLimit),
                              h1[0]->FindBin(HighLimit))
           << " Total Bins   "
           << 1 + (h1[0]->FindBin(HighLimit) - h1[0]->FindBin(LowLimit))
           << " to " << h1[0]->FindBin(HighLimit) << " binValue " << binValue
           << endl;

      hSimul->Scale(1.0 / binValue);
      ;

      for (auto i = 0; i < NumberOfHisto; i++) {
        h1[i]->Scale(1.0 / binValue);
        cout << "Scale to have the yield to one at 50 eV scalling by "
             << binValue << endl;
      }
      TFile* f1 = new TFile("DataPlot/evalFlux_prelim.root", "READ");
      TH1D* FluxEval = (TH1D*)f1->Get("hEval_Abs");
      TH1D* FluxCorrected = (TH1D*)FluxEval->Clone();

      int nbins = FluxCorrected->GetNbinsX();
      double ene1, ene2, ene, Value;
      for (int i = 1; i <= nbins; i++) {
        ene = FluxCorrected->GetBinCenter(i);
        Value = h1[0]->Interpolate(ene);
        if (ene < LowLimit && Value > 0.) {
          // cout << "ene " << ene << " Value " << Value << endl;
          FluxCorrected->SetBinContent(i,
                                       FluxCorrected->GetBinContent(i) * Value);
          //  FluxCorrected->SetBinError(i,
          //  FluxCorrected->GetBinError(i) / Value);
        }
      }

      TCanvas* c2 = new TCanvas("c2", "c2", 800, 600);
      c2->SetLogx();
      c2->SetLogy();
      FluxCorrected->SetLineColor(kRed);
      FluxEval->Draw("histo");
      FluxCorrected->Draw("histo same");

      TLegend* legend2 = new TLegend(0.6, 0.62, 0.96, 0.86, "");
      legend2->AddEntry(FluxEval, "Flux Eval", "l");
      legend2->AddEntry(FluxCorrected, "Flux Corrected", "l");

      legend2->SetTextSize(0.06);
      legend2->SetBorderSize(0);
      legend2->SetFillColor(0);
      legend2->SetFillStyle(0);
      legend2->Draw();
    }
  }
  if (IfNormalize && (!IfEnOrEdep)) {
    cout << "Beforenoramlize" << endl;

    Normalize(h1, n, hSimul, NormalizeMinEdep, NormalizeMaxEdep);
    if (!CompareWithSimul) {
      cout << "StartGAinsShift" << endl;

      double shiftArray[NumberOfHisto];
      double shift;
      for (auto i = 1; i < NumberOfHisto; i++) {
        h1GainShift[i] = CalculateBestShift(
            shift, h1[0], h1[i], NormalizeMinEdep, NormalizeMaxEdep,
            NumberIterations, MinShift, MaxShift);
        shiftArray[i] = shift;
        TitleLegend[i] =
            TitleLegend[i] + " G=" + doubleToDecimalString(shiftArray[i], 3);
        cout << TitleLegend[i] << " Shift= " << shiftArray[i] << endl;
      }
    }
  }

  TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
  TGaxis::SetMaxDigits(3);
  TPad* pad1;
  TPad* pad2 = new TPad("pad2", "Pad", 0.0, 0.02, 1., 0.33, 10);
  c1->ToggleEditor();

  if (CalculateRatio) {
    pad1 = new TPad("pad1", "Pad", 0.0, 0.33, 1., 1., 10);
    pad2 = new TPad("pad2", "Pad", 0.0, 0.02, 1., 0.33, 10);

    pad1->Draw();
    pad2->Draw();
    pad1->SetGridx();
    pad1->SetGridy();
    if (IfEnOrEdep) {
      pad1->SetLogy();
      pad1->SetLogx();
      pad2->SetLogx();
    }
    pad1->SetTopMargin(0.11);      // para que no se vea el eje
    pad1->SetBottomMargin(0.033);  // para que no se vea el eje
    // pad1_6->SetBottomMargin(0.2);//

    pad2->SetTopMargin(0.07);    // para que no se vea el eje
    pad2->SetBottomMargin(0.4);  // para que se vea el eje

    pad1->SetLeftMargin(0.15);  // para que no se vea el eje
    pad2->SetLeftMargin(0.15);  // para que no se vea el eje
    pad2->SetGridy();
    pad1->cd();
    pad1->SetLogy();
    // pad2->SetLogy();
  }
  c1->SetTickx();
  c1->SetTicky();
  if (PType[0] == 1 || PType[0] == 2 || PType[0] == 0) {
    // c1->SetLogy();
    c1->SetLogx();
  }

  if (IfEnOrEdep) {
    c1->SetLogy();
    //  c1->SetLogx();
    c1->SetGridx();
    c1->SetGridy();
  }
  if (TypeOfPlot == "CR") {
    // c1->SetLogy(0);
    c1->SetGridx();
    c1->SetGridy();
  }
  if (TypeOfPlot == "CP") {
    c1->SetGridx();
    c1->SetGridy();
  }
  if (NameHisto[0] == "TOF") {
    c1->SetLogy(0);
    c1->SetLogx(0);
    c1->SetGridx();
    c1->SetGridy();
  }
  TLegend* legend = new TLegend(0.6, 0.62, 0.96, 0.86, "");
  if (NumberOfHisto == 1) {
    legend->SetNColumns(2);
  }
  TH1D* h1Axis = (TH1D*)h1[0]->Clone();
  h1Axis->SetName("h1Axis");
  h1Axis->SetTitle(TitleHisto.c_str());
  // h1Axis->SetTitle("");

  if (IfEnOrEdep) {
    // h1Axis->GetXaxis()->SetRangeUser(ForPlotEmin, ForPlotEmax);
    h1Axis->SetAxisRange(ForPlotEminEn, ForPlotEmaxEn, "x");
  } else {
    h1Axis->SetAxisRange(ForPlotEminEdep, ForPlotEmaxEdep, "x");
  }
  h1Axis->Draw("histo E");

  for (auto i = 0; i < NumberOfHisto; i++) {
    h1[i]->Draw("histo E same");
    if (NumberOfHisto == 1) {
      TitleLegend[i] = "Exp";
    }
    legend->AddEntry(h1[i], TitleLegend[i].c_str(), "l");
    if (IfEnOrEdep) {
      // h1Axis->GetXaxis()->SetRangeUser(ForPlotEmin, ForPlotEmax);
      h1[i]->SetAxisRange(ForPlotEminEn, ForPlotEmaxEn, "x");
    } else {
      h1[i]->SetAxisRange(ForPlotEminEdep, ForPlotEmaxEdep, "x");
    }
  }
  if (CompareWithSimul) {
    if (IfEnOrEdep) {
      hSimul->Draw("histo E same");
      legend->AddEntry(hSimul, "All", "l");

      char namelegend[1000];
      for (int i = 0; i < hSimul2Size; i++) {
        if (NameSimulRootfile2[i][FindPositionString(
                NameSimulArray, MeasurementType[0])] != "-1") {
          hSimul2[i]->Draw("histo E same");
          sprintf(namelegend, "Iso %d", i);
          if (i == 0) {
            sprintf(namelegend, "Sm-144");
          }
          if (i == 1) {
            sprintf(namelegend, "Sm-147");
          }
          if (i == 2) {
            sprintf(namelegend, "Sm-148");
          }
          if (i == 3) {
            sprintf(namelegend, "Sm-149");
          }
          if (i == 4) {
            sprintf(namelegend, "Sm-150");
          }
          if (i == 5) {
            sprintf(namelegend, "Sm-152");
          }
          if (i == 6) {
            sprintf(namelegend, "Sm-154");
          }
          legend->AddEntry(hSimul2[i], namelegend, "l");
        }
      }

    } else {
      hSimul->Draw("histo E same");

      int PositionNameSimul =
          FindPositionString(NameSimulArrayEdep, MeasurementType[0]);
      string fname = NameSimulRootfileEdep[PositionNameSimul];
      fname = getAfterSlash(fname);

      legend->AddEntry(hSimul, fname.c_str(), "l");
    }
  }

  if (Integrate && (!IfEnOrEdep)) {
    vector<double> IntegraValuesMin = {0.05, 0.075, 0.1, 0.12, 0.15, 0.2, 0.25,
                                       0.3,  0.35,  0.4, 0.45, 0.5,  0.6, 0.7,
                                       0.8,  0.9,   1,   2,    3,    4};
    double IntegralMax = 10;
    double IntegralSimul, IntegralExp, IntegralSimulError, IntegralExpError;

    for (auto i = 0; i < (int)IntegraValuesMin.size(); i++) {
      IntegralSimul = hSimul->IntegralAndError(
          hSimul->FindBin(IntegraValuesMin[i]), hSimul->FindBin(IntegralMax),
          IntegralSimulError);
      IntegralExp = h1[0]->IntegralAndError(h1[0]->FindBin(IntegraValuesMin[i]),
                                            h1[0]->FindBin(IntegralMax),
                                            IntegralExpError);
      cout << " Emin=" << IntegraValuesMin[i] << " Exp= " << IntegralExp
           << " Sil= " << IntegralSimul
           << " Ratio with simul= " << IntegralExp / IntegralSimul << " +- "
           << IntegralExpError / IntegralSimul << endl;
    }

  } else if (Integrate) {
    double IntegralHisto[NumberOfHisto];
    double IntegralErrors[NumberOfHisto];
    IntegralHisto[0] = h1[0]->IntegralAndError(h1[0]->FindBin(MinYForCompare),
                                               h1[0]->FindBin(MaxYForCompare),
                                               IntegralErrors[0]);
    for (auto i = 1; i < NumberOfHisto; i++) {
      IntegralHisto[i] = h1[i]->IntegralAndError(h1[i]->FindBin(MinYForCompare),
                                                 h1[i]->FindBin(MaxYForCompare),
                                                 IntegralErrors[i]);
      string AddToLegend =
          "I" + to_string(i) + "/0=" +
          doubleToDecimalString(IntegralHisto[i] / IntegralHisto[0], 2) + "+-" +
          doubleToDecimalString(IntegralErrors[i] / IntegralHisto[0], 2);
      // legend->AddEntry((TObject*)0, AddToLegend.c_str(), "");
    }
  }
  legend->SetTextSize(0.06);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->Draw();

  if (CalculateRatio) {
    h1Axis->GetXaxis()->SetTitleSize(0.090);
    h1Axis->GetXaxis()->SetLabelSize(0.090);
    h1Axis->GetXaxis()->SetLabelOffset(0.005);

    h1Axis->GetYaxis()->SetTitleSize(0.090);
    h1Axis->GetYaxis()->SetLabelSize(0.090);
    h1Axis->GetYaxis()->SetTitleOffset(0.85);

    pad2->cd();
    TH1D* h1Ratio[NumberOfHisto];

    for (auto i = 0; i < NumberOfHisto; i++) {
      h1Ratio[i] = (TH1D*)h1[i]->Clone();
      h1Ratio[i] = CalculateRatioHisto(h1[i], hSimul);
      h1Ratio[i]->SetTitle("");
      if (IfEnOrEdep) {
        h1Ratio[i]->SetAxisRange(ForPlotEminEn, ForPlotEmaxEn, "x");
        h1Ratio[i]->SetAxisRange(MinYForCompare, MaxYForCompare, "y");
      } else {
        h1Ratio[i]->SetAxisRange(ForPlotEminEdep, ForPlotEmaxEdep, "x");
        h1Ratio[i]->SetAxisRange(MinYForCompare, MaxYForCompare, "y");
      }
    }

    h1Ratio[0]->SetMarkerStyle(20);
    h1Ratio[0]->SetMarkerColor(2);
    h1Ratio[0]->SetMarkerSize(0.7);
    h1Ratio[0]->GetYaxis()->SetTitle("Ratio");

    h1Ratio[0]->GetYaxis()->CenterTitle();

    h1Ratio[0]->GetYaxis()->SetTitleOffset(0.35);
    h1Ratio[0]->GetYaxis()->SetTitleSize(0.14);
    h1Ratio[0]->GetYaxis()->SetLabelSize(0.2);
    h1Ratio[0]->GetXaxis()->SetTitleSize(0.18);
    h1Ratio[0]->GetYaxis()->SetTitleSize(0.18);

    h1Ratio[0]->GetXaxis()->SetLabelSize(0.2);
    h1Ratio[0]->GetYaxis()->SetNdivisions(5, 5, 0);
    h1Ratio[0]->GetXaxis()->SetNdivisions(9, 5, 0);
    h1Ratio[0]->GetXaxis()->SetLabelOffset(0.006);

    h1Ratio[0]->Draw("histo E");
    for (auto i = 1; i < NumberOfHisto; i++) {
      h1Ratio[i]->Draw("histo E same");
    }

    // h1Ratio[0]->GetYaxis()->SetRangeUser(-2.01, 2.01);
    h1Ratio[0]->GetYaxis()->SetRangeUser(0.97, 1.03);
  }
  if (IfSaveName == "-1") {
    SaveRootEpsPngTxtFunction(c1, SaveName.c_str());
  } else {
    SaveRootEpsPngTxtFunction(c1, IfSaveName.c_str());
  }
}

// void plot2DVariousCompareWithOneRun() {
//   int rebin = 1;

//   string NameSave;
//   string PreNameSave = "ResultsPlot/ChangeGainMGAS/ChangeGainMGAS_1_";
//   // for (int i = 118849; i <= 119000; i++) {
//   for (int i = 118969; i <= 119028; i++) {
//     NameSave = PreNameSave + to_string(i);
//     vector<string> RunString;
//     RunString.push_back(to_string(i));

//     RunString.push_back(to_string(118849));

//     plot2D({"Edep"}, RunString, {1}, {0.01}, {100}, {1}, "CPulse", rebin,
//     false,
//            true, false, false, NameSave);
//   }
// }

void plot2DVariousCompareWithOneRun() {
  int rebin = 8;
  int detN = 2;
  // int RunCompare = 115569;
  int RunCompare = 118885;

  string NameSave;
  // string PreNameSave = "ResultsPlot/CheckEachRunDeltaTOF/CheckRun_";
  string PreNameSave = "ResultsPlot/CheckEachRunSILI_EDEP/CheckRun";
  vector<int> Detector;
  Detector.push_back(detN);

  // for (int i = 118884; i <= 119600; i++) {
  // for (int i = 115561; i <= 119846; i++) {
  // for (int i = 115815; i <= 119846; i++) {
  // for (int i = 118817; i <= 119846; i++) {
  //  for (int i = 115670; i <= 116078; i++) {
  // for (int i = 115568; i <= 116078; i++) {
  for (int i = 118828; i <= 119846; i++) {
    vector<string> RunString;
    string RunType = TakeRunType("../RunLists/RunList2024_2023_v01.txt", i);
    RunString.push_back(to_string(RunCompare));
    RunString.push_back(to_string(i));
    NameSave =
        PreNameSave + to_string(detN) + "_" + to_string(i) + "_" + RunString[0];

    if ((RunType != "AllRuns") && (RunType != "AllBeamRuns") &&
        (RunType != "AllBeamRunsNoFilters") && (RunType != "23AllRuns") &&
        (i != 115780) && (i != 118864)) {
      // plot2D({"En"}, RunString, {0}, {0.12}, {10}, {1}, "CP", rebin, false,
      //      false, false, true, NameSave);

      // plot2D({"DeltaTOF"}, RunString, {1}, {0.12}, {10}, {0}, "CPulse",
      // rebin,             false, false, false, true, NameSave);
      plot2D({"Edep"}, RunString, Detector, {0.02}, {1e5}, {2}, "CP", rebin,
             false, false, false, false, NameSave);
    }
  }
}
void plot2DVariousCompareWithRunType(int detN) {
  int rebin = 10;
  string NameSaveEDEP, NameSaveEN;
  // string PreNameSave = "ResultsPlot/CheckEachRunDeltaTOF/CheckRun_";
  //  string PreNameSave = "ResultsPlot/CheckEachRunSILI_EDEP/CheckRun";
  string PreNameSave = "ResultsPlot/CheckEachRun/CheckRun";

  vector<int> Detector;
  Detector.push_back(detN);

  // for (int i = 118884; i <= 119600; i++) {
  // for (int i = 115561; i <= 119846; i++) {
  // for (int i = 115815; i <= 119846; i++) {
  for (int i = 118817; i <= 119846; i++) {
    // for (int i = 115561; i <= 116078; i++) {
    vector<string> RunString;
    // RunString.push_back(to_string(i));
    string RunType = TakeRunType("../RunLists/RunList2024_2023_v01.txt", i);
    RunString.push_back(to_string(i));
    RunString.push_back(RunType);

    NameSaveEDEP = PreNameSave + "Det" + to_string(detN) + "_" + to_string(i) +
                   "_" + RunType + "Edep";

    NameSaveEN = PreNameSave + "Det" + to_string(detN) + "_" + to_string(i) +
                 "_" + RunType + "En";
    cout << endl << endl << "RunType " << RunType << endl << endl;
    if ((RunType != "AllRuns") && (RunType != "23BeforeExp") &&
        (RunType != "AllBeamRuns") && (RunType != "AllBeamRunsNoFilters") &&
        (RunType != "23AllRuns") && (i != 115779) && (i != 115780) &&
        (i != 115781) && (i != 115782) && (i != 115783) && (i != 115784) &&
        (i != 115785)) {
      plot2D({"Edep"}, RunString, Detector, {0.01}, {1e4}, {0}, "CPulse", rebin,
             false, false, false, true, NameSaveEDEP);
      plot2D({"En"}, RunString, Detector, {0.1}, {10}, {1}, "CP", rebin * 10,
             false, false, false, true, NameSaveEN);
    }
  }
}
void plot2DCheckCalibrations(int detN) {
  vector<int> Detector;
  Detector.push_back(detN);
  int rebin = 1;
  string outputFolder = "ResultsPlot/CheckCalibrations/CheckCalibrations_";
  BackgroundMeasPredefined[0] = "Background_1";
  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 2.5;
  NormalizeMinEdep = 0.5;
  NormalizeMaxEdep = 2.5;
  plot2D({"Edep"}, {"Y"}, Detector, {0.01}, {1e6}, {3}, "CR", rebin, true, true,
         true, false, (outputFolder + to_string(detN) + "_Y"));

  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 1;
  NormalizeMinEdep = 0.3;
  NormalizeMaxEdep = 0.7;
  plot2D({"Edep"}, {"Cs"}, Detector, {0.01}, {1e6}, {3}, "CR", rebin, true,
         true, true, false, (outputFolder + to_string(detN) + "_Cs"));

  ForPlotEminEdep = 0;
  ForPlotEmaxEdep = 0.5;
  NormalizeMinEdep = 0.1;
  NormalizeMaxEdep = 0.3;
  plot2D({"Edep"}, {"Ba"}, Detector, {0.01}, {1e6}, {3}, "CR", rebin, true,
         true, true, false, (outputFolder + to_string(detN) + "_Ba"));

  ForPlotEminEdep = 3;
  ForPlotEmaxEdep = 8;
  NormalizeMinEdep = 5;
  NormalizeMaxEdep = 7;
  plot2D({"Edep"}, {"CmC"}, Detector, {0.01}, {1e6}, {3}, "CR", rebin * 4, true,
         true, true, false, (outputFolder + to_string(detN) + "_CmC"));

  ForPlotEminEdep = 2;
  ForPlotEmaxEdep = 6;
  NormalizeMinEdep = 3;
  NormalizeMaxEdep = 5;
  plot2D({"Edep"}, {"AmBe"}, Detector, {0.01}, {1e6}, {3}, "CR", rebin * 4,
         true, true, true, false, (outputFolder + to_string(detN) + "_AmBe"));
}

void plot2DChangeGainWithSources() {
  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 2.5;
  NormalizeMinEdep = 0.5;
  NormalizeMaxEdep = 2.5;
  plot2D({"Edep"}, {"Y", "Y_1", "Y_2", "Y_3", "Y_Cu", "Y_Cu_1"}, {1}, {0.01},
         {1e6}, {3}, "CR", 10, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det1_Y");

  plot2D(
      {"Edep"},
      {"Y", "Y_1", "Y_2", "119165", "119247", "119293", "119327", "119390"},
      {1}, {0.01}, {1e6}, {3}, "CR", 10, false, true, false, false,
      "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det1_Y_EXTRA");

  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 1;
  NormalizeMinEdep = 0.3;
  NormalizeMaxEdep = 0.7;
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {1},
         {0.01}, {1e6}, {3}, "CR", 4, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det1_Cs");
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {1},
         {0.01}, {1e6}, {3}, "CR", 4, false, false, false, false,
         "ResultsPlot/ChangeGainWithSources/CR_Det1_Cs");
  ForPlotEminEdep = 2;
  ForPlotEmaxEdep = 6;
  NormalizeMinEdep = 3;
  NormalizeMaxEdep = 5;
  plot2D({"Edep"}, {"AmBe_1", "AmBe_2", "AmBe_3", "AmBe_Cu_1"}, {1}, {0.01},
         {1e6}, {3}, "CR", 50, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det1_AmBe");

  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 2.5;
  NormalizeMinEdep = 0.5;
  NormalizeMaxEdep = 2.5;
  plot2D({"Edep"}, {"Y", "Y_1", "Y_2", "Y_3", "Y_Cu", "Y_Cu_1"}, {2}, {0.01},
         {1e6}, {3}, "CR", 10, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det2_Y");
  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 1;
  NormalizeMinEdep = 0.3;
  NormalizeMaxEdep = 0.7;
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {2},
         {0.01}, {1e6}, {3}, "CR", 4, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det2_Cs");
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {2},
         {0.01}, {1e6}, {3}, "CR", 4, false, false, false, false,
         "ResultsPlot/ChangeGainWithSources/CR_Det2_Cs");
  ForPlotEminEdep = 2;
  ForPlotEmaxEdep = 6;
  NormalizeMinEdep = 3;
  NormalizeMaxEdep = 5;
  plot2D({"Edep"}, {"AmBe_1", "AmBe_2", "AmBe_3", "AmBe_Cu_1"}, {2}, {0.01},
         {1e6}, {3}, "CR", 50, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det2_AmBe");

  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 2.5;
  NormalizeMinEdep = 0.5;
  NormalizeMaxEdep = 2.5;
  plot2D({"Edep"}, {"Y", "Y_1", "Y_2", "Y_3", "Y_Cu", "Y_Cu_1"}, {3}, {0.01},
         {1e6}, {3}, "CR", 10, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det3_Y");
  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 1;
  NormalizeMinEdep = 0.3;
  NormalizeMaxEdep = 0.7;
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {3},
         {0.01}, {1e6}, {3}, "CR", 4, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det3_Cs");
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {3},
         {0.01}, {1e6}, {3}, "CR", 4, false, false, false, false,
         "ResultsPlot/ChangeGainWithSources/CR_Det3_Cs");
  ForPlotEminEdep = 2;
  ForPlotEmaxEdep = 6;
  NormalizeMinEdep = 3;
  NormalizeMaxEdep = 5;
  plot2D({"Edep"}, {"AmBe_1", "AmBe_2", "AmBe_3", "AmBe_Cu_1"}, {3}, {0.01},
         {1e6}, {3}, "CR", 50, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det3_AmBe");

  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 2.5;
  NormalizeMinEdep = 0.5;
  NormalizeMaxEdep = 2.5;
  plot2D({"Edep"}, {"Y", "Y_1", "Y_2", "Y_3", "Y_Cu", "Y_Cu_1"}, {4}, {0.01},
         {1e6}, {3}, "CR", 10, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det4_Y");
  ForPlotEminEdep = 0.1;
  ForPlotEmaxEdep = 1;
  NormalizeMinEdep = 0.3;
  NormalizeMaxEdep = 0.7;
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {4},
         {0.01}, {1e6}, {3}, "CR", 4, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det4_Cs");
  plot2D({"Edep"}, {"Cs", "Cs_1", "Cs_2", "Cs_3", "Cs_Cu", "Cs_Cu_1"}, {4},
         {0.01}, {1e6}, {3}, "CR", 4, false, false, false, false,
         "ResultsPlot/ChangeGainWithSources/CR_Det4_Cs");
  ForPlotEminEdep = 2;
  ForPlotEmaxEdep = 6;
  NormalizeMinEdep = 3;
  NormalizeMaxEdep = 5;
  plot2D({"Edep"}, {"AmBe_1", "AmBe_2", "AmBe_3", "AmBe_Cu_1"}, {4}, {0.01},
         {1e6}, {3}, "CR", 50, false, true, false, false,
         "ResultsPlot/ChangeGainWithSources/ChangeGainWithSources_Det4_AmBe");
}
