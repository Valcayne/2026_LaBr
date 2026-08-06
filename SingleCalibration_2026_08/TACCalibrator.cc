
#include "TACCalibrator.hh"

#include "Functions01.hh"

Double_t fitFunction(Double_t* x, Double_t* par) {
  // Gaussian
  return (par[0] * exp(-0.5 * (pow((x[0] - par[1]) / par[2], 2))));
}

Double_t fitFunction_v2(Double_t* x, Double_t* par) {
  // Gaussian AMBE
  // cout<<"Modify Version"<<endl;
  // return
  // (par[0]*exp(-0.5*(pow((x[0]-par[1])/par[2],2)))+par[3]*exp(-0.5*(pow((x[0]-par[1]*((4438.-511.)/4438.))/par[2],2))));
  return (
      par[0] * exp(-0.5 * (pow((x[0] - par[1]) / par[2], 2))) +
      par[3] *
          exp(-0.5 *
              (pow((x[0] - par[1] * ((4438. - 511.) / 4438.)) / par[2], 2))) +
      par[4] *
          exp(-0.5 *
              (pow((x[0] - par[1] * ((4438. - 1022.) / 4438.)) / par[2], 2))));
}

Double_t fitFunction_v3(Double_t* x, Double_t* par) {
  // Gaussian CMC
  // return
  // (par[0]*exp(-0.5*(pow((x[0]-par[1])/par[2],2)))+par[3]*exp(-0.5*(pow((x[0]-par[1]*((4438.-511.)/4438.))/par[2],2))));
  return (
      par[0] * exp(-0.5 * (pow((x[0] - par[1]) / par[2], 2))) +
      par[3] *
          exp(-0.5 *
              (pow((x[0] - par[1] * ((6130. - 511.) / 6130.)) / par[2], 2))) +
      par[4] *
          exp(-0.5 *
              (pow((x[0] - par[1] * ((6130. - 1022.) / 6130.)) / par[2], 2))));
}

Double_t fitFunction2(Double_t* x, Double_t* par) {
  // Gaussian + straight line
  return (par[0] + par[1] * x[0]) +
         (par[2] * exp(-0.5 * (pow((x[0] - par[3]) / par[4], 2))));
}

Double_t fitFunction2_v2(Double_t* x, Double_t* par) {
  // 2 Gaussians + straight line - Am/Be source
  // return
  // (par[0]+par[1]*x[0])+(par[2]*exp(-0.5*(pow((x[0]-par[3])/par[4],2))))+(par[5]*exp(-0.5*(pow((x[0]-par[3]*((4438.-511.)/4438.))/par[4],2))));
  return (par[0] + par[1] * x[0]) +
         (par[2] * exp(-0.5 * (pow((x[0] - par[3]) / par[4], 2)))) +
         (par[5] *
          exp(-0.5 *
              (pow((x[0] - par[3] * ((4438. - 511.) / 4438.)) / par[4], 2)))) +
         (par[6] *
          exp(-0.5 *
              (pow((x[0] - par[3] * ((4438. - 1022.) / 4438.)) / par[4], 2))));
}

Double_t fitFunction2_v3(Double_t* x, Double_t* par) {
  // 2 Gaussians + straight line - Cm/C source
  // return
  // (par[0]+par[1]*x[0])+(par[2]*exp(-0.5*(pow((x[0]-par[3])/par[4],2))))+(par[5]*exp(-0.5*(pow((x[0]-par[3]*((4438.-511.)/4438.))/par[4],2))));
  return (par[0] + par[1] * x[0]) +
         (par[2] * exp(-0.5 * (pow((x[0] - par[3]) / par[4], 2)))) +
         (par[5] *
          exp(-0.5 *
              (pow((x[0] - par[3] * ((6130. - 511.) / 6130.)) / par[4], 2)))) +
         (par[6] *
          exp(-0.5 *
              (pow((x[0] - par[3] * ((6130. - 1022.) / 6130.)) / par[4], 2))));
}

//----------------------------------------------------------------
//----------------------------------------------------------------

TACCalibrator::TACCalibrator() {
  for (int i = 0; i < NDETECTORS + 1; i++) {
    h[i] = 0;
    d[i] = 0;
    b[i] = 0;
    NFitFun[i] = 0;
    for (int j = 0; j < MAXNLOCALMAX; j++) {
      FitFun[i][j] = 0;
      FitFun2[i][j] = 0;
    }
  }
  FWHM = FWHM_EST;
}

TACCalibrator::~TACCalibrator() {
  for (int i = 0; i < NDETECTORS + 1; i++) {
    if (h[i] != 0) {
      delete h[i];
    }
    if (d[i] != 0) {
      delete d[i];
    }
    if (b[i] != 0) {
      delete b[i];
    }
    for (int j = 0; j < MAXNLOCALMAX; j++) {
      if (FitFun[i][j]) {
        delete FitFun[i][j];
      }
      if (FitFun2[i][j]) {
        delete FitFun2[i][j];
      }
    }
  }
}

void TACCalibrator::FillRatioVal(string CutFilename) {
  ifstream in(CutFilename.c_str());
  int detn0;
  for (int i = 0; i < 40; i++) {
    in >> detn0;
    in >> RatioVal[detn0] >> TimeRatioVal[detn0];
    //     cout<<RatioVal[detn0]<<" Tiem "<<TimeRatioVal[detn0]<<endl;;
  }
  if (!in.good()) {
    cout << " *** Error reading CutList  ***" << endl;
    exit(1);
  }
}

int TACCalibrator::FillAndCreateHistograms(string filename) {
  cout << " Start Filling Histo " << endl;
  for (int i = 0; i < NDETECTORS + 1; i++) {
    if (h[i] != 0) {
      delete h[i];
    }
  }

  TFile* f = new TFile(filename.c_str());
  if (f->IsZombie()) {
    cout << " **** Error opening file: " << filename << " ****" << endl;
    return -1;
  }

  Float_t Area;
  Int_t ParType;

  TTree* theTree = (TTree*)(f->Get(TREENAME));
  Signal* theDetSignal = new Signal;
  theTree->SetBranchAddress("aslow", &(theDetSignal->aslow));
  theTree->SetBranchAddress("afast", &(theDetSignal->afast));
  theTree->SetBranchAddress("detn", &(theDetSignal->detn));
  theTree->SetBranchAddress("area", &(theDetSignal->area));
  theTree->SetBranchAddress("risetime", &(theDetSignal->Tau));
  theTree->SetBranchAddress("fwtm", &(theDetSignal->fwtm));

  char name[100];
  char title[100];
  for (int i = 1; i < NDETECTORS + 1; i++) {
    sprintf(name, "h%d", i);
    sprintf(title, "Crystal %d", i);
    h[i] = new TH1F(name, title, NHISTOBINS, HISTOLOWLIM, HISTOHILIM);
    h[i]->SetLineColor(2);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
  }

  Long64_t entry = 0;
  int check = 0;
  int warningflag = 0;
  do {
    check = theTree->GetEntry(entry /*,1*/);
    //~ Area = GetArea(theBAF2->afast,theBAF2->aslow,theBAF2->area,Tau);
    ParType = GetParType(theDetSignal, TimeRatioVal, RatioVal);
    if (check > 0) {
      if (theDetSignal->detn < 1 || theDetSignal->detn > NDETECTORS) {
        if (!warningflag) {
          cout << " **** WARNING: detn out of range: " << theDetSignal->detn
               << " ****" << endl;
          cout << " Skipping entry " << entry << endl;
          warningflag = 1;
        }
        entry++;
        continue;
      }
      if (ParType == 1) {
        {
          if (TREENAME == "BAF2") {
            h[theDetSignal->detn]->Fill(theDetSignal->aslow);
          } else {
            h[theDetSignal->detn]->Fill(theDetSignal->area);
          }
        }
      }
    }
    entry++;
  } while (check > 0);

  if (check < 0) {
    cout << " *** Error reading tree ***" << endl;
    return -1;
  } else {
    cout << " " << entry << " entries read in tree" << endl;
  }
  cout << " finish Filling Histo " << endl << endl << endl;

  delete theDetSignal;

  return 0;
}

int TACCalibrator::FillHistograms(string filename) {
  cout << " Start Filling Histo " << endl;

  TFile* f = new TFile(filename.c_str());
  if (f->IsZombie()) {
    cout << " **** Error opening file: " << filename << " ****" << endl;
    return -1;
  }

  Float_t slowamp, fastamp, Area;
  Int_t ParType;

  TTree* theTree = (TTree*)(f->Get(TREENAME));

  Signal* theDetSignal = new Signal;
  theTree->SetBranchAddress("aslow", &(theDetSignal->aslow));
  theTree->SetBranchAddress("afast", &(theDetSignal->afast));
  theTree->SetBranchAddress("detn", &(theDetSignal->detn));
  theTree->SetBranchAddress("area", &(theDetSignal->area));
  theTree->SetBranchAddress("risetime", &(theDetSignal->Tau));
  theTree->SetBranchAddress("fwtm", &(theDetSignal->fwtm));

  Long64_t entry = 0;
  int check = 0;
  do {
    check = theTree->GetEntry(entry /*,1*/);
    ParType = GetParType(theDetSignal, TimeRatioVal, RatioVal);
    if (check > 0) {
      if (ParType == 1) {
        if (TREENAME == "BAF2") {
          h[theDetSignal->detn]->Fill(theDetSignal->aslow);
        } else {
          h[theDetSignal->detn]->Fill(theDetSignal->area);
        }
      }
    }
    entry++;
  } while (check > 0);

  if (check < 0) {
    cout << " *** Error reading tree ***" << endl;
    return -1;
  } else {
    cout << " " << entry << " entries read in tree" << endl;
  }
  cout << " finish Filling Histo " << endl << endl << endl;

  delete theDetSignal;

  return 0;
}

int TACCalibrator::TakeBackground(int CrNumber) {
  TSpectrum* s = new TSpectrum();
  b[CrNumber] = (TH1F*)s->Background(h[CrNumber], 20, "Compton");

  d[CrNumber] = new TH1F(*h[CrNumber]);
  d[CrNumber]->Add(b[CrNumber], -1.);

  b[CrNumber]->SetLineColor(1);
  b[CrNumber]->SetLineWidth(1);
  d[CrNumber]->SetLineColor(4);
  d[CrNumber]->SetLineWidth(1);

  //-------------------------
  int nb = d[CrNumber]->GetNbinsX();
  for (int i = 1; i <= nb; i++) {
    if (d[CrNumber]->GetBinContent(i) < 0) {
      d[CrNumber]->SetBinContent(i, 0);
    }
  }
  //-------------------------

  return 0;
}

int TACCalibrator::TakeAllBackgrounds() {
  for (int i = 1; i < NDETECTORS + 1; i++) {
    TakeBackground(i);
  }
  return 0;
}

int TACCalibrator::FindAllPeaks() {
  for (int i = 1; i < NDETECTORS + 1; i++) {
    FindPeaks(i);
  }
  return 0;
}

int TACCalibrator::FindPeaks(int CrNumber) {
  cout << " FindPeak cr = " << CrNumber << endl;
  // We take the maximum value of the histo:
  double maxval = d[CrNumber]->GetMaximum();
  //----------------------------------------------
  // Now, we take the local maximums:
  int nlocalmax = 0;
  int localmax[MAXNLOCALMAX];
  // FWHM, in channels:
  int FWHM_ch = (int)(FWHM / d[CrNumber]->GetBinWidth(1));
  if (FWHM_ch < 5) {
    FWHM_ch = 5;
  }
  int halfFWHM_ch = FWHM_ch / 2;
  for (int i = (halfFWHM_ch + 1);
       i <= d[CrNumber]->GetNbinsX() - (halfFWHM_ch + 1); i++) {
    if (d[CrNumber]->GetBinContent(i) > maxval * TRIGGERLEVEL && maxval > 0) {
      bool islocalmax = true;
      for (int j = i - halfFWHM_ch; j <= i + halfFWHM_ch; j++) {
        if (d[CrNumber]->GetBinContent(j) > d[CrNumber]->GetBinContent(i)) {
          islocalmax = false;
          break;
        }
      }
      if (islocalmax && nlocalmax < MAXNLOCALMAX) {
        localmax[nlocalmax] = i;
        nlocalmax++;
        i += 2 * halfFWHM_ch - 1;
      }
    }
  }
  //----------------------------------------------

  //----------------------------------------------
  // Now, we make a gaussian fit:
  for (int i = 0; i < MAXNLOCALMAX; i++) {
    if (FitFun[CrNumber][i] != 0) {
      delete FitFun[CrNumber][i];
      FitFun[CrNumber][i] = 0;
    }
  }
  for (int i = 0; i < MAXNLOCALMAX; i++) {
    if (FitFun2[CrNumber][i] != 0) {
      delete FitFun2[CrNumber][i];
      FitFun2[CrNumber][i] = 0;
    }
  }
  NFitFun[CrNumber] = 0;

  if (nlocalmax > 0) {
    NFitFun[CrNumber] = nlocalmax;
    for (int i = 0; i < nlocalmax; i++) {
      double thelocalmax = d[CrNumber]->GetBinCenter(localmax[i]);
      char name[100];
      sprintf(name, "FitFun_%d_%d", CrNumber, i);
#ifdef AMBESOURCE
      FitFun[CrNumber][i] =
          new TF1(name, fitFunction_v2,
                  TMath::Max(thelocalmax - FWHM, (double)HISTOLOWLIM),
                  TMath::Min(thelocalmax + FWHM, (double)HISTOHILIM), 5);
#endif
#ifdef CMCSOURCE
      FitFun[CrNumber][i] =
          new TF1(name, fitFunction_v3,
                  TMath::Max(thelocalmax - FWHM, (double)HISTOLOWLIM),
                  TMath::Min(thelocalmax + FWHM, (double)HISTOHILIM), 5);
#endif
#ifdef CSYSOURCE

      FitFun[CrNumber][i] =
          new TF1(name, fitFunction,
                  TMath::Max(thelocalmax - FWHM, (double)HISTOLOWLIM),
                  TMath::Min(thelocalmax + FWHM, (double)HISTOHILIM), 3);
#endif
      FitFun[CrNumber][i]->SetLineColor(6);
      FitFun[CrNumber][i]->SetLineWidth(2);
      // Set aproximate values:
      double constant, center, sigma, area;
      center = thelocalmax;
      sigma = FWHM / 2.35;
      area = FWHM * d[CrNumber]->GetBinContent(localmax[i]);
      constant = area / (sigma * sqrt(2 * 3.14));
#ifdef AMBESOURCE
      int const NTIMES = 2;
      double chi[NTIMES];
      double const1[NTIMES] = {constant / 3, constant};
      double const2[NTIMES] = {constant, constant / 2};
      double const3[NTIMES] = {constant / 3, constant / 10};
      double cent[NTIMES] = {center * ((4438 + 511.) / 4438.), center};
      double sig[NTIMES] = {sigma / 3, sigma / 2};
      double bestchi = 1e10;
      int i_bestchi = 0;
      for (int kkk = 0; kkk < NTIMES; kkk++) {
        FitFun[CrNumber][i]->SetParameters(const1[kkk], cent[kkk], sig[kkk],
                                           const2[kkk], const3[kkk]);
        d[CrNumber]->Fit(FitFun[CrNumber][i], "NRQ");
        chi[kkk] = FitFun[CrNumber][i]->GetChisquare();
        if (chi[kkk] < bestchi) {
          chi[kkk] = bestchi;
          i_bestchi = kkk;
        }
      }
      FitFun[CrNumber][i]->SetParameters(const1[i_bestchi], cent[i_bestchi],
                                         sig[i_bestchi], const2[i_bestchi],
                                         const3[i_bestchi]);
      d[CrNumber]->Fit(FitFun[CrNumber][i], "NRQ");
#endif
#ifdef CMCSOURCE
      int const NTIMES = 2;
      double chi[NTIMES];
      double const1[NTIMES] = {constant / 3, constant};
      double const2[NTIMES] = {constant, constant / 2};
      double const3[NTIMES] = {constant / 3, constant / 10};
      double cent[NTIMES] = {center * ((4438 + 511.) / 4438.), center};
      double sig[NTIMES] = {sigma / 3, sigma / 2};
      double bestchi = 1e10;
      int i_bestchi = 0;
      for (int kkk = 0; kkk < NTIMES; kkk++) {
        FitFun[CrNumber][i]->SetParameters(const1[kkk], cent[kkk], sig[kkk],
                                           const2[kkk], const3[kkk]);
        d[CrNumber]->Fit(FitFun[CrNumber][i], "NRQ");
        chi[kkk] = FitFun[CrNumber][i]->GetChisquare();
        if (chi[kkk] < bestchi) {
          chi[kkk] = bestchi;
          i_bestchi = kkk;
        }
      }
      FitFun[CrNumber][i]->SetParameters(const1[i_bestchi], cent[i_bestchi],
                                         sig[i_bestchi], const2[i_bestchi],
                                         const3[i_bestchi]);
      d[CrNumber]->Fit(FitFun[CrNumber][i], "NRQ");
#endif
#ifdef CSYSOURCE

      FitFun[CrNumber][i]->SetParameters(constant, center, sigma);
      // Fit:
      d[CrNumber]->Fit(FitFun[CrNumber][i], "NRQ");
#endif
      //------------------------------------------------
      ////--------------------------------------------------------------------
      //--------------------------------------------------------------------
      -- -- -- -- -- -- -- -- -- --
                                 //--------------------------------------------------------------------

                                 //--------------------------------------------------------------------
                                 // Second fit:
                                 constant =
          FitFun[CrNumber][i]->GetParameter(0);
      center = FitFun[CrNumber][i]->GetParameter(1);
      sigma = FitFun[CrNumber][i]->GetParameter(2);
      if (sigma < 0) {
        sigma = -sigma;
      }
      double r_min, r_max, r_m, r_b;
      r_min = center - 4 * sigma;
      r_max = center + 4 * sigma;
      sprintf(name, "FitFun2_%d_%d", CrNumber, i);
#ifdef AMBESOURCE
      r_min = center * ((4438. - 511.) / 4438.) - 4 * sigma;
      FitFun2[CrNumber][i] = new TF1(name, fitFunction2_v2, r_min, r_max, 7);
#endif
#ifdef CMCSOURCE
      r_min = center * ((6130. - 511.) / 6130.) - 4 * sigma;
      FitFun2[CrNumber][i] = new TF1(name, fitFunction2_v3, r_min, r_max, 7);
#endif
#ifdef CSYSOURCE

      FitFun2[CrNumber][i] = new TF1(name, fitFunction2, r_min, r_max, 5);
#endif
      FitFun2[CrNumber][i]->SetLineColor(7);
      FitFun2[CrNumber][i]->SetLineWidth(2);
      double y_rmin = 0, y_rmax = 0;
      for (int j = 1; j <= h[CrNumber]->GetNbinsX(); j++) {
        if (h[CrNumber]->GetBinCenter(j) > r_min) {
          y_rmin = (h[CrNumber]->GetBinContent(j - 1) +
                    h[CrNumber]->GetBinContent(j) +
                    h[CrNumber]->GetBinContent(j + 1)) /
                   3.;
          break;
        }
      }
      for (int j = 1; j <= h[CrNumber]->GetNbinsX(); j++) {
        if (h[CrNumber]->GetBinCenter(j) > r_max) {
          y_rmax = (h[CrNumber]->GetBinContent(j - 1) +
                    h[CrNumber]->GetBinContent(j) +
                    h[CrNumber]->GetBinContent(j + 1)) /
                   3.;
          break;
        }
      }
      r_m = (y_rmax - y_rmin) / (r_max - r_min);
      r_b = y_rmax - r_m * r_max;
#ifdef AMBESOURCE
      FitFun2[CrNumber][i]->SetParameters(r_b, r_m, constant, center, sigma,
                                          constant,
                                          FitFun[CrNumber][i]->GetParameter(3),
                                          FitFun[CrNumber][i]->GetParameter(4));
#endif
#ifdef CMCSOURCE
      FitFun2[CrNumber][i]->SetParameters(r_b, r_m, constant, center, sigma,
                                          constant,
                                          FitFun[CrNumber][i]->GetParameter(3),
                                          FitFun[CrNumber][i]->GetParameter(4));
#endif
#ifdef CSYSOURCE
      FitFun2[CrNumber][i]->SetParameters(r_b, r_m, constant, center, sigma);
#endif
      h[CrNumber]->Fit(FitFun2[CrNumber][i], "NRQ");
      //--------------------------------------------------------------------
    }
  }
  //----------------------------------------------

  return 0;
}

int TACCalibrator::SaveValues(string filename) {
  ofstream out(filename.c_str());
  if (!out.good()) {
    cout << " **** Error opening output file: " << filename << " ****" << endl;
    return -1;
  }
  for (int i = 0; i < NDETECTORS; i++) {
    out << Form("%s_%d %d", TREENAME, i + 1, NFitFun[i + 1]) << "  ";
    for (int j = 0; j < NFitFun[i + 1]; j++) {
      out << FitFun[i + 1][j]->GetParameter(0) << "  ";
      out << FitFun[i + 1][j]->GetParameter(1) << "  ";
      out << FitFun[i + 1][j]->GetParameter(2) << "  ";
    }
    out << endl;
  }

  out << endl << " NEW (CYAN FIT) " << endl;
  for (int i = 0; i < NDETECTORS; i++) {
    out << Form("%s_%d %d", TREENAME, i + 1, NFitFun[i + 1]) << "  ";
    for (int j = 0; j < NFitFun[i + 1]; j++) {
      out << FitFun2[i + 1][j]->GetParameter(2) << "  ";
      out << FitFun2[i + 1][j]->GetParameter(3) << "  ";
      out << FitFun2[i + 1][j]->GetParameter(4) << "  ";
      //--------------------------
#ifdef AMBESOURCE
      if (FitFun2[i + 1][j]->GetParameter(2) * 5 <
              FitFun2[i + 1][j]->GetParameter(5) &&
          j == NFitFun[i + 1] - 1) {
        cout << " **** WARINIG: in crystal " << i + 1
             << " area(4438-511)=" << FitFun2[i + 1][j]->GetParameter(5)
             << " and area(4438)=" << FitFun2[i + 1][j]->GetParameter(2)
             << " ****" << endl;
      }
#endif

#ifdef CMCSOURCE
      if (FitFun2[i + 1][j]->GetParameter(2) * 5 <
              FitFun2[i + 1][j]->GetParameter(5) &&
          j == NFitFun[i + 1] - 1) {
        cout << " **** WARINIG: in crystal " << i + 1
             << " area(4438-511)=" << FitFun2[i + 1][j]->GetParameter(5)
             << " and area(4438)=" << FitFun2[i + 1][j]->GetParameter(2)
             << " ****" << endl;
      }
#endif
      //--------------------------
    }
    out << endl;
  }
  out.close();
  return 0;
}
