Programa para fitear los fotopicos de las calibraciones para cada detector. 

Proceso: 

1) Se modifican los parámetros del ajuste en "TACCalibrator.hh"

2) (Opcional) Situar en la misma carpeta el archivo "Cutlist0#.txt", donde # es CUTFILENAME. Si `TREENAME` es "LABR", no se lee/usa CutList. 

3) Compilar con ./doTACCalibrator

4) Ejecutar. Dos formas: 

	4.1) Un único rootfile: >> ` ./TACCalibrator /path/to/rootfile.root 0 `

	4.2) Varios rootfiles consecutivos para acumular estadística: primero añadir la ruta de los archivos en "TACCalibrator.hh", en la variable `ROOTFILEFOLDER`. 
	Y después ejecutar: >> ` ./TACCalibrator [RunNumber] [NumberOfFiles] `

# Ejemplos
## 1- Calibrar un run de Bi-207
> ./TACCalibrator "/media/promojaro/Elements/AdrianSanchez/processed_data/CMT_07/run111860.root" 0

## 2- Calibracion de los runes del Pu-239 (MAR 2023)
### Cs-137
	#define CSYSOURCE 1
	#define NHISTOBINS  700
	#define HISTOLOWLIM 100e3//180e3
	#define HISTOHILIM 710e3
	#define TRIGGERLEVEL 0.9//0.5 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 30e3       // estimation of the FWHM
	#define CUTFILENAME 11 // 

> ./doTACCalibrator && ./TACCalibrator "/mnt/d/AdrianSanchez/processed_data/Pu239_rootfiles/run114667.root" 0

### Ba-133
	#define CSYSOURCE 1
	#define NHISTOBINS  700
	#define HISTOLOWLIM 50e3//180e3
	#define HISTOHILIM 500e3
	#define TRIGGERLEVEL 0.9//0.5 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 30e3       // estimation of the FWHM
	#define CUTFILENAME 11 // 

> ./doTACCalibrator && ./TACCalibrator "/mnt/d/AdrianSanchez/processed_data/Pu239_rootfiles/run114668.root" 0

### Y-88
	#define CSYSOURCE 1
	#define NHISTOBINS 1050
	#define HISTOLOWLIM 100e3
	#define HISTOHILIM 1650e3
	#define TRIGGERLEVEL 0.26 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 40e3      // estimation of the FWHM
	#define CUTFILENAME 11 // 

> ./doTACCalibrator && ./TACCalibrator "/mnt/d/AdrianSanchez/processed_data/Pu239_rootfiles/run114669.root" 0


### Bi-207

	#define CSYSOURCE 1
	#define NHISTOBINS 1050
	#define HISTOLOWLIM 100e3
	#define HISTOHILIM 1000e3
	#define TRIGGERLEVEL 0.26 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 40e3      // estimation of the FWHM
	#define CUTFILENAME 11 // 


> ./doTACCalibrator && ./TACCalibrator "/mnt/d/AdrianSanchez/processed_data/Pu239_rootfiles/run114671.root" 0


### AmBe 

	#define AMBESOURCE 1
	#define NHISTOBINS 500
	#define HISTOLOWLIM 1000e3
	#define HISTOHILIM 3800e3
	#define TRIGGERLEVEL 0.8  //(% of the max value of the no-bkg histo)
	#define FWHM_EST 400e3      // estimation of the FWHM
	#define CUTFILENAME 11 

> ./doTACCalibrator && ./TACCalibrator "/mnt/d/AdrianSanchez/processed_data/Pu239_rootfiles/run114676.root" 0


## [Apr-May-2026] Calibration for LaBr3 at NEL for Pb background tests

### Cs-137 
```c++
	#define CSYSOURCE 1
	#define NHISTOBINS  1000
	#define HISTOLOWLIM 80e3//50e3//180e3
	#define HISTOHILIM 220e3//500e3
	#define TRIGGERLEVEL 0.9//0.5 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 10e3       // estimation of the FWHM
	#define CUTFILENAME 11 // 
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run124964.root 0

### Y-88
```c++
	#define CSYSOURCE 1
  	#define NHISTOBINS 1000
	#define HISTOLOWLIM 100e3
	#define HISTOHILIM 600e3
	#define TRIGGERLEVEL 0.26 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 40e3      // estimation of the FWHM
	#define CUTFILENAME 11 // 
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run124965.root 0

### CmC (multiple files example)

```c++
	#define CMCSOURCE 1
	#define NHISTOBINS 500
	#define HISTOLOWLIM 650e3 //2500
	#define HISTOHILIM 2000e3//5000
	#define TRIGGERLEVEL 0.2  //(% of the max value of the no-bkg histo)
	#define FWHM_EST 100e3      // estimation of the FWHM
	#define CUTFILENAME 11 //
```
> ./doTACCalibrator && ./TACCalibrator 124960 4

### Eu (7 gamma lines)

```c++
	#define CSYSOURCE 1
  	#define NHISTOBINS 2000
	#define HISTOLOWLIM 20e3
	#define HISTOHILIM 290e3
	#define TRIGGERLEVEL 0.10 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 2e3      // estimation of the FWHM
	#define CUTFILENAME 11 // 
```

> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run124959.root 0


---

## [May-2026] Calibration MRR LaBr3 at eLab

### Cs
```c++
	#define CSYSOURCE 1
  	#define NHISTOBINS 500
	#define HISTOLOWLIM 80e3
	#define HISTOHILIM 160e3
	#define TRIGGERLEVEL 0.4 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 5e3      // estimation of the FWHM
	#define CUTFILENAME 11 // 
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run922896.root 0

### Co 
```c++
	#define CSYSOURCE 1
 	#define NHISTOBINS 100
	#define HISTOLOWLIM 140e3
	#define HISTOHILIM 260e3
	#define TRIGGERLEVEL 0.3 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 5e3      // estimation of the FWHM
	#define CUTFILENAME 11 /
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run922885.root 0

### AmBe
```c++
	#define AMBESOURCE 1
	#define NHISTOBINS 200
	#define HISTOLOWLIM 400e3
	#define HISTOHILIM 1000e3
	#define TRIGGERLEVEL 0.6  //(% of the max value of the no-bkg histo)
	#define FWHM_EST 20e3      // estimation of the FWHM
	#define CUTFILENAME 11
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run922881.root 0

## [May-2026] Calibration MRR LaBr3 at EAR1

### Cs
```c++
	#define CSYSOURCE 1
  	#define NHISTOBINS 500
	#define HISTOLOWLIM 80e3
	#define HISTOHILIM 160e3
	#define TRIGGERLEVEL 0.4 //(% of the max value of the no-bkg histo)
	#define FWHM_EST 5e3      // estimation of the FWHM
	#define CUTFILENAME 11 // 
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run125279.root 0

### Eu
```c++
// First group of peaks
  #define CSYSOURCE 1
  #define NHISTOBINS 400
  #define HISTOLOWLIM 15e3
  #define HISTOHILIM 100e3
  #define TRIGGERLEVEL 0.15 //(% of the max value of the no-bkg histo)
  #define FWHM_EST 3e3      // estimation of the FWHM
  #define CUTFILENAME 11 // 
// Second group of peaks
  #define CSYSOURCE 1
  #define NHISTOBINS 200
  #define HISTOLOWLIM 80e3
  #define HISTOHILIM 230e3
  #define TRIGGERLEVEL 0.60 //(% of the max value of the no-bkg histo)
  #define FWHM_EST 6e3      // estimation of the FWHM
  #define CUTFILENAME 11 // 
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run125288.root 0 

### Y
```c++
  #define CSYSOURCE 1
  #define NHISTOBINS 400
  #define HISTOLOWLIM 100e3
  #define HISTOHILIM 400e3
  #define TRIGGERLEVEL 0.3 //(% of the max value of the no-bkg histo)
  #define FWHM_EST 3e3      // estimation of the FWHM
  #define CUTFILENAME 11 // 
```
> ./doTACCalibrator && ./TACCalibrator ~/myWindows/cernbox/2026_Sm_EAR1/processed_rootfiles/run125289.root 0

## [August-2026] Calibration MRR LaBr3 at EAR1


### Eu
```c++
// First group of peaks
  #define CSYSOURCE 1
  #define NHISTOBINS 400
  #define HISTOLOWLIM 15e3
  #define HISTOHILIM 100e3
  #define TRIGGERLEVEL 0.15 //(% of the max value of the no-bkg histo)
  #define FWHM_EST 3e3      // estimation of the FWHM
  #define CUTFILENAME 11 // 
// Second group of peaks
  #define CSYSOURCE 1
  #define NHISTOBINS 200
  #define HISTOLOWLIM 80e3
  #define HISTOHILIM 230e3
  #define TRIGGERLEVEL 0.60 //(% of the max value of the no-bkg histo)
  #define FWHM_EST 6e3      // estimation of the FWHM
  #define CUTFILENAME 11 // 
```
doTACCalibrator && TACCalibrator ../DatosEnDiscoDuro/RootFiles/MichiData/run126032.root 0 
