



Haz lo siguiente (⚠️ esto va a borrar cambios locales, asegúrate de que no necesitas nada):
Perfecto, Víctor . Lo que quieres es descartar tus cambios locales (tanto los modificados como
los no seguidos/untracked) y quedarte exactamente con lo que está en el remoto.
# 1. Descarta todos los cambios locales
git reset --hard
# 2. Elimina los archivos no seguidos que te bloquean
git clean -fd
# 3. Actualiza desde remoto, sobrescribiendo
git fetch origin
git reset --hard origin/main

###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################

To Launch Calibrations
cd ../ApsC6D6/; git pull;cd EnergyCalibration/;doroot  MakeEnergyCalibration12VIC; cd ../../InputsFor_Er_Cu_U/; git pull;doroot MakeEnergyCalibration_2024_Er_Cu_U_L6D6;#
MakeEnergyCalibration_2024_Er_Cu_U_L6D6;


cd ../ApsC6D6/; git pull;cd EnergyCalibration/;doroot  MakeEnergyCalibration12VIC; cd ../../InputsFor_Er_Cu_U/; git pull;doroot MakeEnergyCalibration_2024_Er_Cu_U_L6D6;#
MakeEnergyCalibration_2024_Er_Cu_U_L6D6;


#################################
#
#To put all the calibrations equal using the references calibration
source GeneralFun/GeneralDefinitions.sh

for (( number=$RunMin; number<=$RunMax; number++ )); do
#echo "  cp ${PathCalibrationsInitial} ${PathCalibrations}/Calib_${number}.dat "
 cp ${PathCalibrationsInitial}  ${PathCalibrations}/Calib_${number}.dat
done
more ${PathCalibrations}/Calib_${RunMax}.dat


#################################
## Create all the 2DHistos 
cd Make2DHistos
DoManyMake2DHisto
cd ../

## Calculate the GainShifts
cd GainMonitoring/
DoManyGainCorrecting

##in case you want to check gainshifts


root -l plot01.hh+
plot01("AllRuns", "SILI", 1, 2, 3, 4,true,"/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/GainMonitoring/v02/Plot_SILI");
plot01("Y", "C6D6", 1,2,3,4,true,"/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/GainMonitoring/v02/Plot_C6D6_Y");
plot01("Cs", "C6D6", 1,2,3,4,true,"/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/GainMonitoring/v02/Plot_C6D6_Cs");
plot01("LABR_Cs", "LABR", 1,2,1,2,true,"/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/GainMonitoring/v02/Plot_LABR_Cs");
plot01("LABR_Y", "LABR", 1,2,1,2,true,"/eos/home-v/valcayne/nTOFDataProcessing/2026_Sm/GainMonitoring/v02/Plot_LABR_Y");

cd ../

### Put the calibrations in all the calibrations the same before the correcting the gains shifts
source GeneralFun/GeneralDefinitions.sh

for (( number=$RunMin; number<=$RunMax; number++ )); do
  cp ${PathCalibrationsInitial} ${PathCalibrationsGain}/Calib_${number}.dat
done



## Create the calibration files correcting for each gain shift
cd GainMonitoring/
DoManyCreateCalibFiles
cd ../


## Delete all the 2DHistos Folder2DGainCorrected 
source GeneralFun/GeneralDefinitions.sh
for (( number=$RunMin; number<=$RunMax; number++ )); do
  rm ${Folder2DGainCorrected}/Histos01_${number}.root
done


## Create all the 2DHistos GainCorrecter
cd Make2DHistos
DoManyMake2DHisto GainCorrected


## Create all the 2DHistos GainCorrecter
DoManyMakeMerge2DHisto
cd ../

# Create the monitoring
cd Monitor
condor_submit LaunchMonitor.sh 
cd ../

# Make CompareWithRunType for each run
cd Plots01_Victor
DoManyCompareWithRunType
cd ../

# This program will do every hour DoManyMake2DHisto All. So it will create the 2DHistos for all the runs
cd Make2DHistos
condor_submit Condor/ProgramsLaunch/LaunchRecursive2DHisto.sh 
condor_submit Condor/ProgramsLaunch/LaunchRecursiveMerge.sh 

../


ls -lrth /eos/experiment/ntof/processing/official/done/run12*
