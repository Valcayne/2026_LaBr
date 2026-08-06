#ifndef CALIBRATORVIEWER_HH
#define CALIBRATORVIEWER_HH 1

#include <TGClient.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <RQ_OBJECT.h>
#include <TApplication.h>
#include <TAxis.h>
#include <TROOT.h>
#include <TStyle.h>

#include <fstream>
#include "TACCalibrator.hh"


using namespace std;


class MyMainFrame{
  RQ_OBJECT("MyMainFrame")
    private:
  TGMainFrame *fMain;
  TRootEmbeddedCanvas *fEcanvas;
  TPad* pad[NDETECTORS+1];
  TPad* bigpad;
  TACCalibrator* theTACCalibrator;
  int theShownCr;
  string theROOTfilename;
  string theBasefilename;
  int XFirst,XLast;

public:
  MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~MyMainFrame();

  int MakeTACCalibration(string filename,int NumberFiles);
  int DrawAll();
  int DrawOne(int cr);
  int DrawNext();
  int DrawPrevious();
  int SetCurrentRange();

  int GetBaseFilename();
  int SaveCurrent(int ftype);
  int SaveAll(int ftype);
  void SaveCurrent_root(){SaveCurrent(0);}
  void SaveCurrent_eps(){SaveCurrent(1);}
  void SaveCurrent_gif(){SaveCurrent(2);}
  void SaveAll_eps(){SaveAll(1);}
  void SaveAll_gif(){SaveAll(2);}

  int SaveParameters();

};


#endif
