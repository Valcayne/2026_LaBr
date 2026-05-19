#include "../GeneralFun/GeneralFunctions.hh"
using namespace std;

void save_plot(const char *filename) {
  TCanvas *c;
  // Abrir el archivo ROOT en modo lectura
  TFile *file = TFile::Open(filename, "READ");
  if (!file || file->IsZombie()) {
    cout << "Error: No se pudo abrir el archivo ROOT " << filename << endl;
    return;
  }

  // Acceder al directorio "Dedicated/C6D6"
  TDirectory *dir = (TDirectory *)file->Get("Dedicated/C6D6");
  if (!dir) {
    cout << "Error: No se encontró el directorio Dedicated/C6D6" << endl;
    file->Close();
    return;
  }

  // Obtener el canvas específico
  c = (TCanvas *)dir->Get("C6D6 0 counts per proton (1)");
  if (!c) {
    cout << "Error: No se encontró el canvas C6D6 0 counts per proton (1)"
         << endl;
    file->Close();
    return;
  }
  c->Draw();
  file->Close();

  // Convertir el nombre del archivo en string y quitar la extensión .root
  string filename_str = filename;
  filename = filename;
  size_t pos = filename_str.find(".root");
  if (pos != string::npos) {
    filename_str = filename_str.substr(0, pos);
  }

  // Guardar la imagen del canvas clonado
  string output_filename = filename_str + "Plot";

  SaveRootEpsPngTxtFunction(c, output_filename.c_str());

  cout << "Plot guardado como: " << output_filename << endl;
}
