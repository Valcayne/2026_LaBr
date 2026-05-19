# Simple HTCondor submit description file
# Everything with a leading # is a comment
 
executable   = /afs/cern.ch/user/v/valcayne/Workspace/2026_Sm/GainMonitoring/CreateCalibFiles01
arguments    = $(InpCalibDir) $(OutCalibDir) $(GainShiftsDir) $(DetName) $(DetID) $(RunDescriptor) $(RefCalibRunNumber) $(RunMin) $(RunMax)
#output       = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).out
output       = Condor/out/output_$(run).out
error        = Condor/out/error_$(run).err
#error        = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).err
log          = Condor/out/log_$(run).err
transfer_output_files   = ""
requirements = (OpSysAndVer =?= "AlmaLinux9")
#requirements = (OpSysAndVer =?= "CentOS7")
#+JobFlavour = "workday"
+JobFlavour = "espresso"
#+JobFlavour = "longlunch"


queue InpCalibDir OutCalibDir GainShiftsDir DetName DetID RunDescriptor RefCalibRunNumber RunMin RunMax from /afs/cern.ch/user/v/valcayne/Workspace/2026_Sm/GainMonitoring/Condor/ArgumentsForCondor.txt
