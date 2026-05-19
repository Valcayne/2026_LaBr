# Simple HTCondor submit description file
# Everything with a leading # is a comment
 
executable   = /afs/cern.ch/work/v/valcayne/2026_Sm/MakeCalibrations/MakeEnergyCalibration
arguments    = $(Source)  $(DetectorsCalibrated) $(SourceType) $(DataFolder) $(RunList) $(FolderRootFiles) $(Expfname) $(ExpfnameBackground) $(SourceTypeBakground) $(NumberBinsExpfname) $(EMaxExpfname) $(MCfname) $(outFolder) $(GammaEnergy) $(rebin) $(Percen) $(npRes) $(Res) $(PERRes) $(npCalib) $(Calib) $(PERCalib)
#output       = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).out
output       = Condor/outputs/output_$(Source)_$(DetectorsCalibrated)_$(SourceType).out
error        = Condor/outputs/error_$(Source)_$(DetectorsCalibrated)_$(SourceType).err
#error        = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).err
log          = Condor/outputs/log_$(Source)_$(DetectorsCalibrated)_$(SourceType).err
transfer_output_files   = ""

requirements = (OpSysAndVer =?= "AlmaLinux9")
#requirements = (OpSysAndVer =?= "CentOS7")

+JobFlavour = "tomorrow"
#+JobFlavour = "espresso"
#+JobFlavour = "microcentury"


queue Source,DetectorsCalibrated,SourceType, DataFolder, RunList, FolderRootFiles, Expfname,ExpfnameBackground,  SourceTypeBakground, NumberBinsExpfname, EMaxExpfname,    MCfname, outFolder, GammaEnergy, rebin, Percen, npRes, Res, PERRes, npCalib, Calib, PERCalib from /afs/cern.ch/work/v/valcayne/2026_Sm/MakeCalibrations/Condor/Inputs/ArgumentsForCondor.txt
