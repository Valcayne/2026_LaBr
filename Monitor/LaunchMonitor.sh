# Simple HTCondor submit description file
# Everything with a leading # is a  comment
 
executable   = /afs/cern.ch/user/v/valcayne/Workspace/2026_Sm/Monitor/bin/Monitor
arguments    = $(run) 
#output       = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).out
output       = Condor/outputs/output_$(run).out
error        = Condor/outputs/error_$(run).err
#error        = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).err
log          = Condor/outputs/log_$(run).err
transfer_output_files   = ""
requirements = (OpSysAndVer =?= "AlmaLinux9")
#requirements = (OpSysAndVer =?= "CentOS7")
#+JobFlavour = "workday"
#+JobFlavour = "espresso"
+JobFlavour = "longlunch"



queue run from /afs/cern.ch/user/v/valcayne/Workspace/2026_Sm/Monitor/Condor/Arguments.txt

