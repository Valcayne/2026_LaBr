// Incluimos las cabeceras necesarias de ROOT
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TObject.h>

#include <iostream>
// Ejemplo usando TH1D y GetBinContent (en lugar de Eval)

#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TH1D.h>

#include <iostream>
#include <vector>

double interpolarTH1D(TH1D* hist, double x) {
  // Obtener el número de bins y los límites del eje X
  int nBins = hist->GetNbinsX();
  double x_min = hist->GetXaxis()->GetXmin();
  double x_max = hist->GetXaxis()->GetXmax();

  // Si x está fuera del rango del histograma, devolver el valor en el borde
  if (x < x_min) return hist->GetBinContent(1);
  if (x > x_max) return hist->GetBinContent(nBins);

  // Encontrar el bin correspondiente a x
  int bin = hist->FindBin(x);

  // Obtener los límites de los bins adyacentes
  double x1 = hist->GetXaxis()->GetBinLowEdge(bin);
  double x2 = hist->GetXaxis()->GetBinUpEdge(bin);

  // Obtener los valores de los bins adyacentes
  double y1 = hist->GetBinContent(bin);
  double y2 = hist->GetBinContent(bin + 1);

  // Realizar la interpolación lineal entre los dos bins
  double interpolado = y1 + (x - x1) * (y2 - y1) / (x2 - x1);

  return interpolado;
}

void multiplicarHistogramasInterpolados(const char* archivo1,
                                        const char* archivo2,
                                        const char* histograma1,
                                        const char* histograma2) {
  // Abrir los dos archivos ROOT
  TFile* file1 = TFile::Open(archivo1);
  TFile* file2 = TFile::Open(archivo2);

  // Verificar que los archivos se abrieron correctamente
  if (!file1 || !file2) {
    std::cerr << "Error al abrir los archivos ROOT." << std::endl;
    return;
  }

  // Obtener los histogramas de cada archivo
  TH1D* hist1 = (TH1D*)file1->Get(histograma1);
  TH1D* hist2 = (TH1D*)file2->Get(histograma2);

  // Verificar que los histogramas existan
  if (!hist1 || !hist2) {
    std::cerr << "Error: Los histogramas no se han encontrado." << std::endl;
    file1->ls();
    file2->ls();

    return;
  }

  // Crear un nuevo histograma para el resultado de la multiplicación
  TH1D* hist_multiplicado = (TH1D*)hist1->Clone();
  // Interpolar los valores de cada histograma en el rango común
  for (int bin = 1; bin <= hist_multiplicado->GetNbinsX(); bin++) {
    double x = hist_multiplicado->GetBinCenter(
        bin);  // Obtener el centro de cada bin en el rango común

    double valor1 = hist1->GetBinContent(
        bin);  // Obtener el contenido del bin en el primer histograma
    double valor2 =
        interpolarTH1D(hist2, x);  // Interpolar en el segundo histograma

    // Multiplicar los valores y asignar al nuevo histograma
    hist_multiplicado->SetBinContent(bin, valor1 * valor2);
  }

  // Crear canvas para dibujar los histogramas
  TCanvas* canvas = new TCanvas("canvas", "Histograma Multiplicado", 800, 600);
  hist1->SetLineColor(kRed);                // Color del primer histograma
  hist2->SetLineColor(kBlue);               // Color del segundo histograma
  hist_multiplicado->SetLineColor(kGreen);  // Color del histograma multiplicado

  // Dibujar los histogramas
  hist1->Draw();
  hist2->Draw("SAME");  // Dibujar sobre el mismo canvas
  hist_multiplicado->Draw("SAME");

  // Guardar el canvas en un archivo
  canvas->SaveAs("resultado_histogramas_interpolados_2026.png");
}
