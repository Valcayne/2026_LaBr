#include <TClass.h>
#include <TFile.h>
#include <TKey.h>
#include <TObject.h>
#include <TTree.h>

#include <iomanip>
#include <iostream>
#include <string>

// Convierte bytes a una cadena legible
std::string formatSize(Long64_t bytes) {
  const char* units[] = {"B", "KB", "MB", "GB", "TB"};
  double size = bytes;
  int unitIndex = 0;
  while (size >= 1024 && unitIndex < 4) {
    size /= 1024;
    ++unitIndex;
  }
  std::ostringstream out;
  out << std::fixed << std::setprecision(2) << size << " " << units[unitIndex];
  return out.str();
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Uso: " << argv[0] << " archivo.root" << std::endl;
    return 1;
  }

  const char* filename = argv[1];
  TFile* file = TFile::Open(filename, "READ");
  if (!file || file->IsZombie()) {
    std::cerr << "No se pudo abrir el archivo ROOT: " << filename << std::endl;
    return 1;
  }

  std::cout << "Contenido de " << filename << ":\n\n";

  TIter next(file->GetListOfKeys());
  TKey* key;
  Long64_t totalSize = 0;

  while ((key = (TKey*)next())) {
    TObject* obj = key->ReadObj();
    Long64_t sizeBytes = 0;

    if (obj->InheritsFrom(TTree::Class())) {
      TTree* tree = (TTree*)obj;
      sizeBytes = tree->GetZipBytes();  // tamaño real en disco (comprimido)
    } else {
      sizeBytes = key->GetNbytes();  // cabecera + buffers pequeños
    }

    totalSize += sizeBytes;

    std::cout << "- " << key->GetName() << " (" << obj->ClassName() << ")"
              << " → Tamaño en disco: " << formatSize(sizeBytes) << std::endl;
  }

  std::cout << "\n📦 Tamaño total estimado de objetos ROOT: " << formatSize(totalSize) << std::endl;

  file->Close();
  return 0;
}
