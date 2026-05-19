#!/bin/bash

#Define the location of the files for bash programs


RunMin=124062
#RunMin=124300
#RunMin=124400
#RunMin=124600
RunMin=124730
#RunMin=125000
RunMax=125200
#RunMax=125500


EOSPATH="/eos/experiment/ntof/processing/official/done/"
#EOSPATH="/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/RootFiles/v01/done"


Folder2D="/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/2DHistos/v02"
Folder2DGainCorrected="/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/2DHistos/v02GainCorrected"
FolderOnLXPLUS="/afs/cern.ch/user/v/valcayne/Workspace/2026_Sm/"

RunTypeToBeMerged="/eos/home-v/valcayne/CopiaOrdenadorCIEMAT/CmExperimentFolder/2026_Sm/2026_Sm/RunLists/RunTypeToBeMerged_v01.txt"
RunTypeTypeFolder="/eos/home-v/valcayne/CopiaOrdenadorCIEMAT/CmExperimentFolder/2026_Sm/2026_Sm/RunLists"


PathCalibrationsInitial=/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Calibration/CalibrationRunByRunv02/Calib_2026_Sm_v02.dat
PathCalibrations=/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Calibration/CalibrationRunByRunv02
PathCalibrationsGain=/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/Calibration/CalibrationRunByRunGainCorrectedv02
PathGainMonitoring=/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm//GainMonitoring/v02

RefRunGainShift_SILI=124096
RefRunGainShift_C6D6_Cs=124153
RefRunGainShift_C6D6_Y=124154
RefRunGainShift_LABR_Cs=124964
RefRunGainShift_LABR_Y=124965
