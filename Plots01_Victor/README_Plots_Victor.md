
# `plot2D` Function Documentation

This document describes the inputs and usage of the `plot2D` function for plotting 2D histograms.

The program uses a definition file with all the inputs for plot.

## Function Parameters

### `NameHisto`  
**Description:** Name of the histogram to project.  
**Options:**  
- `En` → Neutron Energy  
- `Edep` → Deposited energy in the detectors  
- `TOF` → Time of flight  
- `TFlash` → TFlash of the detectors  
- `DeltaTOF` → Difference in time between signals of the same detector  

---

### `MeasurementType`  
**Description:** Specifies the run(s) to plot.  
**Options:** Can be a run number or a type of try run (e.g., `"Sb123"`, `"Au_3"`).

---

### `detN`  
**Description:** Number of the detector.  
**Options:**  
- `0` → sum of all detectors  
- `1, 2, ...` → specific detector  

---

### `EnOrEdepMin` and `EnOrEdepMax`  
**Description:** Limits for the plots.  
**Notes:**  
- For `Edep`, limits are in **energy**.  
- For other histograms, limits are applied in **deposited energy**.  

---

### `PType`  
**Description:** Pulse type to select.  
**Options:**  
- `0` → All pulses  
- `1` → Primary  
- `2` → Parasitic  
- `3` → Other (for `Edep` it is recommended to use `3` rather than `0`)  

---

### `TypeOfPlot`  
**Description:** Defines how the Y-axis is normalized.  
**Options:**  
- `Counts` → Raw counts  
- `CR` → Counts normalized per second per bin width (for `Edep`)  
- `CP` → Counts divided by \(8 \times 10^{12}\) protons  
- `CP1e17` → Counts divided by \(1 \times 10^{17}\) protons  
- `YIELD` → Yield (detector efficiency is not considered)  
- `Yield_Sn_25mm/20mm/13mm` → Specialized yield normalization  

---

### `rebin`  
**Description:** Rebin factor to reduce the number of histogram bins.

---

### `UseBackgroundSubtracted`  
**Type:** `bool`  
**Description:** If `true`, subtracts background histograms (`Empty` and `Background`) as defined in the `DefFile`.

---

### `CompareWithSimul`  
**Type:** `bool`  
**Description:** If `true`, compares data with simulations. Input simulation files are defined in `DefFile`. Supports evaluated yields and Geant4 simulations.

---

### `IfNormalize`  
**Type:** `bool`  
**Description:** If `true`, normalizes the histograms in the ranges defined in the `DefFile`.

---

### `CalculateRatio`  
**Type:** `bool`  
**Description:** If `true`, calculates the ratio of histograms and plots it in a secondary pad.

---

### `IfSaveName`  
**Type:** `string`  
**Description:** Name for saving the output plot. Default is `"-1"` (no save).

---

## Example Usage

```cpp
plot2D({"En_WF"}, {"Sm149_Thick"}, {0}, {0.15}, {9.999}, {1}, "Yield_Sn_13mm",100,1,1,1,1)
plot2D({"En_WF"}, {"SmNat_5um"}, {0}, {0.15}, {9.999}, {1}, "Yield_Sn_25mm",50,1,0,1)
plot2D({"En"}, {"Sm149_Thick","Sm149_Thick_Al","Sm149_Thick_Bi",}, {0}, {0.15}, {9.999}, {1}, "CP",100,1)
plot2D({"Edep"}, {"Y_2"}, {1}, {0.01}, {1}, {3}, "CPulse",1,1,1,1)
plot2D({"Edep"},{"Cs_1","Cs_2","Cs_3","Cs_4","Cs_5","Cs_6","Cs_7","Cs_8","Cs_9"}, {0},{0.15},{9.999}, {3}, "CR", {1}, 1,0,0);
