# Simple HTCondor submit description file
# Everything with a leading # is a comment
 
executable   = /afs/cern.ch/user/v/valcayne/Workspace/2026_Sm/MakeCalibrations/TEST
#output       = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).out
output       = Condor/outputs/output_TEST.out
error        = Condor/outputs/error_TEST.err
#error        = outputs_condor/DTAnalyzer01_$(EXTRRun)_$(RAWRun)_det$(DetN)_$(Quant)_$(nEn)_$(nE1).err
log          = Condor/outputs/log_TEST.err
requirements = (OpSysAndVer =?= "AlmaLinux9")
+JobFlavour = "longlunch"
transfer_output_files   = ""
queue 
