# Simple HTCondor submit description file
# Everything with a leading # is a comment
 
executable   = /afs/cern.ch/user/v/valcayne/Workspace/2026_Sm/Make2DHistos/DoRecursiveMerge2DHisto
#arguments    = $(run)
#output       = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).out
output       = Condor/outputs/output_recursive.out
error        = Condor/outputs/error_recursive.err
#error        = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).err
log          = Condor/outputs/log_recursive.log
transfer_output_files   = ""
requirements = (OpSysAndVer =?= "AlmaLinux9")
#requirements = (OpSysAndVer =?= "CentOS7")
#+JobFlavour = "workday"
#+JobFlavour = "espresso"
#+JobFlavour = "microcentury"
#+JobFlavour = "longlunch"
+JobFlavour = "nextweek"



queue 
