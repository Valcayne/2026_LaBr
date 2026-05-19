#include <Pulse.h>

std::vector<double> Pulse::runs = {};

Pulse::Pulse(const int type, const std::string name,
             const std::vector<Detector> detectors)
    : type(type), name(name), detectors(detectors) {}

Pulse::~Pulse() {}
void NormalizeGraph(TGraphErrors *graph);
void Pulse::AppendNumbers(const double n) { numbers.push_back(n); }

void Pulse::AppendProtons(const double p) { protons.push_back(p); }

void Pulse::AppendPkupAreas(const double pa) { pkup_areas.push_back(pa); }

bool Pulse::HasProtons() { return !protons.empty(); }

void Pulse::CreateGraphs() {
  std::string result;
  std::vector<double> ratios;
  std::vector<double> uncertainties;

  result = "Protons per pulse";
  ratios.clear();
  uncertainties.clear();
  for (auto i = 0; i < numbers.size(); i++) {
    ratios.push_back(protons.at(i) * 8e12 / numbers.at(i));
    uncertainties.push_back(0);
  }
  graphs.push_back(CreateGraph(result, ratios, uncertainties,
                               "Protons / 8*10^{12} / pulse"));

  result = "Protons per PKUP area";
  ratios.clear();
  uncertainties.clear();
  for (auto i = 0; i < pkup_areas.size(); i++)
    ratios.push_back(protons.at(i) / pkup_areas.at(i));
  graphs.push_back(CreateGraph(result, ratios, uncertainties,
                               "Protons / 8*10^{12} / PKUP area"));

  for (auto &detector : detectors) {
    for (const auto [id, counts] : detector.GetCounts()) {
      result = detector.name + " " + std::to_string(id) + " counts per proton";
      ratios.clear();
      uncertainties.clear();
      for (auto i = 0; i < protons.size(); i++) {
        const auto c = counts.at(i);
        const auto cpp = c / protons.at(i);
        ratios.push_back(cpp);
        uncertainties.push_back(cpp * TMath::Sqrt(c) / c);
      }
      detector.AppendGraph(CreateGraph(result, ratios, uncertainties,
                                       "Counts / proton / 8*10^{12}"));
    }
  }
}

void Pulse::WriteGraphsToFile(const std::string filename) {
  const auto file =
      std::unique_ptr<TFile>(new TFile(filename.data(), "UPDATE"));

  const auto directory = file->mkdir(name.c_str());
  for (const auto graph : graphs) directory->Append(graph);

  for (auto &detector : detectors) {
    const auto detector_directory = directory->mkdir(detector.name.c_str());
    for (const auto graph : detector.GetGraphs())
      detector_directory->Append(graph);
  }

  file->Write();
  file->Close();
}

TCanvas *Pulse::CreateGraph(const std::string name,
                            const std::vector<double> ratios,
                            const std::vector<double> uncertainties,
                            const std::string ratios_title) {
  const auto unique_name = name + " (" + std::to_string(type) + ")";
  const auto c = new TCanvas(unique_name.c_str(), unique_name.c_str());
  c->SetGrid();

  const auto g = new TGraphErrors(runs.size(), runs.data(), ratios.data(),
                                  nullptr, uncertainties.data());

  g->SetName(c->GetName());
  g->SetTitle(c->GetTitle());
  NormalizeGraph(g);

  const auto y_axis = g->GetYaxis();
  y_axis->SetTitle(ratios_title.c_str());

  const auto x_axis = g->GetXaxis();
  x_axis->SetTitle("Run");
  x_axis->SetNoExponent();

  //// Added by victor to calculate the ratios
  y_axis->SetTitle("Value/Average");

  g->Draw("AP");

  return c;
}

void NormalizeGraph(TGraphErrors *graph) {
  if (!graph) {
    std::cout << "Error: El grafico es nulo." << std::endl;
    return;
  }

  int nPoints = graph->GetN();
  double sumY = 0;

  // Calcular el valor medio de Y
  for (int i = 0; i < nPoints; i++) {
    double y;
    graph->GetPoint(i, y, y);
    if (std::isnan(y)) {
      std::cout << "El valor es nulo (NaN)\n en" << graph->GetTitle()
                << std::endl;
      std::cout << y << std::endl;
    } else {
      sumY += y;
    }
  }
  double avgY = sumY / nPoints;
  if (avgY == 0) {
    std::cout << graph->GetTitle()
              << "  Error: El promedio de Y es 0, no se puede normalizar."
              << std::endl;
    // std::exit(1);

    return;
  }

  // Normalizar cada punto dividiendo por avgY
  for (int i = 0; i < nPoints; i++) {
    double x, y;
    graph->GetPoint(i, x, y);
    double yErr = graph->GetErrorY(i);
    graph->SetPoint(i, x, y / avgY);
    graph->SetPointError(i, 0, yErr / avgY);
  }
}
