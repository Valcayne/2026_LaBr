
#include "CalibratorViewer.hh"

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h) {

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  XFirst=0; XLast=0;
  theTACCalibrator=0;
  theShownCr=1;
  // Create a main frame
  fMain = new TGMainFrame(p,w,h);
  // Create canvas widget
  fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,2000,800);
  //-------------------------------------------------
  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->cd();
  fCanvas->SetFillColor(0);
  fCanvas->SetFrameBorderMode(0);
  //-------------------------
  int nXpos=9;
  int NSmallPads=NDETECTORS;
  if (NDETECTORS<=4) {
    nXpos=3;
    NSmallPads=4;
  }
  else if (NDETECTORS>4 && NDETECTORS<=8) {
    nXpos = 5; 
  }
  int nYpos=NSmallPads/(nXpos-1)+1;
  if(NSmallPads%(nXpos-1)!=0){nYpos++;}
  double *Xpos=new double[nXpos];
  double *Ypos=new double[nYpos];

  double maxXpos=(double)nXpos/(double)(nXpos+nYpos);
  for(int i=0;i<nXpos;i++){
    Xpos[i]=(double)i/(double)(nXpos-1)*maxXpos;
  }
  for(int i=0;i<nYpos;i++){
    Ypos[i]=(double)(nYpos-1-i)/(double)(nYpos-1);
  }

  char name[100];
  char title[100];
  int cont = 1;
  double epsilon = 0.0001;
  for (int j = 0; j < nYpos - 1; j++)
  {
    for (int i = 0; i < nXpos - 1; i++)
    {
      if (cont < NSmallPads + 1)
      {
        sprintf(name, "%s_%d", TREENAME, cont);
        sprintf(title, "%s %d", TREENAME, cont);
        pad[cont] = new TPad(name, title, Xpos[i] + epsilon, Ypos[j + 1] + epsilon, Xpos[i + 1] - epsilon, Ypos[j] - epsilon);
        pad[cont]->SetFillColor(0);
        pad[cont]->SetFrameBorderMode(0);
        pad[cont]->SetTickx();
        pad[cont]->SetTicky();
        pad[cont]->Draw();
      }
      cont++;
    }
  }

  bigpad=new TPad("bigpad","bigpad",maxXpos+epsilon,0,1,1);
  bigpad->SetFillColor(0);
  bigpad->SetFrameBorderMode(0);
  bigpad->SetTickx();
  bigpad->SetTicky();

  bigpad->Draw();

  delete [] Xpos;
  delete [] Ypos;

  //-------------------------

  fCanvas->cd();
  fCanvas->Update();
  fCanvas->SaveAs("RootCanvas.root");cout<<"Saving Canvas"<<endl;
  fCanvas->SaveAs("RootCanvas.png");cout<<"Saving Canvas"<<endl;

  //-------------------------------------------------
  fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,
                                              10,10,10,1));
  // Create a horizontal frame widget with buttons
  TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,800,40);

  //Save current - root:
  TGTextButton *savecurrent_root = new TGTextButton(hframe,"SaveCurrent-root");
  savecurrent_root->Connect("Clicked()","MyMainFrame",this,"SaveCurrent_root()");
  hframe->AddFrame(savecurrent_root, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
  //Save current - eps:
  TGTextButton *savecurrent_eps = new TGTextButton(hframe,"SaveCurrent-eps");
  savecurrent_eps->Connect("Clicked()","MyMainFrame",this,"SaveCurrent_eps()");
  hframe->AddFrame(savecurrent_eps, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
  //Save current - gif:
  TGTextButton *savecurrent_gif = new TGTextButton(hframe,"SaveCurrent-gif");
  savecurrent_gif->Connect("Clicked()","MyMainFrame",this,"SaveCurrent_gif()");
  hframe->AddFrame(savecurrent_gif, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
  //Save all - eps:
  TGTextButton *saveall_eps = new TGTextButton(hframe,"SaveAll-eps");
  saveall_eps->Connect("Clicked()","MyMainFrame",this,"SaveAll_eps()");
  hframe->AddFrame(saveall_eps, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
  //Save all - gif:
  TGTextButton *saveall_gif = new TGTextButton(hframe,"SaveAll-gif");
  saveall_gif->Connect("Clicked()","MyMainFrame",this,"SaveAll_gif()");
  hframe->AddFrame(saveall_gif, new TGLayoutHints(kLHintsCenterX,5,20,3,4));


  //Previous:
  TGTextButton *drawprevious = new TGTextButton(hframe,"&Previous");
  drawprevious->Connect("Clicked()","MyMainFrame",this,"DrawPrevious()");
  hframe->AddFrame(drawprevious, new TGLayoutHints(kLHintsCenterX,20,5,3,4));
  //Next:
  TGTextButton *drawnext = new TGTextButton(hframe,"&Next");
  drawnext->Connect("Clicked()","MyMainFrame",this,"DrawNext()");
  hframe->AddFrame(drawnext, new TGLayoutHints(kLHintsCenterX,5,20,3,4));

  //SetCurrentRange:
  TGTextButton *setcurrentrange = new TGTextButton(hframe,"&SetCurrentRange");
  setcurrentrange->Connect("Clicked()","MyMainFrame",this,"SetCurrentRange()");
  hframe->AddFrame(setcurrentrange, new TGLayoutHints(kLHintsCenterX,20,20,3,4));

  //SaveParameters:
  TGTextButton *saveparameters = new TGTextButton(hframe,"Sa&veParameters");
  saveparameters->Connect("Clicked()","MyMainFrame",this,"SaveParameters()");
  hframe->AddFrame(saveparameters, new TGLayoutHints(kLHintsCenterX,20,20,3,4));


  //Exit:
  TGTextButton *exit = new TGTextButton(hframe,"&Exit","gApplication->Terminate(0)");
  hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,20,5,3,4));

  fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));



  // Set a name to the main frame
  fMain->SetWindowName("TACCalibrator");
  // Map all subwindows of main frame
  fMain->MapSubwindows();
  // Initialize the layout algorithm
  fMain->Resize(fMain->GetDefaultSize());
  // Map main frame
  fMain->MapWindow();
}

MyMainFrame::~MyMainFrame() {
  // Clean up used widgets: frames, buttons, layouthints
  fMain->Cleanup();
  delete fMain;
  if(theTACCalibrator){delete theTACCalibrator;}
}

int MyMainFrame::MakeTACCalibration(string filename, int NumberFiles)
{
  char cutlistname[1000];
  int CutFileNumber = CUTFILENAME;
  int check = 0;
  theROOTfilename = filename;
  GetBaseFilename();
  theTACCalibrator = new TACCalibrator();
  
  if (TREENAME == "BAF2")
  {
    sprintf(cutlistname, "CutList%02d.txt", CutFileNumber);
    theTACCalibrator->FillRatioVal(cutlistname);
  }

  if (NumberFiles == 0)
  {
    check = theTACCalibrator->FillAndCreateHistograms(filename);
  }

  if (!NumberFiles == 0)
  {
    char filenameReal[1000];
    int RunNumber = atoi(filename.c_str());
    cout << "Reading run " << RunNumber << endl;
    sprintf(filenameReal, "%s/run%d.root", ROOTFILEFOLDER.c_str(), RunNumber);

    check = theTACCalibrator->FillAndCreateHistograms(filenameReal);

    for (int i = 1; i < NumberFiles; i++)
    {
      cout << "Reading run " << i + RunNumber << endl;
      sprintf(filenameReal, "%s/run%d.root", ROOTFILEFOLDER.c_str(), i + RunNumber);
      check = theTACCalibrator->FillHistograms(filenameReal);
    }
  }

  if (check != 0)
  {
    cout<<" **** Error filling histograms ****"<<endl;
    return -1;
  }
  theTACCalibrator->TakeAllBackgrounds();
  theTACCalibrator->FindAllPeaks();

  return 0;
}

int MyMainFrame::DrawAll(){

  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->cd();

  for(int cr=1;cr<=NDETECTORS;cr++){
    pad[cr]->cd();
    if(theTACCalibrator->GetHhisto(cr)){
      theTACCalibrator->GetHhisto(cr)->Draw("histo");
    }
    if(theTACCalibrator->GetBhisto(cr)){
      theTACCalibrator->GetBhisto(cr)->Draw("histo same");
    }
    if(theTACCalibrator->GetDhisto(cr)){
      theTACCalibrator->GetDhisto(cr)->Draw("histo same");
    }
    int nfits=theTACCalibrator->GetNFitFun(cr);
    for(int i=0;i<nfits;i++){
      theTACCalibrator->GetFitFun(cr,i)->Draw("L same");
      theTACCalibrator->GetFitFun2(cr,i)->Draw("L same");
    }
  }

  fCanvas->cd();
  fCanvas->Update();
  return 0;
}


int MyMainFrame::DrawOne(int cr){

  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->cd();

  cout << "Plotting crystal " << cr << endl; 

  bigpad->cd();
  bigpad->SetLeftMargin(0.13); 
  bigpad->SetRightMargin(0.12);
  bigpad->SetBottomMargin(0.12);

  if(theTACCalibrator->GetHhisto(cr)){
    theTACCalibrator->GetHhisto(cr)->SetTitle(Form("Crystal %d",cr));
    theTACCalibrator->GetHhisto(cr)->GetXaxis()->SetTitle("Area (ADC channels)");
    theTACCalibrator->GetHhisto(cr)->GetXaxis()->SetNdivisions(507);
    theTACCalibrator->GetHhisto(cr)->GetXaxis()->SetLabelSize(0.05);
    theTACCalibrator->GetHhisto(cr)->GetXaxis()->SetTitleSize(0.05);

    theTACCalibrator->GetHhisto(cr)->GetYaxis()->SetTitle("a.u.");
    theTACCalibrator->GetHhisto(cr)->GetYaxis()->SetMaxDigits(3); 
    theTACCalibrator->GetHhisto(cr)->GetYaxis()->SetLabelSize(0.05);
    theTACCalibrator->GetHhisto(cr)->GetYaxis()->SetTitleSize(0.05);
    theTACCalibrator->GetHhisto(cr)->GetYaxis()->SetTitleOffset(1.4);

    theTACCalibrator->GetHhisto(cr)->Draw("histo");
  }
  if(theTACCalibrator->GetBhisto(cr)){
    theTACCalibrator->GetBhisto(cr)->Draw("histo same");
  }
  if(theTACCalibrator->GetDhisto(cr)){
    theTACCalibrator->GetDhisto(cr)->Draw("histo same");
  }
  int nfits=theTACCalibrator->GetNFitFun(cr);
  for(int i=0;i<nfits;i++){
    if(theTACCalibrator->GetFitFun(cr,i)){
      // theTACCalibrator->GetFitFun(cr,i)->Draw("L same");
      theTACCalibrator->GetFitFun2(cr,i)->Draw("L same");
    }
  }

  TLegend *legend = new TLegend(0.62,0.66,0.84,0.84,"");
  legend->AddEntry(theTACCalibrator->GetHhisto(cr), "Exp.","l");
  legend->AddEntry(theTACCalibrator->GetFitFun2(cr,0),"Fit","l");

  legend->SetMargin(0.25); 
  legend->SetBorderSize(0);
	legend->SetFillColor(0);
	legend->SetFillStyle(0);
	legend->Draw();

  fCanvas->cd();
  fCanvas->Update();
  return 0;
}

int MyMainFrame::DrawNext(){
  theShownCr++;
  if(theShownCr>NDETECTORS){
    theShownCr=1;
  }
  DrawOne(theShownCr);
  return 0;
}

int MyMainFrame::DrawPrevious(){
  theShownCr--;
  if(theShownCr<1){
    theShownCr=NDETECTORS;
  }
  DrawOne(theShownCr);
  return 0;
}

int MyMainFrame::SetCurrentRange(){

  if(theTACCalibrator->GetHhisto(theShownCr)){
    XFirst=theTACCalibrator->GetHhisto(theShownCr)->GetXaxis()->GetFirst();
    XLast=theTACCalibrator->GetHhisto(theShownCr)->GetXaxis()->GetLast();
    cout << "New range set to [" << theTACCalibrator->GetHhisto(theShownCr)->GetXaxis()->GetBinLowEdge(XFirst) << ", " << theTACCalibrator->GetHhisto(theShownCr)->GetXaxis()->GetBinUpEdge(XLast) << "]" << endl;
  }

  for(int i=1;i<=NDETECTORS;i++){
    if(theTACCalibrator->GetHhisto(i)){
      theTACCalibrator->GetHhisto(i)->GetXaxis()->SetRange(XFirst,XLast);
    }
  }

  DrawAll();

  return 0;
}


int MyMainFrame::GetBaseFilename(){

  char fname[100];
  int cont=0;
  for(unsigned int i=0;i<theROOTfilename.size();i++){
    fname[cont]=theROOTfilename.c_str()[i];
    if(fname[cont]=='/'){cont=0;}
    else{cont++;}
  }
  int pointpos=cont-1;
  for(int i=0;i<cont;i++){
    if(fname[i]=='.'){pointpos=i; fname[pointpos]='\0';}
  }

  //fname[pointpos]='\0';	// AdriEdit: Lo meto dentro del if anterior
  theBasefilename=string(fname);
  return 0;
}

int MyMainFrame::SaveCurrent(int ftype){

  string final;
  if(ftype==0){// root
    final=string(".root");
  }
  else if(ftype==1){//eps
    final=string(".eps");
  }
  else{//gif
    final=string(".gif");
  }
  char base[100];
  sprintf(base,"./graphs/BaF2_%.2d_",theShownCr);
  string savefn=string(base)+theBasefilename+final;
  cout<<"Creating "<<savefn<<" ..."<<endl;

  system("mkdir -p graphs");

  bigpad->SaveAs(savefn.c_str());

  return 0;
}


int MyMainFrame::SaveAll(int ftype){

  for(int i=0;i<=NDETECTORS;i++){
    DrawNext();
    SaveCurrent(ftype);
  }
  return 0;
}

/*
int MyMainFrame::SaveAll(int ftype){


  string final;
  if(ftype==0){// ps
    final=string(".ps");
  }
  else if(ftype==1){//eps
    final=string(".eps");
  }
  else{//gif
    final=string(".gif");
  }

  system("mkdir -p graphs");
  char base[100];
  string savefn;
  for(int i=1;i<=NDETECTORS;i++){
    sprintf(base,"./graphs/BaF2_%.2d_",i);
    savefn=string(base)+theBasefilename+final;
    cout<<"Creating "<<savefn<<" ..."<<endl;
    pad[i]->SaveAs(savefn.c_str());
  }

  TCanvas *fCanvas = fEcanvas->GetCanvas();
  savefn=string("./graphs/BaF2_ALL_")+theBasefilename+final;
  cout<<"Creating "<<savefn<<" ..."<<endl;
  fCanvas->SaveAs(savefn.c_str());


  return 0;
}
*/


int MyMainFrame::SaveParameters(){

  system("mkdir -p results");
  string savefn;
  savefn=Form("./results/%s_%s.dat", TREENAME, theBasefilename.c_str());
  cout<<"Creating "<<savefn<<" ..."<<endl;
  theTACCalibrator->SaveValues(savefn);

  return 0;
}





//*********************************************************

int main(int argc, char **argv) {

  if(argc!=3){
    cout<<endl<<"  **** Input has to be like: TACCalibrator <rootfile> NumberFiles****"<<endl;
    return -1;
  }

  string filename=string(argv[1]);
  int NumberFiles=atoi(argv[2]);

  int check=0;
  TApplication theApp("App",&argc,argv);
  MyMainFrame* theMainFrame=new MyMainFrame(gClient->GetRoot(),200,200);
  cout<<" Input file: "<<filename<<endl;
  check=theMainFrame->MakeTACCalibration(filename,NumberFiles);
  if(check!=0){
    cout<<" **** Error doing TACCalibration ****"<<endl;
    return -1;
  }
  theMainFrame->DrawAll();
  theMainFrame->DrawOne(1);

  theApp.Run();
  return 0;
}

