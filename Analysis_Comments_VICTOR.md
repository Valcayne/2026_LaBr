
# Analysis of the Sm in  2026
The idea of this document is to try to store all the information of the analysis in case, I have to repeat it and to understand it.

To convert to pdf:  Open the Markdown file; Press F1 or Ctrl+Shift+P ;Type export and select below 

## TABLE OF CONTENTS

- [Calibrations](#calibrations)
- [AverageSignal](#averagesignal)
- [Preliminary Results ](#preliminary-results)
- [Gain Monitor ](#gain-monitor)
- [BIF calculations ](#bif-calculations)
- [Flux](#flux)
- [Er-164](#er-164)
- [Lead](#lead)
- [SmNat 5um ](#smnat-5um)
- [Sm149 Thick ](#sm149-thick)



## AverageSignal
Average signals they look correct


<img src="SignalAnalizerV01/AverageSignals/CompareSignals_Sm_124063_v01.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/AverageSignals/CompareSignals_Sm_124063_v02.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/AverageSignals/CompareSignals_Sm_124063_v03.png" alt="drawing" width="400"/>


If we compare with the values from 2025 the signals are similar. However there is a considerable improvement in detector 1


<img src="SignalAnalizerV01/AverageSignals/Compare_Marex_Sm_Det1_v01.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/AverageSignals/Compare_Marex_Sm_Det2_v01.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/AverageSignals/Compare_Marex_Sm_Det3_v01.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/AverageSignals/Compare_Marex_Sm_Det4_v01.png" alt="drawing" width="400"1>2

After the change of the voltage we did I calculate the signals again, there are not considerable differences


<img src="SignalAnalizerV01/Compare_Sm_124063_124122_Det1_2_v01.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/Compare_Sm_124063_124122_Det1_2_v02.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/Compare_Sm_124063_124122_Det3_4_v01.png" alt="drawing" width="400"/>
<img src="SignalAnalizerV01/Compare_Sm_124063_124122_Det3_4_v02.png" alt="drawing" width="400"/>


I have check the dead time and 30 ns seem reasonable

## [21/04/2026,Adrian] Baseline oscillation in Det 1 📉
Baseline oscillation increased in Det C6D6 1, starting at run 124724. Seems to be related with the connection of LaBr3 detectors to the DAQ of EAR1 (Pb measurement in NEL). 

<img src="RunLists/graphs/BLOsc-RunSm-124829_02zoom.png" alt="drawing" width="800"/>

Some observations: 
- C6D6 1 already had some oscillations on the baseline but now it is clearly worse (stronger).
- SignalAnalyzer inspected: the oscillations create fake signals fitted by the routine with maximum amplitudes about 150 ADC channels (~65 keV): 
    <img src="RunLists/graphs/PSA_C6D6-1_124846-1-s1_1-1.png" alt="drawing" width="800"/>
- The second rebound seem to be affected by this change, and sometimes the rebound is detected as a fake signal using the previous average pulse shapes (confirmed by Victor by extracting a new average pulse shape). 
- The other three detectors seem to be unaffected.
- The increased oscillation does not seem to get worse since it began in run 124724. 
- Inspecting the Edep, comparing before (Cs_8, Cs_11) and after (Cs_12) the connection of LaBr3 to DAQ, there is no visible effect on the shape of the Cs-137 spectrum: 

    <img src="RunLists/graphs/C6D6_Edep_Cs_8_Det1_PType3_Cs_11_Cs_12.png" alt="drawing" width="400"/>
    <img src="RunLists/graphs/C6D6_Edep_Cs_8_Det1_PType3_Cs_11_Cs_12-zoom01.png" alt="drawing" width="400"/> 

- **Conclusion**: the increased oscillations of baseline seem small enough to have a significant impact on the data analysis, and should not imply any problem. 
- **Action**: we will continue like this since the oscillation appears to be stable during the runs. 

## [21/04/2026,Adrian] Cs_9 issue! 🔍
- There is a bump in the Edep spectrum of Cs_9 measurement at around 1.7 MeV, visible in all detectors. 
- It seems that an Y-88 source was also in the experimental area and affected the measurement. 
- **Action**: I remove this run for the `Cs` run type in the RunList. 

<img src="RunLists/graphs/C6D6_Edep_Cs_9_Det1_PType3_Cs_11_Cs_12.png" alt="drawing" width="800"/>


After all the work from Adrian we decided to also observe if there are any change in the average signal of the detectors.

For detector 1 we observe a change in the average signal. The change is associated with the installation of the LaBr in Run 124724

<img src="SignalAnalizerV01/2026_Sm_Signals_Det1_v01.png" alt="drawing" width="800"/>
<img src="SignalAnalizerV01/2026_Sm_Signals_Det1_v02.png" alt="drawing" width="800"/>


For detector 2 3 4 there are no differences.


<img src="SignalAnalizerV01/2026_Sm_Signals_Det2_v01.png" alt="drawing" width="800"/>
<img src="SignalAnalizerV01/2026_Sm_Signals_Det3_v01.png" alt="drawing" width="800"/>
<img src="SignalAnalizerV01/2026_Sm_Signals_Det4_v01.png" alt="drawing" width="800"/>

After all of this we make DeltaTOF plots to see the effect.

Au_1 is before 124724 and Au_2 and Au_3 are after
Sb121, Mo100, Sm149 are before 124724 and Sm152 and Sm147 are after
Y_11 is before and Y_12 is after.

<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Au13_Det1_v01.png" alt="drawing" width="800"/>
<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Various_Det1_v01.png" alt="drawing" width="800"/>
<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Y_Det1_v01.png" alt="drawing" width="800"/>

As can be seen in the figure for detector 1 there are clear effects. The peak that appears at 250 ns is clearly due to the change of the size of the rebound.
The effect at 500 ns it may be related to the size of the prepulse window that is at 512ns.

There are not effects in the rest of detectors.

<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Au13_Det2_3_4_v01.png.png" alt="drawing" width="800"/>
<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Various_Det2_v01.png" alt="drawing" width="800"/>
<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Y_Det2_v01.png" alt="drawing" width="800"/>


Due to the issue affecting Detector 1 after run 124724, all subsequent runs have been reprocessed using the average pulse shape Sig_C6D6_1_124805_v01.txt.

In addition, prior to this, the DeltaTOF was calculated by applying a signal threshold of 30 keV. As a result, some noise was incorrectly identified as signal, producing the step observed at 500 ns. After run 124724, baseline oscillations increased the noise level, making this step more pronounced.

The signal condition has now been updated to a threshold of 100 keV. With this improved criterion, the new plots no longer show rebounds or steps around 500 ns.
<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Au_Det1_AfterPulseShape124805_v01.png" alt="drawing" width="800"/>
<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Various_Det1_AfterPulseShape124805_v01.png" alt="drawing" width="800"/>
<img src="Plots01_Victor/ResultsPlot/DeltaTOF/Y_Det1_AfterPulseShape124805_v01.png" alt="drawing" width="800"/>


## Calibrations

Version v02 with Y_02, etc ...

The second degree calibration values are:

1 0.019924  0.000305497 -3.43203e-10
2 0.0199209  0.000313759 -6.25235e-10
3 0.0199249  0.000284846 -9.71497e-11
4 0.0199267  0.000270444 -2.41053e-11

The second degree + pol 1 calibration values are:


1 0.0125886  0.000320205 -2.48728e-09 4784.69 0.0695305 0.000296403  0  
2 0.0113683  0.000327125 -2.54539e-09 5626.85 0.091959 0.00029848  0  
3 0.0197883  0.000297224 -2.14551e-09 3725.64 0.0495689 0.000281237  0 
4 0.0198836  0.000281696 -1.77198e-09 3698.25 0.044119 0.00026859  0  


<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/EnergyFitDet1.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/EnergyFitDet2.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/EnergyFitDet3.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/EnergyFitDet4.png" alt="drawing" width="400"/>

<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/ResolFitDet1.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/ResolFitDet2.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/ResolFitDet3.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/Calibration/OutputMakeEnergyCalibration_v02/ResolFitDet4.png" alt="drawing" width="400"/>



Det1

<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_1_Ba.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_1_Cs.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_1_Y.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_1_AmBe.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_1_CmC.png" alt="drawing" width="400"/>

Det2

<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_2_Ba.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_2_Cs.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_2_Y.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_2_AmBe.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_2_CmC.png" alt="drawing" width="400"/>

Det3

<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_3_Ba.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_3_Cs.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_3_Y.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_3_AmBe.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_3_CmC.png" alt="drawing" width="400"/>

Det4

<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_4_Ba.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_4_Cs.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_4_Y.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_4_AmBe.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/CheckCalibrations/CheckCalibrations_4_CmC.png" alt="drawing" width="400"/>




With this calibration the Au cascade seems to be correct

<img src="Plots01_Victor/ResultsPlot/Edep_Au_Cascades_v01.png" alt="drawing" width="400"/>

## Preliminary Results
Compare Empty 2024 with 2026


<img src="Plots01_Victor/ResultsPlot/CompareEmpty_2024_2026.png" alt="drawing" width="400"/>



Compare Au 20 mm with JEFF-3.3

<img src="Plots01_Victor/ResultsPlot/En_Au_Yield_v01.png" alt="drawing" width="400"/>


Compare C for dedicated and parasitic with different thresholds

As always it seems that there are some low energy counts from Carbon in the KeV region that are different for primary than for parasitic this problem is reduced when you increase the threshold to 0.3 MeV.

<img src="Plots01_Victor/ResultsPlot/En_C_Compare_1_2_v01.png" alt="drawing" width="400"/>

<img src="Plots01_Victor/ResultsPlot/En_C_Compare_1_2_v02.png" alt="drawing" width="400"/>



Compare the Au of 45 with the one of 20

<img src="Plots01_Victor/ResultsPlot/Au45 and Au20_v01.png" alt="drawing" width="400"/>


## Gain Monitor
Compare Empty 2024 with 2026

<img src="DatosEnDiscoDuro/GainMonitoring/v02/Plot_SILI.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/GainMonitoring/v02/Plot_SILI_ShortRange_v01.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/GainMonitoring/v02/Plot_C6D6_Y.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/GainMonitoring/v02/Plot_C6D6_Cs.png" alt="drawing" width="400"/>


Gain Shifts!


Det1
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/v01C6D6_Edep_Y_1_Det1_PType3_Y_2.png" alt="drawing" width="400"/>

Det2
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/v01C6D6_Edep_Y_1_Det2_PType3_Y_2.png" alt="drawing" width="400"/>

Det3
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/v01C6D6_Edep_Y_1_Det3_PType3_Y_2.png" alt="drawing" width="400"/>

Det4
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/v01C6D6_Edep_Y_1_Det4_PType3_Y_2.png" alt="drawing" width="400"/>


## BIF calculations

26/03 Calculo para Er164
Centered-> Integrate("EAR1_FLUKA43.root",0.65,0.18,-0.0)-> 0.3084 ->0 %

1mm-> Integrate("EAR1_FLUKA43.root",0.65,0.28,-0.0)-> 0.3067->0.5 %

2mm-> Integrate("EAR1_FLUKA43.root",0.65,0.28,-0.0)->0.29931172 ->3.0 %

<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/BIF_13mm_EAR1_FLUKA43.png" alt="drawing" width="400"/>

They place a misaligned samples that is closed to detectors 2 and 3. The misaligment of the sample is of the order of 1-1.5 mm.


Det0

<img src="Plots01_Victor/ResultsPlot/Au_Mis/Det0_v01.png" alt="drawing" width="400"/>

Det1

<img src="Plots01_Victor/ResultsPlot/Au_Mis/Det1_v01.png" alt="drawing" width="400"/>

Det2

<img src="Plots01_Victor/ResultsPlot/Au_Mis/Det2_v01.png" alt="drawing" width="400"/>

Det3

<img src="Plots01_Victor/ResultsPlot/Au_Mis/Det3_v01.png" alt="drawing" width="400"/>

Det4

<img src="Plots01_Victor/ResultsPlot/Au_Mis/Det4_v01.png" alt="drawing" width="400"/>


As a resume as expected detectos 1 and 4 counts 2% less whereas detectore 2 and 3 count the same. If we do the average of the 4 detectors the diference is of 1%.


If we compare the efficiency between detectors

<img src="Plots01_Victor//ResultsPlot/Au_EffDet.png" alt="drawing" width="400"/>



## Flux


The evaluated flux is normally used in tha n_TOf measurements, however due to the change in the concentration of boron in water, it can change from one year to other.

The evaluated flux used is:

/eos/experiment/ntof/2021_Commissioning/flux/EAR1/evalFlux_prelim.root 

https://indico.cern.ch/event/1403789/contributions/5967927/attachments/2868601/5021738/20240603_CM_Commissioning.pdf

**Year 2026**
The cuts to determine the flux in Edep in the sili detectors are 16e3 to 26e3.



<img src="Plots01_Victor/ResultsPlot/Flux/Edep_AllRuns_NoFilters_Until_124680.png" alt="drawing" width="200"/>
<img src="Plots01_Victor/ResultsPlot/Flux/Edep_VariousRanges_Until124680.png" alt="drawing" width="200"/>

The results obtained with the 4 detectors are compared in the following picture. In this picture the 4 detectors are normalized between 10 and 100 eV. The differences observed are of the order of 2%  below 0.05 eV. The explanation of this can be the fact that at this energy the neutron beam falls due to the gravity. Therefore the point of intersection changes and also the geometric efficiency.

<img src="Plots01_Victor/ResultsPlot/Flux/En_Compare_Det_VariousRanges_Until124680.png" alt="drawing" width="200"/>



If we compare parasitic an dedicated they are almost compatible

<img src="Plots01_Victor/ResultsPlot/Flux/En_Compare_Pulses_VariousRanges_Until124680.png" alt="drawing" width="200"/>


To determine the Flux, the CR have been divided by the Cs of Li-6 and by the Simon Eff provided by Simone. Then this Flux have been divided by the evaluated flux (evalFlux_prelim.root). Then the shape have been normalized to be 10 at 100 eV. 

<img src="Plots01_Victor/ResultsPlot/Flux/En_Until124680.png" alt="drawing" width="200"/>
<img src="Plots01_Victor/ResultsPlot/Flux/Flux_2026_AllRuns_NoFilters_Until124680.png" alt="drawing" width="200"/>

After calculation the flux I correct for the BIF change with the transport code.

<img src="Flux/BIF_20mm_13mm_v02.png" alt="drawing" width="200"/>


Therefore the final flux is in the Flux_23_24_26_v01.root 

And the names are 
 Flux_26_AllRuns_NoFilters_Until124680_13mm
 Flux_26_AllRuns_NoFilters_Until124680_20mm
 Flux_26_AllRuns_NoFilters_Until124680

I compare the flux shape in 23,24,26 normalized to the range 10 to 100 eV we see how there are less thermal neutrons every year. 

<img src="Flux/Compare_Thermal_23_24_26.png" alt="drawing" width="200"/>


We also observed that the flux is changing as function of the time during the capture campaign


<img src="Plots01_Victor/ResultsPlot/Flux/CompareFluxes_v01.png" alt="drawing" width="200"/>
<img src="Plots01_Victor/ResultsPlot/Flux/Flux_SiMON_2026_v01.png" alt="drawing" width="200"/>

<img src="Plots01_Victor/ResultsPlot/Flux/Flux_SiMON_2026_v02.png" alt="drawing" width="200"/>


## Er 164

# Er164 thick sample

plot08("EAR1_4L6D6",100000,1e-3,1e7,217,68,{164,162,166,167,168,170},{0.582,0.1245,0.2525,0.0345,0.006,0.005},false,true,1.5e18,0.65,false,"resultsEr/Er164/Er164_217mg_NoRF_v01")

| Isoflex sample     | -|
|-----------|-----------|
|Er-162  | 12.45% | 
|Er-164  | 58.20% | 
|Er-166  | 25.25% | 
|Er-167  | 3.45% | 
|Er-168  | 0.60% | 
|Er-170  | 0.05% | 

<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thick_v06.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thick_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thick_v02.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thick_v03.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thick_v04.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thick_v05.png" alt="drawing" width="400"/>



| Ulli sample     | -|
|-----------|-----------|
|Er-164  | 73.6% | 
|Er-166  | 15% | 
|Er-167  | 5.5% | 
|Er-168  | 4.4% | 
|Er-170  | 1.5% | 

  plot2D({"En_WF"}, {"Er164_Thin"}, {0}, {0.15}, {9.99}, {1}, "CP",10,1,1,1)
We normalize to between 7 and 8.5 eV
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v02.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v03.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v04.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v05.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v06.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v07.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v08.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v09.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Er164/Er_164_Thin_v10.png" alt="drawing" width="400"/>

## Lead

Las secciones eficaces de los distintos isotopos no son muy diferentes.

<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/Lead_CS.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/Lead_v02.png" alt="drawing" width="400"/>

No estoy seguro de los enriqueciemientos de las muestras pero creo que son estos:

Pb208: 88.110(63)% 208 Pb, 10.988(64)% 206 Pb, 0.8943(84)% 207 Pb and 0.00758(45)% 204 Pb. 

Pb206: 88.53% Pb206, 8.5% Pb207, 2.9% Pb208.

Pbnat: 52.4% 208 Pb, 24.1% 206 Pb, 22.1% 207 Pb and 1.4% 204 Pb.


En la siguiente figura se observa el número de cuentas por pulso, escalando los histogramas a un grosor de 5 mm.

<img src="Plots01_Victor/ResultsPlot/Pb/Pb_ScaledByMass_v01.png" alt="drawing" width="400"/>

Se observan diferencias pero no son muy concluyentes

Si comparamos los pulsos primarios  y secundarios. Se observan más cuentas en los secundarios por debajo de 10 eV. Esto es debido a la activación de algún isótopo.

<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Parasitic_v01.png" alt="drawing" width="400"/>


<img src="Plots01_Victor/ResultsPlot/Pb/Pb206_Parasitic_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb208_Parasitic_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/PbNat_Parasitic_v01.png" alt="drawing" width="400"/>

Después de las medidas de Pb-nat y Pb-208 se ha medido el fondo durante 15 min.

<img src="Plots01_Victor/ResultsPlot/Pb/PbNat_backgrounds.png" alt="drawing" width="400"/>

Como se observa en al figura por debajo de 1 MeV hay diferencias que llegan a ser hasta del 10-15%. 


Estos fondos que he medido después de las medidas de Pb-208 y Pb-Nat, los he sustraido a las mediadas que hemos hecho con Pb-208 y Pb-Nat. Ahora ya no se observa el problema por debajo de 10 eV

<img src="Plots01_Victor/ResultsPlot/Pb/PbNat_Parasitic_UseOfHisOwnBakcground_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb208_Parasitic_UseOfHisOwnBakcground_v01.png" alt="drawing" width="400"/>



Espectros de energia deposositada para los tres plomos, no se observan diferencias significativas. Se ha normalizadp entre 0.2 y 0.8 MeV

<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e-2_1e-1_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e-1_1e0_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e0_1e1_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e1_1e2_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e2_1e3_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e3_1e4_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e4_1e5_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_1e5_1e6_v01.png" alt="drawing" width="400"/>


Espectros de energia deposita para variso rangos de energía

<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_206_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_208_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Pb/Pb_Edep_Nat_v01.png" alt="drawing" width="400"/>


## SmNat 5um

The measurement with the Sm nat of 5 um and 25x25mm. 


<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v03.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v04.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v05.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v06.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v07.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v08.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v09.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v10.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v11.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/SmNat_5um/SmNat_5um_WF_v12.png" alt="drawing" width="400"/>

There are differences in the resonance of the resonance of Sm152 at 8 eV this is due to self-shielding effects because this resonance has big elastic CS and a not negaliable yield.


<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/plot_SmNat_14.68mg_radius1.25cm_v01_c1_v01.png" alt="drawing" width="400"/>


## Sm149 Thick

The values reported from isoflex concerning the contaminations seem to be compatible with our measurment

<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v01.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v02.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v03.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v04.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v05.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v06.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v07.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v08.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v09.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v10.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v11.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v12.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Sm149_Thick_v13.png" alt="drawing" width="400"/>

The problem of this measurment is the self-shielding/Multiple scattering

<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/plot_Sm149_339mg_13mm_v01_c1_v01.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/plot_Sm149_339mg_13mm_v01_c1_v02.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/plot_Sm149_339mg_13mm_v01_c1_v03.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/plot_Sm149_339mg_13mm_v01_c1_v04.png" alt="drawing" width="400"/>
<img src="DatosEnDiscoDuro/ResultsPlot2DHisto/plot_Sm149_339mg_13mm_v01_c1_v05.png" alt="drawing" width="400"/>


The cascade seems not to be horrible. Also there are differences between the resonances with spin 4 ( 0.097, 0.87, 4.94) and the ones with spin 3 (6.43 and 12)

<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Edep_v02.png" alt="drawing" width="400"/>
<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Edep_v01.png" alt="drawing" width="400"/>


As in the case of Er-167

<img src="Plots01_Victor/ResultsPlot/Sm/Sm149_Thick/Edep__NoPrimary_v01.png" alt="drawing" width="400"/>



<img src="" alt="drawing" width="400"/>





<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
<img src="" alt="drawing" width="400"/>
