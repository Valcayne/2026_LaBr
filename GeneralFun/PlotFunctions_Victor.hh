#ifndef PLOTFUNCTIONS_VICTOR_HH
#define PLOTFUNCTIONS_VICTOR_HH 1

#include "../GeneralFun/GeneralFunctions.hh"

TH1D* TH1DFromMC_Resol_v01(TH1D* h1, string MCFile, int detn, double Resa,
                           double Resb, int WFnpar = 0, double* WFpar = 0);
int ReadWF(const std::string& filename, double** WFFile);
TH1D* Project2DHisto(string fname, string NameDetector, string NameHisto,
                     string NameMeasurement, int PulseType, int NumberDetector,
                     bool IfEnOrEdep, double& NPulses, double& NProtons,
                     double TOFD, double EnOrEdepMin, double EnOrEdepMax,
                     double TimeMeasurement_ns, bool CorrectDeadTime = false);
void DivideByLi6CS(TH1D* h1);
TH1D* splitBinsIntoSubBins(TH1D* originalHist, int NumberExtraBins = 100);
double evaluateTH1DInRange(TH1D* hist, double A, double B);
TH1D* Project2DHistoSubtractBackground(
    string fname, string NameDetector, string NameHisto, string NameMeasurement,
    int PulseType, int NumberDetector, bool IfEnOrEdep, double& NPulses,
    double& NProtons, double TOFD, double EnOrEdepMin, double EnOrEdepMax,
    double TimeMeasurement_ns, std::vector<string>& MeasPredefined,
    std::vector<string>& BackgroundMeasPredefined,
    std::vector<string>& DummyPredefined,
    std::vector<string>& BackgroundDummyPredefined, TCanvas* c2,
    bool CorrectDeadTime = false);
double GetCountsSili(string fname, int PulseType);
void DivideByNeutronFluence_iso_2024(TH1D* h1);
void DivideByNeutronFluence_iso_2023(TH1D* h1);

int ChangeTOFD(TH1D* histo, double oldTOFD, double newTOFD) {
  int NBins = histo->GetNbinsX();
  double* Xvals = new double[NBins + 1];
  double ene, time;
  for (int i = 0; i <= NBins; i++) {
    ene = histo->GetBinLowEdge(i + 1);
    time = EtoTOF(ene, oldTOFD);
    ene = TOFtoE(time, newTOFD);
    Xvals[i] = ene;
  }
  histo->GetXaxis()->Set(NBins, Xvals);
  delete[] Xvals;
  return 0;
}

int ReadWF(const std::string& filename, double** WFFile) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo: " << filename << std::endl;
    cout << " ###### Error in " << __FILE__ << ", line " << __LINE__
         << " ######" << endl;
    exit(1);
  }

  // Contar cuántos números hay en el archivo
  int totalNumeros = 7;
  string detname;
  int DetNumber;
  // Crear un array dinámico para almacenar los números
  while (file >> detname >> DetNumber) {
    if (detname != "C6D6") {
      cout << " ###### Error in " << __FILE__ << ", line " << __LINE__
           << " ######" << endl;
      exit(1);
    }
    for (int i = 0; i < totalNumeros; i++) {
      file >> WFFile[DetNumber][i];
    }
  }
  file.close();
  cout << "WFFile [1][1]= " << WFFile[1][1] << endl;
  return totalNumeros;
}

TH1D* TH1DFromMC_Resol_v01(TH1D* h1, string MCFile, int detn, double Resa,
                           double Resb, int WFnpar, double* WFpar) {
  TH1D* hmc = new TH1D(*h1);
  // cout << " numero bins mc" << hmc->GetNbinsX() << endl;

  // hmc->SetDirectory(0);

  hmc->Reset();

  TFile* f = new TFile(MCFile.c_str(), "READ");
  cout << "openMC  " << MCFile << endl;
  cout << "Resa " << Resa << " Resb " << Resb << endl;

  char nameTREE[100];
  sprintf(nameTREE, "C6D6_All");
  TTree* TTreeMC = (TTree*)f->Get(nameTREE);

  Double_t Edep;
  Double_t Edep_Gaus;
  Double_t Det;

  TTreeMC->SetBranchAddress("Edep", &Edep);
  TTreeMC->SetBranchAddress("Det", &Det);

  // read all entries and fill the histograms
  Int_t nentries = TTreeMC->GetEntries();
  // cout<<"Read "<<nameTREE<<" nentries "<<nentries<<  endl;
  double weight = 1;

  for (Int_t i = 0; i < nentries; i++) {
    TTreeMC->GetEntry(i);
    Edep_Gaus = gRandom->Gaus(Edep, sqrt(Resa * Edep + Resb * Edep * Edep));
    if (detn == Det) {
      if (WFnpar != 0) {
        weight = 0;
        for (int j = 0; j < WFnpar; j++) {
          weight += WFpar[j] * pow(Edep_Gaus, (double)j);
        }
      }

      // cout<<i<<" Edep "<<Edep<<" Edep_Gaus "<<Edep_Gaus<<" Sigma"<<sqrt(
      // Resa*Edep+Resb*Edep*Edep)<<endl;
      hmc->Fill(Edep_Gaus, weight);
    }
  }
  TH1D* hNumberOfEvents = (TH1D*)f->Get("hNumberOfEvents");
  double NumberEvents = hNumberOfEvents->GetBinContent(1);

  hmc->Scale(1.0 / NumberEvents / hmc->GetBinWidth(10));
  hmc->GetYaxis()->SetTitle("counts/Event/BinWidth");
  cout << " nEvents" << NumberEvents << "hmc->GetBinWidth(1) "
       << hmc->GetBinWidth(10) << endl;

  f->Close();
  delete f;
  return hmc;
}

std::string getAfterSlash(const std::string& input) {
  size_t pos = input.find_last_of('/');  // Buscar la última aparición de '/'
  if (pos != std::string::npos) {
    return input.substr(pos + 1);  // Devolver la parte después de '/'
  }
  return input;  // Si no hay '/', devolver la cadena completa
}

void DivideByLi6CS(TH1D* h1) {
  string NameFile = "DataPlot/Li6_n_t_CS_JEFF33.txt";
  cout << " Dividing by Li6 Cs " << NameFile << endl;
  const int NumberEntriesMax = 1e4;
  double Energy[NumberEntriesMax], CS[NumberEntriesMax];
  ifstream in(NameFile.c_str());
  if (!in.good()) {
    cout << NameFile << " ###### Error in " << __FILE__ << ", line " << __LINE__
         << " ######" << endl;
    exit(1);
  }

  int i = 0;
  while (in >> Energy[i] >> CS[i]) {
    //  cout << Energy[i] << " " << CS[i] << endl;
    i++;
    if (i > NumberEntriesMax) {
      cout << NameFile << " ###### Error in " << __FILE__ << ", line "
           << __LINE__ << " ######" << endl;
      exit(1);
    }
  }
  int nPoints = i;
  Energy[nPoints + 1] =
      Energy[nPoints] + 1e-6;  // Ajuste pequeño para el último bin

  for (int j = 0; j < nPoints; ++j) {
    // cout << j << " " << Energy[j] << " " << nPoints << endl;
  }
  // Crear el histograma con los límites de los bins calculados
  TH1D* hist = new TH1D("convertedHist", "Histograma convertido desde TGraph",
                        nPoints - 1, Energy);

  for (int i = 0; i < nPoints; ++i) {
    hist->SetBinContent(
        i,
        CS[i]);  // Establecer el valor en el bin correspondiente
                 // cout << x << " " << bin << " " << y << endl;
  }
  TH1D* h1Bins = splitBinsIntoSubBins(hist);

  cout << "Finish defining gr1" << endl;
  int nbins = h1->GetNbinsX();
  double ene1, ene2, ene, ValueCS;
  for (int i = 1; i <= nbins; i++) {
    ene1 = h1->GetBinLowEdge(i);
    ene2 = h1->GetBinLowEdge(i + 1);
    ene = h1->GetBinCenter(i);
    // ValueCS = gr1->Eval(ene);
    ValueCS = (hist->Interpolate(ene1) + hist->Interpolate(ene2)) / 2;
    ValueCS = evaluateTH1DInRange(h1Bins, ene1, ene2);

    //    ValueCS = evaluateMeanTGraphInRange(gr1, ene1, ene2);

    // cout << " " << h1->GetBinContent(i) / ValueCS << " "
    //      << h1->GetBinError(i) / ValueCS << endl;
    cout << ene1 << " " << ene2 << " " << ValueCS << endl;
    //    << hist->Interpolate(ene) << " " << h1->GetBinContent(i) / ValueCS
    //  << " " << h1->GetBinError(i) / ValueCS << endl;

    h1->SetBinContent(i, h1->GetBinContent(i) / ValueCS);
    h1->SetBinError(i, h1->GetBinError(i) / ValueCS);
    // cout << h1->GetBinContent(i);
  }
  h1->GetYaxis()->SetTitle("Yield");
}

void DivideByLi6CS_Eff_Flux_2023(TH1D* h1) {
  string NameFile = "DataPlot/Li6_n_t_CS_JEFF33.txt";
  cout << " Dividing by Li6 Cs " << NameFile << endl;
  const int NumberEntriesMax = 1e4;
  double Energy[NumberEntriesMax], CS[NumberEntriesMax];
  ifstream in(NameFile.c_str());
  if (!in.good()) {
    cout << NameFile << " ###### Error in " << __FILE__ << ", line " << __LINE__
         << " ######" << endl;
    exit(1);
  }

  int i = 0;
  while (in >> Energy[i] >> CS[i]) {
    //  cout << Energy[i] << " " << CS[i] << endl;
    i++;
    if (i > NumberEntriesMax) {
      cout << NameFile << " ###### Error in " << __FILE__ << ", line "
           << __LINE__ << " ######" << endl;
      exit(1);
    }
  }
  int nPoints = i;
  Energy[nPoints + 1] =
      Energy[nPoints] + 1e-6;  // Ajuste pequeño para el último bin

  for (int j = 0; j < nPoints; ++j) {
    // cout << j << " " << Energy[j] << " " << nPoints << endl;
  }
  // Crear el histograma con los límites de los bins calculados
  TH1D* hist =
      new TH1D("convertedHist", "Histograma convertido desde       TGraph ",
               nPoints - 1, Energy);

  for (int i = 0; i < nPoints; ++i) {
    hist->SetBinContent(
        i,
        CS[i]);  // Establecer el valor en el bin correspondiente
                 // cout << x << " " << bin << " " << y << endl;
  }
  TH1D* h1Li6 = splitBinsIntoSubBins(hist);
  cout << "Finish defining h1Li6" << endl;

  string NameFile1 = "DataPlot/efficienze_SiMon.dat";
  cout << " Dividing by efficienze_SiMon.dat " << NameFile1 << endl;
  const int NumberEntriesMax1 = 1e4;
  double Energy1[NumberEntriesMax1], Eff1[NumberEntriesMax1],
      DiffEff1[NumberEntriesMax1];
  ifstream in1(NameFile1.c_str());
  if (!in1.good()) {
    cout << NameFile1 << " ###### Error in " << __FILE__ << ", line "
         << __LINE__ << " ######" << endl;
    exit(1);
  }
  int j = 0;
  while (in1 >> Energy1[j] >> Eff1[j] >> DiffEff1[j]) {
    Energy1[j] = Energy1[j] * 1e6;  // it is in MeV so I convert to eV
    // cout << Energy[i] << " " << Eff[i] << endl;
    j++;
    if (j > NumberEntriesMax1) {
      cout << NameFile1 << " ###### Error in " << __FILE__ << ", line "
           << __LINE__ << " ######" << endl;
      exit(1);
    }
  }
  int nPoints1 = j;
  Energy1[nPoints1 + 1] =
      Energy1[nPoints1] + 1e-6;  // Ajuste pequeño para el último bin

  for (int j = 0; j < nPoints1; ++j) {
    // cout << j << " " << Energy[j] << " " << nPoints << endl;
  }
  // Crear el histograma con los límites de los bins calculados
  TH1D* hist1 =
      new TH1D("convertedHist1", "Histograma convertido desde TGraph1",
               nPoints1 - 1, Energy1);

  for (int i = 0; i < nPoints1; ++i) {
    hist1->SetBinContent(
        i,
        Eff1[i]);  // Establecer el valor en el bin correspondiente
                   // cout << x << " " << bin << " " << y << endl;
  }
  TH1D* h1Eff = splitBinsIntoSubBins(hist1, 100000);

  cout << "Finish defining h1Eff" << endl;

  cout << " Dividing by neutron fluence no iso"
          "...DataPlot/evalFlux_prelim.root"
       << endl;
  TFile* f1 = new TFile("DataPlot/evalFlux_prelim.root", "READ");

  if (f1->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }
  //  TH1D* n_flux = (TH1D*)f1->Get("h_EAR2_Flux");
  TH1D* n_flux = (TH1D*)f1->Get("hEval_Abs");
  TH1D* h1Flux = splitBinsIntoSubBins(n_flux);
  cout << "Finish defining h1Flux" << endl;

  int nbins = h1->GetNbinsX();
  double ene1, ene2, ene, ValueCS, ValueEff, ValueFlux;
  for (int i = 1; i <= nbins; i++) {
    ene1 = h1->GetBinLowEdge(i);
    ene2 = h1->GetBinLowEdge(i + 1);
    ene = h1->GetBinCenter(i);
    // ValueCS = gr1->Eval(ene);
    // ValueCS = (hist->Interpolate(ene1) + hist->Interpolate(ene2)) / 2;
    ValueCS = evaluateTH1DInRange(h1Li6, ene1, ene2);
    ValueEff = evaluateTH1DInRange(h1Eff, ene1, ene2);
    ValueFlux = evaluateTH1DInRange(h1Flux, ene1, ene2);

    if (ValueFlux == 0) {
      cout << " ########### warning in " << __FILE__ << ", line " << __LINE__
           << " the numbers of neutrons at energy" << ene1
           << " is zero  ########## #" << endl;
      ValueFlux = 1e10;
    }

    // cout << ene1 << " " << ene2 << " " << h1->GetBinContent(i) << " "
    //      << ValueFlux << " " << ValueCS << " " << ValueEff << " "
    //      << ValueFlux * ValueCS * ValueEff << endl;

    h1->SetBinContent(i, h1->GetBinContent(i) / ValueCS / ValueEff / ValueFlux);
    h1->SetBinError(i, h1->GetBinError(i) / ValueCS / ValueEff / ValueFlux);
    // cout << h1->GetBinContent(i);
  }
  h1->GetYaxis()->SetTitle("Yield");
}

void DivideByEfficiencySiMon1(TH1D* h1) {
  string NameFile = "DataPlot/efficienze_SiMon.dat";
  cout << " Dividing by efficienze_SiMon.dat " << NameFile << endl;
  const int NumberEntriesMax = 1e4;
  double Energy[NumberEntriesMax], Eff[NumberEntriesMax],
      DiffEff[NumberEntriesMax];
  ifstream in(NameFile.c_str());
  if (!in.good()) {
    cout << NameFile << " ###### Error in " << __FILE__ << ", line " << __LINE__
         << " ######" << endl;
    exit(1);
  }
  int i = 0;
  while (in >> Energy[i] >> Eff[i] >> DiffEff[i]) {
    Energy[i] = Energy[i] * 1e6;  // it is in MeV so I convert to eV
    // cout << Energy[i] << " " << Eff[i] << endl;
    i++;
    if (i > NumberEntriesMax) {
      cout << NameFile << " ###### Error in " << __FILE__ << ", line "
           << __LINE__ << " ######" << endl;
      exit(1);
    }
  }
  int nPoints = i;
  Energy[nPoints + 1] =
      Energy[nPoints] + 1e-6;  // Ajuste pequeño para el último bin

  for (int j = 0; j < nPoints; ++j) {
    // cout << j << " " << Energy[j] << " " << nPoints << endl;
  }
  // Crear el histograma con los límites de los bins calculados
  TH1D* hist = new TH1D("convertedHist", "Histograma convertido desde TGraph",
                        nPoints - 1, Energy);

  for (int i = 0; i < nPoints; ++i) {
    hist->SetBinContent(
        i,
        Eff[i]);  // Establecer el valor en el bin correspondiente
                  // cout << x << " " << bin << " " << y << endl;
  }
  TH1D* h1Bins = splitBinsIntoSubBins(hist);

  cout << "Finish defining gr1" << endl;
  int nbins = h1->GetNbinsX();
  double ene1, ene2, ene, ValueCS;
  for (int i = 1; i <= nbins; i++) {
    ene1 = h1->GetBinLowEdge(i);
    ene2 = h1->GetBinLowEdge(i + 1);
    ene = h1->GetBinCenter(i);
    // ValueCS = gr1->Eval(ene);
    ValueCS = (hist->Interpolate(ene1) + hist->Interpolate(ene2)) / 2;
    ValueCS = evaluateTH1DInRange(h1Bins, ene1, ene2);

    //    ValueCS = evaluateMeanTGraphInRange(gr1, ene1, ene2);

    // cout << " " << h1->GetBinContent(i) / ValueCS << " "
    //      << h1->GetBinError(i) / ValueCS << endl;
    cout << ene1 << " " << ene2 << " " << ValueCS << endl;
    //    << hist->Interpolate(ene) << " " << h1->GetBinContent(i) / ValueCS
    //  << " " << h1->GetBinError(i) / ValueCS << endl;

    h1->SetBinContent(i, h1->GetBinContent(i) / ValueCS);
    h1->SetBinError(i, h1->GetBinError(i) / ValueCS);
    // cout << h1->GetBinContent(i);
  }
  h1->GetYaxis()->SetTitle("Yield");
}
void DivideByNeutronFluence_iso_2023(TH1D* h1) {
  // cout << " Dividing by neutron fluence  ISO"
  // "...DataPlot/evalFlux_prelim.root"
  //  << endl;
  // TFile *f1 = new TFile("DataPlot/evalFlux_prelim.root", "READ");

  string NameFile = "DataPlot/Flux_23_24Corected_v02.root";
  string NameHisto = "Flux_23AllRunsNoFilters_SILI_Sample_2cm";

  cout << "Dividingd by flux File= " << NameFile << " Histo= " << NameHisto
       << endl;
  TFile* f1 = new TFile(NameFile.c_str(), "READ");

  if (f1->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }
  //  TH1D* n_flux = (TH1D*)f1->Get("h_EAR2_Flux");
  TH1D* n_flux = (TH1D*)f1->Get(NameHisto.c_str());

  int nbins = h1->GetNbinsX();
  double ene1, ene2, ene, Nneutrons;
  for (int i = 1; i <= nbins; i++) {
    ene1 = h1->GetBinLowEdge(i);
    ene2 = h1->GetBinLowEdge(i + 1);
    ene = h1->GetBinCenter(i);
    Nneutrons = n_flux->Interpolate(ene) * log(ene2 / ene1);

    if (Nneutrons == 0) {
      // cout << " ########### warning in " << __FILE__ << ", line " << __LINE__
      //      << " the numbers of neutrons at energy" << ene1
      //      << " is zero  ########## #" << endl;
      Nneutrons = 1e10;
    }
    h1->SetBinContent(i, h1->GetBinContent(i) / Nneutrons);
    h1->SetBinError(i, h1->GetBinError(i) / Nneutrons);
  }
  h1->GetYaxis()->SetTitle("Yield");

  f1->Close();
  delete f1;
}
void DivideByNeutronFluence_iso_AllYears(TH1D* h1, string NameHisto) {
  // cout << " Dividing by neutron fluence  ISO"
  // "...DataPlot/evalFlux_prelim.root"
  //  << endl;
  // TFile *f1 = new TFile("DataPlot/evalFlux_prelim.root", "READ");

  string NameFile = "DataPlot/Flux_23_24_26_v01.root";
  // string NameHisto = "Flux_23AllRunsNoFilters_SILI_Sample_2cm";

  cout << "Dividingd by flux File= " << NameFile << " Histo= " << NameHisto
       << endl;
  TFile* f1 = new TFile(NameFile.c_str(), "READ");

  if (f1->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }
  //  TH1D* n_flux = (TH1D*)f1->Get("h_EAR2_Flux");
  TH1D* n_flux = (TH1D*)f1->Get(NameHisto.c_str());

  int nbins = h1->GetNbinsX();
  double ene1, ene2, ene, Nneutrons;
  for (int i = 1; i <= nbins; i++) {
    ene1 = h1->GetBinLowEdge(i);
    ene2 = h1->GetBinLowEdge(i + 1);
    ene = h1->GetBinCenter(i);
    Nneutrons = n_flux->Interpolate(ene) * log(ene2 / ene1);

    if (Nneutrons == 0) {
      // cout << " ########### warning in " << __FILE__ << ", line " << __LINE__
      //      << " the numbers of neutrons at energy" << ene1
      //      << " is zero  ########## #" << endl;
      Nneutrons = 1e10;
    }
    h1->SetBinContent(i, h1->GetBinContent(i) / Nneutrons);
    h1->SetBinError(i, h1->GetBinError(i) / Nneutrons);
  }
  h1->GetYaxis()->SetTitle("Yield");

  f1->Close();
  delete f1;
}

void DivideByNeutronFluence_iso_2024(TH1D* h1) {
  // cout << " Dividing by neutron fluence  ISO"
  // "...DataPlot/evalFlux_prelim.root"
  //  << endl;
  // TFile *f1 = new TFile("DataPlot/evalFlux_prelim.root", "READ");

  string NameFile = "DataPlot/Flux_23_24Corected_v02.root";
  string NameHisto = "Flux_24AllBeamRunsNoFilters_SILI_Sample_13mm";

  cout << "Dividingd by flux File= " << NameFile << " Histo= " << NameHisto
       << endl;
  TFile* f1 = new TFile(NameFile.c_str(), "READ");

  if (f1->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }
  //  TH1D* n_flux = (TH1D*)f1->Get("h_EAR2_Flux");
  TH1D* n_flux = (TH1D*)f1->Get(NameHisto.c_str());

  int nbins = h1->GetNbinsX();
  double ene1, ene2, ene, Nneutrons;
  for (int i = 1; i <= nbins; i++) {
    ene1 = h1->GetBinLowEdge(i);
    ene2 = h1->GetBinLowEdge(i + 1);
    ene = h1->GetBinCenter(i);
    Nneutrons = n_flux->Interpolate(ene) * log(ene2 / ene1);

    if (Nneutrons == 0) {
      // cout << " ########### warning in " << __FILE__ << ", line " << __LINE__
      //      << " the numbers of neutrons at energy" << ene1
      //      << " is zero  ########## #" << endl;
      Nneutrons = 1e10;
    }
    h1->SetBinContent(i, h1->GetBinContent(i) / Nneutrons);
    h1->SetBinError(i, h1->GetBinError(i) / Nneutrons);
  }
  h1->GetYaxis()->SetTitle("Yield");

  f1->Close();
  delete f1;
}

void DivideByNeutronFluence_NOiso_2023(TH1D* h1) {
  // cout << " Dividing by neutron fluence "
  //         "...data/h_EAR1_Flux_FLUKA4.3_L184.4m_r4.5cm"
  //      << endl;
  // // TFile* f1=new TFile("data2/flux_ear2.root","READ");
  // TFile* f1 =
  //     new TFile("data/h_EAR1_Flux_FLUKA4.3_L184.4m_r4.5cm.root",
  //     "READ");
  cout << " Dividing by neutron fluence no iso"
          "...DataPlot/evalFlux_prelim.root"
       << endl;
  TFile* f1 = new TFile("DataPlot/evalFlux_prelim.root", "READ");

  if (f1->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }
  //  TH1D* n_flux = (TH1D*)f1->Get("h_EAR2_Flux");
  TH1D* n_flux = (TH1D*)f1->Get("hEval_Abs");
  TH1D* h1Bins = splitBinsIntoSubBins(n_flux);
  // TCanvas* c6 = new TCanvas("c6", "c6", 800, 600);
  // n_flux->Draw("histo");
  //  h1Bins->Draw(" histo same");
  //   TF1* splineFunc = new TF1(
  //     "splineFunc", [&](double* xx, double*) { return
  //     spline->Eval(xx[0]); },
  //   h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax(), 0);
  int nbins = h1->GetNbinsX();
  double ene1, ene2, ene, Nneutrons;
  for (int i = 1; i <= nbins; i++) {
    ene1 = h1->GetBinLowEdge(i);
    ene2 = h1->GetBinLowEdge(i + 1);
    ene = h1->GetBinCenter(i);
    // Nneutrons = n_flux->Interpolate(ene);
    // Nneutrons = evaluateMeanTH1DInRange(n_flux, ene1, ene2);
    Nneutrons = evaluateTH1DInRange(h1Bins, ene1, ene2);

    if (Nneutrons == 0) {
      // cout << " ########### warning in " << __FILE__ << ", line " <<
      // __LINE__
      //      << " the numbers of neutrons at energy" << ene1
      //      << " is zero  ########## #" << endl;
      Nneutrons = 1e10;
    }
    cout << ene1 << " " << ene2 << " " << Nneutrons << endl;
    //  << n_flux->Interpolate(ene) << endl;
    h1->SetBinContent(i, h1->GetBinContent(i) / Nneutrons);
    h1->SetBinError(i, h1->GetBinError(i) / Nneutrons);
  }
  h1->GetYaxis()->SetTitle("Yield");

  f1->Close();
  delete f1;
}
TH1D* Project2DHistoSubtractBackground(
    string fname, string NameDetector, string NameHisto, string NameMeasurement,
    int PulseType, int NumberDetector, bool IfEnOrEdep, double& NPulses,
    double& NProtons, double TOFD, double EnOrEdepMin, double EnOrEdepMax,
    double TimeMeasurement_ns, std::vector<string>& MeasPredefined,
    std::vector<string>& BackgroundMeasPredefined,
    std::vector<string>& DummyPredefined,
    std::vector<string>& BackgroundDummyPredefined, TCanvas* c2,
    bool CorrectDeadTime) {
  string fnameMeas;

  fnameMeas = fname + NameMeasurement + ".root";
  double npulses[4];
  double nprotons[4];
  int PositionBackgrounds = FindPositionString(MeasPredefined, NameMeasurement);
  double rebinFactor = 1;

  TH1D* hMeas = Project2DHisto(
      fnameMeas, NameDetector, NameHisto, NameMeasurement, PulseType,
      NumberDetector, IfEnOrEdep, npulses[0], nprotons[0], TOFD, EnOrEdepMin,
      EnOrEdepMax, TimeMeasurement_ns, CorrectDeadTime);
  TH1D* hFinal = (TH1D*)hMeas->Clone();

  if ((PulseType == 3) && (NameHisto == "Edep" || NameHisto == "Edep_WF")) {
    cout << "##################" << endl;
    cout << "hMeas " << NameMeasurement << endl;
    cout << "BackgroundMeasPredefined "
         << BackgroundMeasPredefined[PositionBackgrounds] << endl;
    cout << "##################" << endl;
    fnameMeas = fname + BackgroundMeasPredefined[PositionBackgrounds] + ".root";

    TH1D* hDummy = Project2DHisto(
        fnameMeas, NameDetector, NameHisto,
        BackgroundMeasPredefined[PositionBackgrounds], PulseType,
        NumberDetector, IfEnOrEdep, npulses[1], nprotons[1], TOFD, EnOrEdepMin,
        EnOrEdepMax, TimeMeasurement_ns, CorrectDeadTime);

    hFinal->Add(hDummy,
                -npulses[0] / npulses[1]);  // Quitamos el no beam

    c2->SetTickx();
    c2->SetTicky();
    c2->SetLogy();

    hDummy->Scale(npulses[0] / npulses[1]);

    hMeas->Draw("histo E");
    hDummy->Draw("histo E same");
    hFinal->Draw("histo E same");

    hMeas->SetLineColor(1);
    hDummy->SetLineColor(4);
    hFinal->SetLineColor(8);

    c2->ToggleEditor();
    TLegend* legend = new TLegend(0.6, 0.62, 0.96, 0.86, "");
    legend->AddEntry(hMeas, "hMeas", "l");
    legend->AddEntry(hDummy, "hDummy", "l");
    legend->AddEntry(hFinal, "hFinal", "l");

    legend->SetTextSize(0.06);
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();
    c2->cd();
    NPulses = npulses[0];
    NProtons = nprotons[0];
  }

  else {
    rebinFactor = 10;
    double PulseTypForNoBeam = 3;  // can also be 0
    if (NameHisto == "TOF") {
      PulseTypForNoBeam = 0;
    }

    cout << "##################" << endl;
    cout << "hMeas " << NameMeasurement << endl;
    cout << "hDummy " << DummyPredefined[PositionBackgrounds] << endl;
    cout << "hBackMeas " << BackgroundMeasPredefined[PositionBackgrounds]
         << endl;
    cout << "hBackDummy " << BackgroundDummyPredefined[PositionBackgrounds]
         << endl;
    cout << "##################" << endl;

    fnameMeas = fname + DummyPredefined[PositionBackgrounds] + ".root";
    TH1D* hDummy = Project2DHisto(
        fnameMeas, NameDetector, NameHisto,
        DummyPredefined[PositionBackgrounds], PulseType, NumberDetector,
        IfEnOrEdep, npulses[1], nprotons[1], TOFD, EnOrEdepMin, EnOrEdepMax,
        TimeMeasurement_ns, CorrectDeadTime);

    fnameMeas = fname + BackgroundMeasPredefined[PositionBackgrounds] + ".root";
    TH1D* hBackMeas = Project2DHisto(
        fnameMeas, NameDetector, NameHisto,
        BackgroundMeasPredefined[PositionBackgrounds], PulseTypForNoBeam,
        NumberDetector, IfEnOrEdep, npulses[2], nprotons[2], TOFD, EnOrEdepMin,
        EnOrEdepMax, TimeMeasurement_ns, CorrectDeadTime);

    fnameMeas =
        fname + BackgroundDummyPredefined[PositionBackgrounds] + ".root";
    TH1D* hBackDummy = Project2DHisto(
        fnameMeas, NameDetector, NameHisto,
        BackgroundDummyPredefined[PositionBackgrounds], PulseTypForNoBeam,
        NumberDetector, IfEnOrEdep, npulses[3], nprotons[3], TOFD, EnOrEdepMin,
        EnOrEdepMax, TimeMeasurement_ns, CorrectDeadTime);

    // E
    TH1D* hAllBack = (TH1D*)hDummy->Clone();

    hAllBack->Add(hBackDummy,
                  -npulses[1] / npulses[3]);  // quitamos el no beam del dummy
    hAllBack->Scale(nprotons[0] /
                    nprotons[1]);  // normalizamos a protones del Meas

    if (NameMeasurement == DummyPredefined[PositionBackgrounds]) {
      cout << "The meausured is equal to the empty so I do not subtracted"
           << endl;
      cout << NameMeasurement << " =  " << DummyPredefined[PositionBackgrounds]
           << endl;
      hAllBack->Scale(1e-20);
      cout << "Do ENTER to cointinue" << endl;
      cin.get();
    }

    hAllBack->Add(hBackMeas,
                  npulses[0] / npulses[2]);  // añadimos el no beam del Meas
    hFinal->Add(hAllBack, -1);               // sustraemos todos los fondos.

    //
    hDummy->Scale(nprotons[0] /
                  nprotons[1]);  // normalizamos a protones del Meas
    hBackMeas->Scale(npulses[0] / npulses[2]);   // normalizamos pulsos del Meas
    hBackDummy->Scale(npulses[0] / npulses[3]);  // normalizamos pulsos del Meas

    NPulses = npulses[0];
    NProtons = nprotons[0];

    c2->SetTickx();
    c2->SetTicky();
    c2->SetLogy();

    if (IfEnOrEdep) {
      rebinFactor = 500;
      c2->SetLogx();
    }
    hMeas->Draw("histo E");
    hAllBack->Draw("histo E same");
    hBackMeas->Draw("histo E same");
    hBackDummy->Draw("histo E same");
    hDummy->Draw("histo E same");
    hFinal->Draw("histo E same");

    hMeas->SetLineColor(1);
    hBackMeas->SetLineColor(2);
    hBackDummy->SetLineColor(6);
    hDummy->SetLineColor(4);
    hAllBack->SetLineColor(5);
    hFinal->SetLineColor(8);

    c2->ToggleEditor();
    TLegend* legend = new TLegend(0.6, 0.62, 0.96, 0.86, "");
    legend->AddEntry(hMeas, "hMeas", "l");
    legend->AddEntry(hBackMeas, "hBackMeas", "l");
    legend->AddEntry(hBackDummy, "hBackDummy", "l");
    legend->AddEntry(hDummy, "hDummy", "l");
    legend->AddEntry(hAllBack, "hAllBack", "l");
    legend->AddEntry(hFinal, "hFinal", "l");

    legend->SetTextSize(0.06);
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();
    c2->cd();

    hMeas->Rebin(rebinFactor);
    hBackMeas->Rebin(rebinFactor);
    hBackDummy->Rebin(rebinFactor);
    hDummy->Rebin(rebinFactor);
    hAllBack->Rebin(rebinFactor);
  }

  TH1D* hFinalReturn = (TH1D*)hFinal->Clone();

  hFinal->Rebin(rebinFactor);

  return hFinalReturn;
}

TH1D* Project2DHisto(string fname, string NameDetector, string NameHisto,
                     string NameMeasurement, int PulseType, int NumberDetector,
                     bool IfEnOrEdep, double& NPulses, double& NProtons,
                     double TOFD, double EnOrEdepMin, double EnOrEdepMax,
                     double TimeMeasurement_ns, bool CorrectDeadTime) {
  // gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  TFile* f = new TFile(fname.c_str(), "READ");
  // f->ls();
  cout << "Project2DHisto from " << fname.c_str() << endl;
  if (f->IsZombie()) {
    cout << " The rootfile " << fname.c_str() << " does not exist" << endl
         << " ########### in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    // TH1D* hFalse = new TH1D("false", "false", 100, 1, 1e4);
    // NProtons = 1;
    // NPulses = 1;
    // sleep(3);
    // exit(1);
    // return hFalse;
  }

  string NameHistoPulseIntensity = "hPulIntens_" + to_string(PulseType);
  cout << "Get Histo " << NameHistoPulseIntensity << endl;

  TH1D* h1 = (TH1D*)f->Get(NameHistoPulseIntensity.c_str());
  if (h1->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }

  NProtons = (double)h1->GetBinContent(1);
  NPulses = (double)h1->GetBinContent(2);
  double NSili = (double)h1->GetBinContent(5);

  if (UseSiliCountsInsteadOfProtons && NameDetector != "SILI") {
    double CountsSiliGainCorrected = GetCountsSili(fname, PulseType);
    // cout << endl << "CountsSiliGainCorrected = " << CountsSiliGainCorrected
    // << endl;

    cout << endl
         << "CountsSiliGainCorrected are used instead of protons, the "
            "difference bewtween them is "
         << 100 *
                (NProtons - CountsSiliGainCorrected *
                                FactorToMultyplySiliCountsToProtons) /
                NProtons
         << "+-"
         << 100 * sqrt(CountsSiliGainCorrected) *
                FactorToMultyplySiliCountsToProtons / NProtons
         << " % " << " NProtons = " << NProtons << " CountsSiliGainCorrected = "
         << CountsSiliGainCorrected * FactorToMultyplySiliCountsToProtons
         << " SiliCounts = " << NSili * FactorToMultyplySiliCountsToProtons
         << endl;
    cout << "Ratio CountsSiliGainCorrected/CountsSili = "
         << CountsSiliGainCorrected / NSili << endl;
    NProtons = CountsSiliGainCorrected * FactorToMultyplySiliCountsToProtons;
  }

  TH2D* h2;

  string NameHisto2D = NameHisto + "_" + NameDetector + "_" +
                       to_string(NumberDetector) + "_PType_" +
                       to_string(PulseType);
  cout << "Get Histo " << NameHisto2D << endl;

  h2 = (TH2D*)f->Get(NameHisto2D.c_str());
  h2->Sumw2();

  if (h2->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }

  //
  string NameHisto1D = "1D" + NameHisto2D;
  TH1D* h3;

  if (PulseType == 3) {
    // Checks to see if the h2 Histo for Y axis include a time similar to
    // TimeMeasurement_ns
    double TimeHighLimit = EtoTOF(h2->GetXaxis()->GetBinLowEdge(1), TOFD);
    double TimeLowLimit =
        EtoTOF(h2->GetXaxis()->GetBinUpEdge(h2->GetNbinsX()), TOFD);
    if (TimeHighLimit < TimeMeasurement_ns) {
      cout << "TimeHighLimit (" << TimeHighLimit
           << ") is smaller than TimeMeasurement_ns  (" << TimeMeasurement_ns
           << ")" << endl;
      // The time measured high limit has to be higher
      cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
           << " ###########" << endl;
      exit(1);
    }
    if (TimeLowLimit > (TimeMeasurement_ns / 1000)) {
      // The time measured low limit has to be smaller than 0.01%  of the
      // time
      cout << "TimeLowLimit (" << TimeLowLimit
           << ") is bigger than TimeMeasurement_ns / 10000 ("
           << TimeMeasurement_ns / 10000 << ")" << endl;
      cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
           << " ###########" << endl;
      exit(1);
    }
    cout << "Type 3 pulse lowlimit= " << TimeLowLimit
         << "  TimeHighLimit= " << TimeHighLimit << endl;
    if (IfEnOrEdep) {
      int minbin = h2->GetYaxis()->FindBin(EnOrEdepMin);
      int maxbin = h2->GetYaxis()->FindBin(EnOrEdepMax);
      cout << endl
           << " Taking En type 3 spectrum  from " << fname << " between "
           << h2->GetYaxis()->GetBinLowEdge(minbin) << "(" << EnOrEdepMin
           << ") and " << h2->GetYaxis()->GetBinLowEdge(maxbin + 1) << "("
           << EnOrEdepMax << ")   ......" << endl;

      h3 = h2->ProjectionX(NameHisto1D.c_str(), minbin, maxbin, "e");
      // h3->Sumw2();

      double Emin, Emax, ErrorTotalCounts;

      double TotalCounts =
          h3->IntegralAndError(0, h3->GetNbinsX(), ErrorTotalCounts);
      for (int i = 1; i <= h3->GetNbinsX(); i++) {
        Emin = h3->GetBinLowEdge(i);
        Emax = h3->GetBinLowEdge(i + 1);

        h3->SetBinContent(i, TotalCounts * DeltaEnergyToTime(Emin, Emax, TOFD) /
                                 TimeMeasurement_ns);
        h3->SetBinError(i, ErrorTotalCounts *
                               DeltaEnergyToTime(Emin, Emax, TOFD) /
                               TimeMeasurement_ns);
      }
    } else {
      int minbin = h2->GetXaxis()->FindBin(EnOrEdepMin);
      int maxbin = h2->GetXaxis()->FindBin(EnOrEdepMax);
      cout << endl
           << " Taking Edep type 3 for spectrum from " << fname << " between "
           << h2->GetXaxis()->GetBinLowEdge(minbin) << "(" << EnOrEdepMin
           << ") and " << h2->GetXaxis()->GetBinLowEdge(maxbin + 1) << "("
           << EnOrEdepMax << ")   ......" << endl;
      h3 = h2->ProjectionY(NameHisto1D.c_str(), 0, h2->GetNbinsY(), "e");
      // h3->Sumw2();

      double scalefactor = DeltaEnergyToTime(EnOrEdepMin, EnOrEdepMax, TOFD) /
                           TimeMeasurement_ns;
      cout << " DeltaEnergyToTime  "
           << DeltaEnergyToTime(EnOrEdepMin, EnOrEdepMax, TOFD) << endl;

      cout << "scalefactor  " << scalefactor << endl;
      h3->Scale(1.0 * scalefactor);
    };

  }
  ////No pulse 3
  else {
    if (IfEnOrEdep) {
      int minbin = h2->GetYaxis()->FindBin(EnOrEdepMin);
      int maxbin = h2->GetYaxis()->FindBin(EnOrEdepMax);
      cout << endl
           << " Taking En spectrum from " << fname << " between "
           << h2->GetYaxis()->GetBinLowEdge(minbin) << "(" << EnOrEdepMin
           << ") and " << h2->GetYaxis()->GetBinLowEdge(maxbin + 1) << "("
           << EnOrEdepMax << ")   ......" << endl;
      h3 = h2->ProjectionX(NameHisto1D.c_str(), minbin, maxbin, "e");
      // h3->Sumw2();

    } else {
      int minbin = h2->GetXaxis()->FindBin(EnOrEdepMin);
      int maxbin = h2->GetXaxis()->FindBin(EnOrEdepMax);
      cout << endl
           << " Taking Edep spectrum from " << fname << " between "
           << h2->GetXaxis()->GetBinLowEdge(minbin) << "(" << EnOrEdepMin
           << ") and " << h2->GetXaxis()->GetBinLowEdge(maxbin + 1) << "("
           << EnOrEdepMax << ")   ......" << endl;
      h3 = h2->ProjectionY(NameHisto1D.c_str(), minbin, maxbin, "e");
      // h3->Sumw2();
    }
  }

  // Check that the cuts in energy have a diference less than 5% with
  // respect to the ones given in the program
  double MaximunDiferenceAllowedInPercent = 3;

  double EnOrEdepMinUsed =
      h2->GetYaxis()->GetBinLowEdge(h2->GetYaxis()->FindBin(EnOrEdepMin));
  double EnOrEdepMaxUsed =
      h2->GetYaxis()->GetBinLowEdge(h2->GetYaxis()->FindBin(EnOrEdepMax) + 1);

  if (!IfEnOrEdep) {
    EnOrEdepMinUsed =
        h2->GetXaxis()->GetBinLowEdge(h2->GetXaxis()->FindBin(EnOrEdepMin));
    EnOrEdepMaxUsed =
        h2->GetXaxis()->GetBinLowEdge(h2->GetXaxis()->FindBin(EnOrEdepMax) + 1);
  }
  if ((EnOrEdepMinUsed <
       (EnOrEdepMin * (100 - MaximunDiferenceAllowedInPercent) / 100)) ||
      (EnOrEdepMinUsed >
       (EnOrEdepMin * (100 + MaximunDiferenceAllowedInPercent) / 100))) {
    cout << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << "There is more than " << MaximunDiferenceAllowedInPercent
         << " \% diference used=" << EnOrEdepMinUsed << " should be "
         << EnOrEdepMin << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl;
  }

  if ((EnOrEdepMaxUsed <
       (EnOrEdepMax * (100 - MaximunDiferenceAllowedInPercent) / 100)) ||
      (EnOrEdepMaxUsed >
       (EnOrEdepMax * (100 + MaximunDiferenceAllowedInPercent) / 100))) {
    cout << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << "There is more than " << MaximunDiferenceAllowedInPercent
         << " \% diference used=" << EnOrEdepMaxUsed << " should be "
         << EnOrEdepMax << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl;
  }

  cout << " Npulses " << NPulses << " Nprotons " << NProtons
       << " Nprotons/NPulses " << NProtons / NPulses << endl;
  string NameForHisto2D = NameMeasurement + "_" + NameHisto + "_" +
                          NameDetector + "_" + to_string(NumberDetector) +
                          "_PType_" + to_string(PulseType);
  h3->SetName(NameForHisto2D.c_str());
  h3->SetDirectory(0);

  h3->SetLineWidth(3);

  h3->GetXaxis()->SetLabelSize(0.06);
  h3->GetXaxis()->SetTitleSize(0.06);

  h3->GetXaxis()->SetTitleOffset(1.1);
  h3->GetXaxis()->SetLabelOffset(0.015);

  h3->GetYaxis()->SetLabelSize(0.06);
  h3->GetYaxis()->SetTitleSize(0.06);
  if (CorrectDeadTime) {
    TH1D* h4 = new TH1D();

    if (IfEnOrEdep) {
      if (NumberDetector == 0) {
        cout << endl
             << "#######################################" << endl
             << "In the case of Det=0 I take the DeadTime correction for "
                "det=1; This is an approximation "
             << endl
             << "#######################################" << endl;
        NumberDetector = 1;
      }

      double NumberProtonsDeadTime, NumberPulsesDeadTime;
      h4 = Project2DHisto(fname, NameDetector, "En", NameMeasurement, PulseType,
                          NumberDetector, IfEnOrEdep, NumberPulsesDeadTime,
                          NumberProtonsDeadTime, TOFD, EnOrEdepMin, EnOrEdepMax,
                          TimeMeasurement_ns, false);

      h4->Scale(1.0 / NumberPulsesDeadTime);
      if (PulseType == 0) {
        cout << " In the case of PulseType=0 for the dead time, I "
                "calculate "
                "the CR for the pulses 1,2, 3 to determine the "
                "correction. "
                "This is an approximation "

             << endl;
        PulseType = 1;
      }

      if (NumberDetector == 0) {
        cout << " detector 0 is not yet Implemented ########### Error in "
             << __FILE__ << ", line " << __LINE__ << " ###########" << endl;
        exit(1);
      }

      TH2D* h5;
      string NameHistoDeadTime = "DetectorDeadTime_ns_" + NameDetector + "_" +
                                 to_string(NumberDetector) + "_PType_" +
                                 to_string(PulseType);
      // cout << "Get Histo " << NameHistoDeadTime << endl;

      h5 = (TH2D*)f->Get(NameHistoDeadTime.c_str());
      double DeadTimeHisto = h5->GetBinContent(1, 1) / (double)h5->GetEntries();
      cout << endl
           << " entries" << h5->GetEntries() << "  BinContent   "
           << h5->GetBinContent(1, 1) << " DeadTime " << DeadTimeHisto << endl;

      CalculateDeadTimeHisto(h4, TOFD, DeadTimeHisto);

      TCanvas* c4 =
          new TCanvas((NameHistoDeadTime + NameMeasurement).c_str(),
                      (NameHistoDeadTime + NameMeasurement).c_str(), 800, 600);

      h4->Draw("histo");
      c4->SetLogx();
      // c4->SetLogy();
      c4->SetGrid();
      h4->GetYaxis()->SetRangeUser(1, 1.05);

    } else {
      cout << " No dead time correction implememted yet for Edep" << endl;
    }
    h3->Multiply(h4);
  }

  // h3 = (TH1D*)h4->Clone();
  f->Close();
  delete f;
  return h3;
}

TH1D* GetSimulMC(TH1D* h1, int detn, string MeasurementType,
                 std::vector<string>& NameSimulArray,
                 std::vector<string>& NameSimulRootfile,
                 std::vector<double>& Activity_kBq,
                 std::vector<int>& ResolNumberDetector,
                 std::vector<double>& ResolParameter1,
                 std::vector<double>& ResolParameter2, string TypeOfPlot,
                 string WFFile) {
  int PositionNameSimul = FindPositionString(NameSimulArray, MeasurementType);
  string fname = NameSimulRootfile[PositionNameSimul];
  double Activity = Activity_kBq[PositionNameSimul];

  int PositionDetector = FindPositionString(ResolNumberDetector, detn);
  double Resol1 = ResolParameter1[PositionDetector];
  double Resol2 = ResolParameter2[PositionDetector];

  TH1D* h2;
  cout << "Activity " << Activity << " kBq" << endl;
  if (WFFile == "0") {
    cout << "Do ot use WF  " << WFFile << endl;
    h2 = TH1DFromMC_Resol_v01(h1, fname, detn, Resol1, Resol2);
  } else {
    cout << "Use WF  " << WFFile << endl;

    double** WFpar = new double*[100];
    for (int i = 0; i < 100; ++i) {
      WFpar[i] = new double[100];
    }
    int WFnpar = 1;
    WFnpar = ReadWF(WFFile, WFpar);
    double WFparDet[WFnpar];
    for (int i = 0; i < WFnpar; ++i) {
      WFparDet[i] = WFpar[detn][i];
      cout << "WFparDet[" << i << "] " << WFparDet[i] << endl;
    }
    h2 =
        TH1DFromMC_Resol_v01(h1, fname, detn, Resol1, Resol2, WFnpar, WFparDet);
  }

  h2->Scale(Activity * 1000);

  return h2;
}

TH1D* GetSimul(TH1D* h1, string MeasurementType,
               std::vector<string>& NameSimulArray,
               std::vector<string>& NameSimulRootfile, string TypeOfPlot) {
  int PositionNameSimul = FindPositionString(NameSimulArray, MeasurementType);
  string fname = NameSimulRootfile[PositionNameSimul] + ".root";

  TFile* f1 = new TFile(fname.c_str(), "READ");
  cout << endl << "GetSimul " << fname << endl;
  if (f1->IsZombie()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }

  TH1D* h2 = (TH1D*)f1->Get("h1");

  TH1D* h3 = (TH1D*)h1->Clone();
  for (int i = 1; i <= h3->GetNbinsX(); i++) {
    h3->SetBinContent(i, h2->GetBinContent(h2->FindBin(h3->GetBinCenter(i))));
    h3->SetBinError(i, 0);
  }

  return h3;
}

void Normalize(TH1D** h1, int const nHisto, TH1D* hToNormalize, double Emin,
               double Emax) {
  double Integrals[nHisto];
  double Errors[nHisto];
  double IntegralsToNormalize;
  double ErrorsToNormalize;
  IntegralsToNormalize =
      hToNormalize->IntegralAndError(hToNormalize->FindBin(Emin),
                                     hToNormalize->FindBin(Emax),
                                     ErrorsToNormalize) /*/ /
       (hToNormalize->GetBinLowEdge(1 + hToNormalize->FindBin(Emax)) -
        hToNormalize->GetBinLowEdge(hToNormalize->FindBin(Emin)))*/
      / (1 + hToNormalize->FindBin(Emax) - hToNormalize->FindBin(Emin));
  cout << "#####################" << endl;

  cout << "Normalize betwen" << Emin << " " << Emax << endl;
  for (auto i = 0; i < nHisto; i++) {
    Integrals[i] = h1[i]->IntegralAndError(h1[i]->FindBin(Emin),
                                           h1[i]->FindBin(Emax), Errors[i]) /*/
                               (h1[i]->GetBinLowEdge(1 + h1[i]->FindBin(Emax)) -
                               h1[i]->GetBinLowEdge(h1[i]->FindBin(Emin)))*/
                   / (1 + h1[i]->FindBin(Emax) - h1[i]->FindBin(Emin));
    Errors[i] = Errors[i] / (1 + h1[i]->FindBin(Emax) - h1[i]->FindBin(Emin));

    h1[i]->Scale(IntegralsToNormalize / Integrals[i]);
    cout << "Scale" << h1[i]->GetTitle() << " by "
         << IntegralsToNormalize / Integrals[i] << " Real range of integral "
         << h1[i]->GetBinLowEdge(h1[i]->FindBin(Emin)) << " to "
         << h1[i]->GetBinLowEdge(1 + h1[i]->FindBin(Emax)) << " Number of bins"
         << h1[i]->FindBin(Emax) - h1[i]->FindBin(Emin) << " Total Counts = "
         << Integrals[i] * (1 + h1[i]->FindBin(Emax) - h1[i]->FindBin(Emin))
         << " Integral " << Integrals[i] << " +- " << Errors[i]
         << "Error (%)= " << 100 * Errors[i] / Integrals[i] << endl;

    ;
  }
  cout << "#####################" << endl;
}

TH1D* CalculateRatioHisto(TH1D* h1, TH1D* h2) {
  cout << " The errors are not correctly calculated, they are "
          "underestimated"
       << endl;
  TH1D* h3 = (TH1D*)h1->Clone();
  double y1, y2, e1;
  if (h1->GetNbinsX() != h2->GetNbinsX()) {
    cout << " ########### Error in " << __FILE__ << ", line " << __LINE__
         << " ###########" << endl;
    exit(1);
  }
  for (int i = 0; i < h1->GetNbinsX(); i++) {
    y1 = h1->GetBinContent(i);
    e1 = h1->GetBinError(i);
    y2 = h2->GetBinContent(i);
    if (y2 == 0) {
      h3->SetBinContent(i, 0);
      h3->SetBinError(i, 0);
    } else {
      h3->SetBinContent(i, y1 / y2);
      h3->SetBinError(i, e1 / y2);
    }
  }
  return h3;
}

TH1D* CalculateBestShift(double& shift, TH1D* h1, TH1D* h2, double EminFit,
                         double EmaxFit, int Iterations, double MinShift,
                         double MaxShift) {
  TH1D* h3 = (TH1D*)h1->Clone();
  double BestFit = 1e8, BestFitk = 0;
  double Chi2 = 1e8;
  for (int k = 0; k < Iterations; k++) {
    h3 = Transform(h1, MinShift + (k * (MaxShift - MinShift) / Iterations));

    Chi2 = CompareHistograms(h2, h3, EminFit, EmaxFit);

    // cout << k << " " << MinShift + (k * (MaxShift - MinShift) /
    // Iterations)
    //    << " Chi2 " << Chi2 << endl;

    if (Chi2 < BestFit) {
      BestFit = Chi2, BestFitk = k;
    }
  }

  h3 =
      Transform(h1, MinShift + (BestFitk * (MaxShift - MinShift) / Iterations));

  // cout << "BestFit"
  //    << MinShift + (BestFitk * (MaxShift - MinShift) / Iterations) <<
  //    endl;
  shift = MinShift + (BestFitk * (MaxShift - MinShift) / Iterations);

  return h3;
}

// Coje el tipo de run de un RunNumber
string TakeRunType(const char* fname, int RunNumber) {
  char word[1000];
  string RunType = {"NoRun"};
  ifstream in(fname);
  while (in >> word) {
    // cout<<word<<endl;
    if (!strcmp(word, "RUNLIST")) {
      break;
    }
  }
  if (!in.good()) {
    cout << " ###### Error in " << __FILE__ << ", line " << __LINE__
         << " ######" << endl;
    exit(1);
  }

  int runmin, runmax;
  while (in >> runmin >> runmax >> word) {
    // cout<<"Runmin"<<runmin<<" "<<runmin<<" "<<word<<endl;
    if (runmin <= RunNumber && runmax >= RunNumber) {
      //      sprintf( RunType,"%s",str2);
      RunType = word;
      break;
    }
  }
  in.close();
  // cout<<"RunNumber"<<RunNumber<<"RunType= "<<RunType<<endl;

  return RunType;
}

TH1D* splitBinsIntoSubBins(TH1D* originalHist, int NumberExtraBins) {
  int nBins = originalHist->GetNbinsX();

  // Crear un array para almacenar los valores interpolados (1000 puntos por
  // bin)
  // double NumberExtraBins = 100;
  int newNbins = nBins * NumberExtraBins;
  double* xValues = new double[newNbins];
  double* yValues = new double[newNbins];

  // Llenar el array de valores de x y y, interpolando entre los bins
  // originales
  int index = 0;
  for (int i = 1; i <= nBins; ++i) {
    double binLowEdge = originalHist->GetXaxis()->GetBinLowEdge(i);
    double binHighEdge = originalHist->GetXaxis()->GetBinUpEdge(i);
    double binContent = originalHist->GetBinContent(i);

    // Crear NumberExtraBins sub-bins en el rango de cada bin original
    double binWidth = originalHist->GetBinWidth(i);
    for (int j = 0; j < NumberExtraBins; ++j) {
      // Crear los 1000 valores de X dentro de cada bin
      xValues[index] = binLowEdge + j * (binWidth / NumberExtraBins);
      // yValues[index] =
      // binContent;  // Dividimos el contenido entre los 1000 sub-bins
      yValues[index] = originalHist->Interpolate(xValues[index]);
      // Dividimos el contenido entre los 1000 sub-bins
      ++index;
    }
  }

  xValues[(int)(nBins * NumberExtraBins)] =
      originalHist->GetXaxis()->GetBinUpEdge(nBins);
  for (int i = 1; i <= nBins * NumberExtraBins; ++i) {
    // cout << xValues[i] << " " << yValues[i] << endl;

    if ((xValues[i - 1] >= xValues[i])) {
      cout << " ###### Error in " << __FILE__ << ", line " << __LINE__
           << " ######" << endl;
      cout << xValues[i - 1] << " " << yValues[i - 1] << endl;
      cout << xValues[i] << " " << yValues[i] << endl;

      exit(1);
    }
  }

  // Crear el nuevo histograma con más bins, usando los valores interpolados
  TH1D* newHist =
      new TH1D("splitHist", "Histograma con sub-bins", newNbins, xValues);

  // Rellenar el histograma con los valores interpolados
  for (int i = 0; i < newNbins; ++i) {
    newHist->SetBinContent(i + 1, yValues[i]);
  }

  // Dibujar el nuevo histograma
  newHist->Draw();

  // Liberar memoria
  delete[] xValues;
  delete[] yValues;

  return newHist;
}

double evaluateTH1DInRange(TH1D* hist, double A, double B) {
  if (!hist) {
    std::cerr << "Error: El histograma es nulo." << std::endl;
    return -1;
  }

  // Obtener el número de bins y el rango del histograma
  int nBins = hist->GetNbinsX();
  double xMin = hist->GetXaxis()->GetXmin();
  double xMax = hist->GetXaxis()->GetXmax();

  // Comprobar que A y B están dentro del rango del histograma
  if (A < xMin || B > xMax) {
    std::cerr << "Error: El rango de integración está fuera de los límites "
                 "del histograma."
              << std::endl;
    return -1;
  }

  // Encontrar el bin correspondiente a A y B
  int binA = hist->FindBin(A);
  int binB = hist->FindBin(B);

  // Sumar los contenidos de los bins dentro del rango
  double sum = 0.0;
  double totalEntries = 0.0;
  for (int i = binA; i <= binB; ++i) {
    double binContent = hist->GetBinContent(i);
    sum += binContent;
    totalEntries += 1.0;
  }

  // Calcular el valor promedio
  if (totalEntries == 0) {
    std::cerr << "Error: No se encontraron bins en el rango dado." << std::endl;
    return -1;
  }
  // cout << "Total Entries " << sum << endl;
  // return sum;  // Promedio de los contenidos de los bins

  return sum / totalEntries;  // Promedio de los contenidos de los bins
}

double GetCountsSili(string fname, int PulseType) {
  double NPulses, NProtons;
  TH1D* SiliHisto =
      Project2DHisto(fname, "SILI", "En", "Empty", PulseType, 0, true, NPulses,
                     NProtons, TOFD, 2.2e4, 4e4, TimeMeasurement_ns, false);
  double Integral =
      SiliHisto->Integral(SiliHisto->FindBin(0.02), SiliHisto->FindBin(1e5));
  delete SiliHisto;
  return Integral;
}
#endif
