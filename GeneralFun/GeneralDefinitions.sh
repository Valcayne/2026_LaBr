#!/bin/bash

#Define the location of the files for bash programs


RunMin=125277
RunMax=125400


#EOSPATH="/eos/experiment/ntof/processing/official/done/"
EOSPATH="/eos/home-v/valcayne/nTOFDataProcessing/2026_LaBr/RootFiles/v01/done"


Folder2D="/eos/home-v/valcayne/nTOFDataProcessing/2026_LaBr/2DHistos/v01"
Folder2DGainCorrected="/eos/home-v/valcayne/nTOFDataProcessing/2026_LaBr/2DHistos/v01GainCorrected"
FolderOnLXPLUS="/afs/cern.ch/user/v/valcayne/Workspace/2026_LaBr/"

RunTypeToBeMerged="/eos/home-v/valcayne/CopiaOrdenadorCIEMAT/CmExperimentFolder/2026_LaBr/2026_LaBr/RunLists/RunTypeToBeMerged_v01.txt"
RunTypeTypeFolder="/eos/home-v/valcayne/CopiaOrdenadorCIEMAT/CmExperimentFolder/2026_LaBr/2026_LaBr/RunLists"


PathCalibrationsInitial=/eos/home-v/valcayne/nTOFDataProcessing/2026_LaBr/Calibration/CalibrationRunByRunv01/Calib_2026_LaBr_v03.dat
PathCalibrations=/eos/home-v/valcayne/nTOFDataProcessing/2026_LaBr/Calibration/CalibrationRunByRunv01
PathCalibrationsGain=/eos/home-v/valcayne/nTOFDataProcessing/2026_LaBr/Calibration/CalibrationRunByRunGainCorrectedv01
PathGainMonitoring=/eos/home-v/valcayne/nTOFDataProcessing/2026_LaBr//GainMonitoring/v01

RefRunGainShift_SILI=124096
RefRunGainShift_C6D6_Cs=124153
RefRunGainShift_C6D6_Y=124154
RefRunGainShift_LABR_Cs=124964
RefRunGainShift_LABR_Y=124965
