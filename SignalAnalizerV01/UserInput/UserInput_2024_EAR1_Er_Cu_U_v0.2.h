moreU	   *******************************************************
*                                                     *
*   WARNING: Do not use '~' sign to start the line!   *
*   It marks the beginning of the input parameters!   *
*                                                     *
*******************************************************

VERSION 1 (23-01-2017)
- added parameters for the test
M. Bacak



                                               DETECTOR SPECIFIC PARAMETERS (Lines may be commented with '#' sign!)
===================================================================================================================================================================================================================================
DETECTOR   DETECTOR   DETECTOR STEP   TIMING    MIXED     EXPAND   SMOOTHING   TIME    G-FLASH    G-FLASH     G-FLASH    G-FLASH   BASELINE   BASELINE   AMPLITUDE   AMPLITUDE   AREA/AMP.   AREA/AMP.   SIGNAL WIDTH   SIGNAL WIDTH    NUMBER OF     PULSE SHAPE
  NAME      NUMBER     CLASS   SIZE   FILTER   POLARITY   PULSES    FILTER     LIMIT   OPTION    THRESHOLD   MIN_WIDTH   WINDOW     OPTION     FILTER     OPTION     THRESHOLD   LOW THR.    HIGH THR.     LOW THR.       HIGH THR.    PULSE SHAPES     ADDRESS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


PKUP        0           PSA     300/6     0        0          3        50      100000      0          2000         1         0          -1         300         0          2000       0.0        2000          1             4000              0

###################

SILI        1         PSA    500     0       0         0         0      12e3/1e9    0       30000.        0.          0        0/70      3e4         1          500        300         2000         500            4000     	 	  0
SILI        2         PSA    500     0       0         0         0      12e3/1e9    0       30000.        0.          0        0/70      3e4         1          500        300         2000         500            4000     	 	  0
SILI        3         PSA    500     0       0         0         0      12e3/1e9    0       30000.        0.          0        0/70      3e4         1          500        300         2000         500            4000     	 	  0
SILI        4         PSA    500     0       0         0         0      12e3/1e9    0       30000.        0.          0        0/70      3e4         1          500        300         2000         500            4000     	 	  0

###################

C6D6          1         PSA     6         0         0        0        0     12e3/15e3   0        1000.        100          0          5        1000/0.001     2         10        5          5000           2             500           1 /afs/cern.ch/work/v/valcayne/public/Ta_Er/DataProcessing_v02/UserInput/Sig_C6D6_1_118825_v01.txt                                        
C6D6          2         PSA     6         0         0        0        0     12e3/15e3   0        1000.        100          0          5        1000/0.001     2         10        5          5000           2             500           1 /afs/cern.ch/work/v/valcayne/public/Ta_Er/DataProcessing_v02/UserInput/Sig_C6D6_2_118825_v01.txt                                           
C6D6          3         PSA     6         0         0        0        0     12e3/15e3   0        1000.        100          0          5        1000/0.001     2         10        5          5000           2             500           1 /afs/cern.ch/work/v/valcayne/public/Ta_Er/DataProcessing_v02/UserInput/Sig_C6D6_3_118825_v01.txt                                                          
C6D6          4         PSA     6         0         0        0        0     12e3/15e3   0        1000.        100          0          5        1000/0.001     2         10        5          5000           2             500           1 /afs/cern.ch/work/v/valcayne/public/Ta_Er/DataProcessing_v02/UserInput/Sig_C6D6_4_118825_v01.txt                                                             

################### 

LIGL          1         PSA     30/6      0        0          0       100        1e9       0         10000.       50         0          1          3000        2           200        10.0         2e9          30           5000        1   /afs/cern.ch/work/v/valcayne/public/Ta_Er/DataProcessing_v02/UserInput/Sig_LIGL_1_118891_v01.txt
LABR          1         PSA     7/0.5     0        0          0         0     11.6e3/30e3  0         2000.	  50         0      5/100       1000/100       2           100         0.0        9000       10/30           2000        3  /eos/experiment/ntof/repositories/RAW2ROOT/UserInput/2024/LaBr3_shapes/LowEn_dg.txt /eos/experiment/ntof/repositories/RAW2ROOT/UserInput/2024/LaBr3_shapes/Alpha_dg.txt /eos/experiment/ntof/repositories/RAW2ROOT/UserInput/2024/LaBr3_shapes/HighEn_dg.txt
LACL          1         PSA     30/6      0        0          0         0        1e9       0         10000.       50         30e3       1           700        0           200         1.0        9000       10/30           2000        0

################### 

#Settings for FIMG 
FIMG		1      PSA    24/2.4   0        0        0           0      6.e4       0         300        200         3.e3       1        10000        1             250   	  80         3e2         30           9.e2        2/1        /afs/cern.ch/work/z/zeleme/public/Am241_ANALYSIS/GUI_output/FIMG1_Single_Pulse_With_Bump3.dat /afs/cern.ch/work/z/zeleme/public/Am241_ANALYSIS/GUI_output/FIMG1_Single_Pulse_Without_Bump2.dat /afs/cern.ch/work/z/zeleme/public/Pulses/241Am/Gflash_Subtraction/DEDICATED_GFLASH/gflash_FIMG1.dat
FIMG		2      PSA    24/2.4   0        0        0           0      6.e4       0         300        200         3.e3       1        10000        1             250          70         3e2         30           9.e2        2/1        /afs/cern.ch/work/z/zeleme/public/Am241_ANALYSIS/GUI_output/FIMG2_Single_Pulse_With_Bump2.dat /afs/cern.ch/work/z/zeleme/public/Am241_ANALYSIS/GUI_output/FIMG2_Single_Pulse_Without_Bump2.dat /afs/cern.ch/work/z/zeleme/public/Pulses/241Am/Gflash_Subtraction/DEDICATED_GFLASH/gflash_FIMG2.dat
###################
###################





